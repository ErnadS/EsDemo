#include "dl2_aux_setup_screen.h"
#include "gui/widget/selectable_enum_item_widget.h"

Dl2AuxSetupScreen::Dl2AuxSetupScreen(QWidget* parent) :
    SetupScreen(parent)
{
    QSize item_size = m_selectable_item_widget_container->getItemBaseSize();

    m_selectable_item_widget_container->addWidget("Aux 1 Output", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Aux 1 Output", {"StwPulseOutput", "SogPulseOutput", "AlarmBeepOutput", "AlarmOutput", "FitnessOutput", "PowerFailureOutput", "SpeedLimit", "SynchOut", "PingOut", "Disabled"}));
    m_selectable_item_widget_container->addWidget("Aux 2 Output", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Aux 2 Output", {"StwPulseOutput", "SogPulseOutput", "AlarmBeepOutput", "AlarmOutput", "FitnessOutput", "PowerFailureOutput", "SpeedLimit", "SynchOut", "PingOut", "Disabled"}));
    m_selectable_item_widget_container->addWidget("Aux 3 Relay", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Aux 3 Relay", {"StwPulseOutput", "SogPulseOutput", "AlarmBeepOutput", "AlarmOutput", "FitnessOutput", "PowerFailureOutput", "SpeedLimit", "SynchOut", "PingOut", "Disabled"}));
    m_selectable_item_widget_container->addWidget("Aux 4 Input", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Aux 4 Input", {"AlarmAcknowledge", "AlarmSilence", "MuteIn", "Disabled"}));

    setupLayout();
}

void Dl2AuxSetupScreen::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    m_state_vector = {false, false, false, false};

    int x = 15 * m_width_scale;
    int y = 125 * m_height_scale;
    int w = 185 * m_width_scale;
    int h = 50 * m_height_scale;

    QFont font = painter.font();
    font.setPixelSize(18 * m_scale);
    painter.setFont(font);

    qreal alpha = 0.75;

    QRect upper_border_rect(x - 2, y - 2, alpha * w + 4, h + 4);
    QRect lower_border_rect(x - 2, y + h - 2, (1.5f + alpha) * w + 4, (4 + 1) * h + 4);
    painter.fillRect(upper_border_rect, QColor(160, 160, 160));
    painter.fillRect(lower_border_rect, QColor(160, 160, 160));

    QRect status_rect(x, y, alpha * w, h);
    painter.fillRect(status_rect, QColor(218, 218, 218));
    painter.drawText(status_rect, Qt::AlignVCenter, "\tAUX live status");

    painter.setPen(Qt::black);
    QRect channel_title_rect(x, y + h, alpha * w, h);
    painter.fillRect(channel_title_rect, QColor(190, 190, 190));
    painter.drawText(channel_title_rect, Qt::AlignVCenter, "\tChannel:");

    QRect function_title_rect(x + alpha * w, y + h, w, h);
    painter.fillRect(function_title_rect, QColor(190, 190, 190));
    painter.drawText(function_title_rect, Qt::AlignVCenter, "\tFunction:");

    QRect state_title_rect(x + (1 + alpha) * w, y + h, 0.5f * w, h);
    painter.fillRect(state_title_rect, QColor(190, 190, 190));
    painter.drawText(state_title_rect, Qt::AlignVCenter, "\tState:");

    QPen pen = painter.pen();
    pen.setWidth(2);
    pen.setColor(QColor(160, 160, 160));
    painter.setPen(pen);
    painter.drawLine(x, y + h - 1, x + alpha * w, y + h - 1);

    for (int i = 0; i < m_state_vector.count(); i++)
    {
        painter.setPen(Qt::black);
        QColor color = (i % 2 == 0) ? QColor(218, 218, 218) : QColor(190, 190, 190);

        QString aux_name = "\t Aux " + QString::number(i + 1);
        QString function_name = "\t hrkljus";

        QRect channel_value_rect(x, y + (i + 2) * h, alpha * w, h);
        painter.fillRect(channel_value_rect, color);
        painter.drawText(channel_value_rect, Qt::AlignVCenter, aux_name);

        QRect function_value_rect(x + alpha * w, y + (i + 2) * h, w, h);
        painter.fillRect(function_value_rect, color);
        painter.drawText(function_value_rect, Qt::AlignVCenter, function_name);

        QRect state_value_rect(x + (1 + alpha) * w, y + (i + 2) * h, 0.5f * w, h);
        painter.fillRect(state_value_rect, color);

        painter.setPen(pen);
        painter.drawLine(x, y + h - 1, x + alpha * w, y + h - 1);
        painter.drawLine(x, y + (2 + i) * h - 1, x + (1.5f + alpha) * w, y + (2 + i) * h - 1);

        QImage led_image(":/led_off.png");

        if (m_state_vector[i] == true)
        {
            led_image = QImage(":/led_on.png");
        }

        led_image = led_image.scaled(led_image.width() * m_scale, led_image.height() * m_scale, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

        QRect led_rect(state_value_rect.center().x() - led_image.width() / 2, state_value_rect.center().y() - led_image.height() / 2, led_image.width(), led_image.height());
        painter.drawImage(led_rect, led_image);
    }

    pen.setWidth(2);
    pen.setColor(QColor(160, 160, 160));
    painter.setPen(pen);

    painter.drawLine(x + alpha * w + 1, y + h - 1, x + alpha * w + 1, y + (m_state_vector.count() + 2) * h + 1);
    painter.drawLine(x + (1 + alpha) * w + 1, y + h - 1, x + (1 + alpha) * w + 1, y + (m_state_vector.count() + 2) * h + 1);
}
