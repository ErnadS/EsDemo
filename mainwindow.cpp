#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "BackgroundWidget.h"
#include "RuntimeScreen.h"
#include "NavigationController.h"
#include <QDebug>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    m_navigation_controller(Singleton<NavigationController>::instance()),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStackedLayout* layout = m_navigation_controller.getLayout(this, SystemEnum::DL2_SYSTEM_1);

    centralWidget()->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Right)
    {
        m_navigation_controller.navigateRight();
    }

    if (event->key() == Qt::Key_Left)
    {
        m_navigation_controller.navigateLeft();
    }
}
