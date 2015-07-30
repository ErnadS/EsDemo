#include "nmea_use_two_decimals_s.h"

QString NMEA_Use_Two_Decimals_S::getChannelName() const
{
    return channelName;
}

void NMEA_Use_Two_Decimals_S::setChannelName(const QString &value)
{
    channelName = value;
}

bool NMEA_Use_Two_Decimals_S::getUseTwoDecimals() const
{
    return useTwoDecimals;
}

void NMEA_Use_Two_Decimals_S::setUseTwoDecimals(bool value)
{
    useTwoDecimals = value;
}

NMEA_Use_Two_Decimals_S::NMEA_Use_Two_Decimals_S(QObject *parent) :
    QObject(parent)
{
}

NMEA_Use_Two_Decimals_S::NMEA_Use_Two_Decimals_S(QString channelName, int useTwoDecimals): QObject(0)
{
    this->channelName = channelName;
    this->useTwoDecimals = useTwoDecimals;
}

NMEA_Use_Two_Decimals_S::NMEA_Use_Two_Decimals_S(const NMEA_Use_Two_Decimals_S &originalValue) : QObject(0)
{
    *this = originalValue;
}

NMEA_Use_Two_Decimals_S &NMEA_Use_Two_Decimals_S::operator =(const NMEA_Use_Two_Decimals_S &newValue)
{
    this->channelName = newValue.channelName;
    this->useTwoDecimals = newValue.useTwoDecimals;
    return *this;
}
