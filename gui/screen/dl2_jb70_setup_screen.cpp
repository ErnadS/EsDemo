#include "dl2_jb70_setup_screen.h"

#include "gui/widget/selectable_ip_item_widget.h"
#include "gui/widget/selectable_string_item_widget.h"
#include "gui/widget/selectable_enum_item_widget.h"

Dl2Jb70SetupScreen::Dl2Jb70SetupScreen(QWidget* parent) :
    SetupScreen(parent)
{
    QSize item_size = m_selectable_item_widget_container->getItemBaseSize();

    m_selectable_item_widget_container->addWidget("IP ADDRESS", new SelectableIpItemWidget(m_selectable_item_widget_container, item_size, "IP ADDRESS"));
    m_selectable_item_widget_container->addWidget("LOCAL SFI", new SelectableStringItemWidget(m_selectable_item_widget_container, item_size, "LOCAL SFI"));
    m_selectable_item_widget_container->addWidget("GROUP", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "GROUP", {"NAVD"}));
    m_selectable_item_widget_container->addWidget("Alarm SFI", new SelectableStringItemWidget(m_selectable_item_widget_container, item_size, "Alarm SFI"));
    m_selectable_item_widget_container->addWidget("System Name", new SelectableStringItemWidget(m_selectable_item_widget_container, item_size, "System Name"));

    setupLayout();
}
