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

    static QTimer* timer;

    static qreal t;

    static qreal m_sog_long;
    static qreal m_sog_tra;
    static qreal m_sog;
    static qreal m_sog_angle;
    static qreal m_sog_tra_aft;

    static qreal m_stw_long;
    static qreal m_stw_tra;
    static qreal m_stw;
    static qreal m_stw_angle;

    static qreal m_wc_long;
    static qreal m_wc_tra;
    static qreal m_wc;
    static qreal m_wc_angle;

    static qreal m_stw_dl1;

    static qreal m_front_depth;
    static qreal m_side_depth;
    static qreal m_avg_depth;

    static qreal m_water_temp;

    static qreal m_trip;
    static qreal m_total;

    const QColor m_color{144, 255, 112};

    static qreal m_true_heading;

protected:
    void resizeEvent(QResizeEvent*);

    QString string(qreal value);

private slots:
    void timeout();
    void simulate();
};

#endif // SCALABLEWIDGET_H
