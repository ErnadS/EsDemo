#ifndef ES_RUNTIME_SCREEN_H
#define ES_RUNTIME_SCREEN_H

#include "runtime_screen.h"
#include "gui/widget/boat_button.h"

class EsRuntimeScreen : public RuntimeScreen
{
    Q_OBJECT

    BoatButton* m_boat_button;

    QSize m_boat_button_size{40, 25};

    QPoint m_boat_button_pos{600, 25};

public:
    EsRuntimeScreen(QWidget* parent, RuntimeScreenType runtime_screen_type);

protected:
    void setupLayout();

private slots:
    void boatButtonClicked();
};

#endif
