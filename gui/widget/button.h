#ifndef BUTTON_H
#define BUTTON_H

#include "scalable_widget.h"

class Button : public ScalableWidget
{
    Q_OBJECT

    bool m_frame_on;
    int m_font_pixel_size{20};
    QColor borderColor{160, 160, 160, 40};

    QString m_title;

public:
    explicit Button(QWidget* parent, QSize base_size, QString title = "BACK", bool frame_on = true);

    void setTitle(const QString& title);

signals:
    void clicked();

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
};

#endif
