#include "system_widget.h"
#include <QPainter>

void SystemWidget::drawBoat(QPainter& painter, const QRect rect)
{
    QColor color(166, 166, 166);

    QRect bottom_rect(0.125f * rect.width(), 0.3375f * rect.height(), 0.75f * rect.width(), 0.325f * rect.height());
    QRect top_rect(0.125f * rect.width(), 0.0125f * rect.height(), 0.325f * rect.height(), 0.325f * rect.height());
    painter.fillRect(bottom_rect, color);
    painter.fillRect(top_rect, color);

    painter.setPen(Qt::black);

    QFont font = painter.font();
    font.setPixelSize(18 * m_scale);
    painter.setFont(font);

    painter.drawText(bottom_rect, Qt::AlignCenter, m_system_type);

    QRect label_rect(0.125f * rect.width(), 0.6625f * rect.height(), 0.75f * rect.width(), 0.3375f * rect.height());
    painter.drawText(label_rect, Qt::AlignCenter, m_system_name);

    painter.setPen(Qt::yellow);
    int h = 40 * m_height_scale;

    QPolygon polygon(4);
    polygon[0] = QPoint(0, -h);
    polygon[1] = QPoint(-7 * m_width_scale, -h + 12 * m_height_scale);
    polygon[2] = QPoint(7 * m_width_scale, -h + 12 * m_height_scale);
    polygon[3] = QPoint(0, -h);

    QPainterPath path;
    path.addPolygon(polygon);

    if (m_system_type == "SPEED")
    {
        painter.translate(top_rect.center().x() + top_rect.width(), top_rect.center().y());
        painter.rotate(90.0f);
        painter.drawLine(0, 0, 0, -h);

        painter.fillPath(path, Qt::yellow);
        painter.drawPath(path);
    }
    else
    {
        painter.translate(bottom_rect.center().x() + 0.5f * bottom_rect.width() + 0.25f * (width() - bottom_rect.width()), bottom_rect.center().y());
        painter.rotate(180.0f);
        painter.drawLine(0, 0, 0, -h);

        painter.fillPath(path, Qt::yellow);
        painter.drawPath(path);
    }
}

SystemWidget::SystemWidget(QWidget* parent, QSize base_size, QString system_type, QString system_name) : ScalableWidget(parent, base_size), m_system_type(system_type), m_system_name(system_name)
{

}

void SystemWidget::setActive(bool active)
{
    m_active = active;

    update();
}

void SystemWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    if (m_active == true)
    {
        painter.fillRect(QRect(0, 0, width(), height()), QColor(242, 242, 242));
    }
    else
    {
        painter.fillRect(QRect(0, 0, width(), height()), QColor(200, 214, 230));
    }

    drawBoat(painter, rect());
}

void SystemWidget::mouseReleaseEvent(QMouseEvent*)
{
    emit clicked();
}
