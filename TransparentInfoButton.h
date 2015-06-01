#ifndef TRANSPARENTINFOBUTTON_H
#define TRANSPARENTINFOBUTTON_H

#include "ScalableWidget.h"

class TransparentInfoButton : public ScalableWidget
{
    Q_OBJECT

    QString m_title;
    QString m_value;

public:
    TransparentInfoButton(QWidget* parent, QSize base_size, QString title, QString value);

    void setValue(const QString& value);

signals:
    void pressed();

protected:
    void paintEvent(QPaintEvent*);
    void mouseReleaseEvent(QMouseEvent*);
};

#endif // TRANSPARENTINFOBUTTON_H
