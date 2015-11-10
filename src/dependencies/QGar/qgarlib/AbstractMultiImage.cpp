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
 * @file  AbstractMultiImage.cpp
 * @brief Implementation of class qgar::AbstractMultiImage.
 *
 *        See file AbstractMultiImage.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   December 15, 2004  15:52
 * @since  Qgar 2.2
 */


// QGAR
#include "AbstractMultiImage.h"



namespace qgar
{


// -------------------------------------------------------------------
// C O N S T R U C T O R S 
// -------------------------------------------------------------------


// DEFAULT CONSTRUCTOR

AbstractMultiImage::AbstractMultiImage()

  : _width(0),
    _height(0)

{
  // VOID
}


// COPY CONSTRUCTOR


AbstractMultiImage::AbstractMultiImage(const AbstractMultiImage& anImg)

  : _width(anImg._width),
    _height(anImg._height)

{
  // VOID
}


// INITIALIZE WITH GIVEN WIDTH AND HEIGHT

AbstractMultiImage::AbstractMultiImage(unsigned int aWidth,
				       unsigned int aHeight)

  : _width(aWidth),
    _height(aHeight)

{
  // VOID
}


// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------


// VIRTUAL DESTRUCTOR

AbstractMultiImage::~AbstractMultiImage()
{
  // VOID
}


// ---------------------------------------------------------------------
// O P E R A T O R S
// ----------------------------------------------------------------------


// ASSIGNMENT OPERATOR

AbstractMultiImage&
AbstractMultiImage::operator=(const AbstractMultiImage& anImg)
{
  // Are left hand side and right hand side different objects?
  if (this != &anImg)
    {
      _width  = anImg._width;
      _height = anImg._height;
    }
  return *this;
}


// ----------------------------------------------------------------------


} // namespace qgar
