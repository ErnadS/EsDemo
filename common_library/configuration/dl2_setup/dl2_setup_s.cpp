#include "dl2_setup_s.h"


float DL2_Setup_S::getDraft() const
{
    return draft;
}

void DL2_Setup_S::setDraft(float value)
{
    draft = value;
}

float DL2_Setup_S::getVesselMaxSpeed() const
{
    return vesselMaxSpeed;
}

void DL2_Setup_S::setVesselMaxSpeed(float value)
{
    vesselMaxSpeed = value;
}

float DL2_Setup_S::getVesselLength() const
{
    return vesselLength;
}

void DL2_Setup_S::setVesselLength(float value)
{
    vesselLength = value;
}

float DL2_Setup_S::getSensorDistanceFromBow() const
{
    return sensorDistanceFromBow;
}

void DL2_Setup_S::setSensorDistanceFromBow(float value)
{
    sensorDistanceFromBow = value;
}

float DL2_Setup_S::getTonnage() const
{
    return tonnage;
}

void DL2_Setup_S::setTonnage(float value)
{
    tonnage = value;
}

int DL2_Setup_S::getAveragingTime() const
{
    return averagingTime;
}

void DL2_Setup_S::setAveragingTime(int value)
{
    averagingTime = value;
}

int DL2_Setup_S::getCurrentCorrection() const
{
    return currentCorrection;
}

void DL2_Setup_S::setCurrentCorrection(int value)
{
    currentCorrection = value;
}

bool DL2_Setup_S::getStwOn() const
{
    return stwOn;
}

void DL2_Setup_S::setStwOn(bool value)
{
    stwOn = value;
}

bool DL2_Setup_S::getSogLostBottom() const
{
    return sogLostBottom;
}

void DL2_Setup_S::setSogLostBottom(bool value)
{
    sogLostBottom = value;
}

int DL2_Setup_S::getDockingOptionCode() const
{
    return dockingOptionCode;
}

void DL2_Setup_S::setDockingOptionCode(int value)
{
    dockingOptionCode = value;
}

int DL2_Setup_S::getOnePercentOption() const
{
    return onePercentOption;
}

void DL2_Setup_S::setOnePercentOption(int value)
{
    onePercentOption = value;
}

int DL2_Setup_S::getSynchBlankingOptionCode() const
{
    return synchBlankingOptionCode;
}

void DL2_Setup_S::setSynchBlankingOptionCode(int value)
{
    synchBlankingOptionCode = value;
}

int DL2_Setup_S::getAutoGpsOnNmeaOptionCode() const
{
    return autoGpsOnNmeaOptionCode;
}

void DL2_Setup_S::setAutoGpsOnNmeaOptionCode(int value)
{
    autoGpsOnNmeaOptionCode = value;
}


int DL2_Setup_S::getShalowWaterPingLenght() const
{
    return shalowWaterPingLenght;
}

void DL2_Setup_S::setShalowWaterPingLenght(int value)
{
    shalowWaterPingLenght = value;
}

int DL2_Setup_S::getDeepWaterPingLenght() const
{
    return deepWaterPingLenght;
}

void DL2_Setup_S::setDeepWaterPingLenght(int value)
{
    deepWaterPingLenght = value;
}

float DL2_Setup_S::getDepthPingChangeLimit() const
{
    return depthPingChangeLimit;
}

void DL2_Setup_S::setDepthPingChangeLimit(float value)
{
    depthPingChangeLimit = value;
}

bool DL2_Setup_S::getUseTwoDecimals() const
{
    return useTwoDecimals;
}

void DL2_Setup_S::setUseTwoDecimals(bool value)
{
    useTwoDecimals = value;
}
DL2_Setup_S::DL2_Setup_S(QObject *parent) :
    QObject(parent)
{
}
