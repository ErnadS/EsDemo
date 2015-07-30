#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include "gui/navigation_controller.h"
#include "udp/udp_multicast_interface.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    NavigationController& m_navigation_controller;

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    UdpMulticastInterface* m_udp_multicast_interface;
};

#endif
