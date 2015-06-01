#ifndef BOATMENUSCREEN_H
#define BOATMENUSCREEN_H

#include "BaseScreen.h"

class BoatMenuScreen : public BaseScreen
{
public:
    BoatMenuScreen(QWidget* parent);

protected:
    void buttonClicked();
};

#endif // BOATMENUSCREEN_H
