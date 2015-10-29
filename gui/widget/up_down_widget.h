#ifndef UP_DOWN_WIDGET_H
#define UP_DOWN_WIDGET_H

#include "scalable_widget.h"

class UpDownWidget : public ScalableWidget
{
    Q_OBJECT

    QString m_title;
    QString m_unit;
    qreal m_step;
    qreal m_value;

    bool m_up_pressed;
    bool m_down_pressed;

    QColor m_background_color;
    QColor m_border_color;

    void drawUpArrow(QPainter& painter, const QRect& arrow_rect);
    void drawDownArrow(QPainter& painter, const QRect& arrow_rect);

public:
    explicit UpDownWidget(QWidget* parent = 0, QSize base_size = QSize(100, 30), QString title = "Value", QString unit = "Unit", qreal step = 0.1f, qreal value = 0.0f);

    void setBackgroundColor(const QColor& value);
    void setBorderColor(const QColor& value);

protected:
    void paintEvent(QPaintEvent*);
};

#endif
