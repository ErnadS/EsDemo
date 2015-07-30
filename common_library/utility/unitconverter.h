#ifndef UNITCONVERTER_H
#define UNITCONVERTER_H

#include "configuration/system_setup.h"

class UnitConverter
{
    static const float METERS_IN_NAUTICAL_MILE;
    static const float METERS_IN_MILE;
    static const float METERS_IN_KILOMETRE;
    static const float SECONDS_IN_HOUR;
    static const float METERS_IN_FOOT;
    static const float METERS_IN_FATHOM;
    static const float MILI_SECONDS_IN_HOUR;


public:

    // SPEED:
    //////////////////////////////////////////////
    static float mpsToKn(float mpsValue);
    static float knToMps(float knValue);

    static float mpsToKmh(float mpsValue);
    static float kmhToMps(float kmhValue);

    static float mpsToMiph(float mpsValue);
    static float miphToMps(float mihValue);
    //////////////////////////////////////
    static float knToKmh(float knValue);
    static float kmhToKn(float kmhValue);

    static float knToMiph(float knValue);
    static float miphToKn(float mihValue);

    static float kmhToMiph(float kmhValue);
    static float miphToKmh(float mihValue);
    //////////////////////////////////////
    static float speedToDefault(float value, QString currentUnit = "GetItFromSetup");
    static float speedFromDefault(float value, QString newUnit = "GetItFromSetup");
    //////////////////////////////////////////////

    // LENGTH:
    //////////////////////////////////////////////
    static float mToFt(float mValue);
    static float ftToM(float ftValue);

    static float mToFtm(float mValue);
    static float ftmToM(float ftmValue);
    ////////////////////////////////////
    static float ftToFtm(float ftValue);
    static float ftmToFt(float ftmValue);
    ////////////////////////////////////
    static float lengthToDefault(float value, QString currentUnit = "GetItFromSetup");
    static float lengthFromDefault(float value, QString newUnit = "GetItFromSetup");
    //////////////////////////////////////////////


    // TYPES:
    //////////////////////////////////////////////
    static int floatToInt(float value);
    static float intToFloat(int value);

    static int floatToInt3(float value);
    static float intToFloat3(int value);

    //////////////////////////////////////////////

    // ANGLE:
    //////////////////////////////////////////////
    static int degToRad(float value);
    static float radToDeg(float value);


    //////////////////////////////////////////////
};

#endif // UNITCONVERTER_H
