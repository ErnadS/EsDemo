#include "EsRuntimeScreen.h"

EsRuntimeScreen::EsRuntimeScreen(QWidget* parent, RuntimeScreenType runtime_screen_type) : RuntimeScreen(parent, runtime_screen_type)
{
    m_boat_button = new BoatButton(this, m_boat_button_size);

    connect(m_boat_button, SIGNAL(clicked()), this, SLOT(boatButtonClicked()));

    setupLayout();
}

void EsRuntimeScreen::setupLayout()
{
    RuntimeScreen::setupLayout();

    m_boat_button->resize(m_boat_button_size.width() * m_width_scale, m_boat_button_size.height() * m_height_scale);
    m_boat_button->move(m_boat_button_pos.x() * m_width_scale, m_boat_button_pos.y() * m_height_scale);
}

void EsRuntimeScreen::boatButtonClicked()
{
    m_navigation_controller.navigate(SetupMenuType::BOAT_MENU);
}
