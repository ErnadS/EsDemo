#include "dl2_setup.h"
#include <QDebug>


bool DL2_Setup::getSetupReceivedFlag() const
{
    return setupReceivedFlag;
}

void DL2_Setup::setSetupReceivedFlag(bool value)
{
    setupReceivedFlag = value;
}

bool DL2_Setup::loadFromFile(QString fileSuffix)
{
    return SerializationController::Deserialize(Dl2Setup, "dl2_setup" + fileSuffix, "/setup_files/saved_configs/");
}

bool DL2_Setup::saveToFile(QString fileSuffix)
{
    return SerializationController::Serialize(Dl2Setup, "dl2_setup" + fileSuffix, "/setup_files/saved_configs/");
}
void DL2_Setup::getDefaults(int level)
{
        Dl2Setup.setDraft(0);
        Dl2Setup.setVesselLength(148);
        Dl2Setup.setSensorDistanceFromBow(4);
        Dl2Setup.setTonnage(1000);
        Dl2Setup.setAveragingTime(10);
        Dl2Setup.setCurrentCorrection(2);
        Dl2Setup.setStwOn(1);
        Dl2Setup.setSogLostBottom(1);
        Dl2Setup.setDockingOptionCode(0);
        Dl2Setup.setOnePercentOption(0);
        Dl2Setup.setSynchBlankingOptionCode(0);
        Dl2Setup.setAutoGpsOnNmeaOptionCode(0);
        Dl2Setup.setShalowWaterPingLenght(2);
        Dl2Setup.setDeepWaterPingLenght(8);
        Dl2Setup.setDepthPingChangeLimit(16.0f);
        Dl2Setup.setUseTwoDecimals(true);

        if(level > 0)
            Dl2Setup.setVesselMaxSpeed(22);

        writeSetup();
}


bool DL2_Setup::getNewSensorFirmware() const
{
    return newSensorFirmware;
}

void DL2_Setup::setNewSensorFirmware(bool value)
{
    newSensorFirmware = value;
}
void DL2_Setup::readSetup()
{
    if (!SerializationController::Deserialize(Dl2Setup, "dl2_setup", "/setup_files/"))
        getDefaults(7);
}

void DL2_Setup::writeSetup()
{
    SerializationController::Serialize(Dl2Setup, "dl2_setup", "/setup_files/");
}

DL2_Setup::DL2_Setup()
{
    readSetup();
    setupReceivedFlag = false;
    newSensorFirmware = false;
}

void DL2_Setup::setDl2(float draft, float vesselMaxSpeed, float vesselLength,
                       float sensorDistanceFromBow, float tonnage, int avgTime,
                       int currentCorrection, bool stwOn,
                       bool sogLostBottom, int dockingOptionCode,
                       int onePercentOption, int synchBlankingOptionCode,
                       int autoGpsOnNmeaOptionCode, int shalowWaterPingLenght,
                       int deepWaterPingLenght, float depthPingChangeLimit, bool useTwoDecimals)
{
    Dl2Setup.setDraft(draft);
    Dl2Setup.setVesselMaxSpeed(vesselMaxSpeed);
    Dl2Setup.setVesselLength(vesselLength);
    Dl2Setup.setSensorDistanceFromBow(sensorDistanceFromBow);
    Dl2Setup.setTonnage(tonnage);
    Dl2Setup.setAveragingTime(avgTime);
    Dl2Setup.setCurrentCorrection(currentCorrection);
    Dl2Setup.setStwOn(stwOn);
    Dl2Setup.setSogLostBottom(sogLostBottom);
    Dl2Setup.setDockingOptionCode(dockingOptionCode);
    Dl2Setup.setOnePercentOption(onePercentOption);
    Dl2Setup.setSynchBlankingOptionCode(synchBlankingOptionCode);
    Dl2Setup.setAutoGpsOnNmeaOptionCode(autoGpsOnNmeaOptionCode);
    Dl2Setup.setShalowWaterPingLenght(shalowWaterPingLenght);
    Dl2Setup.setDeepWaterPingLenght(deepWaterPingLenght);
    Dl2Setup.setDepthPingChangeLimit(depthPingChangeLimit);
    Dl2Setup.setUseTwoDecimals(useTwoDecimals);

    setupReceivedFlag = true;

    writeSetup();
}

float DL2_Setup::getDraft() const
{
    return Dl2Setup.getDraft();
}

void DL2_Setup::setDraft(float value)
{
    Dl2Setup.setDraft( value);
    writeSetup();
}

float DL2_Setup::getVesselMaxSpeed() const
{
    return Dl2Setup.getVesselMaxSpeed();
}

void DL2_Setup::setVesselMaxSpeed(float value)
{
    Dl2Setup.setVesselMaxSpeed( value);
    writeSetup();
}

float DL2_Setup::getVesselLength() const
{
    return Dl2Setup.getVesselLength();
}

void DL2_Setup::setVesselLength(float value)
{
    Dl2Setup.setVesselLength( value);
    writeSetup();
}

float DL2_Setup::getSensorDistanceFromBow() const
{
    return Dl2Setup.getSensorDistanceFromBow();
}

void DL2_Setup::setSensorDistanceFromBow(float value)
{
    Dl2Setup.setSensorDistanceFromBow( value);
    writeSetup();
}

float DL2_Setup::getTonnage() const
{
    return Dl2Setup.getTonnage();
}

void DL2_Setup::setTonnage(float value)
{
    Dl2Setup.setTonnage(value);
    writeSetup();
}

int DL2_Setup::getAveragingTime() const
{
    return Dl2Setup.getAveragingTime();
}

void DL2_Setup::setAveragingTime(int value)
{
    Dl2Setup.setAveragingTime(value);
    writeSetup();
}

int DL2_Setup::getCurrentCorrection() const
{
    return Dl2Setup.getCurrentCorrection();
}

void DL2_Setup::setCurrentCorrection(int value)
{
    Dl2Setup.setCurrentCorrection( value);
    writeSetup();
}

bool DL2_Setup::getStwOn() const
{
    return Dl2Setup.getStwOn();
}

void DL2_Setup::setStwOn(bool value)
{
    Dl2Setup.setStwOn( value);
    writeSetup();
}

bool DL2_Setup::getSogLostBottom() const
{
    return Dl2Setup.getSogLostBottom();
}

void DL2_Setup::setSogLostBottom(bool value)
{
    Dl2Setup.setSogLostBottom( value);
    writeSetup();
}

int DL2_Setup::getDockingOptionCode() const
{
    return Dl2Setup.getDockingOptionCode();
}

void DL2_Setup::setDockingOptionCode(int value)
{
    Dl2Setup.setDockingOptionCode( value);
    writeSetup();
}

int DL2_Setup::getOnePercentOption() const
{
    return Dl2Setup.getOnePercentOption();
}

int DL2_Setup::numberOfDecimals() const
{
    return 1 + int(bool(Dl2Setup.getOnePercentOption()) && Dl2Setup.getUseTwoDecimals());
}

void DL2_Setup::setOnePercentOption(int value)
{
    Dl2Setup.setOnePercentOption( value);
    writeSetup();
}

int DL2_Setup::getSynchBlankingOptionCode() const
{
    return Dl2Setup.getSynchBlankingOptionCode();
}

void DL2_Setup::setSynchBlankingOptionCode(int value)
{
    Dl2Setup.setSynchBlankingOptionCode( value);
    writeSetup();
}

int DL2_Setup::getAutoGpsOnNmeaOptionCode() const
{
    return Dl2Setup.getAutoGpsOnNmeaOptionCode();
}

void DL2_Setup::setAutoGpsOnNmeaOptionCode(int value)
{
    Dl2Setup.setAutoGpsOnNmeaOptionCode( value);
    writeSetup();
}

int DL2_Setup::getShalowWaterPingLenght() const
{
    return Dl2Setup.getShalowWaterPingLenght();
}

void DL2_Setup::setShalowWaterPingLenght(int value)
{
    Dl2Setup.setShalowWaterPingLenght( value);
    writeSetup();
}

int DL2_Setup::getShalowWaterPingLenghtIndex() const
{
    int pingLength = getShalowWaterPingLenght();
    switch (pingLength) {
    case 1:
        return 0;
    case 2:
        return 1;
    case 4:
        return 2;
    case 8:
        return 3;
    default:
        return 3; // never?
    }
}


int DL2_Setup::getDeepWaterPingLenght() const
{
    return Dl2Setup.getDeepWaterPingLenght();
}

void DL2_Setup::setDeepWaterPingLenght(int value)
{
    Dl2Setup.setDeepWaterPingLenght( value);
    writeSetup();
}

int DL2_Setup::getDepthWaterPingLenghtIndex() const
{
    int pingLength = getDeepWaterPingLenght();
    switch (pingLength) {
    case 1:
        return 0;
    case 2:
        return 1;
    case 4:
        return 2;
    case 8:
        return 3;
    default:
        return 3; // never?
    }
}

float DL2_Setup::getDepthPingChangeLimit() const
{
    return Dl2Setup.getDepthPingChangeLimit();
}

void DL2_Setup::setDepthPingChangeLimit(float value)
{
    Dl2Setup.setDepthPingChangeLimit( value);
    writeSetup();
}

bool DL2_Setup::getUseTwoDecimals() const
{
    return Dl2Setup.getUseTwoDecimals();
}

void DL2_Setup::setUseTwoDecimals(bool value)
{
    Dl2Setup.setUseTwoDecimals( value);
    writeSetup();
}
