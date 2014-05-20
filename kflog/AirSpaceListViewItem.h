/***********************************************************************
**
**   AirSpaceListViewItem.h
**
**   This file is part of KFLog4.
**
************************************************************************
**
**   Copyright (c):  2003 by André Somers
**                   2011 by Axel Pauli
**
**   This file is distributed under the terms of the General Public
**   License. See the file COPYING for more information.
**
**   $Id: AirSpaceListViewItem.h 1101 2011-02-16 22:22:12Z axel $
**
***********************************************************************/
/**
  * \class AirSpaceListViewItem
  *
  * \author Matthias Degenkolb, Axel Pauli
  *
  * \brief List view item that contains an airspace intersection.
  *
  * This class represents a task in the object tree. It manages it's own
  * children, all you need to do is invoke it with the
  * @ref AirSpaceListViewItem(QTreeWidgetItem* parent, Flight* flight) constructor.
  *
  * \date 2003-2011
  *
  * \version $Id
  */

#ifndef AIRSPACE_LIST_VIEW_ITEM_H
#define AIRSPACE_LIST_VIEW_ITEM_H

#include <QTreeWidgetItem>
#include "flight.h"

#define AIRSPACE_LIST_VIEW_ITEM_TYPEID 10008
#define AIRSPACE_FLAG_LIST_VIEW_ITEM_TYPEID 10009

class FlightTask;

class AirSpaceListViewItem : public QTreeWidgetItem
{
 public:
    class AirSpaceFlagListViewItem : public QTreeWidgetItem
    {
     public:
      /**
       * Constructor.
       * @param parent Reference to parent @ref QTreeWidgetItem
       * @param task Reference to @ref FlightTask object to display
       */
      AirSpaceFlagListViewItem( QTreeWidgetItem* parent, const QStringList & Strings , Flight::AirSpaceIntersection theFlightIntersection, Flight * theFlight);
      void Activate();
      inline Flight* getFlight() { return m_Flight; }
    private:
      /**
       * Contains reference to the @ref FlightTask this @ref QTreeWidgetItem is representing
       */
      Flight::AirSpaceIntersection m_ItemToActivate;
      Flight * m_Flight;
    };
  /**
   * Constructor.
   * @param parent Reference to parent @ref QTreeWidgetItem
   * @param task Reference to @ref FlightTask object to display
   */
  AirSpaceListViewItem( QTreeWidgetItem* parent, Flight* theFlight);
  /**
   * Destructor
   */
  virtual ~AirSpaceListViewItem();
  /**
   * Contains reference to the @ref FlightTask this @ref QTreeWidgetItem is representing
   */
  Flight *m_Flight;

  /**
   * Called to make the item update itself.
   */
  void update();

protected:
  /**
   * Creates the child nodes for this flight node.
   */
  void createChildren();
};



#endif
