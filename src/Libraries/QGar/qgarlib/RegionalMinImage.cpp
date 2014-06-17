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
 * @file  RegionalMinImage.cpp
 * @brief Implementation of class qgar::RegionalMinImage.
 *
 *        See file RegionalMinImage.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date   August 21, 2002  15:01
 */



// QGAR
#include "DilatedImage.h"
#include "GenImage.h"
#include "GeodesicRecEroImage.h"
#include "RegionalMinImage.h"



namespace qgar
{

// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
RegionalMinImage::RegionalMinImage(GreyLevelImage& img)

  : GreyLevelImage(img)

{
  perform(this);
}

// -------------------------------------------------------------------
// P U B L I Q U E    F U N C T I O N S
// -------------------------------------------------------------------

void
RegionalMinImage::perform(GreyLevelImage * img)
{
  GreyLevelImage reconst(*img);
  DilatedImage::perform(img);
  GeodesicRecEroImage::perform(img, &reconst);
  *img -= reconst;
}

// ----------------------------------------------------------------------

} // namespace qgar
