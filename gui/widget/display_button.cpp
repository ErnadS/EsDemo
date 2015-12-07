#include "display_button.h"
#include <QPainter>

DisplayButton::DisplayButton(QWidget *parent, QSize base_size) : ScalableWidget(parent, base_size)
{

}

void DisplayButton::setSelected(bool selected)
{
    m_selected = selected;
    update();
}

bool DisplayButton::isSelected() const
{
    return m_selected;
}

void DisplayButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    m_outter_body_color = QColor(50, 50, 50); //dark gray
    m_border_color = QColor(200, 200, 200);
    if (m_selected)
    {
        m_body_color = QColor(221, 255, 141); //light yellow
    }
    else
    {
        m_body_color = QColor(140, 140, 140); //light gray
    }

    QSize button_size(baseSize().width() * m_width_scale, baseSize().height() * m_height_scale);

    QRect outter_rect(QPoint(0, 0), button_size);
    QRect inner_rect(QPoint(0, 0), button_size * 0.85);
    inner_rect.moveCenter(outter_rect.center());

    painter.fillRect(outter_rect, m_outter_body_color);
    painter.fillRect(inner_rect, m_body_color);
    painter.setPen(QPen(m_border_color, 3));
    painter.drawRect(outter_rect);

    QFont font(painter.font());
    font.setPixelSize(m_font_pixel_size * m_scale);
    painter.setFont(font);
    painter.setPen(QPen(Qt::black, 2));
    painter.drawText(inner_rect, Qt::AlignCenter, m_title);
}

void DisplayButton::mouseReleaseEvent(QMouseEvent *)
{
    emit clicked();
//    m_selected = true;
//    update();
}

void DisplayButton::resizeEvent(QResizeEvent *)
{
    ScalableWidget::resizeEvent(nullptr);
    update();
}

void DisplayButton::changeSelected()
{
    m_selected = !m_selected;
    update();
}

