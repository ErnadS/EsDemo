#ifndef BUTTON_H
#define BUTTON_H

#include "ScalableWidget.h"

class Button : public ScalableWidget
{
    Q_OBJECT

    bool m_frame_on;
    int m_font_pixel_size{20};
    QColor borderColor{160, 160, 160, 40};

    QString m_title;

public:
    explicit Button(QWidget* parent, QSize base_size, QString title = "BACK", bool frame_on = true);

    QString title() const;
    bool isFrameOn() const;
    int fontPixelSize() const;

public slots:
    void setTitle(const QString& title);
    void setFrameOn(bool value);
    void setFontPixelSize(int font_pixel_size);

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);

signals:
    void pressed();
};

#endif // BUTTON_H
