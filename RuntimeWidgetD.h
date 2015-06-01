#ifndef RUNTIMEWIDGETD_H
#define RUNTIMEWIDGETD_H

#include "RuntimeWidget.h"

class RuntimeWidgetD : public RuntimeWidget
{
    QSize m_arrow_rect_size{60, 60};
    QSize m_label_rect_size{145, 60};

public:
    RuntimeWidgetD(QWidget* parent, QSize base_size);

protected:
    void paintEvent(QPaintEvent*);

protected:
    void drawBoat(QPainter& painter, const QRect rect);
    void drawArrow(QPainter& painter, const QColor color, const QRect rect, qreal angle, bool fill);
};

#endif // RUNTIMEWIDGETD_H
