#ifndef ALARMLIMITS_SETUP_S_H
#define ALARMLIMITS_SETUP_S_H

#include <QObject>
#include "configuration/serialization_controller.h"

class AlarmLimits_Setup_S : public QObject
{
    Q_OBJECT

    float stwHighLimit;
    float stwLowLimit;
    float sogHighLimit;
    float sogLowLimit;

    float speedLevelHigh1;
    float speedLevelLow1;
    float speedLevelHigh2;
    float speedLevelLow2;

    Q_PROPERTY(float stwHighLimit    READ getStwHighLimit    WRITE setStwHighLimit)
    Q_PROPERTY(float stwLowLimit     READ getStwLowLimit     WRITE setStwLowLimit)
    Q_PROPERTY(float sogHighLimit    READ getSogHighLimit    WRITE setSogHighLimit)
    Q_PROPERTY(float sogLowLimit     READ getSogLowLimit     WRITE setSogLowLimit)
    Q_PROPERTY(float speedLevelHigh1 READ getSpeedLevelHigh1 WRITE setSpeedLevelHigh1)
    Q_PROPERTY(float speedLevelLow1  READ getSpeedLevelLow1  WRITE setSpeedLevelLow1)
    Q_PROPERTY(float speedLevelHigh2 READ getSpeedLevelHigh2 WRITE setSpeedLevelHigh2)
    Q_PROPERTY(float speedLevelLow2  READ getSpeedLevelLow2  WRITE setSpeedLevelLow2)
public:
    explicit AlarmLimits_Setup_S(QObject *parent = 0);

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

signals:

public slots:

};

#endif // ALARMLIMITS_SETUP_S_H
