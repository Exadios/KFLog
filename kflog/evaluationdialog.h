/***********************************************************************
**
**   evaluationdialog.h
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

#ifndef EVALUATIONDIALOG_H
#define EVALUATIONDIALOG_H

#include <qdialog.h>
#include <qlist.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <qspinbox.h>
#include <qscrollview.h>
#include <qlabel.h>
#include <qtextview.h>

#include "wp.h"

class EvaluationView;
class Flight;

/**
 * @author Heiner Lamprecht, Florian Ehinger
 * @version $Id$
 */
class EvaluationDialog : public QDialog
{
  Q_OBJECT

 public:
  /** */
  EvaluationDialog(QList<Flight>* fList);
  /** */
  ~EvaluationDialog();
  /**
   * Called, whenever a flight is loaded or closed, so that the listbox
   * contains all loaded flight.
   */
  void updateListBox();

  /**
   *
   */
  void updateText(int index1, int index2, bool updateAll = false);

 signals:
  void showCursor(QPoint p1, QPoint p2);

 public slots:
  /** */
  void slotShowFlightData(int n);
  /** */
  void slotToggleView();
  /** */
  void slotVarioGlatt(int glatt);
  void slotBaroGlatt(int glatt);
  void slotSpeedGlatt(int glatt);

  void slotScale(int secWidth);

  void hide();

 protected:
  /**
   * Redefinition of the resizeEvent.
   */
  virtual void resizeEvent(QResizeEvent* event);

 private:
  /*
   * Was ist mit diesen labels ???
   */
  QScrollView* graphFrame;
  EvaluationView* evalView;
  QTextView* textLabel;
  QTextView* cursorLabel;

  QCheckBox* check_vario;
  QCheckBox* check_baro;
  QCheckBox* check_speed;
  QComboBox* combo_flight;

  QSpinBox* spinVario;
  QSpinBox* spinBaro;
  QSpinBox* spinSpeed;
  QSpinBox* spinScale;

  QList<Flight>* flightList;

  int glatt_va;
  int glatt_v;
  int glatt_h;

  int secWidth;

};

#endif
