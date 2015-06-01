#include "RuntimeWidgetE.h"

LifoBuffer<DepthMeasurement> RuntimeWidgetE::m_buffer{600};

RuntimeWidgetE::RuntimeWidgetE(QWidget* parent, QSize base_size) : RuntimeWidget(parent, base_size)
{

}

void RuntimeWidgetE::addMeasurement(qreal front_depth, qreal side_depth)
{
    DepthMeasurement measurement;
    measurement.time = 1000;
    measurement.speed = 2.5f;
    measurement.front_depth = front_depth;
    measurement.side_depth = side_depth;

    m_buffer.append(measurement);
}

void RuntimeWidgetE::drawBoat(QPainter& painter, const QRect rect)
{
    QColor color = QColor(64, 64, 64);
    QBrush brush(color, Qt::SolidPattern);

    int half_width = 53 * m_width_scale;
    int half_height = 86 * m_height_scale;
    int top_height = 59 * m_height_scale;

    QPolygon polygon(6);
    polygon[0] = QPoint(-half_width, -half_height);         // Top Left
    polygon[1] = QPoint(0, -(half_height + top_height));    // Top
    polygon[2] = QPoint(half_width, -half_height);          // Top Right
    polygon[3] = QPoint(half_width, half_height);           // Bottom Right
    polygon[4] = QPoint(-half_width, half_height);          // Bottom Left
    polygon[5] = QPoint(-half_width, -half_height);         // Top Left

    painter.save();
    painter.translate(0, 0.5f * top_height);

    QPainterPath path;
    path.addPolygon(polygon);

    painter.translate(rect.center().x(), rect.center().y());
    painter.fillPath(path, brush);

    painter.translate(0, -half_height - 0.5f * top_height);

    QColor orange(255, 192, 0);
    QPen pen = painter.pen();
    pen.setColor(orange);
    pen.setWidth(2 * m_scale);
    painter.setPen(pen);

    qreal rho = 1.75f;
    painter.drawLine(0, 0, 0.5f * rho * half_width, 0);
    painter.drawLine(0, 0, 0, -0.5f * rho * top_height);

    pen.setColor(Qt::black);
    painter.setPen(pen);
    brush = QBrush(orange, Qt::SolidPattern);
    painter.setBrush(brush);
    qreal radius = 3.0f * m_scale;
    painter.drawEllipse(QPointF(0, 0), radius, radius);

    brush = QBrush(Qt::white, Qt::SolidPattern);
    painter.setBrush(brush);
    qreal phi = 1.25f;
    painter.drawEllipse(QPointF(0, -0.5f * rho * top_height), phi * radius, phi * radius);
    painter.drawEllipse(QPointF(0.5f * rho * half_width, 0), phi * radius, phi * radius);

    int wv = 60 * m_width_scale;
    int hv = 30 * m_height_scale;

    QRect front_rect(-0.5f * wv, -0.5f * rho * top_height - hv - 5 * m_height_scale, wv, hv);
    QRect side_rect(0.5f * rho * half_width + 3 * m_width_scale, -0.5f * hv, wv, hv);

    QFont font = painter.font();
    font.setPixelSize(24.0f * m_scale);
    painter.setFont(font);
    painter.setPen(m_color);

    //painter.fillRect(front_rect, Qt::blue);
    //painter.fillRect(side_rect, Qt::blue);
    painter.drawText(front_rect, Qt::AlignCenter, string(m_front_depth));
    painter.drawText(side_rect, Qt::AlignCenter, string(m_side_depth));

    painter.restore();
}

void RuntimeWidgetE::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QRect boat_rect(0.6f * width(), 0, 0.35f * width(), 0.8f * height());
    //painter.fillRect(boat_rect, Qt::red);
    drawBoat(painter, boat_rect);

    QImage vessel_image(":/vessel_4.png");
    QSize vessel_size(vessel_image.width() * m_width_scale, vessel_image.height() * m_height_scale);
    vessel_image = vessel_image.scaled(vessel_size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    qreal vessel_pos = 210 * m_width_scale;

    painter.save();
    painter.translate(0.05 * width(), 0.18125 * height());
    painter.drawImage(QPoint(vessel_pos - vessel_image.width(), -vessel_image.height()), vessel_image);

    int m_pixmap_dimension = 300;
    qreal m_max_depth = 150.0f;

    QImage image(m_pixmap_dimension, m_pixmap_dimension, QImage::Format_RGB32);
    image.fill(Qt::black);

    QPixmap pixmap = QPixmap::fromImage(image);
    QPainter p(&pixmap);

    qreal start_index = 210.0f;
    qreal tan = 0.57735f;
    qreal sum = 0.0f;

    QColor front_depth_color = Qt::red;
    QColor side_depth_color = Qt::cyan;

    qreal prev_time = 0.0f;

    for (auto it = m_buffer.begin(); it != m_buffer.end(); it++)
    {
        qreal front_depth = it->front_depth;
        qreal side_depth = it->side_depth;

        int front_index = start_index + tan * front_depth - sum;
        int side_index = start_index - sum;

        // The relationship between units is linear and therefore
        // the height can be calculated in whichever unit without
        // modifying the result

        if ((front_index >= 0) && (front_index < m_pixmap_dimension))
        {
            int y_average = m_pixmap_dimension / m_max_depth * front_depth;

            p.setPen(front_depth_color);
            p.setBrush(front_depth_color);
            p.drawEllipse(QPoint(front_index, y_average), 2, 2);
        }
        else
        {
            break;
        }

        if ((side_index >= 0) && (side_index < m_pixmap_dimension))
        {
            int y_average = m_pixmap_dimension / m_max_depth * side_depth;

            p.setPen(side_depth_color);
            p.setBrush(side_depth_color);
            p.drawEllipse(QPoint(side_index, y_average), 2, 2);
        }

        // Integrating
        qint64 time_diff_ms = it->time - prev_time;
        float speed = 0.514f * it->speed;
        qreal time_diff = time_diff_ms / 1000.0f;
        sum += speed * time_diff;
    }

    painter.fillRect(QRect(-1, -1, m_pixmap_dimension * m_width_scale + 2, m_pixmap_dimension * m_height_scale + 2), Qt::gray);
    QPixmap drawing_pixmap = pixmap.scaled(pixmap.width() * m_width_scale, pixmap.height() * m_height_scale, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(QPoint(0, 0), drawing_pixmap);
    painter.restore();

    QSize label_rect_size(width(), 0.115f * height());
    QRect label_rect(QPoint(0, height() - label_rect_size.height()), label_rect_size);
    //painter.fillRect(label_rect, Qt::blue);

    QFont font = painter.font();
    font.setPixelSize(40 * m_scale);
    painter.setFont(font);
    painter.setPen(m_color);

    painter.drawText(label_rect, Qt::AlignCenter, "Avg depth below sensor " + string(m_avg_depth));
}


