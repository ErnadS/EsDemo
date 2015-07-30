#ifndef RUNTIME_WIDGET_DL1_H
#define RUNTIME_WIDGET_DL1_H

#include "runtime_widget.h"

class RuntimeWidgetDl1 : public RuntimeWidget
{
public:
    RuntimeWidgetDl1(QWidget* parent, QSize base_size);

protected:
    void paintEvent(QPaintEvent*);
};

#endif
