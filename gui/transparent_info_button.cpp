#include "transparent_info_button.h"
#include <QPainter>

TransparentInfoButton::TransparentInfoButton(QWidget* parent, QSize base_size, QString title, QString value) : ScalableWidget(parent, base_size), m_title(title), m_value(value)
{

}

void TransparentInfoButton::setValue(const QString& value)
{
    m_value = value;

    update();
}

void TransparentInfoButton::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(QColor(144, 255, 112));

    QRect title_rect(0, 0, width(), 0.33f * height());
    QRect value_rect(0, title_rect.height(), width(), height() - title_rect.height());

    QFont font = painter.font();
    font.setPixelSize(20 * m_scale);
    painter.setFont(font);

    //painter.fillRect(title_rect, Qt::red);
    painter.drawText(title_rect, Qt::AlignCenter, m_title);

    font.setPixelSize(30 * m_scale);
    painter.setFont(font);

    //painter.fillRect(value_rect, Qt::blue);
    painter.drawText(value_rect, Qt::AlignCenter, m_value);

    QPen pen(Qt::gray);
    int w = 3.0f * m_scale;
    pen.setWidth(w);
    painter.setPen(Qt::gray);

    painter.drawLine(0, 0, width(), 0);
    painter.drawLine(0, height(), width(), height());

    painter.drawLine(0, 0, 0, height());
    painter.drawLine(width(), 0, width(), height());

    QColor background_color(160, 160, 164, 96);
    painter.fillRect(rect(), background_color);
}

void TransparentInfoButton::mouseReleaseEvent(QMouseEvent*)
{
    emit clicked();
}
