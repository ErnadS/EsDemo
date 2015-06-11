#include "BoatButton.h"
#include <QPainter>

BoatButton::BoatButton(QWidget* parent, QSize base_size) : ScalableWidget(parent, base_size)
{

}

void BoatButton::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(Qt::white);

    QFont font = painter.font();
    font.setPixelSize(16.0f * m_scale);
    painter.setFont(font);

    painter.drawText(rect(), Qt::AlignCenter, "Boat");
}

void BoatButton::mouseReleaseEvent(QMouseEvent*)
{
    emit clicked();
}
