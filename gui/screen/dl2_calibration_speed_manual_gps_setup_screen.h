#ifndef DL2_CALIBRATION_SPEED_MANUAL_GPS_SETUP_SCREEN_H
#define DL2_CALIBRATION_SPEED_MANUAL_GPS_SETUP_SCREEN_H

#include "dl2_calibration_speed_setup_screen.h"
#include "gui/widget/calibration_graph_widget.h"
#include "gui/widget/leg_button.h"

class Dl2CalibrationSpeedManualGpsSetupScreen : public Dl2CalibrationSpeedSetupScreen
{
    Q_OBJECT

    CalibrationGraphWidget* m_graph;

    QTextEdit* m_text_edit;

    LegButton* m_recalibrate_button;
    LegButton* m_save_button;
    LegButton* m_discard_button;

    const QSize m_graph_size{540, 400};
    const QSize m_recalibrate_button_size{250, 50};
    const QSize m_save_button_size{250, 50};
    const QSize m_discard_button_size{250, 50};

    const QPoint m_graph_pos{0, 30};
    const QPoint m_recalibrate_button_pos{540, 195};
    const QPoint m_save_button_pos{540, 195};
    const QPoint m_discard_button_pos{540, 248};

public:
    explicit Dl2CalibrationSpeedManualGpsSetupScreen(QWidget* parent);

protected:
    void setupLayout();
};

#endif
