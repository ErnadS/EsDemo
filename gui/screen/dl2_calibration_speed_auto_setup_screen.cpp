#include "dl2_calibration_speed_auto_setup_screen.h"
#include <QPainter>

Dl2CalibrationSpeedAutoSetupScreen::Dl2CalibrationSpeedAutoSetupScreen(QWidget* parent) : Dl2CalibrationSpeedSetupScreen(parent)
{
    m_title_widget->setTitle("Auto setup");
}

void Dl2CalibrationSpeedAutoSetupScreen::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(Qt::yellow);
    QFont font = painter.font();
    font.setPixelSize(40 * m_scale);
    painter.setFont(font);

    painter.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter | Qt::TextWordWrap, "This function is under development check for software upgrades on www.skipper.no");
}
