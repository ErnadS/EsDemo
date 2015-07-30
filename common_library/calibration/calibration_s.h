#ifndef CALIBRATION_S_H
#define CALIBRATION_S_H

#include <QObject>
#include "configuration/serialization_controller.h"

class calibration_s : public QObject
{
    Q_OBJECT

    float instalationAngle;

    float pitch;
    float roll;

    float realTemp1;
    float measuredTemp1;
    float realTemp2;
    float measuredTemp2;

    Q_PROPERTY(float instalationAngle READ getInstalationAngle WRITE setInstalationAngle)

    Q_PROPERTY(float pitch READ getPitch WRITE setPitch)
    Q_PROPERTY(float roll READ getRoll WRITE setRoll)
    Q_PROPERTY(float realTemp1 READ getRealTemp1 WRITE setRealTemp1)
    Q_PROPERTY(float measuredTemp1 READ getMeasuredTemp1 WRITE setMeasuredTemp1)
    Q_PROPERTY(float realTemp2 READ getRealTemp2 WRITE setRealTemp2)
    Q_PROPERTY(float measuredTemp2 READ getMeasuredTemp2 WRITE setMeasuredTemp2)

public:
    explicit calibration_s(QObject *parent = 0);

    float getInstalationAngle() const;
    void setInstalationAngle(float value);

    float getPitch() const;
    void setPitch(float value);

    float getRoll() const;
    void setRoll(float value);

    float getRealTemp1() const;
    void setRealTemp1(float value);

    float getMeasuredTemp1() const;
    void setMeasuredTemp1(float value);

    float getRealTemp2() const;
    void setRealTemp2(float value);

    float getMeasuredTemp2() const;
    void setMeasuredTemp2(float value);
};

#endif
