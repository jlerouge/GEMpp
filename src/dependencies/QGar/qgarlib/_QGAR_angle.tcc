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
 * @file   _QGAR_angle.tcc
 * @brief  Implementation of global utilities for primitives.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   February 03, 2005  18:28
 * @since  Qgar 2.2
 */



// QGAR
#include "math.h"



namespace qgar
{


/*
 *   O
 *    +---------------> X
 *    |\    |
 *    | \ <-'
 *    |  \    angle (in radians unless specified)
 *    |   \ 
 *    |
 *    v
 *
 *    Y
 *
 * - The origin of the coordinate system is at top left corner
 * - Angles are clockwise from the X axis
 */



/* -------------------------------------------------------------------
 * ANGLE BETWEEN A VECTOR AND THE X AXIS
 * -------------------------------------------------------------------
 *
 *                                        ----->/
 * O                          O          /     /
 *  +---------------> X        +---------|-------------> X
 *  |    \    |                |         |   /  |
 *  |     \ <-' angle          |   angle \_ /__/
 *  |      \                   |           /
 *  |       + aPt1             |          + aPt2
 *  |        \                 |         ^
 *  |         \                |        /
 *  |          v               |       /
 *  v           + aPt2         v      + aPt1
 *
 *  Y                          Y
 *
 * -------------------------------------------------------------------
 */

// IN [0, 2PI[ RADIANS
// 4 COORDINATES GIVEN

template <class T>
double
qgAngle(T aX1, T aY1, T aX2, T aY2)
{
  double angle = atan2(static_cast<double>(aY2 - aY1),
		       static_cast<double>(aX2 - aX1));

  return (angle < 0.) ? (Math::QG_2PI + angle) : angle;
}


// IN [0, 2PI[ RADIANS
// 2 POINTS GIVEN

template <class T>
inline double
qgAngle(const GenPoint<T>& aPt1, const GenPoint<T>& aPt2)
{
  return qgAngle(aPt1.x(), aPt1.y(), aPt2.x(), aPt2.y());
}


// IN [0, 360[ DEGREES
// 4 COORDINATES GIVEN

template <class T>
double
qgAngleDegrees(T aX1, T aY1, T aX2, T aY2)
{
  return qgRadiansToDegrees(qgAngle(aX1, aY1, aX2, aY2));
}


// IN [0, 360[ DEGREES
// 2 POINTS GIVEN

template <class T>
inline double
qgAngleDegrees(const GenPoint<T>& aPt1, const GenPoint<T>& aPt2)
{
  return
    qgRadiansToDegrees(qgAngle(aPt1.x(), aPt1.y(), aPt2.x(), aPt2.y()));
}



/* -------------------------------------------------------------------
 * ANGLE BETWEEN 2 VECTORS DEFINED BY 3 POINTS
 * -------------------------------------------------------------------
 * 0
 *  +---------------------> X      +---------------------> X
 *  |                              |    ----
 *  |                              |   /    \
 *  | aPt1                         |   |     v
 *  |   +--------->+ aPt2          |   |  +------->+ aPt3
 *  |    \    |                    |   \ __\   
 *  |     \ <-'                    |        \
 *  |      \                       |         \
 *  |       v                      |          v   
 *  |        + aPt3                |           + aPt2
 *  v                              v
 *
 *  Y                              Y
 *
 * -------------------------------------------------------------------
 */


// IN [0, 2PI[ RADIANS
// 6 COORDINATES GIVEN

template <class T>
inline double
qgAngle(T aX1, T aY1, T aX2, T aY2, T aX3, T aY3)
{
  return qgAngle(aX1, aY1, aX2, aY2, aX1, aY1, aX3, aY3);
}


// IN [0, 2PI[ RADIANS
// 3 POINTS GIVEN

template <class T>
inline double
qgAngle(const GenPoint<T>& aPt1,
	const GenPoint<T>& aPt2,
	const GenPoint<T>& aPt3)
{
  return qgAngle(aPt1.x(), aPt1.y(),
		 aPt2.x(), aPt2.y(),
		 aPt1.x(), aPt1.y(),
		 aPt3.x(), aPt3.y());
}


// IN [0, 360[ DEGREES
// 6 COORDINATES GIVEN

template <class T>
inline double
qgAngleDegrees(T aX1, T aY1, T aX2, T aY2, T aX3, T aY3)
{
  return
    qgRadiansToDegrees(qgAngle(aX1, aY1, aX2, aY2, aX1, aY1, aX3, aY3));
}


// IN [0, 360[ DEGREES
// 3 POINTS GIVEN

template <class T>
inline double
qgAngleDegrees(const GenPoint<T>& aPt1,
	       const GenPoint<T>& aPt2,
	       const GenPoint<T>& aPt3)
{
  return qgRadiansToDegrees(qgAngle(aPt1.x(), aPt1.y(),
				    aPt2.x(), aPt2.y(),
				    aPt1.x(), aPt1.y(),
				    aPt3.x(), aPt3.y()));
}



/* -------------------------------------------------------------------
 * ANGLE BETWEEN TWO VECTORS DEFINED BY 4 POINTS
 * -------------------------------------------------------------------
 *
 * 0
 *  +----------------------> X      +-------------------------> X
 *  |                               |    ----
 *  |                               |   /    \
 *  |        aPt1                   |   |     v  aPt3
 *  |    \----+------>+ aPt2        |   |  \-----+------>+ aPt4
 *  |     \     |                   |   \ __\   
 *  | aPt3 +    |                   |        \
 *  |       \<--'                   |         + aPt1
 *  |        \                      |          \
 *  |         v                     |           v   
 *  |          + aPt4               |            + aPt2
 *  v                               v
 *
 *  Y                               Y
 *
 * -------------------------------------------------------------------
 */


// IN [0, 2PI[ RADIANS
// 8 COORDINATES GIVEN

template <class T>
double
qgAngle(T aX1, T aY1, T aX2, T aY2, T aX3, T aY3, T aX4, T aY4)
{
  double ang12 = qgAngle(aX1, aY1, aX2, aY2);
  double ang13 = qgAngle(aX3, aY3, aX4, aY4);

  return 
    (ang12 > ang13)
    ? (ang13 - ang12 + Math::QG_2PI)
    : (ang13 - ang12);
}


// IN [0, 2PI[ RADIANS
// 4 POINTS GIVEN

template <class T>
inline double
qgAngle(const GenPoint<T>& aPt1,
	const GenPoint<T>& aPt2,
	const GenPoint<T>& aPt3,
	const GenPoint<T>& aPt4)
{
  return qgAngle(aPt1.x(), aPt1.y(),
		 aPt2.x(), aPt2.y(),
		 aPt3.x(), aPt3.y(),
		 aPt4.x(), aPt4.y());
}



// IN [0, 360[ DEGREES
// 8 COORDINATES GIVEN

template <class T>
inline double
qgAngleDegrees(T aX1, T aY1,
	       T aX2, T aY2,
	       T aX3, T aY3,
	       T aX4, T aY4)
{
  return qgRadiansToDegrees(qgAngle(aX1, aY1,
				    aX2, aY2,
				    aX3, aY3,
				    aX4, aY4));
}


// IN [0, 360[ DEGREES
// 4 POINTS GIVEN

template <class T>
inline double
qgAngleDegrees(const GenPoint<T>& aPt1,
	       const GenPoint<T>& aPt2,
	       const GenPoint<T>& aPt3,
	       const GenPoint<T>& aPt4)
{
  return qgRadiansToDegrees(qgAngle(aPt1.x(), aPt1.y(),
				    aPt2.x(), aPt2.y(),
				    aPt3.x(), aPt3.y(),
				    aPt4.x(), aPt4.y()));
}



/* -------------------------------------------------------------------
 * ANGLE BETWEEN A SEGMENT AND THE X AXIS
 * -------------------------------------------------------------------
 *
 * O                          O
 *  +-----------------> X      +-----------------> X
 *  |    \    |                |    \    |
 *  |     \ <-' angle          |     \ <-' angle
 *  |      \                   |      \
 *  |       + aPt1             |       + aPt2
 *  |        \                 |        \
 *  |         \                |         \
 *  |          \               |          \
 *  v           + aPt2         v           + aPt1
 *
 *  Y                          Y
 *
 * -------------------------------------------------------------------
 */

// IN [0, 2PI[ RADIANS
// 4 COORDINATES GIVEN

template <class T>
double
qgSlope(T aX1, T aY1, T aX2, T aY2)
{
  double s = qgAngle(aX1, aY1, aX2, aY2);

  return (s >= Math::QG_PI) ? (s - Math::QG_PI) : s;
}


// IN [0, 2PI[ RADIANS
// 2 POINTS GIVEN

template <class T>
double
qgSlope(const GenPoint<T>& aPt1, const GenPoint<T>& aPt2)
{
  return qgSlope(aPt1.x(), aPt1.y(), aPt2.x(), aPt2.y());
}


// IN [0, 360[ DEGREES
// 4 COORDINATES GIVEN

template <class T>
double
qgSlopeDegrees(T aX1, T aY1, T aX2, T aY2)
{
  return qgRadiansToDegrees(qgSlope(aX1, aY1, aX2, aY2));
}


// IN [0, 360[ DEGREES
// 2 POINTS GIVEN

template <class T>
inline double
qgSlopeDegrees(const GenPoint<T>& aPt1, const GenPoint<T>& aPt2)
{
  return
    qgRadiansToDegrees(qgSlope(aPt1.x(), aPt1.y(), aPt2.x(), aPt2.y()));
}


// -------------------------------------------------------------------


} // namespace qgar
