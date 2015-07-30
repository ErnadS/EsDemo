#include "nmea_alarm_message_type_s.h"


QString NMEA_Alarm_Message_Type_S::getChannelName() const
{
    return channelName;
}

void NMEA_Alarm_Message_Type_S::setChannelName(const QString &value)
{
    channelName = value;
}

QString NMEA_Alarm_Message_Type_S::getChannelAlarmMessageType() const
{
    return channelAlarmMessageType;

}

void NMEA_Alarm_Message_Type_S::setChannelAlarmMessageType(const QString &value)
{
    channelAlarmMessageType = value;
}
NMEA_Alarm_Message_Type_S::NMEA_Alarm_Message_Type_S(QObject *parent) :
    QObject(parent)
{
}

NMEA_Alarm_Message_Type_S::NMEA_Alarm_Message_Type_S(QString channelName, QString channelAlarmMessageType): QObject(0)
{
    this->channelName = channelName;
    this->channelAlarmMessageType = channelAlarmMessageType;
}

NMEA_Alarm_Message_Type_S::NMEA_Alarm_Message_Type_S(const NMEA_Alarm_Message_Type_S &originalValue) : QObject(0)
{
    *this = originalValue;
}

NMEA_Alarm_Message_Type_S &NMEA_Alarm_Message_Type_S::operator =(const NMEA_Alarm_Message_Type_S &newValue)
{
    this->channelName = newValue.channelName;
    this->channelAlarmMessageType = newValue.channelAlarmMessageType;
    return *this;
}
