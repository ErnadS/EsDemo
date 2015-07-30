#include "calibration.h"
#include <qmath.h>


bool calibration::getSetupReceivedFlag() const
{
    return setupReceivedFlag;
}

void calibration::setSetupReceivedFlag(bool value)
{
    setupReceivedFlag = value;
}
void calibration::getDefaults()
{
    calibration_coeffitients.setInstalationAngle(0);
    calibration_coeffitients.setPitch(0);
    calibration_coeffitients.setRoll(0);
    calibration_coeffitients.setRealTemp1(5);
    calibration_coeffitients.setMeasuredTemp1(5);
    calibration_coeffitients.setRealTemp2(20);
    calibration_coeffitients.setMeasuredTemp2(20);

    writeSetup();
}

void calibration::readSetup()
{
    if (!SerializationController::Deserialize(calibration_coeffitients, "calibration_coeff", "setup_files/"))
    {
        getDefaults();
    }
}

void calibration::writeSetup()
{
    SerializationController::Serialize(calibration_coeffitients, "calibration_coeff", "setup_files/");
}

calibration::calibration()
{
    readSetup();
    setupReceivedFlag = false;
}

void calibration::setCalibration(
        float instalationAngle, float pitch,
        float roll, float realTemp1,
        float measuredTemp1, float realTemp2,
        float measuredTemp2)
{
    calibration_coeffitients.setInstalationAngle(instalationAngle);
    calibration_coeffitients.setPitch(pitch);
    calibration_coeffitients.setRoll(roll);
    calibration_coeffitients.setRealTemp1(realTemp1);
    calibration_coeffitients.setMeasuredTemp1(measuredTemp1);
    calibration_coeffitients.setRealTemp2(realTemp2);
    calibration_coeffitients.setMeasuredTemp2(measuredTemp2);

    setupReceivedFlag = true;

    writeSetup();
}

float calibration::getInstalationAngleDeg() const
{
    return calibration_coeffitients.getInstalationAngle();
}

float calibration::getInstalationAngleRad()
{
    return calibration_coeffitients.getInstalationAngle()*M_PI/180;
}

void calibration::setInstalationAngle(float value)
{
    calibration_coeffitients.setInstalationAngle(value);
    writeSetup();
}

float calibration::getPitchOffsetDeg() const
{
    return calibration_coeffitients.getPitch();
}

float calibration::getPitchOffsetRad() const
{
    return calibration_coeffitients.getPitch()*M_PI/180;
}

void calibration::setPitch(float value)
{
    calibration_coeffitients.setPitch(value);
    writeSetup();
}

float calibration::getRollOffsetDeg() const
{
    return calibration_coeffitients.getRoll();
}

float calibration::getRollOffsetRad() const
{
    return calibration_coeffitients.getRoll()*M_PI/180;
}

void calibration::setRoll(float value)
{
    calibration_coeffitients.setRoll(value);
    writeSetup();
}

float calibration::getRealTemp1() const
{
    return calibration_coeffitients.getRealTemp1();
}

void calibration::setRealTemp1(float value)
{
    calibration_coeffitients.setRealTemp1(value);
    writeSetup();
}

float calibration::getMeasuredTemp1() const
{
    return calibration_coeffitients.getMeasuredTemp1();
}

void calibration::setMeasuredTemp1(float value)
{
    calibration_coeffitients.setMeasuredTemp1(value);
    writeSetup();
}

float calibration::getRealTemp2() const
{
    return calibration_coeffitients.getRealTemp2();
}

void calibration::setRealTemp2(float value)
{
    calibration_coeffitients.setRealTemp2(value);
    writeSetup();
}

float calibration::getMeasuredTemp2() const
{
    return calibration_coeffitients.getMeasuredTemp2();
}

void calibration::setMeasuredTemp2(float value)
{
    calibration_coeffitients.setMeasuredTemp2(value);
    writeSetup();
}
