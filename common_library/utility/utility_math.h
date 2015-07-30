#ifndef UTILITY_MATH_H
#define UTILITY_MATH_H

#include <QtMath>

const double pi = 4.0 * qAtan(1.0);

// Converts from degrees to radian
qreal degToRad(qreal deg)
{
    return deg * pi / 180.0;
}

// Converts from radian to degrees
qreal radToDeg(qreal rad)
{
    return 180.0 * rad / pi;
}

// Normalizes radian angle to range [-pi, pi]
qreal normalizeRad(qreal rad)
{
    return 2.0 * qAtan(qTan(0.5 * rad));
}

// Normalizes degree angle to range [-180.0, 180.0]
qreal normalizeDeg(qreal deg)
{
    qreal rad = degToRad(deg);
    rad = normalizeRad(rad);

    return radToDeg(rad);
}

// Normalizes degree angle to range [0, 360.0]
qreal normalizeDegPositive(qreal deg)
{
    if (deg < 0)
    {
        deg += 360.0;
    }
    else if (deg > 360.0)
    {
        deg -= 360.0;
    }

    return deg;
}

// Rotates coordinates (x, y, z) over x axis by angle t (in degrees)
void rotateX(const qreal&, qreal& y, qreal& z, qreal t)
{
    t = degToRad(t);

    qreal yp = y * qCos(t) - z * qSin(t);
    qreal zp = y * qSin(t) + z * qCos(t);

    y = yp;
    z = zp;
}

// Rotates coordinates (x, y, z) over y axis by angle t (in degrees)
void rotateY(qreal& x, const qreal&, qreal& z, qreal t)
{
    t = degToRad(t);

    qreal xp = x * qCos(t) + z * qSin(t);
    qreal zp = -x * qSin(t) + z * qCos(t);

    x = xp;
    z = zp;
}

// Rotates coordinates (x, y, z) over z axis by angle t (in degrees)
void rotateZ(qreal& x, qreal& y, const qreal&, qreal t)
{
    t = degToRad(t);

    qreal xp = x * qCos(t) - y * qSin(t);
    qreal yp = x * qSin(t) + y * qCos(t);

    x = xp;
    y = yp;
}

#endif
