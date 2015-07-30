#ifndef SPEED_INDICATION_WIDGET_H
#define SPEED_INDICATION_WIDGET_H

#include "scalable_widget.h"

class SpeedIndicationWidget : public ScalableWidget
{
    Q_OBJECT

    QString m_value{"SOG -.-/-.- STW -.-/-.-"};
    int m_font_pixel_size = 18;

public:
    explicit SpeedIndicationWidget(QWidget* parent, QSize base_size);
    explicit SpeedIndicationWidget(QWidget* parent, QSize base_size, QString title);

protected:
    void paintEvent(QPaintEvent* event);
};

#endif
