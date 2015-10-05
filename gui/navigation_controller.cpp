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

#include "gui/screen/cu_setup_screen.h"
#include "gui/screen/system_setup_screen.h"

#include <QDebug>

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
            return new Dl2SetupScreen(parent);

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

QStackedLayout* NavigationController::createLayout(QWidget* parent)
{
    m_parent = parent;
    QStackedLayout* layout = new QStackedLayout();

    // First three screens are SetupMenuScreen, CuSetupScreen and SystemSetupScreen by default
    SetupMenuScreen* setup_menu_screen = new SetupMenuScreen(parent);
    setup_menu_screen->titleWidget()->setTitle("Setup");
    layout->addWidget(setup_menu_screen);

    CuSetupScreen* cu_setup_screen = new CuSetupScreen(parent);
    cu_setup_screen->titleWidget()->setTitle("CU-M001 Setup");
    layout->addWidget(cu_setup_screen);

    SystemSetupScreen* system_setup_screen = new SystemSetupScreen(parent);
    system_setup_screen->titleWidget()->setTitle("System Setup");
    layout->addWidget(system_setup_screen);

    for (auto system_type: m_system_vector)
    {
        addSystemScreens(layout, system_type);
    }

    layout->setCurrentIndex(layoutStartIndex(m_system_index));
    m_previous_index = layoutStartIndex(m_system_index);

    return layout;
}

int NavigationController::layoutStartIndex(int system_index) const
{
    // Start index starts from 3 because first three screens are fixed
    int start_index = 3;

    if ((system_index < 0) || (m_system_index >= m_system_vector.size()))
        throw std::invalid_argument("System index is out of range.");

    for (int i = 0; i < system_index; i++)
    {
        auto system = m_system_vector[i];

        start_index += layoutSize(system);
    }

    return start_index;
}

int NavigationController::layoutSize(SystemEnum system) const
{
    switch (system)
    {
        case SystemEnum::DL1_SYSTEM:
            return m_dl1_system_screen_vector.size() + m_dl1_setup_screen_vector.size();

        case SystemEnum::DL2_SYSTEM:
            return m_dl2_system_screen_vector.size() + m_dl2_setup_screen_vector.size();

        case SystemEnum::ES_SYSTEM:
            return m_es_system_screen_vector.size() + m_es_setup_screen_vector.size();
    }

    throw std::invalid_argument("Provided argument is not in enum range.");
}

int NavigationController::runtimeSize(SystemEnum system) const
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

int NavigationController::setupSize(SystemEnum system) const
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

void NavigationController::addSystemScreens(QStackedLayout* layout, SystemEnum system_type)
{
    const QVector<RuntimeScreenType>* p{nullptr};
    const QVector<SetupScreenType>* q{nullptr};

    QString title;
    switch (system_type)
    {
        case SystemEnum::DL1_SYSTEM:
            p = &m_dl1_system_screen_vector;
            q = &m_dl1_setup_screen_vector;
            title = "DL1 Speed Log";
            break;

        case SystemEnum::DL2_SYSTEM:
            p = &m_dl2_system_screen_vector;
            q = &m_dl2_setup_screen_vector;
            title = "DL2 Speed Log";
            break;

        case SystemEnum::ES_SYSTEM:
            p = &m_es_system_screen_vector;
            q = &m_es_setup_screen_vector;
            title = "ES1 Echosounder";
            break;
    }

    for (auto e: *p)
    {
        RuntimeScreen* runtime_screen = (e != RuntimeScreenType::RUNTIME_ES) ? new RuntimeScreen(m_parent, e) : new EsRuntimeScreen(m_parent, e);
        runtime_screen->titleWidget()->setTitle(title);

        layout->addWidget(runtime_screen);
    }

    for (auto e: *q)
    {
        BaseScreen* setup_screen = dynamic_cast<BaseScreen*>(createSetupScreen(m_parent, e));
        setup_screen->titleWidget()->setTitle(title);

        layout->addWidget(setup_screen);
    }
}

QStackedLayout* NavigationController::getLayout(QWidget* parent)
{
    if (m_layout == nullptr)
    {
        m_layout = createLayout(parent);
    }

    return m_layout;
}

void NavigationController::navigateLeft()
{
    int index = m_layout->currentIndex() - 1;
    int start_index = layoutStartIndex(m_system_index);
    int size = runtimeSize(m_system_vector[m_system_index]);

    if (index < start_index)
    {
        index = start_index + size - 1;
    }

    m_layout->setCurrentIndex(index);
}

void NavigationController::navigateRight()
{
    int index = m_layout->currentIndex() + 1;
    int start_index = layoutStartIndex(m_system_index);
    int size = runtimeSize(m_system_vector[m_system_index]);

    if (index == start_index + size)
    {
        index = start_index;
    }

    m_layout->setCurrentIndex(index);
}

void NavigationController::navigate(SetupMenuType setup_menu_type, bool runtime)
{
    if (runtime == true)
        m_previous_index = m_layout->currentIndex();

    switch (setup_menu_type)
    {
        case SETUP_MENU:
            m_layout->setCurrentIndex(0);
            break;

        case CU_SETUP:
            m_layout->setCurrentIndex(1);
            break;

        case SYSTEM_SETUP:
            m_layout->setCurrentIndex(2);
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
        int index = layoutStartIndex(m_system_index);
        m_layout->setCurrentIndex(index);
    }
}

void NavigationController::layoutChanged(int index)
{
    if ((index < 0) || (index >= m_system_vector.size()))
        throw std::invalid_argument("System index is out of range!");

    m_system_index = index;
    m_switch_layout = true;
}

void NavigationController::navigate(SystemEnum system, int setup_screen_index)
{
    if (system != m_system_vector[m_system_index])
        throw std::invalid_argument("Provided system is not the currently selected.");

    if ((setup_screen_index < 0) || (setup_screen_index >= setupSize(system)))
        throw std::invalid_argument("Setup index is out of range!");


    int index = layoutStartIndex(m_system_index) + runtimeSize(system) + setup_screen_index;
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

int NavigationController::systemIndex() const
{
    return m_system_index;
}

SystemEnum NavigationController::system(int index) const
{
    if ((index < 0) || (index >= m_system_vector.size()))
        throw std::invalid_argument("System index is out of range!");

    return m_system_vector[index];
}

int NavigationController::systemCount() const
{
    return m_system_vector.size();
}

void NavigationController::addSystem(SystemEnum system)
{
    addSystemScreens(m_layout, system);
    m_system_vector.push_back(system);

    emit systemAdded(system);
}

void NavigationController::removeSystem(int index)
{
    if (m_system_vector.size() == 1)
        throw std::invalid_argument("Cannot remove last system!");

    qDebug() << "Remove system: " << index;
}
