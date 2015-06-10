#include "RuntimeWidgetB.h"
#include <QPainter>

RuntimeWidgetB::RuntimeWidgetB(QWidget* parent, QSize base_size) : RuntimeWidget(parent, base_size)
{

}

void RuntimeWidgetB::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QFont font = painter.font();
    font.setPixelSize(60 * m_scale);
    painter.setFont(font);

    // TODO: Count from configuration sources
    const int size = 4;
    qreal h = qreal(height()) / size;

    QRect boat_rect(0, 0, 0.2f * width(), h);
    QRect label_rect(0.2f * width(), 0, 0.8f * width(), h);

    // TODO: Get value, angle and color from configuration / data
    for (int i = 0; i < size; i++)
    {
        QString value_string = "";

        switch (i)
        {
            case 0:
                value_string = "SOG-L -.-";
                painter.setPen(QColor(144, 255, 112));
                break;

            case 1:
                value_string = "SOG-T -.-";
                painter.setPen(QColor(144, 255, 112));
                break;

            case 2:
                value_string = "SOG -.-";
                painter.setPen(QColor(144, 255, 112));
                break;

            case 3:
                value_string = "WC -.-";
                painter.setPen(QColor(147, 205, 255));
                break;
        }

        QPoint text_size = textSize(font, value_string);
        QRect gps_rect(label_rect.x() + text_size.x() + 9 * m_width_scale, label_rect.center().y() - 0.5f * m_scale * m_gps_logo_size.height(), m_gps_logo_size.width() * m_scale, m_gps_logo_size.height() * m_scale);

        // Uncomment for component placement
        /*
        painter.fillRect(gps_rect, Qt::red);
        painter.fillRect(boat_rect, Qt::blue);
        painter.fillRect(label_rect, Qt::green);
        */

        // TODO: Load gps image from resource controller
        QImage gps_image(":/gps.png");
        gps_image = gps_image.scaled(gps_rect.size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        //painter.drawImage(gps_rect, gps_image);

        painter.drawText(label_rect, Qt::AlignVCenter, value_string);

        // TODO: Fix up properly
        if ((i == 2) || (i == 3))
            drawBoat(painter, boat_rect, m_angle);
        else
            drawArrow(painter, boat_rect, m_angle);

        painter.translate(0, h);
    }
}
