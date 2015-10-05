#include "setup_screen.h"
#include <QPainter>

SetupScreen::SetupScreen(QWidget* parent) :
    BaseScreen(parent)
{
    m_keyboard = new QVirtualKeyboard(this);
    m_keyboard->hide();

    m_selectable_item_widget_container = new SelectableItemWidgetContainer(this, m_selectable_item_widget_container_size, m_keyboard, 7);

    setupLayout();
}

void SetupScreen::buttonClicked()
{
    m_navigation_controller.navigate(SETUP_MENU, false);
}

void SetupScreen::setupLayout()
{
    BaseScreen::setupLayout();

    m_selectable_item_widget_container->resize(m_selectable_item_widget_container_size.width() * m_width_scale, m_selectable_item_widget_container_size.height() * m_height_scale);
    m_selectable_item_widget_container->move(m_selectable_item_widget_container_pos.x() * m_width_scale, m_selectable_item_widget_container_pos.y() * m_height_scale);

    m_keyboard->resize(m_keyboard_size.width() * m_width_scale, m_keyboard_size.height() * m_height_scale);
    m_keyboard->move(m_keyboard_pos.x() * m_width_scale, m_keyboard_pos.y() * m_height_scale);
}
