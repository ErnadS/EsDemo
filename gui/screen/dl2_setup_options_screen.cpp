#include "dl2_setup_options_screen.h"

#include "gui/widget/selectable_enum_item_widget.h"

Dl2SetupOptionsScreen::Dl2SetupOptionsScreen(QWidget* parent) :
    SetupScreen(parent)
{
    titleWidget()->setTitle("DL2 Speed Log");

    QSize item_size = m_selectable_item_widget_container->getItemBaseSize();

    m_selectable_item_widget_container->addWidget("Unlock options", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Unlock options", {"Code"}));
    m_selectable_item_widget_container->addWidget("Synchronize", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Synchronize", {"Locked"}));
    m_selectable_item_widget_container->addWidget("1% accuracy", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "1% accuracy", {"Locked"}));
    m_selectable_item_widget_container->addWidget("Docking", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Docking", {"Locked"}));
    m_selectable_item_widget_container->addWidget("Auto GPS on NMEA", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Auto GPS on NMEA", {"Locked"}));
    m_selectable_item_widget_container->addWidget("Temp Compensation", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Temp Compensation", {"Locked"}));
    m_selectable_item_widget_container->addWidget("Tilt Compensation", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Temp Compensation", {"Tilt Compensation"}));

    setupLayout();
}
