#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gui/background_widget.h"
#include "gui/runtime_screen.h"
#include "gui/navigation_controller.h"

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

    QStackedLayout* layout = m_navigation_controller.getLayout(this, SystemEnum::DL2_SYSTEM_1);

    centralWidget()->setLayout(layout);

    m_udp_multicast_interface = new UdpMulticastInterface(this);
    qDebug() << "Init: " << m_udp_multicast_interface->init();
}

MainWindow::~MainWindow()
{
    delete ui;
}
