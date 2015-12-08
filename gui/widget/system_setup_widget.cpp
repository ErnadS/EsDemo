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
    QColor system_colors[3];
    system_colors[0] = QColor(255, 255, 115); //light yellow
    system_colors[1] = QColor(0, 102, 204); //blue
    system_colors[2] = QColor(140, 140, 140); //gray

    QImage image(0.8 * width()/3, height()/2, QImage::Format_RGB32);

    if (qobject_cast<SystemMenuWidgetContainer*> (parentWidget()))
    {
        if (m_selected)
        {
            image.fill(system_colors[int(m_system_connection)]);

        }
        else
        {
            image.fill(system_colors[2]);
        }
    }
    else
    {
        painter.setPen(system_colors[int(m_system_connection)]);
        
        
        if (m_selected)
        {
            painter.fillRect(QRect(0,0,width(), height()), system_colors[int(m_system_connection)]);
        }
        else
        {
            painter.drawRect(0,0,width(), height());
        }
        image.fill(system_colors[int(m_system_connection)]);
    }

    QPixmap pixmap_background = QPixmap::fromImage(image);
    painter.drawPixmap(0,0,width(),height(),pixmap_background);
    painter.drawPixmap(0,0,width(),height(),drawSystemIcon());
    painter.setPen(QPen(QColor(200, 200, 200), 6)); //light gray border
    painter.drawRect(0, 0, width(), height());
}


void SystemSetupWidget::mouseReleaseEvent(QMouseEvent *)
{

    m_selected = true;
    update();
    emit signalSystemSelected(this);

}

QPixmap SystemSetupWidget::drawSystemIcon()
{
    // Image - test image until real icons are available

    const QString system_connections[3] = { "Paired", "Repeater", "Disconnected" };

    QPixmap pixmap;

    if(m_selected)
    {
        pixmap = QPixmap(":/"+m_system_name+"_selected_"+system_connections[m_system_connection]+".png");

    }
    else
    {
        pixmap = QPixmap(":/"+m_system_name+"_not_selected_Disconnected.png");

    }


    QPainter p(&pixmap);
    p.setPen(Qt::white);
    QFont font(p.font());
    font.setPixelSize(18);
    p.setFont(font);
    p.drawText(QRect(0.1 * pixmap.width(), 0.75 * pixmap.height(), 0.8 * pixmap.width(), 0.2 * pixmap.height()), Qt::AlignLeft, m_system_name);

    QPixmap drawing_pixmap = pixmap.scaled(pixmap.width(), pixmap.height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    return drawing_pixmap;
}
