#ifndef SYSTEM_SETUP_WIDGET_H
#define SYSTEM_SETUP_WIDGET_H

#include "scalable_widget.h"

enum systemConnection { Paired, Repeater, Disconnected };

class SystemSetupWidget : public ScalableWidget
{
    Q_OBJECT

    bool m_selected{false};
    QString m_system_type;
    QString m_system_name;
    QString m_system_ID;
    QString m_system_IP;
    systemConnection m_system_connection;

public:
    SystemSetupWidget(QWidget* parent, QSize base_size, QString system_type, QString system_name, QString system_ID, QString system_IP, systemConnection system_connection);
    void setActive(bool active);
    bool isActive() const;
    void setSystemConnection(systemConnection system_connection);
    systemConnection getSystemConnection () const;
    QString getSystemType() const;
    QString getSystemID() const;
    QString getSystemName() const;
    QString getSystemIP() const;

signals:
    void signalSystemSelected(SystemSetupWidget* sys_setup_widget);
protected:
    void paintEvent(QPaintEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    QPixmap drawSystemIcon();


};

#endif // SYSTEM_SETUP_WIDGET_H
