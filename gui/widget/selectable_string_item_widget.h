#ifndef SELECTABLE_STRING_ITEM_WIDGET_H
#define SELECTABLE_STRING_ITEM_WIDGET_H

#include "selectable_item_widget.h"
#include "gui/widget_enum.h"
#include "gui/widget/validator.h"

class SelectableStringItemWidget : public SelectableItemWidget
{
    Q_OBJECT

    QString m_value{"hrkljus"};

public:
    explicit SelectableStringItemWidget(QWidget* parent, QSize base_size, QString title, Validator* validator = new Validator("dummy"), bool password_protected = true);
    void getValue(void* v) const;
    QString getKeyboardString() const;
    void setValueFromString(const QString& value);

protected:
    QString getValueString() const;
    void mouseReleaseEvent(QMouseEvent*);
};

#endif
