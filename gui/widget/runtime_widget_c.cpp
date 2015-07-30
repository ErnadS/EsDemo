#include "runtime_widget_c.h"
#include <QPainter>
#include "utility/utility_math.h"

bool RuntimeWidgetC::m_true_heading_enabled = false;

RuntimeWidgetC::RuntimeWidgetC(QWidget* parent, QSize base_size) : RuntimeWidget(parent, base_size)
{

}

void RuntimeWidgetC::setTrueHeading(bool value)
{
    m_true_heading_enabled = value;
}

void RuntimeWidgetC::drawArrow(QPainter &painter, const QColor &arrowColor, const qreal& speed, const qreal &angle, int radius, int hOffset)
{
    QPen pen(painter.pen());
    QColor colorLine(arrowColor.red(), arrowColor.green(), arrowColor.blue(), 0x20); // set transparent

    pen.setColor(arrowColor);
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(4.0f * m_scale);
    painter.setPen(pen);
    QBrush brush(arrowColor, Qt::SolidPattern);

    int half_width = 7 * m_width_scale;
    int arrow_height = 10 * m_height_scale;
    int arrow_height_offset = 2 * m_height_scale;
    painter.rotate(angle);

    // Line
    qreal alpha = qAbs(speed) / 15.0f;

    if (alpha > 1.0f)
    {
        alpha = 1.0f;
    }

    if (alpha != 0.0f)
    {
        qreal step = 10.0f / radius;

        if (step >= 0.2f)
        {
            step = 0.2f;
        }

        qreal arrow_head_start = radius - arrow_height/2;
        qreal line_end_point = alpha * radius;

        if(line_end_point > arrow_head_start)
        {
            line_end_point = arrow_head_start;
        }

        qreal start_point = 0.0f;
        qreal end_point = 0.0f;
        qreal alpha_i = 0.0f;

        for (; (start_point = alpha_i * radius) <= line_end_point; alpha_i += step)
        {
            end_point = (alpha_i + step / 2.0f) * radius;

            if(end_point > line_end_point)
            {
                end_point = line_end_point;
            }

            painter.drawLine(hOffset, -start_point, hOffset, -end_point);
        }

        if(line_end_point < arrow_head_start)
        {
            for (; (start_point = alpha_i * radius) <= arrow_head_start; alpha_i += step)
            {
                end_point = (alpha_i + step / 2.0f) * radius;

                if (end_point > arrow_head_start)
                {
                    end_point = arrow_head_start;
                }

                pen.setColor(colorLine);
                painter.setPen(pen);
                painter.drawLine(hOffset, -start_point, hOffset, -end_point);
            }
        }
    }

    // Arrow head
    QPolygon polygon(4);

    polygon[0] = QPoint(-half_width + hOffset, -(radius - arrow_height));
    polygon[1] = QPoint(hOffset, -(radius + arrow_height_offset));
    polygon[2] = QPoint(half_width + hOffset, -(radius - arrow_height));
    polygon[3] = QPoint(-half_width + hOffset, -(radius - arrow_height));

    QPainterPath path;
    path.addPolygon(polygon);
    painter.fillPath(path, brush);
    painter.rotate(-angle);

    painter.setPen(QPen(arrowColor));
}

void RuntimeWidgetC::drawCompassLabel(QPainter& painter, int compass_radius, QColor color, qreal angle, QString value)
{
    painter.setPen(color);
    QSize angle_rect_size(m_angle_rect_size.width() * m_width_scale, m_angle_rect_size.height() * m_height_scale);

    int x = 1.125f * compass_radius * qCos(degToRad(angle));
    int y = 1.125f * compass_radius * qSin(degToRad(angle));

    QRect label_rect(QPoint(x - 0.5f * angle_rect_size.width(), y - 0.5f * angle_rect_size.height()), angle_rect_size);
    painter.drawText(label_rect, Qt::AlignCenter, value);
}

void RuntimeWidgetC::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QFont font = painter.font();
    font.setPixelSize(60 * m_scale);
    painter.setFont(font);

    qreal x = 0.1375f * width();

    QImage compass_image = m_true_heading_enabled ? QImage(":/compass_image.png") : QImage(":/no_compass.png");
    QImage vessel_image(":/compass_vessel_image.png");

    QSize compass_size(compass_image.width() * m_scale, compass_image.height() * m_scale);
    QSize normal_size(compass_image.width() * m_width_scale, height());
    QSize vessel_size(vessel_image.width() * m_scale, vessel_image.height() * m_scale);

    int compass_radius = 0.5f * compass_size.width();

    QRect normal_rect(QPoint(x, 0), normal_size);
    QRect compass_rect(QPoint(normal_rect.center().x() - 0.5f * compass_size.width(), normal_rect.center().y() - 0.5f * compass_size.height()), compass_size);

    compass_image = compass_image.scaled(compass_size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    vessel_image = vessel_image.scaled(vessel_size, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    if (m_true_heading_enabled == true)
    {
        painter.save();
        painter.translate(compass_rect.center());
        // TODO: Rotate for true heading
        painter.rotate(-20.0f);
        painter.drawImage(-0.5f * compass_rect.width(), -0.5f * compass_rect.height(), compass_image);
        painter.restore();
    }
    else
    {
        painter.drawImage(compass_rect.topLeft().x(), compass_rect.topLeft().y(), compass_image);
    }

    painter.drawImage(compass_rect.center().x() - 0.5f * vessel_image.width(), compass_rect.center().y() - 0.5f * vessel_image.height(), vessel_image);

    qreal h = height() / 3.0f;
    QRect sog_label_rect(normal_rect.topRight().x() + 0.4f * x, 0, 0.25f * width(), h);
    QRect stw_label_rect(normal_rect.topRight().x() + 0.4f * x, h, 0.25f * width(), h);
    QRect wc_label_rect(normal_rect.topRight().x() + 0.4f * x, 2 * h, 0.25f * width(), h);

    // TODO: Value
    painter.setPen(QColor(144, 255, 112));
    QString sog_label = "SOG\n-.-";
    painter.drawText(sog_label_rect, Qt::AlignCenter, sog_label);

    painter.setPen(QColor(147, 205, 255));
    QString stw_label = "STW\n-.-";
    painter.drawText(stw_label_rect, Qt::AlignCenter, stw_label);

    painter.setPen(QColor(7, 139, 255));
    QString wc_label = "WC\n-.-";
    painter.drawText(wc_label_rect, Qt::AlignCenter, wc_label);

    QImage gps_image(":/gps.png");
    gps_image = gps_image.scaled(QSize(m_gps_logo_size.width() * m_scale, m_gps_logo_size.height() * m_scale), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    qreal gps_x = sog_label_rect.topLeft().x() - m_gps_logo_size.width();
    qreal sog_gps_y = sog_label_rect.center().y() - 0.5f * m_gps_logo_size.height();
    qreal wc_gps_y = wc_label_rect.center().y() - 0.5f * m_gps_logo_size.height();

    QRect sog_gps_rect(gps_x, sog_gps_y, m_gps_logo_size.width() * m_scale, m_gps_logo_size.height() * m_scale);
    QRect wc_gps_rect(gps_x, wc_gps_y, m_gps_logo_size.width() * m_scale, m_gps_logo_size.height() * m_scale);

    painter.drawImage(sog_gps_rect, gps_image);
    painter.drawImage(wc_gps_rect, gps_image);

    // TODO: Values and angles
    // SOG, STW and WC angle arrows
    painter.translate(compass_rect.center());
    drawArrow(painter, QColor(144, 255, 112), 0.0f, 0.0f, 0.5f * compass_rect.width(), 0);
    drawArrow(painter, QColor(147, 205, 255), 0.0f, 0.0f, 0.5f * compass_rect.width(), 0);

    qreal y_offset = 80.0 * m_scale;
    qreal y_arrow = y_offset / 3.0f;

    // TODO: Wc angle
    painter.save();
    painter.rotate(20.0f);
    painter.translate(0, -y_offset + y_arrow);
    drawArrow(painter, QColor(7, 139, 255), 15.0f, 0, y_arrow, 0);

    painter.restore();
    painter.save();
    painter.rotate(20.0f);
    painter.translate(0, y_offset);
    drawArrow(painter, QColor(7, 139, 255), 25.0f, 0, y_arrow, 0);

    // WC, SOG and GPS angle labels
    painter.restore();
    painter.setPen(QColor(7, 139, 255));
    font.setPixelSize(15 * m_scale);
    painter.setFont(font);

    // TODO: Fix
    qreal m_wc_angle = 0.0f;
    qreal m_sog_angle = 0.0f;
    qreal m_stw_angle = 0.0f;
    qreal m_true_heading = 20.0f;

    int label_delta_angle = (m_sog_angle - m_stw_angle < 3) ? 10 : - 10;

    if (m_true_heading_enabled == true)
    {
        drawCompassLabel(painter, 1.175f * y_offset, QColor(7, 139, 255), m_wc_angle - 90.0f, QString::number(normalizeDegPositive(m_wc_angle + m_true_heading), 'f', 1) + QString::fromUtf8("°"));
        drawCompassLabel(painter, compass_radius, QColor(144, 255, 112), m_sog_angle - 90.0f - label_delta_angle, QString::number(normalizeDegPositive(m_sog_angle + m_true_heading), 'f', 1) + QString::fromUtf8("°"));
        drawCompassLabel(painter, compass_radius, QColor(147, 205, 255), m_stw_angle - 90.0f + label_delta_angle, QString::number(normalizeDegPositive(m_stw_angle + m_true_heading), 'f', 1) + QString::fromUtf8("°"));
    }
    else
    {
        drawCompassLabel(painter, 1.175f * y_offset, QColor(7, 139, 255), m_wc_angle - 90.0f, QString::number(normalizeDegPositive(m_wc_angle), 'f', 1) + QString::fromUtf8("°"));
        drawCompassLabel(painter, compass_radius, QColor(144, 255, 112), m_sog_angle - 90.0f - label_delta_angle, QString::number(normalizeDegPositive(m_sog_angle), 'f', 1) + QString::fromUtf8("°"));
        drawCompassLabel(painter, compass_radius, QColor(147, 205, 255), m_stw_angle - 90.0f + label_delta_angle, QString::number(normalizeDegPositive(m_stw_angle), 'f', 1) + QString::fromUtf8("°"));
    }
}
