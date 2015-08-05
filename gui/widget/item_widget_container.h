#ifndef ITEM_WIDGET_CONTAINER_H
#define ITEM_WIDGET_CONTAINER_H

#include "scalable_widget.h"
#include "item_widget.h"
#include "arrow_widget.h"

class ItemWidgetContainer : public ScalableWidget
{
    Q_OBJECT

    int m_display_size;
    QVector<ItemWidget*> m_item_widget_vector;
    ArrowWidget* m_up_arrow;
    ArrowWidget* m_down_arrow;

    void setupLayout();

    int m_rotation_offset{0};

public:
    explicit ItemWidgetContainer(QWidget* parent, QSize base_size, int display_size, QList<QString> item_list);

signals:
    void itemSelected(int index);

private slots:
    void itemPressed(const ItemWidget* item);
    void upPressed();
    void downPressed();

protected:
    void resizeEvent(QResizeEvent*);
};

#endif
