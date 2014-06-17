/*---------------------------------------------------------------------*
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
 * @file  RegionalMaxBinaryImage.cpp
 * @brief Implementation of class qgar::RegionalMaxBinaryImage.
 *
 * See file RegionalMaxBinaryImage.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date   August 12, 2002  17:16
 * @since  Qgar 2.1
 */



// QGAR
#include "ErodedBinaryImage.h"
#include "GenImage.h"
#include "GeodesicRecBinaryImage.h"
#include "RegionalMaxBinaryImage.h"



namespace qgar
{

// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------


// Default constructor
RegionalMaxBinaryImage::RegionalMaxBinaryImage(BinaryImage& anImg)

  : BinaryImage(anImg)

{
  perform(this);
}


// -------------------------------------------------------------------
// P U B L I Q U E    F U N C T I O N S
// -------------------------------------------------------------------


void
RegionalMaxBinaryImage::perform(BinaryImage* anImg)
{
  ErodedBinaryImage eroImg(*anImg);
  GeodesicRecBinaryImage::perform(&eroImg, anImg);
  *anImg -= eroImg;
}


// ----------------------------------------------------------------------

} // namespace qgar
