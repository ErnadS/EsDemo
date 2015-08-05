#include "setup_menu_screen.h"
#include <QMessageBox>
#include <QDebug>

void SetupMenuScreen::deactivateSystemWidgets()
{
    m_dl1_system->setActive(false);
    m_dl2_system->setActive(false);
    m_es_system->setActive(false);

    m_dl1_setup_menu->setVisible(false);
    m_dl2_setup_menu->setVisible(false);
    m_es_setup_menu->setVisible(false);
}

bool SetupMenuScreen::changeLayout() const
{
    QMessageBox message_box(QMessageBox::Question,
                                    "",
                                    "You are about to change the system type. Are you sure you want to continue?",
                                    QMessageBox::No | QMessageBox::Yes, (QWidget*)this,
                                    Qt::FramelessWindowHint);

    // TODO: Generalize style through controller class
    message_box.setStyleSheet("QPushButton { color: rgb(255, 255, 255); background-color: rgb(20, 20, 20); font: 16px; min-width: 230px; min-height: 40px;} QMessageBox { background-color: black; border: 2px solid rgb(80, 80, 80);} QLabel { color: rgb(255, 255, 255); font: 16px; text-align: justify; }");

    int return_status = message_box.exec();

    return return_status == QMessageBox::Yes;
}

SetupMenuScreen::SetupMenuScreen(QWidget* parent) : BaseScreen(parent)
{
    m_dl1_system = new SystemWidget(this, m_system_size, "SPEED", "DL1 SYS 1");
    m_dl2_system = new SystemWidget(this, m_system_size, "SPEED", "DL2 SYS 1");
    m_es_system = new SystemWidget(this, m_system_size, "DEPTH", "ES SYS 1");

    m_dl1_setup_menu = new ItemWidgetContainer(this, m_setup_menu_size, 5, {"RUNTIME SCREEN SETUP", "CALIBRATION", "ALERT SETUP", "DIAGNOSTICS", "DL1 SETUP", "COMMUNICATIONS SETUP", "AUX SETUP"});
    m_es_setup_menu = new ItemWidgetContainer(this, m_setup_menu_size, 5, {"RUNTIME SCREEN SETUP", "ALERT SETUP", "DIAGNOSTICS", "ES SETUP", "COMMUNICATIONS SETUP", "AUX SETUP", "HISTORY TOUCH SCREEN", "JB70 SETUP"});
    m_dl2_setup_menu = new ItemWidgetContainer(this, m_setup_menu_size, 5, {"RUNTIME SCREEN SETUP", "CALIBRATION", "ALERT SETUP", "DIAGNOSTICS", "DL2 SETUP", "COMMUNICATIONS SETUP", "AUX SETUP", "JB70 SETUP"});

    connect(m_dl1_setup_menu, SIGNAL(itemSelected(int)), this, SLOT(dl1SetupSelected(int)));
    connect(m_es_setup_menu, SIGNAL(itemSelected(int)), this, SLOT(esSetupSelected(int)));
    connect(m_dl2_setup_menu, SIGNAL(itemSelected(int)), this, SLOT(dl2SetupSelected(int)));

    connect(m_dl1_system, SIGNAL(clicked()), this, SLOT(dl1SystemClicked()));
    connect(m_dl2_system, SIGNAL(clicked()), this, SLOT(dl2SystemClicked()));
    connect(m_es_system, SIGNAL(clicked()), this, SLOT(esSystemClicked()));

    m_system_button = new Button(this, m_system_button_size, "Available Systems:", false);
}

void SetupMenuScreen::buttonClicked()
{
    m_navigation_controller.navigateBack();
}

void SetupMenuScreen::dl1SystemClicked()
{
    if (changeLayout() == true)
    {
        deactivateSystemWidgets();
        m_dl1_system->setActive(true);
        m_dl1_setup_menu->setVisible(true);
        m_navigation_controller.layoutChanged(SystemEnum::DL1_SYSTEM);
    }
}

void SetupMenuScreen::dl2SystemClicked()
{
    if (changeLayout() == true)
    {
        deactivateSystemWidgets();
        m_dl2_system->setActive(true);
        m_dl2_setup_menu->setVisible(true);
        m_navigation_controller.layoutChanged(SystemEnum::DL2_SYSTEM);
    }
}

void SetupMenuScreen::esSystemClicked()
{
    if (changeLayout() == true)
    {
        deactivateSystemWidgets();
        m_es_system->setActive(true);
        m_es_setup_menu->setVisible(true);
        m_navigation_controller.layoutChanged(SystemEnum::ES_SYSTEM);
    }
}

void SetupMenuScreen::dl1SetupSelected(int index)
{
    m_navigation_controller.navigate(SystemEnum::DL1_SYSTEM, index);
}

void SetupMenuScreen::esSetupSelected(int index)
{
    m_navigation_controller.navigate(SystemEnum::ES_SYSTEM, index);
}

void SetupMenuScreen::dl2SetupSelected(int index)
{
    m_navigation_controller.navigate(SystemEnum::DL2_SYSTEM, index);
}

void SetupMenuScreen::showEvent(QShowEvent*)
{
    deactivateSystemWidgets();
    SystemEnum system = m_navigation_controller.getSystemType();

    switch (system)
    {
        case SystemEnum::DL1_SYSTEM:
            m_dl1_system->setActive(true);
            m_dl1_setup_menu->setVisible(true);
            break;

        case SystemEnum::DL2_SYSTEM:
            m_dl2_system->setActive(true);
            m_dl2_setup_menu->setVisible(true);
            break;

        case SystemEnum::ES_SYSTEM:
            m_es_system->setActive(true);
            m_es_setup_menu->setVisible(true);
            break;
    }
}

void SetupMenuScreen::setupLayout()
{
    BaseScreen::setupLayout();

    QSize system_size(m_system_size.width() * m_width_scale, m_system_size.height() * m_height_scale);
    QSize system_button_size(m_system_button_size.width() * m_width_scale, m_system_button_size.height() * m_height_scale);

    m_dl1_system->resize(system_size);
    m_dl2_system->resize(system_size);
    m_es_system->resize(system_size);
    m_system_button->resize(system_button_size);

    QPoint first_column(m_first_column.x() * m_width_scale, m_first_column.y() * m_height_scale);
    int vertical_space = m_vertical_space * m_height_scale;

    m_dl1_system->move(first_column);
    m_es_system->move(first_column.x(), first_column.y() + system_size.height() + vertical_space);
    m_dl2_system->move(first_column.x(), first_column.y() + 2 * (system_size.height() + vertical_space));

    m_system_button->move(first_column.x() + 0.5f * system_size.width() - 0.5f * m_system_button->width(), first_column.y() - system_button_size.height());

    QSize setup_menu_size(m_setup_menu_size.width() * m_width_scale, m_setup_menu_size.height() * m_height_scale);
    QPoint setup_menu_pos(m_setup_menu_pos.x() * m_width_scale, m_setup_menu_pos.y() * m_height_scale);

    m_dl1_setup_menu->resize(setup_menu_size);
    m_dl1_setup_menu->move(setup_menu_pos);

    m_es_setup_menu->resize(setup_menu_size);
    m_es_setup_menu->move(setup_menu_pos);

    m_dl2_setup_menu->resize(setup_menu_size);
    m_dl2_setup_menu->move(setup_menu_pos);
}
