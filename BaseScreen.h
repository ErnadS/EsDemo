#ifndef BASESCREEN_H
#define BASESCREEN_H

#include "Button.h"
#include "DisplayAliveWidget.h"
#include "SpeedIndicationWidget.h"
#include "NavigationController.h"

class BaseScreen : public ScalableWidget
{
    Q_OBJECT

protected:
    NavigationController& m_navigation_controller;

    Button* m_button;
    DisplayAliveWidget* m_display_alive_widget;
    SpeedIndicationWidget* m_speed_indication_widget;

    const QSize m_button_size{150, 50};
    const QSize m_display_alive_widget_size{80, 50};
    const QSize m_speed_indication_widget_size{350, 24};

    const QPoint m_button_pos{0, 0};
    const QPoint m_display_alive_widget_pos{160, 3};
    const QPoint m_speed_indication_widget_pos{288, 0};

    virtual void setupLayout();

protected:
    explicit BaseScreen(QWidget* parent);
    void resizeEvent(QResizeEvent*);

protected slots:
    virtual void buttonClicked() = 0;

signals:
    void navigate(SetupMenuType setup_menu);
    void navigateBack();
};

#endif // BASESCREEN_H
