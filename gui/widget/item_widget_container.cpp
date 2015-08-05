#include "item_widget_container.h"
#include <QPainter>

void ItemWidgetContainer::setupLayout()
{
    QSize item_size(0.9f * baseSize().width() * m_width_scale, baseSize().height() / m_display_size * m_height_scale + 0.5f);
    QSize arrow_size(0.1f * baseSize().width() * m_scale, 0.1f * baseSize().width() * m_scale);

    for (int i = 0; i < m_item_widget_vector.size(); i++)
    {
        m_item_widget_vector[i]->resize(item_size);
        m_item_widget_vector[i]->move(0, (i - m_rotation_offset) * item_size.height());

        if ((i - m_rotation_offset >= 0) && (i - m_rotation_offset < m_item_widget_vector.size()))
        {
            m_item_widget_vector[i]->setVisible(true);
        }
        else
        {
            m_item_widget_vector[i]->setVisible(false);
        }
    }

    m_up_arrow->resize(arrow_size);
    m_down_arrow->resize(arrow_size);

    m_up_arrow->move(item_size.width(), 0);
    m_down_arrow->move(item_size.width(), height() - arrow_size.height());

    m_rotation_offset == 0 ? m_up_arrow->setVisible(false) : m_up_arrow->setVisible(true);
    m_rotation_offset == m_item_widget_vector.size() - m_display_size ? m_down_arrow->setVisible(false) : m_down_arrow->setVisible(true);
}

ItemWidgetContainer::ItemWidgetContainer(QWidget* parent, QSize base_size, int display_size, QList<QString> item_list) : ScalableWidget(parent, base_size), m_display_size(display_size)
{
    QSize item_size(0.9f * base_size.width(), base_size.height() / display_size + 0.5f);
    QSize arrow_size(0.1f * base_size.width(), 0.1f * base_size.width());

    for (int i = 0; i < item_list.size(); i++)
    {
        RowIndexParity parity = (i % 2 == 0) ? ODD : EVEN;

        ItemWidget* item_widget = new ItemWidget(this, item_size, item_list[i], parity);
        m_item_widget_vector.push_back(item_widget);

        connect(item_widget, SIGNAL(pressed(const ItemWidget*)), this, SLOT(itemPressed(const ItemWidget*)));
    }

    m_up_arrow = new ArrowWidget(this, arrow_size, FORWARD);
    m_down_arrow = new ArrowWidget(this, arrow_size, BACKWARD);

    connect(m_up_arrow, SIGNAL(pressed()), this, SLOT(upPressed()));
    connect(m_down_arrow, SIGNAL(pressed()), this, SLOT(downPressed()));

    setupLayout();
}

void ItemWidgetContainer::itemPressed(const ItemWidget* item)
{
    for (int i = 0; i < m_item_widget_vector.size(); i++)
    {
        if (m_item_widget_vector[i] == item)
        {
            emit itemSelected(i);
            return;
        }
    }
}

void ItemWidgetContainer::upPressed()
{
    m_rotation_offset--;

    if (m_rotation_offset < 0)
    {
        m_rotation_offset = 0;
    }

    setupLayout();
}

void ItemWidgetContainer::downPressed()
{
    m_rotation_offset++;

    if (m_display_size + m_rotation_offset >= m_item_widget_vector.size())
    {
        m_rotation_offset = m_item_widget_vector.size() - m_display_size;
    }

    setupLayout();
}

void ItemWidgetContainer::resizeEvent(QResizeEvent*)
{
    ScalableWidget::resizeEvent(nullptr);
    setupLayout();
}
