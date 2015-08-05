#ifndef TITLE_WIDGET_H
#define TITLE_WIDGET_H

#include "scalable_widget.h"

class TitleWidget : public ScalableWidget
{
    Q_OBJECT

    QString m_title{"-.-"};
    int m_font_pixel_size = 18;

public:
    explicit TitleWidget(QWidget* parent, QSize base_size);
    explicit TitleWidget(QWidget* parent, QSize base_size, QString title);

    void setTitle(const QString& title);

protected:
    void paintEvent(QPaintEvent* event);
};

#endif
