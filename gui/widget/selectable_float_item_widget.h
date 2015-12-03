#ifndef SELECTABLE_FLOAT_ITEM_WIDGET_H
#define SELECTABLE_FLOAT_ITEM_WIDGET_H

#include "selectable_item_widget.h"
#include "gui/widget_enum.h"
#include "gui/widget/validator.h"

class SelectableFloatItemWidget : public SelectableItemWidget
{
    Q_OBJECT

    qreal m_value{0.0f};

public:
    explicit SelectableFloatItemWidget(QWidget* parent, QSize base_size, QString title, QString unit, bool password_protected = true, Validator* validator = new Validator("dummy"));
    void getValue(void* v) const;
    QString getKeyboardString() const;
    void setValueFromString(const QString& value);

protected:
    QString getValueString() const;
    void mouseReleaseEvent(QMouseEvent*);
};

#endif
