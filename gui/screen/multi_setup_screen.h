#ifndef MULTI_SETUP_SCREEN_H
#define MULTI_SETUP_SCREEN_H

#include "base_screen.h"
#include "gui/widget/horizontal_item_widget_container.h"

class MultiSetupScreen : public BaseScreen
{
    Q_OBJECT

protected:
    QStackedLayout* m_layout;
    HorizontalItemWidgetContainer* m_item_container;

public:
    explicit MultiSetupScreen(QWidget* parent);

protected slots:
    void buttonClicked();
};

#endif
