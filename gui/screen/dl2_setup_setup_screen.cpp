#include "dl2_setup_screen.h"

#include "gui/screen/dl2_setup_setup_screen.h"
#include "gui/screen/dl2_setup_options_screen.h"

void Dl2SetupScreen::menuClicked(int index)
{
    m_layout->setCurrentIndex(index);

    setupLayout();
}

Dl2SetupScreen::Dl2SetupScreen(QWidget* parent) :
    MultiSetupScreen(parent)
{    
    m_layout->addWidget(new Dl2SetupSetupScreen(this));
    m_layout->addWidget(new Dl2SetupOptionsScreen(this));

    m_item_container = new HorizontalItemWidgetContainer(this, m_item_container_size, m_item_size, m_item_sep);
    m_item_container->addWidget(new HorizontalItemWidget(m_item_container, m_item_size, "Setup"));
    m_item_container->addWidget(new HorizontalItemWidget(m_item_container, m_item_size, "Options"));
    m_item_container->setActive(0);

    connect(m_item_container, SIGNAL(clicked(int)), this, SLOT(menuClicked(int)));

    setLayout(m_layout);

    setupLayout();
}

void Dl2SetupScreen::setupLayout()
{
    MultiSetupScreen::setupLayout();

    QSize item_container_size(m_item_container_size.width() * m_width_scale, m_item_container_size.height() * m_height_scale);
    QPoint item_container_pos(m_item_container_pos.x() * m_width_scale, m_item_container_pos.y() * m_height_scale);

    m_item_container->resize(item_container_size);
    m_item_container->move(item_container_pos);
    m_item_container->raise();
}
