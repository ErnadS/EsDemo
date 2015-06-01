#ifndef RUNTIMEWIDGETDL1_H
#define RUNTIMEWIDGETDL1_H

#include "RuntimeWidget.h"

class RuntimeWidgetDl1 : public RuntimeWidget
{
public:
    RuntimeWidgetDl1(QWidget* parent, QSize base_size);

protected:
    void paintEvent(QPaintEvent*);
};

#endif // RUNTIMEWIDGETDL1_H
