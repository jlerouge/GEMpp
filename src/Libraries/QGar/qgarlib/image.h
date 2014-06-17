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


#ifndef __IMAGE_H_INCLUDED__
#define __IMAGE_H_INCLUDED__


/**
 * @file   image.h
 * @brief  Definitions of global utilities for image processing.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   December 07 2004  17:48
 * @since  Qgar 2.2
 */


// For RCS/CVS use: Do not delete
/* $Id: image.h,v 1.7 2007/02/14 17:34:06 masini Exp $ */



// QGAR
#include "QgarErrorDomain.h"
#include "QgarErrorInvalidArg.h"



namespace qgar
{

// -------------------------------------------------------------------
// T Y P E S
// -------------------------------------------------------------------


/** 
 * @name Types related to image processing
 */
//@{

/**
 * @ingroup GLOB_IMG
 *
 * @brief Coordinate axes.
 */
enum QGEaxis
{
  QGE_AXIS_X,
  QGE_AXIS_Y
};


/**
 * @ingroup GLOB_IMG
 *
 * @brief Binary pixel type (black & white)
 */
enum QGEbw
{
  QGE_BW_WHITE,
  QGE_BW_BLACK
};


/**
 * @ingroup GLOB_IMG
 *
 * @brief The 8 cardinal directions.
 *
 * @warning As the origin of the coordinates system in images
 * is at top left corner, North and South are upside down
 * for more convenience:
@verbatim
  (0,0) +---------------------------------------------> X
        |
        |                 QGE_DIRECTION_N
        |                        |  
        |     QGE_DIRECTION_NW \ | / QGE_DIRECTION_NE
        |                       \|/
        |   QGE_DIRECTION_W -----+----- QGE_DIRECTION_E
        |                       /|\
        |     QGE_DIRECTION_SW / | \ QGE_DIRECTION_SE
        |                        |
        |                 QGE_DIRECTION_S
      Y V
@endverbatim
 */
enum QGEdirection
{
  QGE_DIRECTION_N  = 0,
  QGE_DIRECTION_NE = 1,
  QGE_DIRECTION_E  = 2,
  QGE_DIRECTION_SE = 3,
  QGE_DIRECTION_S  = 4,
  QGE_DIRECTION_SW = 5,
  QGE_DIRECTION_W  = 6,
  QGE_DIRECTION_NW = 7 
};


/**
 * @ingroup GLOB_IMG
 *
 * @brief Orientations (of a line/segment).
 *
@verbatim
QGE_ORIENTATION_VER           
       |
    \  |  QGE_ORIENTATION_DIAG_POS
     \ | /
      \|/
 ------+------ QGE_ORIENTATION_HOR
      /|\
     / | \
    /  |  QGE_ORIENTATION_DIAG_NEG
@endverbatim
 */
enum QGEorientation
{
  QGE_ORIENTATION_HOR,
  QGE_ORIENTATION_DIAG_POS,
  QGE_ORIENTATION_VER,
  QGE_ORIENTATION_DIAG_NEG,
  QGE_ORIENTATION_ALL
};


/**
 * @ingroup GLOB_IMG
 *
 * @brief Relative positions.
 */
enum QGEposition
{
  QGE_POSITION_TOP,
  QGE_POSITION_RIGHT,
  QGE_POSITION_BOTTOM,
  QGE_POSITION_LEFT
};


/**
 * @ingroup GLOB_IMG
 *
 * @brief Pixel connectivity.
 *
@verbatim
       8 8 8                    x 4 x
       8 c 8                    4 c 4
       8 8 8                    x 4 x

   8-connectivity           4-connectivity
@endverbatim
 *
 * <ul>
 * <li>
 * 8-connectivity (qgar::QGE_CONNECTIVITY_8):
 * the central point (<b>c</b>) is connected
 * to all its neighbors (marked <b>8</b>).
 * </li>
 * <li>
 * 4-connectivity (qgar::QGE_CONNECTIVITY_4):
 * the central point (<b>c</b>) is connected to its 4 neighbors marked
 * <b>4</b>, and is <i>not connected</i> to its 4 neighbors marked <b>x</b>.
 * </li>
 * </ul>
 */
enum QGEconnectivity
{
  QGE_CONNECTIVITY_DEFAULT,
  QGE_CONNECTIVITY_4,
  QGE_CONNECTIVITY_8
};


//@}


// -------------------------------------------------------------------
// F U N C T I O N S   F O R   B L A C K  &  W H I T E
// -------------------------------------------------------------------


/** 
 * @name Global functions for black & white.
 */
//@{


/**
 * @ingroup GLOB_COLOR
 *
 * @brief Conversion
 *   from qgar::QGEbw (black & white) to <b>integer</b>.
 * Return <b>1</b> for qgar::QGE_BW_BLACK,
 *
 * and <b>0</b> for qgar::QGE_BW_WHITE.
 *
 * @param aBW  black or white (qgar::QGEbw)
 */
inline int
qgBWtoInt(QGEbw aBW)
{
  return (aBW == QGE_BW_BLACK) ? 1 : 0;
}


/**
 * @ingroup GLOB_COLOR
 *
 * @brief Dual-conversion
 *   from qgar::QGEbw (black & white) to <b>integer</b>.
 *
 * Return <b>0</b> for qgar::QGE_BW_BLACK,
 * and <b>1</b> for qgar::QGE_BW_WHITE.
 *
 * @param aBW  black or white (qgar::QGEbw)
 */
inline int
qgBWrevInt(QGEbw aBW)
{
  return (aBW == QGE_BW_BLACK) ? 0 : 1;
}


/**
 * @ingroup GLOB_COLOR
 *
 * @brief Conversion
 *   from <b>integer</b> to qgar::QGEbw (black & white).
 *
 * If the given number is <b>0</b>, return qgar::QGE_BW_WHITE,
 * else return qgar::QGE_BW_BLACK.
 *
 * @param anInt  an integer
 */
inline QGEbw
qgIntToBW(int anInt)
{
  return (anInt == 0) ? QGE_BW_WHITE : QGE_BW_BLACK;
}


/**
 * @ingroup GLOB_COLOR
 *
 * @brief Dual-conversion
 *   from <b>integer</b> to qgar::QGEbw (black & white).
 *
 * If the given number is <b>0</b>, return qgar::QGE_BW_BLACK,
 * else return qgar::QGE_BW_WHITE.
 *
 * @param anInt  an integer
 */
inline QGEbw
qgIntToWB(int anInt)
{
  return (anInt == 0) ? QGE_BW_BLACK : QGE_BW_WHITE;
}


/**
 * @ingroup GLOB_COLOR
 *
 * @brief Switch between black and white.
 *
 * Return qgar::QGE_BW_WHITE for QGE_BW_BLACK,
 * and QGE_BW_BLACK for qgar::QGE_BW_WHITE.
 *
 * @param aBW  black or white
 */
inline QGEbw
qgBWswitch(QGEbw aBW)
{
  return (aBW == QGE_BW_WHITE) ? QGE_BW_BLACK : QGE_BW_WHITE;
}


//@}


// -------------------------------------------------------------------
// F U N C T I O N S   F O R   D I R E C T I O N S
// -------------------------------------------------------------------


// ===================================================================
/** 
 * @name Global functions for directions
 *
@verbatim
  (0,0) +--------------------------------------------->  X
        |
        |                 QGE_DIRECTION_N
        |                        |  
        |     QGE_DIRECTION_NW \ | / QGE_DIRECTION_NE
        |                       \|/
        |   QGE_DIRECTION_W -----+----- QGE_DIRECTION_E
        |                       /|\
        |     QGE_DIRECTION_SW / | \ QGE_DIRECTION_SE
        |                        |
        |                 QGE_DIRECTION_S
     Y  V
@endverbatim
 *
 */
// ===================================================================
//@{


/**
 * @ingroup GLOB_IMG
 *
 * @brief Return the direction corresponding to a (X,Y) translation.
 *
 * @param aDx  X translation
 * @param aDy  Y translation
 *
 * @warning
 * The translation must be defined according to one of the 8 Freeman
 * directions, precisely, that is to say, if aDx and aDy are both
 * different from 0, <b>|aDx|</b> must be equal to <b>|aDy|</b>.
 * Otherwise, the correctness of the the result is not guaranteed.
 *
 * @exception qgar::QgarErrorDomain  arguments are 0's
 */
qgar::QGEdirection qgDirection(int aDx, int aDy)
 ;


/**
 * @ingroup GLOB_IMG
 *
 * @brief Return the opposite direction of a given direction.
 *
 * @param aDir  a direction
 *
 * @exception qgar::QgarErrorInvalidArg  unknown direction
 */
qgar::QGEdirection qgOpposite(qgar::QGEdirection aDir)
 ;


//@}


// -------------------------------------------------------------------

} // namespace qgar


#endif /* __IMAGE_H_INCLUDED__ */
