#ifndef MULTIRUNTIMEWIDGET_H
#define MULTIRUNTIMEWIDGET_H

#include "ScalableWidget.h"
#include "RuntimeWidgetA.h"
#include "RuntimeWidgetB.h"
#include "RuntimeWidgetC.h"
#include "RuntimeWidgetD.h"
#include "RuntimeWidgetE.h"
#include <QStackedLayout>

class MultiRuntimeWidget : public ScalableWidget
{
    QSize m_quarter_size;

    QWidget* m_runtime_1;
    QStackedLayout* m_runtime_1_layout;

    QWidget* m_runtime_2;
    QStackedLayout* m_runtime_2_layout;

    QWidget* m_runtime_3;
    QStackedLayout* m_runtime_3_layout;

    QWidget* m_runtime_4;
    QStackedLayout* m_runtime_4_layout;

    QStackedLayout* createLayout(QWidget* parent);

public:
    explicit MultiRuntimeWidget(QWidget* parent, QSize base_size);

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent* event);

    // QWidget interface
protected:
    void mouseReleaseEvent(QMouseEvent* event);
};

#endif // MULTIRUNTIMEWIDGET_H
