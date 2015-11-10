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
 * @file Dist8cBlackCCImage.cpp
 *
 * @brief Implementation of class qgar::Dist8cBlackCCImage.
 *
 * See file Dist8cBlackCCImage.h for the interface.
 *
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date   August 14, 2002  15:04
 * @since  Qgar 2.0
 */


// STD
#include <algorithm>
// QGAR
#include "Dist8cBlackCCImage.h"
#include "GenImage.h"



namespace qgar
{

// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

Dist8cBlackCCImage::Dist8cBlackCCImage(const BinaryImage& anImg)

  : GreyLevelImage(anImg)

{
  // Current image size
  int pixsize = _width * _height;
  // Pointer to current pixel map
  BinaryImage::pointer pMapCurr = _pPixMap;
  
  // First line to 0
  for (int iCnt = 0 ; iCnt < _width ; ++iCnt)
    {
      *pMapCurr = 0;
      ++pMapCurr;
    }

  // First and last columns to 0
  for (int iCnt = 1 ; iCnt < (_height - 1) ; ++iCnt, pMapCurr += _width)
    {
      *pMapCurr = 0;
      *(pMapCurr + _width - 1) = 0;
    }

  // Last line to 0
  for (int iCnt = 0 ; iCnt < _width ; ++iCnt)
    {
      *pMapCurr = 0;
      ++pMapCurr;
    }


  pMapCurr = _pPixMap + _width + 1;

  for (int iCnt = 1 ; iCnt < _height ; ++iCnt)
    {
      for (int jCnt = 1 ; jCnt < _width; ++jCnt, ++pMapCurr)
	{
	  if (*pMapCurr != 0)
	    {
	      *pMapCurr = 1 + std::min(std::min(*(pMapCurr - 1),
						*(pMapCurr - _width - 1)), 
				       std::min(*(pMapCurr - _width),
						*(pMapCurr - _width + 1)));
	    }
	}

      ++pMapCurr;
    }


  pMapCurr = _pPixMap + pixsize - _width - 2;
 
  for (int iCnt = _height - 2 ; iCnt >= 0 ; --iCnt)
    {
      for (int jCnt = _width - 2; jCnt >= 0 ; --jCnt, --pMapCurr)
	{
	  if (*pMapCurr != 0)
	    {
	      BinaryImage::value_type m =
		1 + std::min(std::min(*(pMapCurr + 1),
				      *(pMapCurr + _width + 1)),
			     std::min(*(pMapCurr + _width),
				      *(pMapCurr + _width - 1)));

	      *pMapCurr = std::min(m, *pMapCurr);
	    }
	}

      --pMapCurr;
    }

}

// ----------------------------------------------------------------------

} // namespace qgar
