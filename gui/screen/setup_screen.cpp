#include "setup_screen.h"
#include "multi_setup_screen.h"
#include <QPainter>

SetupScreen::SetupScreen(QWidget* parent) :
    BaseScreen(parent)
{
    m_keyboard = new QVirtualKeyboard(this);
    m_keyboard->hide();

    m_selectable_item_widget_container = new SelectableItemWidgetContainer(this, m_selectable_item_widget_container_size, m_keyboard, 7);

    connect(m_selectable_item_widget_container, SIGNAL(changedProtected(QString)), this, SLOT(changedProtected(QString)));
    connect(m_selectable_item_widget_container, SIGNAL(changeValueProtected(QString,QString)), this, SLOT(changeValueProtected(QString,QString)));

    if (qobject_cast<MultiSetupScreen*>(parent))
    {
        connect(m_password_widget, SIGNAL(login()), this, SLOT(lower()));
        connect(m_password_widget, SIGNAL(cancel()), this, SLOT(lower()));
        connect(m_selectable_item_widget_container->getKeyboard(), SIGNAL(keyPressed(QKeyEvent*)), this, SLOT(slotLower(QKeyEvent*)));
    }
    setupLayout();
}

void SetupScreen::slotLower(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Cancel || event->key() == Qt::Key_Enter)
    {
        lower();
    }
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
