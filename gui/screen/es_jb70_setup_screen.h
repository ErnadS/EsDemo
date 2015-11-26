#ifndef ES_JB70_SETUP_SCREEN_H
#define ES_JB70_SETUP_SCREEN_H

#include "setup_screen.h"

class EsJb70SetupScreen : public SetupScreen
{
    Q_OBJECT

    bool isInValidIpRange(const QString& ip) const;

public:
    explicit EsJb70SetupScreen(QWidget* parent);

protected:
    void paintEvent(QPaintEvent*);
};

#endif
