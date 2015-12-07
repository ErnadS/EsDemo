#include "cu_setup_screen.h"
#include "gui/widget/selectable_string_item_widget.h"
#include "gui/widget/selectable_enum_item_widget.h"
#include "gui/widget/selectable_ip_item_widget.h"


CuSetupScreen::CuSetupScreen(QWidget* parent) : SetupScreen(parent)
{

    QSize item_size = m_selectable_item_widget_container->getItemBaseSize();

    const QString Local_SFI_Valid ("^VD\\d{1,4}$");
    const QString Alarm_SFI_Valid ("^[A-Z]{2}\\d{1,4}$");
    const QString nonvalid ("SFI NOT VALID!");

    m_selectable_item_widget_container->addWidget("SCREEN", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "SCREEN", {"Horizontal", "Vertical"}));
    m_selectable_item_widget_container->addWidget("SYSTEM TYPE", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "SYSTEM TYPE", {"DL2", "DL1", "ES"}));
    m_selectable_item_widget_container->addWidget("IP ADDRESS", new SelectableIpItemWidget(m_selectable_item_widget_container, item_size, "IP ADDRESS", new IpValidator("IP Not Valid!")));
    m_selectable_item_widget_container->addWidget("LOCAL SFI", new SelectableStringItemWidget(m_selectable_item_widget_container, item_size, "LOCAL SFI",new RegexValidator(Local_SFI_Valid,nonvalid)));
    m_selectable_item_widget_container->addWidget("GROUP", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "GROUP", {"NAVD"}));
    m_selectable_item_widget_container->addWidget("REMOTE DIMMING", new SelectableStringItemWidget(m_selectable_item_widget_container, item_size, "REMOTE DIMMING"));
    m_selectable_item_widget_container->addWidget("SYSTEM NAME", new SelectableStringItemWidget(m_selectable_item_widget_container, item_size, "SYSTEM NAME"));
    m_selectable_item_widget_container->addWidget("NMEA LOOP TEST", new SelectableStringItemWidget(m_selectable_item_widget_container, item_size, "NMEA LOOP TEST"));

    setupLayout();
}

void CuSetupScreen::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QFont font = painter.font();
    font.setPixelSize(18 * m_scale);
    painter.setFont(font);
    painter.setPen(QColor(144, 255, 112));

    int item_size = 11;
    int vertical_space = height() / 13.5f;
    for (int i = 0; i < item_size; i++)
    {
        QString value;

        switch (i)
        {
            case 0:
                value = "SYSTEM NAME: hrkljus";
                break;

            case 1:
                value = "SYSTEM TYPE: JB-70";
                break;

            case 2:
                value = "SERIAL NUMBER: hrkljus";
                break;

            case 3:
                value = "System Function ID (SFI): hrkljus";
                break;

            case 4:
                value = "GROUP: hrkljus";
                break;

            case 5:
                value = "IP ADDRESS: hrkljus";
                break;

            case 6:
                value = "APPROVED IP RANGE:";
                break;

            case 7:
                value = "172.16.0.1 to 172.31.255.254";
                break;

            case 8:
                value = "ALARM SFI: hrkljus";
                break;

            // TODO: Check if available
            case 9:
                value = "SOFTWARE VERSION: hrkljus";
                break;

            case 10:
                value = "HARDWARE VERSION: hrkljus";
                break;
        }

        // IP Address coloring
        if (i == 5)
        {
            QPen pen = painter.pen();

            if (isInValidIpRange("172.20.211.200") == false)
            {
                pen.setColor("orange");
            }
            else
            {
                pen.setColor(QColor(144, 255, 112));
            }

            painter.setPen(pen);
        }
        else
        {
            QPen pen = painter.pen();
            pen.setColor(QColor(144, 255, 112));
            painter.setPen(pen);
        }

        painter.drawText(QRect(0, height() / 7.0f + i * vertical_space, width() - m_selectable_item_widget_container->size().width(), height()), Qt::AlignHCenter, value);
    }

}

bool CuSetupScreen::isInValidIpRange(const QString& ip) const
{
    if (ip.split(".").size() != 4)
        return false;

    int ip_byte_3 = (ip.split(".")[0]).toInt();
    int ip_byte_2 = (ip.split(".")[1]).toInt();
    int ip_byte_0 = (ip.split(".")[3]).toInt();

    if ((ip_byte_3 == 172) && (ip_byte_2 >= 16) && (ip_byte_2 <= 31) && (ip_byte_0 >= 1) && (ip_byte_0 <= 254))
    {
        return true;
    }

    return false;

}
