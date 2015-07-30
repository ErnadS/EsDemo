#include "alarmlimits_setup_s.h"


float AlarmLimits_Setup_S::getStwHighLimit() const
{
    return stwHighLimit;
}

void AlarmLimits_Setup_S::setStwHighLimit(float value)
{
    stwHighLimit = value;
}

float AlarmLimits_Setup_S::getStwLowLimit() const
{
    return stwLowLimit;
}

void AlarmLimits_Setup_S::setStwLowLimit(float value)
{
    stwLowLimit = value;
}

float AlarmLimits_Setup_S::getSogHighLimit() const
{
    return sogHighLimit;
}

void AlarmLimits_Setup_S::setSogHighLimit(float value)
{
    sogHighLimit = value;
}

float AlarmLimits_Setup_S::getSogLowLimit() const
{
    return sogLowLimit;
}

void AlarmLimits_Setup_S::setSogLowLimit(float value)
{
    sogLowLimit = value;
}

float AlarmLimits_Setup_S::getSpeedLevelHigh1() const
{
    return speedLevelHigh1;
}

void AlarmLimits_Setup_S::setSpeedLevelHigh1(float value)
{
    speedLevelHigh1 = value;
}

float AlarmLimits_Setup_S::getSpeedLevelLow1() const
{
    return speedLevelLow1;
}

void AlarmLimits_Setup_S::setSpeedLevelLow1(float value)
{
    speedLevelLow1 = value;
}

float AlarmLimits_Setup_S::getSpeedLevelHigh2() const
{
    return speedLevelHigh2;
}

void AlarmLimits_Setup_S::setSpeedLevelHigh2(float value)
{
    speedLevelHigh2 = value;
}

float AlarmLimits_Setup_S::getSpeedLevelLow2() const
{
    return speedLevelLow2;
}

void AlarmLimits_Setup_S::setSpeedLevelLow2(float value)
{
    speedLevelLow2 = value;
}
AlarmLimits_Setup_S::AlarmLimits_Setup_S(QObject *parent) :
    QObject(parent)
{
}
