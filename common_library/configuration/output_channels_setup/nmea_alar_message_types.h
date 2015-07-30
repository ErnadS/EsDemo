#ifndef NMEA_ALAR_MESSAGE_TYPES_H
#define NMEA_ALAR_MESSAGE_TYPES_H

#include "nmea_alarm_message_type_s.h"

class NMEA_Alar_Message_Types
{
    QList<NMEA_Alarm_Message_Type_S> alrMsgTypes;

    void readSetup();
    void writeSetup();
public:
    NMEA_Alar_Message_Types();

    QString getChannelAlarmMsgType(QString channelName) const;
    void setChannelAlarmMsgType(QString channelName, QString value);


    bool loadFromFile(QString fileSuffix);
    bool saveToFile(QString fileSuffix);
    void getDefaults();
};

#endif // NMEA_ALAR_MESSAGE_TYPES_H

