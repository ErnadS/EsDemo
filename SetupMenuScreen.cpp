#include "SetupMenuScreen.h"
#include <QMessageBox>

void SetupMenuScreen::deactivateSystemWidgets()
{
    m_dl1_system->setActive(false);
    m_dl2_system_1->setActive(false);
    m_dl2_system_2->setActive(false);
    m_es_system->setActive(false);
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
    m_dl2_system_1 = new SystemWidget(this, m_system_size, "SPEED", "DL2 SYS 1");
    m_dl2_system_2 = new SystemWidget(this, m_system_size, "SPEED", "DL2 SYS 2");
    m_es_system = new SystemWidget(this, m_system_size, "DEPTH", "ES SYS 1");

    connect(m_dl1_system, SIGNAL(pressed()), this, SLOT(dl1SystemPressed()));
    connect(m_dl2_system_1, SIGNAL(pressed()), this, SLOT(dl2System1Pressed()));
    connect(m_dl2_system_2, SIGNAL(pressed()), this, SLOT(dl2System2Pressed()));
    connect(m_es_system, SIGNAL(pressed()), this, SLOT(esSystemPressed()));

    connect(this, SIGNAL(layoutChanged(SystemEnum)), &m_navigation_controller, SLOT(layoutChanged(SystemEnum)));
}

void SetupMenuScreen::buttonClicked()
{
    emit navigateBack();
}

void SetupMenuScreen::dl1SystemPressed()
{
    if (changeLayout() == true)
    {
        deactivateSystemWidgets();
        m_dl1_system->setActive(true);
        emit layoutChanged(SystemEnum::DL1_SYSTEM);
    }
}

void SetupMenuScreen::dl2System1Pressed()
{
    if (changeLayout() == true)
    {
        deactivateSystemWidgets();
        m_dl2_system_1->setActive(true);
        emit layoutChanged(SystemEnum::DL2_SYSTEM_1);
    }
}

void SetupMenuScreen::dl2System2Pressed()
{
    if (changeLayout() == true)
    {
        deactivateSystemWidgets();
        m_dl2_system_2->setActive(true);
        emit layoutChanged(SystemEnum::DL2_SYSTEM_2);
    }
}

void SetupMenuScreen::esSystemPressed()
{
    if (changeLayout() == true)
    {
        deactivateSystemWidgets();
        m_es_system->setActive(true);
        emit layoutChanged(SystemEnum::ES_SYSTEM);
    }
}

void SetupMenuScreen::showEvent(QShowEvent*)
{
    deactivateSystemWidgets();
    SystemEnum system = m_navigation_controller.getSystemType();

    switch (system)
    {
        case SystemEnum::DL1_SYSTEM:
            m_dl1_system->setActive(true);
            break;

        case SystemEnum::DL2_SYSTEM_1:
            m_dl2_system_1->setActive(true);
            break;

        case SystemEnum::DL2_SYSTEM_2:
            m_dl2_system_2->setActive(true);
            break;

        case SystemEnum::ES_SYSTEM:
            m_es_system->setActive(true);
            break;
    }
}

void SetupMenuScreen::setupLayout()
{
    BaseScreen::setupLayout();

    QSize system_size(m_system_size.width() * m_width_scale, m_system_size.height() * m_height_scale);

    m_dl1_system->resize(system_size);
    m_dl2_system_1->resize(system_size);
    m_dl2_system_2->resize(system_size);
    m_es_system->resize(system_size);

    QPoint first_column(m_first_column.x() * m_width_scale, m_first_column.y() * m_height_scale);
    QPoint second_column(m_second_column.x() * m_width_scale, m_second_column.y() * m_height_scale);
    int vertical_space = m_vertical_space * m_height_scale;

    m_dl1_system->move(first_column);
    m_dl2_system_1->move(second_column);

    m_dl2_system_2->move(first_column.x(), first_column.y() + system_size.height() + vertical_space);
    m_es_system->move(second_column.x(), second_column.y() + system_size.height() + vertical_space);
}
