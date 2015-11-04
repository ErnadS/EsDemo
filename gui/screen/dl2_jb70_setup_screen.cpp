#include "dl2_jb70_setup_screen.h"

#include "gui/widget/selectable_ip_item_widget.h"
#include "gui/widget/selectable_string_item_widget.h"
#include "gui/widget/selectable_enum_item_widget.h"

bool Dl2Jb70SetupScreen::isInValidIpRange(const QString&) const
{
    // TODO: Implement
    return true;
}

Dl2Jb70SetupScreen::Dl2Jb70SetupScreen(QWidget* parent) :
    SetupScreen(parent)
{
    QSize item_size = m_selectable_item_widget_container->getItemBaseSize();

    m_selectable_item_widget_container->addWidget("IP ADDRESS", new SelectableIpItemWidget(m_selectable_item_widget_container, item_size, "IP ADDRESS"));
    m_selectable_item_widget_container->addWidget("LOCAL SFI", new SelectableStringItemWidget(m_selectable_item_widget_container, item_size, "LOCAL SFI"));
    m_selectable_item_widget_container->addWidget("GROUP", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "GROUP", {"NAVD"}));
    m_selectable_item_widget_container->addWidget("Alarm SFI", new SelectableStringItemWidget(m_selectable_item_widget_container, item_size, "Alarm SFI"));
    m_selectable_item_widget_container->addWidget("System Name", new SelectableStringItemWidget(m_selectable_item_widget_container, item_size, "System Name"));

    setupLayout();
}

void Dl2Jb70SetupScreen::paintEvent(QPaintEvent*)
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

            if (isInValidIpRange("127.0.0.1") == false)
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
