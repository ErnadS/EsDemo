#ifndef RUNTIMEWIDGETC_H
#define RUNTIMEWIDGETC_H

#include "RuntimeWidget.h"

class RuntimeWidgetC : public RuntimeWidget
{
    QSize m_angle_rect_size{65, 25};

    void drawArrow(QPainter &painter, const QColor &arrowColor, const qreal& speed, const qreal &angle, int radius, int hOffset);
    void drawCompassLabel(QPainter &painter, int compass_radius, QColor color, qreal angle, QString value);

public:
    RuntimeWidgetC(QWidget* parent, QSize base_size);

protected:
    void paintEvent(QPaintEvent*);
};

#endif // RUNTIMEWIDGETC_H
