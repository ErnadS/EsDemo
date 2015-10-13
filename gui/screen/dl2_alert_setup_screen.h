#ifndef DL2_ALERT_SETUP_SCREEN_H
#define DL2_ALERT_SETUP_SCREEN_H

#include "setup_screen.h"

class Dl2AlertSetupScreen: public SetupScreen
{
    Q_OBJECT

public:
    explicit Dl2AlertSetupScreen(QWidget* parent);

protected:
    void paintEvent(QPaintEvent*);
};

#endif
