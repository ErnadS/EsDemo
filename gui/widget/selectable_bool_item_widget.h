#ifndef SELECTABLE_BOOL_ITEM_WIDGET_H
#define SELECTABLE_BOOL_ITEM_WIDGET_H

#include "selectable_item_widget.h"
#include "gui/widget_enum.h"

class SelectableBoolItemWidget : public SelectableItemWidget
{
    Q_OBJECT

    bool m_value{false};
    QString m_on_state;
    QString m_off_state;

public:
    explicit SelectableBoolItemWidget(QWidget* parent, QSize base_size, QString title, QString on_state, QString off_state, Validator* validator = new Validator("dummy"), bool password_protected = true);
    void getValue(void* v) const;
    QString getKeyboardString() const;
    void setValueFromString(const QString&);
    void setNextValue();

protected:
    QString getValueString() const;
    void mouseReleaseEvent(QMouseEvent*);
};

#endif
