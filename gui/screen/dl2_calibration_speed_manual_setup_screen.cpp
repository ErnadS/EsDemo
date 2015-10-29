#include "dl2_calibration_speed_manual_setup_screen.h"
#include "gui/widget/selectable_enum_item_widget.h"
#include "gui/widget/selectable_float_item_widget.h"

Dl2CalibrationSpeedManualSetupScreen::Dl2CalibrationSpeedManualSetupScreen(QWidget* parent) : Dl2CalibrationSpeedSetupScreen(parent)
{
    m_title_widget->setTitle("Manual");

    QSize item_size = m_selectable_item_widget_container->getItemBaseSize();
    m_selectable_item_widget_container->addWidget("Calibration point", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Calibration point", {"1", "2", "3", "4", "5"}));
    m_selectable_item_widget_container->addWidget("Real Speed", new SelectableFloatItemWidget(m_selectable_item_widget_container, item_size, "Real Speed", "kn", new Validator("dummy")));
    m_selectable_item_widget_container->addWidget("Measured STW", new SelectableFloatItemWidget(m_selectable_item_widget_container, item_size, "Measured STW", "kn", new Validator("dummy")));
    m_selectable_item_widget_container->addWidget("Measured SOG", new SelectableFloatItemWidget(m_selectable_item_widget_container, item_size, "Measured SOG", "kn", new Validator("dummy")));
    m_selectable_item_widget_container->addWidget("Point source", new SelectableEnumItemWidget(m_selectable_item_widget_container, item_size, "Point source", {"Default", "Sea test"}));


    setupLayout();
}
