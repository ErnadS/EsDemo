#include "selectable_string_item_widget.h"

SelectableStringItemWidget::SelectableStringItemWidget(QWidget* parent, QSize base_size, QString title, Validator* validator, bool password_protected) : SelectableItemWidget(parent, base_size, title, "", validator, password_protected)
{

}

void SelectableStringItemWidget::getValue(void* v) const
{
    *(QString*)v = m_value;
}

QString SelectableStringItemWidget::getKeyboardString() const
{
    return m_value;
}

void SelectableStringItemWidget::setValueFromString(const QString& value)
{
    m_value = value;
}

QString SelectableStringItemWidget::getValueString() const
{
    return m_value;
}
void SelectableStringItemWidget::mouseReleaseEvent(QMouseEvent *)
{
    emit changeValue(m_title, "Alphabetical");
}

