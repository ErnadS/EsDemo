#include "background_widget.h"
#include <QPainter>

BackgroundWidget::BackgroundWidget(QColor color, QWidget *parent) :
    QWidget(parent), m_color(color)
{

}

void BackgroundWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.fillRect(QRect(0, 0, width(), height()), m_color);
}
