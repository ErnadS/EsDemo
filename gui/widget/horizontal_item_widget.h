#ifndef HORIZONTAL_ITEM_WIDGET_H
#define HORIZONTAL_ITEM_WIDGET_H

#include "scalable_widget.h"

class HorizontalItemWidget : public ScalableWidget
{
    Q_OBJECT

    QString m_title;
    bool m_active{false};

public:
    explicit HorizontalItemWidget(QWidget* parent, QSize base_size, QString title);
    void setActive(bool active);

signals:
    void clicked(HorizontalItemWidget*);

protected:
    void paintEvent(QPaintEvent*);
    void mouseReleaseEvent(QMouseEvent*);
};

#endif
