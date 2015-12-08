#ifndef DISPLAY_BUTTON_H
#define DISPLAY_BUTTON_H

#include "scalable_widget.h"
#include <QPoint>
#include <QColor>

class DisplayButton : public ScalableWidget
{
    Q_OBJECT

    bool m_selected{false};
    int m_font_pixel_size{23};
    QString m_title{"CU-M001"};

public:
    DisplayButton(QWidget *parent, QSize base_size);

    void setSelected(bool selected);
    bool isSelected() const;

signals:
    void clicked();

protected:
    void paintEvent(QPaintEvent*);
    void mouseReleaseEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *);

public slots:
    void changeSelected();
};

#endif // DISPLAY_BUTTON_H
