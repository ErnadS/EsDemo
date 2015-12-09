#include "selectable_enum_item_widget.h"

SelectableEnumItemWidget::SelectableEnumItemWidget(QWidget* parent, QSize base_size, QString title, QList<QString> value_list, QString unit, Validator* validator, bool password_protected) : SelectableItemWidget(parent, base_size, title, unit, validator, password_protected), m_value(value_list)
{

}

void SelectableEnumItemWidget::getValue(void* v) const
{
    *(int*)v = m_index;
}

QString SelectableEnumItemWidget::getKeyboardString() const
{
    return m_value[m_index];
}

void SelectableEnumItemWidget::setValueFromString(const QString&)
{

}

void SelectableEnumItemWidget::setNextValue()
{
    m_index = (m_index + 1) % m_value.size();
    update();
}

QString SelectableEnumItemWidget::getValueString() const
{
    return m_value[m_index] + m_unit;
}

void SelectableEnumItemWidget::mouseReleaseEvent(QMouseEvent*)
{
    emit changed(m_title);
}
