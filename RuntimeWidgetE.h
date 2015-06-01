#ifndef RUNTIMEWIDGETE_H
#define RUNTIMEWIDGETE_H

#include "RuntimeWidget.h"
#include "common/Buffer.h"

struct DepthMeasurement
{
    qint64 time;
    qreal speed;
    qreal front_depth;
    qreal side_depth;
};

class RuntimeWidgetE : public RuntimeWidget
{
    static int m_vessel_index;
    static LifoBuffer<DepthMeasurement> m_buffer;

public:
    RuntimeWidgetE(QWidget* parent, QSize base_size);

    static void addMeasurement(qreal front_depth, qreal side_depth);
    static int vesselIndex();

protected:
    void paintEvent(QPaintEvent*);
    void drawBoat(QPainter& painter, const QRect rect);
    void mouseReleaseEvent(QMouseEvent*);
};

#endif // RUNTIMEWIDGETE_H
