#include "MultiRuntimeWidget.h"

// TODO: Derive from RuntimeScreen not RuntimeWidget
MultiRuntimeWidget::MultiRuntimeWidget(QWidget* parent, QSize base_size) : ScalableWidget(parent, base_size)
{
    m_quarter_size = QSize(0.5f * base_size.width(), 0.5f * base_size.height());

    m_runtime_1 = new RuntimeWidgetA(this, base_size);
    m_runtime_2 = new RuntimeWidgetB(this, base_size);
    m_runtime_3 = new RuntimeWidgetD(this, base_size);
    m_runtime_4 = new RuntimeWidgetE(this, base_size);
}

void MultiRuntimeWidget::resizeEvent(QResizeEvent* event)
{
    ScalableWidget::resizeEvent(event);

    QSize quarter_size(m_quarter_size.width() * m_width_scale, m_quarter_size.height() * m_height_scale);

    m_runtime_1->resize(quarter_size);
    m_runtime_1->move(0, 0);

    m_runtime_2->resize(quarter_size);
    m_runtime_2->move(quarter_size.width(), 0);

    m_runtime_3->resize(quarter_size);
    m_runtime_3->move(0, quarter_size.height());

    m_runtime_4->resize(quarter_size);
    m_runtime_4->move(quarter_size.width(), quarter_size.height());
}
