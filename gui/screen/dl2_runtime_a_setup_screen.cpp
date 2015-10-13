#include "dl2_runtime_a_setup_screen.h"
#include "gui/widget/selectable_enum_item_widget.h"

Dl2RuntimeASetupScreen::Dl2RuntimeASetupScreen(QWidget* parent) : BaseRuntimeSetupScreen(parent)
{   
    m_title_widget->setTitle("DL2 Runtime Screen A Setup");
    m_runtime_screen = new RuntimeScreen(this, RuntimeScreenType::RUNTIME_A, true);
    m_runtime_screen->titleWidget()->setTitle("DL2 Speed Log");

    QList<QString> value_list{"STW", "WC", "STW(DL1)", "Trip", "Total", "OFF"};
    QList<QString> information_list{"Water temp", "Alert High", "Alert Low", "Total", "Trip", "Depth", "STW2 lon", "STW2 tra", "HDG", "ROT", "GPS SOG", "ROLL", "PITCH", "SOG2L", "SOG2T", "SOG2", "STW2", "Ping Len", "SOG2L QF", "SOG2T QF", "STW2L QF", "STW2T QF", "SOG2QF", "STW2 QF", "QF"};

    QSize item_size = m_selectable_item_widget_container->getItemBaseSize();

    for (int i = 0; i < 4; i++)
    {
        auto key = "Value " + QString::number(i + 1);

        if (i == 1)
        {
            m_selectable_item_widget_container->addWidget(key, new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, key, {"SOG"}, ""));
        }
        else
        {

            m_selectable_item_widget_container->addWidget(key, new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, key, value_list, ""));
        }
    }

    for (int i = 0; i < 5; i++)
    {
        auto key = "INFORMATION " + QString::number(i + 1);

        m_selectable_item_widget_container->addWidget(key, new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, key, information_list, ""));
    }

    setupLayout();
}
