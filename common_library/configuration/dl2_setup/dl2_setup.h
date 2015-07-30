#ifndef DL2_SETUP_H
#define DL2_SETUP_H

#include "dl2_setup_s.h"

enum CurrentCalculationEnum {
    USE_SOG     = 0,
    USE_GPS     = 1,
    AUTO_CALC   = 2
};

class DL2_Setup
{
    DL2_Setup_S Dl2Setup;

    bool setupReceivedFlag;

    bool newSensorFirmware;

    void readSetup();
    void writeSetup();
public:
    DL2_Setup();

    void setDl2(float draft, float vesselMaxSpeed, float vesselLength, float sensorDistanceFromBow, float tonnage, int avgTime, int currentCorrection,
                     bool stwOn, bool sogLostBottom, int dockingOptionCode, int onePercentOption, int synchBlankingOptionCode,
                     int autoGpsOnNmeaOptionCode, int shalowWaterPingLenght, int deepWaterPingLenght, float depthPingChangeLimit, bool useTwoDecimals);

    float getDraft() const;
    void setDraft(float value);

    float getVesselMaxSpeed() const;
    void setVesselMaxSpeed(float value);

    float getVesselLength() const;
    void setVesselLength(float value);

    float getSensorDistanceFromBow() const;
    void setSensorDistanceFromBow(float value);

    float getTonnage() const;
    void setTonnage(float value);

    int getAveragingTime() const;
    void setAveragingTime(int value);

    int getCurrentCorrection() const;
    void setCurrentCorrection(int value);

    bool getStwOn() const;
    void setStwOn(bool value);

    bool getSogLostBottom() const;
    void setSogLostBottom(bool value);

    int getDockingOptionCode() const;
    void setDockingOptionCode(int value);

    int getOnePercentOption() const;
    void setOnePercentOption(int value);

    int getSynchBlankingOptionCode() const;
    void setSynchBlankingOptionCode(int value);

    int getAutoGpsOnNmeaOptionCode() const;
    void setAutoGpsOnNmeaOptionCode(int value);

    bool getSetupReceivedFlag() const;
    void setSetupReceivedFlag(bool value);

    int getShalowWaterPingLenght() const;
    void setShalowWaterPingLenght(int value);
    int getShalowWaterPingLenghtIndex() const;

    int getDeepWaterPingLenght() const;
    void setDeepWaterPingLenght(int value);
    int getDepthWaterPingLenghtIndex() const;

    float getDepthPingChangeLimit() const;
    void setDepthPingChangeLimit(float value);


    bool getUseTwoDecimals() const;
    void setUseTwoDecimals(bool value);


    int numberOfDecimals() const;

    bool loadFromFile(QString fileSuffix);
    bool saveToFile(QString fileSuffix);
    void getDefaults(int level = 0);
    bool getNewSensorFirmware() const;
    void setNewSensorFirmware(bool value);
};

#endif // DL2_SETUP_H
