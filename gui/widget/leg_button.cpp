#include "leg_button.h"
#include <QPainter>

LegButton::LegButton(QWidget* parent, QSize base_size, QString title) : ScalableWidget(parent, base_size), m_title(title)
{

}

void LegButton::setTitle(const QString& title)
{
    m_title = title;
    update();
}

void LegButton::setFontPixelSize(int font_pixel_size)
{
    m_font_pixel_size = font_pixel_size;
    update();
}

void LegButton::setBackgroundColor(const QColor& color)
{
    m_background_color = color;
    update();
}

void LegButton::setBorderColor(const QColor& color)
{
    m_border_color = color;
    update();
}

void LegButton::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QBrush brush(m_background_color, Qt::SolidPattern);

    QFont font = painter.font();
    font.setPixelSize(m_scale * m_font_pixel_size);
    painter.setFont(font);

    QColor color = Qt::black;
    painter.setPen(QPen(color));

    painter.fillRect(0, 0, width(), height(), QBrush(m_border_color, Qt::SolidPattern));
    painter.fillRect(2, 2, width() - 4, height() - 4, brush);

    if (m_highlighted == true)
    {
        painter.fillRect(3, 3, width() - 6, height() - 6, Qt::green);
    }

    painter.drawText(0, 0, width(), height(), Qt::AlignCenter, m_title);
}
