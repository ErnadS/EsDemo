#include "unitconverter.h"
#include <qmath.h>

const float UnitConverter::METERS_IN_NAUTICAL_MILE = 1852.0;
const float UnitConverter::METERS_IN_MILE = 1609.344;
const float UnitConverter::METERS_IN_KILOMETRE = 1000.0;
const float UnitConverter::SECONDS_IN_HOUR = 3600.0;
const float UnitConverter::METERS_IN_FOOT = 0.3048;
const float UnitConverter::METERS_IN_FATHOM = 1.8288;
const float UnitConverter::MILI_SECONDS_IN_HOUR = 3600000.0;

float UnitConverter::mpsToKn(float mpsValue)
{
    float knValue = (mpsValue*SECONDS_IN_HOUR)/METERS_IN_NAUTICAL_MILE;
    return knValue;
}

float UnitConverter::knToMps(float knValue)
{
    float mpsValue = (knValue/SECONDS_IN_HOUR)*METERS_IN_NAUTICAL_MILE;
    return mpsValue;
}

float UnitConverter::mpsToKmh(float mpsValue)
{
    float kmhValue = (mpsValue*SECONDS_IN_HOUR)/METERS_IN_KILOMETRE;
    return kmhValue;
}

float UnitConverter::kmhToMps(float kmhValue)
{
    float mpsValue = (kmhValue/SECONDS_IN_HOUR)*METERS_IN_KILOMETRE;
    return mpsValue;
}

float UnitConverter::mpsToMiph(float mpsValue)
{
    float mihValue = (mpsValue*SECONDS_IN_HOUR)/METERS_IN_MILE;
    return mihValue;
}

float UnitConverter::miphToMps(float mihValue)
{
    float mpsValue = (mihValue/SECONDS_IN_HOUR)*METERS_IN_MILE;
    return mpsValue;
}

float UnitConverter::knToKmh(float knValue)
{
    float mpsValue = knToMps(knValue);
    float kmhValue = mpsToKmh(mpsValue);
    return kmhValue;
}

float UnitConverter::kmhToKn(float kmhValue)
{
    float mpsValue = kmhToMps(kmhValue);
    float knValue = mpsToKn(mpsValue);
    return knValue;
}

float UnitConverter::knToMiph(float knValue)
{
    float mpsValue = knToMps(knValue);
    float mihValue = mpsToMiph(mpsValue);
    return mihValue;
}

float UnitConverter::miphToKn(float mihValue)
{
    float mpsValue = miphToMps(mihValue);
    float knValue = mpsToKn(mpsValue);
    return knValue;
}

float UnitConverter::kmhToMiph(float kmhValue)
{
    float mpsValue = kmhToMps(kmhValue);
    float mihValue = mpsToMiph(mpsValue);
    return mihValue;
}

float UnitConverter::miphToKmh(float mihValue)
{
    float mpsValue = miphToMps(mihValue);
    float kmhValue = mpsToKmh(mpsValue);
    return kmhValue;
}

float UnitConverter::speedToDefault(float value, QString currentUnit)
{
    float resultValue = value;
    QString converteFrom;
    if(currentUnit == "GetItFromSetup")
        converteFrom = SystemSetup::getInstance()->CuM001Setup.getUnitsSpeedString();
    else
        converteFrom = currentUnit;

    if(converteFrom == "mps")
        resultValue = mpsToKn(value);

    else if(converteFrom == "miph")
        resultValue = miphToKn(value);

    else if(converteFrom == "kmh")
        resultValue = kmhToKn(value);


    return resultValue;
}

float UnitConverter::speedFromDefault(float value, QString newUnit)
{
    float resultValue = value;
    QString converteTo;
    if(newUnit == "GetItFromSetup")
        converteTo = SystemSetup::getInstance()->CuM001Setup.getUnitsSpeedString();
    else
        converteTo = newUnit;

    if(converteTo == "mps")
        resultValue = knToMps(value);

    else if(converteTo == "miph")
        resultValue = knToMiph(value);

    else if(converteTo == "kmh")
        resultValue = knToKmh(value);


    return resultValue;
}

float UnitConverter::mToFt(float mValue)
{
    float ftValue = mValue/METERS_IN_FOOT;
    return ftValue;
}

float UnitConverter::ftToM(float ftValue)
{
    float mValue = ftValue*METERS_IN_FOOT;
    return mValue;
}

float UnitConverter::mToFtm(float mValue)
{
    float ftmValue = mValue/METERS_IN_FATHOM;
    return ftmValue;
}

float UnitConverter::ftmToM(float ftmValue)
{
    float mValue = ftmValue*METERS_IN_FATHOM;
    return mValue;
}

float UnitConverter::ftToFtm(float ftValue)
{
    float mValue = ftToM(ftValue);
    float ftmValu = mToFtm(mValue);
    return ftmValu;
}

float UnitConverter::ftmToFt(float ftmValue)
{
    float mValue = ftmToM(ftmValue);
    float ftValu = mToFt(mValue);
    return ftValu;
}

float UnitConverter::lengthToDefault(float value, QString currentUnit)
{
    float resultValue = value;
    QString converteFrom;
    if(currentUnit == "GetItFromSetup")
        converteFrom = SystemSetup::getInstance()->CuM001Setup.getUnitsDepthString();
    else
        converteFrom = currentUnit;

    if(converteFrom == "ft")
        resultValue = ftToM(value);

    else if(converteFrom == "ftm")
        resultValue = ftmToM(value);


    return resultValue;
}

float UnitConverter::lengthFromDefault(float value, QString newUnit)
{
    float resultValue = value;
    QString converteTo;
    if(newUnit == "GetItFromSetup")
        converteTo = SystemSetup::getInstance()->CuM001Setup.getUnitsDepthString();
    else
        converteTo = newUnit;

    if(converteTo == "ft")
        resultValue = mToFt(value);

    else if(converteTo == "ftm")
        resultValue = mToFtm(value);


    return resultValue;
}

int UnitConverter::floatToInt(float value)
{
    if (value == std::numeric_limits<float>::max())
    {
        return std::numeric_limits<int>::max();
    }

    return (int)(value*100.0f);
}

float UnitConverter::intToFloat(int value)
{
    if (value == std::numeric_limits<int>::max())
    {
        return std::numeric_limits<float>::max();
    }

    return (((float)value)/100.0f);
}

int UnitConverter::floatToInt3(float value)
{
    if (value == std::numeric_limits<float>::max())
    {
        return std::numeric_limits<int>::max();
    }

    return (int)(value*1000.0f);
}

float UnitConverter::intToFloat3(int value)
{
    if (value == std::numeric_limits<int>::max())
    {
        return std::numeric_limits<float>::max();
    }

    return (((float)value)/1000.0f);
}

int UnitConverter::degToRad(float value)
{
    return value*M_PI/180;
}

float UnitConverter::radToDeg(float value)
{
    return value*180/M_PI;
}
