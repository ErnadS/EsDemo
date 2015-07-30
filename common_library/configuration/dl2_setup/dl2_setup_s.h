#ifndef DL2_SETUP_S_H
#define DL2_SETUP_S_H

#include <QObject>
#include "configuration/serialization_controller.h"

class DL2_Setup_S : public QObject
{
    Q_OBJECT


    float   draft;
    float   vesselMaxSpeed;
    float   vesselLength;
    float   sensorDistanceFromBow;
    float   tonnage;
    int     averagingTime;
    int     currentCorrection;
    bool    stwOn;
    bool    sogLostBottom;
    int     dockingOptionCode;
    int     onePercentOption;
    int     synchBlankingOptionCode;
    int     autoGpsOnNmeaOptionCode;

    int     shalowWaterPingLenght;
    int     deepWaterPingLenght;
    float   depthPingChangeLimit;

    bool    useTwoDecimals;

    Q_PROPERTY(float draft                 READ getDraft                   WRITE setDraft)
    Q_PROPERTY(float vesselMaxSpeed        READ getVesselMaxSpeed          WRITE setVesselMaxSpeed)
    Q_PROPERTY(float vesselLength          READ getVesselLength            WRITE setVesselLength)
    Q_PROPERTY(float sensorDistanceFromBow READ getSensorDistanceFromBow   WRITE setSensorDistanceFromBow)
    Q_PROPERTY(float tonnage               READ getTonnage                 WRITE setTonnage)
    Q_PROPERTY(int averagingTime           READ getAveragingTime           WRITE setAveragingTime)
    Q_PROPERTY(int currentCorrection       READ getCurrentCorrection       WRITE setCurrentCorrection)
    Q_PROPERTY(bool stwOn                  READ getStwOn                   WRITE setStwOn)
    Q_PROPERTY(bool sogLostBottom          READ getSogLostBottom           WRITE setSogLostBottom)
    Q_PROPERTY(int dockingOptionCode       READ getDockingOptionCode       WRITE setDockingOptionCode)
    Q_PROPERTY(int onePercentOption        READ getOnePercentOption        WRITE setOnePercentOption)
    Q_PROPERTY(int synchBlankingOptionCode READ getSynchBlankingOptionCode WRITE setSynchBlankingOptionCode)
    Q_PROPERTY(int autoGpsOnNmeaOptionCode READ getAutoGpsOnNmeaOptionCode WRITE setAutoGpsOnNmeaOptionCode)

    Q_PROPERTY(int shalowWaterPingLenght   READ getShalowWaterPingLenght   WRITE setShalowWaterPingLenght)
    Q_PROPERTY(int deepWaterPingLenght     READ getDeepWaterPingLenght     WRITE setDeepWaterPingLenght)
    Q_PROPERTY(float depthPingChangeLimit  READ getDepthPingChangeLimit    WRITE setDepthPingChangeLimit)

    Q_PROPERTY(bool useTwoDecimals         READ getUseTwoDecimals          WRITE setUseTwoDecimals)

public:
    explicit DL2_Setup_S(QObject *parent = 0);

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

    int getShalowWaterPingLenght() const;
    void setShalowWaterPingLenght(int value);

    int getDeepWaterPingLenght() const;
    void setDeepWaterPingLenght(int value);

    float getDepthPingChangeLimit() const;
    void setDepthPingChangeLimit(float value);

    bool getUseTwoDecimals() const;
    void setUseTwoDecimals(bool value);

signals:

public slots:

};

#endif // DL2_SETUP_S_H
