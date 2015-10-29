#include "dl2_calibration_setup_screen.h"
#include "dl2_calibration_status_setup_screen.h"
#include "dl2_calibration_speed_manual_gps_setup_screen.h"
#include "dl2_calibration_speed_manual_setup_screen.h"
#include "dl2_calibration_speed_sea_setup_screen.h"
#include "dl2_calibration_speed_auto_setup_screen.h"
#include "dl2_calibration_inst_angle_setup_screen.h"
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

    QSize speed_item_container_size(m_speed_item_container_size.width() * m_width_scale, m_speed_item_container_size.height() * m_height_scale);
    QPoint speed_item_container_pos(m_speed_item_container_pos.x() * m_width_scale, m_speed_item_container_pos.y() * m_height_scale);

    m_speed_item_container->resize(speed_item_container_size);
    m_speed_item_container->move(speed_item_container_pos);
    m_speed_item_container->raise();

    if (m_submenu_active == false)
    {
        m_item_container->show();
        m_speed_item_container->hide();
    }
    else
    {
        m_item_container->hide();
        m_speed_item_container->show();
    }
}

void Dl2CalibrationSetupScreen::menuClicked(int index)
{
    if ((index == 2) && (m_submenu_active == false))
    {
        m_submenu_active = true;
        m_speed_item_container->setActive(0);
        menuClicked(0);
    }
    else if ((index > 2) && (m_submenu_active == false))
    {
        // Skipping speed screens
        index += 3;
    }
    else if (m_submenu_active == true)
    {   // Skipping of first two screens
        index += 2;
    }

    m_layout->setCurrentIndex(index);

    setupLayout();
}

void Dl2CalibrationSetupScreen::navigateBackFromSubmenu()
{   m_submenu_active = false;
    m_item_container->setActive(0);
    menuClicked(0);
}

Dl2CalibrationSetupScreen::Dl2CalibrationSetupScreen(QWidget* parent) :
    MultiSetupScreen(parent)
{
    m_layout->addWidget(new Dl2CalibrationStatusSetupScreen(this));
    m_layout->addWidget(new Dl2CalibrationInstAngleSetupScreen(this));
    m_layout->addWidget(new Dl2CalibrationSpeedManualGpsSetupScreen(this));
    m_layout->addWidget(new Dl2CalibrationSpeedManualSetupScreen(this));
    m_layout->addWidget(new Dl2CalibrationSpeedSeaSetupScreen(this));
    m_layout->addWidget(new Dl2CalibrationSpeedAutoSetupScreen(this));
    m_layout->addWidget(new Dl2CalibrationTiltSetupScreen(this));
    m_layout->addWidget(new Dl2CalibrationTempSetupScreen(this));

    for (int i = 2; i < 6; i++)
    {
        Dl2CalibrationSpeedSetupScreen* speed_setup_screen = dynamic_cast<Dl2CalibrationSpeedSetupScreen*>(m_layout->widget(i));
        connect(speed_setup_screen, SIGNAL(backButtonClicked()), this, SLOT(navigateBackFromSubmenu()));
    }

    m_item_container = new HorizontalItemWidgetContainer(this, m_item_container_size, m_item_size, m_item_sep);
    m_item_container->addWidget(new HorizontalItemWidget(m_item_container, m_item_size, "Status"));
    m_item_container->addWidget(new HorizontalItemWidget(m_item_container, m_item_size, "Inst Angle"));
    m_item_container->addWidget(new HorizontalItemWidget(m_item_container, m_item_size, "Speed"));
    m_item_container->addWidget(new HorizontalItemWidget(m_item_container, m_item_size, "Tilt"));
    m_item_container->addWidget(new HorizontalItemWidget(m_item_container, m_item_size, "Temp"));
    m_item_container->setActive(0);

    m_speed_item_container = new HorizontalItemWidgetContainer(this, m_speed_item_container_size, m_item_size, m_item_sep);
    m_speed_item_container->addWidget(new HorizontalItemWidget(m_speed_item_container, m_speed_item_size, "Manual\nfrom GPS"));
    m_speed_item_container->addWidget(new HorizontalItemWidget(m_speed_item_container, m_speed_item_size, "Manual\ncalib"));
    m_speed_item_container->addWidget(new HorizontalItemWidget(m_speed_item_container, m_speed_item_size, "Sea\ntest"));
    m_speed_item_container->addWidget(new HorizontalItemWidget(m_speed_item_container, m_speed_item_size, "Auto\ncalib"));
    m_speed_item_container->setActive(0);

    connect(m_item_container, SIGNAL(clicked(int)), this, SLOT(menuClicked(int)));
    connect(m_speed_item_container, SIGNAL(clicked(int)), this, SLOT(menuClicked(int)));

    setLayout(m_layout);

    setupLayout();
}
