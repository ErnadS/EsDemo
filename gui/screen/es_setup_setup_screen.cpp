#include "es_setup_setup_screen.h"
#include "gui/widget/selectable_float_item_widget.h"
#include "gui/widget/selectable_enum_item_widget.h"
#include "gui/widget/selectable_bool_item_widget.h"
#include "gui/widget/selectable_string_item_widget.h"

EsSetupSetupScreen::EsSetupSetupScreen(QWidget* parent) :
    SetupScreen(parent)
{
    titleWidget()->setTitle("ES1 Echosounder");

    QSize item_size = m_selectable_item_widget_container->getItemBaseSize();

    m_selectable_item_widget_container->addWidget("Draft", new SelectableFloatItemWidget(m_selectable_item_widget_container, item_size, "Draft", "m", new FloatValidator(0, 50.0f)));
    m_selectable_item_widget_container->addWidget("Vessel image", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Vessel image", {"Cruise", "Tanker", "Military", "Offshore", "File+"}));
    m_selectable_item_widget_container->addWidget("System name", new SelectableStringItemWidget(m_selectable_item_widget_container, item_size, "System name", new RegexValidator("[A-Z]{3,3}", "Incorrect system name!")));
    m_selectable_item_widget_container->addWidget("Acoustics deep", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Acoustics deep",{"Chirp", "Continuous"}));
    m_selectable_item_widget_container->addWidget("Scales speed", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Scales speed", {"kn", "m/s"}));
    m_selectable_item_widget_container->addWidget("Scales depth", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Scales depth", {"m", "ft", "fm"}));
    m_selectable_item_widget_container->addWidget("Options", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Options", {"Speed of sound", "mute"}));
    m_selectable_item_widget_container->addWidget("Speed of sound", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Speed of sound", {"1500", "auto"}));
    m_selectable_item_widget_container->addWidget("Setup save", new SelectableStringItemWidget(m_selectable_item_widget_container, item_size, "Setup save", new RegexValidator("[A-Z]{3,3}", "Incorrect file name!")));
    m_selectable_item_widget_container->addWidget("Setup restore", new SelectableStringItemWidget(m_selectable_item_widget_container, item_size, "Setup restore", new RegexValidator("[A-Z]{3,3}", "Incorrect file name!")));

    setupLayout();
}
