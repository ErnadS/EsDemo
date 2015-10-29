#ifndef DL2_CALIBRATION_INST_ANGLE_SETUP_SCREEN_H
#define DL2_CALIBRATION_INST_ANGLE_SETUP_SCREEN_H

#include "setup_screen.h"
#include "gui/widget/leg_button.h"
#include "gui/widget/up_down_widget.h"

class Dl2CalibrationInstAngleSetupScreen : public SetupScreen
{
    Q_OBJECT

    qreal m_stw_value{0.0f};
    qreal m_sog_value{0.0f};

    qreal m_stw_angle{0.0f};
    qreal m_sog_angle{0.0f};

    LegButton* m_recommended_button;
    UpDownWidget* m_installation_angle_widget;

    const QSize m_recommended_button_size{370, 80};
    const QSize m_installation_angle_widget_size{370, 80};

    const QPoint m_recommended_button_pos{430, 344};
    const QPoint m_installation_angle_widget_pos{430, 34};

    void drawArrow(QPainter& painter, const qreal& angle);
    QString getAngleString() const;

    qreal normalizeAngle(qreal angle) const;

public:
    explicit Dl2CalibrationInstAngleSetupScreen(QWidget* parent);

protected:
    void paintEvent(QPaintEvent*);
    void setupLayout();
};

#endif
