#include "system_setup_widget.h"
#include <QPainter>


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


void SystemSetupWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QColor system_colors[3] = { Qt::yellow, Qt::cyan, Qt::white };

    painter.setPen(system_colors[int(m_system_connection)]);


    if (m_selected)
    {
        painter.fillRect(QRect(0,0,width(), height()), system_colors[int(m_system_connection)]);
    }
    else
    {
        painter.drawRect(0,0,width(), height());
    }

    QImage image(0.8 * width()/3, height()/2, QImage::Format_RGB32);
    image.fill(system_colors[int(m_system_connection)]);

    QPixmap pixmap_background = QPixmap::fromImage(image);
    painter.drawPixmap(0,0,width(),height(),pixmap_background);
    painter.drawPixmap(0,0,width(),height(),drawSystemIcon(m_system_type,m_system_name));
}


void SystemSetupWidget::mouseReleaseEvent(QMouseEvent *)
{

    emit signalSystemSelected(this);

}

QPixmap SystemSetupWidget::drawSystemIcon(QString system_type, QString system_name)
{
    // Image - test image until real icons are available

    QPixmap pixmap = QPixmap(":/"+system_type+"_"+system_name+".png");

    QPainter p(&pixmap);

    p.setPen(Qt::green);
    QFont font;
    font.setPixelSize(50 * m_scale);

    p.drawText(QRect(0.1 * pixmap.width(), 0.75 * pixmap.height(), 0.8 * pixmap.width(), 0.2 * pixmap.height()), Qt::AlignCenter, system_name);

    QPixmap drawing_pixmap = pixmap.scaled(pixmap.width(), pixmap.height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    return drawing_pixmap;


}
