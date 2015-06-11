#ifndef RUNTIMESCREEN_H
#define RUNTIMESCREEN_H

#include "BaseScreen.h"
#include "WidgetEnum.h"
#include "InformationWidget.h"
#include "BrightnessWidget.h"
#include "NavigationWidget.h"
#include "BackgroundWidget.h"
#include "RuntimeWidgetA.h"
#include "RuntimeWidgetB.h"
#include "RuntimeWidgetC.h"
#include "RuntimeWidgetD.h"
#include "RuntimeWidgetE.h"
#include "RuntimeWidgetDl1.h"
#include "RuntimeWidgetEs.h"
#include "MultiRuntimeWidget.h"
#include "Dl1RuntimeWidgetB.h"
#include "EsRuntimeWidgetB.h"

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
    explicit RuntimeScreen(QWidget* parent, RuntimeScreenType runtime_screen_type);

protected:
    void setupLayout();
    void buttonClicked();

protected slots:
    void unitButtonClicked();
};

#endif // RUNTIMESCREEN_H
