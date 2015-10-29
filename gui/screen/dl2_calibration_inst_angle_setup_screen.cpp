#include "dl2_calibration_inst_angle_setup_screen.h"

void Dl2CalibrationInstAngleSetupScreen::drawArrow(QPainter& painter, const qreal& angle)
{
    painter.rotate(angle);
    int h = 40;

    QPen pen = painter.pen();
    pen.setStyle(Qt::DashLine);
    painter.setPen(pen);
    painter.drawLine(0, 0, 0, -h * m_height_scale);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);

    QPolygon polygon(4);
    polygon[0] = QPoint(0, -h * m_height_scale);
    polygon[1] = QPoint(-7 * m_width_scale, (-h + 12) * m_height_scale);
    polygon[2] = QPoint(7 * m_width_scale, (-h + 12) * m_height_scale);
    polygon[3] = QPoint(0, -h * m_height_scale);
    QPainterPath path;
    path.addPolygon(polygon);

    QBrush brush(pen.color());
    painter.fillPath(path, brush);
    painter.drawPath(path);
    painter.rotate(-angle);
}

QString Dl2CalibrationInstAngleSetupScreen::getAngleString() const
{
    return "Row 1\nRow 2\nRow 3\nRow 4\nRow 5";
}

qreal Dl2CalibrationInstAngleSetupScreen::normalizeAngle(qreal angle) const
{
    if (angle < 180.0f)
    {
        return angle;
    }
    else
    {
        return angle - 360.0f;
    }
}

Dl2CalibrationInstAngleSetupScreen::Dl2CalibrationInstAngleSetupScreen(QWidget* parent) : SetupScreen(parent)
{
    m_title_widget->setTitle("Inst angle");

    m_recommended_button = new LegButton(this, m_recommended_button_size, "Recommended -.- deg");
    m_recommended_button->setFontPixelSize(30);
    m_recommended_button->setBackgroundColor(QColor(218, 218, 218));
    m_recommended_button->setBorderColor(QColor(144, 255, 112));

    m_installation_angle_widget = new UpDownWidget(this, m_installation_angle_widget_size, "Installation\nangle", "deg");
    m_installation_angle_widget->setBackgroundColor(QColor(218, 218, 218));
    m_installation_angle_widget->setBorderColor(QColor(144, 255, 112));

    setupLayout();
}

void Dl2CalibrationInstAngleSetupScreen::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QColor stw_color = QColor(147, 205, 255);
    QColor sog_color = QColor(144, 255, 112);

    QFont font = painter.font();
    font.setBold(true);
    font.setPixelSize(35 * m_scale);
    painter.setFont(font);
    QPen pen(sog_color);
    pen.setWidth(2);
    painter.setPen(pen);

    QColor color = QColor(64, 64, 64);
    QBrush brush(color, Qt::SolidPattern);

    painter.translate(45 * m_width_scale, height() / 6);
    painter.save();

    QRect now_rect(0, -35 * m_width_scale, width() / 2.25f, 40 * m_height_scale);
    //painter.fillRect(now_rect, Qt::red);
    painter.drawText(now_rect, Qt::AlignHCenter, "NOW");

    painter.translate(0, height() / 6);

    //TODO: Generalize
    float mu = 0.30f;

    int half_width = mu * 64;
    int half_height = mu * 104;
    int top_height = mu * 72;

    QPolygon polygon(6);
    polygon[0] = QPoint(-half_width * m_width_scale, half_height * m_height_scale);          // Bottom left
    polygon[1] = QPoint(half_width * m_width_scale, half_height * m_height_scale);           // Bottom right
    polygon[2] = QPoint(half_width * m_width_scale, -half_height * m_height_scale);          // Top right
    polygon[3] = QPoint(0, -(half_height + top_height) * m_height_scale);                  // Top
    polygon[4] = QPoint(-half_width * m_width_scale, -half_height * m_height_scale);         // Top left
    polygon[5] = QPoint(-half_width * m_width_scale, half_height * m_height_scale);          // Bottom left

    pen.setColor(stw_color);
    painter.setPen(pen);

    QPainterPath path;
    path.addPolygon(polygon);
    painter.fillPath(path, brush);

    drawArrow(painter, m_stw_angle);

    qreal alpha = 1.15f;
    QRect text_rect(-40 * m_width_scale, m_height_scale * (12 + alpha * (-half_height - top_height)), width() / 2.25f, m_height_scale * (alpha * 2 * half_height + top_height));

    int decimal_points = 1;

    QString stw_text = "STW " + QString::number(m_stw_value, 'f', decimal_points) + " kn \nAngle " + QString::number(normalizeAngle(m_stw_angle), 'f', 1) + " deg";

    painter.translate(m_width_scale * 2.375f * half_width, 0);
    painter.drawText(text_rect, Qt::AlignHCenter, stw_text);
    painter.translate(-m_width_scale * 2.375f * half_width, 0);

    pen.setColor(sog_color);
    painter.setPen(pen);
    painter.translate(0, height() / 3);
    painter.fillPath(path, brush);

    drawArrow(painter, m_sog_angle);

    QString sog_text = "SOG " + QString::number(m_sog_value, 'f', decimal_points) + " kn \nAngle " + QString::number(normalizeAngle(m_sog_angle), 'f', 1) + " deg";

    painter.translate(2.375f * half_width * m_width_scale, 0);
    painter.drawText(text_rect, Qt::AlignHCenter, sog_text);
    painter.translate(-2.375f * half_width * m_width_scale, 0);

    painter.restore();
    painter.translate(width() / 2.0f, 0);

    pen.setColor(sog_color);
    painter.setPen(pen);

    font.setBold(true);
    font.setPixelSize(26 * m_scale);
    painter.setFont(font);

    QRect angle_rect(0, 24 * m_width_scale, width() / 2, height() / 1.95f);
    QString angle_string = getAngleString();
    painter.drawText(angle_rect, Qt::AlignVCenter, angle_string);
}

void Dl2CalibrationInstAngleSetupScreen::setupLayout()
{
    SetupScreen::setupLayout();

    m_recommended_button->resize(m_recommended_button_size.width() * m_width_scale, m_recommended_button_size.height() * m_height_scale);
    m_installation_angle_widget->resize(m_installation_angle_widget_size.width() * m_width_scale, m_installation_angle_widget_size.height() * m_height_scale);

    m_recommended_button->move(m_recommended_button_pos.x() * m_width_scale, m_recommended_button_pos.y() * m_height_scale);
    m_installation_angle_widget->move(m_installation_angle_widget_pos.x() * m_width_scale, m_installation_angle_widget_pos.y() * m_height_scale);
}
