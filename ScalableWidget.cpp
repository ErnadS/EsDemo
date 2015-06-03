#include "ScalableWidget.h"
#include <QTimer>
#include <QtCore/QtMath>
#include "RuntimeWidgetE.h"

QTimer* ScalableWidget::timer{nullptr};
qreal ScalableWidget::t = 0.0f;
qreal ScalableWidget::m_sog_long;
qreal ScalableWidget::m_sog_tra;
qreal ScalableWidget::m_sog;
qreal ScalableWidget::m_sog_angle;
qreal ScalableWidget::m_sog_tra_aft;

qreal ScalableWidget::m_stw_long;
qreal ScalableWidget::m_stw_tra;
qreal ScalableWidget::m_stw;
qreal ScalableWidget::m_stw_angle;

qreal ScalableWidget::m_wc_long;
qreal ScalableWidget::m_wc_tra;
qreal ScalableWidget::m_wc;
qreal ScalableWidget::m_wc_angle;
qreal ScalableWidget::m_stw_dl1;

qreal ScalableWidget::m_front_depth;
qreal ScalableWidget::m_side_depth;
qreal ScalableWidget::m_avg_depth;

qreal ScalableWidget::m_water_temp;

qreal ScalableWidget::m_trip{0.0f};
qreal ScalableWidget::m_total{137.42};

qreal ScalableWidget::m_true_heading{20.0};

void ScalableWidget::updateScale()
{
    m_width_scale = qreal(width()) / baseSize().width();
    m_height_scale = qreal(height()) / baseSize().height();

    m_scale = (m_width_scale < m_height_scale) ? m_width_scale : m_height_scale;
}

void ScalableWidget::resizeEvent(QResizeEvent*)
{
    updateScale();
}

QString ScalableWidget::string(qreal value)
{
    return QString::number(value, 'f', 1);
}

ScalableWidget::ScalableWidget(QWidget* parent, QSize base_size) :
    QWidget(parent)
{
    setBaseSize(base_size);
    resize(base_size);

    if (timer == nullptr)
    {
        timer = new QTimer(this);
        timer->start(1000);
        connect(timer, SIGNAL(timeout()), this, SLOT(simulate()));
    }

    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
}

void ScalableWidget::timeout()
{
    update();
}

qreal abs(qreal x, qreal y)
{
    return qSqrt(x * x + y * y);
}

qreal arg(qreal y, qreal x)
{
    const double pi = 4.0 * qAtan(1.0);

    return 180.0f * qAtan2(y, x) / pi;
}

void ScalableWidget::simulate()
{
    t += 0.0075;

    m_sog_long = 12.0f * qSin(t) + 1.0f;
    m_sog_tra = 8.0f * qSin(t) + 1.0f;
    m_sog = abs(m_sog_long, m_sog_tra);
    m_sog_angle = arg(m_sog_long, m_sog_tra);
    m_sog_tra_aft = m_sog_tra - 0.5f;

    m_stw_long = 10.0f * qSin(t) + 1.0f;
    m_stw_tra = 6.0f * qSin(t) + 1.0f;
    m_stw = abs(m_stw_long, m_stw_tra);
    m_stw_angle = arg(m_stw_long, m_stw_tra);

    m_wc_long = m_stw_long - m_sog_long;
    m_wc_tra = m_stw_tra - m_sog_tra;
    m_wc = abs(m_wc_long, m_wc_tra);
    m_wc_angle = arg(m_wc_long, m_wc_tra);

    m_stw_dl1 = 11.0f * qSin(t);

    m_side_depth = 75.f * (1.0f + qSin(2.0f * t));
    m_front_depth = 65.f * (1.0f + qSin(2.0f * t));
    m_avg_depth = 0.5f * (m_side_depth + m_front_depth);
    RuntimeWidgetE::addMeasurement(m_front_depth, m_side_depth);

    m_water_temp = 10.0f * (1.0f + qSin(t));

    qreal delta_d = m_sog / 3600.0f;
    m_trip += delta_d;
    m_total += delta_d;

    m_true_heading = 20.0f + 5.0f * sin(t);
}
