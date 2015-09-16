#include "system_setup_screen.h"

void SystemSetupScreen::addClicked()
{
    m_navigation_controller.addSystem(SystemEnum::DL2_SYSTEM);
}

void SystemSetupScreen::removeClicked()
{
    int index = m_navigation_controller.systemCount() - 1;

    if (index != 0)
        m_navigation_controller.removeSystem(index);
}

SystemSetupScreen::SystemSetupScreen(QWidget* parent) : SetupScreen(parent)
{
    m_add_button = new QPushButton("Add", this);
    m_add_button->resize(200, 200);
    m_add_button->move(100, 100);

    m_remove_button = new QPushButton("Remove", this);
    m_remove_button->resize(200, 200);
    m_remove_button->move(300, 100);

    connect(m_add_button, SIGNAL(clicked()), this, SLOT(addClicked()));
    connect(m_remove_button, SIGNAL(clicked()), this, SLOT(removeClicked()));
}

void SystemSetupScreen::paintEvent(QPaintEvent*)
{

}
