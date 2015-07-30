#include "color_table.h"

bool ColorTable::isKeyValid(qreal key)
{
    if ((key < 0.0f) || (key > 1.0f))
    {
        // TODO: Log error

        return false;
    }

    return true;
}

ColorTable::ColorTable(std::initializer_list<std::pair<qreal, QColor>> list)
{
    m_color_map.insert(0.0f, Qt::black);

    for (auto e: list)
    {
        if (isKeyValid(e.first) == true)
        {
            m_color_map.insert(e.first, e.second);
        }
    }
}

ColorTable::ColorTable(std::initializer_list<QColor> list)
{
    qreal step = 1.0f / list.size();
    int i = 0;

    for (auto e: list)
    {
        qreal key = i * step;

        m_color_map.insert(key, e);

        i++;
    }
}

ColorTable::ColorTable()
{
    m_color_map.insert(0.0f, Qt::black);
}

bool ColorTable::insert(qreal key, QColor value)
{
    if (isKeyValid(key) == true)
    {
        m_color_map.insert(key, value);
        return true;
    }

    return false;
}

QColor ColorTable::interpolate(qreal value)
{
    if (isKeyValid(value) == false)
    {
        // TODO: Log
        return m_color_map[0.0f];
    }

    auto upper = m_color_map.upperBound(value);
    if (upper == m_color_map.end())
    {
        return (upper - 1).value();
    }

    auto lower = upper - 1;
    qreal range = upper.key() - lower.key();
    qreal alpha = (value - lower.key()) / range;

    int r = (1.0f - alpha) * lower.value().red() + alpha * upper.value().red();
    int g = (1.0f - alpha) * lower.value().green() + alpha * upper.value().green();
    int b = (1.0f - alpha) * lower.value().blue() + alpha * upper.value().blue();

    return QColor(r, g, b);
}

QColor ColorTable::interpolate(unsigned char value)
{
    return interpolate(qreal(value) / 256);
}
