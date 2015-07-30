#ifndef UTILITY_FONT_H
#define UTILITY_FONT_H

#include <QFont>
#include <QPoint>

QPoint textSize(const QFont& font, const QString& text);
QPoint textSize(const QFont* font, const QString& text);

#endif
