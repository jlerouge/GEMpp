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


#ifndef ___QGAR_SEGMENT_H_INCLUDED__
#define ___QGAR_SEGMENT_H_INCLUDED__


/**
 * @file   _QGAR_segment.h
 * @brief  Global functions which compute segments.
 *
 * @warning <b>Not to be used as include file!</b>
 * <br>When working with primitives, use header file primitives.h.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   February 03 2005,  19:19
 * @since  Qgar 2.2
 */


// For RCS/CVS use: Do not delete
/* $Id: _QGAR_segment.h,v 1.2 2005/09/14 10:53:19 masini Exp $ */



namespace qgar
{


/** 
 * @name Global functions which compute segments
 */
//@{


// -------------------------------------------------------------------
// P E R P E N D I C U L A R
// -------------------------------------------------------------------


/**
 * @ingroup GLOB_PRIM_SEG
 *
 * @brief Return a segment perpendicular to the given segment.
 *
 * Its source is the given point, its target is the orthogonal
 * projection of the given point onto the line supporting
 * the given segment.
 *
 * @param aPt   a point
 * @param aSeg  a segment
 *
 * @warning The resulting segment has <b>double</b> coordinates.
 */
template <class T>
inline GenSegment<double>
qgPerpendicular(const GenPoint<T>& aPt, const GenSegment<T>& aSeg);


/**
 * @ingroup GLOB_PRIM_SEG
 *
 * @brief Return a Qgar segment perpendicular to the given Qgar segment.
 *
 * Its source is the given point, its target is the orthogonal
 * projection of the given point onto the line supporting
 * the given segment.
 * Its color, thickness and outline are those of the given segment.
 *
 * @param aPt    a point
 * @param aQSeg  a Qgar segment
 *
 * @warning The resulting Qgar segment has <b>double</b> coordinates.
 */
template <class T>
inline GenQgarSegment<double>
qgPerpendicular(const GenPoint<T>& aPt,	const GenQgarSegment<T>& aQSeg);


// -------------------------------------------------------------------


//@}


} // namespace qgar


#endif /* ___QGAR_SEGMENT_H_INCLUDED__ */
