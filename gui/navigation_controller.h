#ifndef NAVIGATION_CONTROLLER_H
#define NAVIGATION_CONTROLLER_H

#include "utility/Singleton.h"
#include "widget_enum.h"
#include <QStackedLayout>
#include <QVector>

class NavigationController: public QObject
{
    Q_OBJECT

    friend class Singleton<NavigationController>;
    NavigationController() { }

    bool m_embedded{false};

    QStackedLayout* m_layout{nullptr};

    bool m_switch_layout{false};
    SystemEnum m_system_type;

    const QVector<RuntimeScreenType> m_dl1_system_screen_vector
    {
        RuntimeScreenType::RUNTIME_DL1,
        RuntimeScreenType::RUNTIME_DL1_B
    };

    const QVector<RuntimeScreenType> m_dl2_system_screen_vector
    {
        RuntimeScreenType::RUNTIME_A,
        RuntimeScreenType::RUNTIME_B,
        RuntimeScreenType::RUNTIME_C,
        RuntimeScreenType::RUNTIME_D,
        RuntimeScreenType::RUNTIME_E
    };

    const QVector<RuntimeScreenType> m_es_system_screen_vector
    {
        RuntimeScreenType::RUNTIME_ES,
        RuntimeScreenType::RUNTIME_ES_B
    };

    const QVector<SetupScreenType> m_dl1_setup_screen_vector
    {
        SetupScreenType::DL1_RUNTIME_SETUP,
        SetupScreenType::DL1_CALIBRATION_SETUP,
        SetupScreenType::DL1_ALERT_SETUP,
        SetupScreenType::DL1_DIAGNOSTIC_SETUP,
        SetupScreenType::DL1_SETUP,
        SetupScreenType::DL1_COMMUNICATION_SETUP,
        SetupScreenType::DL1_AUX_SETUP
    };

    const QVector<SetupScreenType> m_dl2_setup_screen_vector
    {
        SetupScreenType::DL2_RUNTIME_SETUP,
        SetupScreenType::DL2_CALIBRATION_SETUP,
        SetupScreenType::DL2_ALERT_SETUP,
        SetupScreenType::DL2_DIAGNOSTIC_SETUP,
        SetupScreenType::DL2_SETUP,
        SetupScreenType::DL2_COMMUNICATION_SETUP,
        SetupScreenType::DL2_AUX_SETUP,
        SetupScreenType::DL2_JB70_SETUP
    };

    const QVector<SetupScreenType> m_es_setup_screen_vector
    {
        SetupScreenType::ES_RUNTIME_SETUP,
        SetupScreenType::ES_ALERT_SETUP,
        SetupScreenType::ES_DIAGNOSTIC_SETUP,
        SetupScreenType::ES_SETUP,
        SetupScreenType::ES_COMMUNICATION_SETUP,
        SetupScreenType::ES_AUX_SETUP,
        SetupScreenType::ES_HISTORY_SETUP,
        SetupScreenType::ES_JB70_SETUP
    };

    int m_previous_index{0};

    QWidget* createSetupScreen(QWidget* parent, SetupScreenType setup_screen_type) const;
    QStackedLayout* createLayout(QWidget* parent, SystemEnum system);

    int layoutStartIndex(SystemEnum system) const;
    int layoutSize(SystemEnum system) const;

    int setupStartIndex(SystemEnum system) const;
    int setupMenuSize(SystemEnum system) const;

public:
    QStackedLayout* getLayout(QWidget* parent, SystemEnum system);
    SystemEnum getSystemType() const;

    void navigateLeft();
    void navigateRight();
    void navigate(SetupMenuType setup_menu_type);
    void navigateBack();
    void layoutChanged(SystemEnum system);
    void navigate(SystemEnum system, int setup_screen_index);

    void setEmbedded(bool embedded);
    bool isEmbedded() const;
};

#endif
