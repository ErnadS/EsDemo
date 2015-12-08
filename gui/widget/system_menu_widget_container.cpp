#include "system_menu_widget_container.h"
#include <QPainter>

void SystemMenuWidgetContainer::setupLayout()
{
    QSize p_lab_size(0.35 * width(), 0.1 * height());
    QPoint p_lab_pos(0, 0);
    QSize r_lab_size(0.35 * width(), 0.1 * height());
    QPoint r_lab_pos(0.6 * width(), 0);
    QSize system_widget_size(0.3 * width(), 0.15 * height());
    QPoint system_p_widget_pos = QPoint (0, p_lab_size.height() + 3 * m_height_scale);
    QSize display_button_size(0.3 * width(), 0.15 * height());
    QPoint display_button_pos(0, 0.5 * height());
    QPoint system_r_widget_pos(r_lab_pos.x(), r_lab_size.height() + 3 * m_height_scale);
    QFont font(m_paired_label->font());
    font.setPixelSize(25 * m_scale);
    m_paired_label->setAlignment(Qt::AlignCenter);
    m_repeaters_label->setAlignment(Qt::AlignCenter);
    m_paired_label->setStyleSheet("color : gray");
    m_repeaters_label->setStyleSheet("color : gray");

    m_paired_label->resize(p_lab_size);
    m_paired_label->move(p_lab_pos);
    m_paired_label->setFont(font);
    m_repeaters_label->resize(r_lab_size);
    m_repeaters_label->move(r_lab_pos);
    m_repeaters_label->setFont(font);

    m_display_button->resize(display_button_size);
    m_display_button->move(display_button_pos);

    int j = 0;
    for (int i = 0; i < m_system_setup_widget_vector.size(); i++)
    {
        m_system_setup_widget_vector[i]->resize(system_widget_size);
        if (m_system_setup_widget_vector[i]->getSystemConnection() == Paired)
        {
            m_system_setup_widget_vector[i]->move(system_p_widget_pos);
        }
        else
        {
            m_system_setup_widget_vector[i]->move(system_r_widget_pos + QPoint(0, j * (system_widget_size.height() + 0.01 * height())));
            j++;
        }
    }

}

SystemMenuWidgetContainer::SystemMenuWidgetContainer(QWidget *parent, QSize base_size, QList<QString> type_list, QList<QString> name_list) : ScalableWidget(parent, base_size)
{
    m_paired_label = new QLabel("Paired:", this);
    m_repeaters_label = new QLabel("Repeaters:", this);

    m_display_button_base_size = QSize(0.35 * base_size.width(), 0.2 * base_size.height());
    m_system_base_size = QSize(0.3 * base_size.width(), 0.2 * base_size.height());

    m_display_button = new DisplayButton(this, m_display_button_base_size);

    connect(m_display_button, SIGNAL(clicked()), this, SLOT(slotDisplaySelected()));

    for (int i = 0; i < name_list.size(); i++)
    {
        SystemSetupWidget* system_setup_widget = new SystemSetupWidget(this, m_system_base_size, type_list[i], name_list[i],"1234","172.22.247.250", Repeater);
        m_system_setup_widget_vector.push_back(system_setup_widget);

        connect(system_setup_widget, SIGNAL(signalSystemSelected(SystemSetupWidget*)), this, SLOT(slotSystemSelected(SystemSetupWidget*)));
    }

    m_system_setup_widget_vector[0]->setSystemConnection(Paired);

    m_last_selected = m_system_setup_widget_vector[0];

    setupLayout();
}

void SystemMenuWidgetContainer::addSystem(QString type, QString name, QString system_ID, QString system_IP, systemConnection system_connection)
{
    SystemSetupWidget* system_setup_widget = new SystemSetupWidget(this, m_system_base_size, type, name, system_ID, system_IP, system_connection);
    m_system_setup_widget_vector.push_back(system_setup_widget);

    connect(system_setup_widget, SIGNAL(signalSystemSelected(SystemSetupWidget*)), this, SLOT(slotSystemSelected(SystemSetupWidget*)));

    setupLayout();
}

void SystemMenuWidgetContainer::removeSystem(int index)
{
    SystemSetupWidget* system_widget = m_system_setup_widget_vector[index];
    m_system_setup_widget_vector.remove(index);


    if (system_widget->isActive() == true)
    {
        m_system_setup_widget_vector[0]->setActive(true);

    }

    delete system_widget;

    setupLayout();
}

void SystemMenuWidgetContainer::setSelected(int index)
{
    m_display_button->setSelected(false);
    m_last_selected->setActive(false);
    m_system_setup_widget_vector[index]->setActive(true);
    m_last_selected = m_system_setup_widget_vector[index];
    update();
}

void SystemMenuWidgetContainer::setDisplaySelected()
{
    m_last_selected->setActive(false);
    m_display_button->setSelected(true);
    update();
}

SystemSetupWidget *SystemMenuWidgetContainer::getSelected() const
{
    return m_last_selected;
}

int SystemMenuWidgetContainer::getSelectedIndex() const
{
    for (int index = 0; index < m_system_setup_widget_vector.size(); index++)
    {
        if (m_system_setup_widget_vector[index] == m_last_selected)
        {
            return index;
        }
    }
    throw "No system selected!";
}

void SystemMenuWidgetContainer::slotSystemSelected(SystemSetupWidget *system)
{
    for (int index = 0; index < m_system_setup_widget_vector.size(); index++)
    {
        if (m_system_setup_widget_vector[index] == system)
        {
            emit systemSelected(index);
            break;
        }
    }

}

void SystemMenuWidgetContainer::slotDisplaySelected()
{
    emit displaySelected();
}

void SystemMenuWidgetContainer::resizeEvent(QResizeEvent *)
{
    ScalableWidget::resizeEvent(nullptr);
    setupLayout();
}

void SystemMenuWidgetContainer::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    setupLayout();

    QRect disp_but_rect = m_display_button->geometry();
    QRect syst_wid_rect = m_last_selected->geometry();

    QPoint start_point, mid1_point, mid2_point, end_point;
    painter.setPen(QPen(Qt::gray, 8));

    if (m_last_selected->getSystemConnection() == Paired)
    {
        start_point = (disp_but_rect.topLeft() + disp_but_rect.topRight()) / 2;
        end_point = (syst_wid_rect.bottomLeft() + syst_wid_rect.bottomRight()) / 2;
        mid1_point.ry() = (start_point.y() + end_point.y()) / 2;
        mid1_point.rx() = start_point.x();
        mid2_point.ry() = mid1_point.y();
        mid2_point.rx() = end_point.x();
        painter.drawLine(start_point, mid1_point);
        painter.drawLine(mid1_point, mid2_point);
        painter.drawLine(mid2_point, end_point);
    }
    else
    {
        start_point = (disp_but_rect.topRight() + disp_but_rect.bottomRight()) / 2;
        end_point = (syst_wid_rect.bottomLeft() + syst_wid_rect.topLeft()) / 2;
        mid1_point.rx() = (start_point.x() + end_point.x()) / 2;
        mid1_point.ry() = start_point.y();
        mid2_point.rx() = mid1_point.x();
        mid2_point.ry() = end_point.y();
        painter.drawLine(start_point, mid1_point);
        painter.drawLine(mid1_point, mid2_point);
        painter.drawLine(mid2_point, end_point);
    }

}

