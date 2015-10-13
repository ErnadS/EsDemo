#include "dl2_diagnostic_setup_screen.h"

#include "gui/widget/selectable_bool_item_widget.h"
#include "gui/widget/selectable_enum_item_widget.h"
#include "gui/widget/selectable_float_item_widget.h"

Dl2DiagnosticSetupScreen::Dl2DiagnosticSetupScreen(QWidget* parent) :
    SetupScreen(parent)
{
    QSize item_size = m_selectable_item_widget_container->getItemBaseSize();

    m_selectable_item_widget_container->addWidget("Simulate fixed speed", new SelectableBoolItemWidget(m_selectable_item_widget_container, item_size, "Simulate fixed speed", "STOP", "START"));
    m_selectable_item_widget_container->addWidget("Simulation source", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Simulation source", {"SENSOR", "JB_70", "GPS"}));
    m_selectable_item_widget_container->addWidget("Fixed speed long", new SelectableFloatItemWidget(m_selectable_item_widget_container, item_size, "Fixed speed long", "kn", new FloatValidator(0, 30.0f)));
    m_selectable_item_widget_container->addWidget("Fixed speed tra", new SelectableFloatItemWidget(m_selectable_item_widget_container, item_size, "Fixed speed tra", "kn", new FloatValidator(0, 30.0f)));
    m_selectable_item_widget_container->addWidget("Test alarm output", new SelectableBoolItemWidget(m_selectable_item_widget_container, item_size, "Test alarm output", "STOP", "START"));

    m_self_test_button = new QPushButton("Self-test", this);
    m_self_test_button->setFocusPolicy(Qt::NoFocus);

    m_upgrade_button = new QPushButton("Upgrade now", this);
    m_upgrade_button->setFocusPolicy(Qt::NoFocus);

    connect(m_self_test_button, SIGNAL(clicked()), this, SLOT(selfTestButtonClicked()));
    connect(m_upgrade_button, SIGNAL(clicked()), this, SLOT(upgradeButtonClicked()));

    setupLayout();
}

void Dl2DiagnosticSetupScreen::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Todo: Refactor
    painter.setPen(QColor(144, 255, 112));

    QFont font = painter.font();
    font.setPixelSize(25 * m_scale);
    painter.setFont(font);

    QString value = QString("Speed Simulation: hrkljus");
    painter.drawText(QRect(0, 65 * m_height_scale, 400 * m_width_scale, 60 * m_height_scale), Qt::AlignHCenter | Qt::TextWordWrap, value);

    value = QString("Alarm Output test: hrkljus");

    painter.drawText(QRect(0, 105 * m_height_scale, 400 * m_width_scale, 30 * m_height_scale), Qt::AlignHCenter | Qt::TextWordWrap, value);

    int x = 20 * m_width_scale;
    int y = 150 * m_height_scale;
    int w = 135 * m_width_scale;
    int h = 35 * m_height_scale;

    int item_size = 5;

    font.setPixelSize(18 * m_scale);
    font.setBold(true);
    painter.setFont(font);

    QRect upper_border_rect(x - 2, y - 2, w + 4, h + 4);
    QRect lower_border_rect(x - 2, y + h - 2, 3 * w + 4, item_size * h + 4);
    painter.fillRect(upper_border_rect, QColor(160, 160, 160));
    painter.fillRect(lower_border_rect, QColor(160, 160, 160));

    painter.setPen(Qt::black);
    QRect status_rect(x, y, w, h);
    painter.fillRect(status_rect, QColor(218, 218, 218));
    painter.drawText(status_rect, Qt::AlignVCenter, "\tSensor live");

    font.setBold(false);
    painter.setFont(font);

    QPen pen = painter.pen();
    pen.setWidth(2);
    pen.setColor(QColor(160, 160, 160));
    painter.setPen(pen);
    painter.drawLine(x, y + h - 1, x + w, y + h - 1);

    for (int i = 0; i < item_size; i++)
    {        
        painter.setPen(Qt::black);
        QColor color = (i % 2 == 0) ? QColor(218, 218, 218) : QColor(190, 190, 190);

        QString value_1, value_2, value_3;

        switch (i)
        {
            case 0:
                value_1 = "\tSTW2L -.-";
                value_2 = "\tSTWL QF -.-";
                value_3 = "\tDPT FWD -.-";
                break;

            case 1:
                value_1 = "\tSTW2T -.-";
                value_2 = "\tSTWT QF -.-";
                value_3 = "\tDPT STRB -.-";
                break;

            case 2:
                value_1 = "\tSOG2L -.-";
                value_2 = "\tSOGL QF -.-";
                value_3 = "\tHDG -.-";
                break;

            case 3:
                value_1 = "\tSOG2T -.-";
                value_2 = "\tSOGT QF -.-";
                value_3 = "\tROT -.-";
                break;

            case 4:
                value_1 = "\tGPS SOG -.-";
                value_2 = "\tTEMP -.-";
                break;
        }

        QRect value_1_rect(x, y + (i + 1) * h, w, h);
        painter.fillRect(value_1_rect, color);
        painter.drawText(value_1_rect, Qt::AlignVCenter, value_1);

        QRect value_2_rect(x +  w, y + (i + 1) * h, w, h);
        painter.fillRect(value_2_rect, color);
        painter.drawText(value_2_rect, Qt::AlignVCenter, value_2);

        QRect value_3_rect(x + 2 * w, y + (i + 1) * h, w, h);
        painter.fillRect(value_3_rect, color);
        painter.drawText(value_3_rect, Qt::AlignVCenter, value_3);

        painter.setPen(pen);
        painter.drawLine(x, y + h - 1, x + w, y + h - 1);
        painter.drawLine(x, y + (1 + i) * h - 1, x + 3 * w, y + (1 + i) * h - 1);
    }

    pen.setWidth(2);
    pen.setColor(QColor(160, 160, 160));
    painter.setPen(pen);

    painter.drawLine(x + w + 1, y + h - 1, x + w + 1, y + (item_size + 1) * h + 1);

    painter.drawLine(x + 2 * w + 1, y + h - 1, x + 2 * w + 1, y + (item_size + 1) * h + 1);
}

void Dl2DiagnosticSetupScreen::setupLayout()
{
    SetupScreen::setupLayout();

    int font_pixel_size = 20.0f * m_scale;
    QString css_string = QString("background-color: rgb(218, 218, 218);") +
                         QString("color: black;") +
                         QString("text-align: justify;") +
                         QString("border-style: solid;") +
                         QString("border-width: 2px;") +
                         QString("border-color: rgb(160, 160, 160);") +
                         "\nfont: " + QString::number(font_pixel_size) + "px;";

    m_self_test_button->setStyleSheet(css_string);
    m_upgrade_button->setStyleSheet(css_string);

    m_self_test_button->resize(m_self_test_button_size.width() * m_width_scale, m_self_test_button_size.height() * m_height_scale);
    m_self_test_button->move(m_self_test_button_pos.x() * m_width_scale, m_self_test_button_pos.y() * m_height_scale);

    m_upgrade_button->resize(m_upgrade_button_size.width() * m_width_scale, m_upgrade_button_size.height() * m_height_scale);
    m_upgrade_button->move(m_upgrade_button_pos.x() * m_width_scale, m_upgrade_button_pos.y() * m_height_scale);
}

void Dl2DiagnosticSetupScreen::selfTestButtonClicked()
{
    qDebug() << "Self test button clicked!";
}

void Dl2DiagnosticSetupScreen::upgradeButtonClicked()
{
    qDebug() << "Upgrade button clicked!";
}
