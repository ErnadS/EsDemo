#ifndef RUNTIME_WIDGET_H
#define RUNTIME_WIDGET_H

#include "scalable_widget.h"
#include <QPainter>

class RuntimeWidget : public ScalableWidget
{
protected:
    virtual void drawBoat(QPainter& painter, const QRect rect, qreal angle);
    virtual void drawBoatArrow(QPainter& painter, qreal angle);
    virtual void drawArrow(QPainter& painter, const QRect rect, qreal angle);
    //TODO: Remove later
    QPoint textSize(const QFont& font, const QString& text)
    {
        QFontMetrics metrics(font);
        return QPoint(metrics.width(text), metrics.height());
    }

    QSize m_gps_logo_size{32, 32};

public:
    RuntimeWidget(QWidget* parent, QSize base_size);
};

#endif
