#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gui/widget/background_widget.h"
#include "gui/screen/runtime_screen.h"
#include "gui/navigation_controller.h"

#include "gui/screen/setup_screen.h"

MainWindow* MainWindow::mainWindowInstance = 0;

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    m_navigation_controller(Singleton<NavigationController>::instance()),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (QApplication::arguments().contains("-embedded"))
    {
        m_navigation_controller.setEmbedded(true);
    }

    mainWindowInstance =  this;

    QStackedLayout* layout = m_navigation_controller.getLayout(this);

    centralWidget()->setLayout(layout);

    m_udp_multicast_interface = new UdpMulticastInterface(this);
    qDebug() << "Init: " << m_udp_multicast_interface->init();

    initSerial();
    serialReaderNmea_1.enableReceiving(true);
    serialReaderNmea_2.enableReceiving(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow *MainWindow::getInstance()
{
    return mainWindowInstance;
}

bool MainWindow::initSerial()
{
    bool serialOpen_1 = serialReaderNmea_1.init(USART_NMEA_1, 115200);
    bool serialOpen_2 = serialReaderNmea_2.init(USART_NMEA_2, 4800);


    return (serialOpen_1 && serialOpen_2);
}

void MainWindow::slotSendNmeaMessageOnSerial(NmeaMessage *nmeaMsg)
{
    serialReaderNmea_1.sendMessage(nmeaMsg->getMsgBuffer());
    delete nmeaMsg;
}
