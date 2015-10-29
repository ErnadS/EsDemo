#include "up_down_widget.h"
#include <QPainter>

void UpDownWidget::drawUpArrow(QPainter& painter, const QRect& arrow_rect)
{
    QPolygon polygon(8);

        qreal alpha = 0.185f;
        qreal w = arrow_rect.width();
        qreal h = arrow_rect.height();

        QPoint c = arrow_rect.center();
        c = QPoint(c.x(), c.y() + 1.0f * alpha * h);

        QPoint top_left = QPoint(c.x() - alpha * w, c.y() - alpha * h);
        QPoint top_right = QPoint(c.x() + alpha * w, c.y() - alpha * h);

        QPoint bottom_left = QPoint(c.x() - alpha * w, c.y() + alpha * h);
        QPoint bottom_right = QPoint(c.x() + alpha * w, c.y() + alpha * h);

        QPoint triangle_top_left = QPoint(top_left.x() - 0.75f * alpha * w, top_left.y());
        QPoint triangle_top_right  = QPoint(top_right.x() + 0.75f * alpha * w, top_right.y());;
        QPoint triangle_top = QPoint(c.x(), c.y() - 3.0f * alpha * h);

        polygon[0] = top_left;
        polygon[1] = triangle_top_left;
        polygon[2] = triangle_top;
        polygon[3] = triangle_top_right;
        polygon[4] = top_right;
        polygon[5] = bottom_right;
        polygon[6] = bottom_left;
        polygon[7] = top_left;

        QPainterPath path;
        path.addPolygon(polygon);

        painter.fillPath(path, Qt::white);

        QPen pen = painter.pen();
        pen.setColor(Qt::black);
        painter.setPen(pen);

        painter.drawPath(path);
}

void UpDownWidget::drawDownArrow(QPainter& painter, const QRect& arrow_rect)
{
    QPolygon polygon(8);

        qreal alpha = 0.185f;
        qreal w = arrow_rect.width();
        qreal h = arrow_rect.height();

        QPoint c = arrow_rect.center();
        c = QPoint(c.x(), c.y() - 1.0f * alpha * h);

        QPoint top_left = QPoint(c.x() - alpha * w, c.y() - alpha * h);
        QPoint top_right = QPoint(c.x() + alpha * w, c.y() - alpha * h);

        QPoint bottom_left = QPoint(c.x() - alpha * w, c.y() + alpha * h);
        QPoint bottom_right = QPoint(c.x() + alpha * w, c.y() + alpha * h);

        QPoint triangle_bottom_left = QPoint(bottom_left.x() - 0.75f * alpha * w, bottom_left.y());
        QPoint triangle_bottom_right  = QPoint(bottom_right.x() + 0.75f * alpha * w, bottom_right.y());;
        QPoint triangle_bottom = QPoint(c.x(), c.y() + 3.0f * alpha * h);

        polygon[0] = top_left;
        polygon[1] = top_right;
        polygon[2] = bottom_right;
        polygon[3] = triangle_bottom_right;
        polygon[4] = triangle_bottom;
        polygon[5] = triangle_bottom_left;
        polygon[6] = bottom_left;
        polygon[7] = top_left;

        QPainterPath path;
        path.addPolygon(polygon);

        painter.fillPath(path, Qt::white);

        QPen pen = painter.pen();
        pen.setColor(Qt::black);
        painter.setPen(pen);

        painter.drawPath(path);
}

UpDownWidget::UpDownWidget(QWidget* parent, QSize base_size, QString title, QString unit, qreal step, qreal value) : ScalableWidget(parent, base_size), m_title(title), m_unit(unit), m_step(step), m_value(value)
{
    m_up_pressed = false;
    m_down_pressed = false;

    m_background_color = QColor(168, 168, 168);
    m_border_color = QColor(168, 168, 168);
}

void UpDownWidget::setBackgroundColor(const QColor& value)
{
    m_background_color = value;
    update();
}

void UpDownWidget::setBorderColor(const QColor& value)
{
    m_border_color = value;
    update();
}

void UpDownWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QBrush brush(m_background_color, Qt::SolidPattern);

    QColor color = Qt::black;
    painter.setPen(QPen(color));

    painter.fillRect(0, 0, width(), height(), QBrush(m_border_color, Qt::SolidPattern));
    painter.fillRect(2, 2, width() - 4, height() - 4, brush);

    QFont font = painter.font();
    font.setPixelSize(20 * m_scale);
    painter.setFont(font);

    QRect title_rect(0, 0, 0.4f * width(), height());
    QRect up_rect(0.4f * width(), 0, 0.2f * width(), height());
    QRect value_rect(0.6f * width(), 0, 0.2f * width(), height());
    QRect down_rect(0.8f * width(), 0, 0.2f * width(), height());

    //painter.fillRect(title_rect, Qt::red);
    //painter.fillRect(m_up_rect, Qt::blue);
    //painter.fillRect(value_rect, Qt::green);
    //painter.fillRect(m_down_rect, Qt::blue);

    painter.drawText(title_rect, Qt::AlignCenter, m_title);

    QString value_string = QString::number(m_value, 'f', 1) + "\n" + m_unit;
    painter.drawText(value_rect, Qt::AlignCenter, value_string);

    drawUpArrow(painter, up_rect);
    drawDownArrow(painter, down_rect);
}
