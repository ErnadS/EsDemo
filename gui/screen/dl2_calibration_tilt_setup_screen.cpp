#include "dl2_calibration_tilt_setup_screen.h"

Dl2CalibrationTiltSetupScreen::Dl2CalibrationTiltSetupScreen(QWidget* parent) : SetupScreen(parent)
{
    m_title_widget->setTitle("Tilt");

    m_pitch_button = new LegButton(this, m_pitch_button_size, "NULL");
    m_pitch_button->setFontPixelSize(24);
    m_pitch_button->setBackgroundColor(QColor(218, 218, 218));
    m_pitch_button->setBorderColor(QColor(144, 255, 112));

    m_roll_button = new LegButton(this, m_roll_button_size, "NULL");
    m_roll_button->setFontPixelSize(24);
    m_roll_button->setBackgroundColor(QColor(218, 218, 218));
    m_roll_button->setBorderColor(QColor(144, 255, 112));

    m_pitch_offset_widget = new UpDownWidget(this, m_pitch_offset_widget_size, "PITCH\nOFFSET", "deg");
    m_pitch_offset_widget->setBackgroundColor(QColor(218, 218, 218));
    m_pitch_offset_widget->setBorderColor(QColor(144, 255, 112));

    m_roll_offset_widget = new UpDownWidget(this, m_roll_offset_widget_size, "ROLL\nOFFSET", "deg");
    m_roll_offset_widget->setBackgroundColor(QColor(218, 218, 218));
    m_roll_offset_widget->setBorderColor(QColor(144, 255, 112));

    setupLayout();
}

void Dl2CalibrationTiltSetupScreen::setupLayout()
{
    SetupScreen::setupLayout();

    m_pitch_button->resize(m_pitch_button_size.width() * m_width_scale, m_pitch_button_size.height() * m_height_scale);
    m_roll_button->resize(m_roll_button_size.width() * m_width_scale, m_roll_button_size.height() * m_height_scale);

    m_pitch_button->move(m_pitch_button_pos.x() * m_width_scale, m_pitch_button_pos.y() * m_height_scale);
    m_roll_button->move(m_roll_button_pos.x() * m_width_scale, m_roll_button_pos.y() * m_height_scale);

    m_pitch_offset_widget->resize(m_pitch_offset_widget_size.width() * m_width_scale, m_pitch_offset_widget_size.height() * m_height_scale);
    m_roll_offset_widget->resize(m_roll_offset_widget_size.width() * m_width_scale, m_roll_offset_widget_size.height() * m_height_scale);

    m_pitch_offset_widget->move(m_pitch_offset_widget_pos.x() * m_width_scale, m_pitch_offset_widget_pos.y() * m_height_scale);
    m_roll_offset_widget->move(m_roll_offset_widget_pos.x() * m_width_scale, m_roll_offset_widget_pos.y() * m_height_scale);
}

void Dl2CalibrationTiltSetupScreen::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QPen pen(QColor(204, 255, 153));
    painter.setPen(pen);

    QFont font = painter.font();
    font.setPixelSize(20 * m_scale);
    painter.setFont(font);

    QImage angle_scale(":/angleScale_93_20.png");
    QImage pitch_image(":/vessel_3_yellow.png");

    angle_scale = angle_scale.scaled(angle_scale.width() * m_width_scale, angle_scale.height() * m_height_scale);
    pitch_image = pitch_image.scaled(pitch_image.width() * m_width_scale, pitch_image.height() * m_height_scale);

    /////////////////////////////////////////////////////////////////////////////
    // Angle scale image over pitch image (93x20 pix)
    /////////////////////////////////////////////////////////////////////////////
    // Start pitch painting in x = 125 and y = 141
    // "Scale" image width = 93
    // "pitch" image (boat) width = 165)
    //  Move "scale" image to be simetrical with pitch image:
    painter.drawImage(161 * m_width_scale, 131 * m_height_scale, angle_scale);  // 125 + (165 - 93)/2 = 161

    /////////////////////////////////////////////////////////////////////////////
    // Pitch image
    /////////////////////////////////////////////////////////////////////////////
    qreal rotate_angle_pitch = m_pitch;
    painter.translate((125 + 165/2) * m_width_scale, (170 + 65) * m_height_scale); // translate to center/bottom of the boat image
    painter.rotate(rotate_angle_pitch);
    painter.drawImage((-165/2) * m_width_scale, -38 * m_height_scale, pitch_image);  // 165*38 pix
    painter.rotate(-1.0f * rotate_angle_pitch);
    painter.translate((-125 - 165/2) * m_width_scale, (-170 - 65) * m_height_scale);

    painter.setPen(Qt::white);

    painter.drawLine((125 + 165/2) * m_width_scale, (170 + 65) * m_height_scale, (125 + 165/2 + (65 + 39)* qSin(rotate_angle_pitch * M_PI/180)) * m_width_scale, (170 + 65 - (65 + 39)* qCos(rotate_angle_pitch* M_PI/180)) * m_height_scale);

    painter.setPen(Qt::white);
    painter.drawText(135 * m_width_scale, 170 * m_height_scale, "30");
    painter.drawText(257 * m_width_scale, 170 * m_height_scale, "30");

    // ROLL
    /////////////////////////////////////////////////////////////////////////////
    // Angle scale image
    /////////////////////////////////////////////////////////////////////////////

    painter.translate(556 * m_width_scale, 131 * m_height_scale); // move to roll angle scale image top/left
    painter.drawImage(0, 0, angle_scale);

    QImage roll_image(":/roll_57_98.png");
    roll_image = roll_image.scaled(roll_image.width() * m_width_scale, roll_image.height() * m_height_scale);

    qreal rotate_angle_roll = m_roll;
    painter.translate(46 * m_width_scale, 94 * m_height_scale);  // move to ration point
    painter.rotate(rotate_angle_roll);  // rotate for roll angle
    painter.drawImage(-28 * m_width_scale, -78 * m_height_scale, roll_image);
    painter.setPen(Qt::blue);  // light blue
    painter.rotate(-1* rotate_angle_roll);
    painter.drawLine(-35 * m_width_scale, 0, 35 * m_width_scale, 0); // draw "water" line
    painter.translate((-556 -68) * m_width_scale, (-131 -88) * m_height_scale); // translate back

    painter.setPen(Qt::white);
    painter.drawText(550 * m_width_scale, 170 * m_height_scale, "30");
    painter.drawText(672 * m_width_scale, 170 * m_height_scale, "30");

    font.setPixelSize(24 * m_scale);
    painter.setFont(font);

    QRect pitch_upper_rect(222 * m_width_scale - width() / 4, 245 * m_height_scale, width() / 2, 120 * m_height_scale);
    //painter.fillRect(pitch_upper_rect, Qt::red);

    QString pitch_upper_string = "PITCH " + QString::number(m_pitch, 'f', 1) + " deg\nAvg " +  QString::number(m_avg_pitch_offset, 'f', 1) + " deg\nMax " + QString::number(m_max_pitch_offset, 'f', 1) + " deg\nMin " + QString::number(m_min_pitch_offset, 'f', 1) + " deg\n";
    painter.drawText(pitch_upper_rect, Qt::AlignHCenter, pitch_upper_string);

    QRect roll_upper_rect(622 * m_width_scale - width() / 4, 245 * m_height_scale, width() / 2, 120 * m_height_scale);
    //painter.fillRect(roll_upper_rect, Qt::red);

    QString roll_upper_string = "ROLL " + QString::number(m_roll, 'f', 1) + " deg\nAvg " + QString::number(m_avg_roll_offset, 'f', 1) + " deg\nMax " + QString::number(m_max_roll_offset, 'f', 1) + " deg\nMin " + QString::number(m_min_roll_offset, 'f', 1) + " deg\n";
    painter.drawText(roll_upper_rect, Qt::AlignHCenter, roll_upper_string);
}
