#include "RuntimeWidgetC.h"
#include <QPainter>

RuntimeWidgetC::RuntimeWidgetC(QWidget* parent, QSize base_size) : ScalableWidget(parent, base_size)
{

}

void RuntimeWidgetC::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.fillRect(QRect(0, 0, width(), height()), Qt::blue);

    painter.setPen(Qt::white);
    QFont font = painter.font();
    font.setPixelSize(60 * m_scale);
    painter.setFont(font);
    painter.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, "DL 2 Runtime Widget C");
}
