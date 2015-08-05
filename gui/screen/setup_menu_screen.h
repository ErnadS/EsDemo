#ifndef SETUP_MENU_SCREEN_H
#define SETUP_MENU_SCREEN_H

#include "base_screen.h"
#include "gui/widget/system_widget.h"
#include "gui/widget/button.h"

#include "gui/widget/item_widget_container.h"

class SetupMenuScreen : public BaseScreen
{
    Q_OBJECT

    Button* m_system_button;

    SystemWidget* m_dl1_system;
    SystemWidget* m_dl2_system;
    SystemWidget* m_es_system;

    ItemWidgetContainer* m_dl1_setup_menu;
    ItemWidgetContainer* m_es_setup_menu;
    ItemWidgetContainer* m_dl2_setup_menu;

    const QSize m_system_button_size{175, 60};
    const QSize m_system_size{120, 80};
    const QSize m_setup_menu_size{445, 456};

    const QPoint m_first_column{84, 100};
    const QPoint m_setup_menu_pos{288, 24};

    int m_vertical_space{20};

    void deactivateSystemWidgets();
    bool changeLayout() const;

public:
    SetupMenuScreen(QWidget* parent);

protected:
    void setupLayout();
    void buttonClicked();

protected slots:
    void dl1SystemClicked();
    void dl2SystemClicked();
    void esSystemClicked();

    void dl1SetupSelected(int index);
    void esSetupSelected(int index);
    void dl2SetupSelected(int index);

protected:
    void showEvent(QShowEvent*);
};

#endif
