#ifndef LEG_BUTTON_H
#define LEG_BUTTON_H

#include "scalable_widget.h"

class LegButton : public ScalableWidget
{
    Q_OBJECT

    QString m_title;

    bool m_highlighted{false};

    QColor m_background_color{168, 168, 168};
    QColor m_border_color{168, 168, 168};

    int m_font_pixel_size{20};

public:
    explicit LegButton(QWidget* parent, QSize base_size, QString title);

    void setTitle(const QString& title);
    void setFontPixelSize(int font_pixel_size);
    void setBackgroundColor(const QColor& color);
    void setBorderColor(const QColor& color);

protected:
    void paintEvent(QPaintEvent*);
};

#endif
