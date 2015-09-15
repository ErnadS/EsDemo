#include "system_setup_screen.h"
#include <QDebug>

void SystemSetupScreen::addClicked()
{
    qDebug() << "Add clicked...";
    m_navigation_controller.addSystem(SystemEnum::DL2_SYSTEM);

    qDebug() << m_navigation_controller.systemCount();
}

void SystemSetupScreen::removeClicked()
{
    qDebug() << "Remove clicked...";
}

SystemSetupScreen::SystemSetupScreen(QWidget* parent) : SetupScreen(parent)
{
    /*
    m_add_button = new QPushButton("Add", this);
    m_add_button->resize(200, 200);
    m_add_button->move(100, 100);

    m_remove_button = new QPushButton("Remove", this);
    m_remove_button->resize(200, 200);
    m_remove_button->move(300, 100);

    connect(m_add_button, SIGNAL(clicked()), this, SLOT(addClicked()));
    connect(m_remove_button, SIGNAL(clicked()), this, SLOT(removeClicked()));
    */
}
