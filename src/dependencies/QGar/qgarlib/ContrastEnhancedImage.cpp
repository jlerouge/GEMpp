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
 * @file   ContrastEnhancedImage.cpp
 * @brief  Implementation of class qgar::ContrastEnhancedImage.
 *
 * See file ContrastEnhancedImage.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date   July 3, 2001  17:12
 * @since  qgar 1.0
 */


// STD
#include <sstream>
// QGAR
#include "array.h"
#include "ContrastEnhancedImage.h"
#include "GenImage.h"
#include "QgarErrorDomain.h"



namespace qgar
{

// -------------------------------------------------------------------
// C O N S T R U C T O R
// -------------------------------------------------------------------
ContrastEnhancedImage::ContrastEnhancedImage(GreyLevelImage& anImg,
					     unsigned int aMaskSize)



  : GreyLevelImage(anImg)

{
  int sqsize = (2 * (int)aMaskSize) + 1;  // Effective mask size

  if ((sqsize > _width) || (sqsize > _height))
    {
      std::ostringstream os;
      os << "Mask ["
	 << sqsize
	 << " X "
	 << sqsize
	 << "] too large for image ["
	 << _width
	 << " X "
	 << _height
	 << "]";
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "qgar::ContrastEnhancedImage::ContrastEnhancedImage(qgar::GreyLevelImage&, unsigned int)",
			    os.str());
    }

  // Allocate a table for the maxima and minima per column
  GreyLevelImage::pointer ltabmax = new GreyLevelImage::value_type[_width];
  GreyLevelImage::pointer ltabmin = new GreyLevelImage::value_type[_width];

  // Allocate a table for current input row
  GreyLevelImage::pointer crow = new GreyLevelImage::value_type[_width];

  // Allocate a table for current output row
  GreyLevelImage::pointer orow = new GreyLevelImage::value_type[_width];
  
  GreyLevelImage::pointer p;
  GreyLevelImage::pointer q;
  
  // Now loop on all lines to process
  // As the image was created from anImg, by default the value of the pixels
  // is that of anImg, so we do not need to change the first and last rows

  int i = 0; // current line number in input image

  for (int l = (int)aMaskSize ; l < _height - (int)aMaskSize ; ++l, ++i)
    {
      // Update ltabmax and ltabmin
      GreyLevelImage::pointer smin = ltabmin;
      GreyLevelImage::pointer smax = ltabmax;

      // Set ltabmin to max value (255)
      qgFill(ltabmin, _width, static_cast<GreyLevelImage::value_type>(255));
      // Set ltabmax to min value (0)
      qgFill(ltabmax, _width, static_cast<GreyLevelImage::value_type>(0));
  
      // ii : current line number while computing ltab
      for (int ii = i ; ii < i + sqsize ; ++ii)
	{
	  anImg.row(ii, crow);  // get the current row of anImg
	  q = crow;
	  smin = ltabmin;
	  smax = ltabmax;

	  for (int j = 0 ; j < _width ; ++j, ++q, ++smin, ++smax)
	    {
	      if (*smax < *q)
		{
		  *smax = *q;
		}
	      if (*smin > *q)
		{
		  *smin = *q;
		}
	    } // END for j
	} // END for ii
  

      // And now process the current line

      row(l, orow); // initialize with old values
      
      p = orow + aMaskSize;
      q = crow + aMaskSize;
      smin = ltabmin, smax = ltabmax;

      for (int j = (int)aMaskSize ;
	   j < _width - (int)aMaskSize ;
	   ++j, ++smin, ++smax, ++p, ++q)
	{
	  // On all columns which can be processed
	  GreyLevelImage::value_type curmax = 0;    // current maximum
	  GreyLevelImage::value_type curmin = 255;  // current minimum
	  GreyLevelImage::pointer slmax = smax;
	  GreyLevelImage::pointer slmin = smin;
	  
	  for (int k = 0 ; k < sqsize ; ++k, ++slmin, ++slmax)
	    {
	      if (curmax < *slmax)
		{
		  curmax = *slmax;	// new maximum
		}
	      if (curmin > *slmin)
		{
		  curmin = *slmin;     // new minimum
		}
	    } // END for k

	  // Compute result
	  if ((curmax - *q) < (*q - curmin))
	    {
	      *p = curmax;
	    }
	  else
	    {
	      *p = curmin;
	    }
	} // END for j

      // Write result
      setRow(l, orow);

    } // END for l

  // Clean up
  delete [] ltabmin;
  delete [] ltabmax;
  delete [] crow;
  delete [] orow;
}

// -------------------------------------------------------------------

} // namespace qgar
