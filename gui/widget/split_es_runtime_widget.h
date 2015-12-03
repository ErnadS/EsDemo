#ifndef SPLIT_ES_RUNTIME_WIDGET_H
#define SPLIT_ES_RUNTIME_WIDGET_H

#include "runtime_widget.h"
#include "gui/widget/runtime_widget_es.h"

enum echosonarLayout{ SINGLE, HORIZONTAL, VERTICAL };
class SplitESRuntimeWidget: public RuntimeWidget
{
    RuntimeWidgetEs* m_widget1{nullptr};
    RuntimeWidgetEs* m_widget2{nullptr};

    echosonarLayout m_widget_layout;

public:
    SplitESRuntimeWidget(QWidget* parent, QSize base_size, echosonarLayout widget_layout = VERTICAL);
    void setLayout(echosonarLayout layout);


protected:
    void paintEvent(QPaintEvent*);
    void setupLayout();
    void resizeEvent(QResizeEvent*);

};

#endif // SPLIT_ES_RUNTIME_WIDGET_H
