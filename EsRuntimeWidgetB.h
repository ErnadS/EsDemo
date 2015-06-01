#ifndef ESRUNTIMEWIDGETB_H
#define ESRUNTIMEWIDGETB_H

#include "RuntimeWidget.h"

class EsRuntimeWidgetB : public RuntimeWidget
{
public:
    EsRuntimeWidgetB(QWidget* parent, QSize base_size);

protected:
    void paintEvent(QPaintEvent*);
};

#endif // ESRUNTIMEWIDGETB_H
