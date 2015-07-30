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

    const QVector<RuntimeScreenType> m_dl2_system_1_screen_vector
    {
        RuntimeScreenType::RUNTIME_A,
        RuntimeScreenType::RUNTIME_B,
        RuntimeScreenType::RUNTIME_C,
        RuntimeScreenType::RUNTIME_D,
        RuntimeScreenType::RUNTIME_E,
        RuntimeScreenType::RUNTIME_MULTI
    };

    const QVector<RuntimeScreenType> m_dl2_system_2_screen_vector
    {
        RuntimeScreenType::RUNTIME_A,
        RuntimeScreenType::RUNTIME_B,
        RuntimeScreenType::RUNTIME_C,
        RuntimeScreenType::RUNTIME_D,
        RuntimeScreenType::RUNTIME_E,
        RuntimeScreenType::RUNTIME_MULTI
    };

    const QVector<RuntimeScreenType> m_es_system_screen_vector
    {
        RuntimeScreenType::RUNTIME_ES,
        RuntimeScreenType::RUNTIME_ES
    };

    int m_previous_index{0};

    QStackedLayout* createLayout(QWidget* parent, SystemEnum system);

    int layoutStartIndex(SystemEnum system) const;
    int layoutSize(SystemEnum system) const;

public:
    QStackedLayout* getLayout(QWidget* parent, SystemEnum system);
    SystemEnum getSystemType() const;

    void navigateLeft();
    void navigateRight();
    void navigate(SetupMenuType setup_menu_type);
    void navigateBack();
    void layoutChanged(SystemEnum system);

    void setEmbedded(bool embedded);
    bool isEmbedded() const;
};

#endif
