#include "multi_setup_screen.h"

MultiSetupScreen::MultiSetupScreen(QWidget* parent) : BaseScreen(parent)
{
    m_layout = new QStackedLayout();

    setupLayout();
}

void MultiSetupScreen::buttonClicked()
{
    m_navigation_controller.navigate(SETUP_MENU, false);
}
