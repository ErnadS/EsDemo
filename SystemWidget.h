#ifndef SYSTEMWIDGET_H
#define SYSTEMWIDGET_H

#include "ScalableWidget.h"

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

signals:
    void clicked();

    // QWidget interface
protected:
    void paintEvent(QPaintEvent*);
    void mouseReleaseEvent(QMouseEvent*);
};

#endif // SYSTEMWIDGET_H
