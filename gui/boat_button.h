#ifndef BOAT_BUTTON_H
#define BOAT_BUTTON_H

#include "scalable_widget.h"

class BoatButton : public ScalableWidget
{
    Q_OBJECT

public:
    BoatButton(QWidget* parent, QSize base_size);

signals:
    void clicked();

protected:
    void paintEvent(QPaintEvent*);
    void mouseReleaseEvent(QMouseEvent*);
};

#endif
