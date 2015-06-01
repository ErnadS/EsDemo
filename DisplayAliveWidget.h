#ifndef DISPLAYALIVEWIDGET_H
#define DISPLAYALIVEWIDGET_H

#include "ScalableWidget.h"
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

#endif // DISPLAYALIVEWIDGET_H
