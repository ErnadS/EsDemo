#include "horizontal_item_widget_container.h"
#include <stdlib.h>
#include <stdexcept>

void HorizontalItemWidgetContainer::setupLayout()
{
    QSize item_size(m_item_size.width() * m_width_scale, m_item_size.height() * m_height_scale);
    int item_sep = m_width_scale * m_item_sep;

    int x = 0;
    for (int i = 0; i < m_item_widget_vector.size(); i++)
    {
        m_item_widget_vector[i]->resize(item_size);
        m_item_widget_vector[i]->move(x, 0);

        x += item_size.width() + item_sep;
    }
}

HorizontalItemWidgetContainer::HorizontalItemWidgetContainer(QWidget* parent, QSize base_size, QSize item_size, int item_sep) : ScalableWidget(parent, base_size), m_item_size(item_size), m_item_sep(item_sep)
{
    setupLayout();
}

void HorizontalItemWidgetContainer::addWidget(HorizontalItemWidget* item_widget)
{
    connect(item_widget, SIGNAL(clicked(HorizontalItemWidget*)), this, SLOT(clicked(HorizontalItemWidget*)));

    m_item_widget_vector.push_back(item_widget);

    setupLayout();
}

void HorizontalItemWidgetContainer::setActive(int index)
{
    if ((index < 0) || (index >= m_item_widget_vector.size()))
        throw std::range_error("Index is out of range!");

    for (auto widget: m_item_widget_vector)
        widget->setActive(false);

    m_item_widget_vector[index]->setActive(true);
}

void HorizontalItemWidgetContainer::resizeEvent(QResizeEvent *)
{
    ScalableWidget::resizeEvent(nullptr);
    setupLayout();
}

void HorizontalItemWidgetContainer::clicked(HorizontalItemWidget* item)
{
    for (int i = 0; i < m_item_widget_vector.size(); i++)
        if (m_item_widget_vector[i] == item)
        {
            setActive(i);
            emit clicked(i);
            break;
        }
}
