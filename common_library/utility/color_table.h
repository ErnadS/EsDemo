#ifndef COLOR_TABLE_H
#define COLOR_TABLE_H

#include <QMap>
#include <QColor>

class ColorTable
{
    QMap<qreal, QColor> m_color_map;

    bool isKeyValid(qreal key);

public:
    explicit ColorTable(std::initializer_list<std::pair<qreal, QColor>> list);
    explicit ColorTable(std::initializer_list<QColor> list);
    explicit ColorTable();

    bool insert(qreal key, QColor value);

    QColor interpolate(qreal value);
    QColor interpolate(unsigned char value);
};

#endif
