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


/**
 * @file  image.cpp
 * @brief Implementation of global utilities for image processing.
 *
 *        See file image.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   December 06 2004,  17:13
 * @since  Qgar 2.2
 */



// STD
#include <sstream>
// QGAR
#include "image.h"
#include "QgarErrorDomain.h"
#include "QgarErrorInvalidArg.h"



using namespace std;



namespace qgar
{

// -------------------------------------------------------------------
// F U N C T I O N S   F O R   D I R E C T I O N S
// -------------------------------------------------------------------

/*
 *   (0,0) +--------------------------------------------->  X
 *         |
 *         |                 QGE_DIRECTION_N
 *         |                        |  
 *         |     QGE_DIRECTION_NW \ | / QGE_DIRECTION_NE
 *         |                       \|/
 *         |   QGE_DIRECTION_W -----+----- QGE_DIRECTION_E
 *         |                       /|\ 
 *         |     QGE_DIRECTION_SW / | \ QGE_DIRECTION_SE
 *         |                        |
 *         |                 QGE_DIRECTION_S
 *      Y  V
 */

// RETURN THE DIRECTION CORRESPONDING TO A (X,Y) TRANSLATION
//
// WARNING: The translation must be defined according to one of the
// 8 Freeman directions, precisely, that is to say, if aDx and aDy
// are both different from 0, |aDx| must be equal to |aDy|.
// Otherwise, the correctness of the result is not guaranteed.

QGEdirection
qgDirection(int aDx, int aDy)



{
  if (aDx > 0)
    {
      // Positive X translation: WEST
      // ----------------------------
      if (aDy > 0)
	{
	  return QGE_DIRECTION_NW;
	}
      else if (aDy == 0)
	{
	  return QGE_DIRECTION_W;
	}
      else
	{
	  return QGE_DIRECTION_SW;
	}
    }
  else if (aDx == 0)
    {
      // Null X translation: NORTH/SOUTH
      // -------------------------------
      if (aDy > 0)
	{
	  return QGE_DIRECTION_N;
	}
      else if (aDy == 0)
	{
	  throw QgarErrorDomain(__FILE__, __LINE__,
				"qgar::QGEdirection qgar::qgDirection(int, int)",
				"Both arguments are 0's: No corresponding direction");
	}
      else
	{
	  return QGE_DIRECTION_S;
	}
     }
  else
    {
      // Negative X translation: EAST
      // ----------------------------
      if (aDy > 0)
	{
	  return QGE_DIRECTION_NE;
	}
      else if (aDy == 0)
	{
	  return QGE_DIRECTION_E;
	}
      else
	{
	  return QGE_DIRECTION_SE;
	}
    }
}


// RETURN THE OPPOSITE DIRECTION OF A GIVEN DIRECTION.

QGEdirection
qgOpposite(QGEdirection aDir)



{
  switch (aDir)
  {
    case QGE_DIRECTION_N:
      {
	return QGE_DIRECTION_S;
      }
    case QGE_DIRECTION_NE:
      {
	return QGE_DIRECTION_SW;
      }
    case QGE_DIRECTION_E:
      {
	return QGE_DIRECTION_W;
      }
    case QGE_DIRECTION_SE:
      {
	return QGE_DIRECTION_NW;
      }
    case QGE_DIRECTION_S:
      {
	return QGE_DIRECTION_N;
      }
    case QGE_DIRECTION_SW:
      {
	return QGE_DIRECTION_NE;
      }
    case QGE_DIRECTION_W:
      {
	return QGE_DIRECTION_E;
      }
    case QGE_DIRECTION_NW:
      {
	return QGE_DIRECTION_SE;
      }
    default:
      {
	// **************************************************************************
	// CONTROL SHOULD NEVER REACH THIS POINT
	// **************************************************************************
	ostringstream os;
	os << "Unknown direction: "
	   << aDir;
	throw QgarErrorInvalidArg(__FILE__, __LINE__,
				  "qgar::QGEdirection qgar::qgOpposite(qgar::QGEdirection)",
				  os.str());
	// **************************************************************************
      }
  }
}

// ----------------------------------------------------------------------

} // namespace qgar
