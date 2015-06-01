#include "RuntimeWidget.h"

RuntimeWidget::RuntimeWidget(QWidget* parent, QSize base_size) : ScalableWidget(parent, base_size)
{

}

void RuntimeWidget::drawBoat(QPainter& painter, const QRect rect, qreal angle)
{
    QColor color = QColor(64, 64, 64);
    QBrush brush(color, Qt::SolidPattern);

    int half_width = 20 * m_width_scale;
    int half_height = 31 * m_height_scale;
    int top_height = 22 * m_height_scale;

    QPolygon polygon(6);
    polygon[0] = QPoint(-half_width, half_height );         // Bottom left
    polygon[1] = QPoint(half_width, half_height);           // Bottom right
    polygon[2] = QPoint(half_width, -half_height);          // Top right
    polygon[3] = QPoint(0, -(half_height + top_height));    // Top
    polygon[4] = QPoint(-half_width, -half_height );        // Top left
    polygon[5] = QPoint(-half_width, half_height);          // Bottom left
    polygon.translate(0, 0.5f * top_height);

    QPainterPath path;
    path.addPolygon(polygon);

    painter.save();
    painter.translate(rect.center().x(), rect.center().y());
    painter.fillPath(path, brush);

    drawBoatArrow(painter, angle);

    painter.restore();
}

void RuntimeWidget::drawBoatArrow(QPainter& painter, qreal angle)
{
    painter.rotate(angle);
    int h = 40 * m_height_scale;

    QPen pen = painter.pen();
    pen.setStyle(Qt::DashLine);
    painter.setPen(pen);
    painter.drawLine(0, 0, 0, -h);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);

    QPolygon polygon(4);
    polygon[0] = QPoint(0, -h);
    polygon[1] = QPoint(-7 * m_width_scale, -h + 12 * m_height_scale);
    polygon[2] = QPoint(7 * m_width_scale, -h + 12 * m_height_scale);
    polygon[3] = QPoint(0, -h);
    QPainterPath path;
    path.addPolygon(polygon);

    QBrush brush(pen.color());
    painter.fillPath(path, brush);
    painter.drawPath(path);
    painter.rotate(-angle);
}

void RuntimeWidget::drawArrow(QPainter& painter, const QRect rect, qreal angle)
{
    int half_width = 20 * m_width_scale;
    int half_height = 25 * m_height_scale;
    int top_height = 25 * m_height_scale;
    int top_width = 14 * m_width_scale;

    QPolygon polygon(8);
    polygon[0] = QPoint(-half_width, half_height);                  // Bottom left
    polygon[1] = QPoint(half_width, half_height);                   // Bottom right
    polygon[2] = QPoint(half_width, -half_height);                  // Top right
    polygon[3] = QPoint(half_width + top_width, -half_height);      // Right
    polygon[4] = QPoint(0, -half_height - top_height);              // Top
    polygon[5] = QPoint(-half_width -top_width, -half_height);      // Left
    polygon[6] = QPoint(-half_width, -half_height);                 // Top left
    polygon[7] = QPoint(-half_width, half_height);                  // Bottom left

    polygon.translate(0, 0.5f * top_height);

    QPainterPath path;
    path.addPolygon(polygon);

    QPen pen = painter.pen();
    painter.save();
    painter.translate(rect.center().x(), rect.center().y());
    painter.setPen(QPen(Qt::black));
    painter.rotate(angle);
    painter.drawPolygon(polygon);
    painter.fillPath(path, QBrush(pen.color()));
    painter.restore();
}
