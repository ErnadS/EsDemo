#ifndef DL1_RUNTIME_WIDGET_B_H
#define DL1_RUNTIME_WIDGET_B_H

#include "runtime_widget.h"

class Dl1RuntimeWidgetB : public RuntimeWidget
{
public:
    Dl1RuntimeWidgetB(QWidget* parent, QSize base_size);

protected:
    void paintEvent(QPaintEvent*);
};

#endif
