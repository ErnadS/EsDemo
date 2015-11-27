#include "es_setup_screen.h"
#include "gui/screen/es_setup_setup_screen.h"
#include "gui/screen/es_setup_transducer_select_screen.h"

void EsSetupScreen::menuClicked(int index)
{
    m_layout->setCurrentIndex(index);

    setupLayout();
}

EsSetupScreen::EsSetupScreen(QWidget* parent) :
    MultiSetupScreen(parent)
{
    m_layout->addWidget(new EsSetupSetupScreen(this));
    m_layout->addWidget(new EsSetupTransducerSelectScreen(this));

    m_item_container = new HorizontalItemWidgetContainer(this, m_item_container_size, m_item_size, m_item_sep);
    m_item_container->addWidget(new HorizontalItemWidget(m_item_container, m_item_size, "Setup"));
    m_item_container->addWidget(new HorizontalItemWidget(m_item_container, m_item_size, "Options"));
    m_item_container->setActive(0);

    connect(m_item_container, SIGNAL(clicked(int)), this, SLOT(menuClicked(int)));

    setLayout(m_layout);

    setupLayout();
}

void EsSetupScreen::setupLayout()
{
    MultiSetupScreen::setupLayout();

    QSize item_container_size(m_item_container_size.width() * m_width_scale, m_item_container_size.height() * m_height_scale);
    QPoint item_container_pos(m_item_container_pos.x() * m_width_scale, m_item_container_pos.y() * m_height_scale);

    m_item_container->resize(item_container_size);
    m_item_container->move(item_container_pos);
    m_item_container->raise();
}

