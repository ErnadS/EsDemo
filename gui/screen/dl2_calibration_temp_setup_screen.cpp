#include "dl2_calibration_temp_setup_screen.h"

Dl2CalibrationTempSetupScreen::Dl2CalibrationTempSetupScreen(QWidget* parent) : SetupScreen(parent)
{
    m_title_widget->setTitle("Temp");

    m_real_temp_widget = new UpDownWidget(this, m_real_temp_widget_size, "Real\nTemperature", QString::fromUtf8("°C"));
    m_real_temp_widget->setBackgroundColor(QColor(218, 218, 218));
    m_real_temp_widget->setBorderColor(QColor(144, 255, 112));

    setupLayout();
}

void Dl2CalibrationTempSetupScreen::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    QFont font = painter.font();
    font.setPixelSize(22 * m_scale);
    painter.setFont(font);

    QPen pen = painter.pen();
    pen.setColor(QColor(204, 255, 153));
    painter.setPen(pen);

    int w = m_real_temp_widget->width();
    int h = m_real_temp_widget->height();

    QRect measured_temp_rect(m_real_temp_widget->x(), 0.2f * height(), w, h);
    QString measured_temp_string = "Raw measured temperature: -.-" + QString::fromUtf8("°C");
    //painter.fillRect(measured_temp_rect, Qt::red);
    painter.drawText(measured_temp_rect, Qt::AlignCenter, measured_temp_string);

    QRect calib_temp_rect(m_real_temp_widget->x(), 0.25f * height(), w, h);
    QString calib_temp_string = "Calibrated temperature: -.-" + QString::fromUtf8("°C");
    //painter.fillRect(measured_temp_rect, Qt::red);
    painter.drawText(calib_temp_rect, Qt::AlignCenter, calib_temp_string);

    QRect other_temp_sources_rect(m_real_temp_widget->x(), 0.8f * height() - h, w, h);
    QString other_temp_sources_string = "OTHER Temp sources: NA";
    //painter.fillRect(other_temp_sources_rect, Qt::green);
    painter.drawText(other_temp_sources_rect, Qt::AlignCenter, other_temp_sources_string);
}

void Dl2CalibrationTempSetupScreen::setupLayout()
{
    SetupScreen::setupLayout();

    m_real_temp_widget->resize(m_real_temp_widget_size.width() * m_width_scale, m_real_temp_widget_size.height() * m_height_scale);
    m_real_temp_widget->move(m_real_temp_widget_pos.x() * m_width_scale, m_real_temp_widget_pos.y() * m_height_scale);
}
