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
 * @file FreemanCode.cpp
 *
 * @brief Implementation of class qgar::FreemanCode.
 *
 * See file FreemanCode.h for the interface.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   February 3, 2004  17:17
 * @since  Qgar 2.1.1
 */



// STD
#include <iostream>
#include <sstream>
// QGAR
#include "FreemanCode.h"
#include "image.h"



using namespace std;



namespace qgar
{


// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------


// DEFAULT CONSTRUCTOR

FreemanCode::FreemanCode()

  : _direction(QGE_DIRECTION_N),
    _length(0)

{
  // VOID
}

// COPY CONSTRUCTOR

FreemanCode::FreemanCode(const FreemanCode& aCode)

  : _direction(aCode._direction),
    _length(aCode._length)

{
  // VOID
}

// INITIALIZE WITH A DIRECTION AND A LENGTH

FreemanCode::FreemanCode(QGEdirection aDir, unsigned int aLength)

  : _direction(aDir),
    _length(aLength)

{
  // VOID
}


// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------
// ----------------------------------------------------------------------


// VIRTUAL DESTRUCTOR

FreemanCode::~FreemanCode()
{
  // VOID
}


// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// O P E R A T O R S
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------


// ASSIGNMENT OPERATOR

FreemanCode&
FreemanCode::operator=(const FreemanCode& aCode)
{
  // Are left hand side and right hand side different objects?
  if (this != &aCode)
    {
      _direction = aCode._direction;
      _length    = aCode._length;
    }

  return *this;
}


// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// S E R I A L I Z A T I O N / D E S E R I A L I Z A T I O N
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------


istream& 
FreemanCode::read(istream& anInStream)
{
  qgReadObjName(anInStream, "FreemanCode");

  int dir;
  qgReadObjData(anInStream, dir);
  _direction = (QGEdirection) dir;

  qgReadObjData(anInStream, _length);

  return anInStream;
}


ostream& 
FreemanCode::write(ostream& anOutStream) const
{
  anOutStream << "FreemanCode("
              << _direction
              << ")("
              << _length
              << ')';

  return anOutStream;
}


// ----------------------------------------------------------------------

} // namespace qgar
