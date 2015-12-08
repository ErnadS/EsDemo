#ifndef SYSTEM_MENU_WIDGET_CONTAINER_H
#define SYSTEM_MENU_WIDGET_CONTAINER_H

#include "scalable_widget.h"
#include "system_setup_widget.h"
#include "display_button.h"
#include <QLabel>
#include <QRect>

class SystemMenuWidgetContainer : public ScalableWidget
{
    Q_OBJECT

    QLabel *m_paired_label;
    QLabel *m_repeaters_label;

    DisplayButton *m_display_button;
    QSize m_display_button_base_size;
    QSize m_system_base_size;
    QVector<SystemSetupWidget*> m_system_setup_widget_vector;
    SystemSetupWidget *m_last_selected;

    void setupLayout();

public:
    SystemMenuWidgetContainer(QWidget *parent, QSize base_size, QList<QString> type_list, QList<QString> name_list);

    void addSystem(QString type, QString name, QString system_ID, QString system_IP, systemConnection system_connection);
    void removeSystem(int index);
    int getSystemCount() const;
    void setSelected(int index);
    void setDisplaySelected();
    SystemSetupWidget* getSelected() const;
    int getSelectedIndex() const;
    SystemSetupWidget* getSystemAtIndex(int index) const;

signals:
    void systemSelected(int system_index);
    void displaySelected();

private slots:
    void slotSystemSelected(SystemSetupWidget *system);
    void slotDisplaySelected();

protected:
    void resizeEvent(QResizeEvent*);
    void paintEvent(QPaintEvent*);
};

#endif // SYSTEM_MENU_WIDGET_CONTAINER_H
