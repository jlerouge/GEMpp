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
 * @file IsotropicDilatedBinaryImage.cpp
 *
 * @brief Implementation of class qgar::IsotropicDilatedBinaryImage.
 *
 * See file IsotropicDilatedBinaryImage.h for the interface.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date   July 3, 2001  15:46
 * @since  Qgar 1.0
 */



// QGAR
#include "GenImage.h"
#include "IsotropicDilatedBinaryImage.h"



namespace qgar
{

// ---------------------------------------------------------------------
// C O N S T R U C T O R
// ---------------------------------------------------------------------

IsotropicDilatedBinaryImage::IsotropicDilatedBinaryImage(BinaryImage& aBinImg,
							 unsigned int anIterNb)

  : BinaryImage(aBinImg)

{
  // Allocate tables for the rows to process
  BinaryImage::pointer row1 = new BinaryImage::value_type [_width];
  BinaryImage::pointer row2 = new BinaryImage::value_type [_width];
  BinaryImage::pointer row3 = new BinaryImage::value_type [_width];

  // Allocate a table for current output row
  BinaryImage::pointer orow = new BinaryImage::value_type [_width];

  // Create two work images
  BinaryImage* outputImg = new BinaryImage(aBinImg);

  // Loop on number of iterations
  for (unsigned int iCnt = 1 ; iCnt <= anIterNb ; ++iCnt)
    {
      BinaryImage* inputImg = new BinaryImage(*outputImg);  // from last iteration
      // No need to change the two first lines
      int i = 0; // current line number in input image
      int l = 1; // current line number in output image

      if ((iCnt % 2) != 0)
	{
	  // ______________________________________________________________
	  //
	  // 8-connectivity
	  // ______________________________________________________________

	  for ( /* VOID */ ; l < _height - 1 ; ++l, ++i)
	    {
	      inputImg->row(l, orow); // initialize with old values

	      inputImg->row(i, row1); // get input values
	      inputImg->row(i+1, row2);
	      inputImg->row(i+2, row3);

	      BinaryImage::pointer q = orow + 1;
	      int j = 1;
	      BinaryImage::pointer p1 = row1 + 1;
	      BinaryImage::pointer p2 = row2 + 1;
	      BinaryImage::pointer p3 = row3 + 1;

	      for ( ; j < _width - 1 ; ++j, ++p1, ++p2, ++p3, ++q)
		{              // On all columns which can be processed
		  BinaryImage::value_type curm = *p1; // start with a point
		  if (*p3 > curm)
		    {
		      curm = *p3;
		    }

		  if (*p2 > curm)
		    {
		      curm = *p2;
		    }

		  if (*(p2 - 1) > curm)
		    {
		      curm = *(p2-1);
		    }

		  if (*(p2 + 1) > curm)
		    {
		      curm = *(p2+1);
		    }

		  if (*(p1 - 1) > curm)
		    {
		      curm = *(p1-1);
		    }

		  if (*(p1 + 1) > curm)
		    {
		      curm = *(p1+1);
		    }

		  if (*(p3 - 1) > curm)
		    {
		      curm = *(p3-1);
		    }

		  if (*(p3 + 1) > curm)
		    {
		      curm = *(p3+1);
		    }

		  *q = curm;
		} // END for j

	      // Write result
	      outputImg->setRow(l, orow);

	    } // END for l

	  // ______________________________________________________________
	  //
	  // END 8-connectivity
	  // ______________________________________________________________
	}

      else

	{
	  // ______________________________________________________________
	  //
	  // 4-connectivity
	  // ______________________________________________________________

	  for ( /* VOID */ ; l < _height - 1 ; ++l, ++i)
	    {
	      inputImg->row(l, orow); // initialize with old values

	      inputImg->row(i,   row1); // get input values
	      inputImg->row(i+1, row2);
	      inputImg->row(i+2, row3);

	      BinaryImage::pointer q = orow + 1;
	      int j = 1;
	      BinaryImage::pointer p1 = row1 + 1;
	      BinaryImage::pointer p2 = row2 + 1;
	      BinaryImage::pointer p3 = row3 + 1;

	      for ( ; j < _width - 1 ; ++j, ++p1, ++p2, ++p3, ++q)
		{
		  // On all columns which can be processed
		  BinaryImage::value_type curm = *p1; // start with a point

		  if (*p3 > curm)
		    {
		      curm = *p3;
		    }

		  if (*p2 > curm)
		    {
		      curm = *p2;
		    }

		  if (*(p2 - 1) > curm)
		    {
		      curm = *(p2 - 1);
		    }

		  if (*(p2 + 1) > curm)
		    {
		      curm = *(p2 + 1);
		    }
		
		  *q = curm;
		} // END for j
	    
	      // Write result
	      outputImg->setRow(l, orow);

	    } // END for l

	  // ______________________________________________________________
	  //
	  // END 4-connectivity
	  // ______________________________________________________________
	}

      delete inputImg;

    } // END for iCnt


  // Copy final result to self
  for (int l = 0 ; l < _height ; ++l)
    {
      outputImg->row(l, orow); // initialize with old values
      setRow(l, orow);
    }

  // Clean up
  delete [] row1;
  delete [] row2;
  delete [] row3;
  delete [] orow;

  delete outputImg;
}

// -------------------------------------------------------------------

} // namespace qgar

