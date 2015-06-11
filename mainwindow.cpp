#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "BackgroundWidget.h"
#include "RuntimeScreen.h"
#include "NavigationController.h"

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
}

MainWindow::~MainWindow()
{
    delete ui;
}
