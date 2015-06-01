#ifndef MULTIRUNTIMEWIDGET_H
#define MULTIRUNTIMEWIDGET_H

#include "ScalableWidget.h"
#include "RuntimeWidgetA.h"
#include "RuntimeWidgetB.h"
#include "RuntimeWidgetD.h"
#include "RuntimeWidgetE.h"

class MultiRuntimeWidget : public ScalableWidget
{
    QSize m_quarter_size;

    RuntimeWidgetA* m_runtime_1;
    RuntimeWidgetB* m_runtime_2;
    RuntimeWidgetD* m_runtime_3;
    RuntimeWidgetE* m_runtime_4;

public:
    explicit MultiRuntimeWidget(QWidget* parent, QSize base_size);

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent* event);
};

#endif // MULTIRUNTIMEWIDGET_H
