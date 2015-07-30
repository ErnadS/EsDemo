#ifndef DISPLAY_ALIVE_WIDGET_H
#define DISPLAY_ALIVE_WIDGET_H

#include "scalable_widget.h"
#include <QTimer>

class DisplayAliveWidget : public ScalableWidget
{
    Q_OBJECT

    QTimer* m_blink_timer;
    bool m_toggled{true};
    QString m_hours{"00"};
    QString m_minutes{"00"};

    int m_font_pixel_size{20};

private slots:
    void toggleBlink();

public:
    explicit DisplayAliveWidget(QWidget* parent, QSize base_size);

protected:
    void paintEvent(QPaintEvent*);
};

#endif
