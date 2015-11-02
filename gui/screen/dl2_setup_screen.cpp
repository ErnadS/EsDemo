#include "dl2_setup_setup_screen.h"

#include "gui/widget/selectable_float_item_widget.h"
#include "gui/widget/selectable_enum_item_widget.h"
#include "gui/widget/selectable_bool_item_widget.h"

Dl2SetupSetupScreen::Dl2SetupSetupScreen(QWidget* parent) :
    SetupScreen(parent)
{
    titleWidget()->setTitle("DL2 Speed Log");

    QSize item_size = m_selectable_item_widget_container->getItemBaseSize();

    m_selectable_item_widget_container->addWidget("Draft", new SelectableFloatItemWidget(m_selectable_item_widget_container, item_size, "Draft", "m", new FloatValidator(0, 30.0f)));
    m_selectable_item_widget_container->addWidget("Vessel max speed", new SelectableFloatItemWidget(m_selectable_item_widget_container, item_size, "Vessel max speed", "kn", new FloatValidator(0, 30.0f)));
    m_selectable_item_widget_container->addWidget("Vessel length", new SelectableFloatItemWidget(m_selectable_item_widget_container, item_size, "Vessel length", "m", new FloatValidator(0, 30.0f)));
    m_selectable_item_widget_container->addWidget("Sensor dist from bow", new SelectableFloatItemWidget(m_selectable_item_widget_container, item_size, "Sensor dist from bow", "m", new FloatValidator(0, 30.0f)));
    m_selectable_item_widget_container->addWidget("Tonnage", new SelectableFloatItemWidget(m_selectable_item_widget_container, item_size, "Tonnage", "t", new FloatValidator(0, 2000.0f)));
    m_selectable_item_widget_container->addWidget("Averaging time", new SelectableFloatItemWidget(m_selectable_item_widget_container, item_size, "Averaging time", "s", new FloatValidator(0, 5.0f)));
    m_selectable_item_widget_container->addWidget("Current calculation", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Current calculation", {"Auto", "Log SOG", "GPS SOG"}));
    m_selectable_item_widget_container->addWidget("GPS on lost bottom", new SelectableBoolItemWidget(m_selectable_item_widget_container, item_size, "GPS on lost bottom", "ON", "OFF"));
    m_selectable_item_widget_container->addWidget("Vessel image", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Vessel image", {"1", "2", "3", "4", "5"}));
    m_selectable_item_widget_container->addWidget("SOG Shallow ping length", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "SOG Shallow ping length", {"1", "2", "4", "8"}, "ms"));
    m_selectable_item_widget_container->addWidget("SOG Deep ping length", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "SOG Deep ping length", {"1", "2", "4", "8"}, "ms"));
    m_selectable_item_widget_container->addWidget("SOG Shallow Power", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "SOG Shallow Power", {"Low", "Medium", "High"}));

    setupLayout();
}
