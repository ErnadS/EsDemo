#include "system_setup_widget_container.h"
#include <QPainter>
#include <QDebug>

void SystemSetupWidgetContainer::setupLayout()
{

    QSize availableSize{int(0.75 * width()), int(0.85 * height())};


        for (int i = 0; i < m_system_setup_widget_vector.size() ; i++)
        {
            for (int k = 0; k < m_system_setup_widget_vector.size(); k++)
            {
                if( (3 * i + k) < 4 && (3 * i + k) < m_system_setup_widget_vector.size())
                {
                    m_system_setup_widget_vector[3 * i + k]->move(0.05 * width() + k * availableSize.width()/3, 0.15 * height() + i * availableSize.height()/3);
                    m_system_setup_widget_vector[3 * i + k]->resize(0.75 * availableSize.width()/3, 0.75 * availableSize.height()/3);

                }
                else if ( (3 * i + k) > 4 && (3 * i + k) < m_system_setup_widget_vector.size())
                {
                    m_system_setup_widget_vector[3 * i + k - 1]->move(0.05 * width() + k * availableSize.width()/3, 0.15 * height() + i * availableSize.height()/3);
                    m_system_setup_widget_vector[3 * i + k - 1]->resize( 0.75 * availableSize.width()/3, 0.75 * availableSize.height()/3);
                }
                else
                {
                    break;
                }





            }

        }

   }

SystemSetupWidgetContainer::SystemSetupWidgetContainer(QWidget* parent, QSize base_size, int display_size, QList<QString> type_list, QList<QString> name_list) : ScalableWidget(parent, base_size), m_display_size(display_size)
{
    QSize item_size(0.75 * int(0.75 * width())/3, 0.75*int(0.85 * height())/3);

    m_item_base_size = item_size;

    for (int i = 0; i < name_list.size(); i++)
    {

        SystemSetupWidget* system_setup_widget = new SystemSetupWidget(this, item_size, type_list[i], name_list[i],"1234","172.22.247.250",Disconnected);
        m_system_setup_widget_vector.push_back(system_setup_widget);

        connect(system_setup_widget, SIGNAL(signalSystemSelected(SystemSetupWidget*)), this, SLOT(slotSystemSelected(SystemSetupWidget*)));
    }

    setupLayout();

}

void SystemSetupWidgetContainer::setActive(int index)
{
    for (int i = 0; i < m_system_setup_widget_vector.size(); i++)
    {
        if (i != index)
        {
            m_system_setup_widget_vector[i]->setActive(false);
        }
        else
        {
            m_system_setup_widget_vector[i]->setActive(true);
        }
    }
}

void SystemSetupWidgetContainer::addSystem(QString type, QString name, QString system_ID, QString system_IP, systemConnection system_connection)
{

    SystemSetupWidget* system_setup_widget = new SystemSetupWidget(this, m_item_base_size, type, name, system_ID, system_IP, system_connection);
    m_system_setup_widget_vector.push_back(system_setup_widget);

    connect(system_setup_widget, SIGNAL(signalSystemSelected(SystemSetupWidget*)), this, SLOT(itemPressed(SystemSetupWidget*)));

    setupLayout();
}

void SystemSetupWidgetContainer::removeSystem(int index)
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

void SystemSetupWidgetContainer::setSystemConnection(int index, systemConnection system_connection)
{
    m_system_setup_widget_vector[index]->setSystemConnection(system_connection);
}

int SystemSetupWidgetContainer::getSystemCount() const
{
    return m_system_setup_widget_vector.size();
}

QVector<SystemSetupWidget*> SystemSetupWidgetContainer::getSystems() const
{
    return m_system_setup_widget_vector;
}

void SystemSetupWidgetContainer::slotSystemSelected(SystemSetupWidget *item)
{
    for (int i = 0; i < m_system_setup_widget_vector.size(); i++)
    {
        if (m_system_setup_widget_vector[i] == item)
        {
            update();
            emit itemSelected(i);
            return;
        }
    }
}


void SystemSetupWidgetContainer::resizeEvent(QResizeEvent*)
{
    ScalableWidget::resizeEvent(nullptr);
    setupLayout();
}

void SystemSetupWidgetContainer::paintEvent(QPaintEvent *)
{
    setupLayout();
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    drawConnections(painter);
}

void SystemSetupWidgetContainer::drawConnections(QPainter &painter)
{

    QSize availableSize{int(0.75 * width()), int(0.85 * height())};
    QColor colors[3];
    colors[0] = QColor(255, 255, 115); //light yellow
    colors[1] = QColor(0, 102, 204); //blue
    colors[2] = QColor(140, 140, 140); //gray

    Qt::PenStyle line_style[3]= {Qt::SolidLine, Qt::DashLine, Qt::SolidLine};

    QPen pen;
    pen.setWidth(3 * m_scale);
    painter.setPen(pen);
    QVector <QPoint> start;
    qreal sgnx{1};
    qreal sgny{1};

    for ( int i=0; i<3; i++)
    {

        for (int k=0; k<3;k++)
        {
            if((3 * i + k) == 0||(3 * i + k) == 1||(3 * i + k) == 2)
            {
                sgnx=1;
                sgny=1;
            }

            else if((3 * i + k) == 6||(3 * i + k) == 7||(3 * i + k) == 8)
            {
                sgnx=1;
                sgny=0;
            }
            else if((3 * i + k) == 3)
            {
                sgnx=2;
                sgny=0.5;
            }
            else if((3 * i + k) == 5)
            {
                sgnx=0;

                sgny=0.5;
            }
            else
            {
                continue;
            }

            start.push_back(QPoint{int(0.05 * width() + k * availableSize.width()/3 + sgnx * 0.75 * availableSize.width()/6), int(0.15 * height() + i * availableSize.height()/3 + sgny * 0.75 * availableSize.height()/3)});

        }
    }
    QPoint central{int(0.05 * width() + availableSize.width()/3), int(0.15 * height() + availableSize.height()/3)};

    QVector <QPoint> stop{QPoint{central.x() + int(0.15 * availableSize.width()/3), central.y()},
                          QPoint{central.x() + int(0.75 * availableSize.width()/6), central.y()},
                          QPoint{central.x() + int(0.6 * availableSize.width()/3), central.y()},
                          QPoint{central.x(), central.y() + int(0.75 * availableSize.height()/6)},
                          QPoint{central.x() + int(0.75 * availableSize.width()/3),central.y()+int(0.75 * availableSize.height()/6)},
                          QPoint{central.x() + int(0.15 * availableSize.width()/3), central.y()+int(0.75 * availableSize.height()/3)},
                          QPoint{central.x() + int(0.75 * availableSize.width()/6), central.y()+int(0.75 * availableSize.height()/3)},
                          QPoint{central.x() + int(0.6 * availableSize.width()/3), central.y()+int(0.75 * availableSize.height()/3)}};

    // Arrow midpoints
    QPoint midpoint1;
    QPoint midpoint2;

    //Signs to falicitate arrow rotation
    qreal sgnz{1};
    qreal sgnq{1};
    qreal offset{10};



    for (int i = 0; i < m_system_setup_widget_vector.size(); i++)
    {
        if(i == 0||i == 1||i == 2)
        {
            sgnx = -1;
            sgnz = 1;
            sgny = 1;
            sgnq = 1;
        }

        else if(i == 6 || i == 7||i == 8)
        {
            sgnx = -1;
            sgnz = 1;
            sgny = -1;
            sgnq = -1;
        }
        else if(i == 3)
        {
            sgnx = 1;
            sgnz = 1;
            sgny = -1;
            sgnq = 1;
        }
        else if(i == 5)
        {
            sgnx = -1;
            sgnz = -1;
            sgny = -1;
            sgnq = 1;
        }
        else
        {
            continue;
        }

        if(i < 4)
        {
            QPoint midpoint1{start[i].x(),(start[i].y() + stop[i].y())/2};
            QPoint midpoint2{stop[i].x(),(start[i].y() + stop[i].y())/2};
            pen.setColor(colors[int(m_system_setup_widget_vector[i]->getSystemConnection())]);
            pen.setStyle(line_style[int(m_system_setup_widget_vector[i]->getSystemConnection())]);
            painter.setPen(pen);
            painter.setBrush(colors[int(m_system_setup_widget_vector[i]->getSystemConnection())]);
            painter.drawLine(start[i],midpoint1);
            painter.drawLine(midpoint1,midpoint2);
            painter.drawLine(midpoint2,stop[i]);
            if(m_system_setup_widget_vector[i]->getSystemConnection() == Paired)
            {

                QPointF start_arrow[3]{start[i], QPointF{start[i].x() + sgnx * offset * m_scale, start[i].y() + sgny * offset * m_scale}, QPointF{start[i].x() + sgnz * offset * m_scale, start[i].y() + sgnq * offset * m_scale}};
                painter.drawPolygon(start_arrow, 3, Qt::OddEvenFill);
            }
            QPointF stop_arrow[3]{stop[i], QPointF{stop[i].x() - sgnx * offset * m_scale,stop[i].y() - sgny * offset * m_scale}, QPointF{stop[i].x() - sgnz * offset * m_scale,stop[i].y() - sgnq * offset * m_scale}};
            painter.drawPolygon(stop_arrow, 3, Qt::OddEvenFill);
        }
        else if(i > 4)
        {
            midpoint1={start[i - 1].x(),(start[i - 1].y() + stop[i - 1].y())/2};
            midpoint2={stop[i - 1].x(),(start[i - 1].y() + stop[i - 1].y())/2};
            pen.setColor(colors[int(m_system_setup_widget_vector[i]->getSystemConnection())]);
            pen.setStyle(line_style[int(m_system_setup_widget_vector[i]->getSystemConnection())]);
            painter.setPen(pen);
            painter.setBrush(colors[int(m_system_setup_widget_vector[i]->getSystemConnection())]);
            painter.drawLine(start[i - 1], midpoint1);
            painter.drawLine(midpoint1, midpoint2);
            painter.drawLine(midpoint2, stop[i - 1]);
            if(m_system_setup_widget_vector[i]->getSystemConnection() == Paired)
            {

                QPointF start_arrow[3]{start[i - 1], QPointF{start[i - 1].x() + sgnx *  offset * m_scale,start[i - 1].y() + sgny *  offset * m_scale}, QPointF{start[i - 1].x() + sgnz *  offset * m_scale, start[i - 1].y() + sgnq *  offset * m_scale}};
                painter.drawPolygon(start_arrow, 3, Qt::OddEvenFill);
            }
            QPointF stop_arrow[3]{stop[i - 1], QPointF{stop[i - 1].x() - sgnx *  offset * m_scale, stop[i - 1].y() - sgny *  offset * m_scale}, QPointF{stop[i - 1].x() - sgnz *  offset * m_scale, stop[i - 1].y() - sgnq *  offset * m_scale}};
            painter.drawPolygon(stop_arrow, 3, Qt::OddEvenFill);


        }


    }



}
