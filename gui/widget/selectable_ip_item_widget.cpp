#include "selectable_ip_item_widget.h"

SelectableIpItemWidget::SelectableIpItemWidget(QWidget* parent, QSize base_size, QString title, bool password_protected, Validator* validator) : SelectableItemWidget(parent, base_size, title, "", password_protected, validator)
{

}

void SelectableIpItemWidget::getValue(void* v) const
{
    *(QHostAddress*)v = m_value;
}

QString SelectableIpItemWidget::getKeyboardString() const
{
    return m_value.toString();
}

void SelectableIpItemWidget::setValueFromString(const QString& value)
{
    m_value = QHostAddress(value);
}

QString SelectableIpItemWidget::getValueString() const
{
    return m_value.toString();
}

void SelectableIpItemWidget::mouseReleaseEvent(QMouseEvent *)
{
    emit changeValue(m_title, "Numerical");
}
