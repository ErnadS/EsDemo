#include "selectable_bool_item_widget.h"

SelectableBoolItemWidget::SelectableBoolItemWidget(QWidget* parent, QSize base_size, QString title, QString on_state, QString off_state, Validator* validator) : SelectableItemWidget(parent, base_size, title, "", validator), m_on_state(on_state), m_off_state(off_state)
{

}

void SelectableBoolItemWidget::getValue(void* v) const
{
    *(bool*)v = m_value;
}

QString SelectableBoolItemWidget::getKeyboardString() const
{
    if (m_value == true)
        return m_on_state;

    return m_off_state;
}

void SelectableBoolItemWidget::setValueFromString(const QString&)
{

}

QString SelectableBoolItemWidget::getValueString() const
{
    if (m_value == false)
        return m_off_state;

    return m_on_state;
}

void SelectableBoolItemWidget::mouseReleaseEvent(QMouseEvent*)
{
    m_value = !m_value;

    emit changed(m_title);

    update();
}
