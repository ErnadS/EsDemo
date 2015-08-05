#include "arrow_widget.h"
#include <QPainter>

ArrowWidget::ArrowWidget(QWidget* parent, QSize base_size, VerticalOrientation vertical_orientation) : ScalableWidget(parent, base_size), m_vertical_orientation(vertical_orientation)
{

}

void ArrowWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    if (m_vertical_orientation == FORWARD)
    {
        painter.translate(width() / 2, height() / 2);
    }
    else
    {
        painter.translate(width() / 2, height() / 2);
        painter.rotate(180.0f);
    }

    QPolygon polygon(4);

    int half_width  = width()  / 2;
    int half_height = height() / 2;

    polygon[0] = QPoint(-half_width, half_height);                  // Bottom left
    polygon[1] = QPoint(half_width, half_height);                   // Bottom right
    polygon[2] = QPoint(0, -half_height);                           // Top
    polygon[3] = QPoint(-half_width, half_height);                  // Bottom left

    QPainterPath path;
    path.addPolygon(polygon);
    painter.drawPolygon(polygon);
    painter.fillPath(path, Qt::white);
}

void ArrowWidget::mouseReleaseEvent(QMouseEvent*)
{
    emit pressed();
}
