#include "system_widget_container.h"
#include <QPainter>
#include <QDebug>

void SystemWidgetContainer::setupLayout()
{
    QSize item_size(0.675f * baseSize().width() * m_width_scale, baseSize().height() / (m_display_size + 0.5f) * m_height_scale + 0.5f);
    QSize display_size(0.75f * baseSize().width() * m_width_scale, baseSize().height() / (m_display_size) * m_height_scale + 0.5f);
    QSize arrow_size(0.15f * baseSize().width() * m_scale, 0.15f * baseSize().width() * m_scale);

    for (int i = 0; i < m_system_widget_vector.size(); i++)
    {
        m_system_widget_vector[i]->resize(item_size);
        m_system_widget_vector[i]->move(0, (i - m_rotation_offset) * display_size.height());

        if ((i - m_rotation_offset >= 0) && (i - m_rotation_offset < m_system_widget_vector.size()))
        {
            m_system_widget_vector[i]->setVisible(true);
        }
        else
        {
            m_system_widget_vector[i]->setVisible(false);
        }
    }

    m_up_arrow->resize(arrow_size);
    m_down_arrow->resize(arrow_size);

    m_up_arrow->move(0.85f * baseSize().width() * m_scale, 0);
    m_down_arrow->move(0.85f * baseSize().width() * m_scale, (m_display_size - 1) * display_size.height() + item_size.height() - arrow_size.height());

    m_rotation_offset == 0 ? m_up_arrow->setVisible(false) : m_up_arrow->setVisible(true);
    m_rotation_offset == m_system_widget_vector.size() - m_display_size ? m_down_arrow->setVisible(false) : m_down_arrow->setVisible(true);
}

SystemWidgetContainer::SystemWidgetContainer(QWidget* parent, QSize base_size, int display_size, QList<QString> type_list, QList<QString> name_list) : ScalableWidget(parent, base_size), m_display_size(display_size)
{
    QSize item_size(0.675f * base_size.width(), base_size.height() / display_size + 0.5f);
    QSize arrow_size(0.15f * base_size.width(), 0.15f * base_size.width());

    for (int i = 0; i < name_list.size(); i++)
    {
        SystemWidget* system_widget = new SystemWidget(this, item_size, type_list[i], name_list[i]);
        m_system_widget_vector.push_back(system_widget);

        connect(system_widget, SIGNAL(pressed(const SystemWidget*)), this, SLOT(itemPressed(const SystemWidget*)));
    }

    m_up_arrow = new ArrowWidget(this, arrow_size, FORWARD);
    m_down_arrow = new ArrowWidget(this, arrow_size, BACKWARD);

    connect(m_up_arrow, SIGNAL(pressed()), this, SLOT(upPressed()));
    connect(m_down_arrow, SIGNAL(pressed()), this, SLOT(downPressed()));

    setupLayout();
}

void SystemWidgetContainer::setActive(int index)
{
    for (int i = 0; i < m_system_widget_vector.size(); i++)
    {
        if (i != index)
        {
            m_system_widget_vector[i]->setActive(false);
        }
        else
        {
            m_system_widget_vector[i]->setActive(true);
        }
    }
}

void SystemWidgetContainer::itemPressed(const SystemWidget* item)
{
    for (int i = 0; i < m_system_widget_vector.size(); i++)
    {
        if (m_system_widget_vector[i] == item)
        {
            emit itemSelected(i);
            return;
        }
    }
}

void SystemWidgetContainer::upPressed()
{
    m_rotation_offset--;

    if (m_rotation_offset < 0)
    {
        m_rotation_offset = 0;
    }

    setupLayout();
}

void SystemWidgetContainer::downPressed()
{
    m_rotation_offset++;

    if (m_display_size + m_rotation_offset >= m_system_widget_vector.size())
    {
        m_rotation_offset = m_system_widget_vector.size() - m_display_size;
    }

    setupLayout();
}

void SystemWidgetContainer::resizeEvent(QResizeEvent*)
{
    ScalableWidget::resizeEvent(nullptr);
    setupLayout();
}
