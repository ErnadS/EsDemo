#include "calibration_s.h"


float calibration_s::getInstalationAngle() const
{
    return instalationAngle;
}

void calibration_s::setInstalationAngle(float value)
{
    instalationAngle = value;
}

float calibration_s::getPitch() const
{
    return pitch;
}

void calibration_s::setPitch(float value)
{
    pitch = value;
}

float calibration_s::getRoll() const
{
    return roll;
}

void calibration_s::setRoll(float value)
{
    roll = value;
}

float calibration_s::getRealTemp1() const
{
    return realTemp1;
}

void calibration_s::setRealTemp1(float value)
{
    realTemp1 = value;
}

float calibration_s::getMeasuredTemp1() const
{
    return measuredTemp1;
}

void calibration_s::setMeasuredTemp1(float value)
{
    measuredTemp1 = value;
}

float calibration_s::getRealTemp2() const
{
    return realTemp2;
}

void calibration_s::setRealTemp2(float value)
{
    realTemp2 = value;
}

float calibration_s::getMeasuredTemp2() const
{
    return measuredTemp2;
}

void calibration_s::setMeasuredTemp2(float value)
{
    measuredTemp2 = value;
}
calibration_s::calibration_s(QObject *parent) :
    QObject(parent)
{
}
