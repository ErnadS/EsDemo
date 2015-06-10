#include "ScalableWidget.h"
#include "RuntimeWidgetE.h"

void ScalableWidget::updateScale()
{
    m_width_scale = qreal(width()) / baseSize().width();
    m_height_scale = qreal(height()) / baseSize().height();

    m_scale = (m_width_scale < m_height_scale) ? m_width_scale : m_height_scale;
}

void ScalableWidget::resizeEvent(QResizeEvent*)
{
    updateScale();
}

ScalableWidget::ScalableWidget(QWidget* parent, QSize base_size) :
    QWidget(parent)
{
    setBaseSize(base_size);
    resize(base_size);
}
