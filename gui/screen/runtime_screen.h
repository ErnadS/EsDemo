#ifndef RUNTIME_SCREEN_H
#define RUNTIME_SCREEN_H

#include "base_screen.h"
#include "gui/widget_enum.h"
#include "gui/widget/information_widget.h"
#include "gui/widget/brightness_widget.h"
#include "gui/widget/navigation_widget.h"
#include "gui/widget/background_widget.h"
#include "gui/widget/runtime_widget_a.h"
#include "gui/widget/runtime_widget_b.h"
#include "gui/widget/runtime_widget_c.h"
#include "gui/widget/runtime_widget_d.h"
#include "gui/widget/runtime_widget_e.h"
#include "gui/widget/runtime_widget_dl1.h"
#include "gui/widget/runtime_widget_es.h"
#include "gui/widget/dl1_runtime_widget_b.h"
#include "gui/widget/es_runtime_widget_b.h"

class RuntimeScreen : public BaseScreen
{
    Q_OBJECT

    Button* m_unit_button;
    QVector<InformationWidget*> m_information_widget_vector;
    BrightnessWidget* m_brightness_widget;
    NavigationWidget* m_navigation_widget;
    //TODO: Refactor into RuntimeWidget*
    QWidget* m_runtime_widget;

    QSize m_unit_button_size{40, 25};
    QSize m_right_widget_size{160, 66};
    QSize m_runtime_widget_size{640, 430};
    int m_vertical_padding = 3;

    QPoint m_unit_button_pos{560, 25};
    QPoint m_right_widget_pos{640, 0};
    QPoint m_runtime_widget_pos{0, 50};

    QWidget* createRuntimeWidget(RuntimeScreenType runtime_screen_type);

    RuntimeScreenType m_runtime_screen_type;

public:
    explicit RuntimeScreen(QWidget* parent, RuntimeScreenType runtime_screen_type, bool preview = false);

protected:
    void setupLayout();
    void buttonClicked();

protected slots:
    void unitButtonClicked();
};

#endif
