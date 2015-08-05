#ifndef ITEM_WIDGET_H
#define ITEM_WIDGET_H

#include "scalable_widget.h"
#include "gui/widget_enum.h"

class ItemWidget : public ScalableWidget
{
    Q_OBJECT

    RowIndexParity m_row_index_parity;
    QString m_title;

public:
    explicit ItemWidget(QWidget* parent, QSize base_size, const QString& title, RowIndexParity row_index_parity = ODD);

signals:
    void pressed(const ItemWidget* address);

protected:
    void paintEvent(QPaintEvent*);
    void mouseReleaseEvent(QMouseEvent*);
};

#endif
