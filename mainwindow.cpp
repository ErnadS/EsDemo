#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "BackgroundWidget.h"
#include "RuntimeScreen.h"
#include "NavigationController.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    NavigationController& navigation_controller = Singleton<NavigationController>::instance();

    QStackedLayout* layout = navigation_controller.getLayout(this, SystemEnum::ES_SYSTEM);

    centralWidget()->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
