#include "es_runtime_b_setup_screen.h"
#include "gui/widget/selectable_bool_item_widget.h"
#include "gui/widget/selectable_enum_item_widget.h"

EsRuntimeBSetupScreen::EsRuntimeBSetupScreen(QWidget* parent) : BaseRuntimeSetupScreen(parent)
{
    m_title_widget->setTitle("DL2 Runtime Screen B Setup");
    m_runtime_screen = new RuntimeScreen(this, RuntimeScreenType::RUNTIME_ES_B, true);
    m_runtime_screen->titleWidget()->setTitle("ES1 Echosounder");

    QList<QString> information_list{"Water temp", "Alert High", "Alert Low", "Total", "Trip", "Depth", "STW2 lon", "STW2 tra", "HDG", "ROT", "GPS SOG", "ROLL", "PITCH", "SOG2L", "SOG2T", "SOG2", "STW2", "Ping Len", "SOG2L QF", "SOG2T QF", "STW2L QF", "STW2T QF", "SOG2QF", "STW2 QF", "QF"};

    QSize item_size = m_selectable_item_widget_container->getItemBaseSize();

  //  QList<QString> depth_information_list{"Depth Below Transducer", "Depth Below Surface", "Depth Below Keel"};

    //TO DO - QUERY DRAFT AND OFFSET VALUES TO EDIT depth_information_list!

    m_selectable_item_widget_container->addWidget("VISIBLE", new SelectableBoolItemWidget(m_selectable_item_widget_container, item_size, "VISIBLE", "ON", "OFF"));
    m_selectable_item_widget_container->addWidget("LAYOUT", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "LAYOUT", {"Primary", "Horizontal split", "Vertical split"}));
    m_selectable_item_widget_container->addWidget("SCROLL TYPE", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "SCROLL TYPE", {"LOOP", "NEXT SYSTEM"}));
    m_selectable_item_widget_container->addWidget("DIGITAL FONT SIZE", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "DIGITAL FONT SIZE", {"10", "12", "15", "0"}));
    m_selectable_item_widget_container->addWidget("DEPTH", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "DEPTH", {"SURFACE", "KEEL", "TRANSDUCER"}));
    for (int i = 0; i < 5; i++)
    {
        auto key = "INFORMATION " + QString::number(i + 1);

        m_selectable_item_widget_container->addWidget(key, new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, key, information_list, ""));
    }

    setupLayout();
}
