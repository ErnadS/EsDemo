#include "runtime_widget_dl1.h"

RuntimeWidgetDl1::RuntimeWidgetDl1(QWidget* parent, QSize base_size) : RuntimeWidget(parent, base_size)
{
    QPalette palette(RuntimeWidgetDl1::palette());
    palette.setColor(QPalette::Background, Qt::blue);
    setAutoFillBackground(true);
    setPalette(palette);
}

void RuntimeWidgetDl1::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QRect arrow_rect(0, 0.375f * height(), 0.2f * width(), 0.25f * height());
    QRect label_rect(0.2f * width(), 0.25f * height(), width() - arrow_rect.width(), 0.5f * height());

    // Uncomment for component placement
    /*
    painter.fillRect(arrow_rect, Qt::red);
    painter.fillRect(label_rect, Qt::green);
    */

    painter.setPen(QColor(147, 205, 255));
    QFont font = painter.font();
    font.setPixelSize(60 * m_scale);
    painter.setFont(font);

    if (m_stw_dl1 >= 0.0f)
    {
        drawArrow(painter, arrow_rect, 0);
    }
    else
    {
        drawArrow(painter, arrow_rect, 180);
    }

    QString label = string(qAbs(m_stw_dl1)) + "\nSTW";
    painter.drawText(label_rect, Qt::AlignVCenter, label);
}
