#ifndef RUNTIME_WIDGET_A_H
#define RUNTIME_WIDGET_A_H

#include "runtime_widget.h"

class RuntimeWidgetA : public RuntimeWidget
{
    qreal m_angle = 0.0f;

public:
    RuntimeWidgetA(QWidget* parent, QSize base_size);

protected:
    void paintEvent(QPaintEvent*);
};

#endif
