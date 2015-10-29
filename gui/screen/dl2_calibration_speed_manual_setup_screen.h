#ifndef DL2_CALIBRATION_SPEED_MANUAL_SETUP_SCREEN_H
#define DL2_CALIBRATION_SPEED_MANUAL_SETUP_SCREEN_H

#include "dl2_calibration_speed_setup_screen.h"

class Dl2CalibrationSpeedManualSetupScreen : public Dl2CalibrationSpeedSetupScreen
{
    Q_OBJECT

public:
    explicit Dl2CalibrationSpeedManualSetupScreen(QWidget* parent);
};

#endif
