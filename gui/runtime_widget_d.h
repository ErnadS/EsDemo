#ifndef RUNTIME_WIDGET_D_H
#define RUNTIME_WIDGET_D_H

#include "runtime_widget.h"

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

#endif
