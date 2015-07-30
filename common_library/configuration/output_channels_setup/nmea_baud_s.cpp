#include "nmea_baud_s.h"


QString NMEA_Baud_S::getChannelName() const
{
    return channelName;
}

void NMEA_Baud_S::setChannelName(const QString &value)
{
    channelName = value;
}

int NMEA_Baud_S::getChannelBaud() const
{
    return channelBaud;
}

void NMEA_Baud_S::setChannelBaud(int value)
{
    channelBaud = value;
}
NMEA_Baud_S::NMEA_Baud_S(QObject *parent) :
    QObject(parent)
{
}

NMEA_Baud_S::NMEA_Baud_S(QString channelName, int channelBaud) : QObject(0)
{
    this->channelName = channelName;
    this->channelBaud = channelBaud;
}

NMEA_Baud_S::NMEA_Baud_S(const NMEA_Baud_S &originalValue) : QObject(0)
{
    *this = originalValue;
}

NMEA_Baud_S &NMEA_Baud_S::operator =(const NMEA_Baud_S &newValue)
{
    this->channelName = newValue.channelName;
    this->channelBaud = newValue.channelBaud;
    return *this;
}
