/***********************************************************************
**
**   mapcontents.h
**
**   This file is part of KFLog2.
**
************************************************************************
**
**   Copyright (c):  2000 by Heiner Lamprecht, Florian Ehinger
**
**   This file is distributed under the terms of the General Public
**   Licence. See the file COPYING for more information.
**
**   $Id$
**
***********************************************************************/

#ifndef MAPCONTENTS_H
#define MAPCONTENTS_H

#include <qbitarray.h>
#include <qfile.h>
#include <qlist.h>
#include <qstrlist.h>

#include <basemapelement.h>

class Airport;
class Airspace;
class ElevPoint;
class Flight;
class GliderSite;
class Isohypse;
class LineElement;
class RadioPoint;
class SinglePoint;

/**
 * This class provides functions for accessing the contents of the map.
 * The class contains several QLists holding the mapelements.
 *
 * @author Heiner Lamprecht, Florian Ehinger
 * @version $Id$
 */
class MapContents
{
  public:
    /**
     * Creates a new MapContents-object.
     */
    MapContents();
    /**
     * Destructor, deletes all lists.
     */
    ~MapContents();
    /**
     * Returns the current length of the given list.
     */
    unsigned int getListLength(int listIndex) const;
    /**
     * Pr�ft, ob alle ben�tigten Kartenteile geladen sind und l�dt
     * eventuell fehlende Elemente hinzu.
     */
    void proofeSection();
    /**
     * Returns a BaseMapElement-pointer to the given mapelement in the list.
     */
    BaseMapElement* getElement(int listIndex, unsigned int index);
    /**
     * Returns a pointer to the given airspace.
     */
    Airspace* getAirspace(unsigned int index);
    /**
     * Returns a pointer to the given glidersite.
     */
    GliderSite* getGlidersite(unsigned int index);
    /**
     * Returns a pointer to the given airport.
     */
    Airport* getAirport(unsigned int index);
    /**
     * Returns a pointer to the given mapelement.
     */
    SinglePoint* getSinglePoint(int listIndex, unsigned int index);
    /** Zeichnet die angegebene Liste in den �bergebenen Painter */
    void drawList(QPainter* targetPainter, QPainter* maskPainter,
        unsigned int listID);
    /** Zeichnet die H�henlinien */
    void drawIsoList(QPainter* targetPainter, QPainter* maskPainter);
    /** */
    void printList(QPainter*, unsigned int listID);
    /**
     * Loads a new flight-file.
     */
    bool loadFlight(QFile);
    /** */
//    QStrList getFlightData();
    /** */
    Flight* getFlight();
    /**
      * Returns the flightList
      */
    QList<Flight>* getFlightList();
    /**
     *
     */
    int searchFlightPoint(QPoint cPos, struct flightPoint* fP);
    /** */
    void readConfig();
    /**
     * The listid.
     */
    enum listID {NotSet = 0, IntAirportList, AirportList, GliderList,
        AddSitesList, OutList, NavList, AirspaceList, ObstacleList, ReportList,
        CityList, VillageList, LandmarkList, HighwayList, HighwayEntryList,
        RoadList, RailList, StationList, HydroList, TopoList, IsohypseList,
        WaypointList, DigitList, FlightList};

    static int degreeToNum(const char* degree);

  private:
    /**
     * Converts the longitute or latitute into the internal format
     * suitable for the Location-class. "degree" is a string in the
     * format: [g]gg.mm'ss"X where g,m,s are any digits from 0 to 9
     * and X is one of N, S, E, W.
     */
    int __degreeToNum(const char* degree);
    /** reads a new binary-map-file */
    bool __readBinaryFile(const char* fileName);
    /** */
    bool __readAsciiFile(const char* fileName);
    /** */
    void __setPainterColor(QPainter* targetPainter, int height);
    /**
     * airportList contains all airports.
     */
    QList<Airport> airportList;
    /**
     * gliderList contains all glider-sites.
     */
    QList<GliderSite> gliderList;
    /**
     * addSitesList contains all, ultra-light,
     * hang-glider-sites, free-ballon-sites, parachute-jumping-sites.
     */
    QList<SinglePoint> addSitesList;
    /**
     * outList contains all outlanding-fields.
     */
    QList<ElevPoint> outList;
    /**
     * navList contains all radio navigation facilities.
     */
    QList<RadioPoint> navList;
    /**
     * airspaceList contails all airspaces.
     */
    QList<Airspace> airspaceList;
    /**
     * obstacleList contains all obstacles and -groups, as well
     * as the spots and passes.
     */
    QList<ElevPoint> obstacleList;
    /**
     * reportList contains all reporting points.
     */
    QList<SinglePoint> reportList;
    /**
     * cityList contails all cities.
     */
    QList<LineElement> cityList;
    /**
     * villageList contains all villages.
     */
//    QList<SinglePoint> villageList;
    /**
     * landmarkList contains all landmarks.
     */
    QList<SinglePoint> landmarkList;
    /**
     * highwayList contains all highways.
     */
    QList<LineElement> highwayList;
    /**
     * highEntryList contains all highwayentries.
     */
    QList<SinglePoint> highEntryList;
    /**
     * roadList contails all roads.
     */
    QList<LineElement> roadList;
    /**
     * railList contains all railways and aerial railways.
     */
    QList<LineElement> railList;
    /**
     * stationList contains all stations.
     */
    QList<SinglePoint> stationList;
    /**
     * hydroList contains all shorelines, rivers, lakes, ...
     */
    QList<LineElement> hydroList;
    /**
     * topoList contains all topographical objects.
     */
    QList<LineElement> topoList;
    /**
     * isohypseList contains all isohypses.
     */
    QList< QList<Isohypse> > isoList;
    /** */
    QList<Flight> flightList;
    /**
     * waypointList contains the listID of the waypoint.
     */
    unsigned int* waypointList;
    /**
     * waypointIndex contains the index of the waypoin.
     */
    unsigned int* waypointIndex;
    /**
     * Contains the number of waypoints.
     */
    unsigned int waypointNumber;
    /**
     * Enth�lt den Status der Karten-Kacheln. Die Kacheln werden durchgez�hlt.
     */
    QBitArray sectionArray;
    /** */
    int* isoLines;

    /** nur tempor�r ... */
    bool isFirst;
};

#endif
