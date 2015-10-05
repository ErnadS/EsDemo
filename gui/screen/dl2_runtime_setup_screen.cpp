#include "dl2_runtime_setup_screen.h"
#include "dl2_runtime_a_setup_screen.h"
#include "dl2_runtime_b_setup_screen.h"
#include "dl2_runtime_c_setup_screen.h"
#include "dl2_runtime_d_setup_screen.h"
#include "dl2_runtime_e_setup_screen.h"

void Dl2RuntimeSetupScreen::setupLayout()
{
    MultiSetupScreen::setupLayout();

    QSize item_container_size(m_item_container_size.width() * m_width_scale, m_item_container_size.height() * m_height_scale);
    QPoint item_container_pos(m_item_container_pos.x() * m_width_scale, m_item_container_pos.y() * m_height_scale);

    m_item_container->resize(item_container_size);
    m_item_container->move(item_container_pos);
    m_item_container->raise();
}

void Dl2RuntimeSetupScreen::menuClicked(int index)
{
    m_layout->setCurrentIndex(index);
    setupLayout();
}

Dl2RuntimeSetupScreen::Dl2RuntimeSetupScreen(QWidget* parent) :
    MultiSetupScreen(parent)
{
    m_layout->addWidget(new Dl2RuntimeASetupScreen(this));
    m_layout->addWidget(new Dl2RuntimeBSetupScreen(this));
    m_layout->addWidget(new Dl2RuntimeCSetupScreen(this));
    m_layout->addWidget(new Dl2RuntimeDSetupScreen(this));
    m_layout->addWidget(new Dl2RuntimeESetupScreen(this));

    m_item_container = new HorizontalItemWidgetContainer(this, m_item_container_size, m_item_size, m_item_sep);
    m_item_container->addWidget(new HorizontalItemWidget(m_item_container, m_item_size, "Pg A"));
    m_item_container->addWidget(new HorizontalItemWidget(m_item_container, m_item_size, "Pg B"));
    m_item_container->addWidget(new HorizontalItemWidget(m_item_container, m_item_size, "Pg C"));
    m_item_container->addWidget(new HorizontalItemWidget(m_item_container, m_item_size, "Pg D"));
    m_item_container->addWidget(new HorizontalItemWidget(m_item_container, m_item_size, "Pg E"));
    m_item_container->setActive(0);

    connect(m_item_container, SIGNAL(clicked(int)), this, SLOT(menuClicked(int)));

    setLayout(m_layout);

    setupLayout();
}
