#include "es_alert_setup_screen.h"
#include "gui/widget/selectable_float_item_widget.h"
#include "gui/widget/selectable_enum_item_widget.h"
#include "gui/widget/selectable_int_item_widget.h"

EsAlertSetupScreen::EsAlertSetupScreen(QWidget* parent) :
    SetupScreen(parent)
{
    QSize item_size = m_selectable_item_widget_container->getItemBaseSize();

    m_selectable_item_widget_container->addWidget("Alarm Shallow", new SelectableFloatItemWidget(m_selectable_item_widget_container, item_size, "Alarm Shallow", "m", new FloatValidator(50.0f, 500.0f)));
    m_selectable_item_widget_container->addWidget("Alert Deep", new SelectableFloatItemWidget(m_selectable_item_widget_container, item_size, "Alert Deep", "m", new FloatValidator(100.0f, 1000.0f)));
    m_selectable_item_widget_container->addWidget("Alert Type", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Alert Type", {"ALR", "ALF"}));
    m_selectable_item_widget_container->addWidget("Escalation time", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Escalation time", {"1", "2", "3", "4", "5"}, "min"));
    m_selectable_item_widget_container->addWidget("Alarm Shallow ID", new SelectableIntItemWidget(m_selectable_item_widget_container, item_size, "Alarm Shallow ID", new IntValidator(0, 20000)));
    m_selectable_item_widget_container->addWidget("Alert Deep ID", new SelectableIntItemWidget(m_selectable_item_widget_container, item_size, "Alert Deep ID", new IntValidator(0, 20000)));
    m_selectable_item_widget_container->addWidget("Alert System ID", new SelectableIntItemWidget(m_selectable_item_widget_container, item_size, "Alert System ID", new IntValidator(0, 20000)));

    setupLayout();
}
