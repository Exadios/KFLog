/***********************************************************************
**
**   airport.h
**
**   This file is part of KFLog.
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

#ifndef AIRPORT_H
#define AIRPORT_H

#include <radiopoint.h>
#include <runway.h>

/**
  * This class is used for handling airports. The object can be one of
  * Airport, MilAirport, CivMilAirport, Airfield, ClosedAirfield,
  * CivHeliport, MilHeliport, AmbHeliport.
  * @author Heiner Lamprecht, Florian Ehinger
  * @version $Id$
  * @see BaseMapElement#objectType
  */
class Airport : public RadioPoint
{
  public:
    /**
     * Creates a new Airport-object.
     * @param  name  The name
     * @param  alias  The alias
     * @param  abbr  The abbreviation, used for the gps-logger
     * @param  typeID  The typeid
     * @param  pos  The position
     * @param  elevation  The elevation
     * @param  frequency  The frequency
     * @param  vdf  "true",
     * @param  wP  "true", if the element is a waypoint
     */
    Airport(QString name, QString alias, QString abbr, unsigned int typeID,
        QPoint pos, unsigned int elevation, const char* frequency,
        bool vdf, bool wP);
    /**
     * Destructor
     */
    ~Airport();
    /**
     * @return the frequency of the airport.
     */
    QString getFrequency() const;
    /**
     * @return a runway-struct, containing the data of the given runway.
     */
    struct runway getRunway(int index = 0) const;
    /**
     * @return the number of runways.
     */
    unsigned int getRunwayNumber() const;
    /**
     * Prints the element. Reimplemented from BaseMapElement.
     * @param  printP  The painter to draw the element into.
     */
    virtual void printMapElement(QPainter* printP) const;
    /**
     * @return the elevation of the airport
     */
    unsigned int getElevation() const;
    /**
     * Return a short html-info-string about the airport, containg the
     * name, the alias, the elevation and the frequency as well as a small
     * icon of the airporttype.
     *
     * Reimplemented from SinglePoint (@ref SinglePoint#getInfoString).
     * @return the infostring
     */
    virtual QString getInfoString() const;
    /**
     * Used to define the surface of a runway.
     */
    enum Surface {NotSet, Grass, Asphalt, Concrete};

  private:
    /**
     * The elevation of the airport.
     */
    unsigned int elevation;
    /**
     */
    bool vdf;
    /**
     * Contains the runway-data.
     */
    struct runway* rwData;
    /**
     * Contains the number of runways.
     */
    unsigned int rwNum;
};

#endif
