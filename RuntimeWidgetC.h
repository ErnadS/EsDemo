#ifndef RUNTIMEWIDGETC_H
#define RUNTIMEWIDGETC_H

#include "ScalableWidget.h"

class RuntimeWidgetC : public ScalableWidget
{
public:
    RuntimeWidgetC(QWidget* parent, QSize base_size);

protected:
    void paintEvent(QPaintEvent*);
};

#endif // RUNTIMEWIDGETC_H
