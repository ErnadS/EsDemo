#include "selectable_item_widget.h"
#include <QPainter>

SelectableItemWidget::SelectableItemWidget(QWidget* parent, QSize base_size, QString title, QString unit, bool password_protected, Validator* validator) : ScalableWidget(parent, base_size), m_title(title), m_unit(unit), m_validator(validator), m_password_protected(password_protected)
{

}

void SelectableItemWidget::setRowIndexParity(RowIndexParity parity)
{
    m_row_index_parity = parity;

    update();
}

QString SelectableItemWidget::getUnit()
{
    return m_unit;
}

Validator* SelectableItemWidget::validator() const
{
    return m_validator;
}

bool SelectableItemWidget::isProtected() const
{
    return m_password_protected;
}

void SelectableItemWidget::paintBorderRectangle(QPainter& painter, int x, int y, int width, int height, QColor border_color, QColor background_color)
{
    painter.fillRect(x, y, width, height, background_color);
    painter.setPen(border_color);
    painter.drawRect(x, y, width, height);
}

void SelectableItemWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    QFont font = painter.font();
    font.setPixelSize(18 * m_scale);
    painter.setFont(font);

    QColor value_background_color = QColor(0xDA, 0xDA, 0xDA);

    if (m_row_index_parity == ODD)
    {
        painter.fillRect(rect(), QColor(0xDA, 0xDA, 0xDA));
    }
    else
    {
        painter.fillRect(rect(), QColor(0xBE, 0xBE, 0xBE));
    }

    painter.setPen(Qt::white);
    painter.drawLine(0, height() - 2, width(), height() - 2);
    painter.setPen(QColor(0xA0, 0xA0, 0xA0));
    painter.drawLine(0, height() - 1, width(), height() - 1);

    paintBorderRectangle(painter, 0.7f * width(), 0.25f * height(), 0.25f * width(), 0.5f * height(), QColor(0x90, 0xFF, 0x70), value_background_color);

    painter.setPen(Qt::black);
    painter.drawText(5 * m_scale, 0, 0.66f * width(), height(), Qt::AlignVCenter, m_title);

    font.setPixelSize(13 * m_scale);
    painter.setFont(font);
    painter.drawText(0.7f * width(), 0.25f * height(), 0.25f * width(), 0.5f * height(), Qt::AlignCenter, getValueString());
}
