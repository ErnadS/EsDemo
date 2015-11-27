#ifndef SETUP_SCREEN_H
#define SETUP_SCREEN_H

#include "base_screen.h"
#include "gui/widget/selectable_item_widget_container.h"
#include "gui/keyboard/QVirtualKeyboard.h"

class SetupScreen : public BaseScreen
{
    Q_OBJECT

    QSize m_selectable_item_size{320, 65};
    QSize m_selectable_item_widget_container_size{355, 455};

    QPoint m_selectable_item_widget_container_pos{445, 24};

protected:
    QSize m_keyboard_size{444, 262};
    QPoint m_keyboard_pos{0, 208};
    SelectableItemWidgetContainer* m_selectable_item_widget_container;
    QVirtualKeyboard* m_keyboard;

public:
    explicit SetupScreen(QWidget* parent);

protected slots:
    void buttonClicked();

protected:
    void setupLayout();
};

#endif
