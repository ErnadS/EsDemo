#ifndef SYSTEMSETUP_H
#define SYSTEMSETUP_H

#include <QObject>
#include <QTimer>
#include "configuration/alarm_ids_setup/alarmids_setup.h"
#include "configuration/alarm_limits_setup/alarmlimits_setup.h"
#include "cu_m001_setup/cu_m_001_setup.h"
#include "dl2_setup/dl2_setup.h"
#include "jb70_setup/jb70_setup.h"
#include "trip_setup/triptotal_setup.h"
#include "jb70_aux_setup/jb70_aux_setup.h"
#include "output_channels_setup/outpu_channels_setup.h"
#include "calibration/calibration.h"
#include "simulation_parameters/simulationparameters.h"
#include "update_manager/update_from_usb.h"

#include "nmea/nmea_include.h"

enum CurrentCorrectionEnum {
    SOG_FORM_GPS,
    SOG_FROM_DL2,
    SOG_AUTO
};

enum SetupIDs {
    Jb70SetupID = 1,
    Dl2SetupID = 2,
    CuM001SetupID = 3,
    Jb70AuxSetupID = 4,
    OutputChannelsSetupID = 5,
    AlarmLimitsSetupID = 6,
    AlarmIDsSetupID = 7,
    CalibrationCoeff = 8
};

class SystemSetup : public QObject
{
    Q_OBJECT

    explicit SystemSetup(QObject *parent = 0);
    static SystemSetup* systemSetup;

    static bool initialSetupReceived;

    QString systemType;

    void handleSimulationCommandMsg(MsgICM *msg);
    void handleResetMsg(MsgICM *msg);
    void handleSystemStandbyMsg(MsgICM *msg);
    void handleJbSetupMsg (MsgICM *msg); // Command ID 10
    void handleDl2SetupMsg(MsgICM * msg);
    void handleAllSetupMsg(MsgICM *msg);
    void handleAliSetupMsg(MsgICM *msg);
    void handleAuclSetupMsg(MsgICM * msg);
    void handleOcfSetupMsg(MsgICM *msg);
    void handleCalibrationCoeffsMsg(MsgICM* msg);
    void handleUpdateMsg(MsgICM* msg);

    QString getGroup(int index);

    void checkOptionCode(int optCode);

    int versionMsgSequentialIdentifier;
    bool sendVersionInfo;

    bool systemInStandby;
    bool standbyStateConfirmed;

    msgRequestState resetRequestState;
    int resetLevel;
    QTimer* resetTimer;
    void resetToDefault(int level);

    int sendCommandToSystem(QString command);
    bool fileExists(QString command);
    bool checkForAppProcess(QString appName);
    bool rewriteWholeFile(QString text, QString filePath);

    int transferCounter;
    bool startUpdate;

public:

    Update_From_USB* USB_Update;

    AlarmIDs_Setup AlarmIDsSetup;
    AlarmLimits_Setup AlarmLimitsSetup;
    CU_M_001_Setup CuM001Setup;
    DL2_Setup Dl2Setup;
    JB70_Setup Jb70Setup;
    TripTotal_Setup TripTotalSetup;
    JB70_Aux_Setup Jb70AuxSetup;
    Outpu_Channels_Setup OutputChannelsSetup;

    calibration calibCoeffs;
    SimulationParameters* simulationParameters;

    MsgICM *createJbSetupMsg (); // Command ID 10
    MsgICM *createDl2SetupMsg();
    MsgICM *createAllSetupMsg();
    MsgICM *createAliSetupMsg();
    MsgICM *createAuclSetupMsg();
    MsgICM *createOcfSetupMsg(QString channel);// Command ID 15
    MsgICM *createCalibrationCoeffsMsg();// Command ID 25

    MsgVER *createVersionMsg();// Command ID 25

    QList<NmeaMessage*> getSetupMsgsListTosend();

    static SystemSetup* getInstance();

    bool getSetupReceivedFlag();

    QString getSystemType() const;
    void setSystemType(const QString &value);

    void updateConnectionInfo(QString name, QString ip, QString sfi, QString pairedSfi, int udpGroup);

    bool getSendVersionInfo() const;
    void setSendVersionInfo(bool value);

    bool getSystemInStandby() const;
    void setSystemInStandby(bool value);

    int getGroupIndex(QString group);

    static bool multicastGroupValid(QString group);

    void initiateReset(int level);

signals:
    void sigSendSingleOnUdpOutput(NmeaMessage *msg);
    void sigSetupChanged(int type);
    void sigChannelBaudChanged(QString outputChannelName, int baudRate);
    void sigUpdateUDP_group();
    void sigMaxVesselSpeedChanged();
    void sigSetAveragingPeriodS(int averagingLenght);

    void sigResetToDefaults();

    void sigSynch(bool synch);

    void sigCalibrationCoefsChanged();
    void sigShotDownSensor(bool bOn);

public slots:
    void slotSystemSetupMessage(NmeaMessage *msg);

private slots:
    void slotResetTimerTimeout();
    void slotUpdateAvailable();
    void checkIfTransferFinished();


};

#endif // SYSTEMSETUP_H
