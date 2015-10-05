#include "base_runtime_setup_screen.h"

void BaseRuntimeSetupScreen::setupLayout()
{
    SetupScreen::setupLayout();

    QSize runtime_screen_size(m_runtime_screen_size.width() * m_width_scale, m_runtime_screen_size.height() * m_height_scale);
    QPoint runtime_screen_pos(m_runtime_screen_pos.x() * m_width_scale, m_runtime_screen_pos.y() * m_height_scale);

    if (m_runtime_screen != nullptr)
    {
        m_runtime_screen->resize(runtime_screen_size);
        m_runtime_screen->move(runtime_screen_pos);
    }
}

BaseRuntimeSetupScreen::BaseRuntimeSetupScreen(QWidget* parent) : SetupScreen(parent)
{
    setupLayout();
}

void BaseRuntimeSetupScreen::buttonClicked()
{
    m_navigation_controller.navigate(SETUP_MENU, false);
}
