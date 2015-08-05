#ifndef ARROW_WIDGET_H
#define ARROW_WIDGET_H

#include "scalable_widget.h"
#include "gui/widget_enum.h"

class ArrowWidget : public ScalableWidget
{
    Q_OBJECT

    VerticalOrientation m_vertical_orientation;

public:
    explicit ArrowWidget(QWidget* parent, QSize base_size, VerticalOrientation vertical_orientation);

signals:
    void pressed();

protected:
    void paintEvent(QPaintEvent*);
    void mouseReleaseEvent(QMouseEvent*);
};

#endif
