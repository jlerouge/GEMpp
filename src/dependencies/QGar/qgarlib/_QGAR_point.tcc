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
 * @file   _QGAR_point.tcc
 * @brief  Implementation of global functions which compute points.
 *
 * Computational geometry equations can be found in the FAQ section
 * of comp.graphics.algorithms and are based on
 * [<a href="Bibliography.html#Kirk-1992">Kirk,&nbsp;1992</a>],
 * pages 199-202, and
 * [<a href="Bibliography.html#ORourke-1994">O'Rourke,&nbsp;1994</a>],
 * pages 249-51.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   February 03, 2005  18:53
 * @since  Qgar 2.2
 */



// QGAR
#include "math.h"



namespace qgar
{


// -------------------------------------------------------------------
// A R C S   A N D   C I R C L E S
// -------------------------------------------------------------------


// CENTER OF THE CIRCLE PASSING THROUGH THREE GIVEN POINTS
// =======================================================
// Return 'false' if the 3 points are collinear, 'true' otherwise


// GENERIC VERSION

template <class T>
bool
qgCircleCenter(const GenPoint<T>&  t,
	       const GenPoint<T>&  p,
	       const GenPoint<T>&  q,
	       GenPoint<double>&  aCenter)
{
  double tX = static_cast<double>(t.x());
  double tY = static_cast<double>(t.y());

  double pX = static_cast<double>(p.x());
  double pY = static_cast<double>(p.y());

  double qX = static_cast<double>(q.x());
  double qY = static_cast<double>(q.y());

  // The coordinates of the center of the circle passing through
  // points t, p, and q are:
  //
  //     A = pX - tX
  //     B = pY - tY
  //     C = qX - tX
  //     D = qY - tY
  //     E = A*(tX + pX) + B*(tY + pY)
  //     F = C*(tX + qX) + D*(tY + qY)
  //     G = 2 * (A*(qY - pY) - B*(qX - pX))
  //
  //     centerX = (D*E - B*F) / G
  //     centerY = (A*F - C*E) / G
  //
  // If G is zero then the three points are collinear
  // and no finite-radius circle through them exists

  double A = pX - tX;
  double B = pY - tY;
  double G = 2. * (A * (qY - pY) - B * (qX - pX));

  if (qgEq0(G))
    {
      return false;  // Collinear points
    }

  double C = qX - tX;
  double D = qY - tY;
  double E = A * (tX + pX) + B * (tY + pY);
  double F = C * (tX + qX) + D * (tY + qY);

  aCenter.setXY((D*E - B*F) / G, (A*F - C*E) / G);

  return true;
}


// SPECIALIZED VERSION, TO PRESERVE EFFICIENCY WHEN USING DOUBLES
// => no local variables needed

template <>
inline bool
qgCircleCenter<double>(const GenPoint<double>&  t,
		       const GenPoint<double>&  p,
		       const GenPoint<double>&  q,
		       GenPoint<double>&  aCenter)
{
  double A = p.x() - t.x();
  double B = p.y() - t.y();
  double G = 2. * (A * (q.y() - p.y()) - B * (q.x() - p.x()));

  if (qgEq0(G))
    {
      return false;  // Collinear points
    }

  double C = q.x() - t.x();
  double D = q.y() - t.y();
  double E = A * (t.x() + p.x()) + B * (t.y() + p.y());
  double F = C * (t.x() + q.x()) + D * (t.y() + q.y());

  aCenter.setXY((D*E - B*F) / G, (A*F - C*E) / G);

  return true;
}


// -------------------------------------------------------------------
// I N T E R S E C T I O N S
// -------------------------------------------------------------------


// INTERSECTION OF THE LINES SUPPORTING TWO GIVEN SEGMENTS
// =======================================================
// Return 'false' if the lines supporting the segments are
// approximately collinear/parallel according to threshold
// 'anAngle'. Otherwise, assign the intersection point to
// 'aPt' and return 'true'.

template <class T>
bool
qgIntersect(const GenSegment<T>& ab,
	    const GenSegment<T>& cd,
	    GenPoint<double>& i,
	    double anAngle)
{
  // Are the lines approximately collinear or parallel?
  if (qgEq(ab.theta(), cd.theta(), anAngle) ||
      qgEq(std::fabs(ab.theta() - cd.theta()), Math::QG_PI, anAngle))
    {
      return false;
    }

  // ________________________________________________________________
  //
  // Each coordinate is separately casted: If only the result of the
  // of the operations of the numerator of 'r' were casted, overflows
  // may occur when dealing with large integers or floats

  double xA = ab.xSource();
  double yA = ab.ySource();
  double xB = ab.xTarget();
  double yB = ab.yTarget();

  double xC = cd.xSource();
  double yC = cd.ySource();
  double xD = cd.xTarget();
  double yD = cd.yTarget();
  // ________________________________________________________________

  // Let A,B,C,D be 2-space position vectors.
  // Then the directed line segments AB & CD are given by:
  //
  //   AB = A + r(B - A), r in [0,1]
  //   CD = C + s(D - C), s in [0,1]
  //
  // If AB & CD intersect, then
  //
  //   A + r(B-A) = C + s(D-C): XA + r(XB - XA) = XC + s(XD - XC)
  //                            YA + r(YB - YA) = YC + s(YD - YC)
  //                            for r,s in [0,1]
  //
  // Solving the above for r and s yields
  //
  //       (YA - YC)(XD - XC) - (XA - XC)(YD - YC)
  //   r = ---------------------------------------    [EQN5]
  //       (XB - XA)(YD - YC) - (YB - YA)(XD - XC)
  //
  //       (YA - YC)(XB - XA) - (XA - XC)(YB - YA)
  //   s = ---------------------------------------    [EQN6]
  //       (XB - XA)(YD - YC) - (YB - YA)(XD - XC)
  //
  // Let I be the position vector of the intersection point, then
  //
  //   I = A + r(B - A):  XI = XA + r(XB - XA)   [EQN7]
  //                      YI = YA + r(YB - YA)   [EQN8]
  //
  // In EQN5 and EQN6, the denominator is:
  //   d = (XB - XA)(YD - YC) - (YB - YA)(XD - XC)
  //
  // Let abDX = XB - XA, adDY = YB - YA, cdDX = XD - XC, cdDY = YD - YC
  //   d = abDX*cdDY - abDY*cdDX
  //
  // EQN5 is: r = ((YA - YC)(XD - XC) - (XA - XC)(YD - YC)) / d
  //          r = (cdDX(YA - YC) - cdDY(XA - XC)) / d
  //
  // EQN7 is: XI = XA + r(XB - XA) = XA + r*abDX
  // EQN8 is: YI = YA + r(YB - YA) = YA + r*abDY
  //
  // By examining the values of r & s, you can also determine some
  // other limiting conditions:
  //
  //     If 0 <= r <= 1 & 0 <= s <=1          intersection exists
  //     If r < 0 or r > 1 or s < 0 or s > 1  line segments do not intersect
  //
  //     If the denominator in EQN5 is zero, AB & CD are parallel
  //     If the numerator in EQN5 is also zero, AB & CD are coincident
  //
  // If the intersection point of the 2 lines are needed (lines in this
  // context mean infinite lines) regardless whether the two line
  // segments intersect,
  // then if r > 1, I is located on extension of AB
  //      if r < 0, I is located on extension of BA
  //      if s > 1, I is located on extension of CD
  //      if s < 0, I is located on extension of DC
  //
  // Also note that the denominators of EQN5 & EQN6 are identical.

  double abDX = xB - xA;
  double abDY = yB - yA;
  double cdDX = xD - xC;
  double cdDY = yD - yC;
  
  double r =  ((cdDX * (yA - yC)) - (cdDY * (xA - xC)))
            /
              ((abDX * cdDY) - (abDY * cdDX));

  i.setXY(xA + (r * abDX), yA + (r * abDY));

  return true;
}


// SPECIALIZED VERSION, TO PRESERVE EFFICIENCY WHEN USING DOUBLES:
// NO LOCAL VARIABLES NEEDED

template <>
inline bool
qgIntersect<double>(const GenSegment<double>& ab,
		    const GenSegment<double>& cd,
		    GenPoint<double>& i,
		    double anAngle)
{
  // Are the lines approximately collinear or parallel?

  if (qgEq(ab.theta(), cd.theta(), anAngle) ||
      qgEq(std::fabs(ab.theta() - cd.theta()), Math::QG_PI, anAngle))
    {
      return false;
    }

  double abDX = ab.dx();
  double abDY = ab.dy();
  double cdDX = cd.dx();
  double cdDY = cd.dy();
  
  double r =  (  (cdDX * (ab.ySource() - cd.ySource()))
               -
                 (cdDY * (ab.xSource() - cd.xSource())) )
            /
              ((abDX * cdDY) - (abDY * cdDX));

  i.setXY(ab.xSource() + (r * abDX), ab.ySource() + (r * abDY));

  return true;
}


// INTERSECTION OF THE LINES SUPPORTING TWO GIVEN Qgar SEGMENTS
// ============================================================

template <class T>
inline bool
qgIntersect(const GenQgarSegment<T>& aQSeg1,
	    const GenQgarSegment<T>& aQSeg2,
	    GenPoint<double>& aPt,
	    double anAngle)
{
  return qgIntersect(aQSeg1.accessGeomStructure(),
		     aQSeg2.accessGeomStructure(),
		     aPt,
		     anAngle);
}


// -------------------------------------------------------------------
// M I D D L E   P O I N T S
// -------------------------------------------------------------------


// MIDDLE POINT OF A SEGMENT
// =========================

template <class T>
inline GenPoint<double>
qgMiddle(const GenSegment<T>& aSeg)
{
  return qgMiddle(aSeg.accessSource(), aSeg.accessTarget());
}


// MIDDLE POINT OF A Qgar SEGMENT
// ==============================

template <class T>
inline GenPoint<double>
qgMiddle(const GenQgarSegment<T>& aQSeg)
{
  return qgMiddle(aQSeg.accessSource(), aQSeg.accessTarget());
}


// MIDDLE POINT OF THE SEGMENT JOINING TWO POINTS
// ==============================================

template <class T>
inline GenPoint<double>
qgMiddle(const GenPoint<T>& aPt1, const GenPoint<T>& aPt2)
{
  return GenPoint<double>((static_cast<double>(aPt1.xSource())
			   + static_cast<double>(aPt2.xTarget())) / 2.,
			  (static_cast<double>(aPt1.ySource())
			   + static_cast<double>(aPt2.yTarget())) / 2.);
}


// -------------------------------------------------------------------
// P R O J E C T I O N S
// -------------------------------------------------------------------


// RETURN THE ORTHOGONAL PROJECTION OF A POINT ONTO A SEGMENT
// ==========================================================

template <class T>
GenPoint<double>
qgProjectPoint(const GenPoint<T>& aPt, const GenSegment<T>& aSeg)
{
  GenPoint<double> p = GenPoint<double>(aPt);
  qgProject(p, aSeg);

  return p;
}


// ORTHOGONAL PROJECTION OF THE GIVEN POINT ONTO A SEGMENT
// =======================================================


template <class T>
inline void
qgProject(GenPoint<double>& aPt, const GenSegment<T>& aSeg)
{
  qgProject(aPt, static_cast< GenSegment<double> >(aSeg));
}


// SPECIALIZED VERSION, TO PRESERVE EFFICIENCY WHEN USING DOUBLES


template <>
inline void
qgProject<double>(GenPoint<double>& aPt, const GenSegment<double>& aSeg)
{
  // ___________________________________________________________________
  //
  // Let the point be C (XC,YC) and the line be AB (XA,YA) to (XB,YB).
  // The length of the line segment AB is L:
  //
  //     L = ((XB-XA)**2 + (YB-YA)**2)**0.5
  // and
  //     r = ((YA - YC)(YA - YB) - (XA - XC)(XB - XA)) / L**2  [EQN1]
  //     s = ((YA - YC)(XB - XA) - (XA - XC)(YB - YA)) / L**2  [EQN2]
  //
  // Let I be the point of perpendicular projection of C onto AB:
  //
  //     XI = XA + r(XB - XA)  [EQN3]
  //     YI = YA + r(YB - YA)  [EQN4]
  // ___________________________________________________________________

  // Let dx = XB-XA, dy = YA-YB  in [EQN1]

  double dx =   aSeg.dx();
  double dy = - aSeg.dy();

  // =>  r = (dy * (YA-YC) - dx * (XA-XC)) / L**2  [EQN1]

  double l = aSeg.length();
  double r =   (   dy * (aSeg.ySource() - aPt.y()) 
		 - dx * (aSeg.xSource() - aPt.x()) )
             / (l * l);
    
  // =>  XI = XA + r * dx  [EQN3]
  // =>  YI = YA + r * dy  [EQN4]

  aPt.setX(aSeg.xSource() + (r * dx));
  aPt.setY(aSeg.ySource() - (r * dy));
}
  


// RETURN THE ORTHOGONAL PROJECTION OF A POINT ONTO A Qgar SEGMENT
// ===============================================================


template <class T>
inline GenPoint<double>
qgProjectPoint(const GenPoint<T>& aPt, const GenQgarSegment<T>& aQSeg)
{
  return qgProjectPoint(aPt, aQSeg.accessGeomStructure());
}


// ORTHOGONAL PROJECTION OF THE GIVEN POINT ONTO A SEGMENT
// =======================================================


template <class T>
inline void
qgProject(GenPoint<double>& aPt,
	  const GenQgarSegment<T>& aQSeg)
{
  qgProject(aPt, aQSeg.accessGeomStructure());
}


// -------------------------------------------------------------------


} // namespace qgar
