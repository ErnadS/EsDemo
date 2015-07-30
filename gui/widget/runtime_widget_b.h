#ifndef RUNTIME_WIDGET_B_H
#define RUNTIME_WIDGET_B_H

#include "runtime_widget.h"

class RuntimeWidgetB : public RuntimeWidget
{
    qreal m_angle{0.0f};
public:
    RuntimeWidgetB(QWidget* parent, QSize base_size);

protected:
    void paintEvent(QPaintEvent*);
};

#endif
