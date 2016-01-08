#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include "gui/navigation_controller.h"
#include "udp/udp_multicast_interface.h"

#include "serialreader.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    static MainWindow* mainWindowInstance;

    NavigationController& m_navigation_controller;

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

    static MainWindow * getInstance();

public slots:
    void slotSendNmeaMessageOnSerial(NmeaMessage *nmeaMsg);

private:
    Ui::MainWindow* ui;
    UdpMulticastInterface* m_udp_multicast_interface;

    SerialReader serialReaderNmea_1;
    SerialReader serialReaderNmea_2;

    bool initSerial();
};

#endif
