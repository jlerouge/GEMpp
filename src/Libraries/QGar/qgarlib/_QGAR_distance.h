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


#ifndef ___QGAR_DISTANCE_H_INCLUDED__
#define ___QGAR_DISTANCE_H_INCLUDED__


/**
 * @file   _QGAR_distance.h
 * @brief  Global functions to compute distances between primitives.
 *
 * @warning <b>Not to be used as include file!</b>
 * <br>When working with primitives, use header file primitives.h.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   February 03 2005,  17:44
 * @since  Qgar 2.2
 */


// For RCS/CVS use: Do not delete
/* $Id: _QGAR_distance.h,v 1.3 2005/11/23 17:08:31 masini Exp $ */



namespace qgar
{


/*-------------------------------------------------------------------*
 |                                                                   |
 |      GLOBAL FUNCTIONS TO COMPUTE DISTANCES BETWEEN PRIMITIVES     |
 |                                                                   |
 *-------------------------------------------------------------------*/


/** @name Global functions to compute distances between primitives */
//        ========================================================
//@{


/**
 * @ingroup GLOB_PRIM_DIST
 *
 * @brief Difference between X coordinates of the given points:
 *   <b>X(aPt1) - X(aPt2)</b>.
 *
 * @param aPt1  a point
 * @param aPt2  a point
 */
template <class T>
inline T
qgDX(const GenPoint<T>& aPt1, const GenPoint<T>& aPt2);


/**
 * @ingroup GLOB_PRIM_DIST
 *
 * @brief Difference between Y coordinates of the given points:
 *  <b>Y(aPt1) - Y(aPt2)</b>.
 *
 * @param aPt1  a point
 * @param aPt2  a point
 */
template <class T>
inline T
qgDY(const GenPoint<T>& aPt1, const GenPoint<T>& aPt2);


/**
 * @ingroup GLOB_PRIM_DIST
 *
 * @brief Distance between two points.
 *
 * @param aPt1  a point
 * @param aPt2  a point
 */
template <class T>
inline double
qgDist(const GenPoint<T>& aPt1, const GenPoint<T>& aPt2);


/**
 * @ingroup GLOB_PRIM_DIST
 *
 * @brief Distance between two points.
 *
 * @param aX1  X coordinate of the first point
 * @param aY1  Y coordinate of the first point
 * @param aX2  X coordinate of the second point
 * @param aY2  Y coordinate of the second point
 */
template <class T>
double
qgDist(T aX1, T aY1, T aX2, T aY2);


/**
 * @ingroup GLOB_PRIM_DIST
 *
 * @brief Distance between point <b>c</b> and its a perpendicular
 *   projection onto the line passing through points
 *  <b>a</b> and <b>b</b>.
 *
 * @param c  a point
 * @param a  a point
 * @param b  a point
 */
template <class T>
double
qgDist(const GenPoint<T>& c,
       const GenPoint<T>& a,
       const GenPoint<T>& b);


/**
 * @ingroup GLOB_PRIM_DIST
 *
 * @brief Distance between point <b>(0,0)</b> and its perpendicular
 *   projection onto the line supporting a segment.
 *
 * Always positive.
 *
 * @param aSeg  a segment
 */
template <class T>
inline double
qgDist(const GenSegment<T>& aSeg);


/**
 * @ingroup GLOB_PRIM_DIST
 *
 * @brief Distance between point <b>(0,0)</b> and its perpendicular
 *   projection onto the line supporting a Qgar segment.
 *
 * Always positive.
 *
 * @param aQSeg  a Qgar segment
 */
template <class T>
inline double
qgDist(const GenQgarSegment<T>& aQSeg);


/**
 * @ingroup GLOB_PRIM_DIST
 *
 * @brief Distance between a point and its perpendicular
 *   projection onto the line supporting a segment.
 *
 * Always positive.
 *
 * @param aPt   a point
 * @param aSeg  a segment
 */
template <class T>
inline double
qgDist(const GenPoint<T>& aPt, const GenSegment<T>& aSeg);


/**
 * @ingroup GLOB_PRIM_DIST
 *
 * @brief Distance between a point and its perpendicular
 *   projection onto the line supporting a segment.
 *
 * Always positive.
 *
 * @param aX    X coordinate of the point
 * @param aY    Y coordinate of the point
 * @param aSeg  a segment
 */
template <class T>
inline double
qgDist(T aX, T aY, const GenSegment<T>& aSeg);


/**
 * @ingroup GLOB_PRIM_DIST
 *
 * @brief Distance between a point and its perpendicular
 *   projection onto the line supporting a Qgar segment.
 *
 * Always positive.
 *
 * @param c      a point
 * @param aQSeg  a Qgar segment
 */
template <class T>
inline double
qgDist(const GenPoint<T>& c, const GenQgarSegment<T>& aQSeg);


/**
 * @ingroup GLOB_PRIM_DIST
 *
 * @brief Distance between a point and its perpendicular
 *   projection onto the line supporting a Qgar segment.
 *
 * Always positive.
 *
 * @param aX     X coordinate of the point
 * @param aY     Y coordinate of the point
 * @param aQSeg  a Qgar segment
 */
template <class T>
inline double
qgDist(T aX, T aY, const GenQgarSegment<T>& aQSeg);


/**
 * @ingroup GLOB_PRIM_DIST
 *
 * @brief Squared distance between two points.
 *
 * @param aPt1  a point
 * @param aPt2  a point
 */
template <class T>
inline double
qgSqr_dist(const GenPoint<T>& aPt1, const GenPoint<T>& aPt2);


/**
 * @ingroup GLOB_PRIM_DIST
 *
 * @brief Squared distance between two points.
 *
 * @param aX1  X coordinate of the first point
 * @param aY1  Y coordinate of the first point
 * @param aX2  X coordinate of the second point
 * @param aY2  Y coordinate of the second point
 */
template <class T>
double
qgSqr_dist(T aX1, T aY1, T aX2, T aY2);


//@}


/*-------------------------------------------------------------------*
 |                                                                   |
 *-------------------------------------------------------------------*/


} // namespace qgar


#endif /* ___QGAR_DISTANCE_H_INCLUDED__ */
