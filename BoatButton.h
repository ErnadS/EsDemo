#ifndef BOATBUTTON_H
#define BOATBUTTON_H

#include "ScalableWidget.h"

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

#endif // BOATBUTTON_H
