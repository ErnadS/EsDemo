#ifndef RUNTIME_WIDGET_E_H
#define RUNTIME_WIDGET_E_H

#include "runtime_widget.h"
#include "utility/Buffer.h"

struct DepthMeasurement
{
    qint64 time;
    qreal speed;
    qreal front_depth;
    qreal side_depth;
};

class RuntimeWidgetE : public RuntimeWidget
{
    bool m_is_multi{false};
    static int m_vessel_index;
    static LifoBuffer<DepthMeasurement> m_buffer;

public:
    RuntimeWidgetE(QWidget* parent, QSize base_size, bool is_multi);

    static void addMeasurement(qreal front_depth, qreal side_depth);
    static int vesselIndex();

protected:
    void paintEvent(QPaintEvent*);
    void drawBoat(QPainter& painter, const QRect rect);
    void mouseReleaseEvent(QMouseEvent*);
};

#endif