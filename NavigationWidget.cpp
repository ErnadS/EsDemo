#include "NavigationWidget.h"
#include <QPainter>
#include <QMouseEvent>

NavigationWidget::NavigationWidget(QWidget* parent, QSize base_size) :
    ScalableWidget(parent, base_size)
{

}

void NavigationWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QBrush brush(QColor(64, 64, 64));

    QFont font = painter.font();
    font.setPixelSize(20 * m_scale);
    painter.setFont(font);

    painter.setPen(QColor(144, 255, 112));

    painter.fillRect(QRectF(0, 0, width(), height()), brush);
    painter.drawText(QRectF(0, 0, width(), height() / 3), Qt::AlignCenter, "Navigate");

    // Arrows
    brush.setColor(QColor(144, 255, 112));
    painter.setBrush(brush);

    painter.translate((width() / 4) - 10 * m_width_scale, 25 * m_height_scale);

    const int polygon_size = 7;

    QPointF left[polygon_size]
    {
        QPointF(0.0, 0.0),
        QPointF(-15.0 * m_width_scale, 15.0 * m_height_scale),
        QPointF(0.0, 30.0 * m_height_scale),
        QPointF(0.0, 22.5 * m_height_scale),
        QPointF(15.0 * m_width_scale, 22.5 * m_height_scale),
        QPointF(15.0 * m_width_scale, 7.5 * m_height_scale),
        QPointF(0.0, 7.5 * m_height_scale),
     };

    painter.drawPolygon(left, 7);

    painter.translate((width() / 2) + 20 * m_width_scale, 0);
    QPointF right[polygon_size]
    {
        QPointF(0.0, 0.0),
        QPointF(15.0 * m_width_scale, 15.0 * m_height_scale),
        QPointF(0.0, 30.0 * m_height_scale),
        QPointF(0.0, 22.5 * m_height_scale),
        QPointF(-15.0 * m_width_scale, 22.5 * m_height_scale),
        QPointF(-15.0 * m_width_scale, 7.5 * m_height_scale),
        QPointF(0.0, 7.5 * m_height_scale),
     };

    painter.drawPolygon(right, 7);
}

void NavigationWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->x() < width() / 2)
    {
        emit navigateLeft();
    }
    else
    {
        emit navigateRight();
    }
}
