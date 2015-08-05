#include "navigation_controller.h"
#include "screen/runtime_screen.h"
#include "screen/es_runtime_screen.h"
#include "screen/boat_menu_screen.h"
#include "screen/setup_menu_screen.h"
#include <stdexcept>
#include <QDebug>

#include "gui/screen/dl1_alert_setup_screen.h"
#include "gui/screen/dl1_aux_setup_screen.h"
#include "gui/screen/dl1_communication_setup_screen.h"
#include "gui/screen/dl1_calibration_setup_screen.h"
#include "gui/screen/dl1_diagnostic_setup_screen.h"
#include "gui/screen/dl1_runtime_setup_screen.h"
#include "gui/screen/dl1_setup_screen.h"

#include "gui/screen/dl2_alert_setup_screen.h"
#include "gui/screen/dl2_aux_setup_screen.h"
#include "gui/screen/dl2_calibration_setup_screen.h"
#include "gui/screen/dl2_diagnostic_setup_screen.h"
#include "gui/screen/dl2_jb70_setup_screen.h"
#include "gui/screen/dl2_runtime_setup_screen.h"
#include "gui/screen/dl2_setup_screen.h"
#include "gui/screen/dl2_communication_setup_screen.h"

#include "gui/screen/es_alert_setup_screen.h"
#include "gui/screen/es_aux_setup_screen.h"
#include "gui/screen/es_communication_setup_screen.h"
#include "gui/screen/es_diagnostic_setup_screen.h"
#include "gui/screen/es_jb70_setup_screen.h"
#include "gui/screen/es_history_setup_screen.h"
#include "gui/screen/es_runtime_setup_screen.h"
#include "gui/screen/es_setup_screen.h"

QWidget* NavigationController::createSetupScreen(QWidget* parent, SetupScreenType setup_screen_type) const
{
    switch (setup_screen_type)
    {
        case DL1_ALERT_SETUP:
            return new Dl1AlertSetupScreen(parent);

        case DL1_AUX_SETUP:
            return new Dl1AuxSetupScreen(parent);

        case DL1_COMMUNICATION_SETUP:
            return new Dl1CommunicationSetupScreen(parent);

        case DL1_CALIBRATION_SETUP:
            return new Dl1CalibrationSetupScreen(parent);

        case DL1_DIAGNOSTIC_SETUP:
            return new Dl1DiagnosticSetupScreen(parent);

        case DL1_RUNTIME_SETUP:
            return new Dl1RuntimeSetupScreen(parent);

        case DL1_SETUP:
            return new Dl1SetupScreen(parent);

        case DL2_ALERT_SETUP:
            return new Dl2AlertSetupScreen(parent);

        case DL2_AUX_SETUP:
            return new Dl2AuxSetupScreen(parent);

        case DL2_CALIBRATION_SETUP:
            return new Dl2CalibrationSetupScreen(parent);

        case DL2_DIAGNOSTIC_SETUP:
            return new Dl2DiagnosticSetupScreen(parent);

        case DL2_JB70_SETUP:
            return new Dl2Jb70SetupScreen(parent);

        case DL2_RUNTIME_SETUP:
            return new Dl2RuntimeSetupScreen(parent);

        case DL2_SETUP:
            return new Dl2RuntimeSetupScreen(parent);

        case DL2_COMMUNICATION_SETUP:
            return new Dl2CommunicationSetupScreen(parent);

        case ES_ALERT_SETUP:
            return new EsAlertSetupScreen(parent);

        case ES_AUX_SETUP:
            return new EsAuxSetupScreen(parent);

        case ES_COMMUNICATION_SETUP:
            return new EsCommunicationSetupScreen(parent);

        case ES_DIAGNOSTIC_SETUP:
            return new EsDiagnosticSetupScreen(parent);

        case ES_JB70_SETUP:
            return new EsJb70SetupScreen(parent);

        case ES_HISTORY_SETUP:
            return new EsHistorySetupScreen(parent);

        case ES_RUNTIME_SETUP:
            return new EsRuntimeSetupScreen(parent);

        case ES_SETUP:
            return new EsSetupScreen(parent);
    }

    throw std::invalid_argument("Provided argument is not in enum range.");
}

QStackedLayout* NavigationController::createLayout(QWidget* parent, SystemEnum system)
{
    QStackedLayout* layout = new QStackedLayout();

    const QVector<RuntimeScreenType>* p{nullptr};
    const QVector<SetupScreenType>* q{nullptr};

    for (int i = 0; i < 3; i++)
    {
        QString title;
        switch (i)
        {
            case 0:
                p = &m_dl1_system_screen_vector;
                title = "DL1 Speed Log";
                break;

            case 1:
                p = &m_dl2_system_screen_vector;
                title = "DL2 Speed Log";
                break;

            case 2:
                p = &m_es_system_screen_vector;
                title = "ES1 Echosounder";
                break;
        }

        for (auto e: *p)
        {
            RuntimeScreen* runtime_screen = (e != RuntimeScreenType::RUNTIME_ES) ? new RuntimeScreen(parent, e) : new EsRuntimeScreen(parent, e);
            runtime_screen->titleWidget()->setTitle(title);

            layout->addWidget(runtime_screen);
        }
    }

    SetupMenuScreen* setup_menu_screen = new SetupMenuScreen(parent);
    layout->addWidget(setup_menu_screen);

    BoatMenuScreen* boat_menu_screen = new BoatMenuScreen(parent);
    layout->addWidget(boat_menu_screen);

    for (int i = 0; i < 3; i++)
    {
        QString title;
        switch (i)
        {
            case 0:
                q = &m_dl1_setup_screen_vector;
                title = "DL1 Speed Log";
                break;

            case 1:
                q = &m_dl2_setup_screen_vector;
                title = "DL2 Speed Log";
                break;

            case 2:
                q = &m_es_setup_screen_vector;
                title = "ES1 Echosounder";
                break;
        }

        for (auto e: *q)
        {
            SetupScreen* setup_screen = dynamic_cast<SetupScreen*>(createSetupScreen(parent, e));
            setup_screen->titleWidget()->setTitle(title);

            layout->addWidget(setup_screen);
        }
    }

    m_system_type = system;

    return layout;
}

int NavigationController::layoutStartIndex(SystemEnum system) const
{
    switch (system)
    {
        case SystemEnum::DL1_SYSTEM:
            return 0;

        case SystemEnum::DL2_SYSTEM:
            return layoutStartIndex(SystemEnum::DL1_SYSTEM) + layoutSize(SystemEnum::DL1_SYSTEM);

        case SystemEnum::ES_SYSTEM:
            return layoutStartIndex(SystemEnum::DL2_SYSTEM) + layoutSize(SystemEnum::DL2_SYSTEM);
    }

    throw std::invalid_argument("Provided argument is not in enum range.");
}

int NavigationController::layoutSize(SystemEnum system) const
{
    switch (system)
    {
        case SystemEnum::DL1_SYSTEM:
            return m_dl1_system_screen_vector.size();

        case SystemEnum::DL2_SYSTEM:
            return m_dl2_system_screen_vector.size();

        case SystemEnum::ES_SYSTEM:
            return m_es_system_screen_vector.size();
    }

    throw std::invalid_argument("Provided argument is not in enum range.");
}

int NavigationController::setupStartIndex(SystemEnum system) const
{
    int start_index = layoutStartIndex(SystemEnum::ES_SYSTEM) + layoutSize(SystemEnum::ES_SYSTEM) + 2;

    switch (system)
    {
        // dl1, dl2, es
        case SystemEnum::DL1_SYSTEM:
            return start_index;

        case SystemEnum::DL2_SYSTEM:
            return start_index + setupMenuSize(SystemEnum::DL1_SYSTEM);

        case SystemEnum::ES_SYSTEM:
            return setupStartIndex(SystemEnum::DL2_SYSTEM) + setupMenuSize(SystemEnum::DL2_SYSTEM);
    }

    throw std::invalid_argument("Provided argument is not in enum range.");
}

int NavigationController::setupMenuSize(SystemEnum system) const
{
    switch (system)
    {
        case SystemEnum::DL1_SYSTEM:
            return m_dl1_setup_screen_vector.size();

        case SystemEnum::DL2_SYSTEM:
            return m_dl2_setup_screen_vector.size();

        case SystemEnum::ES_SYSTEM:
            return m_es_setup_screen_vector.size();
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
    int index = layoutStartIndex(SystemEnum::ES_SYSTEM) + layoutSize(SystemEnum::ES_SYSTEM);

    switch (setup_menu_type)
    {
        case SETUP_MENU:
            m_layout->setCurrentIndex(index);
            break;

        case BOAT_MENU:
            m_layout->setCurrentIndex(index + 1);
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

void NavigationController::navigate(SystemEnum system, int setup_screen_index)
{
    m_previous_index = m_layout->currentIndex();

    int index = setupStartIndex(system) + setup_screen_index;
    m_layout->setCurrentIndex(index);
}

void NavigationController::setEmbedded(bool embedded)
{
    m_embedded = embedded;
}

bool NavigationController::isEmbedded() const
{
    return m_embedded;
}
