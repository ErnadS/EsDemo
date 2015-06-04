#include "SetupMenuScreen.h"
#include <QMessageBox>
#include <QHeaderView>

void SetupMenuScreen::setupTableWidget(QTableWidget* table_widget, int index)
{
    table_widget->resize(m_table_size);
    table_widget->horizontalHeader()->setStretchLastSection(true);
    table_widget->horizontalHeader()->setVisible(false);
    table_widget->verticalHeader()->setVisible(false);
    table_widget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table_widget->setAlternatingRowColors(true);
    table_widget->setEnabled(false);
    table_widget->setStyleSheet("border: 0px solid rgb(230, 170, 30); font: 26px; color: black;");
    table_widget->setAutoFillBackground(true);
    table_widget->setShowGrid(false);

    QVector<QString> dl1{"DL1 SETUP", "RUNTIME SETUP", "CALIBRATION", "DIAGNOSTICS", "COMMUNICATION", "AUX", "ALARM SETUP"};
    QVector<QString> dl2{"DL2 SETUP", "RUNTIME SETUP", "CALIBRATION", "DIAGNOSTICS", "COMMUNICATION", "AUX", "ALARM SETUP"};
    QVector<QString> es{"ES SETUP", "RUNTIME SETUP", "CALIBRATION", "DIAGNOSTICS", "COMMUNICATION", "AUX", "ALARM SETUP"};

    QVector<QString>* p{nullptr};

    switch (index)
    {
        case 0:
            p = &dl1;
            break;

        case 1:
        case 2:
            p = &dl2;
            break;

        case 3:
            p = &es;
            break;
    }

    for (int i = 0; i < p->size(); i++)
    {
        QTableWidgetItem* item = new QTableWidgetItem((*p)[i]);
        item->setTextAlignment(Qt::AlignCenter);

        table_widget->setItem(0, i, item);
    }
}

void SetupMenuScreen::deactivateSystemWidgets()
{
    m_dl1_system->setActive(false);
    m_dl2_system_1->setActive(false);
    m_dl2_system_2->setActive(false);
    m_es_system->setActive(false);

    m_table_widget_dl1->hide();
    m_table_widget_dl2_1->hide();
    m_table_widget_dl2_2->hide();
    m_table_widget_es->hide();
}

bool SetupMenuScreen::changeLayout() const
{
    QMessageBox message_box(QMessageBox::Question,
                                    "",
                                    "You are about to change the system type. Are you sure you want to continue?",
                                    QMessageBox::No | QMessageBox::Yes, (QWidget*)this,
                                    Qt::FramelessWindowHint);

    // TODO: Generalize style through controller class
    message_box.setStyleSheet("QPushButton { color: rgb(255, 255, 255); background-color: rgb(20, 20, 20); font: 16px; min-width: 230px; min-height: 40px;} QMessageBox { background-color: black; border: 2px solid rgb(80, 80, 80);} QLabel { color: rgb(255, 255, 255); font: 16px; text-align: justify; }");

    int return_status = message_box.exec();

    return return_status == QMessageBox::Yes;
}

SetupMenuScreen::SetupMenuScreen(QWidget* parent) : BaseScreen(parent)
{
    m_table_widget_dl1 = new QTableWidget(7, 1, this);
    setupTableWidget(m_table_widget_dl1, 0);
    m_table_widget_dl1->hide();

    m_table_widget_dl2_1 = new QTableWidget(7, 1, this);
    setupTableWidget(m_table_widget_dl2_1, 1);
    m_table_widget_dl2_1->hide();

    m_table_widget_dl2_2 = new QTableWidget(7, 1, this);
    setupTableWidget(m_table_widget_dl2_2, 2);
    m_table_widget_dl2_2->hide();

    m_table_widget_es = new QTableWidget(7, 1, this);
    setupTableWidget(m_table_widget_es, 3);
    m_table_widget_es->hide();

    m_dl1_system = new SystemWidget(this, m_system_size, "SPEED", "DL1 SYS 1");
    m_dl2_system_1 = new SystemWidget(this, m_system_size, "SPEED", "DL2 SYS 1");
    m_dl2_system_2 = new SystemWidget(this, m_system_size, "SPEED", "DL2 SYS 2");
    m_es_system = new SystemWidget(this, m_system_size, "DEPTH", "ES SYS 1");

    connect(m_dl1_system, SIGNAL(pressed()), this, SLOT(dl1SystemPressed()));
    connect(m_dl2_system_1, SIGNAL(pressed()), this, SLOT(dl2System1Pressed()));
    connect(m_dl2_system_2, SIGNAL(pressed()), this, SLOT(dl2System2Pressed()));
    connect(m_es_system, SIGNAL(pressed()), this, SLOT(esSystemPressed()));

    connect(this, SIGNAL(layoutChanged(SystemEnum)), &m_navigation_controller, SLOT(layoutChanged(SystemEnum)));

    m_system_button = new Button(this, m_system_button_size, "Available Systems:", false);
}

void SetupMenuScreen::buttonClicked()
{
    emit navigateBack();
}

void SetupMenuScreen::dl1SystemPressed()
{
    if (changeLayout() == true)
    {
        deactivateSystemWidgets();
        m_dl1_system->setActive(true);
        m_table_widget_dl1->show();
        emit layoutChanged(SystemEnum::DL1_SYSTEM);
    }
}

void SetupMenuScreen::dl2System1Pressed()
{
    if (changeLayout() == true)
    {
        deactivateSystemWidgets();
        m_table_widget_dl2_1->show();
        m_dl2_system_1->setActive(true);
        emit layoutChanged(SystemEnum::DL2_SYSTEM_1);
    }
}

void SetupMenuScreen::dl2System2Pressed()
{
    if (changeLayout() == true)
    {
        deactivateSystemWidgets();
        m_table_widget_dl2_2->show();
        m_dl2_system_2->setActive(true);
        emit layoutChanged(SystemEnum::DL2_SYSTEM_2);
    }
}

void SetupMenuScreen::esSystemPressed()
{
    if (changeLayout() == true)
    {
        deactivateSystemWidgets();
        m_table_widget_es->show();
        m_es_system->setActive(true);
        emit layoutChanged(SystemEnum::ES_SYSTEM);
    }
}

void SetupMenuScreen::showEvent(QShowEvent*)
{
    deactivateSystemWidgets();
    SystemEnum system = m_navigation_controller.getSystemType();

    switch (system)
    {
        case SystemEnum::DL1_SYSTEM:
            m_dl1_system->setActive(true);
            m_table_widget_dl1->show();
            break;

        case SystemEnum::DL2_SYSTEM_1:
            m_dl2_system_1->setActive(true);
            m_table_widget_dl2_1->show();
            break;

        case SystemEnum::DL2_SYSTEM_2:
            m_dl2_system_2->setActive(true);
            m_dl2_system_2->show();
            break;

        case SystemEnum::ES_SYSTEM:
            m_es_system->setActive(true);
            m_table_widget_es->show();
            break;
    }
}

void SetupMenuScreen::setupLayout()
{
    BaseScreen::setupLayout();

    QSize system_size(m_system_size.width() * m_width_scale, m_system_size.height() * m_height_scale);
    QSize system_button_size(m_system_button_size.width() * m_width_scale, m_system_button_size.height() * m_height_scale);

    m_dl1_system->resize(system_size);
    m_dl2_system_1->resize(system_size);
    m_dl2_system_2->resize(system_size);
    m_es_system->resize(system_size);
    m_system_button->resize(system_button_size);

    QPoint first_column(m_first_column.x() * m_width_scale, m_first_column.y() * m_height_scale);
    QPoint second_column(m_second_column.x() * m_width_scale, m_second_column.y() * m_height_scale);
    int vertical_space = m_vertical_space * m_height_scale;

    m_dl1_system->move(first_column);
    m_dl2_system_1->move(second_column);

    m_dl2_system_2->move(first_column.x(), first_column.y() + system_size.height() + vertical_space);
    m_es_system->move(second_column.x(), second_column.y() + system_size.height() + vertical_space);

    m_system_button->move(first_column.x(), first_column.y() - system_button_size.height());

    QSize table_size(m_table_size.width() * m_width_scale, m_table_size.height() * m_height_scale);

    int font_pixel_size = 26 * m_width_scale;
    QString css = "border: 0px solid rgb(230, 170, 30); font: " + QString::number(font_pixel_size) + "px; color: black;";

    m_table_widget_dl1->resize(table_size);
    m_table_widget_dl1->move(width() - m_table_widget_dl1->width(), m_speed_indication_widget->height());
    m_table_widget_dl1->setStyleSheet(css);

    m_table_widget_dl2_1->resize(table_size);
    m_table_widget_dl2_1->move(width() - m_table_widget_dl1->width(), m_speed_indication_widget->height());
    m_table_widget_dl2_1->setStyleSheet(css);

    m_table_widget_dl2_2->resize(table_size);
    m_table_widget_dl2_2->move(width() - m_table_widget_dl1->width(), m_speed_indication_widget->height());
    m_table_widget_dl2_2->setStyleSheet(css);

    m_table_widget_es->resize(table_size);
    m_table_widget_es->move(width() - m_table_widget_dl1->width(), m_speed_indication_widget->height());
    m_table_widget_es->setStyleSheet(css);
}
