#ifndef NAVIGATION_WIDGET_H
#define NAVIGATION_WIDGET_H

#include "scalable_widget.h"
#include "navigation_controller.h"

class NavigationWidget : public ScalableWidget
{
    Q_OBJECT

    NavigationController& m_navigation_controller;

public:
    explicit NavigationWidget(QWidget* parent, QSize base_size);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent* event);
};

#endif
