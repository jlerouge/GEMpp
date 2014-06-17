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


#ifndef ___QGAR_ANGLE_H_INCLUDED__
#define ___QGAR_ANGLE_H_INCLUDED__


/**
 * @file   _QGAR_angle.h
 *
 * @brief  Global functions to compute angles from primitives.
 *
 *
 * @warning <b>Not to be used as include file!</b>
 * <br>When working with primitives, use header file primitives.h.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   February 03 2005,  18:18
 * @since  Qgar 2.2
 */



// For RCS/CVS use: Do not delete
/* $Id: _QGAR_angle.h,v 1.3 2006/03/31 09:32:20 gerald Exp $ */



namespace qgar
{



/*-------------------------------------------------------------------*
 |                                                                   |
 |        GLOBAL FUNCTIONS TO COMPUTE ANGLES FROM PRIMITIVES         |
 |                                                                   |
 *-------------------------------------------------------------------*/



// -------------------------------------------------------------------
// ANGLE BETWEEN A VECTOR AND THE X AXIS
// -------------------------------------------------------------------


/** 
 * @name Global functions to compute angles between vectors
 *
 * @warning
@verbatim
 O
  +---------------> X
  |\    |
  | \ <-'
  |  \    angle (in radians unless specified)
  |   \
  |
  v

    Y
@endverbatim
 * <ul>
 * <li>The origin of the coordinate system is at top left corner.</li>
 * <li>Angles are clockwise from the X axis.</li>
 * </ul>
 */
//@{




/**
 * @ingroup GLOB_PRIM_ANG
 *
 * @brief (Oriented) angle, in \f$[0, 2\pi[\f$ radians,
 * between the X axis and the vector formed by 2 points.
 *
@verbatim
                                        ----->/
 O                          O          /     /
  +---------------> X        +---------|-------------> X
  |    \    |                |         |   /  |
  |     \ <-' angle          |   angle \_ /__/
  |      \                   |           /
  |       + aPt1             |          + aPt2
  |        \                 |         ^
  |         \                |        /
  |          v               |       /
  v           + aPt2         v      + aPt1

  Y                          Y
@endverbatim
 *
 * @param aX1  X coordinate of point Pt1 (vector origin)
 * @param aY1  Y coordinate of point Pt1 (vector origin)
 * @param aX2  X coordinate of point Pt2 (vector extremity)
 * @param aY2  Y coordinate of point Pt2 (vector extremity)
 */
template <class T>
double
qgAngle(T aX1, T aY1, T aX2, T aY2);


/**
 * @ingroup GLOB_PRIM_ANG
 *
 * @brief Same as qgar::qgAngle(T,T,T,T).
 *
 * @param aPt1  point representing the vector origin
 * @param aPt2  point representing the vector extremity
 */
template <class T>
inline double
qgAngle(const GenPoint<T>& aPt1, const GenPoint<T>& aPt2);


/**
 * @ingroup GLOB_PRIM_ANG
 *
 * @brief Same as qgar::qgAngle(T,T,T,T),
 * but the result is delivered in degrees.
 *
 * @param aX1  X coordinate of point Pt1 (vector origin)
 * @param aY1  Y coordinate of point Pt1 (vector origin)
 * @param aX2  X coordinate of point Pt2 (vector extremity)
 * @param aY2  Y coordinate of point Pt2 (vector extremity)
 */
template <class T>
double
qgAngleDegrees(T aX1, T aY1, T aX2, T aY2);


/**
 * @ingroup GLOB_PRIM_ANG
 *
 * @brief Same as qgar::qgAngleDegrees(T,T,T,T).
 *
 * @param aPt1  point representing the vector origin
 * @param aPt2  point representing the vector extremity
 */
template <class T>
inline double
qgAngleDegrees(const GenPoint<T>& aPt1, const GenPoint<T>& aPt2);



// -------------------------------------------------------------------
// ANGLE BETWEEN 2 VECTORS
// -------------------------------------------------------------------



/**
 * @ingroup GLOB_PRIM_ANG
 *
 * @brief (Oriented) angle, in \f$[0, 2\pi[\f$ radians,
 * between 2 vectors defined by 3 points.
 *
@verbatim
 0
  +---------------------> X      +---------------------> X
  |                              |    ----
  |                              |   /    \
  | aPt1                         |   |     v
  |   +--------->+ aPt2          |   |  +------->+ aPt3
  |    \    |                    |   \ __\   
  |     \ <-'                    |        \
  |      \                       |         \
  |       v                      |          v   
  |        + aPt3                |           + aPt2
  v                              v

  Y                              Y
@endverbatim
 *
 * @param aX1  X coordinate of point Pt1 (origin of both vectors)
 * @param aY1  Y coordinate of point Pt1 (origin of both vectors)
 * @param aX2  X coordinate of point Pt2 (extremity of 1st vector)
 * @param aY2  Y coordinate of point Pt2 (extremity of 1st vector)
 * @param aX3  X coordinate of point Pt3 (extremity of 2nd vector)
 * @param aY3  Y coordinate of point Pt3 (extremity of 2nd vector)
 */
template <class T>
inline double
qgAngle(T aX1, T aY1, T aX2, T aY2, T aX3, T aY3);


/**
 * @ingroup GLOB_PRIM_ANG
 *
 * @brief Same as qgar::qgAngle(T,T,T,T,T,T)
 *
 * @param aPt1  point representing the origin of both vectors
 * @param aPt2  point representing the extremity of 1st vector
 * @param aPt3  point representing the extremity of 2nd vector
 */
template <class T>
inline double
qgAngle(const GenPoint<T>& aPt1,
	const GenPoint<T>& aPt2,
	const GenPoint<T>& aPt3);


/**
 * @ingroup GLOB_PRIM_ANG
 *
 * @brief Same as qgar::qgAngle(T,T,T,T,T,T),
 * but the result is delivered in \f$[0, 360[\f$ degrees.
 *
 * @param aX1  X coordinate of point Pt1 (origin of both vectors)
 * @param aY1  Y coordinate of point Pt1 (origin of both vectors)
 * @param aX2  X coordinate of point Pt2 (extremity of 1st vector)
 * @param aY2  Y coordinate of point Pt2 (extremity of 1st vector)
 * @param aX3  X coordinate of point Pt3 (extremity of 2nd vector)
 * @param aY3  Y coordinate of point Pt3 (extremity of 2nd vector)
 */
template <class T>
inline double
qgAngleDegrees(T aX1, T aY1, T aX2, T aY2, T aX3, T aY3);


/**
 * @ingroup GLOB_PRIM_ANG
 *
 * @brief Same as qgar::qgAngleDegrees(T,T,T,T,T,T).
 *
 * @param aPt1  point representing the origin of both vectors
 * @param aPt2  point representing the extremity of 1st vector
 * @param aPt3  point representing the extremity of 2nd vector
 */
template <class T>
inline double
qgAngleDegrees(const GenPoint<T>& aPt1,
	       const GenPoint<T>& aPt2,
	       const GenPoint<T>& aPt3);



/**
 * @ingroup GLOB_PRIM_ANG
 *
 * @brief (Oriented) angle, in \f$[0, 2\pi[\f$ radians,
 * between 2 vectors defined by 4 points.
 *
@verbatim
 0
  +----------------------> X      +-------------------------> X
  |                               |    ----
  |                               |   /    \
  |        aPt1                   |   |     v  aPt3
  |    \----+------>+ aPt2        |   |  \-----+------>+ aPt4
  |     \     |                   |   \ __\   
  | aPt3 +    |                   |        \
  |       \<--'                   |         + aPt1
  |        \                      |          \
  |         v                     |           v   
  |          + aPt4               |            + aPt2
  v                               v

  Y                               Y
@endverbatim
 *
 * @param aX1  X coordinate of point Pt1 (origin of 1st vectors)
 * @param aY1  Y coordinate of point Pt1 (origin of 1st vectors)
 * @param aX2  X coordinate of point Pt2 (extremity of 1st vector)
 * @param aY2  Y coordinate of point Pt2 (extremity of 1st vector)
 * @param aX3  X coordinate of point Pt3 (origin of 2nd vectors)
 * @param aY3  Y coordinate of point Pt3 (origin of 2nd vectors)
 * @param aX4  X coordinate of point Pt4 (extremity of 2nd vector)
 * @param aY4  Y coordinate of point Pt4 (extremity of 2nd vector)
 */
template <class T>
double
qgAngle(T aX1, T aY1, T aX2, T aY2, T aX3, T aY3, T aX4, T aY4);


/**
 * @ingroup GLOB_PRIM_ANG
 *
 * @brief Same as qgar::qgAngle(T,T,T,T,T,T,T,T).
 *
 * @param aPt1  point representing the origin of 1st vector
 * @param aPt2  point representing the extremity of 1st vector
 * @param aPt3  point representing the origin of 2nd vector
 * @param aPt4  point representing the extremity of 2nd vector
 */
template <class T>
inline double
qgAngle(const GenPoint<T>& aPt1,
	const GenPoint<T>& aPt2,
	const GenPoint<T>& aPt3,
	const GenPoint<T>& aPt4);


/**
 * @ingroup GLOB_PRIM_ANG
 *
 * @brief Same as qgar::qgAngle(T,T,T,T,T,T,T,T),
 * but the result is delivered in \f$[0, 360[\f$ degrees.
 *
 * @param aX1  X coordinate of point Pt1 (origin of 1st vectors)
 * @param aY1  Y coordinate of point Pt1 (origin of 1st vectors)
 * @param aX2  X coordinate of point Pt2 (extremity of 1st vector)
 * @param aY2  Y coordinate of point Pt2 (extremity of 1st vector)
 * @param aX3  X coordinate of point Pt3 (origin of 2nd vectors)
 * @param aY3  Y coordinate of point Pt3 (origin of 2nd vectors)
 * @param aX4  X coordinate of point Pt4 (extremity of 2nd vector)
 * @param aY4  Y coordinate of point Pt4 (extremity of 2nd vector)
 */
template <class T>
inline double
qgAngleDegrees(T aX1, T aY1,
	       T aX2, T aY2,
	       T aX3, T aY3,
	       T aX4, T aY4);


/**
 * @ingroup GLOB_PRIM_ANG
 *
 * @brief Same as qgar::qgAngleDegrees(T,T,T,T,T,T,T,T).
 *
 * @param aPt1  point representing the origin of 1st vector
 * @param aPt2  point representing the extremity of 1st vector
 * @param aPt3  point representing the origin of 2nd vector
 * @param aPt4  point representing the extremity of 2nd vector
 */
template <class T>
inline double
qgAngleDegrees(const GenPoint<T>& aPt1,
	       const GenPoint<T>& aPt2,
	       const GenPoint<T>& aPt3,
	       const GenPoint<T>& aPt4);



// -------------------------------------------------------------------
// ANGLE BETWEEN A SEGMENT AND THE X AXIS
// -------------------------------------------------------------------



/**
 * @ingroup GLOB_PRIM_ANG
 *
 * @brief (Non-oriented) angle, in \f$[0, \pi[\f$ radians,
 * between the segment defined by 2 points and the X axis.
 *
@verbatim
 O                          O
  +-----------------> X      +-----------------> X
  |    \    |                |    \    |
  |     \ <-' angle          |     \ <-' angle
  |      \                   |      \
  |       + aPt1             |       + aPt2
  |        \                 |        \
  |         \                |         \
  |          \               |          \
  v           + aPt2         v           + aPt1

  Y                          Y
@endverbatim
 *
 * @param aX1  X coordinate of point Pt1
 * @param aY1  Y coordinate of point Pt1
 * @param aX2  X coordinate of point Pt2
 * @param aY2  Y coordinate of point Pt2
 */
template <class T>
double
qgSlope(T aX1, T aY1, T aX2, T aY2);


/**
 * @ingroup GLOB_PRIM_ANG
 *
 * @brief Same as qgar::qgSlope(T,T,T,T).
 *
 * @param aPt1  a point
 * @param aPt2  a point
 */
template <class T>
inline double
qgSlope(const GenPoint<T>& aPt1, const GenPoint<T>& aPt2);



/**
 * @ingroup GLOB_PRIM_ANG
 *
 * @brief Same as qgar::qgSlope(T,T,T,T),
 * but the result is delivered in \f$[0, 180[\f$ degrees.
 *
 * @param aX1  X coordinate of point Pt1
 * @param aY1  Y coordinate of point Pt1
 * @param aX2  X coordinate of point Pt2
 * @param aY2  Y coordinate of point Pt2
 */
template <class T>
inline double
qgSlopeDegrees(T aX1, T aY1, T aX2, T aY2);


/**
 * @ingroup GLOB_PRIM_ANG
 *
 * @brief Same as qgar::qgSlopeDegrees(T,T,T,T).
 *
 * @param aPt1  a point
 * @param aPt2  a point
 */
template <class T>
inline double
qgSlopeDegrees(const GenPoint<T>& aPt1, const GenPoint<T>& aPt2);


//@}



/*-------------------------------------------------------------------*
 |                                                                   |
 *-------------------------------------------------------------------*/



} // namespace qgar


#endif /* ___QGAR_GLOBALPRIMITIVEFUNCTIONS_H_INCLUDED__ */
