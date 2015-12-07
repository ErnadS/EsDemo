#include "es_runtime_a_setup_screen.h"
#include "gui/widget/selectable_enum_item_widget.h"
#include "gui/widget/selectable_int_item_widget.h"

EsRuntimeASetupScreen::EsRuntimeASetupScreen(QWidget* parent) : BaseRuntimeSetupScreen(parent)
{   
    m_title_widget->setTitle("ES Runtime Screen A Setup");
    m_runtime_screen = new RuntimeScreen(this, RuntimeScreenType::RUNTIME_ES, true);
    m_runtime_screen->titleWidget()->setTitle("ES1 Echosounder");


    m_keyboard_pos=QPoint(445,208);
    m_keyboard_size=QSize(320,height()-208);

    QList<QString> information_list{"Water temp", "Alert High", "Alert Low", "Total", "Trip", "Depth", "STW2 lon", "STW2 tra", "HDG", "ROT", "GPS SOG", "ROLL", "PITCH", "SOG2L", "SOG2T", "SOG2", "STW2", "Ping Len", "SOG2L QF", "SOG2T QF", "STW2L QF", "STW2T QF", "SOG2QF", "STW2 QF", "QF"};

     QList<QString> depth_information_list{"Depth Below Transducer", "Depth Below Surface", "Depth Below Keel"};
    QSize item_size = m_selectable_item_widget_container->getItemBaseSize();

    m_selectable_item_widget_container->addWidget("DEPTH", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "DEPTH", {"SURFACE", "KEEL", "TRANSDUCER"}));
    m_selectable_item_widget_container->addWidget("PRIMARY CHANNEL", new SelectableIntItemWidget(m_selectable_item_widget_container, item_size, "PRIMARY CHANNEL", new IntValidator(0, 200)));
    m_selectable_item_widget_container->addWidget("BUTTONS", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "BUTTONS",{"Always", "Pop Up", "Never"}));
    m_selectable_item_widget_container->addWidget("BUTTON 2", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "BUTTON 2", {"Power", "Transducer","Screen Speed", "Mode", "Hidden"}));
    m_selectable_item_widget_container->addWidget("BUTTON 3", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "BUTTON 3", {"Transducer","Screen Speed", "Mode", "Hidden"}));
    m_selectable_item_widget_container->addWidget("SCROLL TYPE", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "SCROLL TYPE", {"Loop","Next System"}));



    for (int i = 0; i < 5; i++)
    {
        auto key = "INFORMATION " + QString::number(i + 1);

        m_selectable_item_widget_container->addWidget(key, new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, key, information_list, ""));
    }


    setupLayout();
}
