#ifndef OUTPU_CHANNELS_SETUP_H
#define OUTPU_CHANNELS_SETUP_H

#include "singlechannelsetup.h"
#include "nmea_bauds_setup.h"
#include "nmea_alar_message_types.h"
#include "nmea_decimals_setup.h"
#include "nmea/nmea_include.h"

#define OUTPUT_NAME_NMEA_0       "Nmea_1"
#define OUTPUT_NAME_NMEA_1       "Nmea_2"
#define OUTPUT_NAME_UDP          "UDPM"

#define OUTPUT_ID_NMEA_1        1
#define OUTPUT_ID_NMEA_2        2
#define OUTPUT_ID_SENSOR        3
#define OUTPUT_ID_UDP           4

class Outpu_Channels_Setup
{

    QList<SingleChannelSetup> outputChannels;
    NMEA_Bauds_Setup nmeaBauds;

    NMEA_Alar_Message_Types nmeaAlrTypes;

    NMEA_Decimals_Setup nmeaDecimals;

    QList<int> getAvailableMsgsEnabled(int index);

    QList<bool> chSetupReceivedFlag;

public:
    Outpu_Channels_Setup();

    MsgICM *getChannelSetupMessage(QString chName);

    void setChannel(QList<int> msgParameters);

    void setEnabled(QString chName, QString msgType, bool enable);
    bool isEnabled(QString msgType, QString chName);

    bool isEnabledByAny(QString msgType);

    int getChannelBaudRate(QString chName) const;
    void setChannelBaudRate(QString chName, int value);

    bool getChannelUseTwoDecimals(QString chName) const;
    void setChannelUseTwoDecimals(QString chName, bool value);


    QString getChannelAlarmMsgType(QString chName) const;
    void setChannelAlarmMsgType(QString chName, QString value);

    QList<QString> getAvailableMsgsTypes(QString chName);
    QList<bool> getAvailableMsgsEnabled(QString chName);

    bool getSetupReceivedFlag();
    void setSetupReceivedFlag(QString chName, bool value);

    bool isAlarmOutputEnabled(QString chName);
    void getDefaults();
};

#endif // OUTPU_CHANNELS_SETUP_H
