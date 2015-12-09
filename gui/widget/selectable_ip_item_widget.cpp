#include "selectable_ip_item_widget.h"

SelectableIpItemWidget::SelectableIpItemWidget(QWidget* parent, QSize base_size, QString title, Validator* validator, bool password_protected) : SelectableItemWidget(parent, base_size, title, "", validator, password_protected)
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
