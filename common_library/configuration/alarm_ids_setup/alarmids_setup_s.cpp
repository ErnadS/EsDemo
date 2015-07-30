#include "alarmids_setup_s.h"


int AlarmIDs_Setup_S::getStwHighAlarmID() const
{
    return stwHighAlarmID;
}

void AlarmIDs_Setup_S::setStwHighAlarmID(int value)
{
    stwHighAlarmID = value;
}

int AlarmIDs_Setup_S::getStwLowAlarmID() const
{
    return stwLowAlarmID;
}

void AlarmIDs_Setup_S::setStwLowAlarmID(int value)
{
    stwLowAlarmID = value;
}

int AlarmIDs_Setup_S::getSogHighAlarmID() const
{
    return sogHighAlarmID;
}

void AlarmIDs_Setup_S::setSogHighAlarmID(int value)
{
    sogHighAlarmID = value;
}

int AlarmIDs_Setup_S::getSogLowAlarmID() const
{
    return sogLowAlarmID;
}

void AlarmIDs_Setup_S::setSogLowAlarmID(int value)
{
    sogLowAlarmID = value;
}

int AlarmIDs_Setup_S::getSystemAlarmID() const
{
    return systemAlarmID;
}

void AlarmIDs_Setup_S::setSystemAlarmID(int value)
{
    systemAlarmID = value;
}

bool AlarmIDs_Setup_S::getUseALR() const
{
    return useALR;
}

void AlarmIDs_Setup_S::setUseALR(bool value)
{
    useALR = value;
}

int AlarmIDs_Setup_S::getEscalationTime() const
{
    return escalationTime;
}

void AlarmIDs_Setup_S::setEscalationTime(int value)
{
    escalationTime = value;
}
AlarmIDs_Setup_S::AlarmIDs_Setup_S(QObject *parent) :
    QObject(parent)
{
}
