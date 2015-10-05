#include "runtime_widget_a.h"

RuntimeWidgetA::RuntimeWidgetA(QWidget* parent, QSize base_size) : RuntimeWidget(parent, base_size)
{

}

void RuntimeWidgetA::paintEvent(QPaintEvent*)
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

    QRect label_rect(0.025f * width(), 0, 0.775f * width(), h);
    QRect boat_rect(0.8f * width(), 0, 0.2f * width(), h);

    // TODO: Get value, angle and color from configuration / data
    for (int i = 0; i < size; i++)
    {
        QString value_string = "";

        switch (i)
        {
            case 0:
                value_string = "STW " + string(m_stw);
                painter.setPen(QColor(147, 205, 255));
                m_angle = m_stw_angle;
                break;

            case 1:
                value_string = "SOG " + string(m_sog);
                painter.setPen(QColor(144, 255, 112));
                m_angle = m_sog_angle;
                break;

            case 2:
                value_string = "WC " + string(m_wc);
                painter.setPen(QColor(7, 139, 255));
                m_angle = m_wc_angle;
                break;

            case 3:
                value_string = "STW (DL1) " + string(qAbs(m_stw_dl1));
                painter.setPen(QColor(147, 205, 255));
                if (m_stw_dl1 >= 0.0f)
                {
                    m_angle = 0.0f;
                }
                else
                {
                    m_angle = 180.0f;
                }
                break;
        }

        QPoint text_size = textSize(font, value_string);
        QRect gps_rect(label_rect.x() + text_size.x() + 9 * m_width_scale, label_rect.center().y() - 0.5f * m_scale * m_gps_logo_size.height(), m_gps_logo_size.width() * m_scale, m_gps_logo_size.height() * m_scale);

        // Uncomment for component placement
        /*
        painter.fillRect(gps_rect, Qt::red);
        painter.fillRect(label_rect, Qt::green);
        painter.fillRect(boat_rect, Qt::blue);
        */

        // TODO: Load gps image from resource controller
        QImage gps_image(":/gps.png");
        gps_image = gps_image.scaled(gps_rect.size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        //painter.drawImage(gps_rect, gps_image);
        painter.drawText(label_rect, Qt::AlignVCenter, value_string);

        // TODO: Fix up properly
        if (i != 3)
            drawBoat(painter, boat_rect, m_angle);
        else
            drawArrow(painter, boat_rect, m_angle);

        painter.translate(0, h);
    }
}
