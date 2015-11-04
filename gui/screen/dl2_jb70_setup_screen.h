#ifndef DL2_JB70_SETUP_SCREEN_H
#define DL2_JB70_SETUP_SCREEN_H

#include "setup_screen.h"

class Dl2Jb70SetupScreen : public SetupScreen
{
    Q_OBJECT

    bool isInValidIpRange(const QString& ip) const;

public:
    explicit Dl2Jb70SetupScreen(QWidget* parent);

protected:
    void paintEvent(QPaintEvent*);
};

#endif
