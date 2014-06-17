/*---------------------------------------------------------------------*
 | Library QgarLib, graphics analysis and recognition                  |
 | Copyright (C) 2004  Qgar Project, LORIA                             |
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
 | http://www.gnu.org/licenses/lgpl.html for the terms of the license. |
 | To receive a paper copy, write to the Free Software Foundation,     |
 | Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.       |
 |                                                                     |
 | Contact Project Qgar for any information:                           |
 |   LORIA - équipe Qgar                                               |
 |   B.P. 239, 54506 Vandoeuvre-lès-Nancy Cedex, France                |
 |   email: qgar-contact@loria.fr                                      |
 |   http://www.qgar.org/                                              |
 *---------------------------------------------------------------------*/



#ifndef __PRIMITIVES_H_INCLUDED__
#define __PRIMITIVES_H_INCLUDED__


/**
 * @file   primitives.h
 * @brief  Header file for the classes defining primitives.
 *
 * @warning This header, and only this header file, must be used for:
 *
 * - points, defined by class
 *     qgar::GenPoint,
 * - any geometrical primitives, defined by classes
 *     qgar::AbstractGenPrimitive,
 *     qgar::GenArc,
 *     qgar::GenPolygon,
 *     qgar::GenPolyline,
 *     qgar::GenSegment,
 * - any graphical (Qgar) primitives, defined by classes
 *     qgar::AbstractGenQgarPrimitive,
 *     qgar::GenQgarArc,
 *     qgar::GenQgarPolygon,
 *     qgar::GenQgarPolyline,
 *     qgar::GenQgarSegment.
 *
 * Some global functions, exclusively dealing with points and primitives,
 * are also provided. They compute:
 *
 * - angles between vectors
 *   (see module <a href="group__GLOB__PRIM__ANG.html" target="_blank">Angles</a>)
 * - distances between primitives
 *   (see module <a href="group__GLOB__PRIM__DIST.html" target="_blank">Distances</a>)
 * - points
 *   (see module <a href="group__GLOB__PRIM__PT.html" target="_blank">Points</a>)
 * - segments
 *   (see module <a href="group__GLOB__PRIM__SEG.html" target="_blank">Segments</a>)
 * - translations
 *   (see module <a href="group__GLOB__PRIM__TRANS.html" target="_blank">Translations</a>)
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   December 14, 2004  14:25
 * @since  Qgar 2.2
 */



// For RCS/CVS use: Do not delete.
/* $Id: primitives.h,v 1.3 2005/09/14 10:53:19 masini Exp $ */



// -------------------------------------------------------------------
// T O   R E S O L V E   F O R W A R D   D E C L A R A T I O N S 
// -------------------------------------------------------------------


namespace qgar
{


// POINTS

template <class T> class GenPoint;

// PRIMITIVES

template <class T> class AbstractGenPrimitive;
template <class T> class GenArc;
template <class T> class GenPolygon;
template <class T> class GenPolyline;
template <class T> class GenSegment;

// Qgar PRIMITIVES

template <class T> class AbstractGenQgarPrimitive;
template <class T> class GenQgarArc;
template <class T> class GenQgarPolygon;
template <class T> class GenQgarPolyline;
template <class T> class GenQgarSegment;


} // namespace qgar


// -------------------------------------------------------------------
// D  E  F  I  N  I  T  I  O  N  S
// -------------------------------------------------------------------


// TYPES RELATED TO PRIMITIVES
// ===========================

#include "_QGAR_primitiveTypes.h"


// GLOBAL FUNCTIONS FOR PRIMITIVES
// ===============================

// Utilities

#include "_QGAR_angle.h"
#include "_QGAR_distance.h"
#include "_QGAR_point.h"
#include "_QGAR_segment.h"

// Geometry

#include "_QGAR_translation.h"


// POINTS
// ======

#include "_QGAR_GenPoint.h"


// GEOMETRICAL PRIMITIVES
// ======================

#include "_QGAR_AbstractGenPrimitive.h"
#include "_QGAR_GenArc.h"
#include "_QGAR_GenPolygon.h"
#include "_QGAR_GenPolyline.h"
#include "_QGAR_GenSegment.h"


// GRAPHICAL (Qgar) PRIMITIVES
// ===========================

#include "_QGAR_AbstractGenQgarPrimitive.h"
#include "_QGAR_GenQgarArc.h"
#include "_QGAR_GenQgarPolygon.h"
#include "_QGAR_GenQgarPolyline.h"
#include "_QGAR_GenQgarSegment.h"


// -------------------------------------------------------------------
// I  M  P  L  E  M  E  N  T  A  T  I  O  N  S
// -------------------------------------------------------------------


// GLOBAL FUNCTIONS FOR PRIMITIVES
// ===============================

// Utilities

#include "_QGAR_angle.tcc"
#include "_QGAR_distance.tcc"
#include "_QGAR_point.tcc"
#include "_QGAR_segment.tcc"

// Geometry

#include "_QGAR_translation.tcc"


// POINTS
// ======

#include "_QGAR_GenPoint.tcc"


// GEOMETRICAL PRIMITIVES
// ======================

#include "_QGAR_AbstractGenPrimitive.tcc"
#include "_QGAR_GenArc.tcc"
#include "_QGAR_GenPolygon.tcc"
#include "_QGAR_GenPolyline.tcc"
#include "_QGAR_GenSegment.tcc"


// GRAPHICAL (Qgar) PRIMITIVES
// ===========================

#include "_QGAR_AbstractGenQgarPrimitive.tcc"
#include "_QGAR_GenQgarArc.tcc"
#include "_QGAR_GenQgarPolygon.tcc"
#include "_QGAR_GenQgarPolyline.tcc"
#include "_QGAR_GenQgarSegment.tcc"



#endif /* __PRIMITIVES_H_INCLUDED__ */
