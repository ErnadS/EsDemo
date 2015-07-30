#include "information_widget.h"
#include <QPainter>
#include <stdexcept>

QString InformationWidget::getDescription(InformationSource source)
{
    switch(source)
    {
        case InformationSource::W_TEMP:
            return "Water temp";

        case InformationSource::SOG_LONG:
            return "SOG long";

        case InformationSource::SOG_TRA:
            return "SOG tra";

        case InformationSource::SOG:
            return "SOG";

        case InformationSource::STW_LONG:
            return "STW long";

        case InformationSource::STW_TRA:
            return "STW tra";

        case InformationSource::STW:
            return "STW";

        case InformationSource::STW_DL1:
            return "STW DL1";

        case InformationSource::ALARM_HIGH:
            return "Alarm High";

        case InformationSource::ALARM_LOW:
            return "Alarm Low";

        case InformationSource::DEPTH:
            return "Depth";

        case InformationSource::TRIP:
            return "Trip";

        case InformationSource::TOTAL:
            return "Total";

        case InformationSource::DRAFT:
            return "Draft";

        case InformationSource::GPS_SOG:
            return "GPS SOG";

        case InformationSource::GAIN:
            return "Gain";

        case InformationSource::SHALLOW_ALARM:
            return "Shallow alarm";

        case InformationSource::DEEP_ALARM:
            return "Deep alarm";
    }

    throw std::invalid_argument("Provided argument is not in enum range.");
}

QString InformationWidget::getUnit(InformationSource source)
{
    switch(source)
    {
        case InformationSource::W_TEMP:
            return QString::fromUtf8("°C");

        case InformationSource::SOG_LONG:
            return "kn";

        case InformationSource::SOG_TRA:
            return "kn";

        case InformationSource::SOG:
            return "kn";

        case InformationSource::STW_LONG:
            return "kn";

        case InformationSource::STW_TRA:
            return "kn";

        case InformationSource::STW:
            return "kn";

        case InformationSource::STW_DL1:
            return "kn";

        case InformationSource::ALARM_HIGH:
            return "kn";

        case InformationSource::ALARM_LOW:
            return "kn";

        case InformationSource::DEPTH:
            return "m";

        case InformationSource::TRIP:
            return "NM";

        case InformationSource::TOTAL:
            return "NM";

        case InformationSource::DRAFT:
            return "m";

        case InformationSource::GPS_SOG:
            return "kn";

        case InformationSource::GAIN:
            return "%";

        case InformationSource::SHALLOW_ALARM:
            return "m";

        case InformationSource::DEEP_ALARM:
            return "m";
    }

    throw std::invalid_argument("Provided argument is not in enum range.");
}

InformationWidget::InformationWidget(QWidget* parent, QSize base_size, RuntimeScreenType screen_type) :
    ScalableWidget(parent, base_size)
{
    m_screen_type = screen_type;

    if ((m_screen_type == RUNTIME_ES) || (m_screen_type == RUNTIME_ES_B))
    {
        m_source_vector = {InformationSource::DRAFT, InformationSource::GPS_SOG, InformationSource::GAIN, InformationSource::SHALLOW_ALARM, InformationSource::DEEP_ALARM};
    }
}

void InformationWidget::setIndex(int index)
{
    if ((index < 0) || (index >= m_source_vector.size()))
        throw std::out_of_range("Provided index is out of range!");

    m_index = index;

    update();
}

void InformationWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QBrush brush(QColor(64, 64, 64));

    QFont font = painter.font();
    font.setPixelSize(20 * m_scale);
    painter.setFont(font);

    painter.setPen(QColor(144, 255, 112));
    painter.fillRect(QRectF(0, 0, width(), height()), brush);

    // TODO: Value
    QString description = m_title + " " + m_unit;
    painter.drawText(QRectF(0, 0, width(), height() / 3), Qt::AlignCenter, description);

    font.setPixelSize(40 * m_scale);
    painter.setFont(font);

    painter.drawText(QRectF(0, height() / 3, width(), 2.0 * height() / 3), Qt::AlignCenter, m_value);
}

void InformationWidget::mouseReleaseEvent(QMouseEvent*)
{
    m_index = (m_index + 1) % m_source_vector.size();
    update();
}
