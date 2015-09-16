#ifndef SYSTEM_WIDGET_H
#define SYSTEM_WIDGET_H

#include "scalable_widget.h"

class SystemWidget : public ScalableWidget
{
    Q_OBJECT

    bool m_active{false};
    QString m_system_type;
    QString m_system_name;

    void drawBoat(QPainter& painter, const QRect rect);

public:
    SystemWidget(QWidget* parent, QSize base_size, QString system_type, QString system_name);
    void setActive(bool active);
    bool isActive() const;

signals:
    void pressed(const SystemWidget* address);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent*);
    void mouseReleaseEvent(QMouseEvent*);
};

#endif
