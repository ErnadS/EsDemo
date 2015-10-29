#ifndef CALIBRATION_GRAPH_WIDGET_H
#define CALIBRATION_GRAPH_WIDGET_H

#include "scalable_widget.h"

class CalibrationGraphWidget: public ScalableWidget
{
public:
    explicit CalibrationGraphWidget(QWidget* parent, QSize base_size);

protected:
    void paintEvent(QPaintEvent*);
};

#endif
