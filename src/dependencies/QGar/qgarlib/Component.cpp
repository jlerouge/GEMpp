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
 * @file Component.cpp
 *
 * @brief Implementation of class qgar::Component.
 *
 * See file Component.h for the interface.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   March 17, 2004  17:17
 * @since  Qgar 2.1
 */


// STD
#include <cmath>
#include <limits>
#include <list>
// QGAR
#include "BoundingBox.h"
#include "Component.h"
#include "GenImage.h"
#include "image.h"
#include "Maer.h"
#include "math.h"
#include "primitives.h"
#include "QgarErrorDeveloper.h"



namespace qgar
{


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// S P E C I A L   L A B E L S   (STATIC)
// -------------------------------------------------------------------
// -------------------------------------------------------------------


// MAXIMUM LABEL

const Component::label_type
Component::LABEL_MAX_ = std::numeric_limits<Component::label_type>::max();


// NO LABEL

const Component::label_type Component::LABEL_NO_       = -1;

// STARTING MARK

const Component::label_type Component::LABEL_START_    = -2;

// CONTOUR MARK

const Component::label_type Component::LABEL_CONTOUR_  = -3;


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// CONTOUR FOLLOWING OF 4-CONNECTED COMPONENTS (STATIC)
// -------------------------------------------------------------------
// -------------------------------------------------------------------


// TABLE OF X COORDINATES INCREMENTS

const int
Component::s_4_incr_x_[13] =
{
  -1,    // <------ N entry
      0, // useless
   0,    // <------ E entry
      0, // useless
   1,    // <------ S entry
      0, // useless
   0,    // <------ W entry
      0, // useless
  -1,
      0, // useless
   0,
      0, // useless
   1
};


// TABLE OF Y COORDINATES INCREMENTS

const int
Component::s_4_incr_y_[13] =
{
   0,    // <------ N entry
      0, // useless
  -1,    // <------ E entry
      0, // useless
   0,    // <------ S entry
      0, // useless
   1,    // <------ W entry
      0, // useless
   0,
      0, // useless
  -1,
      0, // useless
   0
};


// TABLE OF NEW CONTOUR DIRECTIONS

const int
Component::s_4_new_dir_[13] =
{
  QGE_DIRECTION_W,
  0,                // useless
  QGE_DIRECTION_N,
  0,                // useless
  QGE_DIRECTION_E,
  0,                // useless
  QGE_DIRECTION_S,
  0,                // useless
  QGE_DIRECTION_W,
  0,                // useless
  QGE_DIRECTION_N,
  0,                // useless
  QGE_DIRECTION_E
};


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// CONTOUR FOLLOWING OF 8-CONNECTED COMPONENTS (STATIC)
// -------------------------------------------------------------------
// -------------------------------------------------------------------


// NUMBER OF PERTINENT NEIGHBORS IN A 3X3 NEIGHBORHOOD

const int
Component::s_8_ngh_cnt_ = 6;


// TABLE OF X COORDINATES INCREMENTS

const int
Component::s_8_incr_x_[48] =
{
  -1,  0, -1,  1,  1,  0, // N
   0, -1,  1,  1,  1, -1, // NE
   0,  1,  1,  0,  1, -1, // E
   1,  1,  0,  1, -1, -1, // SE
   1,  0,  1, -1, -1,  0, // S
   0,  1, -1, -1, -1,  1, // SW
   0, -1, -1,  0, -1,  1, // W
  -1, -1,  0, -1,  1,  1  // NW

};


// TABLE OF Y COORDINATES INCREMENTS

const int
Component::s_8_incr_y_[48] =
{
   0, -1, -1,  0, -1,  1, // N
  -1, -1,  0, -1,  1,  1, // NE
  -1,  0, -1,  1,  1,  0, // E
   0, -1,  1,  1,  1, -1, // SE
   0,  1,  1,  0,  1, -1, // S
   1,  1,  0,  1, -1, -1, // SW
   1,  0,  1, -1, -1,  0, // W
   0,  1, -1, -1, -1,  1  // NW
};


// TABLE OF NEW CONTOUR DIRECTIONS

const int
Component::s_8_new_dir_[48] =
{
  QGE_DIRECTION_W,  QGE_DIRECTION_N, QGE_DIRECTION_NW,  // N
  QGE_DIRECTION_E, QGE_DIRECTION_NE,  QGE_DIRECTION_S,  //

  QGE_DIRECTION_N, QGE_DIRECTION_NW,  QGE_DIRECTION_E,  // NE
  QGE_DIRECTION_NE, QGE_DIRECTION_SE, QGE_DIRECTION_SW, //

  QGE_DIRECTION_N,  QGE_DIRECTION_E, QGE_DIRECTION_NE,  // E
  QGE_DIRECTION_S, QGE_DIRECTION_SE,  QGE_DIRECTION_W,  //

  QGE_DIRECTION_E, QGE_DIRECTION_NE,  QGE_DIRECTION_S,  // SE
  QGE_DIRECTION_SE, QGE_DIRECTION_SW, QGE_DIRECTION_NW, //

  QGE_DIRECTION_E,  QGE_DIRECTION_S, QGE_DIRECTION_SE,  // S
  QGE_DIRECTION_W, QGE_DIRECTION_SW,  QGE_DIRECTION_N,  //

  QGE_DIRECTION_S, QGE_DIRECTION_SE,  QGE_DIRECTION_W,  // SW
  QGE_DIRECTION_SW, QGE_DIRECTION_NW, QGE_DIRECTION_NE, //

  QGE_DIRECTION_S,  QGE_DIRECTION_W, QGE_DIRECTION_SW,  // W
  QGE_DIRECTION_N, QGE_DIRECTION_NW,  QGE_DIRECTION_E,  //

  QGE_DIRECTION_W, QGE_DIRECTION_SW,  QGE_DIRECTION_N,  // N
  QGE_DIRECTION_NW, QGE_DIRECTION_NE, QGE_DIRECTION_SE  //
};


// TABLE OF PERIMETER INCREMENTS

const int 
Component::s_8_incr_perimeter_[48] =
{
  0, 1, 1, 2, 2, 3, // N
  1, 1, 2, 2, 3, 4, // NE
  0, 1, 1, 2, 2, 3, // E
  1, 1, 2, 2, 3, 4, // SE
  0, 1, 1, 2, 2, 3, // S
  1, 1, 2, 2, 3, 4, // SW
  0, 1, 1, 2, 2, 3, // W
  1, 1, 2, 2, 3, 4  // NW
};


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// C O N S T R U C T O R S
// -------------------------------------------------------------------
// -------------------------------------------------------------------


// ___________________________________________________________________
//
// WARNING: the default constructor belongs to the private section
// so that clients cannot use it

Component::Component()
{
  throw QgarErrorDeveloper(__FILE__, __LINE__,
			   "qgar::Component::Component()",
			   "Disabled constructor: should not be used!");
}
// ___________________________________________________________________



// CONSTRUCT FROM FULL DATA

Component::Component(GenImage<Component::label_type>* aPCompImg,
		     int   aLabel,
		     int   anInLabel,
		     QGEbw aBW,
		     int   aXTopLeftPix,
		     int   aYTopLeftPix,
		     int   aXTopLeft,
		     int   aYTopLeft,
		     int   aXBottomRight,
		     int   aYBottomRight,
		     int   anAreaPx,
		     int*  aPOffset4,
		     int*  aPOffset8)

  : pCompImg_        (aPCompImg),
    label_           (aLabel),
    inLabel_         (anInLabel),
    color_           (aBW),
    xTopLeftPix_     (aXTopLeftPix),
    yTopLeftPix_     (aYTopLeftPix),
    boundingBox_     (aXTopLeft, aYTopLeft, aXBottomRight, aYBottomRight),
    areaPx_          (anAreaPx),
    maer_            (0),
    contour_         (0),
    perimeterPx_     (0),
    offset3X3_4_     (aPOffset4),
    offset3X3_8_     (aPOffset8)

{
  // VOID
}


// COPY CONSTRUCTOR.

Component::Component(const Component& aCComp)

  : pCompImg_        (aCComp.pCompImg_),
    label_           (aCComp.label_),
    inLabel_         (aCComp.inLabel_),
    color_           (aCComp.color_),
    xTopLeftPix_     (aCComp.xTopLeftPix_),
    yTopLeftPix_     (aCComp.yTopLeftPix_),
    boundingBox_     (aCComp.boundingBox_),
    areaPx_          (aCComp.areaPx_),
    maerAreaPx_      (aCComp.maerAreaPx_),
    contour_         (aCComp.contour_),
    perimeterPx_     (aCComp.perimeterPx_),
    offset3X3_4_     (aCComp.offset3X3_4_),
    offset3X3_8_     (aCComp.offset3X3_8_)

{
  // Copy MAER if and only if it is computed
  if (maer_ != 0)
    {
      maer_ = new Maer(*(aCComp.maer_));
    }
}


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// D E S T R U C T O R
// -------------------------------------------------------------------
// -------------------------------------------------------------------


Component::~Component()
{
  delete maer_;
}


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// C O O R D I N A T E S
// -------------------------------------------------------------------
// -------------------------------------------------------------------


// GET BOUNDING BOX

const BoundingBox&
Component::accessBoundingBox() const
{
  return boundingBox_;
}


// GET A COPY OF THE BOUNDING BOX

BoundingBox
Component::boundingBox() const
{
  return boundingBox_;
}


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// A R E A
// -------------------------------------------------------------------
// -------------------------------------------------------------------


// GET DENSITY WITH REGARD TO THE BOUNDING BOX

double
Component::densityBox() const
{
  double a = boundingBox_.area();

  if (a < 1.)
    {
      // When the area is less than 1, it should mean that the component
      // is a degenerated one, with a null length and/or width
      return 1.;
    }
  else
    {
      return ((double) areaPx_) / a;
    }
}


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// M A E R   (MINIMUM-AREA ENCASING RECTANGLE)
// -------------------------------------------------------------------
// -------------------------------------------------------------------


// GET THE MAER

const Maer&
Component::accessMaer()
{
  if (maer_ == 0)
    {
      PRIVATEcomputeMaer();
    }

  return *maer_;
}


// GET A COPY OF THE MAER

Maer
Component::maer()
{
  if (maer_ == 0)
    {
      PRIVATEcomputeMaer();
    }

  return *maer_;
}


// GET MAER AREA

int
Component::maerAreaPx()
{
  if (maer_ == 0)
    {
      PRIVATEcomputeMaer();
    }

  return maerAreaPx_;
}


// GET DENSITY WITH REGARD TO THE MAER

double
Component::densityMaer()
{
  if (maer_ == 0)
    {
      PRIVATEcomputeMaer();
    }

  return ((double) areaPx_) / ((double) maerAreaPx_);
}


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// A C C E S S   T O   C O N T O U R S
// -------------------------------------------------------------------
// -------------------------------------------------------------------


// GET THE CONTOUR POINTS

const std::list<IPoint>& 
Component::accessContour()
{
  if (contour_.empty())
    {
      PRIVATEcomputeContour();
    }

  return contour_;
}


// GET A COPY OF THE CONTOUR POINTS

std::list<IPoint>
Component::contour()
{
  if (contour_.empty())
    {
      PRIVATEcomputeContour();
    }

  return contour_;
}


// GET THE PERIMETER

int
Component::perimeterPx()
{
  // Perimeter is initialized to -1 by the constructor
  if (perimeterPx_ < 0)
    {
      PRIVATEcomputeContour();
    }

  return perimeterPx_;
}


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// O P E R A T O R S
// -------------------------------------------------------------------
// -------------------------------------------------------------------


Component&
Component::operator=(const Component& aCComp)
{
  // Are left hand side and right hand side different objects?
  if (this != &aCComp)
    {
      pCompImg_     = aCComp.pCompImg_;
      label_        = aCComp.label_;
      inLabel_      = aCComp.inLabel_;
      color_        = aCComp.color_;
      xTopLeftPix_  = aCComp.xTopLeftPix_;
      yTopLeftPix_  = aCComp.yTopLeftPix_;
      boundingBox_  = aCComp.boundingBox_;
      areaPx_       = aCComp.areaPx_;
      offset3X3_4_  = aCComp.offset3X3_4_;
      offset3X3_8_  = aCComp.offset3X3_8_;

      // Copy MAER if it is computed
      if (maer_ != 0)
	{
	  maer_ = new Maer(*(aCComp.maer_));
	}
    }

  return *this;
}


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// COMPUTE CONTOUR POINTS (PRIVATE FUNCTIONS)
// -------------------------------------------------------------------
// -------------------------------------------------------------------


// GET CONTOUR POINTS

void
Component::PRIVATEcomputeContour()
{
  // *****************************************************************
  // COMPONENT IS A SINGLE POINT
  // *****************************************************************
  // Contour following does not work if the component is a single
  // point, as the starting point cannot be reached again when
  // searching for a new contour point around itself!

  if (areaPx_ == 1)
    {
      contour_.push_back(IPoint(boundingBox_.xTopLeft(),
				boundingBox_.yTopLeft()));
      perimeterPx_ = 4;

      return;
    }
  // *****************************************************************
  // END component is a single point
  // *****************************************************************
 

  // *****************************************************************
  // COMPONENT 0 (BACKGROUND) IS A PARTICULAR CASE
  // *****************************************************************
  // There is no surrounding component!
  //
  // Used 4-connectivity as this component is always WHITE

  if (label_ == 0)
    {
      // Coordinates of the top left and bottom right corners
      int xTopL = boundingBox_.xTopLeft();
      int yTopL = boundingBox_.yTopLeft();
      int xBotR = boundingBox_.xBottomRight();
      int yBotR = boundingBox_.yBottomRight();
      // Current contour coordinates
      int x = xTopL;
      int y = yTopL;
  
      // First contour point
      contour_.push_back(IPoint(x,y));
  
      // Upper contour
      for (++x ; x <= xBotR ; ++x)
	{
	  contour_.push_back(IPoint(x,y));
	}
  
      // Right contour
      for (--x, ++y ; y <= yBotR ; ++y)
	{
	  contour_.push_back(IPoint(x,y));
	}

      // Lower contour
      for (--x, --y ; x >= xTopL ; --x)
	{
	  contour_.push_back(IPoint(x,y));
	}

      // Left contour
      for (++x, --y ; y > yTopL ; --y)
	{
	  contour_.push_back(IPoint(x,y));
	}

      // The perimeter
      perimeterPx_ = (2 * (xBotR - xTopL)) + (2 * (yBotR - yTopL)) + 4;

      return;
    }
  // *****************************************************************
  // END component 0 (background)
  // *****************************************************************


  // *****************************************************************
  // THE COMPONENT IS NOT A SINGLE POINT AND IS NOT THE BACKGROUND
  // *****************************************************************

  if (color_ == QGE_BW_WHITE)
    {
      PRIVATEcontour4(); // Use 4-connectivity for white components
    }
  else
    {
      PRIVATEcontour8(); // Use 8-connectivity for black components
    }

  // *****************************************************************
  // END component is not a single point and is not the background
  // *****************************************************************

} // END function PRIVATEcomputeContour



// _________________________________________________________________
//
// CONTOUR FOLLOWING USING 4-CONNECTIVITY
// _________________________________________________________________
//
// (4.1) DIRECTION CODING
//   
//     N  NE  E  SE  S  SW  W  NW
//     0  1   2  3   4  5   6  7
//   
// Directions are coded clockwise, from north (N) to North-West (NW):
// see enum type QGEdirection in file image.h.
// 
// (4.2) SEARCHING FOR THE NEW CONTOUR POINT
//   
//      +---+---+---+
//      | * | n0| * |
//      +---+---+---+   contour
// (1)  --n6--c | n2|-> direction      SEARCH LIST: n0 - n2 - n4 - n6
//      +---+---+---+   (East)                RANK:  0    2    4    6
//      | * | n4| * |
//      +---+---+---+
// 
//      +---+-|-+---+
//      | * | n0| * |
//      +---+-|-+---+
// (2)  | n6| c | n2|                  SEARCH LIST: n2 - n4 - n6 - n0
//      +---+---+---+                         RANK:  0    2    4    6
//      | * | n4| * |
//      +---+---+---+
//            |
//            V
// contour direction (South)
//   
//   
// - currDir is the so-called "contour direction", that is to say
//   the direction of the contour part being constructed, whose c
//   is the current end.
// - The outside of the component is always on the left side when
//   moving along the contour direction.
// - The new contour point is searched clockwise among the 4 neighbors
//   of c, starting from the point left-perpendicular to currDir:
//   n0 and n2 on figures 1 and 2, respectively.
// - The elements of the search list are successively ranked
//   0 - 2 - 4 - 6 for more convenience, as shown in next sections.
//
// (4.3) COORDINATES OF NEIGHBORS
//   
//                  figure 1 --+     +-- figure 2
//                             |     |
//                             V     V
//             currDir   N     E     S     W
//                       0  1  2  3  4  5  6  7  8  9 10 11 12 
//                     +--+--+--+--+--+--+--+--+--+--+--+--+--+
//         s_4_incr_x_ |-1| *| 0| *| 1| *| 0| *|-1| *| 0| *| 1|
//                     +--+--+--+--+--+--+--+--+--+--+--+--+--+
//                     +--+--+--+--+--+--+--+--+--+--+--+--+--+
//         s_4_incr_y_ | 0| *|-1| *| 0| *| 1| *| 0| *|-1| *| 0|
//                     +--+--+--+--+--+--+--+--+--+--+--+--+--+
//                     +--+--+--+--+--+--+--+--+--+--+--+--+--+
//        offset3X3_4_ |-1| *|-w| *| 1| *| w| *|-1| *|-w| *| 1| w == image width
//                     +--+--+--+--+--+--+--+--+--+--+--+--+--+
// nghIdx for figure 1         0     2     4     6
// nghIdx for figure 2               0     2     4     6
//   
// - Contour direction currDir determines the index to enter
//   each table: 2 (East) and 4 (South) on figures 1 and 2, resp.
// - nghIdx is the relative index of the 4 consecutive
//   pertinent values (excepting those marked '*') available
//   from this entry.
// - In table s_4_incr_x_ (resp. s_4_incr_y_), these values provide
//   the X (resp. Y) increments to add to the X (resp. Y) coordinate
//   of c in order to get the X (resp. Y) coordinates of the 4 neighbors
//   of c in the appropriate order, as explained in previous section.
// - The new contour point is found at index
//   newIdx == currDir + nghIdx.
// - In the same way, table offset3X3_4_ provides the offsets to add
//   to the pointer to c in order to get the pointers to the 4 neighbors.
//   neighbors in the same way.
//
// [NOTE] In fact, odd-indexed values have no use and just exist
//        to preserve the correspondance between the current
//        direction code and the entry index.
// 
// (4.4) THE NEW CONTOUR DIRECTION
//   
//       entry for figure 1 --+     +-- entry for figure 2
//                            |     |
//                            V     V
//            currDir   N     E     S     W
//                      0  1  2  3  4  5  6  7  8  9 10 11 12 
//                    +--+--+--+--+--+--+--+--+--+--+--+--+--+
//        s_4_incr_x_ |-1| *| 0| *| 1| *| 0| *|-1| *| 0| *| 1|
//                    +--+--+--+--+--+--+--+--+--+--+--+--+--+
//                                        | newIdx
//                                        V
//                    +--+--+--+--+--+--+--+--+--+--+--+--+--+
//       s_4_new_dir_ | W| *| N| *| E| *| S| *| W| *| N| *| E|
//                    +--+--+--+--+--+--+--+--+--+--+--+--+--+
//
// Once the new contour point is found, its index newIdx
// determines the entry in table s_4_new_dir_  to get the new
// contour direction.
//
// [EXAMPLES] On figure 1, when the new contour point is n4:
// nghIdx == 4, newIdx == currDir + nghIdx == 2 + 4, and
// s_4_new_dir_[6] gives South as new direction.
// On figure 2, when the new contour point is n4:
// nghIdx == 2, newIdx == currDir + nghIdx == 4 + 2, and
// the new contour direction is South again.
//
// (4.5) THE PERIMETER
//
// nghIdx      0                 2                 4                 6
// increment  +0                +1                +2                +3
// 
//       +---+-|-+---+     +---+-|-+---+     +---+-|-+---+     +---X-|-+---+
//       | * | n0| * |     | * | n0| * |     | * | n0| * |     | * | n0| * |
//       +---+-|-+---X     +---+-|-+---+     +---+-|-+---+     +---+-|-+---+
//       | n6| c---n2|     | n6| c | n2|     | n6--c | n2|     | n6| c | n2|
//       +---+---O---+     +---+-|-O---+     X---+---O---+     +---+---O---+
//       | * | n4| * |     | * | n4| * |     | * | n4| * |     | * | n4| * |
//       +---+---+---+     +---+---X---+     +---+---+---+     +---+---+---+
//             |                 |                 |                 |      
//             V                 V                 V                 V      
//                            contour direction (South)
// 
//                         SEARCH LIST: n2 - n4 - n6 - n0
//                              nghIdx: 0    2    4    6
//
// - A pixel is supposed to be a unit-width-square.
// - The current so-called "perimeter in pixels" is the length between
//  the top left corner of the starting pixel and the top right
//  (relatively to the current contour direction)
//  corner of the current pixel.
//- Once the new contour point is found, the value to add to the current
//  perimeter is equal to nghIdx/2.
//
// [EXAMPLE] The figure above shows the case of figure 2, when the
// contour direction is South. 'O' represents the top right corner
// of the current contour pixel, and 'X' represents the top right
// corner of the new contour pixel.
// _________________________________________________________________


void
Component::PRIVATEcontour4()
{
  // Component image width
  int width = pCompImg_->width();
  
  // Pointer to the first contour point
  Component::label_type* pCurrPt =
    pCompImg_->pPixMap() + (yTopLeftPix_ * width) + xTopLeftPix_;
  // Mark this point as starting point
  *pCurrPt = LABEL_START_;

  // Save this point as contour point
  contour_.push_back(IPoint(xTopLeftPix_, yTopLeftPix_));
  // Save the pointer to the point
  std::list<Component::label_type*> pPtList;
  pPtList.push_back(pCurrPt);

  // In the beginning, there is only *1* contour point (c)
  //
  //       +---+---+---+
  //       | * | n0| * |
  //       +---+---+---+
  //       | n6| c | n2|    SEARCH LIST: n2 - n4 - n6 - n0
  //       +---+---+---+
  //       | * | n4| * |
  //       +---+---+---+
  //             |
  //             V South
  //
  // As c is the top left pixel, n0 and n6 cannot be contour points
  // and it is useless to examine them
  // => assume initial contour direction is South to examine n2 first

  int currDir = QGE_DIRECTION_S;
  
  // Coordinates of the current contour point
  int currX = xTopLeftPix_;
  int currY = yTopLeftPix_;

  // Initialize perimeter
  // WARNING: initial direction is supposed to be South
  //
  // O---+          S: starting pixel
  // | S |
  // +---X          length(OX) == 2
  //   |
  //   V South

  perimeterPx_ = 2;


  bool notContourCompleted = true;
  
  while (notContourCompleted)
    // WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
    // BLOCK-WHILE
    // while the whole contour is not followed
    // WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
    {
      
      for (int nghIdx = 0 ; nghIdx < 8 ; nghIdx += 2)
	//             ^^^          ^^^         ^^^^
	// For each direction around the current point
	// See section (4.3) in the function header
	{
	  // Index to enter the different tables used to construct
	  // the contour: see section (4.3) in the function header
	  int newIdx = currDir + nghIdx;
	  
	  // Pointer to the current possible contour point
	  // in the pixel map of the component image
	  // See section (4.3) in the function header
	  Component::label_type* pNewPt = pCurrPt + offset3X3_4_[newIdx];
	  
	  // Label of the current possible contour point
	  Component::label_type currLabel = *pNewPt;

	  if (currLabel == label_)
	    {
	      // -------------------------------------------------
	      // THE NEW POINT IS LABELLED LIKE THE COMPONENT
	      // => new contour point
	      // -------------------------------------------------
	      // Update:
	      // - pointer to the current contour point
	      // - current contour direction
	      // - coordinates of the current contour point
	      // - perimeter: see section (4.5) in function header
	      pCurrPt       = pNewPt;
	      currDir       = s_4_new_dir_[newIdx];
	      currX        += s_4_incr_x_[newIdx];
	      currY        += s_4_incr_y_[newIdx];
	      perimeterPx_ += nghIdx / 2;

	      // Save new contour point and new pointer to it
	      contour_.push_back(IPoint(currX,currY));
	      pPtList.push_back(pCurrPt);

	      // Mark new point as contour point in component image
	      *pCurrPt = LABEL_CONTOUR_;

	      // Leave loop for
	      break;
	      // -------------------------------------------------
	      // END new point is labelled like the component
	      // -------------------------------------------------
	    }

	  if (currLabel == LABEL_START_)
	    {
	      // -------------------------------------------------
	      // STARTING POINT IS REACHED
	      // => contour is completed
	      // -------------------------------------------------
	      // Update perimeter using new contour direction
	      // See section (4.5) in the function header
	      perimeterPx_ += nghIdx / 2;

	      // Leave both loops for and while
	      notContourCompleted = false;
	      break;
	      // -------------------------------------------------
	      // END starting point is reached
	      // -------------------------------------------------
	    }

	  if (currLabel == LABEL_CONTOUR_)
	    {
	      // -------------------------------------------------
	      // THE NEW POINT IS ALREADY MARKED AS CONTOUR
	      // => do not record it as contour point
	      // -------------------------------------------------
	      // Update:
	      // - pointer to the current contour point
	      // - current contour direction
	      // - coordinates of the current contour point
	      // - perimeter: see section (V) in function header
	      pCurrPt       = pNewPt;
	      currDir       = s_4_new_dir_[newIdx];
	      currX        += s_4_incr_x_[newIdx];
	      currY        += s_4_incr_y_[newIdx];
	      perimeterPx_ += nghIdx / 2;

	      // Leave loop for
	      break;
	      // -------------------------------------------------
	      // END new point is marked as contour point
	      // -------------------------------------------------
	    }

	} // END for nghIdx

      //
      // **** LEAVING LOOP FOR LEADS HERE ****
      //

    }
  // WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
  // END BLOCK-WHILE
  // back to the starting point
  // WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW

  // Unmark the contour points in the component image

  for (std::list<Component::label_type*>::iterator itML = pPtList.begin();
       itML != pPtList.end();
       ++itML)
    {
      **itML = label_;
    }


} // END Component::PRIVATEcontour4()



// _________________________________________________________________
//
// CONTOUR POINTS USING 8-CONNECTIVITY
// _________________________________________________________________
//
// 
// (8.1) DIRECTION CODING
//   
// N  NE  E  SE  S  SW  W  NW
// 0  1   2  3   4  5   6  7
//   
// Directions are coded clockwise, from N(orth) to N(orth-)W(est):
// see enum type QGEdirection in file image.h.
// 
// (8.2) SEARCHING FOR THE NEW CONTOUR POINT
//   
//       +---+---+---+                     +---+---+---+           +---+---+---+
//       | * | n0| n1|                     | w | w | b |           | w | w | w |
//       +---+---+---+   contour           +---+---+---+           +---+---+---+
//   (1) --n6--c | n2|-> direction    (1a) --b---b | b |->    (1b) --b---b | w |->
//       +---+---+---+   (East)            +---+---+---+           +---+---+---+
//       | * | n4| n3|                     | b | b | b |           | b | w | w |
//       +---+---+---+                     +---+---+---+           +---+---+---+
// 
//       SEARCH LIST:
// n0 - n2 - n1 - n4 - n3 - n6
// 
// 
//       \---+---+---+                     \---+---+---+           \---+---+---+
//       | n7| * | n1|                     | b | w | b |           | b | w | w |
//       +---\---+---+                     +---\---+---+           +---\---+---+
//   (2) | * | c | n2|                (2a) | w | b | b |      (2b) | b | b | w |
//       +---+---+---+                     +---+---+---+           +---+---+---+
//       | n5| n4| n3|                     | w | b | b |           | w | w | w |
//       +---+---+---+                     +---+---+---+           +---+---+---+
//                    \ contour                         \ SE                    \ SE
//         	       direction            
//                    (South-East)         b: black pixel          b: black pixel
//                                         w: white pixel          w: white pixel
//       SEARCH LIST:
// n2 - n1 - n4 - n3 - n5 - n7
// @endverbatim
// 
// - currDir is the so-called "contour direction", that is to say 
//   the direction of the contour part beingconstructed, whose c
//   is the current end.
// - The outside of the component is always on the left side when
//   moving along the contour direction.
// - The new contour point is searched clockwise among the 8 neighbors
//   of c, starting from the point left-perpendicular to currDir:
//   n0 and n1 on figures 1 and 2, respectively.
// 
// Thus, the search list a priori is
// n0 - n1 - n2 - n3 - n4 - n5 - n6 - n7  for figure 1, and
// n1 - n2 - n3 - n4 - n5 - n6 - n7 - n0  for figure 2.
// 
// However, a 4-connected neighbor must be examined BEFORE the neighbor
// of previous diagonal direction, in order to get ALL the contour points.
// Otherwise, on figures 1a and 2a, the new contour point would be n1,
// and point n2 would be missed. Thus, the search list becomes
// n0 - n2 - n1 - n4 - n3 - n6 - n5 - n7  for figure 1, and
// n2 - n1 - n4 - n3 - n6 - n5 - n0 - n7  for figure 2.
// 
// Moreover, by construction, n5 and n7 on figure 1 and n6 and n0
// on figure 2 (6th and 8th neighbors of the initial lists) cannot be
// contour points. Thus, the final search list is
// n0 - n2 - n1 - n4 - n3 - n6  for figure 1, and
// n2 - n1 - n4 - n3 - n5 - n7  for figure 2.
// 
// (8.3) COORDINATES OF NEIGHBORS
// 
//                        <------ nghIdx ----->
//                        0   1   2   3   4   5
//                      +---+---+---+---+---+---+
//               / N  0 |-1 | 0 |-1 | 1 | 1 | 0 |
//               |      +---+---+---+---+---+---+
//               | NE 1 | 0 |-1 | 1 | 1 | 1 |-1 |
//               |      +---+---+---+---+---+---+
//               | E  2 | 0 | 1 | 1 | 0 | 1 |-1 | <- figure 1
//               |      +---+---+---+---+---+---+
//               | SE 3 | 1 | 1 | 0 | 1 |-1 |-1 | <- figure 2
//      currDir <       +---+---+---+---+---+---+
//               | S  4 | 1 | 0 | 1 |-1 |-1 | 0 |
//               |      +---+---+---+---+---+---+
//               | SW 5 | 0 | 1 |-1 |-1 |-1 | 1 |
//               |      +---+---+---+---+---+---+
//               | W  6 | 0 |-1 |-1 | 0 |-1 | 1 |
//               |      +---+---+---+---+---+---+
//               \ NW 7 |-1 |-1 | 0 |-1 | 1 | 1 |
//                      +---+---+---+---+---+---+
//                             s_8_incr_x_
// 
// 
//                        <------ nghIdx ----->
//                        0   1   2   3   4   5
//                      +---+---+---+---+---+---+
//               / N  0 | 0 |-1 |-1 | 0 |-1 | 1 |
//               |      +---+---+---+---+---+---+
//               | NE 1 |-1 |-1 | 0 |-1 | 1 | 1 |
//               |      +---+---+---+---+---+---+
//               | E  2 |-1 | 0 |-1 | 1 | 1 | 0 | <- figure 1
//               |      +---+---+---+---+---+---+
//               | SE 3 | 0 |-1 | 1 | 1 | 1 |-1 | <- figure 2
//      currDir <       +---+---+---+---+---+---+
//               | S  4 | 0 | 1 | 1 | 0 | 1 |-1 |
//               |      +---+---+---+---+---+---+
//               | SW 5 | 1 | 1 | 0 | 1 |-1 |-1 |
//               |      +---+---+---+---+---+---+
//               | W  6 | 1 | 0 | 1 |-1 |-1 | 0 |
//               |      +---+---+---+---+---+---+
//               \ NW 7 | 0 | 1 |-1 |-1 |-1 | 1 |
//                      +---+---+---+---+---+---+
//                             s_8_incr_y_
//   
// - Contour direction currDir determines the row to be used in each
//   table: rows 2 (East) and 3 (South-East) on figures 1 and 2, respectively.
// - The successive values in a row of table s_8_incr_x_
//   (resp. s_8_incr_y_) provide the X (resp. Y) increments to add to the X
//   (resp. Y) coordinate of c in order to get the X (resp. Y) coordinates
//   of the 6 possible new contour points in the appropriate order,
//   as explained in section (8.2).
// - In the same way, table offset3X3_8_ provides the offsets to add to the
//   pointer to c in order to get the pointers to the 6 neighbors.
// - nghIdx is the column index corresponding to the new contour point.
// 
// (8.4) THE NEW CONTOUR DIRECTION
// 
//                        <------ nghIdx ----->
//                        0   1   2   3   4   5
//                      +---+---+---+---+---+---+
//               / N  0 | W | N |NW | E |NE | S |
//               |      +---+---+---+---+---+---+
//               | NE 1 | N |NW | E |NE |SE |SW |
//               |      +---+---+---+---+---+---+
//               | E  2 | N | E |NE | S |SE | W | <- figure 1
//               |      +---+---+---+---+---+---+
//               | SE 3 | E |NE | S |SE |SW |NW | <- figure 2
//      currDir <       +---+---+---+---+---+---+
//               | S  4 | E | S |SE | W |SW | N |
//               |      +---+---+---+---+---+---+
//               | SW 5 | S |SE | W |SW |NW |NE |
//               |      +---+---+---+---+---+---+
//               | W  6 | S | W |SW | N |NW | E |
//               |      +---+---+---+---+---+---+
//               \ NW 7 | W |SW | N |NW |NE |SE |
//                      +---+---+---+---+---+---+
//                             s_8_new_dir_
// 
// - Once the new contour point is found, table s_8_new_dir_ provides
//   the new contour direction.
// - currDir determines the row to be used: rows 2
//   (East) and 3 (South-East) on figures 1 and 2, respectively.
// - Index nghIdx determines the column to be used.
// 
// [EXAMPLE] on figure 1, if the new contour point is n3,
// currDir == 2, nghIdx == 4, and the new contour
// direction is provided by s_8_new_dir_[2][4]: South-East.
// On figure 2, if the new contour point is n3,
// currDir == 3, nghIdx == 3, and the new contour
// direction is provided by s_8_new_dir_[3][3]: South-East, again.
//
// (8.5) THE PERIMETER
// 
// nghIdx         0                1                2
//          \---+---+---+    \---+---X---+    \---+---+---+
//          | n7|   |   |    | n7|   | n1|    | n7|   |   |
//          +---\---O---X    +---\---O---+    +---\---O---+
//          |   | c---n2|    |   | c |   |    |   | c |   |
//          +---+---+---+    +---+---+---+    +---+-|-+---+
//          |   |   |   |    |   |   |   |    |   | n4|   |
//          +---+---+---+    +---+---+---+    +---+---X---+
// increment      +1     \         +1     \         +2     \ currDir (South-East)
// 
// nghIdx         3                4                5
//          \---+---+---+    \---+---+---+    \---+---+---+
//          | n7|   |   |    | n7|   |   |    | n7|   |   |
//          +---\---O---+    +---\---O---+    X---\---O---+
//          |   | c |   |    |   | c |   |    |   | c |   |
//          +---+---\---X    +---/---+---+    +---+---+---+
//          |   |   | n3|    | n5|   |   |    |   |   |   |
//          +---+---+---+    +---X---+---+    +---+---+---+
// increment      +2     \         +3     \         +4     \ currDir (South-East)
// 
// SEARCH LIST (figure 2): n2 - n1 - n4 - n3 - n5 - n7
//                 nghIdx: 0    1    2    3    4    5
// 
// - A pixel is supposed to be a <i>unit-width-square</i>.
// - The current so-called <i>perimeter in pixels</i> is the length
//   between the top left corner of the starting pixel and the top right
//   (relatively to the current contour direction)
//   corner of the current pixel.
// 
// The figure above shows the values to add to the current perimeter
// for each possible neighbor of current contour point c
// when the contour direction is South-East (case of figure 2):
// O represents the top right corner of the current
// contour pixel, and X represents the top right corner
// of the new contour pixel.
// 
// @verbatim
//                        <------ nghIdx ----->
//                        0   1   2   3   4   5
//                      +---+---+---+---+---+---+
//               / N  0 | 0 | 1 | 1 | 2 | 2 | 3 |
//               |      +---+---+---+---+---+---+
//               | NE 1 | 1 | 1 | 2 | 2 | 3 | 4 |
//               |      +---+---+---+---+---+---+
//               | E  2 | 0 | 1 | 1 | 2 | 2 | 3 | <- figure 1
//               |      +---+---+---+---+---+---+
//               | SE 3 | 1 | 1 | 2 | 2 | 3 | 4 | <- figure 2
//      currDir <       +---+---+---+---+---+---+
//               | S  4 | 0 | 1 | 1 | 2 | 2 | 3 |
//               |      +---+---+---+---+---+---+
//               | SW 5 | 1 | 1 | 2 | 2 | 3 | 4 |
//               |      +---+---+---+---+---+---+
//               | W  6 | 0 | 1 | 1 | 2 | 2 | 3 |
//               |      +---+---+---+---+---+---+
//               \ NW 7 | 1 | 1 | 2 | 2 | 3 | 4 |
//                      +---+---+---+---+---+---+
//                         s_8_incr_perimeter_
// @endverbatim
// 
// - Table qgar::Component::s_8_incr_perimeter gives the value
//   to increment the current perimeter in pixels.
// - Contour direction currDir determines the row to be used:
//   rows 2 (East) and 3 (South-East) on figures 1 and 2,
//   respectively.
// - nghIdx determines the column to be used.
// 
// For example, on figure 1, if the new contour point is n3,
// currDir == 2, nghIdx == 4, and the perimeter increment
// is provided by s_8_incr_perimeter_[2][4]: 2.
// On figure 2, if the new contour point is n3, 
// currDir == 3, nghIdx == 3, and the perimeter increment
// is provided by s_8_incr_perimeter_[3][3]: 2, again.
// _________________________________________________________________


void
Component::PRIVATEcontour8()
{
  // Component image width
  int width = pCompImg_->width();
  
  // Pointer to the first contour point
  Component::label_type* pCurrPt =
    pCompImg_->pPixMap() + (yTopLeftPix_ * width) + xTopLeftPix_;
  // Mark this first point
  *pCurrPt = LABEL_START_;
  
  // Save this point as contour point
  contour_.push_back(IPoint(xTopLeftPix_, yTopLeftPix_));
  // Save the pointer to the point
  std::list<Component::label_type*> pPtList;
  pPtList.push_back(pCurrPt);

  // In the beginning, there is only *1* contour point (c)
  //
  //       +---+---+---+                    +---+---+---+
  //       | * | n0| * |                    | * | n0| n1|
  //       +---+---+---+                    +---+---+---+
  //  (1)  | n6| c | n2|               (2)  | n6| c | n2|-> East
  //       +---+---+---+                    +---+---+---+
  //       | n5| n4| n3|                    | * | n4| n3|
  //       +---+---+---+                    +---+---+---+
  //             |
  //             V South
  //
  //        SEARCH LIST:                     SEARCH LIST:
  // n2 - n4 - n3 - n6 - n5 - n0      n0 - n2 - n1 - n4 - n3 - n6
  //
  // As c is the top left pixel, n6, n7, n0 and n1 cannot be contour points:
  // => assume initial contour direction is South
  //    to start neighbors examination with n2 (case 1)
  // Otherwise, if, for example, the initial contour direction was assumed
  // to be East (case 2), n5 would not be examined and no contour would be
  // found when it goes first in the corresponding direction (South-West)

  int currDir = QGE_DIRECTION_S;
  
  // Coordinates of the current contour point
  int currX = xTopLeftPix_;
  int currY = yTopLeftPix_;

  // Initialize perimeter
  // WARNING: initial direction is supposed to be South
  //
  // O---+          S: starting pixel
  // | S |
  // +---X          length(OX) == 2
  //   |
  //   V South

  perimeterPx_ = 2;


  bool notContourCompleted = true;
  
  while (notContourCompleted)
    // WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
    // BLOCK-WHILE
    // while the whole contour is not followed
    // WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
    {
      // WARNING
      // The different 2-dimensional tables used to construct
      // the contour (see function header) are in fact implemented
      // as 1-dimensional tables for efficiency
      // Offset to access the appropriate row of these tables
      int rowOffset = (currDir * s_8_ngh_cnt_) - 1;

      // For each neighbor: see section (8.2) in function header
      for (int nghIdx = 0 ; nghIdx < s_8_ngh_cnt_ ; ++nghIdx)
	{
	  // Update offset to access the tables
	  rowOffset += 1;

	  // Pointer to the current possible contour point
	  // in the pixel map of the component image
	  // See section (8.3) in the function header
	  Component::label_type* pNewPt
	    = pCurrPt + *(offset3X3_8_ + rowOffset);
	  
	  // Label of the current possible contour point
	  Component::label_type currLabel = *pNewPt;

	  if (currLabel == label_)
	    {
	      // -------------------------------------------------
	      // THE NEW POINT IS LABELLED LIKE THE COMPONENT
	      // => new contour point
	      // -------------------------------------------------
	      // Update:
	      // - pointer to the component image: see (8.3)
	      // - coordinates of contour point  : see (8.3)
	      // - contour direction             : see (8.4)
	      // - perimeter                     : see (8.5)
	      pCurrPt       = pNewPt;
	      currDir       = *(s_8_new_dir_        + rowOffset);
	      currX        += *(s_8_incr_x_         + rowOffset);
	      currY        += *(s_8_incr_y_         + rowOffset);
	      perimeterPx_ += *(s_8_incr_perimeter_ + rowOffset);

	      // Save new contour point and new pointer to it
	      contour_.push_back(IPoint(currX,currY));
	      pPtList.push_back(pCurrPt);

	      // Mark new point as contour point in component image
	      *pCurrPt = LABEL_CONTOUR_;

	      // Leave loop for
	      break;
	      // -------------------------------------------------
	      // END new point is labelled like the component
	      // -------------------------------------------------
	    }


	  if (currLabel == LABEL_START_)
	    {
	      // -------------------------------------------------
	      // STARTING POINT IS REACHED
	      // -------------------------------------------------

	      // Pointers to points at south and east of new point
	      Component::label_type* pEast  = pNewPt + 1;
	      Component::label_type* pSouth = pNewPt + width;

	      if (
		     // cases [1] and [2]
		     (
		       (*(pSouth - 1) == label_) &&
		       ((pCurrPt == pEast) || (pCurrPt == (pSouth + 1)))
		     )
		  ||
		     // case [3]
		     (
		       (*pSouth == label_) && (pCurrPt == pEast)
		     )
		  ) // if

		{
		  // =================================================
		  // WARNING: PARTICULAR CASES DUE TO 8-CONNECTIVITY
		  //          AND ONE-PIXEL-THICK PARTS
		  // A pixel with the same label as the component is
		  // located at SOUTH or SOUTH-WEST of starting point
		  // => continue contour following
		  // =================================================
		  //     
		  // -+---+---+---+-  -+---+---+---+-  -+---+---+---+-
		  //  | * | * | * |    | * | * | * |    | * | * | * |
		  // -+---+---+---+-  -+---+---+---+-  -+---+---+---+-
		  //  | * | S | c |    | * | S | * |    | * | S | c |
		  // -+---+---+---+-  -+---+---+---+-  -+---+---+---+-
		  //  | X | * |*/X|    | X | * | c |    | * | X | * |
		  // -+---+---+---+-  -+---+---+---+-  -+---+---+---+-
		  //       [1]              [2]              [3]
		  //
		  //  c: current point
		  //  *: points of other components
		  //  X: point of the current component
		  //  S: starting point (top left pixel)
		  // =================================================
		  // Update:
		  // - pointer to the component image: see (8.3)
		  // - coordinates of contour point  : see (8.3)
		  // - contour direction             : see (8.4)
		  // - perimeter                     : see (8.5)
		  pCurrPt       = pNewPt;
		  currDir       = *(s_8_new_dir_        + rowOffset);
		  currX        += *(s_8_incr_x_         + rowOffset);
		  currY        += *(s_8_incr_y_         + rowOffset);
		  perimeterPx_ += *(s_8_incr_perimeter_ + rowOffset);
		  // =================================================
		  // END particular cases
		  // =================================================
		}
	      else
		{
		  // =================================================
		  // NO PARTICULAR CASE
		  // => contour is effectively completed
		  // =================================================
		  // Update perimeter: see (8.5) in function header
		  perimeterPx_ += *(s_8_incr_perimeter_ + rowOffset);

		  /* Particular cases of perimeter updating
		  //
		  //    North-West
		  //         \
		  //          I---+---+---+              I---+---+
		  //          | S |   |   |      West <--| S | c |
		  //          X---\---+---+              X---O---+
		  //          |   | c |   |
		  //          +---O---+---+
		  //
		  // c: current contour pixel
		  // S: starting pixel (new contour point)
		  // I: initial corner from which the perimeter is measured
		  // O: top right corner of the current contour pixel
		  // X: top right corner of the new contour pixel
		  // (see section 8.5 in function header)
		  //
		  // => 1 must be added to the perimeter in both cases
		  */
		  currDir = *(s_8_new_dir_ + rowOffset);

		  if ((currDir == QGE_DIRECTION_W) ||
		      (currDir == QGE_DIRECTION_NW))
		    {
		      perimeterPx_ += 1;
		    }

		  // Leave both loop while
		  notContourCompleted = false;
		  // =================================================
		  // END contour is effectively completed
		  // =================================================
		}

	      // Leave loop for
	      break;

	      // -------------------------------------------------
	      // END starting point is reached
	      // -------------------------------------------------
	    }


	  if (currLabel == LABEL_CONTOUR_)
	    {
	      // -------------------------------------------------
	      // THE NEW POINT IS ALREADY MARKED AS CONTOUR
	      // => do not record it as contour point
	      // -------------------------------------------------
	      // Update:
	      // - pointer to the component image: see (8.3)
	      // - coordinates of contour point  : see (8.3)
	      // - contour direction             : see (8.4)
	      // - perimeter                     : see (8.5)
	      pCurrPt       = pNewPt;
	      currDir       = *(s_8_new_dir_        + rowOffset);
	      currX        += *(s_8_incr_x_         + rowOffset);
	      currY        += *(s_8_incr_y_         + rowOffset);
	      perimeterPx_ += *(s_8_incr_perimeter_ + rowOffset);

	      // Leave loop for
	      break;
	      // -------------------------------------------------
	      // END new point is labelled like the component
	      // -------------------------------------------------
	    }

	} // END for nghIdx

      //
      // **** LEAVING LOOP FOR LEADS HERE ****
      //

    }
  // WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
  // END BLOCK-WHILE
  // back to the starting point
  // WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW

  // Unmark the contour points in the component image

  for (std::list<Component::label_type*>::iterator itML = pPtList.begin();
       itML != pPtList.end();
       ++itML)
    {
      **itML = label_;
    }

} // END Component::PRIVATEcontour8()



// -------------------------------------------------------------------
// -------------------------------------------------------------------
// M A E R (PRIVATE FUNCTION)
// -------------------------------------------------------------------
// -------------------------------------------------------------------


// Compute the MAER (Minimum-Area Encasing Rectangle)

void
Component::PRIVATEcomputeMaer()
{
  // Construct the maer
  maer_ = new Maer(accessContour());

  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // WARNING: The computation of the MAER is performed in the continuous
  // 2D space, while the computation of connected components features is
  // performed in the 2D discrete space. In particular, a component area
  // is provided in terms of a number of pixels, but its MAER area is not.
  // => An APPROXIMATION of the MAER area (in pixels) is calculated
  //    by adding 1 to the width and length of the MAER
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  const std::list<DPoint>& lv = maer_->accessVertices();
  std::list<DPoint>::const_iterator itV1 = lv.begin();
  std::list<DPoint>::const_iterator itV2 = itV1;
  ++itV2;

  double dx12 = itV1->x() - itV2->x();
  double dy12 = itV1->y() - itV2->y();

  ++itV1;
  ++itV2;
  double dx23 = itV1->x() - itV2->x();
  double dy23 = itV1->y() - itV2->y();

  maerAreaPx_
    = (int) std::ceil((hypot(dx12,dy12) + 1.) * (hypot(dx23,dy23) + 1.));
}

// -------------------------------------------------------------------
// -------------------------------------------------------------------

} // namespace qgar
