#ifndef CU_SETUP_SCREEN_H
#define CU_SETUP_SCREEN_H

#include "setup_screen.h"

class CuSetupScreen : public SetupScreen
{
    Q_OBJECT

public:
    explicit CuSetupScreen(QWidget* parent);
protected:
    void paintEvent(QPaintEvent*);
    bool isInValidIpRange(const QString& ip) const;
};

#endif
