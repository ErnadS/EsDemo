#include "system_setup_screen.h"
#include <QDebug>

void SystemSetupScreen::slotSystemSelected(int index)
{
    m_selection_vector=QVector<bool>(m_system_setup_widget_container->getSystemCount(),false);
    m_selection_vector[index]=true;
    m_system_setup_widget_container->getSystems()[index]->setActive(true);
}

void SystemSetupScreen::slotSetupSelected(systemConnection status)
{

    int paired_index{10}; //HIGHER THAN POSSIBLE SYSTEM NUMBER

    for(int i=0; i<m_status_vector.size(); i++)
    {
        // Determining if paired device exists
        if(m_status_vector[i] == Paired && status == Paired) paired_index = i;
    }
    // Checking paired index
    for(int i=0; i<m_selection_vector.size(); i++)
    {// Setting selected setting
        if(m_selection_vector[i])
        {
            if(paired_index != i && paired_index != 10)
            {//Disconnect paired index
                m_status_vector[paired_index] = Disconnected;
                m_system_setup_widget_container->setSystemConnection(paired_index, Disconnected);
            }

            m_status_vector[i] = status;
            m_system_setup_widget_container->setSystemConnection(i, status);


            repaint();
        }
    }
}

void SystemSetupScreen::slotRefreshSystems()
{
    //TO DO : IMPLEMENT REINITIALISATION OF SYSTEM WIDGET CONTAINER

}



SystemSetupScreen::SystemSetupScreen(QWidget* parent) : SetupScreen(parent)
{
    // TO DO - construct status vector with existing system data, compare previous values with new ones - show for error!
    // Check for errors in configuration


    QList<QString> type_list, name_list;

    for (int i = 0; i < m_navigation_controller.systemCount(); i++)
    {
        QString type = "SPEED";
        auto system = m_navigation_controller.system(i);

        if (system == SystemEnum::ES_SYSTEM)
            type = "DEPTH";

        QString prefix;

        switch (system)
        {
        case SystemEnum::DL1_SYSTEM:
            prefix = "DL1";
            break;

        case SystemEnum::DL2_SYSTEM:
            prefix = "DL2";
            break;

        case SystemEnum::ES_SYSTEM:
            prefix = "ES";
            break;

      }

        QString system_name = prefix + " SYS " + QString::number(i + 1);

        type_list << type;
        name_list << system_name;
    }

   QSize base_size(width(), 0.95 * height());

   m_system_setup_widget_container = new SystemSetupWidgetContainer(this,base_size,2,type_list,name_list);

   m_status_vector = QVector<systemConnection>(m_system_setup_widget_container->getSystemCount(),Disconnected);
   m_selection_vector = QVector<bool>(m_system_setup_widget_container->getSystemCount(), false);

   connect(this, SIGNAL (signalRefreshSystems()), this, SLOT(slotRefreshSystems()));
   connect(m_system_setup_widget_container, SIGNAL(itemSelected(int)), this, SLOT(slotSystemSelected(int)));
   connect(this, SIGNAL(signalSetupSelected(systemConnection)), this, SLOT(slotSetupSelected(systemConnection)));


}

void SystemSetupScreen::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.setRenderHint(QPainter::Antialiasing, true);


    painter.setPen(Qt::white);
    QFont font = painter.font();
    font.setPixelSize(20 * m_scale);
    painter.setFont(font);

    QColor colors[3];
    colors[0] = QColor(255, 255, 115); //light yellow
    colors[1] = QColor(0, 102, 204); //blue
    colors[2] = QColor(140, 140, 140); //gray

    QString statuses[3] = {"PAIRED", "REPEATER", "DISCONNECTED"};

    int systemSelected{9};
    for (int i = 0; i < m_system_setup_widget_container->getSystemCount(); i++)
    {
        if(m_selection_vector[i])
        {systemSelected = i;
        break;}
    }

    QSize availableSize{int(0.75 * width()), int(0.85 * 0.95 *height())};

    // Drawing CU - M001 system box

    painter.setPen(Qt::white);
    painter.drawRect(0.05 * width() + availableSize.width()/3, 0.2 * height() + availableSize.height()/3, 0.75 * availableSize.width()/3, 0.75 * availableSize.height()/3);
    painter.drawText(QRect(0.05 * width() + availableSize.width()/3, 0.2 * height() + availableSize.height()/3, 0.75 * availableSize.width()/3, 0.75 * availableSize.height()/3), Qt::AlignCenter, " CU-M001 \n System ");


    //Drawing refresh button
    painter.drawRect(0.05 * width() + 2.90 * availableSize.width()/3, 0.2 * height() + 2 * availableSize.height()/3, 0.8 * availableSize.width()/3, 0.75 * availableSize.height()/3);
    painter.drawText(QRect(0.05 * width() + 2.90 * availableSize.width()/3, 0.2 * height() + 2 * availableSize.height()/3, 0.8 * availableSize.width()/3, 0.75 * availableSize.height()/3), Qt::AlignCenter, "Refresh \n Systems");

    // Drawing choice pixmap

    if(systemSelected<m_system_setup_widget_container->getSystemCount())
    {
        QImage image(0.8 * availableSize.width()/3, 0.45 * height(), QImage::Format_RGB32);
        image.fill(Qt::black);

        QPixmap pixmap = QPixmap::fromImage(image);
        QPainter p(&pixmap);

        p.setPen(Qt::white);
        font = p.font();

        font.setPixelSize(14 * 0.95 * m_scale);
        p.setFont(font);
        p.drawRect(0,0,0.95 * pixmap.width(), 0.95 * pixmap.height());
        p.drawRect(0,0, 0.95 * pixmap.width(), 0.95 * pixmap.height()/3);
        p.drawText(QRect(0, 0, 0.95 * pixmap.width(), 0.95 * pixmap.height()/3), Qt::AlignLeft, "SYSTEM NAME:"+(m_system_setup_widget_container->getSystems())[systemSelected]->getSystemName()+
                                                                                                "\nSYSTEM ID:"+(m_system_setup_widget_container->getSystems())[systemSelected]->getSystemID()+
                                                                                                "\nSYSTEM IP:\n"+(m_system_setup_widget_container->getSystems())[systemSelected]->getSystemIP());

        font.setPixelSize(15 * 0.95 * m_scale);
        p.setFont(font);
        QSize small_rect_size(13 * m_scale, 13 * m_scale);


            for (int l=0; l<3; l++)
            {
                p.setPen(colors[l]);
                p.drawRect(0.11 * pixmap.width(), 1.1 * pixmap.height()/3 + 2 * l * pixmap.height()/9, small_rect_size.width(), small_rect_size.height());

                if(m_status_vector[systemSelected] == l)
                {
                    p.fillRect(0.11 * pixmap.width(), 1.1 * pixmap.height()/3 + 2 * l * pixmap.height()/9, small_rect_size.width(), small_rect_size.height(), colors[l]);
                }
                p.drawText(QRect( 0.23 * pixmap.width(), 1.06 * pixmap.height()/3 + 2 * l * pixmap.height()/9, pixmap.width(), 2 * pixmap.height()/9), Qt::AlignLeft, statuses[l]);
            }


        QPixmap drawing_pixmap = pixmap.scaled(pixmap.width(), pixmap.height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

        painter.drawPixmap(QPoint(0.05 * width() + 2.90 * availableSize.width()/3, 0.15 * height()), drawing_pixmap);
    }
    setupLayout();

}

void SystemSetupScreen::mouseReleaseEvent(QMouseEvent*)
{
    QPoint mouse_pos = this->mapFromGlobal(QCursor::pos());

    QSize availableSize{int(0.75 * width()), int(0.85 * height())};

    if      (mouse_pos.x() >= (0.05 * width() + 2.90 * availableSize.width()/3) &&
            mouse_pos.y() >= (0.15 * height() + 2 * availableSize.height()/3) &&
            mouse_pos.x() <= (0.05 * width() + 2.90 * availableSize.width()/3 + 0.8 * availableSize.width()/3 ) &&
            mouse_pos.y() <= (0.15 * height() + 2 * availableSize.height()/3 +  0.75 * availableSize.height()/3))
    {
        emit signalRefreshSystems();
        return;
    }

        QSize pix_size {int(0.8 * availableSize.width()/3),  int(0.45 * height())};
        QPoint pix_start{int(0.05 * width() + 2.90 * availableSize.width()/3), int(0.15 * height())};

        systemConnection statuses[3] = {Paired, Repeater, Disconnected};

        for (int k = 0; k<3; k++)
        {

            if(mouse_pos.x()>=(pix_start.x() + 0.11 * pix_size.width())&&
               mouse_pos.y()>=(pix_start.y() + 0.85 * pix_size.height()/3 + 1.9 * k * pix_size.height()/9)&&
               mouse_pos.x()<=(pix_start.x() + 0.11 * pix_size.width() + pix_size.width())&&
               mouse_pos.y()<=(pix_start.y() + 0.85 * pix_size.height()/3 + 1.9 * k * pix_size.height()/9 + 2 * pix_size.height()/9))
            {

               emit signalSetupSelected(statuses[k]);
                return;

            }


        }
        for (int i = 0; i < m_system_setup_widget_container->getSystemCount(); i++)
        {
            m_selection_vector[i] = false;
        }





}


void SystemSetupScreen::setupLayout()
{

    m_system_setup_widget_container->move(0, 0.05 * height());
    m_system_setup_widget_container->resize(width(), 0.95 * height());
}

void SystemSetupScreen::resizeEvent(QResizeEvent *)
{
    updateScale();
    SetupScreen::setupLayout();
    setupLayout();
}

