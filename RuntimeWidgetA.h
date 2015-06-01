#ifndef RUNTIMEWIDGETA_H
#define RUNTIMEWIDGETA_H

#include "RuntimeWidget.h"

class RuntimeWidgetA : public RuntimeWidget
{
    qreal m_angle = 0.0f;

public:
    RuntimeWidgetA(QWidget* parent, QSize base_size);

protected:
    void paintEvent(QPaintEvent*);
};

#endif // RUNTIMEWIDGETA_H
