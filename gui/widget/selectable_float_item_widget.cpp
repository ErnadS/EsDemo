#include "selectable_float_item_widget.h"

SelectableFloatItemWidget::SelectableFloatItemWidget(QWidget* parent, QSize base_size, QString title, QString unit, bool password_protected, Validator* validator) : SelectableItemWidget(parent, base_size, title, unit, password_protected, validator)
{

}

void SelectableFloatItemWidget::getValue(void* v) const
{
    *(float*)v = m_value;
}

QString SelectableFloatItemWidget::getKeyboardString() const
{
    return QString::number(m_value, 'f', 1);
}

void SelectableFloatItemWidget::setValueFromString(const QString& value)
{
    m_value = value.toFloat();
}

QString SelectableFloatItemWidget::getValueString() const
{
    return QString::number(m_value, 'f', 1) + m_unit;
}

void SelectableFloatItemWidget::mouseReleaseEvent(QMouseEvent*)
{
    emit changeValue(m_title, "Numerical");
}
