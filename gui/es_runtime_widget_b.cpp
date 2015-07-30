#include "es_runtime_widget_b.h"

EsRuntimeWidgetB::EsRuntimeWidgetB(QWidget *parent, QSize base_size) : RuntimeWidget(parent, base_size)
{

}

void EsRuntimeWidgetB::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.fillRect(QRect(0, 0, width(), height()), Qt::magenta);

    painter.setPen(Qt::white);
    QFont font = painter.font();
    font.setPixelSize(60 * m_scale);
    painter.setFont(font);
    painter.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, "ES Runtime Widget B");
}
