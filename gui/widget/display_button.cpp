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

    if (m_selected)
    {
        QPixmap pixmap = QPixmap(":/display_selected.png");
        painter.drawPixmap(QRect(0, 0, width(), height()), pixmap);
    }
    else
    {
        QPixmap pixmap = QPixmap(":/display_not_selected.png");
        painter.drawPixmap(QRect(0, 0, width(), height()), pixmap);
    }

    QFont font(painter.font());
    font.setPixelSize(m_font_pixel_size * m_scale);
    painter.setFont(font);
    painter.setPen(QPen(Qt::white, 2));
    painter.drawText(0, 0, width(), height(), Qt::AlignCenter, m_title);

//    QRect outter_rect(0, 0, width(), height());

//    painter.setPen(QPen(Qt::white, 1));
//    painter.drawRect(outter_rect);
}

void DisplayButton::mouseReleaseEvent(QMouseEvent *)
{
    emit clicked();
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

