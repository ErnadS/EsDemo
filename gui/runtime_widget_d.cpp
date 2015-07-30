#include "runtime_widget_d.h"
#include <QPainter>

RuntimeWidgetD::RuntimeWidgetD(QWidget* parent, QSize base_size) : RuntimeWidget(parent, base_size)
{

}

void RuntimeWidgetD::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QFont font = painter.font();
    font.setPixelSize(60 * m_scale);
    painter.setFont(font);

    // Arrow rect declaration
    QSize arrow_rect_size(m_arrow_rect_size.width() * m_width_scale, m_arrow_rect_size.height() * m_height_scale);

    QRect top_arrow_rect(QPoint(rect().center().x() - 0.5f * arrow_rect_size.width(), 0.25f * height()), arrow_rect_size);
    QRect bottom_arrow_rect(QPoint(rect().center().x() - 0.5f * arrow_rect_size.width(), 0.65f * height()), arrow_rect_size);
    QRect top_left_arrow_rect(QPoint(rect().center().x() - 0.115f * width() - arrow_rect_size.width(), rect().center().y() - 0.4125f * height()), arrow_rect_size);
    QRect top_right_arrow_rect(QPoint(rect().center().x() + 0.115f * width(), rect().center().y() - 0.4125f * height()), arrow_rect_size);
    QRect bottom_left_arrow_rect(QPoint(rect().center().x() - 0.115f * width() - arrow_rect_size.width(), rect().center().y() + 0.2825f * height()), arrow_rect_size);
    QRect bottom_right_arrow_rect(QPoint(rect().center().x() + 0.115f * width(), rect().center().y() + 0.2825f * height()), arrow_rect_size);

    // Label rect declaration
    QSize label_rect_size(m_label_rect_size.width() * m_width_scale, m_label_rect_size.height() * m_height_scale);

    QRect center_label_rect(QPoint(rect().center().x() - 0.5f * label_rect_size.width(), rect().center().y() - 0.35f * label_rect_size.height()), label_rect_size);
    qreal top_left_x = top_left_arrow_rect.topLeft().x() - label_rect_size.width();
    QRect top_left_label_rect(QPoint(top_left_x, top_left_arrow_rect.topLeft().y()), label_rect_size);
    QRect top_right_label_rect(top_right_arrow_rect.topRight(), label_rect_size);
    QRect bottom_left_label_rect(QPoint(top_left_x, bottom_left_arrow_rect.topLeft().y()), label_rect_size);
    QRect bottom_right_label_rect(bottom_right_arrow_rect.topRight(), label_rect_size);

    drawBoat(painter, rect());

    /*
    painter.fillRect(top_arrow_rect, Qt::black);
    painter.fillRect(bottom_arrow_rect, Qt::black);
    painter.fillRect(top_left_arrow_rect, Qt::black);
    painter.fillRect(top_right_arrow_rect, Qt::black);
    painter.fillRect(bottom_left_arrow_rect, Qt::black);
    painter.fillRect(bottom_right_arrow_rect, Qt::black);

    painter.fillRect(center_label_rect, Qt::blue);
    painter.fillRect(top_left_label_rect, Qt::blue);
    painter.fillRect(top_right_label_rect, Qt::blue);
    painter.fillRect(bottom_left_label_rect, Qt::blue);
    painter.fillRect(bottom_right_label_rect, Qt::blue);
    */

    QColor sog_color(144, 255, 112);

    /*
    drawArrow(painter, sog_color, top_arrow_rect, 0.0f, true);
    drawArrow(painter, sog_color, bottom_arrow_rect, 180.0f, true);
    drawArrow(painter, sog_color, top_left_arrow_rect, -90.0f, true);
    drawArrow(painter, sog_color, top_right_arrow_rect, 90.0f, false);
    drawArrow(painter, sog_color, bottom_left_arrow_rect, -90.0f, false);
    drawArrow(painter, sog_color, bottom_right_arrow_rect, 90.0f, false);

    painter.drawText(center_label_rect, Qt::AlignCenter, "13.82");
    painter.drawText(top_left_label_rect, Qt::AlignVCenter | Qt::AlignRight, "13.82");
    painter.drawText(top_right_label_rect, Qt::AlignVCenter | Qt::AlignLeft, "13.82");
    painter.drawText(bottom_left_label_rect, Qt::AlignVCenter | Qt::AlignRight, "13.82");
    painter.drawText(bottom_right_label_rect, Qt::AlignVCenter | Qt::AlignLeft, "13.82");
    */

    // TODO: Refactor:
    qreal m_sog_long = 20.0f;
    qreal m_sog_tra = 20.0f;
    qreal m_sog_tra_aft = 20.0f;

    painter.setPen(sog_color);
    QString sog_label = QString::number(qAbs(m_sog_long), 'f', 1);
    painter.drawText(center_label_rect, Qt::AlignCenter, sog_label);

    if (m_sog_long >= 0.0f)
    {
        drawArrow(painter, sog_color, top_arrow_rect, 0.0f, true);
        drawArrow(painter, sog_color, bottom_arrow_rect, 180.0f, false);
    }
    else
    {
        drawArrow(painter, sog_color, top_arrow_rect, 0.0f, false);
        drawArrow(painter, sog_color, bottom_arrow_rect, 180.0f, true);
    }

    QString sog_tra_label = QString::number(qAbs(m_sog_tra), 'f', 1);

    if (m_sog_tra >= 0.0f)
    {
        drawArrow(painter, sog_color, top_right_arrow_rect, 90.0f, true);
        drawArrow(painter, sog_color, top_left_arrow_rect, -90.0f, false);

        painter.drawText(top_right_label_rect, Qt::AlignVCenter | Qt::AlignLeft, sog_tra_label);
    }
    else
    {
        drawArrow(painter, sog_color, top_right_arrow_rect, 90.0f, false);
        drawArrow(painter, sog_color, top_left_arrow_rect, -90.0f, true);

        painter.drawText(top_left_label_rect, Qt::AlignVCenter | Qt::AlignRight, sog_tra_label);
    }

    QString sog_tra_aft_label = QString::number(qAbs(m_sog_tra_aft), 'f', 1);

    if (m_sog_tra_aft >= 0.0f)
    {
        drawArrow(painter, sog_color, bottom_right_arrow_rect, 90.0f, true);
        drawArrow(painter, sog_color, bottom_left_arrow_rect, -90.0f, false);

        painter.drawText(bottom_right_label_rect, Qt::AlignVCenter | Qt::AlignLeft, sog_tra_aft_label);
    }
    else
    {
        drawArrow(painter, sog_color, bottom_right_arrow_rect, 90.0f, false);
        drawArrow(painter, sog_color, bottom_left_arrow_rect, -90.0f, true);

        painter.drawText(bottom_left_label_rect, Qt::AlignVCenter | Qt::AlignRight, sog_tra_aft_label);
    }

    //QSize gps_logo_size(m_gps_logo_size.width() * m_scale, m_gps_logo_size.height() * m_scale);
    //QRect center_gps_rect(QPoint(center_label_rect.topRight().x() + 9 * m_width_scale, center_label_rect.center().y() - 0.5f * m_scale * m_gps_logo_size.height()), gps_logo_size);

    //QPoint text_size = textSize(font, "13.82");
    /*
    QRect top_left_gps_rect(QPoint(top_left_label_rect.topRight().x() - text_size.x() - 9 * m_width_scale - gps_logo_size.width(), top_left_label_rect.center().y() - 0.5f * gps_logo_size.height()), gps_logo_size);
    QRect top_right_gps_rect(QPoint(top_right_label_rect.x() + text_size.x() + 9 * m_width_scale, top_right_label_rect.center().y() - 0.5f * gps_logo_size.height()), gps_logo_size);
    QRect bottom_left_gps_rect(QPoint(bottom_left_label_rect.topRight().x() - text_size.x() - 9 * m_width_scale - gps_logo_size.width(), bottom_left_label_rect.center().y() - 0.5f * gps_logo_size.height()), gps_logo_size);
    QRect bottom_right_gps_rect(QPoint(bottom_right_label_rect.x() + text_size.x() + 9 * m_width_scale, bottom_right_label_rect.center().y() - 0.5f * gps_logo_size.height()), gps_logo_size);
    */

    /*
    QRect top_left_gps_rect(QPoint(top_left_label_rect.topRight().x() - text_size.x() - gps_logo_size.width(), top_left_label_rect.center().y() - 0.5f * gps_logo_size.height()), gps_logo_size);
    QRect top_right_gps_rect(QPoint(top_right_label_rect.x() + text_size.x(), top_right_label_rect.center().y() - 0.5f * gps_logo_size.height()), gps_logo_size);
    QRect bottom_left_gps_rect(QPoint(bottom_left_label_rect.topRight().x() - text_size.x() - gps_logo_size.width(), bottom_left_label_rect.center().y() - 0.5f * gps_logo_size.height()), gps_logo_size);
    QRect bottom_right_gps_rect(QPoint(bottom_right_label_rect.x() + text_size.x(), bottom_right_label_rect.center().y() - 0.5f * gps_logo_size.height()), gps_logo_size);

    QImage gps_image(":/gps.png");
    gps_image = gps_image.scaled(center_gps_rect.size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    painter.drawImage(center_gps_rect, gps_image);
    painter.drawImage(top_left_gps_rect, gps_image);
    painter.drawImage(top_right_gps_rect, gps_image);
    painter.drawImage(bottom_left_gps_rect, gps_image);
    painter.drawImage(bottom_right_gps_rect, gps_image);
    */
}

void RuntimeWidgetD::drawBoat(QPainter& painter, const QRect rect)
{
    QColor color = QColor(64, 64, 64);
    QBrush brush(color, Qt::SolidPattern);

    QPolygon polygon(6);

    int half_width = 58 * m_width_scale;
    int half_height = 117 * m_height_scale;
    int top_height = 88 * m_height_scale;
    polygon[0] = QPoint(-half_width, -half_height);         // Top Left
    polygon[1] = QPoint(0, -(half_height + top_height));    // Top
    polygon[2] = QPoint(half_width, -half_height);          // Top Right
    polygon[3] = QPoint(half_width, half_height);           // Bottom Right
    polygon[4] = QPoint(-half_width, half_height);          // Bottom Left
    polygon[5] = QPoint(-half_width, -half_height);         // Top Left
    polygon.translate(0, 0.5f * top_height);

    QPainterPath path;
    path.addPolygon(polygon);

    painter.save();
    painter.translate(rect.center().x(), rect.center().y());
    painter.fillPath(path, brush);
    painter.restore();
}

void RuntimeWidgetD::drawArrow(QPainter& painter, const QColor color, const QRect rect, qreal angle, bool fill)
{    
    QPen pen(painter.pen());
    pen.setColor(color);

    /* TODO: Keep only solid line?
    if (fill == true)
    {
        pen.setStyle(Qt::SolidLine);
    }
    else
    {
        pen.setStyle(Qt::DashLine);
    }
    */

    pen.setStyle(Qt::SolidLine);

    painter.setPen(pen);
    QBrush brush(color, Qt::SolidPattern);

    int half_width = 11 * m_width_scale;
    int half_height = 17 * m_height_scale;
    int top_height = 22 * m_height_scale;
    int top_width = 11 * m_width_scale;

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

    painter.save();
    painter.translate(rect.center());
    painter.rotate(angle);
    painter.drawPolygon(polygon);

    if (fill == true)
    {
        painter.fillPath(path, brush);
    }

    painter.restore();
}
