/***********************************************************************
**
**   mapconfig.h
**
**   This file is part of KFLog2.
**
************************************************************************
**
**   Copyright (c):  2001 by Heiner Lamprecht
**
**   This file is distributed under the terms of the General Public
**   Licence. See the file COPYING for more information.
**
**   $Id$
**
***********************************************************************/

#ifndef MAPCONFIG_H
#define MAPCONFIG_H

#include <qbrush.h>
#include <qlist.h>
#include <qobject.h>
#include <qpen.h>
#include <qpixmap.h>

/**
 * This class takes care of the configuration-data for displaying
 * and printing map-elements. To avoid problems, there should be only
 * one element per application.
 *
 * @author Heiner Lamprecht, Florian Ehinger
 * @version $Id$
 */
class MapConfig : public QObject
{
  Q_OBJECT

  public:
    /**
     * Creates a new MapConfig object.
     */
    MapConfig();
    /**
     * Destructor
     */
    ~MapConfig();
    /**
     * @param  type  The typeID of the element.
     *
     * @return "true", if the current scale is smaller than the switch-scale,
     *         so that small icons should be used for displaying.
     */
    bool isBorder(unsigned int type);
    /**
     * @param  type  The typeID of the element.
     *
     * @return "true", if the current scale is smaller than the switch-scale,
     *          so that small icons should be used for printing.
     */
    bool isPrintBorder(unsigned int type);
    /**
     * @param  type  The typeID of the element.
     *
     * @return the pen for drawing a mapelement.
     */
    QPen getDrawPen(unsigned int typeID);
    /**
     * @param  fP  The flightpoint, which is used to determine the color
     *             of the line.
     *
     * @return the pen for drawing a line between two flightpoints of a flight.
     */
    QPen getDrawPen(struct flightPoint* fP);
    /**
     * @param  type  The typeID of the element.
     *
     * @return the pen for printing a mapelement.
     */
    QPen getPrintPen(unsigned int typeID);
    /**
     * @param  type  The typeID of the element.
     *
     * @return the brush for drawing an areaelement.
     */
    QBrush getDrawBrush(unsigned int typeID);
    /**
     * @param  type  The typeID of the element.
     *
     * @return the brush for printing an areaelement.
     */
    QBrush getPrintBrush(unsigned int typeID);
    /**
     * @param  heighIndex  The index of the height of the isohypse.
     *
     * @return the color for a isohypse.
     */
    QColor getIsoColor(unsigned int heightIndex);
    /**
     * @param  type  The typeID of the element.
     * @param  isWinch  Used only for glidersites to determine, if the
     *                  icon should indicate that only winch-launch is
     *                  available.
     *
     * @returns the icon-pixmap of the element.
     */
    QPixmap getPixmap(unsigned int typeID, bool isWinch = true);
    /**
     * @param  type  The typeID of the element.
     * @param  isWinch  Used only for glidersites to determine, if the
     *                  icon should indicate that only winch-launch is
     *                  available.
     *
     * @return the name of the pixmap of the element.
     */
    QString getPixmapName(unsigned int type, bool isWinch = true);
    /**
     * The possible datatypes, that could be drawn.
     *
     * @see #slotSetFlightDataType
     */
    enum DrawFlightPoint {Vario, Speed, Altitude, Cycling, Quality};

  public slots:
    /**
     * Forces MapConfig to read the configdata.
     */
    void slotReadConfig();
    /**
     * Sets the datatype to be used for drawing flights.
     *
     * @param  type  The datattype
     * @see #DrawFlightPoint
     */
    void slotSetFlightDataType(int type);
    /**
     * Sets the scaleindex an the flag for small icons. Called from
     * MapMatrix.
     *
     * @see MapMatrix#scaleAdd
     *
     * @param  index  The scaleindex
     * @param  isSwitch  "true" if the current scale is smaller than the
     *                   switch-scale
     */
    void slotSetMatrixValues(int index, bool isSwitch);
    /**
     * Sets the printScaleIndex.
     */
    void slotSetPrintMatrixValues(int index);

  signals:
    /**
     * Emitted each time, the config has changed.
     */
    void configChanged();
    /**
     * Emitted each time the user has selected a new data-type for
     * drawing the flights.
     */
    void flightDataChanged();

  private:
    /**
     * Determines the brush to be used to draw or print a given element-type.
     *
     * @param  typeID  The typeID of the element.
     * @param  scaleIndex  The scaleindex to be used.
     *
     * @return the brush
     */
    QBrush __getBrush(unsigned int typeID, int scaleIndex);
    /**
     * Determines the pen to be used to draw or print a given element-type.
     *
     * @param  typeID  The typeID of the element.
     * @param  scaleIndex  The scaleindex to be used.
     *
     * @return the pen
     */
    QPen __getPen(unsigned int typeID, int sIndex);

    QList<QColor> topographyColorList;

    QList<QPen> airAPenList;
    QList<QBrush> airABrushList;
    QList<QPen> airBPenList;
    QList<QBrush> airBBrushList;
    QList<QPen> airCPenList;
    QList<QBrush> airCBrushList;
    QList<QPen> airDPenList;
    QList<QBrush> airDBrushList;
    QList<QPen> airElPenList;
    QList<QBrush> airElBrushList;
    QList<QPen> airEhPenList;
    QList<QBrush> airEhBrushList;
    QList<QPen> airFPenList;
    QList<QBrush> airFBrushList;
    QList<QPen> ctrCPenList;
    QList<QBrush> ctrCBrushList;
    QList<QPen> ctrDPenList;
    QList<QBrush> ctrDBrushList;
    QList<QPen> lowFPenList;
    QList<QBrush> lowFBrushList;
    QList<QPen> dangerPenList;
    QList<QBrush> dangerBrushList;
    QList<QPen> restrPenList;
    QList<QBrush> restrBrushList;
    QList<QPen> tmzPenList;
    QList<QBrush> tmzBrushList;

    QList<QPen> roadPenList;
    QList<QPen> railPenList;
    QList<QPen> riverPenList;
    QList<QPen> highwayPenList;
    QList<QPen> cityPenList;
    QList<QBrush> cityBrushList;
    /**
     */
    bool* airABorder;
    bool* airBBorder;
    bool* airCBorder;
    bool* airDBorder;
    bool* airElBorder;
    bool* airEhBorder;
    bool* airFBorder;
    bool* ctrCBorder;
    bool* ctrDBorder;
    bool* dangerBorder;
    bool* lowFBorder;
    bool* restrBorder;
    bool* tmzBorder;

    bool* roadBorder;
    bool* highwayBorder;
    bool* railBorder;
    bool* riverBorder;
    bool* cityBorder;
    /**
     * The current scaleindex for displaying the map. The index is set
     * from the mapmatrix-object each time, the map is zoomed.
     *
     * @see #slotSetMatrixValues
     * @see MapMatrix#displayMatrixValues
     */
    int scaleIndex;
    /**
     * The current scaleindex for printing the map. The index is set
     * from the mapmatrix-object after initializing the print-matrix
     *
     * @see #slotSetPrintMatrix
     * @see MapMatrix#printMatrixValues
     */
    int printScaleIndex;
    /**
     * true, if small icons should be drawn. Set from the mapmatrix-object
     * each time, the map is zoomed.
     */
    bool isSwitch;
    /**
     * The datatype to be used for drawing flights.
     *
     * @see #slotSetFlightDataType
     */
    int drawFType;
};

#endif