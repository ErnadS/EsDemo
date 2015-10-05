#ifndef SELECTABLE_IP_ITEM_WIDGET_H
#define SELECTABLE_IP_ITEM_WIDGET_H

#include "selectable_item_widget.h"
#include "gui/widget_enum.h"
#include <QHostAddress>
#include "gui/widget/validator.h"

class SelectableIpItemWidget : public SelectableItemWidget
{
    Q_OBJECT

    QHostAddress m_value{"127.0.0.1"};

public:
    explicit SelectableIpItemWidget(QWidget* parent, QSize base_size, QString title, Validator* validator = new Validator("dummy"));
    void getValue(void* v) const;
    QString getKeyboardString() const;
    void setValueFromString(const QString& value);

protected:
    QString getValueString() const;
};

#endif
