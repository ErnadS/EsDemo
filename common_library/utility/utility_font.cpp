#include "utility_font.h"
#include <QFontMetrics>

QPoint textSize(const QFont& font, const QString& text)
{
    QFontMetrics metrics(font);
    return QPoint(metrics.width(text), metrics.height());
}

QPoint textSize(const QFont* font, const QString& text)
{
    QFontMetrics metrics(*font);
    return QPoint(metrics.width(text), metrics.height());
}
