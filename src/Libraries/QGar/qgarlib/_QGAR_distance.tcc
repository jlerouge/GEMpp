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
 * @file   _QGAR_distance.tcc
 *
 * @brief Implementation of global functions to compute distances
 * between primitives.
 *
 * Computational geometry equations can be found in the FAQ section
 * of comp.graphics.algorithms. They are based on
 * [<a href="Bibliography.html#Kirk-1992">Kirk,&nbsp;1992</a>],
 * pages 199-202, and
 * [<a href="Bibliography.html#ORourke-1994">O'Rourke,&nbsp;1994</a>],
 * pages 249-51.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   February 03, 2005  17:58
 * @since  Qgar 2.2
 */



// STD
#include <cmath>



namespace qgar
{


// -------------------------------------------------------------------
// DIFFERENCE BETWEEN X COORDINATES OF THE GIVEN POINTS
// -------------------------------------------------------------------


template <class T>
inline T
qgDX(const GenPoint<T>& aPt1, const GenPoint<T>& aPt2)
{
  return aPt1.x() - aPt2.x();
}


// -------------------------------------------------------------------
// DIFFERENCE BETWEEN Y COORDINATES OF THE GIVEN POINTS
// -------------------------------------------------------------------


template <class T>
inline T
qgDY(const GenPoint<T>& aPt1, const GenPoint<T>& aPt2)
{
  return aPt1.y() - aPt2.y();
}


// -------------------------------------------------------------------
// DISTANCE BETWEEN TWO POINTS
// -------------------------------------------------------------------


template <class T>
double
qgDist(const GenPoint<T>& aPt1, const GenPoint<T>& aPt2)
{
  return qgDist(aPt1.x(), aPt1.y(), aPt2.x(), aPt2.y());
}


template <class T>
inline double
qgDist(T aX1, T aY1, T aX2, T aY2)
{
  return hypot(static_cast<double>(aX1 - aX2),
	       static_cast<double>(aY1 - aY2));
}


// -------------------------------------------------------------------
// DISTANCE BETWEEN POINT aPt AND ITS A PERPENDICULAR PROJECTION
// ONTO THE LINE PASSING THROUGH POINTS aPt1 AND aPt2
// -------------------------------------------------------------------


// Let C  be the point (XC,YC)
//     AB be the line segment (XA,YA) to (XB,YB)
//     L  be the length of AB
//
//     L = ((XB-XA)**2 + (YB-YA)**2)**0.5
// and
//     s = ((YA-YC)(XB-XA) - (XA-XC)(YB-YA)) / L**2
//
// Let I be the point of perpendicular projection of C onto AB
//     d be the distance from C to I
//
//     d = s * L
//     d = ((YA-YC)(XB-XA) - (XA-XC)(YB-YA)) / L


template <class T>
double
qgDist(const GenPoint<T>& c,
       const GenPoint<T>& a,
       const GenPoint<T>& b)
{
  // Each coordinate is separately casted: If only the result of the
  // of the operations of the numerator of 'd' were casted, an
  // overflow may occur when dealing with large integers or floats

  double xA = static_cast<double>(a.x());
  double yA = static_cast<double>(a.y());

  double xB = static_cast<double>(b.x());
  double yB = static_cast<double>(b.y());

  double yC = static_cast<double>(c.y());
  double xC = static_cast<double>(c.x());

  return std::fabs(  (((yA - yC) * (xB - xA)) - ((xA - xC) * (yB - yA)))
                   /
                     qgDist(a,b) );
}


// SPECIALIZED VERSION, TO PRESERVE EFFICIENCY WHEN USING DOUBLES
// => no local variables needed

template <>
inline double
qgDist<double>(const GenPoint<double>& c,
	       const GenPoint<double>& a,
	       const GenPoint<double>& b)
{
  return
    std::fabs( (  ((a.y() - c.y()) * (b.x() - a.x()))
                - ((a.x() - c.x()) * (b.y() - a.y())) )
	      /
	        qgDist(a,b) );
}


// -------------------------------------------------------------------
// DISTANCE BETWEEN POINT (0,0) AND ITS PERPENDICULAR
// PROJECTION ONTO THE LINE SUPPORTING A SEGMENT
// -------------------------------------------------------------------


template <class T>
inline double
qgDist(const GenSegment<T>& aSeg)
{
  return std::fabs(aSeg.rho());
}


// -------------------------------------------------------------------
// DISTANCE BETWEEN POINT (0,0) AND ITS PERPENDICULAR
// PROJECTION ONTO THE LINE SUPPORTING A Qgar SEGMENT
// -------------------------------------------------------------------


template <class T>
inline double
qgDist(const GenQgarSegment<T>& aQSeg)
{
  return qgDist(aQSeg.accessGeomStructure());
}


// -------------------------------------------------------------------
// DISTANCE BETWEEN A POINT AND ITS PERPENDICULAR
// PROJECTION ONTO THE LINE SUPPORTING A SEGMENT
// -------------------------------------------------------------------


template <class T>
inline double
qgDist(const GenPoint<T>& aPt, const GenSegment<T>& aSeg)
{
  return qgDist(aPt, aSeg.accessSource(), aSeg.accessTarget());
}


template <class T>
inline double
qgDist(T aX, T aY, const GenSegment<T>& aSeg)
{
  return qgDist(GenPoint<T>(aX,aY), aSeg);
}


// -------------------------------------------------------------------
// DISTANCE BETWEEN A POINT AND ITS PERPENDICULAR
// PROJECTION ONTO THE LINE SUPPORTING A Qgar SEGMENT
// -------------------------------------------------------------------


template <class T>
inline double
qgDist(const GenPoint<T>& c, const GenQgarSegment<T>& aQSeg)
{
  return qgDist(c, aQSeg.accessGeomStructure());
}


template <class T>
inline double
qgDist(T aX, T aY, const GenQgarSegment<T>& aQSeg)
{
  return qgDist(GenPoint<T>(aX,aY), aQSeg);
}


// -------------------------------------------------------------------
// SQUARED DISTANCE BETWEEN TWO POINTS
// -------------------------------------------------------------------


template <class T>
inline double
qgSqr_dist(const GenPoint<T>& aPt1, const GenPoint<T>& aPt2)
{
  return qgSqr_dist(aPt1.x(), aPt1.y(), aPt2.x(), aPt2.y());
}


template <class T>
double
qgSqr_dist(T aX1, T aY1, T aX2, T aY2)
{
  double dX = aX1 - aX2;
  double dY = aY1 - aY2;

  return (dX * dX) + (dY * dY);
}


// -------------------------------------------------------------------


} // namespace qgar
