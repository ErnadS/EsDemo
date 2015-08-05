#include "setup_screen.h"
#include <QDebug>

SetupScreen::SetupScreen(QWidget* parent) :
    BaseScreen(parent)
{
    setupLayout();
}

void SetupScreen::buttonClicked()
{
    m_navigation_controller.navigateBack();
}
