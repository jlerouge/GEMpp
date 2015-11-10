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
 * @file GenConvexHull.tcc
 *
 * @brief Implementation of function members of class qgar::GenConvexHull.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   January 27, 2005  20:20
 * @since  Qgar 2.2
 */



// STD
#include <iostream>
#include <list>
#include <set>
#include <utility>
// QGAR
#include "ISerializable.h"
#include "math.h"
#include "primitives.h"




namespace qgar
{


// -------------------------------------------------------------------
// C O N S T R U C T O R S
// -------------------------------------------------------------------


// DEFAULT CONSTRUCTOR.

template <class T>
GenConvexHull<T>::GenConvexHull()
{
  // VOID
}


// COMPUTE THE CONVEX HULL OF A STL LIST OF POINTS

template <class T>
GenConvexHull<T>::GenConvexHull(const std::list< GenPoint<T> >& aPtList)
{
   PRIVATEgraham_sScan(aPtList);
}


// COPY-CONSTRUCTOR

template <class T>
GenConvexHull<T>::GenConvexHull(const GenConvexHull<T>& aCHull)
  : _vertices(aCHull._vertices),
    _hull(aCHull._hull),
    _pivot(aCHull._pivot)
{
  // VOID
}


// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------


template <class T>
GenConvexHull<T>::~GenConvexHull()
{
  // VOID
}


// -------------------------------------------------------------------
// A C C E S S   T O   C H A R A C T E R I S T I C S
// -------------------------------------------------------------------


// IS HULL EMPTY?

template <class T>
bool GenConvexHull<T>::empty() const
{
  return _vertices.empty();
}


// GET NUMBER OF VERTICES
template <class T>
int
GenConvexHull<T>::size() const
{
  return (int) _vertices.size();
}


// -------------------------------------------------------------------
// A C C E S S   T O   P O I N T S
// -------------------------------------------------------------------


// GET VERTICES

template <class T>
const std::list< GenPoint<T> >&
GenConvexHull<T>::accessVertices() const
{
  return _vertices;
}


// GET A COPY OF THE VERTICES

template <class T>
std::list< GenPoint<T> >
GenConvexHull<T>::vertices() const
{
  return _vertices;
}


// GET PIVOT
template <class T>
const GenPoint<T>&
GenConvexHull<T>::accessPivot() const
{
  return _pivot;
}


// GET A COPY OF THE PIVOT
template <class T>
GenPoint<T>
GenConvexHull<T>::pivot() const
{
  return _pivot;
}


// -------------------------------------------------------------------
// O P E R A T O R S
// -------------------------------------------------------------------


// ASSIGNMENT

template <class T>
GenConvexHull<T>&
GenConvexHull<T>::operator=(const GenConvexHull<T>& aCHull)
{
  // Are left hand side and right hand side different objects?
  if (this != &aCHull)
    {
      _vertices = aCHull._vertices;
      _hull     = aCHull._hull;
      _pivot    = aCHull._pivot;
    }

  return *this;
}


// -------------------------------------------------------------------
// S E R I A L I Z A T I O N / D E S E R I A L I Z A T I O N
// -------------------------------------------------------------------


template <class T>
std::istream& 
GenConvexHull<T>::read(std::istream& anInStream)
{
  qgReadObjName(anInStream, "ConvexHull");

  // Retrieve vertices

  std::list< GenPoint<T> > ptList;

  int pointCnt;
  qgReadObjData(anInStream, pointCnt);
  
  for(int iCnt = 0 ; iCnt < pointCnt ; ++iCnt)
    {
      GenPoint<T> point;
      qgReadObjData(anInStream, point);
      // Conform to the initial ordering of vertices
      ptList.push_back(point);
    }
  
  // Create hull from the list of points
  PRIVATEgraham_sScan(ptList);

  return anInStream;
}


template <class T>
std::ostream& 
GenConvexHull<T>::write(std::ostream& anOutStream) const
{
  anOutStream << "ConvexHull("
	      << _vertices.size()
	      << ')';

  // Write the list of vertices to the stream.
  
  for(typename std::list< GenPoint<T> >::const_iterator
	itLP = _vertices.begin();
      itLP != _vertices.end();
      ++itLP)
    {
      anOutStream << '('
		  << *itLP
		  << ')';
    }

  return anOutStream;
}


// -------------------------------------------------------------------
// A U X I L I A R Y   F U N C T I O N S   ( P R I V A T E )
// -------------------------------------------------------------------


// EFFECTIVE CONSTRUCTION OF THE CONVEX HULL

template <class T>
void
GenConvexHull<T>::PRIVATEgraham_sScan(const std::list< GenPoint<T> >& aPtList)
{
if (aPtList.empty())
    {
      // Empty list: Nothing to do
      return;
    }

  //+---------------------------------------------------------------+
  //|              Graham's scan works in three steps               |
  //+---------------------------------------------------------------+

  // 1. Compute pivot
  //    -------------
  // Find an extreme point, the so-called pivot, which is guaranteed
  // to be on the hull: It is chosen as the point with the minimum
  // Y coordinate.

  // Iterator on the given list of points
  typename std::list< qgar::GenPoint<T> >::const_iterator
    itPL = aPtList.begin();

  // Pointer to the pivot
  typename std::list< qgar::GenPoint<T> >::const_iterator
    itPivot = itPL;

  // Find the point of minimum Y coordinate
  // For equal Y coordinates, choose the minimum X coordinate
  for (++itPL ; itPL != aPtList.end() ; ++itPL)
    {
      T yCurr = itPL->y();
      T yPiv  = itPivot->y();

      if (yCurr < yPiv)
	{
	  itPivot = itPL;
	}
      else if (yCurr == yPiv)
	{
	  if ((itPL->x()) < (itPivot->x()))
	    {
	      itPivot = itPL;
	    }
	}
    }

  // Save pivot
  _pivot = *itPivot;


  // 2. Sort the points
  //    ---------------
  // in the order of increasing angle about the pivot.
  // The result is a star-shaped polygon,
  // in which the pivot can "see" the whole polygon.

  for (itPL = aPtList.begin() ; itPL != aPtList.end() ; ++itPL)
    {
      // Do not process the pivot
      if (itPL != itPivot)
	{
	  typename std::pair< double, GenPoint<T> > p(qgAngle(_pivot, *itPL), *itPL);
	  _hull.insert(p);
	}
    }

  // Check the number of remaining points (because of possible duplicates)

  if(_hull.size() < 3)
    {
      // 1, 2 or 3 points: Just copy pivot and selected points
      _vertices.push_back(_pivot);

      for(typename std::multiset<QGDpair, _sortPred>::iterator itH = _hull.begin();
	  itH != _hull.end();
	  ++itH)
	{
	  _vertices.push_back(itH->second);
	}
      return;
    }


  // 3. Build the hull
  //    --------------
  // by marching around the star-shaped poly, adding edges at right turns,
  // and backtracking at left turns.

  // THE GIVEN LIST OF POINTS INCLUDES AT LEAST 4 POINTS

  // Previous point
  typename std::multiset<QGDpair, _sortPred>::iterator itPrev = _hull.begin();

  // Current point
  typename std::multiset<QGDpair, _sortPred>::iterator itCurr = itPrev;
  ++itCurr;
  
  // Next point
  typename std::multiset<QGDpair, _sortPred>::iterator itNext = itCurr;
  ++itNext;

  for ( ; itNext != _hull.end() ; ++itNext)
    {
      // Angle between vector formed by previous and current point
      // and vector formed by current and next point
      if (  qgAngle(itPrev->second, itCurr->second, itNext->second)
	   >
	    Math::QG_PI )
	{
	  // The angle is greater than PI: The current point does not
	  // belong to the hull and must be erased
	  _hull.erase(itCurr);

	  // Backtrack unless at beginning
	  if (itPrev != _hull.begin())
	    {
	      --itPrev;
	    }
	}
      else
	{
	  // The angle is less than PI:
	  // Update previous point for next turn in loop
	  ++itPrev;
	}

      // Update current and next points for next turn in loop
      itCurr = itPrev;
      ++itCurr;
      itNext = itCurr;

    } // END for


  // CONSTRUCT THE LIST OF VERTICES OF THE HULL
  for (itCurr = _hull.begin() ; itCurr != _hull.end() ; ++itCurr)
    {
      _vertices.push_back(itCurr->second);
    }

  // ADD PIVOT
  _vertices.push_front(_pivot);

}


// -------------------------------------------------------------------


} // namespace qgar
