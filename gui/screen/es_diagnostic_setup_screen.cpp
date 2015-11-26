#include "es_diagnostic_setup_screen.h"
#include "gui/widget/selectable_bool_item_widget.h"
#include "gui/widget/selectable_enum_item_widget.h"
#include "gui/widget/selectable_float_item_widget.h"

EsDiagnosticSetupScreen::EsDiagnosticSetupScreen(QWidget* parent) :
    SetupScreen(parent)
{
    QSize item_size = m_selectable_item_widget_container->getItemBaseSize();

    m_selectable_item_widget_container->addWidget("Simulate", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Simulate depth", {"OFF", "FIXED", "CHANGING"}));
    m_selectable_item_widget_container->addWidget("Simulate source", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Source", {"JB_70", "SENSOR"}));
    m_selectable_item_widget_container->addWidget("Simulate value", new SelectableFloatItemWidget(m_selectable_item_widget_container, item_size, "Depth", "m", new FloatValidator(0.5, 6000.0f)));
    m_selectable_item_widget_container->addWidget("Test alarm", new SelectableBoolItemWidget(m_selectable_item_widget_container, item_size, "Test alarm", "Stop", "Start"));

//    m_self_test_button = new QPushButton("Self-test", this);
//    m_self_test_button->setFocusPolicy(Qt::NoFocus);

    setupLayout();
}
