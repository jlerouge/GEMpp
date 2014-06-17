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


#ifndef ___QGAR_TRANSLATION_H_INCLUDED__
#define ___QGAR_TRANSLATION_H_INCLUDED__


/**
 * @file   _QGAR_translation.h
 * @brief  Global functions to perform translations.
 *
 * @warning <b>Not to be used as include file!</b>
 * <br>When working with primitives, use header file primitives.h.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   February 10 2005,  19:44
 * @since  Qgar 2.2
 */


// For RCS/CVS use: Do not delete
/* $Id: _QGAR_translation.h,v 1.2 2005/09/14 10:53:19 masini Exp $ */



namespace qgar
{


/**
 * @name Global functions to translate points and primitives
 */
//@{


// -------------------------------------------------------------------
// T R A N S L A T I O N   O F   A   P O I N T
// -------------------------------------------------------------------


/**
 * @ingroup GLOB_PRIM_TRANS
 *
 * @brief Return the given point translated along X and Y axis.
 *
 * @param aPt      point to be translated
 * @param aTransX  X translation factor
 * @param aTransY  Y translation factor
 */
template <class T>
inline GenPoint<T>
qgTranslatedPoint(const GenPoint<T>& aPt, T aTransX, T aTransY);


// -------------------------------------------------------------------
// T R A N S L A T I O N   O F   A   S E G M E N T
// -------------------------------------------------------------------


/**
 * @ingroup GLOB_PRIM_TRANS
 *
 * @brief Return the given segment translated along X and Y axis.
 *
 * @param aSeg     segment to be translated
 * @param aTransX  X translation factor
 * @param aTransY  Y translation factor
 */
template <class T>
inline GenSegment<T>
qgTranslatedSegment(const GenSegment<T>& aSeg, T aTransX, T aTransY);


// -------------------------------------------------------------------
// T R A N S L A T I O N   O F   A N   A R C
// -------------------------------------------------------------------


/**
 * @ingroup GLOB_PRIM_TRANS
 *
 * @brief Return the given arc translated along X and Y axis.
 *
 * @param anArc    arc to be translated
 * @param aTransX  X translation factor
 * @param aTransY  Y translation factor
 */
template <class T>
inline GenArc<T>
qgTranslatedArc(const GenArc<T>& anArc, T aTransX, T aTransY);


// -------------------------------------------------------------------
// T R A N S L A T I O N   O F   A   P O L Y G O N
// -------------------------------------------------------------------


/**
 * @ingroup GLOB_PRIM_TRANS
 *
 * @brief Return the given polygon translated along X and Y axis.
 *
 * @param aPolygon  polygon to be translated
 * @param aTransX   X translation factor
 * @param aTransY   Y translation factor
 */
template <class T>
inline GenPolygon<T>
qgTranslatedPolygon(const GenPolygon<T>& aPolygon, T aTransX, T aTransY);


// -------------------------------------------------------------------
// T R A N S L A T I O N   O F   A   P O L Y L I N E
// -------------------------------------------------------------------


/**
 * @ingroup GLOB_PRIM_TRANS
 *
 * @brief Return the given polyline translated along X and Y axis.
 *
 * @param aPolyline  polyline to be translated
 * @param aTransX    X translation factor
 * @param aTransY    Y translation factor
 */
  template <class T>
  GenPolyline<T>
  qgTranslatedPolyline(const GenPolyline<T>& aPolyline, T aTransX, T aTransY);


// -------------------------------------------------------------------


//@}


} // namespace qgar


#endif /* ___QGAR_TRANSLATION_H_INCLUDED__ */
