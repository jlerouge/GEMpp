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
 * @file  StandardDeviationImage.cpp
 *
 * @brief Implementation of class qgar::StandardDeviationImage.
 *
 *
 * See file StandardDeviationImage.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date   July 13, 2001  15:46
 * @since  Qgar 1.0
 */



// STD
#include <cmath>
#include <sstream>
// QGAR
#include "GenConvolImage.h"
#include "GenImage.h"
#include "GenMask2d.h"
#include "QgarErrorInvalidArg.h"
#include "StandardDeviationImage.h"



using namespace std;



namespace qgar
{

// ----------------------------------------------------------------------
// C O N S T R U C T O R
// ----------------------------------------------------------------------


StandardDeviationImage::StandardDeviationImage(const FloatImage& anImg,
					       FloatImage*& aMeanImg,
					       unsigned int aMaskSize)



  : FloatImage(anImg)

{
  if ((aMaskSize % 2) == 0)
    {
      ostringstream os;
      os << "Mask size must be an odd value: "
	 << aMaskSize;
      throw QgarErrorInvalidArg(__FILE__, __LINE__,
				"qgar::StandardDeviationImage::StandardDeviationImage(const qgar::FloatImage&, qgar::FloatImage*&, unsigned int)",
				os.str());
    }

  double coeff = 1.0 / (double) (aMaskSize * aMaskSize);
  DMask2d mymsk(aMaskSize, aMaskSize, coeff);
  
  // erase previous content of aMeanImg
  if (aMeanImg != 0)
    {
      delete aMeanImg;
    }

  // Compute mean
  aMeanImg = new FConvolImage(anImg, mymsk);

  int n = aMaskSize / 2;
  int r = n;   // row
  
  // Inner lines
  for (/* VOID */ ; r < _height - n ; ++r)
    {
      float* q = _pPixMap + r * _width;
      float* p = anImg.pPixMap() + (r - n) * _width;
      float* m = aMeanImg->pPixMap() + r * _width;
      //First columns
      int c = 0;   // column
      for (c = 0 ; c < n ; ++c, ++m)
	{
	  double sum = 0.0;
	  int cc = c - n;
	  float* pp = p;
	  for (int i = 0 ; i < (int)aMaskSize ; ++i)
	    {
	      for (int j = 0 ; j < (int)aMaskSize ; ++j, ++cc)
		{
		  sum +=   (*(pp + borderCols(cc)) - *m)
		         * (*(pp + borderCols(cc)) - *m);
		}
	      pp += _width;
	    }
	  *q = (float) (coeff * sqrt(sum));
	  ++q;
	}

      // Inner columns
      for (/* VOID */ ; c < _width - n ; ++c, ++p, ++m)
	{
	  double sum = 0.0;
	  float* pp = p;
	  for (int i = 0 ; i < (int)aMaskSize ; ++i, pp += _width)
	    {
	      float* ppp = pp;
	      for (int j = 0 ; j < (int)aMaskSize ; ++j, ++ppp)
		{
		  sum += (*ppp - *m) * (*ppp - *m);
		}
	    }
	  *q = (float) (coeff * sqrt(sum));
	  ++q;
	}

      // Reset
      p = anImg.pPixMap() + (r - n) * _width;
      // Last columns
      for (/* VOID */ ; c < _width ; ++c, ++m)
	{
	  double sum = 0.0;
	  int cc = c - n;
	  float* pp = p;
	  for (int i = 0 ; i < (int)aMaskSize ; ++i)
	    {
	      for (int j = 0 ; j < (int)aMaskSize ; ++j, ++cc)
		{
		  sum += (*(pp + borderCols(cc)) - *m) * (*(pp + borderCols(cc)) - *m);
		}
	      pp += _width;
	    }
	  *q = (float) (coeff * sqrt(sum));
	  ++q;
	}
    }

  // First lines
  r = 0;
  for (/* VOID */ ; r < n ; ++r)
    {
      float* q = _pPixMap + r * _width;
      float* m = aMeanImg->pPixMap() + r * _width;
      //First columns
      int c = 0;   // column
      for (c = 0 ; c < n ; ++c, ++m)
	{
	  double sum = 0.0;
	  int cc = c - n;
	  int rr = r - n;
	  for (int i = 0 ; i < (int)aMaskSize ; ++i, ++rr)
	    {
	      float* pp = anImg.pPixMap() + borderRows(rr) * _width;
	      for (int j = 0 ; j < (int)aMaskSize ; ++j, ++cc)
		{
		  sum += (*(pp + borderCols(cc)) - *m) * (*(pp + borderCols(cc)) - *m);
		}
	    }
	  *q = (float) (coeff * sqrt(sum));
	  ++q;
	}

      // Inner columns
      for (/* VOID */ ; c < _width - n ; ++c, ++m)
	{
	  double sum = 0.0;
	  int rr = r - n;
	  for (int i = 0 ; i < (int)aMaskSize ; ++i, ++rr)
	    {
	      float* pp = anImg.pPixMap() + borderRows(rr) * _width;
	      for (int j = 0 ; j < (int)aMaskSize ; ++j, ++pp)
		{
		  sum += (*pp - *m) * (*pp - *m);
		}
	    }
	  *q = (float) (coeff * sqrt(sum));
	  ++q;
	}

      // Last columns
      for (/* VOID */ ; c < _width ; ++c, ++m)
	{
	  double sum = 0.0;
	  int cc = c - n;
	  int rr = r - n;
	  for (int i = 0 ; i < (int)aMaskSize ; ++i, ++rr)
	    {
	      float* pp = anImg.pPixMap() + borderRows(rr) * _width;
	      for (int j = 0 ; j < (int)aMaskSize ; ++j, ++cc)
		{
		  sum += (*(pp + borderCols(cc)) - *m) * (*(pp + borderCols(cc)) - *m);
		}
	    }
	  *q = (float) (coeff * sqrt(sum));
	  ++q;
	}
    }
      
  // And same for last lines
  r = _height - n;
  for (/* VOID */ ; r < _height ; ++r)
    {
      float* q = _pPixMap + r * _width;
      float* m = aMeanImg->pPixMap() + r * _width;
      //First columns
      int c = 0;   // column
      for (c = 0 ; c < n ; ++c, ++m)
	{
	  double sum = 0.0;
	  int cc = c - n;
	  int rr = r - n;
	  for (int i = 0 ; i < (int)aMaskSize ; ++i, ++rr)
	    {
	      float* pp = anImg.pPixMap() + borderRows(rr) * _width;
	      for (int j = 0 ; j < (int)aMaskSize ; ++j, ++cc)
		{
		  sum += (*(pp + borderCols(cc)) - *m) * (*(pp + borderCols(cc)) - *m);
		}
	    }
	  *q = (float) (coeff * sqrt(sum));
	  ++q;
	}

      // Inner columns
      for (/* VOID */ ; c < _width - n ; ++c, ++m)
	{
	  double sum = 0.0;
	  int rr = r - n;
	  for (int i = 0 ; i < (int)aMaskSize ; ++i, ++rr)
	    {
	      float* pp = anImg.pPixMap() + borderRows(rr) * _width;
	      for (int j = 0 ; j < (int)aMaskSize ; ++j, ++pp)
		{
		  sum += (*pp - *m) * (*pp - *m);
		}
	    }
	  *++q = (float) (coeff * sqrt(sum));
	}

      // Last columns
      for (/* VOID */ ; c < _width ; ++c, ++m)
	{
	  double sum = 0.0;
	  int cc = c - n;
	  int rr = r - n;
	  for (int i = 0 ; i < (int)aMaskSize ; ++i, ++rr)
	    {
	      float* pp = anImg.pPixMap() + borderRows(rr) * _width;
	      for (int j = 0 ; j < (int)aMaskSize ; ++j, ++cc)
		{
		  sum += (*(pp + borderCols(cc)) - *m) * (*(pp + borderCols(cc)) - *m);
		}
	    }
	  *q = (float) (coeff * sqrt(sum));
	  ++q;
	}
    }
}

// ----------------------------------------------------------------------

} // namespace qgar
