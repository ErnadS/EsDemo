#include "title_widget.h"
#include <QPainter>

TitleWidget::TitleWidget(QWidget* parent, QSize base_size) : ScalableWidget(parent, base_size)
{

}

TitleWidget::TitleWidget(QWidget* parent, QSize base_size, QString title) : ScalableWidget(parent, base_size)
{
    m_title = title;
}

void TitleWidget::setTitle(const QString& title)
{
    m_title = title;

    update();
}

void TitleWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QBrush brush(QColor(64, 64, 64));

    QFont font = painter.font();
    font.setPixelSize(18 * m_scale);
    painter.setFont(font);

    // TODO: Load logo image from resource controller
    QRect logo_rect(0, 0, height(), height());
    QImage logo_image(":/skipper-no-background.jpg");
    logo_image = logo_image.scaled(logo_rect.size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    painter.drawImage(logo_rect, logo_image);

    painter.setPen(QColor(144, 255, 112));

    QRect label_rect(logo_rect.width(), 0, width() - logo_rect.width(), height());
    painter.fillRect(label_rect, brush);
    painter.drawText(label_rect, Qt::AlignCenter, m_title);
}
