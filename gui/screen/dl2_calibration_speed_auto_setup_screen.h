#ifndef DL2_CALIBRATION_SPEED_AUTO_SETUP_SCREEN_H
#define DL2_CALIBRATION_SPEED_AUTO_SETUP_SCREEN_H

#include "dl2_calibration_speed_setup_screen.h"

class Dl2CalibrationSpeedAutoSetupScreen : public Dl2CalibrationSpeedSetupScreen
{
    Q_OBJECT

public:
    explicit Dl2CalibrationSpeedAutoSetupScreen(QWidget* parent);

protected:
    void paintEvent(QPaintEvent*);
};

#endif
