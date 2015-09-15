#include "setup_screen.h"
#include <QPainter>

SetupScreen::SetupScreen(QWidget* parent) :
    BaseScreen(parent)
{
    setupLayout();
}

void SetupScreen::buttonClicked()
{
    m_navigation_controller.navigate(SETUP_MENU, false);
}

void SetupScreen::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(Qt::yellow);
    QFont font = painter.font();
    font.setPixelSize(40 * m_scale);
    painter.setFont(font);

    painter.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter | Qt::TextWordWrap, "This function is under development check for software upgrades on www.skipper.no");
}
