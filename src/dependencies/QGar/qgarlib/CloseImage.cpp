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
 * @file  CloseImage.cpp
 * @brief Implementation of class qgar::CloseImage.
 *
 *        See file CloseImage.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date   July 26, 2002  11:45
 * @since  Qgar 2.0
 */


// STD
#include <sstream>
// QGAR
#include "CloseImage.h"
#include "DilatedImage.h"
#include "ErodedImage.h"
#include "GenImage.h"
#include "QgarErrorDomain.h"



namespace qgar
{

// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
CloseImage::CloseImage(GreyLevelImage& anImg, unsigned int aClosingSize)


  : GreyLevelImage(anImg)

{
  int sqsize = (2 * aClosingSize) + 1;  // Effective mask size

  if ((sqsize > anImg.width()) || (sqsize > anImg.height()))
    {
      std::ostringstream os;
      os << "Closing size ["
	 << aClosingSize
	 << " -> "
	 << sqsize
	 << "] too large for image ["
	 << anImg.width()
	 << " X "
	 << anImg.height()
	 << "]";
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "qgar::CloseImage::CloseImage(qgar::GreyLevelImage&, unsigned int)",
			    os.str());
    }

  perform(this, aClosingSize);
}

// ---------------------------------------------------------------------
// C L O S U R E
// ----------------------------------------------------------------------

void
CloseImage::perform(GreyLevelImage* anImg, unsigned int aClosingSize) 
{ 
  DilatedImage::perform(anImg, aClosingSize);
  ErodedImage::perform(anImg, aClosingSize);
}

// ----------------------------------------------------------------------

} // namespace qgar
