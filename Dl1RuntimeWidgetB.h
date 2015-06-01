#ifndef DL1RUNTIMEWIDGETB_H
#define DL1RUNTIMEWIDGETB_H

#include "RuntimeWidget.h"

class Dl1RuntimeWidgetB : public RuntimeWidget
{
public:
    Dl1RuntimeWidgetB(QWidget* parent, QSize base_size);

protected:
    void paintEvent(QPaintEvent*);
};

#endif // DL1RUNTIMEWIDGETB_H
