#ifndef SYSTEM_WIDGET_CONTAINER_H
#define SYSTEM_WIDGET_CONTAINER_H

#include "scalable_widget.h"
#include "system_widget.h"
#include "arrow_widget.h"

class SystemWidgetContainer : public ScalableWidget
{
    Q_OBJECT

    int m_display_size;
    QVector<SystemWidget*> m_system_widget_vector;
    ArrowWidget* m_up_arrow;
    ArrowWidget* m_down_arrow;

    void setupLayout();

    int m_rotation_offset{0};

public:
    explicit SystemWidgetContainer(QWidget* parent, QSize base_size, int display_size, QList<QString> type_list, QList<QString> name_list);
    void setActive(int index);

signals:
    void itemSelected(int index);

private slots:
    void itemPressed(const SystemWidget* item);
    void upPressed();
    void downPressed();

protected:
    void resizeEvent(QResizeEvent*);
};

#endif
