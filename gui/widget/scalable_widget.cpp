#include "scalable_widget.h"
#include <QTimer>
#include <QtCore/QtMath>
#include "runtime_widget_e.h"

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
    t += 1;
    if (t<11) {
        m_sog_long = 30.f;
        m_sog_tra = 0.f;
    }
    if (t>10 && t<21) m_sog_long = 10.0f;
    if (t>20 && t<31) m_sog_long = 2.0f;
    if (t>30 && t<41) m_sog_long = 0.5f;
    if (t>40) m_sog_long = 30.f;

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

    m_avg_depth = 0.5f * (m_side_depth + m_front_depth);

    m_water_temp = 10.0f * (1.0f + qSin(t));

    qreal delta_d = m_sog*t/3600.0f;
    m_trip += delta_d;
    m_total += delta_d;

    m_side_depth = 75.0f * (1.0f + qSin(m_trip/5));
    m_front_depth = 65.0f * (1.0f + qSin(m_trip/5));

    RuntimeWidgetE::addMeasurement(t, m_sog, m_front_depth, m_side_depth);

    m_true_heading = 20.0f + 5.0f * sin(t);
}

QString ScalableWidget::string(qreal value)
{
    return QString::number(value, 'f', 1);
}
