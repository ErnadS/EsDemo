#include "runtime_widget_es.h"
#include "information_widget.h"
#include "brightness_widget.h"
#include "navigation_widget.h"
#include "utility/data_processing.h"
#include <QMouseEvent>
#include <QPainter>

RuntimeWidgetEs::RuntimeWidgetEs(QWidget* parent, QSize base_size) :
    ScalableWidget(parent, base_size)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(timeout()));

    timer.start(10);

    m_bin_file.open(QIODevice::ReadOnly);

    m_range_info = new TransparentInfoButton(this, m_range_info_button_size, "Range", "500m");
    m_power_info = new TransparentInfoButton(this, m_power_info_button_size, "Power", "100%");
    m_transducer_info = new TransparentInfoButton(this, m_transducer_info_button_size, "Transducer", "FWD / 200");

    connect(m_range_info, SIGNAL(clicked()), this, SLOT(rangeChanged()));

    updateInfo();
}

void RuntimeWidgetEs::setFontSize(int font_size)
{
    m_font_size=font_size;
    repaint();
}

int RuntimeWidgetEs::getFontSize() const
{
    return m_font_size;
}

void RuntimeWidgetEs::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QImage image(m_buffer.size(), sample_size, QImage::Format_RGB888);
    image.fill(Qt::black);

    int index = 0;
    for (auto v: m_buffer)
    {
        int i = m_buffer.size() - 1 - index;

        for (int j = 0; j < v[m_color_index].size(); j++)
        {
            image.setPixel(i, j, v[m_color_index][j].rgba());
        }

        index++;
    }

    image = image.scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    painter.drawImage(QPoint(0, 0), image);

    // TODO: Clean up implementation
    QPen pen(Qt::white);
    pen.setWidth(2);

    QFont font = painter.font();
    font.setPixelSize(25 * m_scale);

    painter.setPen(pen);
    painter.setFont(font);

    int size = 8;
    qreal max_depth = m_max_depth_vector[m_depth_index];
    int depth_step = max_depth / (size + 2);
    for (int i = 0; i <= size; i++)
    {
        qreal step = qreal(image.height()) / size;

        painter.drawLine(0.9875f * image.width(), i * step, image.width(), i * step);

        QSize label_size(55 * m_width_scale, 20 * m_height_scale);
        QRect label_rect(QPoint(0.9875f * image.width() - label_size.width() - 10 * m_width_scale, i * step - 0.5f * label_size.height()), label_size);

        if ((i % 2 != 0) && (i != size / 2))
        {
            //painter.fillRect(label_rect, Qt::green);

            int depth = (i + 1) * depth_step;
            QString depth_label = QString::number(depth);

            painter.drawText(label_rect, Qt::AlignVCenter | Qt::AlignRight, depth_label);
        }
    }

    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawLine(0, image.height() / 2, image.width(), image.height() / 2);

    QRect label_rect(0, 0, 0.25f * width(), 0.15f * height());
    //painter.fillRect(label_rect, Qt::red);
    QRect source_rect(0, label_rect.height(), 0.25f * width(), 0.1f * height());
    //painter.fillRect(source_rect, Qt::blue);

    painter.setPen(Qt::white);

    font.setPixelSize(m_font_size);
    painter.setFont(font);

    // TODO: Validation
    if (m_depth < 1000.0f)
    {
        qreal depth = max_depth * m_depth / 1000.0f;

        // TODO: Value
        painter.drawText(label_rect, QString::number(depth, 'f', 1));
    }
    else
    {
        painter.drawText(label_rect, "-.-");
    }

    font.setPixelSize(int(0.37 * m_font_size));
    painter.setFont(font);

    painter.drawText(source_rect, "Depth Below Surface");
}

void RuntimeWidgetEs::mousePressEvent(QMouseEvent* event)
{
    if (event->x() >= 0.8f * width())
    {
        m_target = MousePressTarget::Right;
    }
    else if (event->y() >= 0.8f * height())
    {
        m_target = MousePressTarget::Bottom;
    }
    else
    {
        m_target = MousePressTarget::Top;
    }

    updateInfo();
}

void RuntimeWidgetEs::updateInfo()
{
    switch (m_target)
    {
        case MousePressTarget::Right:
            m_color_index = (m_color_index + 1) % 4;
            update();
            break;

        case MousePressTarget::Bottom:
            m_range_info->show();
            m_power_info->show();
            m_transducer_info->show();
            break;

        case MousePressTarget::Top:
            m_range_info->hide();
            m_power_info->hide();
            m_transducer_info->hide();
    }
}

void RuntimeWidgetEs::timeout()
{
    QByteArray buffer;
    const int buffer_size{512};

    buffer = m_bin_file.read(buffer_size);

    if (buffer.size() == buffer_size)
    {
        QVector<QVector<QColor>> color_buffer(4, QVector<QColor>(buffer_size));

        for (int i = 0; i < buffer_size / 2; i++)
        {
            char temp = buffer[i];
            buffer[i] = buffer[buffer_size - i - 1];
            buffer[buffer_size - i - 1] = temp;
        }

        for (int i = 0; i < buffer_size; i++)
        {
            unsigned char value = (unsigned char)buffer[i];

            color_buffer[0][i] = m_color_table_0.interpolate(value);
            color_buffer[1][i] = m_color_table_1.interpolate(value);
            color_buffer[2][i] = m_color_table_2.interpolate(value);
            color_buffer[3][i] = m_color_table_3.interpolate(value);
        }

        m_buffer.append(color_buffer);

        char output_buffer[buffer_size];
        DataProcessing::kalmanFilter(buffer.data(), buffer_size, output_buffer);
        m_depth = DataProcessing::bottomDetection(output_buffer, buffer_size) / 10.0f;
    }
    else
    {
        m_bin_file.close();
        m_bin_file.open(QIODevice::ReadOnly);
    }

    update();
}

void RuntimeWidgetEs::rangeChanged()
{
    m_depth_index = (m_depth_index + 1) % m_max_depth_vector.size();

    int max_depth = m_max_depth_vector[m_depth_index];

    m_range_info->setValue(QString::number(max_depth) + "m");
    update();
}

void RuntimeWidgetEs::resizeEvent(QResizeEvent* event)
{
    ScalableWidget::resizeEvent(event);

    QSize range_size(m_range_info_button_size.width() * m_width_scale, m_range_info_button_size.height() * m_height_scale);
    QSize power_size(m_power_info_button_size.width() * m_width_scale, m_power_info_button_size.height() * m_height_scale);
    QSize transducer_size(m_transducer_info_button_size.width() * m_width_scale, m_transducer_info_button_size.height() * m_height_scale);

    m_range_info->resize(range_size);
    m_power_info->resize(power_size);
    m_transducer_info->resize(transducer_size);

    qreal space = 5.0f * m_width_scale;

    QPoint range_pos(space, height() - m_range_info->height() - space);
    m_range_info->move(range_pos);

    QPoint power_pos(m_range_info->width() + 2.0f * space, range_pos.y());
    m_power_info->move(power_pos);

    QPoint transducer_pos(m_range_info->width() + m_power_info->width() + 3.0f * space, range_pos.y());
    m_transducer_info->move(transducer_pos);

}
