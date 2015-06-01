#include "Dl1RuntimeWidgetB.h"

Dl1RuntimeWidgetB::Dl1RuntimeWidgetB(QWidget* parent, QSize base_size) : RuntimeWidget(parent, base_size)
{

}

void Dl1RuntimeWidgetB::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.fillRect(QRect(0, 0, width(), height()), Qt::cyan);

    painter.setPen(Qt::white);
    QFont font = painter.font();
    font.setPixelSize(60 * m_scale);
    painter.setFont(font);
    painter.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, "DL 1 Runtime Widget B");
}
