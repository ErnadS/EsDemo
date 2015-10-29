#ifndef DL2_CALIBRATION_TILT_SETUP_SCREEN_H
#define DL2_CALIBRATION_TILT_SETUP_SCREEN_H

#include "setup_screen.h"
#include "gui/widget/up_down_widget.h"
#include "gui/widget/leg_button.h"

class Dl2CalibrationTiltSetupScreen : public SetupScreen
{
    Q_OBJECT

    LegButton* m_pitch_button;
    LegButton* m_roll_button;
    UpDownWidget* m_pitch_offset_widget;
    UpDownWidget* m_roll_offset_widget;

    qreal m_pitch{0.0f};
    qreal m_roll{0.0f};

    qreal m_max_pitch_offset{0.0f};
    qreal m_min_pitch_offset{0.0f};
    qreal m_avg_pitch_offset{0.0f};
    qreal m_max_roll_offset{0.0f};
    qreal m_min_roll_offset{0.0f};
    qreal m_avg_roll_offset{0.0f};

    const QSize m_pitch_button_size{115, 50};
    const QSize m_roll_button_size{115, 50};
    const QSize m_pitch_offset_widget_size{350, 60};
    const QSize m_roll_offset_widget_size{350, 60};

    const QPoint m_pitch_button_pos{140, 375};
    const QPoint m_roll_button_pos{540, 375};
    const QPoint m_pitch_offset_widget_pos{0, 45};
    const QPoint m_roll_offset_widget_pos{450, 45};

public:
    explicit Dl2CalibrationTiltSetupScreen(QWidget* parent);

protected:
    void setupLayout();
    void paintEvent(QPaintEvent*);
};

#endif
