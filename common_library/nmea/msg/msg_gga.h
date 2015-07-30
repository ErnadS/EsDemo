//////////////////////////////////////////////////////////////
// Standard Sentence:
// ***********************************************************
// GGA Global Positioning System Fix Data. Time, Position and fix related data for a GPS receiver
//         1          2     3    4     5 6 7   8   9 10 11 12 13  14  15
//         |          |     |    |     | | |   |   |  |  |  |  |   |   |
// $--GGA,hhmmss.ss,llll.ll,a,yyyyy.yy,a,x,xx,x.x,x.x,M,x.x,M,x.x,xxxx*hh
// 1) Time (UTC)
// 2) Latitude
// 3) N or S (North or South)
// 4) Longitude
// 5) E or W (East or West)
// 6) GPS Quality Indicator,
//      0 - fix not available,
//      1 - GPS fix,
//      2 - Differential GPS fix
// 7) Number of satellites in view, 00 - 12
// 8) Horizontal Dilution of precision
// 9) Antenna Altitude above/below mean-sea-level (geoid)
// 10) Units of antenna altitude, meters
// 11) Geoidal separation, the difference between the WGS-84 earth
//     ellipsoid and mean-sea-level (geoid),"-" means mean-sea-level below ellipsoid
// 12) Units of geoidal separation, meters
// 13) Age of differential GPS data, time in seconds since last SC104
//     type 1 or 9 update, null field when DGPSis not used
// 14) Differential reference station ID, 0000-1023
// 15) Checksum
//////////////////////////////////////////////////////////////

#ifndef MSG_GGA_H
#define MSG_GGA_H

#include "nmea/nmea_message.h"

class MsgGGA : public NmeaMessage
{
public:
    MsgGGA();
    MsgGGA(QString time, float latitude, QString northOrSouth, float longitude, QString eastOrWest, 
           int gpsQualityIndicator, int nrOfSatellitesInView, float horDilPrecision, float antennaAltitude,
           QString unitsOfAntAlt, float geoidalseparation, QString unitsOfGeoidals, float ageOfGpsData, 
           int difRefStationID);

    QString time;                          // hhmmss.ss = Time of alarm (UTC)
    float latitude;                        // llll.ll = Latitude
    QString northOrSouth;                  // a = N or S (North or South)
    float longitude;                       // llll.ll = Latitude
    QString eastOrWest;                    // a = E or W (East or West)
    int gpsQualityIndicator;               // x = 0 - fix not available, 1 - GPS fix, 2 - Differential GPS fix
    int nrOfSatellitesInView;              // xx = Number of satellites in view, 00 - 12
    float horDilPrecision;                 // x.x = Horizontal Dilution of precision
    float antennaAltitude;                 // x.x = Antenna Altitude above/below mean-sea-level (geoid)
    QString unitsOfAntAlt;                 // M = Units of antenna altitude, meters
    float geoidalseparation;               // x.x = Geoidalseparation, the difference between the WGS-84 earth ellipsoid and mean-sea-level (geoid),"-" means mean-sea-level below ellipsoid
    QString unitsOfGeoidals;               // M = Units of antenna altitude, meters
    float ageOfGpsData;                    // x.x = Age of differential GPS data, time in seconds since last SC104
    int difRefStationID;                   // xxxx = Differential reference station ID, 0000-1023


    static const unsigned long GGAhash = 4671297;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgGGA * clone() {return new MsgGGA(*this);}
};

#endif
