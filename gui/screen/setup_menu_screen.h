#ifndef SETUP_MENU_SCREEN_H
#define SETUP_MENU_SCREEN_H

#include "base_screen.h"
#include "gui/widget/system_widget.h"
#include "gui/widget/button.h"

#include "gui/widget/item_widget_container.h"
#include "gui/widget/system_widget_container.h"

class SetupMenuScreen : public BaseScreen
{
    Q_OBJECT

    SystemWidgetContainer* m_system_widget_container;

    ItemWidget* m_cu_m001_setup_button;
    ItemWidget* m_system_setup_button;

    ItemWidgetContainer* m_dl1_setup_menu;
    ItemWidgetContainer* m_es_setup_menu;
    ItemWidgetContainer* m_dl2_setup_menu;

    const QSize m_button_size{220, 91};
    const QSize m_system_button_size{175, 60};
    const QSize m_setup_menu_size{445, 456};
    const QSize m_system_menu_size{220, 225};

    const QPoint m_setup_menu_pos{288, 24};
    const QPoint m_button_pos{0, 298};
    const QPoint m_system_menu_pos{0, 50};

    bool changeLayout() const;

public:
    SetupMenuScreen(QWidget* parent);

protected:
    void setupLayout();
    void buttonClicked();

protected slots:
    void systemSelected(int index);
    void dl1SetupSelected(int index);
    void esSetupSelected(int index);
    void dl2SetupSelected(int index);

    void cuM001SetupPressed(const ItemWidget*);
    void systemSetupPressed(const ItemWidget*);
};

#endif
