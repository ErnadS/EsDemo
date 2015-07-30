#ifndef SETUP_MENU_SCREEN_H
#define SETUP_MENU_SCREEN_H

#include "base_screen.h"
#include "system_widget.h"
#include "button.h"
#include <QTableWidget>

class SetupMenuScreen : public BaseScreen
{
    Q_OBJECT

    void setupTableWidget(QTableWidget* table_widget, int index);

    Button* m_system_button;
    QTableWidget* m_table_widget_dl1;
    QTableWidget* m_table_widget_dl2_1;
    QTableWidget* m_table_widget_dl2_2;
    QTableWidget* m_table_widget_es;

    SystemWidget* m_dl1_system;
    SystemWidget* m_dl2_system_1;
    SystemWidget* m_dl2_system_2;
    SystemWidget* m_es_system;

    QSize m_table_size{300, 456};
    QSize m_system_button_size{350, 60};
    QSize m_system_size{120, 80};

    QPoint m_first_column{15, 100};
    QPoint m_second_column{215, 100};

    int m_vertical_space{10};

    void deactivateSystemWidgets();
    bool changeLayout() const;

public:
    SetupMenuScreen(QWidget* parent);

protected:
    void setupLayout();
    void buttonClicked();

protected slots:
    void dl1SystemClicked();
    void dl2System1Clicked();
    void dl2System2Clicked();
    void esSystemClicked();

    // QWidget interface
protected:
    void showEvent(QShowEvent*);
};

#endif
