#include "udp_multicast_interface.h"
#include "configuration/system_setup.h"
#include "configuration/system_configuration.h"

MsgIDM *UdpMulticastInterface::getAckMsg(NmeaMessage *msg)
{
    QString fullType = sendingStack.getFullType(msg);

    return getAckMsg(fullType, false);
}

MsgIDM *UdpMulticastInterface::getAckMsg(QList<NmeaMessage *> msgList)
{
    QString fullType = sendingStack.getListFullType(msgList);

    return getAckMsg(fullType, true);
}

MsgIDM *UdpMulticastInterface::getAckMsg(QString fullType, bool isGroupMsg)
{
    int groupMsg = int(isGroupMsg);

    return new MsgIDM(MsgAck, QList<QString>()
                  <<QString::number(groupMsg)
                  <<fullType);
}

void UdpMulticastInterface::handleAckMsg(MsgIDM *ackMsg, QString msgSource)
{
    bool isGroupAck = bool((ackMsg->msgParameters[0]).toInt());
    QString msgFullType = ackMsg->msgParameters[1];

    if(isGroupAck)
    {
        int stackedGroupIndex = -1;
        QList<QString> msgTypes;

        for(int i = 0; i < sendingStack.groupMsgList.length(); i++)
        {
            if(sendingStack.getListFullType(sendingStack.groupMsgList[i]) == msgFullType)
            {
                stackedGroupIndex = i;
            }
        }
        if(stackedGroupIndex != -1)
        {
            for(int i = 0; i < sendingStack.groupMsgList[stackedGroupIndex].length(); i++)
            {
                msgTypes<<sendingStack.getFullType(sendingStack.groupMsgList[stackedGroupIndex][i]);
            }
        }

        ackedStatus.ackMsgList(msgTypes, msgSource);
    }
    else
    {
        ackedStatus.ackMsg(ackMsg->msgParameters[1], msgSource);

        if(isStackedMsgAcked(msgFullType))
            sendingStack.removeFromStack(msgFullType, false);
    }
    for(int i = 0; i < sendingStack.groupMsgList.length(); i++)
    {
        if(isStackedGroupAcked(i))
        {
            sendingStack.removeGroupFromStack(i);
        }
    }
}

bool UdpMulticastInterface::isStackedGroupAcked(int stackedGroupIndex)
{
    QString fullType;
    for(int i = 0; i < sendingStack.groupMsgList[stackedGroupIndex].length(); i++)
    {
        fullType = sendingStack.getFullType(sendingStack.groupMsgList[stackedGroupIndex][i]);
        if(!ackedStatus.getMessageAcked(fullType))
            return false;
    }
    return true;
}

bool UdpMulticastInterface::isStackedMsgAcked(QString msgFullType)
{
    return ackedStatus.getMessageAcked(msgFullType);
}

void UdpMulticastInterface::checkExpiryTime()
{
    for(int i = 0; i < ackedStatus.ackRequiredMsgTypes.length(); i++)
    {
        if(!ackedStatus.getMessageAcked(ackedStatus.ackRequiredMsgTypes[i]))
        {
            if(ackedStatus.isExpired(i))
            {
                foreach (QString device, ackedStatus.pairedDevices)
                {
                    MsgIDM* ackMsg = getAckMsg(ackedStatus.ackRequiredMsgTypes[i], false);
                    handleAckMsg(ackMsg, device);
                    delete ackMsg;
                }
            }
        }
    }
}

void UdpMulticastInterface::handleConnectionRequest(QString sourceSfi, QString msgCommand)
{
    if(SystemSetup::getInstance()->getSystemType() == "JB_70")
    {
        if(msgCommand != "Request")
            return;

        bool sfiValid = true;
        for(int i = 0; i < ackedStatus.pairedDevices.length(); i++)
        {
            if(ackedStatus.pairedDevices[i] == sourceSfi)
                sfiValid = false;
        }

        if(sfiValid)
        {
            ackedStatus.addPairedDevice(sourceSfi);
            slotSendSingleMsg(new MsgIDM(ConnectionRequest, QList<QString>()
                                         <<"Confirm"),false);
        }
        else
            slotSendSingleMsg(new MsgIDM(ConnectionRequest, QList<QString>()
                                         <<"Deny"),false);
    }
    else
    {
        if(sourceSfi != SystemConfiguration::getDestination())
            return;
        if(msgCommand == "Confirm")
        {
            connected = true;
            ackedStatus.addPairedDevice(sourceSfi);
            localSfi = SystemConfiguration::getSource();
        }
    }
}

UdpMulticastInterface::UdpMulticastInterface(QObject *parent) :
    QObject(parent)
{
    connected = false;
    localSfi = SystemConfiguration::getSource();
    udp61162_450 = new UDP_61162_450();
    connect(udp61162_450, SIGNAL(sigHandleUdpMulticast(UdpMulticastGroupMsg*)),this,
            SLOT(slotHandleUdpMulticast(UdpMulticastGroupMsg*)));

    sendingTimer = new QTimer(this);
    // Resending of messages that have not been acked
    connect(sendingTimer, SIGNAL(timeout()), this, SLOT(sendingTimerTimeout()));
    sendingTimer->start(1000);

    // List of messages that need acknowledgement
    QList<QString> needsAck = QList<QString>()
            << "ICM5"
            << "ICM6"
            << "ICM7"
            << "ICM8"
            << "ICM9"
            << "ICM10"
            << "ICM11"
            << "ICM12"
            << "ICM13"
            << "ICM14"
            << "ICM15"
            << "ICM16"
            << "ICM18"
            << "ICM21"
            << "ICM24"
            << "ICM25"
            << "ICM27"
            << "ICM28"
            << "ICM25"
            << "IDM11"
            << "ICM33"
            << "ALRS"
            << "DDC";

    for(int i = 0; i < needsAck.length(); i++)
        ackedStatus.addAckRequiredMsgType(needsAck[i]);
    /*
    MsgAck = 0,
    DockingModeOn = 5,
    DockingModeOff = 6,
    SimulatinCommand = 7,
    RestToDefault = 8,
    SystemStandby = 9,
    JBsetupCommand = 10,
    DL2setupCommand = 11,
    ALLsetupCommand = 12,
    ALIsetupCommand = 13,
    AUCLsetupCommand = 14,
    OCFsetupCommand = 15,
    CUsetupCommand = 16,
    SetupReceivedConfirmationCommand = 17, // Should be removed
    CalibrationCommand = 18,
    SendMeConfigurationCommand = 19,
    FitnessConfirmCommand = 20,
    CalibrationPointCommand = 21,
    DataForManualCalibrationCommand = 22,
    DataForSemiAutoCalibrationCommand = 23,
    CurrentCalibrationpoints = 24,
    CalibrationCoeffitients = 25,
    AuxStatesCommand = 26,
    CalibrationPointAccepted = 27,
    CalibrationPointRejected = 28,
    DataForTempCalibrationCommand = 29,
    DataForTiltCalibrationCommand = 30

    ***IDM***
    SelfTestData = 9,
    CommunicationDiagnostics = 10,
    StartSelfTest = 11,
    StartDiagnosticsTest = 12*/
}

bool UdpMulticastInterface::init()
{
    return udp61162_450->init();
}

void UdpMulticastInterface::updateUdpGroup()
{
    udp61162_450->updateUdpGroup();
}

qint64 UdpMulticastInterface::sendMulticastMsg(QByteArray array)
{
    return udp61162_450->sendMulticastMsg(array);
}

void UdpMulticastInterface::requestConnection()
{
    NmeaMessage* msg = new MsgIDM(ConnectionRequest, QList<QString>()
                  <<"Request");
    slotSendSingleMsg(msg,false);
}

int UdpMulticastInterface::groupNameToIndex(QString groupName)
{
    return UDP_61162_450::groupNameToIndex(groupName);
}

QString UdpMulticastInterface::groupIndexToName(int nIndex)
{
    return UDP_61162_450::groupIndexToName(nIndex);
}

void UdpMulticastInterface::slotSendSingleMsg(NmeaMessage *message, bool notInStack)
{
    // Test
    //delete message;
    //return;
    /////////////////////
    if(SystemSetup::getInstance()->getSystemInStandby())
    {
       if(message->messageType() == "ICM")
       {
           MsgICM* icmMsg = static_cast<MsgICM*>(message);
           if(icmMsg->commandID != SystemStandby)
           {
               delete message;
               return;
           }
       }
       else
       {
           delete message;
           return;
       }
    }

    QByteArray testBuff;

    if(SystemConfiguration::getSystemType() == "JB_70")
    {
        UdpMulticastSingleMsg udpMsg =
                UdpMulticastCreator::createSingleMsg(message);
        testBuff = udpMsg.getCompletMsgArray();
    }
    else
    {
        UdpMulticastSingleMsg udpMsg =
                UdpMulticastCreator::createSingleMsgWithDest(message);
        testBuff = udpMsg.getCompletMsgArray();
    }
    if (!udp61162_450->sendMulticastMsg(testBuff))
    {
        qDebug() << "Error sending msg on UDP\r\n";
        delete(message);
    }
    else
    {
        if(notInStack)
        {
            QString fullType = sendingStack.getFullType(message);
            if(ackedStatus.messageNeedsAck(fullType))
            {
                ackedStatus.resetMsgAcked(fullType);
                sendingStack.addSingleTostack(message);
            }
            else
                delete message;
        }
    }
}

void UdpMulticastInterface::slotSendListOfMsgs(QList<NmeaMessage *> messageList, bool notInStack)
{
    // Test
    /*foreach (NmeaMessage* msg, messageList)
        delete msg;
    return;*/
    /////////////////////
    if(SystemSetup::getInstance()->getSystemInStandby())
    {
        foreach (NmeaMessage* msg, messageList)
            delete msg;
        return;
    }

    QByteArray testBuff;

    if(SystemConfiguration::getSystemType() == "JB_70")
    {
        UdpMulticastGroupMsg udpMsg = UdpMulticastCreator::createGroupMessageNoDest(messageList);
        testBuff = udpMsg.getCompletMsgArray();
    }
    else
    {
        UdpMulticastGroupMsg udpMsg = UdpMulticastCreator::createGroupMessageWithDest(messageList);
        testBuff = udpMsg.getCompletMsgArray();
    }

    qint64 ret = udp61162_450->sendMulticastMsg(testBuff);
    if (ret <= 0)
    {
        qDebug() << "Error sending UDP multicast msg\r\n";
        foreach (NmeaMessage* msg, messageList)
            delete msg;
    }
    else
    {
        if(notInStack)
        {
            bool addToStack = false;
            for(int i = 0; i < messageList.length(); i++)
                {
                    QString fullType = sendingStack.getFullType(messageList[i]);
                    if(ackedStatus.messageNeedsAck(fullType))
                    {
                        ackedStatus.resetMsgAcked(fullType);
                        addToStack = true;
                    }
                }
            if(addToStack)
                sendingStack.addGroupTostack(messageList);
            else
            {
                foreach (NmeaMessage* msg, messageList)
                    delete msg;
            }
        }
    }
}

void UdpMulticastInterface::sendingTimerTimeout()
{
    if(SystemSetup::getInstance()->getSystemInStandby() == false)
    {
        for(int i = 0;  i< sendingStack.singleMsgList.length(); i ++)
        {
            if(!ackedStatus.getMessageAcked(sendingStack.singleMsgList[i]->messageType()))
                slotSendSingleMsg(sendingStack.singleMsgList[i], false);
        }
        for(int i = 0; i < sendingStack.groupMsgList.length(); i++)
        {
            for(int j = 0; j < sendingStack.groupMsgList[i].length(); j++)
            {
                if(!ackedStatus.getMessageAcked(sendingStack.groupMsgList[i][j]->messageType()))
                {
                    slotSendListOfMsgs(sendingStack.groupMsgList[i], false);
                    break;
                }
            }
        }


        ackedStatus.increaseDisconnectCounters();
        if(SystemSetup::getInstance()->getSystemType() != "JB_70")
        {
            if(connected)
            {
                if((ackedStatus.pairedDevices.length() == 0) ||
                   (ackedStatus.pairedDevices[0] != SystemConfiguration::getDestination()) ||
                   (localSfi != SystemConfiguration::getSource()))
                connected = false;
            }

            if(!connected)
            {
                ackedStatus.pairedDevices.empty();
                requestConnection();
            }
        }
    }

    checkExpiryTime();
}

void UdpMulticastInterface::slotHandleUdpMulticast(UdpMulticastGroupMsg *udpMulticastGroupMsg)
{
    if(SystemSetup::getInstance()->getSystemInStandby())
    {
        if(udpMulticastGroupMsg->msgsList.length() == 1)
        {
            NmeaMessage* message = udpMulticastGroupMsg->msgsList[0]->nmeaMessage;
            if(message->messageType() == "ICM")
            {
                MsgICM* icmMsg = static_cast<MsgICM*>(message);
                if(icmMsg->commandID != SystemStandby)
                {
                    delete message;
                    delete udpMulticastGroupMsg;
                    return;
                }
            }
            else
            {
                delete message;
                delete udpMulticastGroupMsg;
                return;
            }
        }
        else
        {
            for(int i = 0; i < udpMulticastGroupMsg->msgsList.length(); i++)
                delete udpMulticastGroupMsg->msgsList[i]->nmeaMessage;
            delete udpMulticastGroupMsg;
            return;
        }
    }

    // Test:
    //////////////////////////////////
    /*for(int i = 0; i < udpMulticastGroupMsg->msgsList.length(); i++)
        delete udpMulticastGroupMsg->msgsList[i]->nmeaMessage;
    delete udpMulticastGroupMsg;
    return;*/
    ////////////////////////////////////
    if (!udpMulticastGroupMsg->bValid) {
        qDebug() << "INVALID UDP MSG \r\n";

        foreach (UdpMulticastSingleMsg* single, udpMulticastGroupMsg->msgsList)
        {
           if (single->nmeaMessage != NULL)
           {
               if(SystemSetup::getInstance()->getSystemType() == "JB_70")
                emit sigSendDiagnosticsInfo("UDPM", "IN", single->nmeaMessage->clone());

               delete single->nmeaMessage;
               single->nmeaMessage = NULL;
           }
        }

        delete udpMulticastGroupMsg;
        return;
    }

    QString sourceSfi = udpMulticastGroupMsg->msgsList[0]->udpSourceTag->sfi;
    ackedStatus.resetDisconnectCounter(sourceSfi);

    if(udpMulticastGroupMsg->msgsList.length() == 1)
    {
        NmeaMessage* message = udpMulticastGroupMsg->msgsList[0]->nmeaMessage;

        if(SystemSetup::getInstance()->getSystemType() == "JB_70")
            emit sigSendDiagnosticsInfo("UDPM", "IN", message->clone());

        if(message->messageType() == "IDM")
        {
            MsgIDM* idmMsg = static_cast<MsgIDM*>(message);
            if(idmMsg->commandID == MsgAck)
            {
                handleAckMsg(idmMsg, sourceSfi);
                delete message;
                delete udpMulticastGroupMsg;
                return;
            }
            else if(idmMsg->commandID == ConnectionRequest)
            {
                QString sourceSfi = udpMulticastGroupMsg->msgsList[0]->udpSourceTag->sfi;
                QString msgCommand = idmMsg->msgParameters[0];
                handleConnectionRequest(sourceSfi, msgCommand);
                delete message;
                delete udpMulticastGroupMsg;
                return;
            }
        }
        if(ackedStatus.messageNeedsAck(sendingStack.getFullType(message)))
        {
            slotSendSingleMsg(getAckMsg(message));
        }

        emit sigNmeaMsgReceived(message->clone());
        delete message;
        delete udpMulticastGroupMsg;
        return;
    }

    else
    {
        bool sendAck = false;
        QString fullType = "";
        for(int i = 0; i < udpMulticastGroupMsg->msgsList.length(); i++)
        {
            NmeaMessage* message = udpMulticastGroupMsg->msgsList[i]->nmeaMessage;

            if(SystemSetup::getInstance()->getSystemType() == "JB_70")
                emit sigSendDiagnosticsInfo("UDPM", "IN", message->clone());

            QString singleMsgFullType = sendingStack.getFullType(message);
            fullType += singleMsgFullType;
            if(ackedStatus.messageNeedsAck(singleMsgFullType))
                sendAck = true;

            emit sigNmeaMsgReceived(message->clone());
            delete message;
        }
        if(sendAck)
        {
            slotSendSingleMsg(getAckMsg(fullType, true));
        }
        delete udpMulticastGroupMsg;
    }
}
