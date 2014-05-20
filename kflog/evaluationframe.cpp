/***********************************************************************
**
**   evaluationframe.cpp
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

#include "evaluationframe.h"
#include <evaluationdialog.h>

#include <klocale.h>
#include <qlayout.h>
#include <qsplitter.h>

EvaluationFrame::EvaluationFrame(QWidget* parent, EvaluationDialog* dlg)
  : QFrame(parent)
{

  // m�ssen noch gespeichert werden
  glatt_va = 0;
  glatt_v = 0;
  glatt_h = 0;
  secWidth = 10;


  // variable Kontrolle
  QSplitter* kontSplitter = new QSplitter(QSplitter::Horizontal, this);

  graphFrame = new QScrollView(kontSplitter);
  graphFrame->setResizePolicy(QScrollView::AutoOne);
  graphFrame->setHScrollBarMode(QScrollView::AlwaysOn);
  graphFrame->setVScrollBarMode(QScrollView::AlwaysOff);
  graphFrame->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  graphFrame->setBackgroundMode(PaletteLight);

  evalView = new EvaluationView(graphFrame, dlg);
  graphFrame->addChild(evalView);

  cursorLabel = new QTextView(this);
  cursorLabel->setFixedHeight(35);
  cursorLabel->setVScrollBarMode(QScrollView::AlwaysOff);
  cursorLabel->setHScrollBarMode(QScrollView::AlwaysOff);

  // Kontrollelemente
  QFrame* kontrolle = new QFrame(kontSplitter);
  kontrolle->setMinimumWidth(1);

  QLabel* scale_label = new QLabel(i18n("Zeitskalierung:"),kontrolle);
  scale_label->setAlignment(AlignHCenter);
  spinScale = new QSpinBox(1,60,1,kontrolle);
//  spinScale->setValue(secWidth);

  kontrolle->setMaximumWidth(scale_label->sizeHint().width() + 5);

  QLabel* label_glaettung = new QLabel(i18n("Gl�ttung:"),kontrolle);
  label_glaettung->setAlignment(AlignHCenter);

  sliderVario = new QSlider(0,10,1,0,QSlider::Vertical,kontrolle);
  sliderBaro  = new QSlider(0,10,1,0,QSlider::Vertical,kontrolle);
  sliderSpeed = new QSlider(0,10,1,0,QSlider::Vertical,kontrolle);
  sliderVario->sizeHint().setHeight(20);
  sliderBaro->sizeHint().setHeight(20);
  sliderSpeed->sizeHint().setHeight(20);

  check_vario = new QCheckBox(kontrolle);
  check_vario->setChecked(true);
  check_baro = new QCheckBox(kontrolle);
  check_baro->setChecked(true);
  check_speed = new QCheckBox(kontrolle);
  check_speed->setChecked(true);

  QLabel* label_vario = new QLabel(i18n("V"),kontrolle);
  QLabel* label_baro  = new QLabel(i18n("H"),kontrolle);
  QLabel* label_speed = new QLabel(i18n("S"),kontrolle);
  label_vario->setAlignment(AlignHCenter);
  label_baro->setAlignment(AlignHCenter);
  label_speed->setAlignment(AlignHCenter);

  QVBoxLayout* mittelayout = new QVBoxLayout(this);

  QGridLayout* kontrolllayout = new QGridLayout(kontrolle,12,6,5,1);

  mittelayout->addWidget(kontSplitter);
  mittelayout->addWidget(cursorLabel);

  kontrolllayout->addMultiCellWidget(scale_label,1,1,0,6);
  kontrolllayout->addMultiCellWidget(spinScale,3,3,2,5);
  kontrolllayout->addMultiCellWidget(label_glaettung,5,5,0,6);
  kontrolllayout->addWidget(sliderBaro,7,1);
  kontrolllayout->addWidget(sliderVario,7,3);
  kontrolllayout->addWidget(sliderSpeed,7,5);
  kontrolllayout->addWidget(check_baro,9,1);
  kontrolllayout->addWidget(check_vario,9,3);
  kontrolllayout->addWidget(check_speed,9,5);
  kontrolllayout->addWidget(label_baro,11,1);
  kontrolllayout->addWidget(label_vario,11,3);
  kontrolllayout->addWidget(label_speed,11,5);

  kontrolllayout->addColSpacing(1,sliderBaro->sizeHint().width() + 4);
  kontrolllayout->addColSpacing(3,sliderVario->sizeHint().width() + 4);
  kontrolllayout->addColSpacing(5,sliderSpeed->sizeHint().width() + 4);
  kontrolllayout->setColStretch(0,2);
  kontrolllayout->setColStretch(2,1);
  kontrolllayout->setColStretch(4,1);
  kontrolllayout->setColStretch(6,2);
  kontrolllayout->addRowSpacing(2,5);
  kontrolllayout->addRowSpacing(4,10);
  kontrolllayout->addRowSpacing(6,5);
  kontrolllayout->addRowSpacing(8,5);
  kontrolllayout->addRowSpacing(10,5);
  kontrolllayout->setRowStretch(12,3);

// Setzt die Anfangsgr��en des Splitters
  typedef QValueList<int> testList;
  testList kontList;
  kontList.append(300);
  kontList.append(scale_label->sizeHint().width() + 5);
  kontSplitter->setSizes(kontList);
  kontSplitter->setSizes(kontList);



  this->connect(check_vario, SIGNAL(clicked()),
        SLOT(slotShowGraph()));
  this->connect(check_baro, SIGNAL(clicked()),
        SLOT(slotShowGraph()));
  this->connect(check_speed, SIGNAL(clicked()),
        SLOT(slotShowGraph()));

  this->connect(sliderVario, SIGNAL(valueChanged(int)),
        SLOT(slotVarioGlatt(int)));
  this->connect(sliderSpeed, SIGNAL(valueChanged(int)),
        SLOT(slotSpeedGlatt(int)));
  this->connect(sliderBaro, SIGNAL(valueChanged(int)),
        SLOT(slotBaroGlatt(int)));

  this->connect(spinScale, SIGNAL(valueChanged(int)),
        SLOT(slotScale(int)));

}

EvaluationFrame::~EvaluationFrame()
{

}

void EvaluationFrame::slotShowFlight(Flight* arg_flight)
{
  flight = arg_flight;

  slotShowGraph();
}

void EvaluationFrame::slotShowGraph()
{
/*  this->setCaption(i18n("Flightevaluation:") + flightList->at(n)->getPilot()
                    + "  " + flightList->at(n)->getDate());
  // GRUNDWERTE setzen
  updateText(0,flightList->at(n)->getRouteLength() - 1, true);
*/


  warning("EvaluationFrame::slotShowGraph");

  // Kurve malen
  evalView->drawCurve(flight, check_vario->isChecked(),
                check_speed->isChecked(), check_baro->isChecked(),
                glatt_va, glatt_v, glatt_h, secWidth);
}


void EvaluationFrame::slotVarioGlatt(int g)
{
  // gibt den Gl�sttungsfaktor zur�ck
  glatt_va = g;

  slotShowGraph();
}

void EvaluationFrame::slotBaroGlatt(int g)
{
  // gibt den Gl�ttungsfaktor zur�ck
  glatt_h = g;

  slotShowGraph();
}

void EvaluationFrame::slotSpeedGlatt(int g)
{
  // gibt den Gl�ttungsfaktor zur�ck
  glatt_v = g;

  slotShowGraph();
}

void EvaluationFrame::slotScale(int g)
{
  // gibt den Scalierungsfaktor zur�ck
  secWidth = g;

  slotShowGraph();
}

void EvaluationFrame::slotUpdateCursorText(QString text)
{
  cursorLabel->setText(text);
}

void EvaluationFrame::resizeEvent(QResizeEvent* event)
{
  QFrame::resizeEvent(event);
  slotShowGraph();
}
