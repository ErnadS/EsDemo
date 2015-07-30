#ifndef RUNTIME_WIDGET_C_H
#define RUNTIME_WIDGET_C_H

#include "runtime_widget.h"

class RuntimeWidgetC : public RuntimeWidget
{
    QSize m_angle_rect_size{65, 25};
    static bool m_true_heading_enabled;

    void drawArrow(QPainter &painter, const QColor &arrowColor, const qreal& speed, const qreal &angle, int radius, int hOffset);
    void drawCompassLabel(QPainter &painter, int compass_radius, QColor color, qreal angle, QString value);

public:
    RuntimeWidgetC(QWidget* parent, QSize base_size);

    static void setTrueHeading(bool value);

protected:
    void paintEvent(QPaintEvent*);
};

#endif
