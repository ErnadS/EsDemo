#include "configuration/system_setup.h"
#include "utility/ip_handler.h"
#include "utility/unitconverter.h"
#include "jb70_aux_setup/default_jb70_aux_setup.h"
#include "utility/code_option.h"
#include "device_info/deviceinfo.h"
#include "udp/udp_61162_450.h"

#include <fcntl.h>
#include <unistd.h>
#include <cstdio>

#include <QDebug>
#include "nmea/nmea_parser.h"

SystemSetup* SystemSetup::systemSetup = 0;

bool SystemSetup::initialSetupReceived = false;

SystemSetup::SystemSetup(QObject *parent) :
    QObject(parent)
{
#ifdef SYSTEM_JB70
    systemType = "JB_70";
#else
    systemType = "CU_M001";
#endif
    versionMsgSequentialIdentifier = 0;
    sendVersionInfo = true;
    systemInStandby = false;
    standbyStateConfirmed = true;


    resetRequestState = REQUEST_IDLE;
    resetLevel = 0;
    resetTimer = new QTimer();
    connect(resetTimer, SIGNAL(timeout()),
            this, SLOT(slotResetTimerTimeout()));

    simulationParameters = new SimulationParameters();

    USB_Update = new Update_From_USB();

    connect(USB_Update, SIGNAL(sigUpdateAvailable()), this, SLOT(slotUpdateAvailable()));
}

void SystemSetup::handleSimulationCommandMsg(MsgICM *msg)
{
    bool simulationStateChange = bool(simulationParameters->getSimulationModeOn() != bool(msg->msgParameters[0]));
    if(msg->msgParameters[5] != (int)WAITING)
        simulationParameters->slotSimulationCommand(msg);
    if(msg->msgParameters[5] == (int)REQUEST)
    {
        if(simulationStateChange && (simulationParameters->getSimulationSource() == SENSOR_FIXED_SPEED))
            return;
        emit sigSendSingleOnUdpOutput(simulationParameters
                                      ->simParamsChangeConfirm());
    }
}

void SystemSetup::handleResetMsg(MsgICM *msg)
{
    MsgICM* replyMsg = msg->clone();

    if(systemType == "JB_70")
    {
        replyMsg->msgParameters[1] = CONFIRMED;
        emit sigSendSingleOnUdpOutput(replyMsg);
        resetToDefault(msg->msgParameters[0]);
    }

    else
    {
        resetToDefault(msg->msgParameters[0]);
        resetRequestState = CONFIRMED;
        delete replyMsg;
    }
}

void SystemSetup::handleSystemStandbyMsg(MsgICM *msg)
{
    if(systemInStandby == msg->msgParameters[0])
    {
        standbyStateConfirmed = true;
        if(systemType == "JB_70")
            emit sigSendSingleOnUdpOutput(new MsgICM(SystemStandby,
                                 QList<int>()<<systemInStandby));
    }
    else
    {
        systemInStandby = msg->msgParameters[0];
        emit sigSendSingleOnUdpOutput(new MsgICM(SystemStandby,
                                 QList<int>()<<systemInStandby));
        emit sigShotDownSensor(systemInStandby);
    }

}
QString SystemSetup::getSystemType() const
{
    return systemType;
}

void SystemSetup::setSystemType(const QString &value)
{
    systemType = value;
}


SystemSetup *SystemSetup::getInstance()
{
    if (systemSetup == 0)
        systemSetup = new SystemSetup();

    return systemSetup;
}

bool SystemSetup::getSetupReceivedFlag()
{
    bool result = (AlarmIDsSetup.getSetupReceivedFlag() && AlarmLimitsSetup.getSetupReceivedFlag()
                   && Dl2Setup.getSetupReceivedFlag() && Jb70Setup.getSetupReceivedFlag() &&
                   Jb70AuxSetup.getSetupReceivedFlag() && OutputChannelsSetup.getSetupReceivedFlag()
                   && calibCoeffs.getSetupReceivedFlag());
    if(result)
        initialSetupReceived = true;

    return result;
}

void SystemSetup::slotSystemSetupMessage(NmeaMessage* msg)
{
    MsgICM* message = static_cast<MsgICM*>(msg);

    int commandId = message->commandID;

    switch (commandId)
    {
        case SimulatinCommand:
            handleSimulationCommandMsg(message);
            break;

        case RestToDefault:
            handleResetMsg(message);
            break;

        case SystemStandby:
            handleSystemStandbyMsg(message);
            break;

        case JBsetupCommand:
            handleJbSetupMsg(message);
            break;

        case DL2setupCommand:
            handleDl2SetupMsg(message);
            break;

        case ALLsetupCommand:
            handleAllSetupMsg(message);
            break;

        case ALIsetupCommand:
            handleAliSetupMsg(message);
            break;

        case AUCLsetupCommand:
            handleAuclSetupMsg(message);
            break;

        case OCFsetupCommand:
            handleOcfSetupMsg(message);
            break;

        case CalibrationCoeffitients:
            handleCalibrationCoeffsMsg(message);
            break;

        case UpdateAvailable:
            handleUpdateMsg(message);
            break;

            default:
                break;

    }

    delete message;

    emit sigSetupChanged(commandId);
}

void SystemSetup::slotResetTimerTimeout()
{





    resetLevel = 0;
}

void SystemSetup::slotUpdateAvailable()
{
    emit sigSendSingleOnUdpOutput( new MsgICM(UpdateAvailable,
                                              QList<int>()<<0));
}

void SystemSetup::checkIfTransferFinished()
{
    if(startUpdate)
    {
        rewriteWholeFile("yess","/opt/version_info/update_available");

        startUpdate = false;
        return;
    }
    if(checkForAppProcess("wget") == false)
    {
        emit sigSendSingleOnUdpOutput( new MsgICM(UpdateAvailable,
                                                  QList<int>()<<1));
        startUpdate = true;
        QTimer::singleShot(60000, this, SLOT(checkIfTransferFinished()));
    }
    else
    {
        transferCounter ++;
        QTimer::singleShot(1000, this, SLOT(checkIfTransferFinished()));
    }
}

void SystemSetup::updateConnectionInfo(QString name, QString ip, QString sfi, QString pairedSfi, int udpGroup) {
    NetInterface* interface;

#ifdef SYSTEM_JB70
    Jb70Setup.setIpAddress(ip);
    Jb70Setup.setLocalID("VD" + sfi);

    if(!IP_handler:: getInstance()->eth0_interface.isNull())
        interface = &IP_handler:: getInstance()->eth0_interface;
    else
        interface = &IP_handler:: getInstance()->eth1_interface;

    //interface = &IP_handler:: getInstance()->eth0_interface;
#else
    CuM001Setup.setIpAddress(ip);
    CuM001Setup.setLocalID ("II" + sfi);
    interface = &IP_handler:: getInstance()->eth1_interface;
#endif
    if(interface->ipAddress != ip)
    {
        interface->setInterfaceIp(ip);
        interface->defGateway = interface->getDefoultGteway();
        IP_handler:: getInstance()->saveInterface();
    }


    QString groupName = UDP_61162_450::groupIndexToName(udpGroup - 1);

#ifdef SYSTEM_JB70
    Jb70Setup.setUnitName(name);
    if (Jb70Setup.getGroup() != groupName) {
        Jb70Setup.setGroup(groupName);
        emit sigUpdateUDP_group();
    }
    sigSendSingleOnUdpOutput(createJbSetupMsg());
#else
    CuM001Setup.setPairedID("VD" + pairedSfi);
    CuM001Setup.setUnitName(name);

    if (CuM001Setup.getGroup() != groupName) {
        CuM001Setup.setGroup(groupName);
        emit sigUpdateUDP_group();
    }
#endif
}

void SystemSetup::handleJbSetupMsg(MsgICM *msg)
{
    QString msgIpAddress = QString::number(msg->msgParameters[0]) + "." + QString::number(msg->msgParameters[1])
            + "." + QString::number(msg->msgParameters[2]) + "." + QString::number(msg->msgParameters[3]);

    QString msgLocalID = Jb70Setup.getLocalID();
    msgLocalID.remove(2,4);

    QString tmp = QString::number(msg->msgParameters[4]);
    while(tmp.count()<4)
        tmp = "0" + tmp;

    msgLocalID += tmp;

    QString msgGroup = getGroup( msg->msgParameters[5]);

    QString msgAlarmID = "AA";
    msgAlarmID[0] = QChar(msg->msgParameters[6]);
    msgAlarmID[1] = QChar(msg->msgParameters[7]);
    msgAlarmID += QString::number(msg->msgParameters[8]);

    int serialNum = msg->msgParameters[9];

    bool updateGroup = false;
    if (msgGroup != Jb70Setup.getGroup())
        updateGroup = true;

    if(updateGroup)
    {
        if(!multicastGroupValid(msgGroup))
            return;
    }

    bool updateSourceAndDestination = false;
    if(msgLocalID != Jb70Setup.getLocalID())
        updateSourceAndDestination = true;

    this->Jb70Setup.setJb70(msgIpAddress, msgLocalID, msgGroup, msgAlarmID/*, msgTime*/, serialNum);

    // Should be sent to all units displaying these configurations?!?!?!?!?!?!?!?!?!?!
    if(systemType == "JB_70")
    {
        NetInterface* interface;
        if(!IP_handler:: getInstance()->eth0_interface.isNull())
            interface = &IP_handler:: getInstance()->eth0_interface;
        else
            interface = &IP_handler:: getInstance()->eth1_interface;

        if(interface->ipAddress != msgIpAddress)
        {
            interface->setInterfaceIp(msgIpAddress);
            interface->defGateway = interface->getDefoultGteway();
            IP_handler:: getInstance()->saveInterface();
        }
        emit sigSendSingleOnUdpOutput(createJbSetupMsg());
    }
    else  // CU (display)
    {
        if(updateSourceAndDestination)
        {
            this->CuM001Setup.setPairedID(msgLocalID);
            emit sigSetupChanged(CUsetupCommand);
        }

        // JB70 UDP group is changed. We have to change also on CuM001 and restart UDP
        if (updateGroup)
        {
            this->CuM001Setup.setGroup(Jb70Setup.getGroup());
            emit sigSetupChanged(CUsetupCommand);
        }

        int version_1 = msg->msgParameters[10];
        int version_2 = msg->msgParameters[11];
        int version_3 = msg->msgParameters[12];

        if ((NmeaParser::isNumberValidInt(version_1) == true) && (NmeaParser::isNumberValidInt(version_2) == true) &&
            (NmeaParser::isNumberValidInt(version_3) == true))
        {
            QString software_version = QString::number(version_1) + "." + QString::number(version_2) + "." + QString::number(version_3);

            Jb70Setup.setSoftwareVersion(software_version);
        }
    }

    // Common for both projects. Notify UDP to change group (NAVD, MISC ...)
    if (updateGroup)
        emit sigUpdateUDP_group();
}

void SystemSetup::handleDl2SetupMsg(MsgICM *msg)
{
    float msgDraft = UnitConverter::intToFloat(msg->msgParameters[0]);
    float msgVesselMaxSpeed = UnitConverter::intToFloat(msg->msgParameters[1]);
    float msgVesselLength = UnitConverter::intToFloat(msg->msgParameters[2]);
    float msgSensorDistanceFromBow = UnitConverter::intToFloat(msg->msgParameters[3]);
    float msgVesselTonnage = UnitConverter::intToFloat(msg->msgParameters[4]);

    int avgTime = msg->msgParameters[5];

    bool avgTimeChanged = avgTime != Dl2Setup.getAveragingTime();
    bool tonnageChanged = msgVesselTonnage != Dl2Setup.getTonnage();

    int msgCurrentCorrection = msg->msgParameters[6];
    bool msgStwOn = msg->msgParameters[7];
    bool msgSogLostBottom = msg->msgParameters[8];
    int msgDockingOptionCode = msg->msgParameters[9];
    int msgOnePercentOption = msg->msgParameters[10];
    int msgSynchBlankingOptionCode = msg->msgParameters[11];
    int msgAutoGpsOnNmeaOptionCode = msg->msgParameters[12];

    int msgShallowWaterPingLenght = msg->msgParameters[13];
    int msgDeepWaterPingLenght = msg->msgParameters[14];
    float msgDepthPingChangeLimit = UnitConverter::intToFloat(msg->msgParameters[15]);
    bool useTwoDecimals = bool(msg->msgParameters[16]);

    bool maxSpeedChanged = Dl2Setup.getVesselMaxSpeed() != msgVesselMaxSpeed;

    if(systemType == "JB_70")
        {
            this->Dl2Setup.setDl2(msgDraft, msgVesselMaxSpeed, msgVesselLength, msgSensorDistanceFromBow,
                                  msgVesselTonnage, avgTime, msgCurrentCorrection, msgStwOn, msgSogLostBottom,
                                  Dl2Setup.getDockingOptionCode(),Dl2Setup.getOnePercentOption(),
                                  Dl2Setup.getSynchBlankingOptionCode(), Dl2Setup.getAutoGpsOnNmeaOptionCode(),
                                  msgShallowWaterPingLenght, msgDeepWaterPingLenght, msgDepthPingChangeLimit,
                                  useTwoDecimals);

            checkOptionCode(msgDockingOptionCode);
        }
    else
    {
        this->Dl2Setup.setDl2(msgDraft, msgVesselMaxSpeed, msgVesselLength, msgSensorDistanceFromBow, msgVesselTonnage,
                              avgTime, msgCurrentCorrection, msgStwOn, msgSogLostBottom, msgDockingOptionCode,
                              msgOnePercentOption, msgSynchBlankingOptionCode, msgAutoGpsOnNmeaOptionCode,
                              msgShallowWaterPingLenght, msgDeepWaterPingLenght, msgDepthPingChangeLimit,
                              useTwoDecimals);
        this->Dl2Setup.setNewSensorFirmware(bool(msg->msgParameters[17]));
    }

    if(maxSpeedChanged)
        emit sigMaxVesselSpeedChanged();

    if(avgTimeChanged || tonnageChanged)
    {
        if(tonnageChanged)
            emit sigSetAveragingPeriodS(-1);
        else if(avgTimeChanged)
            emit sigSetAveragingPeriodS(avgTime);
    }

    if(systemType == "JB_70")
        emit sigSendSingleOnUdpOutput(createDl2SetupMsg());
}

void SystemSetup::handleAllSetupMsg(MsgICM *msg)
{
    float msgStwHighLimit = UnitConverter::intToFloat(msg->msgParameters[0]);
    float msgStwLowLimit = UnitConverter::intToFloat(msg->msgParameters[1]);
    float msgSogHighLimit = UnitConverter::intToFloat(msg->msgParameters[2]);
    float msgSogLowLimit = UnitConverter::intToFloat(msg->msgParameters[3]);
    float msgSpeedLevelHigh1 = UnitConverter::intToFloat(msg->msgParameters[4]);
    float msgSpeedLevelLow1 = UnitConverter::intToFloat(msg->msgParameters[5]);
    float msgSpeedLevelHigh2 = UnitConverter::intToFloat(msg->msgParameters[6]);
    float msgSpeedLevelLow2 = UnitConverter::intToFloat(msg->msgParameters[7]);

    this->AlarmLimitsSetup.setAlarmLimits(msgStwHighLimit, msgStwLowLimit, msgSogHighLimit,
                                                           msgSogLowLimit, msgSpeedLevelHigh1, msgSpeedLevelLow1,
                                                           msgSpeedLevelHigh2, msgSpeedLevelLow2);


    if(systemType == "JB_70")
        emit sigSendSingleOnUdpOutput(msg->clone());
}

void SystemSetup::handleAliSetupMsg(MsgICM *msg)
{

    int msgStwHighAlarmID = msg->msgParameters[0];
    int msgStwLowAlarmID = msg->msgParameters[1];
    int msgSogHighAlarmID = msg->msgParameters[2];
    int msgSogLowAlarmID = msg->msgParameters[3];
    int msgSystemAlarmID = msg->msgParameters[4];
    bool msgUseALR = msg->msgParameters[5];
    int msgEscalationTime = msg->msgParameters[6];

    this->AlarmIDsSetup.setAlarmIDs(msgStwHighAlarmID, msgStwLowAlarmID, msgSogHighAlarmID,
                  msgSogLowAlarmID, msgSystemAlarmID, msgUseALR, msgEscalationTime);

    if(systemType == "JB_70")
        emit sigSendSingleOnUdpOutput(msg->clone());
}

void SystemSetup::handleAuclSetupMsg(MsgICM *msg)
{
    QList<QString> msgAuxFunction = QList<QString>();

    for(int i = 2; i < msg->msgParameters.length(); i += 3)
    msgAuxFunction<<Default_JB70_Aux_Setup::intToFname(msg->msgParameters[i]);

    this->Jb70AuxSetup.setFunctionNames(msgAuxFunction);

    if(systemType == "JB_70")
        emit sigSendSingleOnUdpOutput(msg->clone());
}

void SystemSetup::handleOcfSetupMsg(MsgICM *msg)
{

    QString chanellName = Default_Channels_config::channelList[msg->msgParameters[0]];

    int newBaud = msg->msgParameters[1];
    int oldBaud = OutputChannelsSetup.getChannelBaudRate(chanellName);

    QList<int> parameters = msg->msgParameters;

    this->OutputChannelsSetup.setChannel(parameters);

    if(newBaud != oldBaud)
        emit sigChannelBaudChanged(chanellName, newBaud);

    if(systemType == "JB_70")
        emit sigSendSingleOnUdpOutput(msg->clone());
}

void SystemSetup::handleCalibrationCoeffsMsg(MsgICM *msg)
{
    calibCoeffs.setCalibration(
        UnitConverter::intToFloat(msg->msgParameters[0]),
        UnitConverter::intToFloat(msg->msgParameters[1]),
        UnitConverter::intToFloat(msg->msgParameters[2]),
        UnitConverter::intToFloat(msg->msgParameters[3]),
        UnitConverter::intToFloat(msg->msgParameters[4]),
        UnitConverter::intToFloat(msg->msgParameters[5]),
        UnitConverter::intToFloat(msg->msgParameters[6]));

    emit sigCalibrationCoefsChanged();
    if(systemType == "JB_70")
        emit sigSendSingleOnUdpOutput(msg->clone());
}

void SystemSetup::handleUpdateMsg(MsgICM *msg)
{
    if((msg->msgParameters[0] == 0) && (systemType != "JB_70"))
    {
        QString commandString = "cd /opt/version_info/update\n";
        commandString += "wget http://";
        commandString += Jb70Setup.getIpAddress();
        commandString += "/ui";
        sendCommandToSystem(commandString);
        transferCounter = 0;
        startUpdate =false;
        checkIfTransferFinished();
    }
    else
    {
        sendCommandToSystem("rm /var/www/ui");
        startUpdate = true;
        QTimer::singleShot(60000, this, SLOT(checkIfTransferFinished()));
    }
}

QString SystemSetup::getGroup(int index)
{
    switch (index) {
    case 0:
        return "MISC";
    case 1:
        return "TGTD";
    case 2:
        return "SATD";
    case 3:
        return "NAVD";
    case 4:
        return "VDRD";
    case 5:
        return "RCOM";
    case 6:
        return "TIME";
    case 7:
        return "PROP";

    default:
        return "NAVD";
    }
}

int SystemSetup::getGroupIndex(QString group)
{
    if( group == "MISC")
        return 0;
    if( group == "TGTD")
        return 1;
    if( group == "SATD")
        return 2;
    if( group == "NAVD")
        return 3;
    if( group == "VDRD")
        return 4;
    if( group == "RCOM")
        return 5;
    if( group == "TIME")
        return 6;
    if( group == "PROP")
        return 7;

    return -1;
}

bool SystemSetup::multicastGroupValid(QString group)
{
    if( group == "MISC")
        return true;
    if( group == "TGTD")
        return true;
    if( group == "SATD")
        return true;
    if( group == "NAVD")
        return true;
    if( group == "VDRD")
        return true;
    if( group == "RCOM")
        return true;
    if( group == "TIME")
        return true;
    if( group == "PROP")
        return true;

    return false;
}

void SystemSetup::initiateReset(int level)
{
    resetLevel = level;
    resetRequestState = REQUEST;
    emit sigSendSingleOnUdpOutput(new MsgICM(RestToDefault,
                                             QList<int>()<<resetLevel<< REQUEST));
}

void SystemSetup::resetToDefault(int level)
{
    /*if(level > 6)
    {
        if(!resetTimer->isActive())
        {
            resetLevel = level;
            resetTimer->start(60000);
        }
        return;
    }*/


    AlarmIDsSetup.getDefaults();
    AlarmLimitsSetup.getDefaults();
    Dl2Setup.getDefaults(level);
    Jb70Setup.getDefaults(level);
    if(systemType != "JB_70")
    {
        CuM001Setup.getDefaults(level);
    }
    if(level > 0)
    {
        emit sigMaxVesselSpeedChanged();
        calibCoeffs.setInstalationAngle(0);
    }
    emit sigResetToDefaults();
}


// 12345:   Auto GPS on NMEA (same code for all IDs)
// 14858    1%               (for System ID = 99999)
// 59933    Synchronise      (for System ID = 99999)

void SystemSetup::checkOptionCode(int optCode)
{
    int  serNo = Jb70Setup.getSerialNumber();


    bool onePercentOption = CodeOption::validateOnePercentAccuracyOption(serNo, optCode);
    bool synchOption = CodeOption::validateSyncOption(serNo, optCode);
    bool autoGpsOnNmea = optCode == 123456;

    Dl2Setup.setOnePercentOption((Dl2Setup.getOnePercentOption() + onePercentOption)%2);
    Dl2Setup.setSynchBlankingOptionCode((Dl2Setup.getSynchBlankingOptionCode() + synchOption)%2);
    Dl2Setup.setAutoGpsOnNmeaOptionCode((Dl2Setup.getAutoGpsOnNmeaOptionCode() + autoGpsOnNmea)%2);

    if(Dl2Setup.getSynchBlankingOptionCode() == 0)
        emit sigSynch(false);
}

bool SystemSetup::getSystemInStandby() const
{
    return systemInStandby;
}

void SystemSetup::setSystemInStandby(bool value)
{
    systemInStandby = value;
    standbyStateConfirmed = false;
    emit sigSendSingleOnUdpOutput(new MsgICM(SystemStandby,
                         QList<int>()<<systemInStandby));

    if(systemInStandby)
    {
        // TO DO:
        // Go to sleep.
        // Turn of communicationd, except for UDP,
        // UDP must stay alive, but should ignore
        // all messages except for MsgICM with
        // msgCommand = "SystemStandby" ( 9 ).
    }
    else
    {
        // TO DO:
        // Wake up.
    }
}

bool SystemSetup::getSendVersionInfo() const
{
    return sendVersionInfo;
}

void SystemSetup::setSendVersionInfo(bool value)
{
    sendVersionInfo = value;
}


MsgICM *SystemSetup::createJbSetupMsg()
{
    if(systemType != "JB_70")
        Jb70Setup.setSetupReceivedFlag(false);


    QList<int> masgParameters = QList<int>();

    QList<QString> ipChunks = Jb70Setup.getIpAddress().split(".");
    for(int i = 0; i < ipChunks.length(); i++)
        masgParameters<<ipChunks[i].toInt();

    QString msgLocalId = Jb70Setup.getLocalID();
    msgLocalId.remove(0,2);

    masgParameters<<msgLocalId.toInt();
    masgParameters<<getGroupIndex(Jb70Setup.getGroup());

    QString msgAlarmID = Jb70Setup.getAlarmID();
    masgParameters<<msgAlarmID[0].toLatin1();
    masgParameters<<msgAlarmID[1].toLatin1();
    msgAlarmID.remove(0,2);
    masgParameters<<msgAlarmID.toInt();

    masgParameters<<Jb70Setup.getSerialNumber();

    if (systemType == "JB_70")
    {
        QStringList pieces = Jb70Setup.getSoftwareVersion().split(".");

        for (int i = 0; i < pieces.size(); i++)
        {
            masgParameters << pieces[i].toInt();
        }
    }

    return new MsgICM(JBsetupCommand,
                      masgParameters);
}

MsgICM *SystemSetup::createDl2SetupMsg()
{
    if(systemType != "JB_70")
            Dl2Setup.setSetupReceivedFlag(false);

    return new MsgICM(DL2setupCommand,
                      QList<int>()<<UnitConverter::floatToInt(Dl2Setup.getDraft())
                      <<UnitConverter::floatToInt(Dl2Setup.getVesselMaxSpeed())
                      <<UnitConverter::floatToInt(Dl2Setup.getVesselLength())
                      <<UnitConverter::floatToInt(Dl2Setup.getSensorDistanceFromBow())
                      <<UnitConverter::floatToInt(Dl2Setup.getTonnage())
                      <<Dl2Setup.getAveragingTime()
                      <<Dl2Setup.getCurrentCorrection()
                      <<Dl2Setup.getStwOn()
                      <<Dl2Setup.getSogLostBottom()
                      <<Dl2Setup.getDockingOptionCode()
                      <<Dl2Setup.getOnePercentOption()
                      <<Dl2Setup.getSynchBlankingOptionCode()
                      <<Dl2Setup.getAutoGpsOnNmeaOptionCode()
                      <<Dl2Setup.getShalowWaterPingLenght()
                      <<Dl2Setup.getDeepWaterPingLenght()
                      <<UnitConverter::floatToInt(Dl2Setup.getDepthPingChangeLimit())
                      <<int(Dl2Setup.getUseTwoDecimals())
                      <<int(Dl2Setup.getNewSensorFirmware()));
}

MsgICM *SystemSetup::createAllSetupMsg()
{
    if(systemType != "JB_70")
            AlarmLimitsSetup.setSetupReceivedFlag(false);

    return new MsgICM(ALLsetupCommand,
                      QList<int>()<<UnitConverter::floatToInt(AlarmLimitsSetup.getStwHighLimit())
                      <<UnitConverter::floatToInt(AlarmLimitsSetup.getStwLowLimit())
                      <<UnitConverter::floatToInt(AlarmLimitsSetup.getSogHighLimit())
                      <<UnitConverter::floatToInt(AlarmLimitsSetup.getSogLowLimit())
                      <<UnitConverter::floatToInt(AlarmLimitsSetup.getSpeedLevelHigh1())
                      <<UnitConverter::floatToInt(AlarmLimitsSetup.getSpeedLevelLow1())
                      <<UnitConverter::floatToInt(AlarmLimitsSetup.getSpeedLevelHigh2())
                      <<UnitConverter::floatToInt(AlarmLimitsSetup.getSpeedLevelLow2()));
}

MsgICM *SystemSetup::createAliSetupMsg()
{
    if(systemType != "JB_70")
            AlarmIDsSetup.setSetupReceivedFlag(false);

    return new MsgICM(ALIsetupCommand,
                      QList<int>()<<AlarmIDsSetup.getStwHighAlarmID()
                      <<AlarmIDsSetup.getStwLowAlarmID()
                      <<AlarmIDsSetup.getSogHighAlarmID()
                      <<AlarmIDsSetup.getSogLowAlarmID()
                      <<AlarmIDsSetup.getSystemAlarmID()
                      <<AlarmIDsSetup.getUseALR()
                      <<AlarmIDsSetup.getEscalationTime());
}

MsgICM *SystemSetup::createAuclSetupMsg()
{
    if(systemType != "JB_70")
        Jb70AuxSetup.setSetupReceivedFlag(false);

    QList<int> msgParameters = QList<int>();

    QList<QString> msgAuxNames = Jb70AuxSetup.getAuxNames();
    QList<QString> msgAuxDirections = Jb70AuxSetup.getAuxDirections();
    QList<QString> msgAuxFunction = Jb70AuxSetup.getFunctionNames();

    for(int i = 0; i < msgAuxNames.length(); i++)
        {
            msgParameters<<Default_JB70_Aux_Setup::auxNameToInt(msgAuxNames[i])
                           <<Default_JB70_Aux_Setup::directionToInt(msgAuxDirections[i])
                           <<Default_JB70_Aux_Setup::functionNameToInt(msgAuxFunction[i]);
        }

    return new MsgICM(AUCLsetupCommand, msgParameters);
}

MsgICM *SystemSetup::createOcfSetupMsg(QString channel)
{
    if(systemType != "JB_70")
        OutputChannelsSetup.setSetupReceivedFlag(channel, false);

    return OutputChannelsSetup.getChannelSetupMessage(channel);
}

MsgICM *SystemSetup::createCalibrationCoeffsMsg()
{
    if(systemType != "JB_70")
        calibCoeffs.setSetupReceivedFlag(false);

    return new MsgICM(CalibrationCoeffitients,
                      QList<int>()<<UnitConverter::floatToInt(calibCoeffs.getInstalationAngleDeg())
                      <<UnitConverter::floatToInt(calibCoeffs.getPitchOffsetDeg())
                      <<UnitConverter::floatToInt(calibCoeffs.getRollOffsetDeg())
                      <<UnitConverter::floatToInt(calibCoeffs.getRealTemp1())
                      <<UnitConverter::floatToInt(calibCoeffs.getMeasuredTemp1())
                      <<UnitConverter::floatToInt(calibCoeffs.getRealTemp2())
                      <<UnitConverter::floatToInt(calibCoeffs.getMeasuredTemp2()));
}

MsgVER *SystemSetup::createVersionMsg()
{
    QString sfiNumber = Jb70Setup.getLocalID();
    sfiNumber.remove(0,2);
    MsgVER* msg = new MsgVER(1,1,DeviceInfo::getDeviceType(), DeviceInfo::getVendorID(),
           sfiNumber, QString::number(Jb70Setup.getSerialNumber()),
           DeviceInfo::getModelCode(), DeviceInfo::getSoftwareRevision(),
           DeviceInfo::getHardwareRevision(), versionMsgSequentialIdentifier);

    versionMsgSequentialIdentifier++;

    return msg;
}

QList<NmeaMessage *> SystemSetup::getSetupMsgsListTosend()
{
    QList<NmeaMessage*> resultList;

    if(!standbyStateConfirmed)
    {
        emit sigSendSingleOnUdpOutput(new MsgICM(SystemStandby,
                        QList<int>()<<systemInStandby));
        return resultList;
    }

    if((systemType != "JB_70") && resetRequestState == REQUEST)
    {
        resultList.append(new MsgICM(RestToDefault,
                  QList<int>()<<resetLevel<< REQUEST));
        return resultList;
    }

    if((systemType != "JB_70") && !initialSetupReceived)
        return resultList;

    if(systemType == "JB_70")
    {
        if(AlarmIDsSetup.getSetupReceivedFlag())
            resultList.append(createAliSetupMsg());
        if(AlarmLimitsSetup.getSetupReceivedFlag())
            resultList.append(createAllSetupMsg());
        if(Dl2Setup.getSetupReceivedFlag())
            resultList.append(createDl2SetupMsg());
        if(Jb70Setup.getSetupReceivedFlag())
            resultList.append(createJbSetupMsg());
        if(Jb70AuxSetup.getSetupReceivedFlag())
            resultList.append(createAuclSetupMsg());
        if(OutputChannelsSetup.getSetupReceivedFlag())
        {
            resultList.append(createOcfSetupMsg("Nmea_1"));
            resultList.append(createOcfSetupMsg("Nmea_2"));
            resultList.append(createOcfSetupMsg("UDPM"));
        }
        if(calibCoeffs.getSetupReceivedFlag())
            resultList.append(createCalibrationCoeffsMsg());
    }
    else
    {
        if(!AlarmIDsSetup.getSetupReceivedFlag())
            resultList.append(createAliSetupMsg());
        if(!AlarmLimitsSetup.getSetupReceivedFlag())
            resultList.append(createAllSetupMsg());
        if(!Dl2Setup.getSetupReceivedFlag())
            resultList.append(createDl2SetupMsg());
        if(!Jb70Setup.getSetupReceivedFlag())
            resultList.append(createJbSetupMsg());
        if(!Jb70AuxSetup.getSetupReceivedFlag())
            resultList.append(createAuclSetupMsg());
        if(!OutputChannelsSetup.getSetupReceivedFlag())
        {
            resultList.append(createOcfSetupMsg("Nmea_1"));
            resultList.append(createOcfSetupMsg("Nmea_2"));
            resultList.append(createOcfSetupMsg("UDPM"));
        }
        if(!calibCoeffs.getSetupReceivedFlag())
            resultList.append(createCalibrationCoeffsMsg());
        if(!simulationParameters->getChangeConfirmed())
            resultList.append(simulationParameters->simParamsChangeRequest());
    }
    return resultList;

}

int SystemSetup::sendCommandToSystem(QString command)
{
    int result = -1;
    QByteArray commandByteArray = command.toLatin1();
    char* commandCharArray = new char[command.length() + 1];
    try
    {
        result = sprintf(commandCharArray, commandByteArray.data());
        system(commandCharArray);
        delete[] commandCharArray;
        return result;
    }
    catch (int e)
    {
        delete[] commandCharArray;
        qDebug() << "Error sending command to system:\n " << command;
        qDebug() << "Exception:\n " << e;
        return result;
    }
    return result;
}

bool SystemSetup::fileExists(QString command)
{
    QByteArray commandByteArray = command.toLatin1();
    char* commandCharArray = new char[command.length() + 1];
    bool result = false;
    try
    {
        sprintf(commandCharArray, commandByteArray.data());
        result = (0 == access(commandCharArray, F_OK));
        delete[] commandCharArray;
        return result;
    }
    catch (int e)
    {
        delete[] commandCharArray;
        qDebug() << "Error sending command to system:\n " << command;
        qDebug() << "Exception:\n " << e;
        return result;
    }
    return result;
}

bool SystemSetup::checkForAppProcess(QString appName)
{
    QString command = "pidof " + appName;
    QByteArray commandByteArray = command.toLatin1();
    char* commandCharArray = new char[command.length() + 1];
    bool result = false;
    try
    {
        sprintf(commandCharArray, commandByteArray.data());
        result = (0 == system(commandCharArray));
        delete[] commandCharArray;
        return result;
    }
    catch (int e)
    {
        delete[] commandCharArray;
        qDebug() << "Error sending command to system:\n " << command;
        qDebug() << "Exception:\n " << e;
        return result;
    }
    return result;
}

bool SystemSetup::rewriteWholeFile(QString text, QString filePath)
{
    char descriptorPath[100];
    QByteArray bArr = filePath.toLatin1();
    sprintf(descriptorPath, bArr.data());

    int  fdWriteTo = open(descriptorPath, O_WRONLY | O_TRUNC | O_CREAT, 0644);

    int lenght = text.length() + 1;

    QByteArray bArr1 = text.toLatin1();
    char* data = new char[lenght];
    sprintf(data, bArr1.data());

    try
    {
        if(write(fdWriteTo, data, lenght) != lenght)
        {
            close(fdWriteTo);
            delete[] data;
            qDebug() << "Error in writing to file!!!";
            return false;
        }
        else
        {
            #if defined(Q_OS_WIN)
            {
                _commit(fdWriteTo);
            }
            #else
            {
                fsync(fdWriteTo);
            }
            #endif

            close(fdWriteTo);
            delete[] data;
            return true;
        }
    }
    catch (int e)
    {
        close(fdWriteTo);
        delete[] data;
        qDebug() << "Error in serialization: " << e;
        return false;
    }
    return false;

}
