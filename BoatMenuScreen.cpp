#include "BoatMenuScreen.h"

BoatMenuScreen::BoatMenuScreen(QWidget* parent) : BaseScreen(parent)
{

}

void BoatMenuScreen::buttonClicked()
{
    m_navigation_controller.navigateBack();
}
