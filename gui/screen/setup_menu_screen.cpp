#include "setup_menu_screen.h"
#include <QMessageBox>
#include <QPainter>
#include <QDebug>

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
    QList<QString> type_list, name_list;


    for (int i = 0; i < m_navigation_controller.systemCount(); i++)
    {
        QString type = "SPEED";
        auto system = m_navigation_controller.system(i);

        if (system == SystemEnum::ES_SYSTEM)
            type = "DEPTH";

        QString prefix;

        switch (system)
        {
            case SystemEnum::DL1_SYSTEM:
                prefix = "DL1";
                break;

            case SystemEnum::DL2_SYSTEM:
                prefix = "DL2";
                break;

            case SystemEnum::ES_SYSTEM:
                prefix = "ES";
                break;
        }

        QString system_name = prefix + " SYS " + QString::number(i + 1);

        type_list << type;
        name_list << system_name;
    }

    m_system_widget_container = new SystemWidgetContainer(this, m_system_menu_size, 3, type_list, name_list);

    m_cu_m001_setup_button = new ItemWidget(this, m_button_size, "CU-M001 SETUP", EVEN);
    m_system_setup_button = new ItemWidget(this, m_button_size, "SYSTEM SETUP");

    m_dl1_setup_menu = new ItemWidgetContainer(this, m_setup_menu_size, 5, {"RUNTIME SCREEN SETUP", "CALIBRATION", "ALERT SETUP", "DIAGNOSTICS", "DL1 SETUP", "COMMUNICATIONS SETUP", "AUX SETUP"});
    m_es_setup_menu = new ItemWidgetContainer(this, m_setup_menu_size, 5, {"RUNTIME SCREEN SETUP", "ALERT SETUP", "DIAGNOSTICS", "ES SETUP", "COMMUNICATIONS SETUP", "AUX SETUP", "HISTORY TOUCH SCREEN", "JB70 SETUP"});
    m_dl2_setup_menu = new ItemWidgetContainer(this, m_setup_menu_size, 5, {"RUNTIME SCREEN SETUP", "CALIBRATION", "ALERT SETUP", "DIAGNOSTICS", "DL2 SETUP", "COMMUNICATIONS SETUP", "AUX SETUP", "JB70 SETUP"});

    // Initializing default system menu
    m_dl1_setup_menu->hide();
    m_es_setup_menu->hide();
    m_dl2_setup_menu->hide();

    auto system = m_navigation_controller.system(m_navigation_controller.systemIndex());

    switch (system)
    {
        case SystemEnum::DL1_SYSTEM:
            m_dl1_setup_menu->show();
            break;

        case SystemEnum::DL2_SYSTEM:
            m_dl2_setup_menu->show();
            break;

        case SystemEnum::ES_SYSTEM:
            m_es_setup_menu->show();
            break;
    }

    connect(m_system_widget_container, SIGNAL(itemSelected(int)), this, SLOT(systemSelected(int)));

    connect(m_cu_m001_setup_button, SIGNAL(pressed(const ItemWidget*)), this, SLOT(cuM001SetupPressed(const ItemWidget*)));
    connect(m_system_setup_button, SIGNAL(pressed(const ItemWidget*)), this, SLOT(systemSetupPressed(const ItemWidget*)));

    connect(m_dl1_setup_menu, SIGNAL(itemSelected(int)), this, SLOT(dl1SetupSelected(int)));
    connect(m_es_setup_menu, SIGNAL(itemSelected(int)), this, SLOT(esSetupSelected(int)));
    connect(m_dl2_setup_menu, SIGNAL(itemSelected(int)), this, SLOT(dl2SetupSelected(int)));

    connect(&m_navigation_controller, SIGNAL(systemAdded(SystemEnum)), this, SLOT(systemAdded(SystemEnum)));
    connect(&m_navigation_controller, SIGNAL(systemRemoved(int)), this, SLOT(systemRemoved(int)));

    m_system_widget_container->setActive(m_navigation_controller.systemIndex());
}

void SetupMenuScreen::buttonClicked()
{
    m_navigation_controller.navigateBack();
}

void SetupMenuScreen::systemSelected(int index)
{
    if (changeLayout() == true)
    {
        m_system_widget_container->setActive(index);

        auto system = m_navigation_controller.system(index);

        switch (system)
        {
            case SystemEnum::DL1_SYSTEM:
                m_dl1_setup_menu->show();
                m_dl1_setup_menu->resetRotationOffset();
                m_dl2_setup_menu->hide();
                m_es_setup_menu->hide();
                break;

            case SystemEnum::DL2_SYSTEM:
                m_dl1_setup_menu->hide();
                m_dl2_setup_menu->show();
                m_dl2_setup_menu->resetRotationOffset();
                m_es_setup_menu->hide();
                break;

            case SystemEnum::ES_SYSTEM:
                m_dl1_setup_menu->hide();
                m_dl2_setup_menu->hide();
                m_es_setup_menu->show();
                m_es_setup_menu->resetRotationOffset();
                break;
        }

        m_navigation_controller.layoutChanged(index);
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

void SetupMenuScreen::cuM001SetupPressed(const ItemWidget*)
{
    m_navigation_controller.navigate(CU_SETUP, false);
}

void SetupMenuScreen::systemSetupPressed(const ItemWidget*)
{
    m_navigation_controller.navigate(SYSTEM_SETUP, false);
}

void SetupMenuScreen::systemAdded(SystemEnum system)
{
    QString type = system == SystemEnum::ES_SYSTEM ? "Depth" : "Speed";

    QString prefix;

    switch (system)
    {
        case SystemEnum::DL1_SYSTEM:
            prefix = "DL1";
            break;

        case SystemEnum::DL2_SYSTEM:
            prefix = "DL2";
            break;

        case SystemEnum::ES_SYSTEM:
            prefix = "ES";
            break;
    }

    QString name = prefix + " SYS " + QString::number(m_navigation_controller.systemCount());

    m_system_widget_container->addSystem(type, name);
}

void SetupMenuScreen::systemRemoved(int index)
{
    qDebug() << "System removed!" << index;
}

void SetupMenuScreen::setupLayout()
{
    BaseScreen::setupLayout();

    QSize system_menu_size(m_system_menu_size.width() * m_width_scale, m_system_menu_size.height() * m_height_scale);
    QPoint system_menu_pos(m_system_menu_pos.x() * m_width_scale, m_system_menu_pos.y() * m_height_scale);

    QSize setup_menu_size(m_setup_menu_size.width() * m_width_scale, m_setup_menu_size.height() * m_height_scale);
    QPoint setup_menu_pos(m_setup_menu_pos.x() * m_width_scale, m_setup_menu_pos.y() * m_height_scale);

    QSize button_size(m_button_size.width() * m_width_scale, m_button_size.height() * m_height_scale);
    QPoint button_pos(m_button_pos.x() * m_width_scale, m_button_pos.y() * m_height_scale);

    m_system_widget_container->resize(system_menu_size);
    m_system_widget_container->move(system_menu_pos);

    m_dl1_setup_menu->resize(setup_menu_size);
    m_dl1_setup_menu->move(setup_menu_pos);

    m_es_setup_menu->resize(setup_menu_size);
    m_es_setup_menu->move(setup_menu_pos);

    m_dl2_setup_menu->resize(setup_menu_size);
    m_dl2_setup_menu->move(setup_menu_pos);

    m_cu_m001_setup_button->resize(button_size);
    m_cu_m001_setup_button->move(button_pos);

    m_system_setup_button->resize(button_size);
    m_system_setup_button->move(button_pos.x(), button_pos.y() + button_size.height());
}