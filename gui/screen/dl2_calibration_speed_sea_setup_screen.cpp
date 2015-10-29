#include "dl2_calibration_speed_sea_setup_screen.h"

void Dl2CalibrationSpeedSeaSetupScreen::init()
{
    // TODO: Change to other default set of values
    m_meas_stw = std::numeric_limits<float>::max();
    m_meas_sog = std::numeric_limits<float>::max();
    m_calc_real_speed = std::numeric_limits<float>::max();
    m_gps_avg = std::numeric_limits<float>::max();
    m_gps_min = std::numeric_limits<float>::max();
    m_gps_max = std::numeric_limits<float>::max();
    //m_est_dist = std::numeric_limits<float>::max();

    m_distance_water = std::numeric_limits<float>::max();
    m_distance_ground = std::numeric_limits<float>::max();

    m_leg_one_sog_valid_percentage = 0.0f;
    m_leg_one_stw_valid_percentage = 0.0f;
    m_leg_two_sog_valid_percentage = 0.0f;
    m_leg_two_stw_valid_percentage = 0.0f;
}

bool Dl2CalibrationSpeedSeaSetupScreen::displayMeasurementsGps() const
{
    switch (m_state)
    {
        case IDLE:
        case START_LEG_1:
            return false;

        default:
            return true;
    }
}

bool Dl2CalibrationSpeedSeaSetupScreen::orientationRight() const
{
    if ((m_state < START_LEG_2) || (m_state == COMPLETE))
    {
        return true;
    }

    return false;
}

QString Dl2CalibrationSpeedSeaSetupScreen::getValueString(qreal value, int decimal)
{
    if (value == std::numeric_limits<float>::max())
    {
        return "-.-";
    }

    return QString::number(value, 'f', decimal);
}

QString Dl2CalibrationSpeedSeaSetupScreen::getInstructionString() const
{
    switch(m_state)
    {
        case IDLE:
            return QString("Plot a leg that will take about 3 minutes on the chart, measure the distance and add it  where it says 'Enter leg distance'.");

        case START_LEG_1:
            return QString("Sail to the start of the leg and sail the leg at a constant speed. Follow the track, not heading.");

        case STOP_LEG_1:
            return QString("Press the stop button, when you cross the end of the leg on the chart.");

        case START_LEG_2:
            return QString("Turn the vessel and sail the same leg (slightly to one side to avoid your wake) in the opposite direction at the same speed as the first leg.");

        case STOP_LEG_2:
            return QString("Press stop when you reach the end of the leg.");

        default:
            return QString("");
    }
}

QColor Dl2CalibrationSpeedSeaSetupScreen::getValidityColour(qreal value) const
{
    if (value < 30.0f)
    {
        return Qt::red;
    }

    if (value > 70.0f)
    {
        return Qt::green;
    }

    return QColor(255, 128, 0);
}

void Dl2CalibrationSpeedSeaSetupScreen::drawArrow(QPainter& painter, int x, int y, int w, int h, const QColor &color)
{
    painter.save();
    painter.translate(x, y);

    QPoint p1(0, h / 2);
    QPoint p2(w, -h / 2);

    painter.fillRect(QRect(p1, p2), color);

    painter.translate(w, 0);

    QPolygon polygon(4);
    polygon[0] = QPoint(2 * h, 0);
    polygon[1] = QPoint(0, -2 * h);
    polygon[2] = QPoint(0, 2 * h);
    polygon[3] = QPoint(2 * h, 0);
    QPainterPath path;
    path.addPolygon(polygon);

    if (w < 0)
    {
        painter.rotate(180.0f);
    }

    painter.fillPath(path, color);
    painter.restore();
}

void Dl2CalibrationSpeedSeaSetupScreen::updateState()
{
    switch (m_state)
    {
        case IDLE:
            m_cancel_button->hide();
            m_save_button->hide();
            m_discard_button->hide();
            m_graph->hide();

            m_left_button->setEnabled(false);
            m_right_button->setEnabled(false);
            m_leg_distance_button->setEnabled(true);

            m_left_button->setBorderColor(Qt::black);
            m_left_button->setBackgroundColor(QColor(100, 100, 100));

            m_right_button->setBorderColor(Qt::black);
            m_right_button->setBackgroundColor(QColor(100, 100, 100));

            m_leg_distance_button->setBackgroundColor(Qt::white);
            m_leg_distance_button->setBorderColor(QColor(230, 170, 30));

            m_left_button->setTitle("Start Leg 1");
            m_right_button->setTitle("Stop Leg 1");
            m_leg_distance_button->setTitle("Enter leg distance");

            m_text_edit->show();
            init();

            break;

        case START_LEG_1:
            m_cancel_button->show();
            m_cancel_button->setEnabled(true);

            m_cancel_button->setBorderColor(QColor(230, 170, 30));
            m_cancel_button->setBackgroundColor(Qt::white);

            m_left_button->setEnabled(true);
            m_leg_distance_button->setEnabled(false);

            m_left_button->setBorderColor(QColor(230, 170, 30));
            m_left_button->setBackgroundColor(Qt::white);

            m_leg_distance_button->setBackgroundColor(QColor(100, 100, 100));
            m_leg_distance_button->setBorderColor(QColor(230, 170, 30));

            break;

        case STOP_LEG_1:
            m_left_button->setEnabled(false);
            m_right_button->setEnabled(true);

            m_left_button->setBorderColor(Qt::black);
            m_left_button->setBackgroundColor(QColor(100, 100, 100));

            m_right_button->setBorderColor(QColor(230, 170, 30));
            m_right_button->setBackgroundColor(Qt::white);

            m_distance_water = 0.0f;
            m_distance_ground = 0.0f;

            break;

        case PARTIAL:
            m_save_button->show();
            m_save_button->setTitle("Save Leg 1");
            m_discard_button->show();

            m_left_button->setEnabled(false);
            m_cancel_button->setEnabled(false);

            m_left_button->setBorderColor(Qt::black);
            m_left_button->setBackgroundColor(QColor(100, 100, 100));

            m_right_button->setBorderColor(Qt::black);
            m_right_button->setBackgroundColor(QColor(100, 100, 100));

            m_cancel_button->setBorderColor(Qt::black);
            m_cancel_button->setBackgroundColor(QColor(100, 100, 100));

            break;

        case START_LEG_2:
            m_left_button->setTitle("Stop Leg 2");
            m_right_button->setTitle("Start Leg 2");

            break;

        case STOP_LEG_2:
            m_left_button->setEnabled(true);
            m_right_button->setEnabled(false);

            m_left_button->setBorderColor(QColor(230, 170, 30));
            m_left_button->setBackgroundColor(Qt::white);

            m_right_button->setBorderColor(Qt::black);
            m_right_button->setBackgroundColor(QColor(100, 100, 100));

            m_distance_water = 0.0f;
            m_distance_ground = 0.0f;

            break;

        case COMPLETE:
            m_save_button->show();
            m_discard_button->show();
            m_graph->show();

            m_save_button->setTitle("Save");

            m_left_button->setEnabled(false);
            m_cancel_button->setEnabled(false);

            m_left_button->setBorderColor(Qt::black);
            m_left_button->setBackgroundColor(QColor(100, 100, 100));

            m_cancel_button->setBorderColor(Qt::black);
            m_cancel_button->setBackgroundColor(QColor(100, 100, 100));

            m_text_edit->hide();

            /*
            SpeedCalibrationPoint x;
            x.setRealSpeed(m_calc_real_speed);
            x.setMeasuredSOG(m_meas_sog);
            x.setMeasuredSTW(m_meas_stw);
            m_graph->setPreviewValue(x);
            */

            break;
    }

    m_text_edit->setText(getInstructionString());

    update();
}

Dl2CalibrationSpeedSeaSetupScreen::Dl2CalibrationSpeedSeaSetupScreen(QWidget* parent) : Dl2CalibrationSpeedSetupScreen(parent)
{
    m_title_widget->setTitle("Sea setup");

    m_graph = new CalibrationGraphWidget(this, m_graph_size);
    m_text_edit = new QTextEdit(this);
    m_text_edit->setDisabled(true);

    int font_pixel_size = 12;

    m_left_button = new LegButton(this, m_left_button_size, "Start Leg 1");
    m_left_button->setFontPixelSize(font_pixel_size);

    m_right_button = new LegButton(this, m_right_button_size, "Stop Leg 1");
    m_right_button->setFontPixelSize(font_pixel_size);

    m_leg_distance_button = new LegButton(this, m_leg_distance_button_size, "Enter leg distance");
    m_leg_distance_button->setFontPixelSize(1.25f * font_pixel_size);

    m_cancel_button = new LegButton(this, m_cancel_button_size, "Cancel");
    m_cancel_button->setFontPixelSize(font_pixel_size);

    m_save_button = new LegButton(this, m_save_button_size, "Save");
    m_save_button->setFontPixelSize(1.5f * font_pixel_size);

    m_discard_button = new LegButton(this, m_discard_button_size, "Discard");
    m_discard_button->setFontPixelSize(1.5f * font_pixel_size);

    updateState();
}

void Dl2CalibrationSpeedSeaSetupScreen::setupLayout()
{
    Dl2CalibrationSpeedSetupScreen::setupLayout();

    QSize text_edit_size(m_text_edit_size.width() * m_width_scale, m_text_edit_size.height() * m_height_scale);
    QSize left_button_size(m_left_button_size.width() * m_width_scale, m_left_button_size.height() * m_height_scale);
    QSize right_button_size(m_right_button_size.width() * m_width_scale, m_right_button_size.height() * m_height_scale);
    QSize leg_distance_button_size(m_leg_distance_button_size.width() * m_width_scale, m_leg_distance_button_size.height() * m_height_scale);
    QSize cancel_button_size(m_cancel_button_size.width() * m_width_scale, m_cancel_button_size.height() * m_height_scale);
    QSize save_button_size(m_save_button_size.width() * m_width_scale, m_save_button_size.height() * m_height_scale);
    QSize discard_button_size(m_discard_button_size.width() * m_width_scale, m_discard_button_size.height() * m_height_scale);

    QPoint text_edit_pos(m_text_edit_pos.x() * m_width_scale, m_text_edit_pos.y() * m_height_scale);
    QPoint left_button_pos(m_left_button_pos.x() * m_width_scale, m_left_button_pos.y() * m_height_scale);
    QPoint right_button_pos(m_right_button_pos.x() * m_width_scale, m_right_button_pos.y() * m_height_scale);
    QPoint leg_distance_button_pos(m_leg_distance_button_pos.x() * m_width_scale, m_leg_distance_button_pos.y() * m_height_scale);
    QPoint cancel_button_pos(m_cancel_button_pos.x() * m_width_scale, m_cancel_button_pos.y() * m_height_scale);
    QPoint save_button_pos(m_save_button_pos.x() * m_width_scale, m_save_button_pos.y() * m_height_scale);
    QPoint discard_button_pos(m_discard_button_pos.x() * m_width_scale, m_discard_button_pos.y() * m_height_scale);

    m_left_button->resize(left_button_size);
    m_right_button->resize(right_button_size);
    m_leg_distance_button->resize(leg_distance_button_size);
    m_cancel_button->resize(cancel_button_size);
    m_save_button->resize(save_button_size);
    m_discard_button->resize(discard_button_size);

    m_left_button->move(left_button_pos);
    m_right_button->move(right_button_pos);
    m_leg_distance_button->move(leg_distance_button_pos);
    m_cancel_button->move(cancel_button_pos);
    m_save_button->move(save_button_pos);
    m_discard_button->move(discard_button_pos);

    int font_pixel_size = 18.0f * m_scale;
    QString css_string = QString("color: green;") +
                         "\nfont: " + QString::number(font_pixel_size) + "px;"
                         + QString("background-color: black;");

    m_text_edit->setStyleSheet(css_string);
    m_text_edit->resize(text_edit_size);
    m_text_edit->move(text_edit_pos);
}

void Dl2CalibrationSpeedSeaSetupScreen::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    int x_ff = 420 * m_width_scale;
    int y_ff = (5 + 24) * m_height_scale;
    int w_ff = 370 * m_width_scale;
    int h_ff = (220 - 24) * m_height_scale;

    int border = 8 * m_scale;

    QRect outer_rect(x_ff - border / 2, y_ff - border / 2, w_ff + border, h_ff + border);
    QRect inner_rect(x_ff, y_ff, w_ff, h_ff);

    painter.fillRect(outer_rect, QColor(230, 170, 30));
    painter.fillRect(inner_rect, QColor(100, 100, 100));

    //qreal y_v = 90 * m_height_scale;
    qreal x_v = x_ff + 10 * m_width_scale;

    if ((m_state == STOP_LEG_1) || (m_state == STOP_LEG_2))
    {
        if(orientationRight() == true)
        {
            x_v = x_ff + 10 * m_width_scale + (w_ff - 84 * m_width_scale)*m_distance_ground/m_leg_distance;

            if(x_v > x_ff + 10 * m_width_scale + (w_ff - 84 * m_width_scale))
                x_v = x_ff + 10 * m_width_scale + (w_ff - 84 * m_width_scale);
            /*if(m_distance_ground > 7*m_leg_distance/8)
                x_v = x_v + (w_ff - 84 * width_scale);
            else if(m_distance_ground > 5*m_leg_distance/8)
                x_v = x_v + 3*(w_ff - 84 * width_scale) / 4;

            else if(m_distance_ground > 3*m_leg_distance/8)
                x_v = x_v + (w_ff - 84 * width_scale) / 2;

            else if(m_distance_ground > m_leg_distance/8)
                x_v = x_v + (w_ff - 84 * width_scale) / 4;*/
        }
        else
        {
            x_v = x_ff + (w_ff - 66 * m_width_scale)*(1-m_distance_ground/m_leg_distance);

            if(x_v < x_ff + 18 * m_width_scale)
                x_v = x_ff + 18 * m_width_scale;
            /*if(m_distance_ground > 7*m_leg_distance/8)
                x_v = x_ff + 10 * width_scale;
            else if(m_distance_ground > 5*m_leg_distance/8)
                x_v = x_v + (w_ff - 84 * width_scale) / 4;

            else if(m_distance_ground > 3*m_leg_distance/8)
                x_v = x_v + (w_ff - 84 * width_scale) / 2;

            else if(m_distance_ground > m_leg_distance/8)
                x_v = x_v + 3*(w_ff - 84 * width_scale) / 4;

            else
                x_v = x_v + (w_ff - 84 * width_scale);*/
        }
    }

    if ((m_state == START_LEG_2) || (m_state == PARTIAL))
    {
        x_v = x_ff + w_ff - 10 * m_width_scale - 56 * m_width_scale;
    }

    if (orientationRight() == true)
    {
        drawArrow(painter, x_ff + 10 * m_width_scale, 129 * m_height_scale, w_ff - 28 * m_width_scale, 4 * m_height_scale, QColor(50, 209, 232));

        //painter.drawImage(x_v, y_v + 24 * height_scale, m_dimming_palette_controller.getSeaCalVessel());
    }
    else
    {
        drawArrow(painter, x_ff + w_ff - 10 * m_width_scale, 129 * m_height_scale, -(w_ff - 28 * m_width_scale), 4 * m_height_scale, QColor(50, 209, 232));

        //painter.drawImage(x_v, y_v + 24 * height_scale, m_dimming_palette_controller.getSeaCalFlippedVessel());
    }

    drawArrow(painter, x_ff + 20 * m_width_scale, 64 * m_height_scale, w_ff - 38 * m_width_scale, 4 * m_height_scale, Qt::white);
    drawArrow(painter, x_ff + w_ff - 18 * m_width_scale, 64 * m_height_scale, -(w_ff - 38 * m_width_scale), 4 * m_height_scale, Qt::white);

    if (displayMeasurementsGps() == true)
    {
        int m_border = 4 * m_scale;
        int x_mf = x_ff - border / 2 + m_border / 2;
        int y_mf = 260 * m_height_scale + m_border / 2;
        int w_mf = 210 * m_width_scale;
        int h_mf = 99 * m_height_scale - m_border / 2;

        QRect meas_outer_rect(x_mf - m_border / 2, y_mf - m_border / 2, w_mf + m_border, h_mf + m_border);
        QRect meas_inner_rect(x_mf, y_mf, w_mf, h_mf);

        painter.fillRect(meas_outer_rect, QColor(193, 143, 25));
        painter.fillRect(meas_inner_rect, Qt::black);

        int y_gf = 360 * m_height_scale;
        int h_gf = 0.66f * h_mf;

        QRect gps_outer_rect(x_mf - m_border / 2, y_gf - m_border / 2, w_mf + m_border, h_gf + m_border);
        QRect gps_inner_rect(x_mf, y_gf, w_mf, h_gf);

        painter.fillRect(gps_outer_rect, QColor(193, 143, 25));
        painter.fillRect(gps_inner_rect, Qt::black);

        QRect avg_meas_stw_label_rect(x_mf + 0.025f * w_mf, y_mf, 0.675f * w_mf, 0.33f * h_mf);
        QRect avg_meas_stw_value_rect(x_mf + 0.75f * w_mf, y_mf, 0.225f * w_mf, 0.33f * h_mf);

        QRect avg_meas_sog_label_rect(x_mf + 0.025f * w_mf, y_mf + 0.33f * h_mf, 0.675f * w_mf, 0.33f * h_mf);
        QRect avg_meas_sog_value_rect(x_mf + 0.75f * w_mf, y_mf + 0.33f * h_mf, 0.225f * w_mf, 0.33f * h_mf);

        QRect calc_real_speed_label_rect(x_mf + 0.025f * w_mf, y_mf + 0.66f * h_mf, 0.675f * w_mf, 0.33f * h_mf);
        QRect calc_real_speed_value_rect(x_mf +  0.75f * w_mf, y_mf + 0.66f * h_mf, 0.225f * w_mf, 0.33f * h_mf);

        QFont font = painter.font();
        font.setPixelSize(15 * m_scale);
        painter.setFont(font);

        /* Uncomment for label placement help
        painter.fillRect(avg_meas_stw_label_rect, QColor(50, 207, 230));
        painter.fillRect(avg_meas_stw_value_rect, QColor(50, 207, 230));

        painter.fillRect(avg_meas_sog_label_rect, QColor(138, 78, 16));
        painter.fillRect(avg_meas_sog_value_rect, QColor(138, 78, 16));

        painter.fillRect(calc_real_speed_label_rect, QColor(50, 209, 50));
        painter.fillRect(calc_real_speed_value_rect, QColor(50, 209, 50));
        */

        painter.setPen(QColor(50, 207, 230));
        painter.drawText(avg_meas_stw_label_rect,  Qt::AlignVCenter, "Avg Meas STW: ");
        painter.drawText(avg_meas_stw_value_rect,  Qt::AlignVCenter | Qt::AlignRight, getValueString(m_meas_stw));

        painter.setPen(Qt::red);
        painter.drawText(avg_meas_sog_label_rect, Qt::AlignVCenter, "Avg Meas SOG: ");
        painter.drawText(avg_meas_sog_value_rect, Qt::AlignVCenter | Qt::AlignRight, getValueString(m_meas_sog));

        painter.setPen(QColor(50, 209, 50));
        painter.drawText(calc_real_speed_label_rect, Qt::AlignVCenter, "Calcul Real Speed: ");
        painter.drawText(calc_real_speed_value_rect, Qt::AlignVCenter | Qt::AlignRight, getValueString(m_calc_real_speed));

        QRect gps_label_rect(x_mf + 0.025f * w_mf, y_gf, 0.2f * w_mf, 0.5f * h_gf);

        QRect gps_avg_label_rect(x_mf +  0.525f * w_mf, y_gf, 0.2f * w_mf, 0.5f * h_gf);
        QRect gps_avg_value_rect(x_mf +  0.75f * w_mf, y_gf, 0.225f * w_mf, 0.5f * h_gf);

        QRect gps_min_label_rect(x_mf + 0.025f * w_mf, y_gf + 0.5f * h_gf, 0.2f * w_mf, 0.5f * h_gf);
        QRect gps_min_value_rect(x_mf + 0.25f * w_mf, y_gf + 0.5f * h_gf, 0.225f * w_mf, 0.5f * h_gf);

        QRect gps_max_label_rect(x_mf +  0.525f * w_mf, y_gf + 0.5f * h_gf, 0.2f * w_mf, 0.5f * h_gf);
        QRect gps_max_value_rect(x_mf +  0.75f * w_mf, y_gf + 0.5f * h_gf, 0.225f * w_mf, 0.5f * h_gf);

        /* Uncomment for label placement help
        painter.fillRect(gps_label_rect, QColor(50, 209, 50));

        painter.fillRect(gps_avg_label_rect, QColor(50, 209, 50));
        painter.fillRect(gps_avg_value_rect, QColor(50, 209, 50));

        painter.fillRect(gps_min_label_rect, QColor(50, 209, 50));
        painter.fillRect(gps_min_value_rect, QColor(50, 209, 50));

        painter.fillRect(gps_max_label_rect, QColor(50, 209, 50));
        painter.fillRect(gps_max_value_rect, QColor(50, 209, 50));
        */

        painter.drawText(gps_label_rect, Qt::AlignVCenter, "GPS");

        painter.drawText(gps_avg_label_rect, Qt::AlignVCenter, "Avg:");
        painter.drawText(gps_avg_value_rect, Qt::AlignVCenter | Qt::AlignRight, getValueString(m_gps_avg));

        painter.drawText(gps_min_label_rect, Qt::AlignVCenter, "Min:");
        painter.drawText(gps_min_value_rect, Qt::AlignVCenter | Qt::AlignRight, getValueString(m_gps_min));

        painter.drawText(gps_max_label_rect, Qt::AlignVCenter, "Max:");
        painter.drawText(gps_max_value_rect, Qt::AlignVCenter | Qt::AlignRight, getValueString(m_gps_max));
    }

    if ((m_state == STOP_LEG_1) || (m_state == STOP_LEG_2) || (m_state == START_LEG_2) || (m_state == COMPLETE))
    {
        qreal x_ed = 525 * m_width_scale;
        qreal y_ed = 120 * m_height_scale;
        qreal w_ed = 160 * m_width_scale;
        qreal h_ed = 35 * m_height_scale;

        QRect est_dist_label_rect(x_ed, y_ed + 24 * m_height_scale, w_ed, h_ed);
        QRect est_dist_value_rect(x_ed, y_ed + h_ed + 24 * m_height_scale, w_ed, 0.5f * h_ed);

        QFont font = painter.font();
        font.setPixelSize(15 * m_scale);
        painter.setFont(font);

        painter.setPen(QColor(50, 207, 230));
        painter.drawText(est_dist_label_rect, Qt::AlignCenter, "Water: " + getValueString(m_distance_water, 3) + " NM");

        painter.setPen(Qt::red);
        painter.drawText(est_dist_value_rect, Qt::AlignCenter, "Ground: " + getValueString(m_distance_ground, 3) + " NM");
    }

    if ((m_state == PARTIAL) || (m_state == COMPLETE))
    {
        int x_s = x_ff;
        int y_s = 232 * m_height_scale;
        int w_s = w_ff;
        int h_s = 25 * m_height_scale;

        QRect status_rect(x_s, y_s, w_s, h_s);

        // Uncomment for label placement help
        // painter.fillRect(status_rect, Qt::white);

        painter.setPen(Qt::white);

        QFont font = painter.font();
        font.setPixelSize(15 * m_scale);
        painter.setFont(font);

        QString status_string = "New Calibration point obtained from both legs";

        if (m_state == PARTIAL)
        {
            status_string = "New Calibration point obtained from Leg 1";
        }

        painter.drawText(status_rect, Qt::AlignVCenter, status_string);
    }

    QRect leg_one_title_rect(width() - 346 * m_width_scale, height() - 54 * m_height_scale, 173 * m_width_scale, 18 * m_height_scale);
    QRect leg_one_sog_rect(width() - 346 * m_width_scale, height() - 36 * m_height_scale, 173 * m_width_scale, 18 * m_height_scale);
    QRect leg_one_stw_rect(width() - 346 * m_width_scale, height() - 18 * m_height_scale, 173 * m_width_scale, 18 * m_height_scale);

    QRect leg_two_title_rect(width() - 173 * m_width_scale, height() - 54 * m_height_scale, 173 * m_width_scale, 18 * m_height_scale);
    QRect leg_two_sog_rect(width() - 173 * m_width_scale, height() - 36 * m_height_scale, 173 * m_width_scale, 18 * m_height_scale);
    QRect leg_two_stw_rect(width() - 173 * m_width_scale, height() - 18 * m_height_scale, 173 * m_width_scale, 18 * m_height_scale);

    // Uncomment for label placement help
    // painter.fillRect(leg_one_rect, Qt::red);
    // painter.fillRect(leg_two_rect, Qt::green);

    QFont font = painter.font();
    font.setPixelSize(15 * m_scale);
    painter.setFont(font);

    if ((m_state == STOP_LEG_1) || (m_state == START_LEG_2) || (m_state == STOP_LEG_2) || (m_state == COMPLETE) || (m_state == PARTIAL))
    {
        painter.setPen(Qt::white);
        painter.drawText(leg_one_title_rect, Qt::AlignHCenter, "Leg One Validity:");

        painter.setPen(getValidityColour(m_leg_one_sog_valid_percentage));
        painter.drawText(leg_one_sog_rect, Qt::AlignHCenter, "SOG " + QString::number(m_leg_one_sog_valid_percentage, 'f', 1) + "%");

        painter.setPen(getValidityColour(m_leg_one_stw_valid_percentage));
        painter.drawText(leg_one_stw_rect, Qt::AlignHCenter, "STW " + QString::number(m_leg_one_stw_valid_percentage, 'f', 1) + "%");
    }

    if ((m_state == STOP_LEG_2) || (m_state == COMPLETE))
    {
        painter.setPen(Qt::white);
        painter.drawText(leg_two_title_rect, Qt::AlignHCenter, "Leg Two Validity:");

        painter.setPen(getValidityColour(m_leg_two_sog_valid_percentage));
        painter.drawText(leg_two_sog_rect, Qt::AlignHCenter, "SOG " + QString::number(m_leg_two_sog_valid_percentage, 'f', 1) + "%");

        painter.setPen(getValidityColour(m_leg_two_stw_valid_percentage));
        painter.drawText(leg_two_stw_rect, Qt::AlignHCenter, "STW " + QString::number(m_leg_two_stw_valid_percentage, 'f', 1) + "%");
    }
}
