/***********************************************************************
**
**   isohypse.cpp
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

#include "isohypse.h"

#include <mapmatrix.h>

Isohypse::Isohypse(QPointArray pA, unsigned int elev, bool isV)
: LineElement(0, BaseMapElement::Isohypse, pA, isV),
  elevation(elev)
{

}

Isohypse::~Isohypse()
{

}

void Isohypse::drawMapElement(QPainter* targetP, QPainter* maskP)
{
  if(glMapMatrix->isVisible(bBox))
      targetP->drawPolygon(glMapMatrix->map(projPointArray));
}

int Isohypse::getElevation() const { return elevation; }
