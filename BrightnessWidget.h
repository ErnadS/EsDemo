#ifndef BRIGHTNESSWIDGET_H
#define BRIGHTNESSWIDGET_H

#include "ScalableWidget.h"

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

#endif // BRIGHTNESSWIDGET_H
