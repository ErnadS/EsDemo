#ifndef ALARMIDS_SETUP_H
#define ALARMIDS_SETUP_H

#include "alarmids_setup_s.h"
#include "alarm/alarminstance.h"

class AlarmIDs_Setup
{
    AlarmIDs_Setup_S AlarmIDsSetup;

    bool setupReceivedFlag;

    void readSetup();
    void writeSetup();
public:
    AlarmIDs_Setup();

    void setAlarmIDs(int stwHigh, int stwLow, int sogHigh, int sogLow,
                     int systemAlarm, bool useALR, int escalationTime);

    int getStwHighAlarmID() const;
    void setStwHighAlarmID(int value);

    int getStwLowAlarmID() const;
    void setStwLowAlarmID(int value);

    int getSogHighAlarmID() const;
    void setSogHighAlarmID(int value);

    int getSogLowAlarmID() const;
    void setSogLowAlarmID(int value);

    int getAlarmIDbyIndex(const int& index);
    AlarmSource getAlarmSouceByAlarmID(const int &id);

    bool getSetupReceivedFlag() const;
    void setSetupReceivedFlag(bool value);

    int getSystemAlarmID() const;
    void setSystemAlarmID(int value);

    bool getUseALR() const;
    void setUseALR(bool value);

    int getEscalationTime() const;
    void setEscalationTime(int value);

    bool loadFromFile(QString fileSuffix);
    bool saveToFile(QString fileSuffix);
    void getDefaults();
};

#endif // ALARMIDS_SETUP_H
