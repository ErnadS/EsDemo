#ifndef NAVIGATIONWIDGET_H
#define NAVIGATIONWIDGET_H

#include "ScalableWidget.h"

class NavigationWidget : public ScalableWidget
{
    Q_OBJECT
public:
    explicit NavigationWidget(QWidget* parent, QSize base_size);

signals:
    void navigateLeft();
    void navigateRight();

    // QWidget interface
protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent* event);
};

#endif // NAVIGATIONWIDGET_H
