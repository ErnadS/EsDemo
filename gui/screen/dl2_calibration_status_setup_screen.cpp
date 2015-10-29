#include "dl2_calibration_status_setup_screen.h"

Dl2CalibrationStatusSetupScreen::Dl2CalibrationStatusSetupScreen(QWidget* parent) : SetupScreen(parent)
{
    m_calibration_status_label = new QLabel(this);
    m_reason_label = new QLabel(this);
    m_suggestion_label = new QLabel(this);

    m_title_widget->setTitle("Status");

    m_graph = new CalibrationGraphWidget(this, m_graph_size);

    setupLayout();
}

void Dl2CalibrationStatusSetupScreen::setupLayout()
{
    SetupScreen::setupLayout();

    QSize graph_size(m_graph_size.width() * m_width_scale, m_graph_size.height() * m_height_scale);
    QPoint graph_pos(m_graph_pos.x() * m_width_scale, m_graph_pos.y() * m_height_scale);

    m_graph->resize(graph_size);
    m_graph->move(graph_pos);
}

// TODO: Refactor to use standard Qt UI components
void Dl2CalibrationStatusSetupScreen::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    int x_ff = 420 * m_width_scale;
    int y_ff = 45 * m_height_scale;
    int w_ff = 370 * m_width_scale;
    int h_ff = 120 * m_height_scale;

    int border = 8 * m_scale;

    QRect first_outer_rect(x_ff - border / 2, y_ff - border / 2, w_ff + border, h_ff + border);
    QRect first_inner_rect(x_ff, y_ff, w_ff, h_ff);

    painter.fillRect(first_outer_rect, QColor(230, 170, 30));
    painter.fillRect(first_inner_rect, QColor(100, 100, 100));

    int y_ss = y_ff + h_ff + 15 * m_height_scale;

    QRect second_outer_rect(x_ff - border / 2, y_ss - border / 2, w_ff + border, 1.5*h_ff + border);
    QRect second_inner_rect(x_ff, y_ss, w_ff, 1.5*h_ff);

    painter.fillRect(second_outer_rect, QColor(230, 170, 30));
    painter.fillRect(second_inner_rect, QColor(100, 100, 100));

    QRect angle_label_rect(x_ff + 0.0125f * w_ff, y_ff, 0.8f * w_ff, 0.2f * h_ff);
    QRect sea_test_number_label_rect(x_ff + 0.0125f * w_ff, y_ff + 0.2f * h_ff, 0.9f * w_ff, 0.2f * h_ff);
    QRect auto_mode_label_rect(x_ff + 0.0125f * w_ff, y_ff + 0.4f * h_ff, 0.9f * w_ff, 0.2f * h_ff);
    QRect tilt_offset_label_rect(x_ff + 0.0125f * w_ff, y_ff + 0.6f * h_ff, 0.9f * w_ff, 0.2f * h_ff);
    QRect temp_offset_label_rect(x_ff + 0.0125f * w_ff, y_ff + 0.8f * h_ff, 0.9f * w_ff, 0.2f * h_ff);

    /* Uncomment for label placement help
    painter.fillRect(angle_label_rect, Qt::red);
    painter.fillRect(sea_test_number_label_rect, Qt::green);
    painter.fillRect(auto_mode_label_rect, Qt::red);
    painter.fillRect(tilt_offset_label_rect, Qt::green);
    painter.fillRect(temp_offset_label_rect, Qt::red);
    */

    QFont font = painter.font();
    font.setPixelSize(15 * m_scale);
    painter.setFont(font);

    painter.setPen(Qt::black);

    QString installation_angle_value = QString::number(0.0f, 'f', 1) + " deg";
    QString tilt_offset_value = "Pitch: " + QString::number(0.0f, 'f', 1) + " deg, Roll: " + QString::number(0.0f, 'f', 1) + " deg";
    QString temp_offset_value = QString::number(0.0f, 'f', 1) + QString::fromUtf8("°C");

    painter.drawText(angle_label_rect, Qt::AlignVCenter, "Installation angle: " + installation_angle_value);
    painter.drawText(sea_test_number_label_rect, Qt::AlignVCenter, "Number of SEA TEST calibration points: " + QString::number(2));
    painter.drawText(auto_mode_label_rect, Qt::AlignVCenter, "Auto mode: ");
    painter.drawText(tilt_offset_label_rect, Qt::AlignVCenter, "TILT OFFSET: " + tilt_offset_value);
    painter.drawText(temp_offset_label_rect, Qt::AlignVCenter, "TEMP OFFSET: " + temp_offset_value);

    QRect calibration_status_label_rect(x_ff + 0.0125f * w_ff, y_ss, 0.975f * w_ff, 0.3f * h_ff);
    QRect reason_label_rect(x_ff + 0.0125f * w_ff, y_ss + 0.3f * h_ff, 0.975f * w_ff, 0.45f * h_ff);
    QRect suggestion_label_rect(x_ff + 0.0125f * w_ff, y_ss + 0.75f * h_ff, 0.975f * w_ff, 0.75f * h_ff);

    // Uncomment for label placement help
    //painter.fillRect(calibration_status_label_rect, Qt::red);
    //painter.fillRect(reason_label_rect, Qt::green);
    //painter.fillRect(suggestion_label_rect, Qt::blue);

    // Fix for 100% cpu usage
    if ((m_calibration_status_label->size() != calibration_status_label_rect.size()) || (m_calibration_status_label->pos() != calibration_status_label_rect.topLeft()))
    {
        m_calibration_status_label->resize(calibration_status_label_rect.size());
        m_calibration_status_label->move(calibration_status_label_rect.topLeft());
        m_calibration_status_label->setFont(font);
        m_calibration_status_label->setWordWrap(true);
        m_calibration_status_label->setAlignment(Qt::AlignTop);
        m_calibration_status_label->setMargin(1);
    }

    m_calibration_status_label->setText("Speed calibration Status: \n- ");

    if ((m_reason_label->size() != reason_label_rect.size()) || (m_reason_label->pos() != reason_label_rect.topLeft()))
    {
        m_reason_label->move(reason_label_rect.topLeft());
        m_reason_label->resize(reason_label_rect.size());
        m_reason_label->setFont(font);
        m_reason_label->setWordWrap(true);
        m_reason_label->setAlignment(Qt::AlignTop);
        m_reason_label->setMargin(1);
    }

    m_reason_label->setText("Reason: \n- ");

    if ((m_suggestion_label->size() != suggestion_label_rect.size()) || (m_suggestion_label->pos() != suggestion_label_rect.topLeft()))
    {
        m_suggestion_label->move(suggestion_label_rect.topLeft());
        m_suggestion_label->resize(suggestion_label_rect.size());

        m_suggestion_label->setFont(font);
        m_suggestion_label->setWordWrap(true);
        m_suggestion_label->setAlignment(Qt::AlignTop);
        m_suggestion_label->setMargin(1);
    }

    m_suggestion_label->setText("Suggestion: \n- ");
}
