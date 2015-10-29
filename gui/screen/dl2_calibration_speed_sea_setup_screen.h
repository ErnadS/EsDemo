#ifndef DL2_CALIBRATION_SPEED_SEA_SCREEN_H
#define DL2_CALIBRATION_SPEED_SEA_SCREEN_H

#include "dl2_calibration_speed_setup_screen.h"
#include "gui/widget/leg_button.h"
#include "gui/widget/calibration_graph_widget.h"

enum SeaTestState { IDLE, START_LEG_1, STOP_LEG_1, START_LEG_2, STOP_LEG_2, PARTIAL, COMPLETE };

class Dl2CalibrationSpeedSeaSetupScreen : public Dl2CalibrationSpeedSetupScreen
{
    Q_OBJECT

    SeaTestState m_state{IDLE};

    qreal m_leg_distance{0.0f};
    qreal m_meas_stw{0.0f};
    qreal m_meas_sog{0.0f};
    qreal m_calc_real_speed{0.0f};
    qreal m_gps_avg{0.0f};
    qreal m_gps_min{0.0f};
    qreal m_gps_max{0.0f};
    qreal m_distance_water{0.0f};
    qreal m_distance_ground{0.0f};
    qreal m_leg_one_sog_valid_percentage{0.0f};
    qreal m_leg_one_stw_valid_percentage{0.0f};
    qreal m_leg_two_sog_valid_percentage{0.0f};
    qreal m_leg_two_stw_valid_percentage{0.0f};

    CalibrationGraphWidget* m_graph;
    QTextEdit* m_text_edit;
    LegButton* m_left_button;
    LegButton* m_right_button;
    LegButton* m_leg_distance_button;
    LegButton* m_cancel_button;
    LegButton* m_save_button;
    LegButton* m_discard_button;

    const QSize m_graph_size{540, 400};
    const QSize m_text_edit_size{400, 300};
    const QSize m_left_button_size{95, 35};
    const QSize m_right_button_size{95, 35};
    const QSize m_leg_distance_button_size{160, 40};
    const QSize m_cancel_button_size{95, 35};
    const QSize m_save_button_size{155, 65};
    const QSize m_discard_button_size{155, 65};

    const QPoint m_graph_pos{0, 30};
    const QPoint m_text_edit_pos{2, 80};
    const QPoint m_left_button_pos{430, 144};
    const QPoint m_right_button_pos{685, 144};
    const QPoint m_leg_distance_button_pos{515, 44};
    const QPoint m_cancel_button_pos{685, 185};
    const QPoint m_save_button_pos{639, 260};
    const QPoint m_discard_button_pos{639, 327};

    void init();

    bool displayMeasurementsGps() const;
    bool orientationRight() const;

    QString getValueString(qreal value, int decimal = 1);

    QString getInstructionString() const;
    QColor getValidityColour(qreal value) const;

    void drawArrow(QPainter& painter, int x, int y, int w, int h, const QColor& color);

    void updateState();

public:
    explicit Dl2CalibrationSpeedSeaSetupScreen(QWidget* parent);

protected:
    void setupLayout();
    void paintEvent(QPaintEvent*);
};

#endif
