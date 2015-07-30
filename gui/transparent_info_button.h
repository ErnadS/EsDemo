#ifndef TRANSPARENT_INFO_BUTTON_H
#define TRANSPARENT_INFO_BUTTON_H

#include "scalable_widget.h"

class TransparentInfoButton : public ScalableWidget
{
    Q_OBJECT

    QString m_title;
    QString m_value;

public:
    TransparentInfoButton(QWidget* parent, QSize base_size, QString title, QString value);

    void setValue(const QString& value);

signals:
    void clicked();

protected:
    void paintEvent(QPaintEvent*);
    void mouseReleaseEvent(QMouseEvent*);
};

#endif
