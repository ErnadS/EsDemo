#ifndef BRIGHTNESS_WIDGET_H
#define BRIGHTNESS_WIDGET_H

#include "scalable_widget.h"

class BrightnessWidget : public ScalableWidget
{
    Q_OBJECT

public:
    explicit BrightnessWidget(QWidget* parent, QSize base_size);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent* event);
};

#endif
