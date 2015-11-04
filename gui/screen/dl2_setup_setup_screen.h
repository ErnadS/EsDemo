#ifndef DL2_SETUP_SETUP_SCREEN_H
#define DL2_SETUP_SETUP_SCREEN_H

#include "setup_screen.h"

class Dl2SetupSetupScreen : public SetupScreen
{
    Q_OBJECT

    Button* m_reset_button;

    void drawDistanceLine(QPainter& painter, int x, int y, int width);
    void drawArrow(QPainter& painter, int x, int y, int width);

    const QSize m_reset_button_size{200, 50};
    const QPoint m_reset_button_pos{0, 380};

public:
    explicit Dl2SetupSetupScreen(QWidget* parent);

protected:
    void paintEvent(QPaintEvent*);
    void setupLayout();
};

#endif
