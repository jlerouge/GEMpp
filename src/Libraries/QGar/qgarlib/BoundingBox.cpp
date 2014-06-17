/*---------------------------------------------------------------------+
 | Library QgarLib, graphics analysis and recognition                  |
 | Copyright (C) 2002  Qgar Project, LORIA                             |
 |                                                                     |
 | This library is free software; you can redistribute it and/or       |
 | modify it under the terms of the GNU Lesser General Public          |
 | License version 2.1, as published by the Free Software Foundation.  |
 |                                                                     |
 | This library is distributed in the hope that it will be useful,     |
 | but WITHOUT ANY WARRANTY; without even the implied warranty of      |
 | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                |
 | See the GNU Lesser General Public License for more details.         |
 |                                                                     |
 | The GNU Lesser General Public License is included in the file       |
 | LICENSE.LGPL, in the root directory of the Qgar packaging. See      |
 | http://www.gnu.org/licenses/lgpl.html for the terms of the licence. |
 | To receive a paper copy, write to the Free Software Foundation,     |
 | Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.       |
 |                                                                     |
 | Contact Project Qgar for any information:                           |
 |   LORIA - équipe Qgar                                               |
 |   B.P. 239, 54506 Vandoeuvre-lès-Nancy Cedex, France                |
 |   email: qgar-contact@loria.fr                                      |
 |   http://www.qgar.org/                                              |
 *---------------------------------------------------------------------*/


/**
 * @file   BoundingBox.cpp
 * @brief  Implementation of class qgar::BoundingBox.
 *
 *         See file BoundingBox.h for the interface.
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   June 17, 2004  18:46
 * @since  Qgar 2.1.1
 */


// STD
#include <cstring>
#include <cmath>
#include <iostream>
// QGAR
#include "BoundingBox.h"
#include "primitives.h"
#include "QgarErrorDomain.h"



using namespace std;



namespace qgar
{

// -------------------------------------------------------------------
// C O N S T R U C T O R S 
// -------------------------------------------------------------------

  
// DEFAULT CONSTRUCTOR

BoundingBox::BoundingBox()

  : topLeft_    (0, 0),
    bottomRight_(0, 0)

{
  // VOID
}


// COPY CONSTRUCTOR

BoundingBox::BoundingBox(const BoundingBox& aBox)

  : topLeft_    (aBox.topLeft_),
    bottomRight_(aBox.bottomRight_)

{
  // VOID
}


// INITIALIZE FROM TWO POINTS

BoundingBox::BoundingBox(const IPoint& aPt1,
			 const IPoint& aPt2)
{
   setCorners(aPt1, aPt2);
}


// INITIALIZE FROM COORDINATES OF TWO POINTS

BoundingBox::BoundingBox(int aX1, int aY1, int aX2, int aY2)
{
  setCorners(aX1, aY1, aX2, aY2);
}


// INITIALIZE FROM TOP LEFT CORNER, LENGTH AND HEIGHT

BoundingBox::BoundingBox(const IPoint& aTopLeft,
			 int aLength,
			 int aHeight)

  : topLeft_(aTopLeft),
    bottomRight_(aTopLeft.x() + aLength - 1, 
		 aTopLeft.y() + aHeight - 1)

{
  // Ensure that width and height are greater than 0

  if (aLength <= 0) 
    {
      ostringstream os;
      os << "Bounding box length must be greater than 0: "
	 << aLength;
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "qgar::BoundingBox::BoundingBox(const qgar::GenPoint<int>&, int, int)",
			    os.str());
    }

  if (aHeight <= 0) 
    {
      ostringstream os;
      os << "Bounding box height must be greater than 0: "
	 << aHeight;
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "qgar::BoundingBox::BoundingBox(const qgar::GenPoint<int>&, int, int)",
			    os.str());
    }
}


// INITIALIZE FROM BOTTOM RIGHT CORNER, LENGTH AND HEIGHT

BoundingBox::BoundingBox(int aLength,
			 int aHeight,
			 const IPoint& aBottomRight) 


  : topLeft_(aBottomRight.x() - aLength + 1, 
	     aBottomRight.y() - aHeight + 1),
    bottomRight_(aBottomRight)

{
  // Ensure that width and height are greater than 1.
  // Throw exception otherwise.

  if (aLength <= 0) 
    {
      ostringstream os;
      os << "Bounding box length must be greater than 0: "
	 << aLength;
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "qgar::BoundingBox::BoundingBox(int, int, const qgar::GenPoint<int>&)",
			    os.str());
    }

  if (aHeight <= 0) 
    {
      ostringstream os;
      os << "Bounding box height must be greater than 0: "
	 << aHeight;
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "qgar::BoundingBox::BoundingBox(int, int, const qgar::GenPoint<int>&)",
			    os.str());
    }
}


// -------------------------------------------------------------------
// D E S T R U C T O R
// -------------------------------------------------------------------


BoundingBox::~BoundingBox()
{
  // VOID
}


// -------------------------------------------------------------------
// S E T   C O R N E R S
// -------------------------------------------------------------------


// SET TOP LEFT CORNER

void 
BoundingBox::setTopLeft(const IPoint& aPt)



{
  // Is the new point a valid top left corner?
  if ((aPt.x() > topLeft_.x()) || (aPt.y() > bottomRight_.y()))
    {
      ostringstream os;
      os << "New top left corner (" << aPt.x() << ',' << aPt.y()
	 << ") does not fit current box: top left("
	 << topLeft_.x() << ',' << topLeft_.y()
	 << "), bottom right("
	 << bottomRight_.x() << ',' << bottomRight_.y()
	 << ')';
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "void qgar::BoundingBox::setTopLeft(const qgar::GenPoint<int>&)",
			    os.str());
    }
  topLeft_ = aPt;
}


// SET (X AND Y OF) TOP LEFT CORNER

void
BoundingBox::setTopLeft(int aX, int aY)



{
  // Is the new point a valid top left corner?
  if ((aX > topLeft_.x()) || (aY > bottomRight_.y()))
    {
      ostringstream os;
      os << "New top left corner (" << aX << ',' << aY
	 << ") does not fit current box: top left("
	 << topLeft_.x() << ',' << topLeft_.y()
	 << "), bottom right("
	 << bottomRight_.x() << ',' << bottomRight_.y()
	 << ')';
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "void qgar::BoundingBox::setTopLeft(int, int)",
			    os.str());
    }

  topLeft_.setXY(aX, aY);
}


// SET X COORDINATE OF TOP LEFT CORNER

void
BoundingBox::setXTopLeft(int aX)



{
  // Is the new point a valid top left corner?
  if (aX > bottomRight_.x())
    {
      ostringstream os;
      os << "New top left corner (" << aX << ',' << topLeft_.y()
	 << ") does not fit current box: top left("
	 << topLeft_.x() << ',' << topLeft_.y()
	 << "), bottom right("
	 << bottomRight_.x() << ',' << bottomRight_.y()
	 << ')';
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "void qgar::BoundingBox::setXTopLeft(int)",
			    os.str());
    }

  topLeft_.setX(aX);
}


// SET Y COORDINATE OF TOP LEFT CORNER

void
BoundingBox::setYTopLeft(int aY)



{
  // Is the new point a valid top left corner?
  if (aY > bottomRight_.y())
    {
      ostringstream os;
      os << "New top left corner (" << topLeft_.x() << ',' << aY
	 << ") does not fit current box: top left("
	 << topLeft_.x() << ',' << topLeft_.y()
	 << "), bottom right("
	 << bottomRight_.x() << ',' << bottomRight_.y()
	 << ')';
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "void qgar::BoundingBox::setYTopLeft(int)",
			    os.str());
    }

  topLeft_.setY(aY);
}


// SET BOTTOM RIGHT CORNER

void 
BoundingBox::setBottomRight(const IPoint& aPt)



{
  // Is the new point a valid bottom right corner?
  if ((aPt.x() < topLeft_.x()) || (aPt.y() < bottomRight_.y()))
    {
      ostringstream os;
      os << "New bottom right corner (" << aPt.x() << ',' << aPt.y()
	 << ") does not fit current box: top left("
	 << topLeft_.x() << ',' << topLeft_.y()
	 << "), bottom right("
	 << bottomRight_.x() << ',' << bottomRight_.y()
	 << ')';
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "void qgar::BoundingBox::BottomRight(const qgar::GenPoint<int>&)",
			    os.str());
    }
  bottomRight_ = aPt;
}


// SET (X AND Y OF) BOTTOM RIGHT CORNER

void
BoundingBox::setBottomRight(int aX, int aY)



{
  // Is the new point a valid bottom right corner?
  if ((aX < topLeft_.x()) || (aY < bottomRight_.y()))
    {
      ostringstream os;
      os << "New bottom right corner (" << aX << ',' << aY
	 << ") does not fit current box: top left("
	 << topLeft_.x() << ',' << topLeft_.y()
	 << "), bottom right("
	 << bottomRight_.x() << ',' << bottomRight_.y()
	 << ')';
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "void qgar::BoundingBox::setBottomRight(int, int)",
			    os.str());
    }
  bottomRight_.setXY(aX, aY);
}


// SET X COORDINATE OF BOTTOM RIGHT CORNER

void
BoundingBox::setXBottomRight(int aX)



{
  // Is the new point a valid bottom right corner?
  if (aX < topLeft_.x())
    {
      ostringstream os;
      os << "New bottom right corner (" << aX << ',' << bottomRight_.y()
	 << ") does not fit current box: top left("
	 << topLeft_.x() << ',' << topLeft_.y()
	 << "), bottom right("
	 << bottomRight_.x() << ',' << bottomRight_.y()
	 << ')';
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "void qgar::BoundingBox::setXBottomRight(int)",
			    os.str());
    }

  bottomRight_.setX(aX);
}


// SET Y COORDINATE OF BOTTOM RIGHT CORNER

void
BoundingBox::setYBottomRight(int aY)



{
  // Is the new point a valid bottom right corner?
  if (aY < topLeft_.y())
    {
      ostringstream os;
      os << "New bottom right corner (" << bottomRight_.x() << ',' << aY
	 << ") does not fit current box: top left("
	 << topLeft_.x() << ',' << topLeft_.y()
	 << "), bottom right("
	 << bottomRight_.x() << ',' << bottomRight_.y()
	 << ')';
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "void qgar::BoundingBox::setYBottomRight(int)",
			    os.str());
    }

  bottomRight_.setY(aY);
}


// SET BOTH TOP LEFT AND BOTTOM RIGHT CORNERS, USING POINTS

void
BoundingBox::setCorners(const IPoint& aPt1, const IPoint& aPt2)
{
  setCorners(aPt1.x(), aPt1.y(), aPt2.x(), aPt2.y());
}


// SET BOTH TOP LEFT AND BOTTOM RIGHT CORNERS, USING COORDINATES

void
BoundingBox::setCorners(int aX1, int aY1, int aX2, int aY2)
{
  // WARNING: THE ORIGIN OF THE COORDINATE SYSTEM
  //          IS AT TOP LEFT OF THE (IMAGE) PLANE
  //   0
  //    +--------------------------------------> X
  //    |
  //    |  top left o--------------+
  //    |           |              |
  //    |           | Bounding Box |
  //    |           |              |
  //    |           +--------------o
  //    |                           bottom right
  //    V
  //
  //    Y

  topLeft_.setXY    ((aX1 > aX2) ? aX2 : aX1, (aY1 > aY2) ? aY2 : aY1);
  bottomRight_.setXY((aX1 > aX2) ? aX1 : aX2, (aY1 > aY2) ? aY1 : aY2);
}


// -------------------------------------------------------------------
// G E O M E T R I C A L   P R E D I C A T E S
// -------------------------------------------------------------------


// DOES THE POINT DEFINED BY THE GIVEN COORDINATES BELONG
// TO THE CURRENT BOUNDING BOX?

bool
BoundingBox::contains(int aX, int aY) const
{
  // WARNING: THE ORIGIN OF THE COORDINATE SYSTEM
  //          IS AT TOP LEFT OF THE (IMAGE) PLANE
  //   0
  //    +--------------------------------------> X
  //    |
  //    |  top left o--------------+
  //    |           |              |
  //    |           | Bounding Box |
  //    |           |              |
  //    |           +--------------o
  //    |                           bottom right
  //    V
  //
  //    Y

  return
       (aX >= topLeft_.x())
    && (aX <= bottomRight_.x())
    && (aY >= topLeft_.y())
    && (aY <= bottomRight_.y());
}


// DOES THE CURRENT BOUNDING BOX INTERSECT THE GIVEN BOUNDING BOX?

bool
BoundingBox::intersects(const BoundingBox& aBox) const
{
  //  0
  //   +-------------------------------> X
  //   |        |           | |               t: current box top left
  //   |        |    -------R |    T---      r: current box bottom right
  //   |        |             |    |
  //   |--------t-------------+--------      T: given box top left
  //   |        |/////////////|              R: given box bottom right
  //   |        |/current box/|
  //   |        |/////////////|
  //   |--------+-------------r--------
  //   |    |   |             |
  //   |  --R   |       T--   |
  //   |        |       |     |
  //   V
  //   Y
  //
  //  The given box does not intersect the current box iff:
  //
  //  X(R) < X(t)  or  Y(R) < Y(t)  or  X(T) > X(r)  or  Y(T) > Y(r)
  //
  //  => The given box intersects the current box iff:

  return
       (aBox.xBottomRight() >= topLeft_.x())       // X(R) >= X(t)
    && (aBox.yBottomRight() >= topLeft_.y())       // Y(R) >= Y(t)
    && (aBox.xTopLeft()     <= bottomRight_.x())   // X(T) <= X(r)
    && (aBox.yTopLeft()     <= bottomRight_.y());  // Y(T) <= Y(r)
}


// -------------------------------------------------------------------
// G E O M E T R I C A L   O P E R A T I O N S
// -------------------------------------------------------------------


// INTERSECTION BETWEEN THE CURRENT AND GIVEN BOUNDING BOXES

BoundingBox*
BoundingBox::intersection(const BoundingBox& aBox) const
{
  if (this->intersects(aBox))
    {
      // WARNING: THE ORIGIN OF THE COORDINATE SYSTEM
      //          IS AT TOP LEFT OF THE (IMAGE) PLANE
      //   0
      //    +--------------------------------------> X
      //    |
      //    |  top left o--------------+
      //    |           |              |
      //    |           | Bounding Box |
      //    |           |              |
      //    |           +--------------o
      //    |                           bottom right
      //    V
      //
      //    Y

      return
	new BoundingBox(max(topLeft_.x(), aBox.xTopLeft()),
			max(topLeft_.y(), aBox.yTopLeft()),
			min(bottomRight_.x(), aBox.xBottomRight()),
			min(bottomRight_.y(), aBox.yBottomRight()));
    }
  else
    {
      return (BoundingBox*)0;
    }
}


// -------------------------------------------------------------------
// O P E R A T O R S
// -------------------------------------------------------------------


// ASSIGNMENT

BoundingBox&
BoundingBox::operator=(const BoundingBox& aBox)
{
  // Are left hand side and right hand side different objects?
  if (this != &aBox)
    {
      topLeft_     = aBox.topLeft_;
      bottomRight_ = aBox.bottomRight_;
    }
  return *this;
}


// -------------------------------------------------------------------
// F U N C T I O N A L   O P E R A T O R S
// -------------------------------------------------------------------


// EQUALITY

bool
BoundingBox::eq(const BoundingBox& aBox) const
{
  return (topLeft_ == aBox.topLeft()) && (bottomRight_ == aBox.bottomRight());
}


// INEQUALITY

bool
BoundingBox::notEq(const BoundingBox& aBox) const
{
  return (topLeft_ != aBox.topLeft()) || (bottomRight_ != aBox.bottomRight());
}


// -------------------------------------------------------------------
// S E R I A L I Z A T I O N / D E S E R I A L I Z A T I O N
// -------------------------------------------------------------------


istream& 
BoundingBox::read(istream& anInStream)
{
  IPoint topL;
  IPoint bottomR;
  qgReadObjName(anInStream, "BoundingBox");
  qgReadObjData(anInStream, topL);
  qgReadObjData(anInStream, bottomR);

  setCorners(topL, bottomR);

  return anInStream;
}


ostream& 
BoundingBox::write(ostream& anOutStream) const
{
  anOutStream << "BoundingBox("
	      << topLeft_
	      << ")("
	      << bottomRight_
	      << ')';

  return anOutStream;
}


// -------------------------------------------------------------------


} // namespace qgar
