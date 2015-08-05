#ifndef BASE_SCREEN_H
#define BASE_SCREEN_H

#include "gui/widget/button.h"
#include "gui/widget/display_alive_widget.h"
#include "gui/widget/title_widget.h"
#include "gui/navigation_controller.h"

class BaseScreen : public ScalableWidget
{
    Q_OBJECT

protected:
    NavigationController& m_navigation_controller;

    Button* m_button;
    DisplayAliveWidget* m_display_alive_widget;
    TitleWidget* m_title_widget;

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

public:
    TitleWidget* titleWidget() const;
};

#endif
