#ifndef ES_SETUP_TRANSDUCER_SELECT_SCREEN_H
#define ES_SETUP_TRANSDUCER_SELECT_SCREEN_H

#include "setup_screen.h"

class EsSetupTransducerSelectScreen : public SetupScreen
{
    Q_OBJECT

public:
    explicit EsSetupTransducerSelectScreen(QWidget *parent);

protected:
    void paintEvent(QPaintEvent *);
};


#endif // ES_SETUP_TRANSDUCER_SELECT_SCREEN_H
