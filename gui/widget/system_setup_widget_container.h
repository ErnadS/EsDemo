#ifndef SYSTEM_SETUP_WIDGET_CONTAINER_H
#define SYSTEM_SETUP_WIDGET_CONTAINER_H

#include "scalable_widget.h"
#include "system_setup_widget.h"

class SystemSetupWidgetContainer : public ScalableWidget
{
    Q_OBJECT

    QSize m_item_base_size;
    int m_display_size;
    QVector<SystemSetupWidget*> m_system_setup_widget_vector;


    void setupLayout();


public:
    explicit SystemSetupWidgetContainer(QWidget* parent, QSize base_size, int display_size, QList<QString> type_list, QList<QString> name_list);
    void setActive(int index);

    void addSystem(QString type, QString name, QString system_ID, QString system_IP, systemConnection system_connection);
    void removeSystem(int index);
    void setSystemConnection(int index, systemConnection system_connection);
    int getSystemCount() const;
    QVector<SystemSetupWidget *> getSystems() const;

signals:
    void itemSelected(int index);

private slots:
    void slotSystemSelected(SystemSetupWidget *item);

protected:
    void resizeEvent(QResizeEvent*);
    void paintEvent(QPaintEvent*);
    void drawConnections(QPainter& painter);
};

#endif // SYSTEM_SETUP_WIDGET_CONTAINER_H
