#ifndef SETUP_SCREEN_H
#define SETUP_SCREEN_H

#include "base_screen.h"

class SetupScreen : public BaseScreen
{
    Q_OBJECT

public:
    explicit SetupScreen(QWidget* parent);

    // BaseScreen interface
protected slots:
    void buttonClicked();

protected:
    void paintEvent(QPaintEvent *);
};

#endif
