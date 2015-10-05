#include "dl2_runtime_c_setup_screen.h"
#include "gui/widget/selectable_enum_item_widget.h"
#include "gui/widget/selectable_bool_item_widget.h"

Dl2RuntimeCSetupScreen::Dl2RuntimeCSetupScreen(QWidget* parent) : BaseRuntimeSetupScreen(parent)
{
    m_title_widget->setTitle("DL2 Runtime Screen B Setup");
    m_runtime_screen = new RuntimeScreen(this, RuntimeScreenType::RUNTIME_B, true);
    m_runtime_screen->titleWidget()->setTitle("DL2 Speed Log");

    QList<QString> information_list{"Water temp", "Alert High", "Alert Low", "Total", "Trip", "Depth", "STW2 lon", "STW2 tra", "HDG", "ROT", "GPS SOG", "ROLL", "PITCH", "SOG2L", "SOG2T", "SOG2", "STW2", "Ping Len", "SOG2L QF", "SOG2T QF", "STW2L QF", "STW2T QF", "SOG2QF", "STW2 QF", "QF"};

    QSize item_size = m_selectable_item_widget_container->getItemBaseSize();

    m_selectable_item_widget_container->addWidget("VISIBLE", new SelectableBoolItemWidget(m_selectable_item_widget_container, item_size, "VISIBLE", "ON", "OFF"));
    m_selectable_item_widget_container->addWidget("STW RESULTANT", new SelectableBoolItemWidget(m_selectable_item_widget_container, item_size, "STW RESULTANT", "ON", "OFF"));
    m_selectable_item_widget_container->addWidget("SOG RESULTANT", new SelectableBoolItemWidget(m_selectable_item_widget_container, item_size, "SOG RESULTANT", "ON", "OFF"));
    m_selectable_item_widget_container->addWidget("CURRENT RESULTANT", new SelectableBoolItemWidget(m_selectable_item_widget_container, item_size, "CURRENT RESULTANT", "ON", "OFF"));
    m_selectable_item_widget_container->addWidget("COMPASS", new SelectableBoolItemWidget(m_selectable_item_widget_container, item_size, "COMPASS", "ON", "OFF"));
    m_selectable_item_widget_container->addWidget("ANGLE CALC", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "ANGLE CALC", {"TRUE", "RELATIVE"}));

    for (int i = 0; i < 5; i++)
    {
        auto key = "INFORMATION " + QString::number(i + 1);

        m_selectable_item_widget_container->addWidget(key, new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, key, information_list, ""));
    }

    setupLayout();
}
