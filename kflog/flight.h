/***********************************************************************
**
**   flight.h
**
**   This file is part of KFLog2.
**
************************************************************************
**
**   Copyright (c):  2001 Heiner Lamprecht, Florian Ehinger
**
**   This file is distributed under the terms of the General Public
**   Licence. See the file COPYING for more information.
**
**   $Id$
**
***********************************************************************/

#ifndef FLIGHT_H
#define FLIGHT_H

#include <basemapelement.h>
#include <flighttask.h>
#include <wp.h>

#include <qlist.h>
#include <qstring.h>
#include <qstrlist.h>

/**
 * Contains the logged flight-data.
 *
 * @author Heiner Lamprecht, Florian Ehinger, Jan Max Walter Krueger
 * @version $Id$
 */
class Flight : public BaseMapElement
{
  public:
	  /**
	   * Creates a new flight-object.
	   * @param  fileName  The name of the igc-file
	   * @param  route  The logged flight-points
	   * @param  pName  The name of the pilot
	   * @param  gType  The type of the glider
	   * @param  gIG  The id of the glider
	   * @param  wpL  The list of waypoints of the task
	   * @param  date  The date of the flight
	   */
    Flight(QString fileName, QString recID,
  	    QList<flightPoint> route, QString pName, QString gType,
        QString gID, QList<wayPoint> wpL, QString date);
	  /**
	   * Destroys the flight-object.
	   */
  	~Flight();
	  /**
	   * @return the name of the pilot.
	   */
  	QString getPilot() const;
	  /**
	   * @return the type of the glider.
	   */
  	QString getType() const;
	  /**
	   * @return the id of the glider.
	   */
  	QString getID() const;
	  /**
	   * @param  isOrig  "true", if the original-task should be returned.
	   *                 The default is "false". If the flight has not been
	   *                 optimized, the original-task will be returned in any
	   *                 case.
	   * @return the route-type of the flight
	   */
  	QString getRouteType(bool isOrig = false) const;
	  /**
	   * @param  isOrig  "true", if the original-task should be used.
	   *                 The default is "false". If the flight has not been
	   *                 optimized, the original-task will be used in any case.
	   * @return the distance between all reached waypoints
	   */
    QString getDistance(bool isOrig = false) const;
	  /**
	   * @param  isOrig  "true", if the original-task should be used.
	   *                 The default is "false". If the flight has not been
	   *                 optimized, the original-task will be used in any case.
	   * @return the distance of the task
	   */
    QString getTaskDistance(bool isOrig = false) const;
    /**
	   * @param  isOrig  "true", if the original-task should be used.
	   *                 The default is "false". If the flight has not been
	   *                 optimized, the original-task will be used in any case.
	   * @return the dmst-points of the flight.
     */
    QString getPoints(bool isOrig = false) const;
	  /**
	   * @return the starttime.
	   */
  	int getStartTime() const;
	  /**
	   * @return the start-site.
	   */
    QString getStartSite() const;
    /**
     * @return the landing time.
     */
    int getLandTime() const;
    /**
     * @return the number of logged points.
     */
    unsigned int getRouteLength() const;
    /**
     * @return the site, where the glider has landed.
     */
    QString getLandSite() const;
    /**
     * Creates a stringlist, that contains several info about the part
     * between the two given points.
     * @return the info-string
     * @param  start  the index of the first point of the section. If the
     *                index is 0, the first point of the flight will be
     *                used.
     * @param  end  the index of the last point of the section. If the index
     *              is 0, the last point of the flight will be used.
     */
    QStrList getFlightValues(unsigned int start = 0, unsigned int end = 0);
    /**
     * @return the date of the flight.
     */
    QString getDate() const;
    /**
     * Searches the point of the flight, which time is the nearest
     * to the given time.
     * @return the point
     */
    flightPoint getPointByTime(int time);
    /**
     * Searches the point of the flight, which time is the nearest
     * to the given time.
     * @return the index of the point
     */
    int getPointIndexByTime(int time);
    /**
     * Draws the flight an the task into the given painter. Reimplemented
     * from BaseMapElement.
     * @param  targetP  The painter to draw the element into.
     * @param  maskP  The maskpainter for targetP
     */
    virtual void drawMapElement(QPainter* targetP, QPainter* maskP);
    /** */
    virtual void printMapElement(QPainter* targetP, bool isText);
    /**
     * @return the point with the index "n"
     */
    flightPoint getPoint(int n);
    /**
	   * @param  isOrig  "true", if the original-task should be used.
	   *                 The default is "false". If the flight has not been
	   *                 optimized, the original-task will be used in any case.
	   * @return the list of waypoints
     */
    QList<wayPoint> getWPList(bool isOrig = false);
    /**
     * @return the filename of the igc-file
     */
    const char* getFileName() const;
    /**
     * @return the type of the task
     */
    unsigned int getTaskType() const;
    /**
     * Optimizes the task.
     * @return  "true", if the user wants to use the optimized task.
     */
    bool optimizeTask();
    /**
     * Searches the first point of the flight, which distance to the
     * mousecursor is less than 30 pixel. If no point is found, -1 is
     * returned.
     * @param  cPoint  The map-position of the mousecursor.
     * @param  searchPoint  A pointer to a flightpoint. Will be filled
     *                      with the flightpoint found.
     * @return the index of the flightpoint or -1 if no point is found.
     */
    int searchPoint(QPoint cPoint, flightPoint& searchPoint);
    /**
		 * Get the previous FlightPoint before number 'index'
		 */
    int searchGetPrevPoint(int index, flightPoint& searchPoint);
    /**
		 * Get the next FlightPoint after number 'index'
		 */
    int searchGetNextPoint(int index, flightPoint& searchPoint);
    /**
     * @return "true" if the flight has been optimized.
     */
    bool isOptimized() const;
    /**
     * @return the bounding-box of the flight.
     */
    QRect getFlightRect() const;
    /**
     * @return the bounding-box of the task.
     */
    QRect getTaskRect() const;
    /**
     * @return the header-info of the igc-file (date, pilot-name, ...)
     */
    QStrList getHeader();
    /**
     * The waypoint-types.
     */
    enum WaypointType {NotSet = 0, TakeOff = 1, Begin = 2, RouteP = 4,
                     End = 8, FreeP = 16, Landing = 32};
    /**
     * The flight-types.
     */
    enum FlightType {ZielS = 1, ZielR = 2, FAI = 3, Dreieck = 4, FAI_S = 5,
                   Dreieck_S = 6, Abgebrochen = 7, Unknown = 8, FAI_2 = 9,
                   FAI_S2 = 10, FAI_3 = 11, FAI_S3 = 12, Vieleck = 13};
    /**
     * Return values for the Min/Max Points
     */
    enum MaxPoints {V_MAX = -1, H_MAX = -2, VA_MAX=-3, VA_MIN = -4};
    /**
     *  Flight State
     */
    enum FlightState {Straight = 0, LeftTurn = 1, RightTurn = 2, MixedTurn = 3};

  private:
    /** */
    unsigned int __calculateBestTask(unsigned int start[], unsigned int stop[],
        unsigned int step, unsigned int idList[],
        double taskValue[], bool isTotal);
    /** */
    void __moveOptimizePoint(unsigned int idList[], double taskValue[],
        unsigned int id);
    /** */
    void __setOptimizeRange(unsigned int start[], unsigned int stop[],
        unsigned int idList[], unsigned int id, unsigned int step);
    /** */
    double __calculateOptimizePoints(flightPoint* fp1,
        flightPoint* fp2, flightPoint* fp3);
	  /** */
  	void __checkMaxMin();
  	/** */
  	virtual bool __isVisible() const;
  	/** Kreisflug?? */
  	void __flightState();

    QString recorderID;
	  QString pilotName;
    QString gliderType;
    QString gliderID;
    QString date;
    QString sourceFileName;
    flightPoint* drawRoute;
    unsigned int drawLength;
    unsigned int v_max;
    unsigned int h_max;
    unsigned int va_min;
    unsigned int va_max;

    QList<flightPoint> route;

    QRect bBoxFlight;
    int landTime;
    int startTime;

    FlightTask origTask;
    FlightTask optimizedTask;

    bool optimized;
};

#endif
