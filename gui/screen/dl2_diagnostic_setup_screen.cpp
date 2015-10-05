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

    setupLayout();
}
