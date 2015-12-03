#include "dl2_setup_setup_screen.h"

#include "gui/widget/selectable_float_item_widget.h"
#include "gui/widget/selectable_enum_item_widget.h"
#include "gui/widget/selectable_bool_item_widget.h"

void Dl2SetupSetupScreen::drawDistanceLine(QPainter& painter, int x, int y, int width)
{
    QPoint p1(x - width / 2, y);
    QPoint p2(x + width / 2, y);

    painter.drawLine(p1, p2);

    QPolygon polygon(4);
    polygon[0] = QPoint(6, 0);
    polygon[1] = QPoint(0, -7);
    polygon[2] = QPoint(0, 7);
    polygon[3] = QPoint(6, 0);
    QPainterPath path;
    path.addPolygon(polygon);

    QPen pen = painter.pen();
    QBrush brush(pen.color());

    painter.save();
    painter.translate(x, y);

    painter.save();
    painter.translate(width / 2, 0);

    painter.fillPath(path, brush);
    painter.drawPath(path);

    painter.restore();
    painter.translate(-width / 2, 0);

    painter.rotate(180.0f);
    painter.fillPath(path, brush);
    painter.drawPath(path);

    painter.restore();
}

void Dl2SetupSetupScreen::drawArrow(QPainter& painter, int x, int y, int width)
{
    painter.save();
    painter.translate(x, y);
    QPoint p1(0, 0);
    QPoint p2(width, 0);

    painter.drawLine(p1, p2);

    painter.translate(width, 0);

    QPolygon polygon(4);
    polygon[0] = QPoint(6, 0);
    polygon[1] = QPoint(0, -7);
    polygon[2] = QPoint(0, 7);
    polygon[3] = QPoint(6, 0);
    QPainterPath path;
    path.addPolygon(polygon);

    QPen pen = painter.pen();
    QBrush brush(pen.color());

    painter.fillPath(path, brush);
    painter.drawPath(path);

    painter.restore();
}

Dl2SetupSetupScreen::Dl2SetupSetupScreen(QWidget* parent) :
    SetupScreen(parent)
{
    titleWidget()->setTitle("DL2 Speed Log");

    QSize item_size = m_selectable_item_widget_container->getItemBaseSize();

    m_selectable_item_widget_container->addWidget("Draft", new SelectableFloatItemWidget(m_selectable_item_widget_container, item_size, "Draft", "m", new FloatValidator(0, 30.0f)));
    m_selectable_item_widget_container->addWidget("Vessel max speed", new SelectableFloatItemWidget(m_selectable_item_widget_container, item_size, "Vessel max speed", "kn", new FloatValidator(0, 30.0f)));
    m_selectable_item_widget_container->addWidget("Vessel length", new SelectableFloatItemWidget(m_selectable_item_widget_container, item_size, "Vessel length", "m", new FloatValidator(0, 30.0f)));
    m_selectable_item_widget_container->addWidget("Sensor dist from bow", new SelectableFloatItemWidget(m_selectable_item_widget_container, item_size, "Sensor dist from bow", "m", new FloatValidator(0, 30.0f)));
    m_selectable_item_widget_container->addWidget("Tonnage", new SelectableFloatItemWidget(m_selectable_item_widget_container, item_size, "Tonnage", "t", new FloatValidator(0, 2000.0f)));
    m_selectable_item_widget_container->addWidget("Averaging time", new SelectableFloatItemWidget(m_selectable_item_widget_container, item_size, "Averaging time", "s", new FloatValidator(0, 5.0f)));
    m_selectable_item_widget_container->addWidget("Current calculation", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Current calculation", {"Auto", "Log SOG", "GPS SOG"}));
    m_selectable_item_widget_container->addWidget("GPS on lost bottom", new SelectableBoolItemWidget(m_selectable_item_widget_container, item_size, "GPS on lost bottom", "ON", "OFF"));
    m_selectable_item_widget_container->addWidget("Vessel image", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Vessel image", {"1", "2", "3", "4", "5"}));
    m_selectable_item_widget_container->addWidget("SOG Shallow ping length", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "SOG Shallow ping length", {"1", "2", "4", "8"}, "ms"));
    m_selectable_item_widget_container->addWidget("SOG Deep ping length", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "SOG Deep ping length", {"1", "2", "4", "8"}, "ms"));
    m_selectable_item_widget_container->addWidget("SOG Shallow Power", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "SOG Shallow Power", {"Low", "Medium", "High"}));

    m_reset_button = new Button(this, m_reset_button_size, "Reset");

    setupLayout();
}


void Dl2SetupSetupScreen::paintEvent(QPaintEvent*)
{    
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QPen pen(QColor(144, 255, 112));
    pen.setWidth(2);
    painter.setPen(pen);

    painter.translate(40 * m_width_scale, height() / 3.5f);
    QPixmap* vessel_pixmap = new QPixmap(":/vessel_" + QString::number(1) + ".png");
    QPixmap scaled_vessel_pixmap = vessel_pixmap->scaled(2 * vessel_pixmap->width() * m_width_scale, 2 * vessel_pixmap->height() * m_height_scale, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    painter.drawPixmap(0, 0, scaled_vessel_pixmap);

    drawDistanceLine(painter, scaled_vessel_pixmap.width() / 2, 1.8f * scaled_vessel_pixmap.height(), scaled_vessel_pixmap.width());

    qreal x = 0.75f * scaled_vessel_pixmap.width();
    qreal y = scaled_vessel_pixmap.height();

    painter.drawLine(x, y, x + y / 3, 2 * y);
    painter.drawLine(x, y, x - y / 3, 2 * y);

    int half_width = (scaled_vessel_pixmap.width() - x) / 2;
    x = x + half_width;
    drawDistanceLine(painter, x + 3, 1.4f * scaled_vessel_pixmap.height(), 2 * half_width - 6);

    int w = scaled_vessel_pixmap.width() / 2.75f;

    QColor background_color(62, 62, 62);
    QRect vessel_length_rect = QRect(x / 3 - w / 2, 2 * scaled_vessel_pixmap.height(), w, w / 2.75f);
    QRect bow_distance_rect = QRect(x / 3 - w / 2 + scaled_vessel_pixmap.width() / 2, 2 * scaled_vessel_pixmap.height(), w, w / 2.75f);


    painter.fillRect(QRect(vessel_length_rect.x() - 1, vessel_length_rect.y() - 1, vessel_length_rect.width() + 2, vessel_length_rect.height() + 2), Qt::gray);
    painter.fillRect(vessel_length_rect, background_color);

    painter.fillRect(QRect(bow_distance_rect.x() - 1, bow_distance_rect.y() - 1, bow_distance_rect.width() + 2, bow_distance_rect.height() + 2), Qt::gray);
    painter.fillRect(bow_distance_rect, background_color);

    drawArrow(painter, x - 30 * m_width_scale, -20 / m_height_scale, 60 * m_width_scale);

    QRect speed_rect = QRect(bow_distance_rect.x(), -30 - bow_distance_rect.height(), bow_distance_rect.width(), bow_distance_rect.height());

    painter.fillRect(QRect(speed_rect.x() - 1, speed_rect.y() - 1, speed_rect.width() + 2, speed_rect.height() + 2), Qt::gray);
    painter.fillRect(speed_rect, background_color);

    ////
    QRect sensor_timer_rect = QRect(x / 3 - w / 2 + scaled_vessel_pixmap.width() / 2, /*3 * scaled_vessel_pixmap.height() */this->height() - w / 1.5f - height() / 3.5f, 1.50f*w, w / 1.5f);
    painter.fillRect(QRect(sensor_timer_rect.x() - 1, sensor_timer_rect.y() - 1, sensor_timer_rect.width() + 2, sensor_timer_rect.height() + 2), Qt::gray);
    painter.fillRect(sensor_timer_rect, background_color);

    QFont font = painter.font();
    font.setPixelSize(16 * m_scale);
    painter.setFont(font);

    QString vessel_length_string = "Vessel length " + QString::number(150.0f, 'f', 1) + "m";
    QString bow_distance_string = "Distance from bow " + QString::number(5.0f, 'f', 1) + "m";
    QString speed_string = "Max speed " + QString::number(22.0f, 'f', 1) + "kn";

    painter.drawText(vessel_length_rect, Qt::AlignCenter | Qt::TextWordWrap, vessel_length_string);
    painter.drawText(bow_distance_rect, Qt::AlignCenter | Qt::TextWordWrap, bow_distance_string);
    painter.drawText(speed_rect, Qt::AlignCenter | Qt::TextWordWrap, speed_string);

    QString sensor_timer_string = "Sensor running time: 0:00:00";
    painter.drawText(sensor_timer_rect, Qt::AlignCenter | Qt::TextWordWrap, sensor_timer_string);
}

void Dl2SetupSetupScreen::setupLayout()
{
    SetupScreen::setupLayout();

    QSize reset_button_size(m_reset_button_size.width() * m_width_scale, m_reset_button_size.height() * m_height_scale);
    QPoint reset_button_pos(m_reset_button_pos.x() * m_width_scale, m_reset_button_pos.y() * m_height_scale);

    m_reset_button->resize(reset_button_size);
    m_reset_button->move(reset_button_pos);
}
