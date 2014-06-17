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
 * @file   _QGAR_translation.tcc
 * @brief  Implementation of global functions to translate primitives.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date    February 9, 2005  14:32
 * @since   Qgar 2.2
 */



// STD
#include <deque>



namespace qgar
{


// -------------------------------------------------------------------
// T R A N S L A T I O N   O F   A   P O I N T
// -------------------------------------------------------------------


// RETURN THE GIVEN POINT TRANSLATED ALONG X AND Y AXIS

template <class T>
inline GenPoint<T>
qgTranslatedPoint(const GenPoint<T>& aPt, T aTransX, T aTransY)
{
  return (GenPoint<T>(aPt)).translate(aTransX, aTransY);
}


// -------------------------------------------------------------------
// T R A N S L A T I O N   O F   A   S E G M E N T
// -------------------------------------------------------------------


// RETURN THE GIVEN SEGMENT TRANSLATED ALONG X AND Y AXIS


template <class T>
inline GenSegment<T>
qgTranslatedSegment(const GenSegment<T>& aSeg, T aTransX, T aTransY)
{
  return (GenSegment<T>(aSeg)).translate(aTransX, aTransY);
}


// -------------------------------------------------------------------
// T R A N S L A T I O N   O F   A N   A R C
// -------------------------------------------------------------------


// RETURN THE GIVEN ARC TRANSLATED ALONG X AND Y AXIS


template <class T>
inline GenArc<T>
qgTranslatedArc(const GenArc<T>& anArc, T aTransX, T aTransY)
{
  return (GenArc<T>(anArc)).translate(aTransX, aTransY);
}


// -------------------------------------------------------------------
// T R A N S L A T I O N   O F   A   P O L Y G O N
// -------------------------------------------------------------------


// RETURN THE GIVEN POLYGON TRANSLATED ALONG X AND Y AXIS


template <class T>
inline GenPolygon<T>
qgTranslatedPolygon(const GenPolygon<T>& aPoly, T aTransX, T aTransY)
{
  return (GenPolygon<T>(aPoly)).translate(aTransX, aTransY);
}


// -------------------------------------------------------------------
// T R A N S L A T I O N   O F   A   P O L Y L I N E
// -------------------------------------------------------------------


// RETURN THE GIVEN POLYLINE TRANSLATED ALONG X AND Y AXIS


template <class T>
GenPolyline<T>
qgTranslatedPolyline(const GenPolyline<T>& aPoly, T aTransX, T aTransY)
{
  return (GenPolyline<T>(aPoly)).translate(aTransX, aTransY);
}


// -------------------------------------------------------------------


} // namespace qgar
