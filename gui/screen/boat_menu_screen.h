#ifndef BOAT_MENU_SCREEN_H
#define BOAT_MENU_SCREEN_H

#include "base_screen.h"

class BoatMenuScreen : public BaseScreen
{
public:
    BoatMenuScreen(QWidget* parent);

protected:
    void buttonClicked();
};

#endif
