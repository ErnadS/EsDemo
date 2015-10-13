#include "dl2_calibration_setup_screen.h"
#include "dl2_calibration_status_setup_screen.h"
#include "dl2_calibration_inst_angle_setup_screen.h"
#include "dl2_calibration_speed_setup_screen.h"
#include "dl2_calibration_tilt_setup_screen.h"
#include "dl2_calibration_temp_setup_screen.h"

void Dl2CalibrationSetupScreen::setupLayout()
{
    MultiSetupScreen::setupLayout();

    QSize item_container_size(m_item_container_size.width() * m_width_scale, m_item_container_size.height() * m_height_scale);
    QPoint item_container_pos(m_item_container_pos.x() * m_width_scale, m_item_container_pos.y() * m_height_scale);

    m_item_container->resize(item_container_size);
    m_item_container->move(item_container_pos);
    m_item_container->raise();
}

void Dl2CalibrationSetupScreen::menuClicked(int index)
{
    m_layout->setCurrentIndex(index);
    setupLayout();
}


Dl2CalibrationSetupScreen::Dl2CalibrationSetupScreen(QWidget* parent) :
    MultiSetupScreen(parent)
{
    m_layout->addWidget(new Dl2CalibrationStatusSetupScreen(this));
    m_layout->addWidget(new Dl2CalibrationInstAngleSetupScreen(this));
    m_layout->addWidget(new Dl2CalibrationSpeedSetupScreen(this));
    m_layout->addWidget(new Dl2CalibrationTempSetupScreen(this));
    m_layout->addWidget(new Dl2CalibrationTiltSetupScreen(this));

    m_item_container = new HorizontalItemWidgetContainer(this, m_item_container_size, m_item_size, m_item_sep);
    m_item_container->addWidget(new HorizontalItemWidget(m_item_container, m_item_size, "Status"));
    m_item_container->addWidget(new HorizontalItemWidget(m_item_container, m_item_size, "INST Angle"));
    m_item_container->addWidget(new HorizontalItemWidget(m_item_container, m_item_size, "Speed"));
    m_item_container->addWidget(new HorizontalItemWidget(m_item_container, m_item_size, "Tilt"));
    m_item_container->addWidget(new HorizontalItemWidget(m_item_container, m_item_size, "TEMP"));
    m_item_container->setActive(0);

    connect(m_item_container, SIGNAL(clicked(int)), this, SLOT(menuClicked(int)));

    setLayout(m_layout);

    setupLayout();
}
