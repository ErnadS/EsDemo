#include "SpeedIndicationWidget.h"
#include <QPainter>

SpeedIndicationWidget::SpeedIndicationWidget(QWidget* parent, QSize base_size) : ScalableWidget(parent, base_size)
{

}

SpeedIndicationWidget::SpeedIndicationWidget(QWidget* parent, QSize base_size, QString title) : ScalableWidget(parent, base_size)
{
    m_value = title;
}

void SpeedIndicationWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    m_value = "SOG " + string(m_sog_long) + "/" + string(m_sog_tra) + " STW " + string(m_stw_long) + "/" + string(m_stw_tra);

    QBrush brush(QColor(64, 64, 64));

    QFont font = painter.font();
    font.setPixelSize(18 * m_scale);
    painter.setFont(font);

    // TODO: Load logo image from resource controller
    QRect logo_rect(0, 0, height(), height());
    QImage logo_image(":/skipper-no-background.jpg");
    logo_image = logo_image.scaled(logo_rect.size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    painter.drawImage(logo_rect, logo_image);

    painter.setPen(QPen(m_color));

    QRect label_rect(logo_rect.width(), 0, width() - logo_rect.width(), height());
    painter.fillRect(label_rect, brush);
    painter.drawText(label_rect, Qt::AlignCenter, m_value);
}
