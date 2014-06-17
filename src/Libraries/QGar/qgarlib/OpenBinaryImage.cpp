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
 * @file  OpenBinaryImage.cpp
 * @brief Implementation of class qgar::OpenBinaryImage.
 *
 *        See file OpenBinaryImage.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date   July 18, 2002  15:48
 * @since  Qgar 2.0
 */



// STD
#include <sstream>
// QGAR
#include "DilatedBinaryImage.h"
#include "ErodedBinaryImage.h"
#include "QgarErrorDomain.h"
#include "OpenBinaryImage.h"



namespace qgar
{

// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

OpenBinaryImage::OpenBinaryImage(const BinaryImage& anImg,
				 unsigned int anOpenSize)



  : BinaryImage(anImg)

{
  int sqsize = (2 * anOpenSize) + 1;  // Effective mask size

  if ((sqsize > anImg.width()) || (sqsize > anImg.height()))
    {
      std::ostringstream os;
      os << "Opening size ["
	 << sqsize
	 << " X "
	 << sqsize
	 << "] too large for image ["
	 << anImg.width()
	 << " X "
	 << anImg.height()
	 << "]";
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "void qgar::OpenBinaryImage::OpenBinaryImage(const qgar::BinaryImage&, unsigned int)",
			    os.str());
    }

  perform(this, anOpenSize);
}

// ---------------------------------------------------------------------
// O P E N I N G
// ----------------------------------------------------------------------

void
OpenBinaryImage::perform(BinaryImage* anImg, unsigned int anOpenSize) 
{ 
  ErodedBinaryImage::perform(anImg, anOpenSize);
  DilatedBinaryImage::perform(anImg, anOpenSize);
}

// ----------------------------------------------------------------------

} // namespace qgar
