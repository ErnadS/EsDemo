#ifndef CALIBRATION_H
#define CALIBRATION_H

#include "calibration_s.h"

class calibration
{
    calibration_s calibration_coeffitients;

    bool setupReceivedFlag;

    void readSetup();
    void writeSetup();
public:
    calibration();

    void setCalibration(float instalationAngle,
                        float pitch, float roll,
                        float realTemp1,
                        float measuredTemp1,
                        float realTemp2,
                        float measuredTemp2);

    float getInstalationAngleDeg() const;
    float getInstalationAngleRad();
    void setInstalationAngle(float value);

    float getPitchOffsetDeg() const;
    float getPitchOffsetRad() const;
    void setPitch(float value);

    float getRollOffsetDeg() const;
    float getRollOffsetRad() const;
    void setRoll(float value);

    float getRealTemp1() const;
    void setRealTemp1(float value);

    float getMeasuredTemp1() const;
    void setMeasuredTemp1(float value);

    float getRealTemp2() const;
    void setRealTemp2(float value);

    float getMeasuredTemp2() const;
    void setMeasuredTemp2(float value);

    bool getSetupReceivedFlag() const;
    void setSetupReceivedFlag(bool value);
    void getDefaults();
};

#endif
