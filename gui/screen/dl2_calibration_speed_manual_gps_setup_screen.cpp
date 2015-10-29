#include "dl2_calibration_speed_manual_gps_setup_screen.h"

Dl2CalibrationSpeedManualGpsSetupScreen::Dl2CalibrationSpeedManualGpsSetupScreen(QWidget* parent) : Dl2CalibrationSpeedSetupScreen(parent)
{
    m_title_widget->setTitle("Manual GPS");

    m_graph = new CalibrationGraphWidget(this, m_graph_size);

    int font_pixel_size = 16;

    m_recalibrate_button = new LegButton(this, m_recalibrate_button_size, "Recalibrate zone 3\nusing speed from GPS");
    m_recalibrate_button->setFontPixelSize(font_pixel_size);
    m_recalibrate_button->setBackgroundColor(QColor(100, 100, 100));
    m_recalibrate_button->setBorderColor(QColor(233, 225, 38));
    m_recalibrate_button->hide();

    m_save_button = new LegButton(this, m_save_button_size, "Save");
    m_save_button->setFontPixelSize(font_pixel_size);
    m_save_button->setBackgroundColor(QColor(100, 100, 100));
    m_save_button->setBorderColor(QColor(233, 225, 38));
    m_save_button->hide();

    m_discard_button = new LegButton(this, m_discard_button_size, "Discard");
    m_discard_button->setFontPixelSize(font_pixel_size);
    m_discard_button->setBackgroundColor(QColor(100, 100, 100));
    m_discard_button->setBorderColor(QColor(233, 225, 38));
    m_discard_button->hide();

    setupLayout();
}

void Dl2CalibrationSpeedManualGpsSetupScreen::setupLayout()
{
    Dl2CalibrationSpeedSetupScreen::setupLayout();

    QSize graph_size(m_graph_size.width() * m_width_scale, m_graph_size.height() * m_height_scale);
    QPoint graph_pos(m_graph_pos.x() * m_width_scale, m_graph_pos.y() * m_height_scale);

    QSize recalibrate_button_size(m_recalibrate_button_size.width() * m_width_scale, m_recalibrate_button_size.height() * m_height_scale);
    QSize save_button_size(m_save_button_size.width() * m_width_scale, m_save_button_size.height() * m_height_scale);
    QSize discard_button_size(m_discard_button_size.width() * m_width_scale, m_discard_button_size.height() * m_height_scale);

    QPoint recalibrate_button_pos(m_recalibrate_button_pos.x() * m_width_scale, m_recalibrate_button_pos.y() * m_height_scale);
    QPoint save_button_pos(m_save_button_pos.x() * m_width_scale, m_save_button_pos.y() * m_height_scale);
    QPoint discard_button_pos(m_discard_button_pos.x() * m_width_scale, m_discard_button_pos.y() * m_height_scale);

    m_graph->resize(graph_size);
    m_recalibrate_button->resize(recalibrate_button_size);
    m_save_button->resize(save_button_size);
    m_discard_button->resize(discard_button_size);

    m_graph->move(graph_pos);
    m_recalibrate_button->move(recalibrate_button_pos);
    m_save_button->move(save_button_pos);
    m_discard_button->move(discard_button_pos);
}
