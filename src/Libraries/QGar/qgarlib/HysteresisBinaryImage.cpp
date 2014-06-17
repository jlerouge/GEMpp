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



// The implementation of the hysteresis algorithm is strongly inspired
// by that made by Simon A.J. Winder in the IMG* package.
// Here is his copyright notice:

/*---------------------------------------------------------------------+
 |             IMG* Image Processing Toolset and C Library             |
 |                                                                     |
 |                   Copyright 1994 Simon A.J. Winder                  |
 |                        All Rights Reserved                          |
 |                                                                     |
 | Permission to use, copy, and modify this software and its           |
 | documentation is hereby granted only under the following terms and  |
 | conditions.  Both the above copyright notice and this permission    |
 | notice must be included along with all copies of the software,      |
 | derivative works or modified versions, and any portions thereof,    |
 | and both notices must appear in supporting documentation.           |
 |                                                                     |
 | This software may be distributed (but not offered for sale or       |
 | transferred for compensation) to third parties, provided such third |
 | parties agree to abide by the terms and conditions of this notice.  |
 |                                                                     |
 | The software is provided "as is" and the author disclaims all       |
 | warranties with regard to this software, including all implied      |
 | warranties of merchantability and fitness. In no event shall the    |
 | author  be liable for any special, direct, indirect, or             |
 | consequential damages or any damages whatsoever resulting from loss |
 | of use, data or profits, whether in an action of contract,          |
 | negligence or other tortious action, arising out of or in           |
 | connection with the use or performance of this software.            |
 *---------------------------------------------------------------------*/



/**
 * @file HysteresisBinaryImage.cpp
 *
 * @brief Implementation of class qgar::HysteresisBinaryImage.
 *
 * See file HysteresisBinaryImage.h for the interface.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date   July 3, 2001  16:30
 * @since  Qgar 1.0
 */



// STD
#include <stack>
#include <vector>
// QGAR
#include "GradientLocalMaxImage.h"
#include "HysteresisBinaryImage.h"
#include "primitives.h"



using namespace std;



namespace qgar
{

// -------------------------------------------------------------------
// C O N S T R U C T O R
// -------------------------------------------------------------------
HysteresisBinaryImage::HysteresisBinaryImage(const GradientLocalMaxImage& aGradImg,
					     unsigned int aLowThrsl,
					     unsigned int aHighThrsl)

    : BinaryImage(aGradImg.width(), aGradImg.height())  // Allocate binary image
  
{
  // Stack of points
  stack< Point, vector<Point> >  stackPt;

  // Create two images for low and high thresholded images
  BinaryImage lowImg (_width, _height);
  BinaryImage highImg(_width, _height);
  
  // Fill them with 1's and 0's
  int size = _width * _height;
  BinaryImage::pointer pMapLow  = lowImg.pPixMap();
  BinaryImage::pointer pMapHigh = highImg.pPixMap();
  float* pMapGrad = aGradImg.pPixMap();

  for (int iCnt = 0 ; iCnt < size ; ++iCnt, ++pMapLow, ++pMapHigh, ++pMapGrad)
    {
      float pix = *pMapGrad;

      if ((pix == 0.0) || (pix < aLowThrsl))
	{
	  (*pMapLow) = QGE_BW_WHITE;
	}
      else
	{
	  (*pMapLow) = QGE_BW_BLACK;
	}

      if ((pix == 0.0) || (pix < aHighThrsl))
	{
	  (*pMapHigh) = QGE_BW_WHITE;
	}
      else
	{
	  (*pMapHigh) = QGE_BW_BLACK;
	}
    }

  // highImg is seed of final result
  BinaryImage::operator=(highImg);

  // Add all points on edges with a gradient lower than high but
  // higher than low that are connected to strong edges
  for (int y = 0 ; y < _height ; ++y)
    {
      for (int x = 0; x < _width ; ++x)
	{

	  // if we have a seed
	  if (highImg.pixel(x, y) != QGE_BW_WHITE)
	    {
	      // Push starting point and clear from lowImg
	      Point pt(x, y);
	      stackPt.push(pt);
	      lowImg.setPixel(x, y, QGE_BW_WHITE);

	      // Trace the line from this point
	      while (! stackPt.empty())
		{
		  pt = stackPt.top();
		  stackPt.pop();
		  // write point to output and delete from highImg
		  int ptX = pt.x();
		  int ptY = pt.y();
		  setPixel(ptX, ptY, QGE_BW_BLACK);

		  highImg.setPixel(ptX, ptY, QGE_BW_WHITE);
		  
		  // Stack and delete points we want to go to next
		  for (int yCnt = ptY - 1 ; yCnt < (ptY + 2) ; ++yCnt)
		    {
		      for (int xCnt = ptX - 1 ; xCnt < (ptX + 2) ; ++xCnt)
			{
			  if ((yCnt >= 0)      &&
			      (yCnt < _height) &&
			      (xCnt >= 0)      &&
			      (xCnt < _width)  &&
			      (lowImg.pixel(xCnt, yCnt) != QGE_BW_WHITE))
			    {
			      pt.setXY(xCnt, yCnt);
			      stackPt.push(pt);
			      lowImg.setPixel(xCnt, yCnt, QGE_BW_WHITE);
			    }
			} // END for xCnt
		    } // END for yCnt

		} // END while

	    } // END if
	  
	} // END for x
    } // END for y
}
// -------------------------------------------------------------------

} // namespace qgar
