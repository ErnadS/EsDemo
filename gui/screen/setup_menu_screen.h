#ifndef SETUP_MENU_SCREEN_H
#define SETUP_MENU_SCREEN_H

#include "base_screen.h"
#include "gui/widget/system_widget.h"
#include "gui/widget/button.h"

#include "gui/widget/item_widget_container.h"
#include "gui/widget/system_menu_widget_container.h"

class SetupMenuScreen : public BaseScreen
{
    Q_OBJECT

    SystemMenuWidgetContainer* m_system_widget_container;

    ItemWidget* m_system_setup_button;

    ItemWidgetContainer* m_dl1_setup_menu;
    ItemWidgetContainer* m_es_setup_menu;
    ItemWidgetContainer* m_dl2_setup_menu;
    ItemWidgetContainer* m_display_setup_menu;

    const QSize m_button_size{220, 70};
    const QSize m_setup_menu_size{400, 456};
    const QSize m_system_menu_size{345, 500};

    const QPoint m_setup_menu_pos{400, 24};
    const QPoint m_button_pos{10, 320};
    const QPoint m_system_menu_pos{10, 50};

    bool changeLayout(int index) const;

public:
    SetupMenuScreen(QWidget* parent);

protected:
    void setupLayout();
    void buttonClicked();

protected slots:
    void systemSelected(int index);
    void displaySelected();
    void dl1SetupSelected(int index);
    void esSetupSelected(int index);
    void dl2SetupSelected(int index);

    void systemSetupPressed(const ItemWidget*);

    void systemAdded(SystemEnum system);
    void systemRemoved(int index);
};

#endif
