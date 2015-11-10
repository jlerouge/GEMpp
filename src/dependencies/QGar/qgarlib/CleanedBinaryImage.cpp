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
 * @file CleanedBinaryImage.cpp
 *
 * @brief Implementation of class qgar::CleanedBinaryImage.
 *
 * See file CleanedBinaryImage.h for the interface.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>,
 *         from previous work by Adlane Habed and Karl Tombre
 * @date   July 4, 2001  17:32
 * @since  Qgar 1.0
 */



// QGAR
#include "CleanedBinaryImage.h"



namespace qgar
{

// -------------------------------------------------------------------
// C O N S T R U C T O R
// -------------------------------------------------------------------


// CONSTRUCT FROM GIVEN BINARY IMAGE


CleanedBinaryImage::CleanedBinaryImage(const BinaryImage& aBinImg)

  : BinaryImage(aBinImg)

{
  // Constants
  const int QG_W_m_1 = _width - 1;
  const int QG_W_p_1 = _width + 1;

  // Pointers to current pixels
  BinaryImage::pointer pBinMap   = aBinImg.pPixMap() + QG_W_p_1; // given image
  BinaryImage::pointer pCleanMap = _pPixMap          + QG_W_p_1; // cleaned image


  // FOR EACH ROW
  for (int rowCnt = 1 ; rowCnt < (_height - 1) ; ++rowCnt, pBinMap += 2, pCleanMap += 2)
    {
      // FOR EACH CENTER PIXEL IN A ROW
      for (int colCnt = 1 ; colCnt < QG_W_m_1 ; ++colCnt, ++ pBinMap, ++pCleanMap)
	{

	  if(*pBinMap == QGE_BW_WHITE)
	    {
	      // ===================================================== 
	      // CENTER PIXEL IS WHITE => set to BLACK iff:
	      //
	      // B B B   w B B   w w w   B B w   * B *       NW N NE
	      // B w B   w w B   B w B   B w w   B w B       W  .  E
	      // w w w   w B B   B B B   B B w   * B *       SW S SE
	      //
	      //  [a]     [b]     [c]     [d]     [e]
	      // ===================================================== 

	      if (*(pBinMap - _width) == QGE_BW_WHITE) // N
		{
		  // N is WHITE
		  if ((*(pBinMap - QG_W_p_1) == QGE_BW_WHITE) && // NW     w . w
		      (*(pBinMap - QG_W_m_1) == QGE_BW_WHITE) && // NE     B . B
		      (*(pBinMap - 1)        == QGE_BW_BLACK) && // W      B B B
		      (*(pBinMap + 1)        == QGE_BW_BLACK) && // E
		      (*(pBinMap + QG_W_m_1) == QGE_BW_BLACK) && // SW
		      (*(pBinMap + _width)   == QGE_BW_BLACK) && // S
		      (*(pBinMap + QG_W_p_1) == QGE_BW_BLACK))   // SE
		    {
		      *pCleanMap = QGE_BW_BLACK;  // **** [c] ****
		    }
		}

	      // N is BLACK
	      else if (*(pBinMap - 1) == QGE_BW_WHITE) // W
		{
		  // (N is BLACK) && (W is WHITE)
		  if ((*(pBinMap - QG_W_p_1) == QGE_BW_WHITE) &&  // NW    w . B
		      (*(pBinMap - QG_W_m_1) == QGE_BW_BLACK) &&  // NE    . . B
		      (*(pBinMap + 1)        == QGE_BW_BLACK) &&  // E     w B B
		      (*(pBinMap + QG_W_m_1) == QGE_BW_WHITE) &&  // SW
		      (*(pBinMap + _width)   == QGE_BW_BLACK) &&  // S
		      (*(pBinMap + QG_W_p_1) == QGE_BW_BLACK))    // SE
		    {
		      *pCleanMap = QGE_BW_BLACK;  // **** [b] ****
		    }
		}

	      // (N is BLACK) && (W is BLACK)
	      else if (*(pBinMap + 1) == QGE_BW_WHITE) // E
		{
		  // (N is BLACK) && (W is BLACK) && (E is WHITE)
		  if ((*(pBinMap - QG_W_p_1) == QGE_BW_BLACK) &&  // NW    B . w
		      (*(pBinMap - QG_W_m_1) == QGE_BW_WHITE) &&  // NE    . . .
		      (*(pBinMap + QG_W_m_1) == QGE_BW_BLACK) &&  // SW    B B w
		      (*(pBinMap + _width)   == QGE_BW_BLACK) &&  // S
		      (*(pBinMap + QG_W_p_1) == QGE_BW_WHITE))    // SE
		    {
		      *pCleanMap = QGE_BW_BLACK;  // **** [d] ****
		    }
		}

	      // (N is BLACK) && (W is BLACK) && (E is BLACK)
	      else if (*(pBinMap + _width) == QGE_BW_BLACK) // S
		{
		  // (N is BLACK) && (W is BLACK) && (E is BLACK) && (S is BLACK)

		  *pCleanMap = QGE_BW_BLACK;  // **** [e] ****
		}
	      
	      //  (N is BLACK) && (W is BLACK) && (E is BLACK) && (S is WHITE)
	      else if ((*(pBinMap - QG_W_p_1) == QGE_BW_BLACK) && // NW    B . B
		       (*(pBinMap - QG_W_m_1) == QGE_BW_BLACK) && // NE    . . .
		       (*(pBinMap + QG_W_m_1) == QGE_BW_WHITE) && // SW    w . w
		       (*(pBinMap + QG_W_p_1) == QGE_BW_WHITE))   // SE 
		{
		  *pCleanMap = QGE_BW_BLACK;  // **** [a] ****
		}
	      
	      // ===================================================== 
	      // END center pixel is WHITE
	      // ===================================================== 
	    }

	  else

	    {
	      // ===================================================== 
	      // CENTER PIXEL IS BLACK => set to WHITE iff:
	      //
	      // B B B   w w B   w w w   B w w   w w w       NW N NE
	      // w B w   w B B   w B w   B B w   w B w       W  .  E
	      // w w w   w w B   B B B   B w w   w w w       SW S SE
	      //
	      //  [f]     [g]     [h]     [i]     [j]
	      // ===================================================== 
	      
	      if (*(pBinMap - 1) == QGE_BW_BLACK) // W
		{
		  // W is BLACK
		  if ((*(pBinMap - QG_W_p_1) == QGE_BW_BLACK) && // NW     B w w
		      (*(pBinMap - _width)   == QGE_BW_WHITE) && // N      . . w
		      (*(pBinMap - QG_W_m_1) == QGE_BW_WHITE) && // NE     B w w
		      (*(pBinMap + 1)        == QGE_BW_WHITE) && // E
		      (*(pBinMap + QG_W_m_1) == QGE_BW_BLACK) && // SW
		      (*(pBinMap + _width)   == QGE_BW_WHITE) && // S
		      (*(pBinMap + QG_W_p_1) == QGE_BW_WHITE))   // SE
		    {
		      *pCleanMap = QGE_BW_WHITE;  // **** [i] ****
		    }
		}

	      // W is WHITE
	      else if (*(pBinMap + 1) == QGE_BW_BLACK) // E
		{
		  // (W is WHITE) && (E is BLACK)
		  if ((*(pBinMap - QG_W_p_1) == QGE_BW_WHITE) &&  // NW    w w B
		      (*(pBinMap - _width)   == QGE_BW_WHITE) &&  // N     . . .
		      (*(pBinMap - QG_W_m_1) == QGE_BW_BLACK) &&  // NE    w w B
		      (*(pBinMap + QG_W_m_1) == QGE_BW_WHITE) &&  // SW
		      (*(pBinMap + _width)   == QGE_BW_WHITE) &&  // S
		      (*(pBinMap + QG_W_p_1) == QGE_BW_BLACK))    // SE
		    {
		      *pCleanMap = QGE_BW_WHITE;  // **** [g] ****
		    }
		}

	      // (W is WHITE) && (E is WHITE)
	      else if (*(pBinMap - QG_W_p_1) == QGE_BW_BLACK) // NW
		{
		  // (W is WHITE) && (E is WHITE) && (NW is BLACK)
		  if ((*(pBinMap - _width)   == QGE_BW_BLACK) &&  // N     . B B
		      (*(pBinMap - QG_W_m_1) == QGE_BW_BLACK) &&  // NE    . . .
		      (*(pBinMap + QG_W_m_1) == QGE_BW_WHITE) &&  // SW    w w w
		      (*(pBinMap + _width)   == QGE_BW_WHITE) &&  // S
		      (*(pBinMap + QG_W_p_1) == QGE_BW_WHITE))    // SE
		    {
		      *pCleanMap = QGE_BW_WHITE;  // **** [f] ****
		    }
		}

	      // (W is WHITE) && (E is WHITE) && (NW is WHITE)
	      else if (*(pBinMap + QG_W_m_1) == QGE_BW_BLACK) // SW
		{
		  // (W is WHITE) && (E is WHITE) && (NW is WHITE) && (SW is BLACK)
		  if ((*(pBinMap - _width)   == QGE_BW_WHITE) &&  // N     . w w
		      (*(pBinMap - QG_W_m_1) == QGE_BW_WHITE) &&  // NE    . . .
		      (*(pBinMap + _width)   == QGE_BW_BLACK) &&  // S     . B B
		      (*(pBinMap + QG_W_p_1) == QGE_BW_BLACK))    // SE
		    {
		      *pCleanMap = QGE_BW_WHITE;  // **** [h] ****
		    }
		}
	      
	      // (W is WHITE) && (E is WHITE) && (NW is WHITE) && (SW is WHITE)
	      else if ((*(pBinMap - _width)   == QGE_BW_WHITE) &&  // N     . w w
		       (*(pBinMap - QG_W_m_1) == QGE_BW_WHITE) &&  // NE    . . .
		       (*(pBinMap + _width)   == QGE_BW_WHITE) &&  // S     . w w
		       (*(pBinMap + QG_W_p_1) == QGE_BW_WHITE))    // SE
		{
		  *pCleanMap = QGE_BW_WHITE;  // **** [j] ****
		}

	      // ===================================================== 
	      // END center pixel is BLACK
	      // ===================================================== 
	    }

	} // END FOR EACH CENTER PIXEL
    }     // END FOR EACH ROW

} // END function


// -------------------------------------------------------------------

} // namespace qgar
