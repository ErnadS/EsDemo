#ifndef DL2_CALIBRATION_TEMP_SETUP_SCREEN_H
#define DL2_CALIBRATION_TEMP_SETUP_SCREEN_H

#include "setup_screen.h"
#include "gui/widget/up_down_widget.h"

class Dl2CalibrationTempSetupScreen : public SetupScreen
{
    Q_OBJECT

    UpDownWidget* m_real_temp_widget;

    const QSize m_real_temp_widget_size{400, 86};
    const QPoint m_real_temp_widget_pos{200, 197};

public:
    explicit Dl2CalibrationTempSetupScreen(QWidget* parent);

protected:
    void paintEvent(QPaintEvent*);
    void setupLayout();
};

#endif
