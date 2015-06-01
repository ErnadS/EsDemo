#ifndef RUNTIMEWIDGETB_H
#define RUNTIMEWIDGETB_H

#include "RuntimeWidget.h"

class RuntimeWidgetB : public RuntimeWidget
{
    qreal m_angle{0.0f};
public:
    RuntimeWidgetB(QWidget* parent, QSize base_size);

protected:
    void paintEvent(QPaintEvent*);
};

#endif // RUNTIMEWIDGETB_H
