#include "selectable_int_item_widget.h"

SelectableIntItemWidget::SelectableIntItemWidget(QWidget* parent, QSize base_size, QString title, bool password_protected, Validator* validator) : SelectableItemWidget(parent, base_size, title, "", password_protected, validator)
{

}

void SelectableIntItemWidget::getValue(void* v) const
{
    *(int*)v = m_value;
}

QString SelectableIntItemWidget::getKeyboardString() const
{
    return QString::number(m_value);
}

void SelectableIntItemWidget::setValueFromString(const QString& value)
{
    m_value = value.toInt();
}

QString SelectableIntItemWidget::getValueString() const
{
    return QString::number(m_value) + m_unit;
}

void SelectableIntItemWidget::mouseReleaseEvent(QMouseEvent*)
{
    emit changeValue(m_title, "Numerical");
}
