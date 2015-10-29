#include "horizontal_item_widget.h"
#include <QPainter>

HorizontalItemWidget::HorizontalItemWidget(QWidget* parent, QSize base_size, QString title) : ScalableWidget(parent, base_size), m_title(title)
{

}

void HorizontalItemWidget::setActive(bool active)
{
    m_active = active;

    update();
}

void HorizontalItemWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    QFont font;
    font.setPixelSize(22 * m_scale);
    painter.setFont(font);
    QPen pen(Qt::black);
    painter.setPen(pen);

    if (m_active == true)
    {
        painter.fillRect(0, 0, width(), height(), QColor(218, 218, 218));
        painter.fillRect(2, 2, width() - 4, height() - 4, QColor(144, 255, 112));
    }
    else
    {
        painter.fillRect(0, 0, width(), height(), QColor(144, 255, 112));
        painter.fillRect(2, 2, width() - 4, height() - 4, QColor(218, 218, 218));
    }

    painter.drawText(0, 0, width(), height(), Qt::AlignCenter, m_title);
}

void HorizontalItemWidget::mouseReleaseEvent(QMouseEvent*)
{
    emit clicked(this);
}
