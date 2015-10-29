#include "runtime_widget_e.h"

LifoBuffer<DepthMeasurement> RuntimeWidgetE::m_buffer{300};
int RuntimeWidgetE::m_vessel_index{1};
qreal RuntimeWidgetE::len{0.2f};

RuntimeWidgetE::RuntimeWidgetE(QWidget* parent, QSize base_size, bool is_multi) : RuntimeWidget(parent, base_size), m_is_multi(is_multi)
{
    if (is_multi == true)
    {
        setAttribute(Qt::WA_TransparentForMouseEvents);
    }

    m_vessel_index = 1;
}

void RuntimeWidgetE::addMeasurement(qreal time, qreal speed, qreal front_depth, qreal side_depth)
{
    DepthMeasurement measurement;
    measurement.time = time;
    measurement.speed = speed;
    measurement.front_depth = front_depth;
    measurement.side_depth = side_depth;

    m_buffer.append(measurement);

}

int RuntimeWidgetE::vesselIndex()
{
    return m_vessel_index;
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
    painter.setPen(QColor(144, 255, 112));

    //painter.fillRect(front_rect, Qt::blue);
    //painter.fillRect(side_rect, Qt::blue);
    painter.drawText(front_rect, Qt::AlignCenter, QString::number(m_front_depth, 'f', 1));
    painter.drawText(side_rect, Qt::AlignCenter, QString::number(m_side_depth, 'f', 1));

    painter.restore();
}

void RuntimeWidgetE::mouseReleaseEvent(QMouseEvent*)
{
    m_vessel_index = (m_vessel_index + 1) % 5 + 1;

    update();

    parentWidget()->update();
}

void RuntimeWidgetE::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QRect boat_rect(0.6f * width(), 0, 0.35f * width(), 0.8f * height());
    //painter.fillRect(boat_rect, Qt::red);
    drawBoat(painter, boat_rect);

    QImage vessel_image(":/vessel_" + QString::number(m_vessel_index) + ".png");
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
    //qreal len=0.2f;  //ukupna širina grafika u miljama
    qreal speed = m_buffer.begin()->speed;   //brzina u kn
    qreal time_diff = (m_buffer.begin()->time - ((m_buffer.begin())++)->time)/3600; //razlika u vremenu izmedju dva najnovija mjerenja u h
    qreal sum = speed*time_diff*m_pixmap_dimension/len; //odgovarajuci pomak na grafiku

    QColor front_depth_color = Qt::red;
    QColor side_depth_color = Qt::cyan;

    qreal dist = 0.0f;
    qreal prev_time = 0.0f;
    qreal prev_speed = 0.0f;
    int prev_f_i=0;
    int prev_s_i=0;
    int prev_y_f=0;
    int prev_y_s=0;

    for (auto it = m_buffer.begin(); it != m_buffer.end(); it++)
    {
        qreal front_depth = it->front_depth;
        qreal side_depth = it->side_depth;


        //dodano:
        if (it != m_buffer.begin())
        {
            dist += ((it->speed + prev_speed)/2.0f * (prev_time - it->time)/3600)*m_pixmap_dimension/len; //pomak u odnosu na noviju tacku

        }

        int front_index = start_index + tan * front_depth - sum - dist;
        int side_index = start_index - sum - dist;


        // The relationship between units is linear and therefore
        // the height can be calculated in whichever unit without
        // modifying the result

        if ((front_index >= 0) && (front_index < m_pixmap_dimension))
        {
            int y_average = m_pixmap_dimension / m_max_depth * front_depth;

            p.setPen(front_depth_color);
            p.setBrush(front_depth_color);
            p.drawEllipse(QPoint(front_index, y_average), 2, 2);

            if (it != m_buffer.begin()) {
                p.drawLine(QPoint(front_index, y_average), QPoint(prev_f_i, prev_y_f));
            }
            prev_y_f=y_average;

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

            if (it != m_buffer.begin()) {
                p.drawLine(QPoint(side_index, y_average), QPoint(prev_s_i, prev_y_s));
            }
            prev_y_s=y_average;
        }

        prev_speed = it->speed;
        prev_time = it->time;

        prev_f_i=front_index;
        prev_s_i=side_index;

        // Integrating
        //qint64 time_diff_ms = it->time - prev_time;
        //float speed = 0.514f * it->speed;
        //qreal time_diff = time_diff_ms / 1000.0f;
        //sum += speed * time_diff;



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
    painter.setPen(QColor(144, 255, 112));

    painter.drawText(label_rect, Qt::AlignCenter, "Avg depth below sensor " + QString::number(m_avg_depth, 'f', 1));
}


