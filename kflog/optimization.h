/***********************************************************************
**
**   optimization.h
**
**   This file is part of KFLog.
**
************************************************************************
**
**   Copyright (c):  2003 by Christof Bodner
**                   2011 by Axel pauli
**
**   This file is distributed under the terms of the General Public
**   License. See the file COPYING for more information.
**
**   $Id$
**
***********************************************************************/

#ifndef OPTIMIZATION_H
#define OPTIMIZATION_H

#include <QProgressBar>

#include "mapcalc.h"
#include "flightpoint.h"

/**
 * \class Optimization
 *
  * \brief This class optimizes a task according to the OLC 2003 rules
  *
  * \author Christof Bodner, Axel Pauli
  *
  * \date 2003-2011
  *
  * \version $Id$
  */

#define LEGS 6  // number of legs
  
class Optimization : public QObject
{
  Q_OBJECT

public:
 /**
  * Constructor for the route with the first resp. last point allowed
  * an optional progress bar can be specified, since optimizing can take
  * a long time.
  *
  * @param firstPoint Index of first point in the @ref route ?
  * @param lastPoint Index of last point in the @ref route ?
  * @param route List of flightpoints that together consitute the route this flight used.
  * @param progressBar optional reference to a progressbar to indicate optimisation progress.
  */
  Optimization( unsigned int firstPoint,
                unsigned int lastPoint,
                QList<FlightPoint*> route,
                QProgressBar *progressBar=0 );
 /**
  * Destructor
  */ 
  virtual ~Optimization();
 /**
  * @return the indices, the points awarded and the distance of the optimized task
  */
  double optimizationResult( unsigned int* pointList,double *points );

public slots:
 /**
  * Starts optimization of the given route
  */
  void run();
 /**
  * ?
  */
  void setTimes(unsigned int start_int, unsigned int stop_int);
 /**
  * Cancels optimization
  */ 
  void stopRun();
 /**
  * ?
  */ 
  void enableRun();

private:

  double weight(unsigned int k); // different weight for the legs

  QList<FlightPoint*> original_route;
  QList<FlightPoint*> route;
  double distance, points;
  unsigned int pointList[LEGS+1];   // solution points
  unsigned int start;    // first
  unsigned int stop;     // last valid point
  bool  optimized;
  bool  stopit;
  QProgressBar *progress;
};

#endif
