#ifndef DL2_DIAGNOSTIC_SETUP_SCREEN_H
#define DL2_DIAGNOSTIC_SETUP_SCREEN_H

#include "setup_screen.h"

class Dl2DiagnosticSetupScreen : public SetupScreen
{
    Q_OBJECT

    QPushButton* m_self_test_button;
    QPushButton* m_upgrade_button;

    const QSize m_self_test_button_size{145, 60};
    const QPoint m_self_test_button_pos{161, 410};

    const QSize m_upgrade_button_size{145, 60};
    const QPoint m_upgrade_button_pos{579, 410};

public:
    explicit Dl2DiagnosticSetupScreen(QWidget* parent);

protected:
    void paintEvent(QPaintEvent*);
    void setupLayout();

protected slots:
    void selfTestButtonClicked();
    void upgradeButtonClicked();
};

#endif
