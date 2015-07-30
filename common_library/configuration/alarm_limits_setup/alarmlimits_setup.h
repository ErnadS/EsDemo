#ifndef ALARMLIMITS_SETUP_H
#define ALARMLIMITS_SETUP_H

#include "alarmlimits_setup_s.h"

class AlarmLimits_Setup
{
    AlarmLimits_Setup_S AlarmLimitsSetup;

    bool setupReceivedFlag;

    void readSetup();
    void writeSetup();
public:
    AlarmLimits_Setup();

    void setAlarmLimits(float stwHigh, float stwLow, float sogHigh, float sogLow, float speedLevhigh1, float speedLevLow1,
                     float speedLevhigh2, float speedLevLow2);

    float getStwHighLimit() const;
    void setStwHighLimit(float value);

    float getStwLowLimit() const;
    void setStwLowLimit(float value);

    float getSogHighLimit() const;
    void setSogHighLimit(float value);

    float getSogLowLimit() const;
    void setSogLowLimit(float value);

    float getSpeedLevelHigh1() const;
    void setSpeedLevelHigh1(float value);

    float getSpeedLevelLow1() const;
    void setSpeedLevelLow1(float value);

    float getSpeedLevelHigh2() const;
    void setSpeedLevelHigh2(float value);

    float getSpeedLevelLow2() const;
    void setSpeedLevelLow2(float value);

    bool getSetupReceivedFlag() const;
    void setSetupReceivedFlag(bool value);

    bool loadFromFile(QString fileSuffix);
    bool saveToFile(QString fileSuffix);
    void getDefaults();
};

#endif // ALARMLIMITS_SETUP_H
