#include "item_widget.h"
#include <QPainter>

ItemWidget::ItemWidget(QWidget* parent, QSize base_size, const QString& title, RowIndexParity row_index_parity) : ScalableWidget(parent, base_size), m_row_index_parity(row_index_parity), m_title(title)
{

}

void ItemWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QFont font = painter.font();
    font.setPixelSize(30 * m_scale);
    painter.setFont(font);
    painter.setPen(Qt::black);

    if (m_row_index_parity == ODD)
    {
        painter.fillRect(0, 0, width(), height(), QColor(219, 219, 219));
    }
    else
    {
        painter.fillRect(0, 0, width(), height(), QColor(191, 191, 191));
    }

    painter.setPen(Qt::white);
    painter.drawLine(0, 0, width(), 0);
    painter.setPen(QColor(161, 161, 161));
    painter.drawLine(0, 1, width(), 1);

    painter.setPen(Qt::black);
    painter.drawText(0, 0, width(), height(), Qt::AlignCenter, m_title);
}

void ItemWidget::mouseReleaseEvent(QMouseEvent*)
{
    emit pressed(this);
}
