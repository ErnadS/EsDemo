#ifndef DL2_CALIBRATION_STATUS_SETUP_SCREEN_H
#define DL2_CALIBRATION_STATUS_SETUP_SCREEN_H

#include "setup_screen.h"
#include "gui/widget/calibration_graph_widget.h"

class Dl2CalibrationStatusSetupScreen : public SetupScreen
{
    Q_OBJECT

    CalibrationGraphWidget* m_graph;

    const QSize m_graph_size{540, 400};
    const QPoint m_graph_pos{0, 30};

    QLabel* m_calibration_status_label;
    QLabel* m_reason_label;
    QLabel* m_suggestion_label;

public:
    explicit Dl2CalibrationStatusSetupScreen(QWidget* parent);

protected:
    void setupLayout();
    void paintEvent(QPaintEvent*);
};

#endif
