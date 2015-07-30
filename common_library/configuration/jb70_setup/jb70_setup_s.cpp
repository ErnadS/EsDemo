#include "jb70_setup_s.h"


QString JB70_Setup_S::getIpAddress() const
{
    return ipAddress;
}

void JB70_Setup_S::setIpAddress(const QString &value)
{
    ipAddress = value;
}

QString JB70_Setup_S::getLocalID() const
{
    return localID;
}

void JB70_Setup_S::setLocalID(const QString &value)
{
    localID = value;
}

QString JB70_Setup_S::getGroup() const
{
    return group;
}

void JB70_Setup_S::setGroup(const QString &value)
{
    group = value;
}

QString JB70_Setup_S::getAlarmID() const
{
    return alarmID;
}

void JB70_Setup_S::setAlarmID(QString value)
{
    alarmID = value;
}

QString JB70_Setup_S::getUnitName() const
{
    return unitName;
}

void JB70_Setup_S::setUnitName(const QString &value)
{
    unitName = value;
}


quint32 JB70_Setup_S::getSerialNumber() const
{
    return serialNumber;
}

void JB70_Setup_S::setSerialNumber(quint32 value)
{
    serialNumber = value;
}
JB70_Setup_S::JB70_Setup_S(QObject *parent) :
    QObject(parent)
{
}
