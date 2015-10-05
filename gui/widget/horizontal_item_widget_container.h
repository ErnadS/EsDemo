#ifndef HORIZONTAL_ITEM_WIDGET_CONTAINER_H
#define HORIZONTAL_ITEM_WIDGET_CONTAINER_H

#include "scalable_widget.h"
#include "horizontal_item_widget.h"

class HorizontalItemWidgetContainer : public ScalableWidget
{
    Q_OBJECT

    QVector<HorizontalItemWidget*> m_item_widget_vector;

    void setupLayout();

    QSize m_item_size;
    int m_item_sep;

public:
    explicit HorizontalItemWidgetContainer(QWidget* parent, QSize base_size, QSize item_size, int item_sep);
    void addWidget(HorizontalItemWidget* item_widget);
    void setActive(int index);

signals:
    void clicked(int);

protected:
    void resizeEvent(QResizeEvent*);

private slots:
    void clicked(HorizontalItemWidget* item);
};

#endif
