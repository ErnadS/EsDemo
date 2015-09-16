#ifndef SYSTEM_SETUP_SCREEN_H
#define SYSTEM_SETUP_SCREEN_H

#include "setup_screen.h"
#include <QPushButton>

class SystemSetupScreen : public SetupScreen
{
    Q_OBJECT

    QPushButton* m_add_button;
    QPushButton* m_remove_button;

private slots:
    void addClicked();
    void removeClicked();

public:
    explicit SystemSetupScreen(QWidget* parent);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent*);
};

#endif
