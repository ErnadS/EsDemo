#include "alarmlimits_setup.h"


bool AlarmLimits_Setup::getSetupReceivedFlag() const
{
    return setupReceivedFlag;
}

void AlarmLimits_Setup::setSetupReceivedFlag(bool value)
{
    setupReceivedFlag = value;
}

bool AlarmLimits_Setup::loadFromFile(QString fileSuffix)
{
    return SerializationController::Deserialize(AlarmLimitsSetup, "alarm_limits_setup" + fileSuffix, "/setup_files/saved_configs/");
}

bool AlarmLimits_Setup::saveToFile(QString fileSuffix)
{
    return SerializationController::Serialize(AlarmLimitsSetup, "alarm_limits_setup" + fileSuffix, "/setup_files/saved_configs/");
}
void AlarmLimits_Setup::getDefaults()
{
    {
        AlarmLimitsSetup.setStwHighLimit(24);
        AlarmLimitsSetup.setStwLowLimit(0.5);
        AlarmLimitsSetup.setSogHighLimit(24);
        AlarmLimitsSetup.setSogLowLimit(0.5);
        AlarmLimitsSetup.setSpeedLevelHigh1(5);
        AlarmLimitsSetup.setSpeedLevelLow1(0);
        AlarmLimitsSetup.setSpeedLevelHigh2(10);
        AlarmLimitsSetup.setSpeedLevelLow2(0);

        writeSetup();
    }
}

void AlarmLimits_Setup::readSetup()
{
    if (!SerializationController::Deserialize(AlarmLimitsSetup, "alarm_limits_setup", "/setup_files/"))
        getDefaults();
}

void AlarmLimits_Setup::writeSetup()
{
    SerializationController::Serialize(AlarmLimitsSetup, "alarm_limits_setup", "/setup_files/");
}

AlarmLimits_Setup::AlarmLimits_Setup()
{
    readSetup();
    setupReceivedFlag = false;
}

void AlarmLimits_Setup::setAlarmLimits(float stwHigh, float stwLow, float sogHigh, float sogLow, float speedLevhigh1, float speedLevLow1,
                                       float speedLevhigh2, float speedLevLow2)
{
    AlarmLimitsSetup.setStwHighLimit(stwHigh);
    AlarmLimitsSetup.setStwLowLimit(stwLow);
    AlarmLimitsSetup.setSogHighLimit(sogHigh);
    AlarmLimitsSetup.setSogLowLimit(sogLow);
    AlarmLimitsSetup.setSpeedLevelHigh1(speedLevhigh1);
    AlarmLimitsSetup.setSpeedLevelLow1(speedLevLow1);
    AlarmLimitsSetup.setSpeedLevelHigh2(speedLevhigh2);
    AlarmLimitsSetup.setSpeedLevelLow2(speedLevLow2);

    setupReceivedFlag = true;

    writeSetup();
}

float AlarmLimits_Setup::getStwHighLimit() const
{
    return AlarmLimitsSetup.getStwHighLimit();
}

void AlarmLimits_Setup::setStwHighLimit(float value)
{
    AlarmLimitsSetup.setStwHighLimit(value);
    writeSetup();
}

float AlarmLimits_Setup::getStwLowLimit() const
{
    return AlarmLimitsSetup.getStwLowLimit();
}

void AlarmLimits_Setup::setStwLowLimit(float value)
{
    AlarmLimitsSetup.setStwLowLimit(value);
    writeSetup();
}

float AlarmLimits_Setup::getSogHighLimit() const
{
    return AlarmLimitsSetup.getSogHighLimit();
}

void AlarmLimits_Setup::setSogHighLimit(float value)
{
    AlarmLimitsSetup.setSogHighLimit(value);
    writeSetup();
}

float AlarmLimits_Setup::getSogLowLimit() const
{
    return AlarmLimitsSetup.getSogLowLimit();
}

void AlarmLimits_Setup::setSogLowLimit(float value)
{
    AlarmLimitsSetup.setSogLowLimit(value);
    writeSetup();
}

float AlarmLimits_Setup::getSpeedLevelHigh1() const
{
    return AlarmLimitsSetup.getSpeedLevelHigh1();
}

void AlarmLimits_Setup::setSpeedLevelHigh1(float value)
{
    AlarmLimitsSetup.setSpeedLevelHigh1(value);
    writeSetup();
}

float AlarmLimits_Setup::getSpeedLevelLow1() const
{
    return AlarmLimitsSetup.getSpeedLevelLow1();
}

void AlarmLimits_Setup::setSpeedLevelLow1(float value)
{
    AlarmLimitsSetup.setSpeedLevelLow1(value);
    writeSetup();
}

float AlarmLimits_Setup::getSpeedLevelHigh2() const
{
    return AlarmLimitsSetup.getSpeedLevelHigh2();
}

void AlarmLimits_Setup::setSpeedLevelHigh2(float value)
{
    AlarmLimitsSetup.setSpeedLevelHigh2(value);
    writeSetup();
}

float AlarmLimits_Setup::getSpeedLevelLow2() const
{
    return AlarmLimitsSetup.getSpeedLevelLow2();
}

void AlarmLimits_Setup::setSpeedLevelLow2(float value)
{
    AlarmLimitsSetup.setSpeedLevelLow2(value);
    writeSetup();
}

