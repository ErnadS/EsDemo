#include "MultiRuntimeWidget.h"
#include <QMouseEvent>
#include <QDebug>
#include "BackgroundWidget.h"

// TODO: Derive from RuntimeScreen not RuntimeWidget
QStackedLayout* MultiRuntimeWidget::createLayout(QWidget* parent)
{
    QStackedLayout* layout = new QStackedLayout(this);

    RuntimeWidgetA* runtime_widget_a = new RuntimeWidgetA(parent, parent->size());
    RuntimeWidgetB* runtime_widget_b = new RuntimeWidgetB(parent, parent->size());
    RuntimeWidgetC* runtime_widget_c = new RuntimeWidgetC(parent, parent->size());
    RuntimeWidgetD* runtime_widget_d = new RuntimeWidgetD(parent, parent->size());
    RuntimeWidgetE* runtime_widget_e = new RuntimeWidgetE(parent, parent->size(), true);

    layout->addWidget(runtime_widget_a);
    layout->addWidget(runtime_widget_b);
    layout->addWidget(runtime_widget_c);
    layout->addWidget(runtime_widget_d);
    layout->addWidget(runtime_widget_e);

    parent->setLayout(layout);

    return layout;
}

MultiRuntimeWidget::MultiRuntimeWidget(QWidget* parent, QSize base_size) : ScalableWidget(parent, base_size)
{
    m_quarter_size = QSize(0.5f * base_size.width(), 0.5f * base_size.height());

    // A, B, D, E

    m_runtime_1 = new QWidget(this);
    m_runtime_1->resize(base_size);
    m_runtime_1_layout = createLayout(m_runtime_1);
    m_runtime_1_layout->setCurrentIndex(0);

    m_runtime_2 = new QWidget(this);
    m_runtime_2->resize(base_size);
    m_runtime_2_layout = createLayout(m_runtime_2);
    m_runtime_2_layout->setCurrentIndex(1);

    m_runtime_3 = new QWidget(this);
    m_runtime_3->resize(base_size);
    m_runtime_3_layout = createLayout(m_runtime_3);
    m_runtime_3_layout->setCurrentIndex(3);

    m_runtime_4 = new QWidget(this);
    m_runtime_4->resize(base_size);
    m_runtime_4_layout = createLayout(m_runtime_4);
    m_runtime_4_layout->setCurrentIndex(4);

    QPalette palette(MultiRuntimeWidget::palette());
    palette.setColor(QPalette::Background, Qt::gray);
    setAutoFillBackground(true);
    setPalette(palette);
}

void MultiRuntimeWidget::resizeEvent(QResizeEvent* event)
{
    ScalableWidget::resizeEvent(event);

    int offset = 1 * m_scale;
    QSize quarter_size(m_quarter_size.width() * m_width_scale - offset, m_quarter_size.height() * m_height_scale - offset);

    m_runtime_1->resize(quarter_size);
    m_runtime_1->move(0, 0);

    m_runtime_2->resize(quarter_size);
    m_runtime_2->move(quarter_size.width() + 2 * offset, 0);

    m_runtime_3->resize(quarter_size);
    m_runtime_3->move(0, quarter_size.height() + 2 * offset);

    m_runtime_4->resize(quarter_size);
    m_runtime_4->move(quarter_size.width() + 2 * offset, quarter_size.height() + 2 * offset);
}

void MultiRuntimeWidget::mouseReleaseEvent(QMouseEvent* event)
{
    QPoint p = event->pos();
    int w = width();
    int h = height();

    if ((p.x() <= 0.5f * w) && (p.y() <= 0.5f * h))
    {
        int index = (m_runtime_1_layout->currentIndex() + 1) % m_runtime_1_layout->count();

        m_runtime_1_layout->setCurrentIndex(index);
    }
    else if ((p.x() > 0.5f * w) && (p.y() <= 0.5f * h))
    {
        int index = (m_runtime_2_layout->currentIndex() + 1) % m_runtime_2_layout->count();

        m_runtime_2_layout->setCurrentIndex(index);
    }
    else if ((p.x() <= 0.5f * w) && (p.y() > 0.5f * h))
    {
        int index = (m_runtime_3_layout->currentIndex() + 1) % m_runtime_3_layout->count();

        m_runtime_3_layout->setCurrentIndex(index);
    }
    else
    {
        int index = (m_runtime_4_layout->currentIndex() + 1) % m_runtime_4_layout->count();

        m_runtime_4_layout->setCurrentIndex(index);
    }
}
