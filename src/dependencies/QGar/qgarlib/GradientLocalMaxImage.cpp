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
 * @file GradientLocalMaxImage.cpp
 *
 * @brief Implementation of class qgar::GradientLocalMaxImage.
 *
 * See file GradientLocalMaxImage.h for the interface.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date   July 3, 2001  16:14
 * @since  Qgar 1.0
 */



// STD
#include <cmath>
// QGAR
#include "AbstractGradientImage.h"
#include "GenImage.h"
#include "GradientLocalMaxImage.h"



using namespace std;



namespace qgar
{

// ----------------------------------------------------------------------
// C O N S T R U C T O R
// ----------------------------------------------------------------------


GradientLocalMaxImage::GradientLocalMaxImage(AbstractGradientImage& aGradImg)

  : FloatImage(aGradImg.accessDxImg())

{
  float* p = _pPixMap;

  // Set first row to zero
  for (int jCnt = 0 ; jCnt < _width ; ++jCnt, ++p)
    {
      *p = 0.0;
    }

  // References to derivative images
  const FloatImage& rDxImg = aGradImg.accessDxImg();
  const FloatImage& rDyImg = aGradImg.accessDyImg();

  // Loop on all rows where a local maximum can be found
  for (int iCnt = 1 ; iCnt < (_height - 1) ; ++iCnt)
    {

      // Set first pixel to zero
      *p = 0;
      ++p;
      
      // <======================= _width =======================>
      //
      // |      |             |      |      |            |      |
      // +------+--        ---+------+------+--        --+------+
      // |      |             |  px1 |      |            |      |
      // |      |             |      |      |            |      |
      // |      |             |  py1 |      |            |      |
      // +------+--        ---+------+------+--        --+------+
      // |      |             |  px2 |  px  |            |      |
      // |      |             |      |      |            |      |
      // |      |             |  py2 |  py  |            |      |
      // +------+--        ---+------+------+--        --+------+
      // |      |             |  px3 |      |            |      |
      // |      |             |      |      |            |      |
      // |      |             |  py3 |      |            |      |
      // +------+--        ---+------+------+--        --+------+
      // |      |             |      |      |            |      |
      //
      // Pointers in x derivatives image
      float* px1 = rDxImg.pPixMap() + (iCnt - 1) * _width;
      float* px2 = px1 + _width;
      float* px3 = px2 + _width;
      float* px  = px2 + 1;
      // Pointers in y derivatives image
      float* py1 = rDyImg.pPixMap() + (iCnt - 1) * _width;
      float* py2 = py1 + _width;
      float* py3 = py2 + _width;
      float* py  = py2 + 1;

      // Loop on all columns
      float cmp1 = 0.0;   // first value with which to compare
      float cmp2 = 0.0;   // second value with which to compare
      float mod  = 0.0;   // square of module of current point

      for (int jCnt = 1 ;
	   jCnt < (_width - 1) ; 
	   ++jCnt, ++px1, ++px2, ++px3, ++px, ++py1, ++py2, ++py3, ++py)
	{
	  if (fabs(*py) < (0.4142 * fabs(*px)))
	    {
	      //strongly horizontal gradient
	      cmp1 = *px2 * *px2 + *py2 * *py2;
	      cmp2 = *(px2 + 2) * *(px2 + 2) + *(py2 + 2) * *(py2 + 2);
	    }
	  else if (fabs(*px) < (0.4142 * fabs(*py)))
	    {
	      // strongly vertical gradient	      
	      cmp1 = *(px1 + 1) * *(px1 + 1) + *(py1 + 1) * *(py1 + 1);
	      cmp2 = *(px3 + 1) * *(px3 + 1) + *(py3 + 1) * *(py3 + 1);
	    }
	  else if (((*px > 0.0) && (*py > 0.0)) || ((*px < 0.0) && (*py < 0.0)))
	    {
	      // positive diagonal -- remember direction of axes!	      
	      cmp1 = *px1 * *px1 + *py1 * *py1;
	      cmp2 = *(px3 + 2) * *(px3 + 2) + *(py3 + 2) * *(py3 + 2);
	    }
	  else
	    {
	      // negative diagonal
	      cmp1 = *(px1 + 2) * *(px1 + 2) + *(py1 + 2) * *(py1 + 2);
	      cmp2 = *px3 * *px3 + *py3 * *py3;
	    }

	  mod = ((*px) * (*px)) + ((*py) * (*py));

	  if ((mod > cmp1) && (mod > cmp2))
	    {
	      *p = (float)sqrt(mod);
	      ++p;
	    }	  
	  else
	    {
	      *p = 0.0;
	      ++p;
	    }
	} // END for jCnt
      
      // Set last pixel to zero
      *p = 0;
      ++p;

    } // END for iCnt

  // Set last row to zero
  for (int jCnt = 0 ; jCnt < _width ; ++jCnt, ++p)
    {
      *p = 0.0;
    }
}


// ----------------------------------------------------------------------


} // namespace qgar
