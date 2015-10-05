#ifndef SELECTABLE_INT_ITEM_WIDGET_H
#define SELECTABLE_INT_ITEM_WIDGET_H

#include "selectable_item_widget.h"
#include "gui/widget_enum.h"
#include "gui/widget/validator.h"

class SelectableIntItemWidget : public SelectableItemWidget
{
    Q_OBJECT

    int m_value{0};

public:
    explicit SelectableIntItemWidget(QWidget* parent, QSize base_size, QString title, Validator* validator);
    void getValue(void* v) const;
    QString getKeyboardString() const;
    void setValueFromString(const QString& value);

protected:
    QString getValueString() const;
    void mouseReleaseEvent(QMouseEvent*);
};

#endif
