#ifndef BASE_RUNTIME_SETUP_SCREEN_H
#define BASE_RUNTIME_SETUP_SCREEN_H

#include "setup_screen.h"
#include "gui/screen/runtime_screen.h"

class BaseRuntimeSetupScreen : public SetupScreen
{
    Q_OBJECT

protected:
    RuntimeScreen* m_runtime_screen{nullptr};

    QSize m_runtime_screen_base_size{800, 480};
    QSize m_runtime_screen_size{400, 240};
    QPoint m_runtime_screen_pos{0, 100};

    void setupLayout();

public:
    explicit BaseRuntimeSetupScreen(QWidget* parent);

protected slots:
    void buttonClicked();
};

#endif
