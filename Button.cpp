#include "Button.h"
#include <QPainter>

Button::Button(QWidget* parent, QSize base_size, QString title, bool frame_on) : ScalableWidget(parent, base_size), m_frame_on(frame_on), m_title(title)
{

}

void Button::setTitle(const QString& title)
{
    m_title = title;
}

void Button::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    int shown_height = 0.66f * baseSize().height() * m_height_scale;

    QBrush brush(QColor(125, 125, 125, 40));

    QFont font = painter.font();
    font.setPixelSize(m_font_pixel_size * m_scale);
    painter.setFont(font);

    painter.setPen(QColor(144, 255, 112));

    if (m_frame_on == true)
    {
        painter.fillRect(0, 0, width(), shown_height, brush);
    }

    painter.drawText(0, 0, width(), shown_height, Qt::AlignCenter, m_title);

    if (m_frame_on == true)
    {
        painter.setPen(QPen(borderColor, 4 * m_scale));
        painter.drawRect(0, 0, width() - 2 * m_width_scale, shown_height - 2 * m_height_scale);

        painter.setPen(QPen(QColor(220, 220, 220, 40), 2 * m_scale));
        painter.drawRect(4 * m_width_scale, 4 * m_height_scale, width() - 8 * m_width_scale, shown_height - 8 * m_height_scale);
    }
}

void Button::mousePressEvent(QMouseEvent*)
{
    borderColor = QColor(0x88, 0x88, 0xFF);
    repaint();
}

void Button::mouseReleaseEvent(QMouseEvent*)
{
    borderColor = QColor(220, 220, 220, 40);
    emit clicked();
}
