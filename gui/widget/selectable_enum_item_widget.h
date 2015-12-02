#ifndef SELECTABLE_ENUM_ITEM_WIDGET_H
#define SELECTABLE_ENUM_ITEM_WIDGET_H

#include "selectable_item_widget.h"
#include "gui/widget_enum.h"
#include "gui/widget/validator.h"

class SelectableEnumItemWidget : public SelectableItemWidget
{
    Q_OBJECT
    int m_index = 0;
    QList<QString> m_value;

public:
    explicit SelectableEnumItemWidget(QWidget* parent, QSize base_size, QString title, QList<QString> value_list, QString unit = "", bool password_protected = true, Validator* validator = new Validator("dummy"));
    void getValue(void* v) const;
    QString getKeyboardString() const;
    void setValueFromString(const QString&);
    void setNextValue();

protected:
    QString getValueString() const;
    void mouseReleaseEvent(QMouseEvent*);
};

#endif
