#include "dl2_alert_setup_screen.h"
#include "gui/widget/selectable_float_item_widget.h"
#include "gui/widget/selectable_enum_item_widget.h"
#include "gui/widget/selectable_int_item_widget.h"

Dl2AlertSetupScreen::Dl2AlertSetupScreen(QWidget* parent) :
    SetupScreen(parent)
{
    QSize item_size = m_selectable_item_widget_container->getItemBaseSize();

    m_selectable_item_widget_container->addWidget("Alarm high", new SelectableFloatItemWidget(m_selectable_item_widget_container, item_size, "Alarm high", "kn", new FloatValidator(5.0f, 30.0f)));
    m_selectable_item_widget_container->addWidget("Alarm low", new SelectableFloatItemWidget(m_selectable_item_widget_container, item_size, "Alarm low", "kn", new FloatValidator(0, 5.0f)));
    m_selectable_item_widget_container->addWidget("Alarm type", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Alarm type", {"ALR", "ALF"}));
    m_selectable_item_widget_container->addWidget("Escalation time", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Escalation time", {"1", "2", "3", "4", "5"}, "min"));
    m_selectable_item_widget_container->addWidget("STW high ID", new SelectableIntItemWidget(m_selectable_item_widget_container, item_size, "STW high ID", new IntValidator(0, 1000)));
    m_selectable_item_widget_container->addWidget("STW low ID", new SelectableIntItemWidget(m_selectable_item_widget_container, item_size, "STW low ID", new IntValidator(0, 1000)));
    m_selectable_item_widget_container->addWidget("SOG high ID", new SelectableIntItemWidget(m_selectable_item_widget_container, item_size, "SOG high ID", new IntValidator(0, 1000)));
    m_selectable_item_widget_container->addWidget("SOG low ID", new SelectableIntItemWidget(m_selectable_item_widget_container, item_size, "SOG low ID", new IntValidator(0, 1000)));
    m_selectable_item_widget_container->addWidget("System Alert ID", new SelectableIntItemWidget(m_selectable_item_widget_container, item_size, "System Alert ID", new IntValidator(0, 1000)));

    setupLayout();
}

void Dl2AlertSetupScreen::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QFont font = painter.font();
    font.setPixelSize(18 * m_scale);
    painter.setFont(font);
    painter.setPen(QPen(Qt::yellow));

    int item_size = 9;
    int vertical_space = height() / 13.5f;
    for (int i = 0; i < item_size; i++)
    {
        QString value;

        switch (i)
        {
            case 0:
                value = "ALERT HIGH: hrkljus";
                break;

            case 1:
                value = "ALERT LOW: hrkljus";
                break;

            case 2:
                value = "System Alert ID: hrkljus";
                break;

            case 5:
                value = "STW high ID: hrkljus";
                break;

            case 6:
                value = "STW low ID: hrkljus";
                break;

            case 7:
                value = "SOG high ID: hrkljus";
                break;

            case 8:
                value = "SOG low ID: hrkljus";
                break;
        }

        painter.drawText(QRect(0, height() / 7.0f + i * vertical_space, width() - m_selectable_item_widget_container->size().width(), height()), Qt::AlignHCenter, value);
    }
}
