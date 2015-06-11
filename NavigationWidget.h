#ifndef NAVIGATIONWIDGET_H
#define NAVIGATIONWIDGET_H

#include "ScalableWidget.h"
#include "NavigationController.h"

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

#endif // NAVIGATIONWIDGET_H
