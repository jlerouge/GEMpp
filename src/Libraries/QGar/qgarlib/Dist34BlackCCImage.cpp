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


/**
 * @file Dist34BlackCCImage.cpp
 *
 * @brief Implementation of class Dist34BlackCCImage.
 *
 * See file Dist34BlackCCImage.h for the interface.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   July 3, 2001  15:03
 * @since  Qgar 1.0
 */


// STD
#include <algorithm>
// QGAR
#include "Dist34BlackCCImage.h"
#include "GenImage.h"



using namespace std;



namespace qgar
{

// -------------------------------------------------------------------
// C O N S T R U C T O R
// -------------------------------------------------------------------
Dist34BlackCCImage::Dist34BlackCCImage(const BinaryImage& anImg)

  : IntImage(anImg.width(), anImg.height())

{
  BinaryImage::const_pointer  pMapImg;
  Dist34BlackCCImage::pointer pMapRes;
 
  // Size of pixel maps
  int pixsize = _width * _height;
 
  // Initialization of the result image:
  // a 0 value is needed on the borders of the image

  // First line
  pMapRes = _pPixMap;
  for (int iCnt = 0 ; iCnt < _width ; ++iCnt)
    {
      *pMapRes = 0;
      ++pMapRes;
    }

  // First and last columns
  for (int iCnt = 1 ; iCnt < (_height - 1) ; ++iCnt, pMapRes += _width)
    {
      *pMapRes = 0;
      *(pMapRes + _width - 1) = 0;
    }

  // Last line
  for (int iCnt = 0 ; iCnt < _width ; ++iCnt)
    {
      *pMapRes = 0;
      ++pMapRes;
    }

  // DISTANCE TRANSFORM (DT)

  // Only the distance transform of the black pixels is computed.
  // The DT value is computed according to 4 neighbors, either black
  // or white. The direction of processing ensures that pixels are
  // always associated to a consistent DT: white pixels are always
  // associated to a DT value equal to 0 (which is neutral for this
  // operation) and black pixels result from previous computations.
  //
  // In the first step, and only in this step, we take advantage of the
  // loops to initialize white pixels.

  // STEP ONE: up to bottom and left to right

  pMapImg = anImg.pPixMap() + _width + 1;
  pMapRes = _pPixMap + _width + 1;

  for (int iCnt = 1 ; iCnt < (_height - 1) ; ++iCnt)
    {
      for (int jCnt = 1 ; jCnt < (_width - 1) ; ++jCnt, ++pMapRes, ++pMapImg)
	{
	  if (*pMapImg == QGE_BW_BLACK)
	    {
	      Dist34BlackCCImage::pointer pw = pMapRes - _width;
 
	      // BLACK pixel
	      *pMapRes = min(min(*(pMapRes - 1) + 3, *(pw - 1) + 4), 
			     min(*pw + 3, *(pw + 1) + 4));
	    }
	  else
	    {
	      // WHITE pixel
	      *pMapRes = 0;
	    }
	} // END for jCnt

      pMapRes += 2;
      pMapImg += 2;

    } // END for iCnt


  // STEP TWO: bottom to up and right to left

  pMapImg = anImg.pPixMap() + pixsize - _width - 2;
  pMapRes = _pPixMap + pixsize - _width - 2;

  for (int iCnt = _height - 2 ; iCnt > 0 ; --iCnt)
    {
      for (int jCnt = _width - 2 ; jCnt > 0 ; --jCnt, --pMapRes, -- pMapImg)
	{
	  if (*pMapImg == QGE_BW_BLACK)
	    {
	      Dist34BlackCCImage::pointer pw = pMapRes + _width;

	      *pMapRes = min(min(min(*(pMapRes + 1) + 3, *(pw + 1) + 4),
				 min(*pw + 3, *(pw - 1) + 4)),
			     *pMapRes);
	    }
	} // END for jCnt

      pMapRes -= 2;
      pMapImg -= 2;

    } // END for iCnt
}
// -------------------------------------------------------------------

} // namespace qgar

