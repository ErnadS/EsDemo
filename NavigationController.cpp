#include "NavigationController.h"
#include "RuntimeScreen.h"
#include "SetupMenuScreen.h"
#include "BoatMenuScreen.h"

QStackedLayout* NavigationController::createLayout(QWidget* parent, SystemEnum system)
{
    QStackedLayout* layout = new QStackedLayout();

    const QVector<RuntimeScreenType>* p{nullptr};

    for (int i = 0; i < 4; i++)
    {
        switch (i)
        {
            case 0:
                p = &m_dl1_system_screen_vector;
                break;

            case 1:
                p = &m_dl2_system_1_screen_vector;
                break;

            case 2:
                p = &m_dl2_system_2_screen_vector;
                break;

            case 3:
                p = &m_es_system_screen_vector;
                break;
        }

        for (auto e: *p)
        {
            RuntimeScreen* runtime_screen = new RuntimeScreen(parent, e);
            layout->addWidget(runtime_screen);
        }
    }

    SetupMenuScreen* setup_menu_screen = new SetupMenuScreen(parent);
    layout->addWidget(setup_menu_screen);

    BoatMenuScreen* boat_menu_screen = new BoatMenuScreen(parent);
    layout->addWidget(boat_menu_screen);

    m_system_type = system;

    return layout;
}

int NavigationController::layoutStartIndex(SystemEnum system) const
{
    switch (system)
    {
        case SystemEnum::DL1_SYSTEM:
            return 0;

        case SystemEnum::DL2_SYSTEM_1:
            return layoutStartIndex(SystemEnum::DL1_SYSTEM) + layoutSize(SystemEnum::DL1_SYSTEM);

        case SystemEnum::DL2_SYSTEM_2:
            return layoutStartIndex(SystemEnum::DL2_SYSTEM_1) + layoutSize(SystemEnum::DL2_SYSTEM_1);

        case SystemEnum::ES_SYSTEM:
            return layoutStartIndex(SystemEnum::DL2_SYSTEM_2) + layoutSize(SystemEnum::DL2_SYSTEM_2);
    }

    throw std::invalid_argument("Provided argument is not in enum range.");
}

int NavigationController::layoutSize(SystemEnum system) const
{
    switch (system)
    {
        case SystemEnum::DL1_SYSTEM:
            return m_dl1_system_screen_vector.size();

        case SystemEnum::DL2_SYSTEM_1:
            return m_dl2_system_1_screen_vector.size();

        case SystemEnum::DL2_SYSTEM_2:
            return m_dl2_system_2_screen_vector.size();

        case SystemEnum::ES_SYSTEM:
            return m_es_system_screen_vector.size();
    }

    throw std::invalid_argument("Provided argument is not in enum range.");
}

QStackedLayout* NavigationController::getLayout(QWidget* parent, SystemEnum system)
{
    if (m_layout == nullptr)
    {
        m_layout = createLayout(parent, system);
    }

    m_layout->setCurrentIndex(layoutStartIndex(system));
    m_previous_index = layoutStartIndex(system);

    return m_layout;
}

SystemEnum NavigationController::getSystemType() const
{
    return m_system_type;
}

void NavigationController::navigateLeft()
{
    int index = m_layout->currentIndex() - 1;

    int start_index = layoutStartIndex(m_system_type);
    int size = layoutSize(m_system_type);

    if (index < start_index)
    {
        index = start_index + size - 1;
    }

    m_layout->setCurrentIndex(index);
}

void NavigationController::navigateRight()
{
    int index = m_layout->currentIndex() + 1;

    int start_index = layoutStartIndex(m_system_type);
    int size = layoutSize(m_system_type);

    if (index == start_index + size)
    {
        index = start_index;
    }

    m_layout->setCurrentIndex(index);
}

void NavigationController::navigate(SetupMenuType setup_menu_type)
{
    m_previous_index = m_layout->currentIndex();

    switch (setup_menu_type)
    {
        case SETUP_MENU:
            m_layout->setCurrentIndex(m_layout->count() - 2);
            break;

        case BOAT_MENU:
            m_layout->setCurrentIndex(m_layout->count() - 1);
            break;
    }
}

void NavigationController::navigateBack()
{
    if (m_switch_layout == false)
    {
        m_layout->setCurrentIndex(m_previous_index);
    }
    else
    {
        m_switch_layout = false;
        int index = layoutStartIndex(m_system_type);
        m_layout->setCurrentIndex(index);
    }
}

void NavigationController::layoutChanged(SystemEnum system)
{
    m_system_type = system;
    m_switch_layout = true;
}
