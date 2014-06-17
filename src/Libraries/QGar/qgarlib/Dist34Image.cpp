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
 * @file Dist34Image.cpp
 *
 * @brief Implementation of class Dist34Image.
 *
 * See file Dist34Image.h for the interface.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Perrin & Kheder">Julien Perrin & Sami Kheder</a>
 * @date   March 24,  2003  16:16
 * @since  Qgar 2.1.1
 */


// STD
#include <algorithm>
#include <limits>
// QGAR
#include "Dist34Image.h"
#include "GenImage.h"



namespace qgar
{

// -------------------------------------------------------------------
// C O N S T R U C T O R
// -------------------------------------------------------------------


Dist34Image::Dist34Image(const BinaryImage& anImg)

  : IntImage(anImg.width(), anImg.height())

{
  // ''neutral'' pixel value for the distance transformation
  const int DIST34_NEUTRAL = INT_MAX;

  // Pointer to source and result pixmaps
  const BinaryImage::value_type* pMapImg;
  IntImage::value_type*          pMapRes = _pPixMap;

  // Top to bottom, left to right

  // First line
  for (int iCnt = 0 ; iCnt < _width ; ++iCnt)
    {
      *pMapRes = DIST34_NEUTRAL;
      ++pMapRes;
    }

  // First and last columns
  for (int iCnt = 1 ; iCnt < (_height - 1) ; ++iCnt, pMapRes += _width)
    {
      *pMapRes = DIST34_NEUTRAL;
      *(pMapRes + _width - 1) = DIST34_NEUTRAL;
    }
 
  // Last line
  for (int iCnt = 0 ; iCnt < _width ; ++iCnt)
    {
      *pMapRes = DIST34_NEUTRAL;
      ++pMapRes;
    }
 

  // TOP TO BOTTOM, LEFT TO RIGHT NEIGHBORHOOD
  //
  //         +--+--+--+
  //         |P2|P3|P4|
  //         +--+--+--+
  //         |P1| x|  |
  //         +--+--+--+
  //         |  |  |  |
  //         +--+--+--+


  pMapImg =  anImg.pPixMap() + anImg.width() + 1;
  pMapRes =  pPixMap() + _width + 1;
 
  for (int iCnt = 1 ; iCnt < (_height -1); ++iCnt)
    {
      for (int jCnt = 1 ; jCnt < (_width -1); ++jCnt, ++pMapImg, ++pMapRes)
	{  

	  if (*pMapImg == QGE_BW_WHITE)
	    {
	      // ======================
	      // CURRENT PIXEL IS WHITE
	      // ======================

	      // ******** P1 ********

	      if ((*(pMapImg - 1)) == QGE_BW_WHITE)
		{
		  if (*(pMapRes - 1) != DIST34_NEUTRAL)
		    {
		      *pMapRes = *(pMapRes - 1) + 3;
		    }
		  else
		    {
		      *pMapRes = DIST34_NEUTRAL;
		    }
		}
	      else 
		{
		  *pMapRes = 3;
		}

	      // ******** P2 ********

	      if ( (*(pMapImg - _width - 1)) == QGE_BW_WHITE)
		{ 
		  if (*(pMapRes - _width - 1) != DIST34_NEUTRAL)
		    {
		      *pMapRes = std::min(*pMapRes, *(pMapRes - _width - 1) + 4);
		    }
		  else
		    {
		      *pMapRes = std::min(*pMapRes, DIST34_NEUTRAL);
		    }
		}
	      else 
		{
		  *pMapRes = std::min(*pMapRes, 4);
		}

	      // ******** P3 ********

	      if ((*(pMapImg - _width)) == QGE_BW_WHITE)
		{
		  if (*(pMapRes - _width) != DIST34_NEUTRAL)
		    {
		      *pMapRes = std::min(*pMapRes, *(pMapRes - _width) + 3);
		    }
		  else
		    {
		      *pMapRes = std::min(*pMapRes, DIST34_NEUTRAL);
		    }
		}
	      else 
		{
		  *pMapRes = 3;
		}

	      // ******** P4 ********

	      if ((*(pMapImg - _width + 1)) == QGE_BW_WHITE)
		{
		  if (*(pMapRes - _width + 1) != DIST34_NEUTRAL)
		    {
		      *pMapRes = std::min(*pMapRes, *(pMapRes - _width + 1) + 4);
		    }
		  else
		    {
		      *pMapRes = std::min(*pMapRes, DIST34_NEUTRAL);
		    }
		}
	      else 
		{
		  *pMapRes = std::min(*pMapRes, 4);
		}

	      // ==================
	      // END OF WHITE PIXEL
	      // ==================
	    }

	  else 

	    {
	      // ======================
	      // CURRENT PIXEL IS BLACK
	      // ======================

	      // ******** P1 ********

	      if ((*( pMapImg - 1)) == QGE_BW_BLACK)
		{
		  if (*(pMapRes - 1) != DIST34_NEUTRAL)
		    {
		      *pMapRes = *(pMapRes - 1) + 3;
		    }
		  else
		    {
		      *pMapRes = DIST34_NEUTRAL;
		    }
		}
	      else 
		{
		  *pMapRes = 3;
		}

	      // ******** P2 ********

	      if ((*(pMapImg - _width - 1)) == QGE_BW_BLACK)
		{
		  if (*(pMapRes - _width - 1) != DIST34_NEUTRAL)
		    {
		      *pMapRes = std::min(*pMapRes, *(pMapRes - _width - 1) + 4);
		    }
		  else
		    {
		      *pMapRes = std::min(*pMapRes, DIST34_NEUTRAL);
		    }
		}
	      else 
		{
		  *pMapRes = std::min(*pMapRes, 4);
		}

	      // ******** P3 ********

	      if ((*(pMapImg - _width)) == QGE_BW_BLACK)
		{
		  if (*(pMapRes - _width) != DIST34_NEUTRAL)
		    {
		      *pMapRes = std::min(*pMapRes, *(pMapRes - _width) + 3);
		    }
		  else
		    {
		      *pMapRes = std::min(*pMapRes, DIST34_NEUTRAL);
		    }
		}
	      else 
		{
		  *pMapRes = 3;
		}

	      // ******** P4 ********

	      if ( (*(pMapImg - _width + 1)) == QGE_BW_BLACK)
		{
		  if (*(pMapRes - _width + 1) != DIST34_NEUTRAL)
		    {
		      *pMapRes = std::min(*pMapRes, *(pMapRes - _width + 1) + 4);
		    }
		  else
		    {
		      *pMapRes = std::min(*pMapRes, DIST34_NEUTRAL);
		    }
		}
	      else 
		{
		  *pMapRes = std::min(*pMapRes, 4);
		}

	      // ==================
	      // END OF BLACK PIXEL
	      // ==================
	    }
	} // END for jCnt

      pMapImg += 2;
      pMapRes += 2;

    } // END for iCnt


  //  BOTTOM TO TOP, RIGHT TO LEFT NEIGHBORHOOD
  //
  //        +--+--+--+
  //        |  |  |  |
  //        +--+--+--+
  //        |  | x|P5|
  //        +--+--+--+
  //        |P6|P7|P8|
  //        +--+--+--+

  int size = _width * _height;  // Image size

  pMapImg = anImg.pPixMap() + size - anImg.width() - 2; 
  pMapRes = _pPixMap + size - _width - 2;


  for (int iCnt = _height - 2; iCnt > 0; --iCnt)
    {
      for (int jCnt = _width - 2; jCnt > 0; --jCnt, --pMapImg, --pMapRes)
	{

	  if (*pMapImg == QGE_BW_WHITE)
	    {
	      // ======================
	      // CURRENT PIXEL IS WHITE
	      // ======================

	      // ******** P5 ********

	      if ((*(pMapImg + 1)) == QGE_BW_WHITE)
		{
		  if (*(pMapRes + 1) != DIST34_NEUTRAL)
		    {
		      *pMapRes = std::min(*pMapRes, *(pMapRes + 1) + 3);
		    }
		}
	      else 
		{
		  *pMapRes = 3;
		}

	      // ******** P6 ********

	      if ((*(pMapImg + _width - 1)) == QGE_BW_WHITE)
		{ 
		  if (*(pMapRes + _width - 1) != DIST34_NEUTRAL)
		    {
		      *pMapRes = std::min(*pMapRes, *(pMapRes + _width - 1) + 4);
		    }
		}
	      else 
		{
		  *pMapRes = std::min(*pMapRes, 4);
		}

	      // ******** P7 ********

	      if ((*(pMapImg + _width)) == QGE_BW_WHITE)
		{
		  if (*(pMapRes + _width) != DIST34_NEUTRAL)
		    {
		      *pMapRes = std::min(*pMapRes, *(pMapRes + _width) + 3);
		    }
		}
	      else 
		{
		  *pMapRes = 3;
		}

	      // ******** P8 ********

	      if ((*(pMapImg + _width + 1)) == QGE_BW_WHITE)
		{
		  if (*(pMapRes + _width + 1) != DIST34_NEUTRAL)
		    {
		      *pMapRes = std::min(*pMapRes, *(pMapRes + _width + 1) + 4);
		    }
		}
	      else 
		{
		  *pMapRes = std::min(*pMapRes, 4);
		}
	      
	      // ==================
	      // END OF WHITE PIXEL
	      // ==================
	    }

	  else

	    {
	      // ======================
	      // CURRENT PIXEL IS BLACK
	      // ======================

	      // ******** P5 ********

	      if ((*(pMapImg + 1)) == QGE_BW_BLACK)
		{
		  if (*(pMapRes + 1) != DIST34_NEUTRAL)
		    {
		      *pMapRes = std::min(*pMapRes, *(pMapRes + 1) + 3);
		    }
		}
	      else 
		{
		  *pMapRes = 3;
		}

	      // ******** P6 ********

	      if ( (*(pMapImg + _width - 1)) == QGE_BW_BLACK)
		{
		  if (*(pMapRes + _width - 1))
		    {
		      *pMapRes = std::min(*pMapRes, *(pMapRes + _width - 1) + 4);
		    }
		}
	      else 
		{
		  *pMapRes = std::min(*pMapRes, 4);
		}

	      // ******** P7 ********

	      if ((*(pMapImg + _width)) == QGE_BW_BLACK)
		{ 
		  if (*(pMapRes + _width) != DIST34_NEUTRAL)
		    {
		      *pMapRes = std::min(*pMapRes, *(pMapRes + _width) + 3);
		    }
		}
	      else 
		{
		  *pMapRes = 3;
		}

	      // ******** P8 ********

	      if ((*(pMapImg + _width + 1)) == QGE_BW_BLACK)
		{
		  if (*(pMapRes + _width + 1) != DIST34_NEUTRAL)
		    {
		      *pMapRes = std::min(*pMapRes, *(pMapRes + _width + 1) + 4);
		    }
		}
	      else 
		{
		  *pMapRes = std::min(*pMapRes, 4);
		}

	      // ==================
	      // END OF BLACK PIXEL
	      // ==================
	    }
	  
	} // END for jCnt

      pMapImg -= 2;
      pMapRes -= 2;

    } // END for iCnt
}


// -------------------------------------------------------------------

} // namespace qgar



