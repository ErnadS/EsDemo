#include "alarmids_setup.h"


bool AlarmIDs_Setup::getSetupReceivedFlag() const
{
    return setupReceivedFlag;
}

void AlarmIDs_Setup::setSetupReceivedFlag(bool value)
{
    setupReceivedFlag = value;
}

int AlarmIDs_Setup::getSystemAlarmID() const
{
    return AlarmIDsSetup.getSystemAlarmID();
}

void AlarmIDs_Setup::setSystemAlarmID(int value)
{
    AlarmIDsSetup.setSystemAlarmID(value);
    writeSetup();
}

bool AlarmIDs_Setup::getUseALR() const
{
    return AlarmIDsSetup.getUseALR();
}

void AlarmIDs_Setup::setUseALR(bool value)
{
    AlarmIDsSetup.setUseALR(value);
    writeSetup();
}

int AlarmIDs_Setup::getEscalationTime() const
{
    return AlarmIDsSetup.getEscalationTime();
}

void AlarmIDs_Setup::setEscalationTime(int value)
{
    AlarmIDsSetup.setEscalationTime(value);
    writeSetup();
}

bool AlarmIDs_Setup::loadFromFile(QString fileSuffix)
{
    return SerializationController::Deserialize(AlarmIDsSetup, "alarm_ids_setup" + fileSuffix, "/setup_files/saved_configs/");
}

bool AlarmIDs_Setup::saveToFile(QString fileSuffix)
{
    return SerializationController::Serialize(AlarmIDsSetup, "alarm_ids_setup" + fileSuffix, "/setup_files/saved_configs/");
}

void AlarmIDs_Setup::getDefaults()
{
    {
        AlarmIDsSetup.setStwHighAlarmID(10234);
        AlarmIDsSetup.setStwLowAlarmID(10235);
        AlarmIDsSetup.setSogHighAlarmID(10236);
        AlarmIDsSetup.setSogLowAlarmID(10237);
        AlarmIDsSetup.setSystemAlarmID(10238);
        AlarmIDsSetup.setUseALR(false);
        AlarmIDsSetup.setEscalationTime(5);

        writeSetup();
    }
}

void AlarmIDs_Setup::readSetup()
{
    if (!SerializationController::Deserialize(AlarmIDsSetup, "alarm_ids_setup", "/setup_files/"))
        getDefaults();
}

void AlarmIDs_Setup::writeSetup()
{
    SerializationController::Serialize(AlarmIDsSetup, "alarm_ids_setup", "/setup_files/");
}

AlarmIDs_Setup::AlarmIDs_Setup()
{
    readSetup();
    setupReceivedFlag = false;
}

void AlarmIDs_Setup::setAlarmIDs(int stwHigh, int stwLow, int sogHigh, int sogLow, int systemAlarm,
                                 bool useALR, int escalationTime)
{
    AlarmIDsSetup.setStwHighAlarmID(stwHigh);
    AlarmIDsSetup.setStwLowAlarmID(stwLow);
    AlarmIDsSetup.setSogHighAlarmID(sogHigh);
    AlarmIDsSetup.setSogLowAlarmID(sogLow);
    AlarmIDsSetup.setSystemAlarmID(systemAlarm);
    AlarmIDsSetup.setUseALR(useALR);
    AlarmIDsSetup.setEscalationTime(escalationTime);

    setupReceivedFlag = true;

    writeSetup();
}

int AlarmIDs_Setup::getStwHighAlarmID() const
{
    return AlarmIDsSetup.getStwHighAlarmID();
}

void AlarmIDs_Setup::setStwHighAlarmID(int value)
{
    AlarmIDsSetup.setStwHighAlarmID(value);
    writeSetup();
}

int AlarmIDs_Setup::getStwLowAlarmID() const
{
    return AlarmIDsSetup.getStwLowAlarmID();
}

void AlarmIDs_Setup::setStwLowAlarmID(int value)
{
    AlarmIDsSetup.setStwLowAlarmID(value);
    writeSetup();
}

int AlarmIDs_Setup::getSogHighAlarmID() const
{
    return AlarmIDsSetup.getSogHighAlarmID();
}

void AlarmIDs_Setup::setSogHighAlarmID(int value)
{
    AlarmIDsSetup.setSogHighAlarmID(value);
    writeSetup();
}

int AlarmIDs_Setup::getSogLowAlarmID() const
{
    return AlarmIDsSetup.getSogLowAlarmID();
}

void AlarmIDs_Setup::setSogLowAlarmID(int value)
{
    AlarmIDsSetup.setSogLowAlarmID(value);
    writeSetup();
}

int AlarmIDs_Setup::getAlarmIDbyIndex(const int &index)
{
    switch(index)
    {
    case 0:
        return AlarmIDsSetup.getStwLowAlarmID();
    case 1:
        return AlarmIDsSetup.getStwHighAlarmID();
    case 2:
        return AlarmIDsSetup.getSogLowAlarmID();
    case 3:
        return AlarmIDsSetup.getSogHighAlarmID();
    case 4:
        return AlarmIDsSetup.getSystemAlarmID();

    default:
        return 0;

    }
}

AlarmSource AlarmIDs_Setup::getAlarmSouceByAlarmID(const int &id)
{
    if (id == AlarmIDsSetup.getStwLowAlarmID())
        return ALARM_LOW_SPEED_WATER;
    else if (id == AlarmIDsSetup.getStwHighAlarmID())
        return ALARM_HIGH_SPEED_WATER;
    else if (id == AlarmIDsSetup.getSogLowAlarmID())
        return ALARM_LOW_SPEED_GROUND;
    else if (id == AlarmIDsSetup.getSogHighAlarmID())
        return ALARM_HIGH_SPEED_GROUND;
    else if (id == AlarmIDsSetup.getSystemAlarmID())
        return ALARM_SYSTEM;
    // TODO: System Alarm

    return UNKNOWN_SOURCE; // not found
}

