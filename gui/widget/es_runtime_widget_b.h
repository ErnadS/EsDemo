#ifndef ES_RUNTIME_WIDGET_B_H
#define ES_RUNTIME_WIDGET_B_H

#include "runtime_widget.h"

class EsRuntimeWidgetB : public RuntimeWidget
{
public:
    EsRuntimeWidgetB(QWidget* parent, QSize base_size);

protected:
    void paintEvent(QPaintEvent*);
};

#endif
