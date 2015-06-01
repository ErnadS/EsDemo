#include "BrightnessWidget.h"
#include <QPainter>
#include <QMouseEvent>

BrightnessWidget::BrightnessWidget(QWidget* parent, QSize base_size) :
    ScalableWidget(parent, base_size)
{

}

void BrightnessWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QBrush brush(QColor(64, 64, 64));

    QFont font = painter.font();
    font.setPixelSize(20 * m_scale);
    painter.setFont(font);

    painter.setPen(m_color);

    painter.fillRect(QRectF(0, 0, width(), height()), brush);

    painter.drawText(QRectF(0, 0, width(), height() / 3), Qt::AlignCenter, "Brightness");
    QString brighText = "100";

    painter.drawText(QRectF(0, 0, width(), height()), Qt::AlignCenter, brighText + "%");

    // Arrows
    brush.setColor(m_color);
    painter.setBrush(brush);

    painter.translate((width() / 4) - 10 * m_width_scale, 25 * m_height_scale);

    const int polygon_size = 7;

    QPointF up[polygon_size]
    {
        QPointF(-15.0 * m_width_scale, 15.0 * m_height_scale),
        QPointF(0.0, 0.0),
        QPointF(15.0 * m_width_scale, 15.0 * m_height_scale),
        QPointF(7.5 * m_width_scale, 15.0 * m_height_scale),
        QPointF(7.5 * m_width_scale, 30.0 * m_height_scale),
        QPointF(-7.5 * m_width_scale, 30.0 * m_height_scale),
        QPointF(-7.5 * m_width_scale, 15.0 * m_height_scale)
     };

    painter.drawPolygon(up, 7);

    painter.translate((width() / 2) + 20 * m_width_scale, 0);

    QPointF down[polygon_size]
    {
        QPointF(-15.0 * m_width_scale, 15.0 * m_height_scale),
        QPointF(0.0, 30.0 * m_height_scale),
        QPointF(15.0 * m_width_scale, 15.0 * m_height_scale),
        QPointF(7.5 * m_width_scale, 15.0 * m_height_scale),
        QPointF(7.5 * m_width_scale, 0.0),
        QPointF(-7.5 * m_width_scale, 0.0),
        QPointF(-7.5 * m_width_scale, 15.0 * m_height_scale)
    };

    painter.drawPolygon(down, 7);
}

void BrightnessWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->x() <= width() / 2)
    {
        // TODO: Increase brightness by 1
    }
    else
    {
        // TODO: Decrease brightness by 1
    }
}
