#ifndef DL2_AUX_SETUP_SCREEN_H
#define DL2_AUX_SETUP_SCREEN_H

#include "setup_screen.h"
#include <QVector>

class Dl2AuxSetupScreen : public SetupScreen
{
    Q_OBJECT

    QVector<bool> m_state_vector;

public:
    explicit Dl2AuxSetupScreen(QWidget* parent);

protected:
    void paintEvent(QPaintEvent*);
};

#endif
