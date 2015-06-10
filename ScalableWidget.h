#ifndef SCALABLEWIDGET_H
#define SCALABLEWIDGET_H

#include <QWidget>
#include <QSize>

class ScalableWidget : public QWidget
{
    Q_OBJECT

protected:
    explicit ScalableWidget(QWidget* parent, QSize base_size);

    qreal m_scale{1.0};
    qreal m_width_scale{1.0};
    qreal m_height_scale{1.0};

    void updateScale();

protected:
    void resizeEvent(QResizeEvent*);
};

#endif // SCALABLEWIDGET_H
