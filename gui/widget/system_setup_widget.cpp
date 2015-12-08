#include "system_setup_widget.h"
#include "system_menu_widget_container.h"
#include <QPainter>
#include <QDebug>

SystemSetupWidget::SystemSetupWidget(QWidget *parent, QSize base_size, QString system_type, QString system_name, QString system_ID, QString system_IP, systemConnection system_connection) : ScalableWidget(parent, base_size), m_system_type(system_type), m_system_name(system_name), m_system_ID(system_ID), m_system_IP(system_IP), m_system_connection(system_connection)
{
    //m_selected = true;

}

void SystemSetupWidget::setActive(bool active)
{
    m_selected = active;
    update();
}

bool SystemSetupWidget::isActive() const
{
    return m_selected;
}

void SystemSetupWidget::setSystemConnection(systemConnection system_connection)
{
    m_system_connection = system_connection;
}

systemConnection SystemSetupWidget::getSystemConnection() const
{
    return m_system_connection;
}

QString SystemSetupWidget::getSystemType() const
{
    return m_system_type;
}

QString SystemSetupWidget::getSystemID() const
{
    return m_system_ID;
}
QString SystemSetupWidget::getSystemName() const
{
    return m_system_name;
}


QString SystemSetupWidget::getSystemIP() const
{
    return m_system_IP;
}


void SystemSetupWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    painter.drawPixmap(0,0,width(),height(),drawSystemIcon());

    painter.setPen(QPen(QColor(200, 200, 200), 4)); //light gray border
    painter.drawRect(0, 0, width(), height());

    painter.setPen(Qt::white);
    QFont font(painter.font());
    font.setPixelSize(23 * m_scale);
    painter.setFont(font);
    painter.drawText(QRect(0.1 * width(), 0.7 * height(), 0.8 * width(), 0.3 * height()), Qt::AlignLeft, m_system_name);

}


void SystemSetupWidget::mouseReleaseEvent(QMouseEvent *)
{
    emit signalSystemSelected(this);
}

QPixmap SystemSetupWidget::drawSystemIcon()
{
    // Image - test image until real icons are available

    const QString system_connections[3] = { "Paired", "Repeater", "Disconnected" };

    QPixmap pixmap;

    if (qobject_cast<SystemMenuWidgetContainer*> (parentWidget()))
    {
        if(m_selected)
        {
            pixmap = QPixmap(":/"+m_system_name+"_selected_"+system_connections[m_system_connection]+".png");

        }
        else
        {
            pixmap = QPixmap(":/"+m_system_name+"_not_selected_Disconnected.png");

        }
    }
    else
    {
        pixmap = QPixmap(":/"+m_system_name+"_selected_"+system_connections[m_system_connection]+".png");
    }

    QPainter p(&pixmap);

    QPixmap drawing_pixmap = pixmap.scaled(pixmap.width(), pixmap.height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    return drawing_pixmap;
}
