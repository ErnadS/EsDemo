#include "dl2_calibration_speed_setup_screen.h"

Dl2CalibrationSpeedSetupScreen::Dl2CalibrationSpeedSetupScreen(QWidget* parent) : SetupScreen(parent)
{

}

void Dl2CalibrationSpeedSetupScreen::buttonClicked()
{
    emit backButtonClicked();
}
