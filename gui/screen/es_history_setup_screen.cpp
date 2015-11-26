#include "es_history_setup_screen.h"
#include "gui/widget/selectable_enum_item_widget.h"
#include "gui/widget/selectable_bool_item_widget.h"
#include "gui/widget/selectable_string_item_widget.h"
//#include "gui/widget/selectable_date_time_item_widget.h"

EsHistorySetupScreen::EsHistorySetupScreen(QWidget* parent) :
    SetupScreen(parent)
{
    QSize item_size = m_selectable_item_widget_container->getItemBaseSize();


    // TO DO - recalculate - long term log hours, raw data hours, Log Period
    // TO DO -
    const QString valid("\\b(0?[1-9]|[12][0-9]|3[01])[- /.](0?[1-9]|1[012])[- /.](19|20)?[0-9]{2}\\b");
    const QString nonvalid("Date Not Valid");
    m_selectable_item_widget_container->addWidget("Mode ", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Mode", {"Loop", "Stop"}));
    m_selectable_item_widget_container->addWidget("Start", new SelectableStringItemWidget(m_selectable_item_widget_container, item_size, "Start", new RegexValidator(valid,nonvalid)));
    m_selectable_item_widget_container->addWidget("Stop", new SelectableStringItemWidget(m_selectable_item_widget_container, item_size, "Stop", new RegexValidator(valid,nonvalid)));
    m_selectable_item_widget_container->addWidget("Long Term Log to", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Long Term Log to", {"Long Log to: SD\n(2000h)","Long Log to: USB\n(2500h)", " Long Log to: Internal\n(600h)","Long Log to: Disabled)"}));
    m_selectable_item_widget_container->addWidget("Log Raw Data", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Log Raw Data", {"On", "Off"}));
    m_selectable_item_widget_container->addWidget("Log Peripherals", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Log Peripherals", {"On", "Off"}));
    m_selectable_item_widget_container->addWidget("Log Period", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Log Period", {"Log Period: Continuous", "Log Period: 1 min", "Log Period: 15 min", "Log Period: 30 min"}));
    m_selectable_item_widget_container->addWidget("Dump Internal To Disk", new SelectableBoolItemWidget(m_selectable_item_widget_container, item_size, "Dump Internal To Disk", "True", "False"));
    m_selectable_item_widget_container->addWidget("Print", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Printer", {"EPSON LQ450", "Via Service Software"}));

    setupLayout();
}

void EsHistorySetupScreen::paintEvent(QPaintEvent *)
{

}
