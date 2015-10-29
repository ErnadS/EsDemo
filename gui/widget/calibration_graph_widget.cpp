#include "calibration_graph_widget.h"
#include <QPainter>

CalibrationGraphWidget::CalibrationGraphWidget(QWidget* parent, QSize base_size) : ScalableWidget(parent, base_size)
{

}

void CalibrationGraphWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(Qt::yellow);
    QFont font = painter.font();
    font.setPixelSize(25 * m_scale);
    painter.setFont(font);

    painter.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter | Qt::TextWordWrap, "Graph widget");
}


