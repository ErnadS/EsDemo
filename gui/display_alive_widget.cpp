#include "display_alive_widget.h"
#include <QPainter>
#include <QTime>
#include "utility/utility_font.h"

void DisplayAliveWidget::toggleBlink()
{
    m_toggled = !m_toggled;

    update();
}

DisplayAliveWidget::DisplayAliveWidget(QWidget* parent, QSize base_size) : ScalableWidget(parent, base_size)
{
    m_blink_timer = new QTimer(this);
    m_blink_timer->start(2000);

    connect(m_blink_timer, SIGNAL(timeout()), this, SLOT(toggleBlink()));
}

void DisplayAliveWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QFont font;
    font.setPixelSize(m_font_pixel_size * m_scale);
    painter.setFont(font);

    QTime time = QTime::currentTime();
    m_hours = QString("%1").arg(time.hour(), 2, 10, QChar('0'));
    m_minutes = QString("%1").arg(time.minute(), 2, 10, QChar('0'));

    int hour_pos = 0;
    QPoint value_metric = textSize(font, "00");
    int seperator_pos = value_metric.x();
    value_metric = textSize(font, ":");
    int minute_pos = seperator_pos + value_metric.x();

    painter.setPen(QColor(144, 255, 112));

    painter.drawText(QRectF(hour_pos, 0, width(), height()), Qt::AlignLeft, m_hours);

    if (m_toggled == true)
    {
        painter.drawText(QRectF(seperator_pos, 0, width(), height()), Qt::AlignLeft, ":");
    }

    painter.drawText(QRectF(minute_pos, 0, width(), height()), Qt::AlignLeft, m_minutes);
}
