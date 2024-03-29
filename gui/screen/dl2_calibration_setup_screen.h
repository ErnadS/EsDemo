#ifndef DL2_CALIBRATION_SETUP_SCREEN_H
#define DL2_CALIBRATION_SETUP_SCREEN_H

#include "multi_setup_screen.h"

class Dl2CalibrationSetupScreen : public MultiSetupScreen
{
    Q_OBJECT

protected:
    const QSize m_item_size{110, 50};
    const int m_item_count{5};
    const int m_item_sep{3};
    const QSize m_item_container_size{m_item_count * m_item_size.width() + (m_item_count - 1) * m_item_sep, m_item_size.height()};
    const QPoint m_item_container_pos{0, 430};

    const QSize m_speed_item_size{110, 50};
    const int m_speed_item_count{4};
    const QSize m_speed_item_container_size{m_speed_item_count * m_speed_item_size.width() + (m_speed_item_count - 1) * m_item_sep, m_speed_item_size.height()};
    const QPoint m_speed_item_container_pos{0, 430};

    HorizontalItemWidgetContainer* m_speed_item_container;

    bool m_submenu_active{false};

    void setupLayout();

private slots:
    void menuClicked(int index);
    void navigateBackFromSubmenu();

public:
    explicit Dl2CalibrationSetupScreen(QWidget* parent);
};

#endif
