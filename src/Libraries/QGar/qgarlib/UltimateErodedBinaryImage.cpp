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
 * @file  UltimateErodedBinaryImage.cpp
 * @brief Implementation of class qgar::UltimateErodedBinaryImage.
 *
 *        See file UltimateErodedBinaryImage.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date   August 13, 2002  18:04
 * @since  Qgar 2.0
 */



// QGAR
#include "Dist8cBlackCCImage.h"
#include "GenImage.h"
#include "RegionalMaxImage.h"
#include "UltimateErodedBinaryImage.h"



namespace qgar
{

// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
UltimateErodedBinaryImage::UltimateErodedBinaryImage(BinaryImage& img)

  : BinaryImage(img)

{
  perform(this);
}

// -------------------------------------------------------------------
// P U B L I Q U E    F U N C T I O N S
// -------------------------------------------------------------------


void
UltimateErodedBinaryImage::perform(BinaryImage* anImg)
{
  // WARNING
  // Due to the use of the distance function of img when performing
  // the ULT, be carefull to avoid images where distance value may be
  // greater than 255 (i.e. square bigger than 510 x 510)

  Dist8cBlackCCImage distImg(*anImg);
  RegionalMaxImage::perform(&distImg);
  
  BinaryImage::pointer p = anImg->pPixMap();
  BinaryImage::pointer q = distImg.pPixMap();

  int pixSize = anImg->width() * anImg->height();
  
  for (int iCnt = 0; iCnt < pixSize; ++iCnt, ++p, ++q)
    {
      *p = *q;
    }
}

// ----------------------------------------------------------------------

} // namespace qgar


