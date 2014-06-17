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


#ifndef ___QGAR_POINT_H_INCLUDED__
#define ___QGAR_POINT_H_INCLUDED__


/**
 * @file   _QGAR_point.h
 * @brief  Global geometrical functions which compute points.
 *
 * @warning <b>Not to be used as include file!</b>
 * <br>When working with primitives, use header file primitives.h.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   February 03 2005,  18:44
 * @since  Qgar 2.2
 */


// For RCS/CVS use: Do not delete
/* $Id: _QGAR_point.h,v 1.3 2005/10/14 17:05:48 masini Exp $ */




// QGAR
#include "math.h"



namespace qgar
{


/**
 * @name Global geometrical functions which compute points
 */
//@{


// -------------------------------------------------------------------
// A R C S   A N D   C I R C L E S
// -------------------------------------------------------------------


/**
 * @ingroup GLOB_PRIM_PT
 *
 * @brief Center of the circle passing through three given points.
 *
 * Return <b>false</b> if the 3 points are collinear,
 * <b>true</b> otherwise.
 *
 * @param t        a point
 * @param p        a point
 * @param q        a point
 * @param aCenter  center of the circle
 *
 * @warning The center has <b>double</b> coordinates.
 */
template <class T>
bool
qgCircleCenter(const GenPoint<T>& t,
	       const GenPoint<T>& p,
	       const GenPoint<T>& q,
	       GenPoint<double>&  aCenter);


// -------------------------------------------------------------------
// I N T E R S E C T I O N S
// -------------------------------------------------------------------


/**
 * @ingroup GLOB_PRIM_PT
 *
 * @brief Intersection of the lines supporting two given segments.
 *
 * Return <b>false</b> if the lines supporting the segments are
 * approximately collinear/parallel according to threshold <b>anAngle</b>.
 * Otherwise, assign the intersection point to <b>i</b> and return
 * <b>true</b>.
 *
 * @param ab  a segment (AB)
 * @param cd  a segment (CD)
 * @param i   resulting intersection point (I)
 * @param anAngle  threshold angle to decide whether current and given
 *   segments are collinear or parallel (default qgar::Math::epsilonRadian())
 *
 * @warning The intersection point has <b>double</b> coordinates.
 */
template <class T>
bool
qgIntersect(const GenSegment<T>& ab,
	    const GenSegment<T>& cd,
	    GenPoint<double>& i,
	    double anAngle = Math::epsilonRadian());


/**
 * @ingroup GLOB_PRIM_PT
 *
 * @brief Intersection of the lines supporting two given Qgar segments.
 *
 * Return <b>false</b> if the lines supporting the segments are
 * approximately collinear/parallel according to threshold <b>anAngle</b>.
 * Otherwise, assign the intersection point to <b>i</b> and return
 * <b>true</b>.
 *
 * @param aQSeg1   a Qgar segment
 * @param aQSeg2   a Qgar segment
 * @param aPt      resulting intersection point
 * @param anAngle  threshold angle to decide whether current and given
 *   segments are collinear or parallel (default qgar::Math::epsilonRadian())
 *
 * @warning The intersection point has <b>double</b> coordinates.
 */
template <class T>
inline bool
qgIntersect(const GenQgarSegment<T>& aQSeg1,
	    const GenQgarSegment<T>& aQSeg2,
	    GenPoint<double>& aPt,
	    double anAngle = Math::epsilonRadian());


// -------------------------------------------------------------------
// M I D D L E   P O I N T S
// -------------------------------------------------------------------


/**
 * @ingroup GLOB_PRIM_PT
 *
 * @brief Return the middle point of a segment.
 *
 * @param aSeg  a segment
 *
 * @warning The resulting point has <b>double</b> coordinates.
 */
template <class T>
inline GenPoint<double>
qgMiddle(const GenSegment<T>& aSeg);


/**
 * @ingroup GLOB_PRIM_PT
 *
 * @brief Return the middle point of a Qgar segment.
 *
 * @param aQSeg  a Qgar segment
 *
 * @warning The resulting point has <b>double</b> coordinates.
 */
template <class T>
inline GenPoint<double>
qgMiddle(const GenQgarSegment<T>& aQSeg);


/**
 * @ingroup GLOB_PRIM_PT
 *
 * @brief Return the middle point of the segment joining two points.
 *
 * @param aPt1  a point
 * @param aPt2  a point
 *
 * @warning The resulting point has <b>double</b> coordinates.
 */
template <class T>
inline GenPoint<double>
qgMiddle(const GenPoint<T>& aPt1, const GenPoint<T>& aPt2);


// -------------------------------------------------------------------
// P R O J E C T I O N S
// -------------------------------------------------------------------


/**
 * @ingroup GLOB_PRIM_PT
 *
 * @brief Return the orthogonal projection of a point onto a segment.
 *
 * @param aPt   a point
 * @param aSeg  a segment
 *
 * @warning The resulting point has <b>double</b> coordinates.
 * @since Qgar 2.2
 */
template <class T>
GenPoint<double>
qgProjectPoint(const GenPoint<T>& aPt, const GenSegment<T>& aSeg);


/**
 * @ingroup GLOB_PRIM_PT
 *
 * @brief Orthogonal projection of a point onto a segment.
 *
 * @param aPt   a point
 * @param aSeg  a segment
 *
 * @warning The point has <b>double</b> coordinates.
 * @since Qgar 2.2
 */
template <class T>
inline void
qgProject(GenPoint<double>& aPt, const GenSegment<T>& aSeg);


/**
 * @ingroup GLOB_PRIM_PT
 *
 * @brief Return the orthogonal projection of a point
 *   onto a Qgar segment.
 *
 * @param aPt    a point
 * @param aQSeg  a Qgar segment
 *
 * @warning The resulting point has <b>double</b> coordinates.
 * @since Qgar 2.2
 */
template <class T>
inline GenPoint<double>
qgProjectPoint(const GenPoint<T>& aPt, const GenQgarSegment<T>& aQSeg);


/**
 * @brief Ortogonal projection of a point onto a Qgar segment.
 *
 * @param aPt    a point
 * @param aQSeg  a Qgar segment
 *
 * @warning The point has <b>double</b> coordinates.
 * @since Qgar 2.2
 */
template <class T>
inline void
qgProject(GenPoint<double>& aPt, const GenQgarSegment<T>& aQSeg);


// -------------------------------------------------------------------


//@}


} // namespace qgar


#endif /* ___QGAR_POINT_H_INCLUDED__ */
