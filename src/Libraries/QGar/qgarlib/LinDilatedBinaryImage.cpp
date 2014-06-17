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
 * @file LinDilatedBinaryImage.cpp
 *
 * @brief Implementation of class qgar::LinDilatedBinaryImage.
 *
 * See file LinDilatedBinaryImage.h for the interface.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date   August 5, 2002  16:41
 * @since Qgar 2.0
 */



// STD
#include <sstream>
// QGAR
#include "GenImage.h"
#include "LinDilatedBinaryImage.h"
#include "QgarErrorDomain.h"



namespace qgar
{

// -------------------------------------------------------------------
// C O N S T R U C T O R
// -------------------------------------------------------------------


LinDilatedBinaryImage::LinDilatedBinaryImage(BinaryImage& anImg,
					     QGEorientation anOrient,
					     unsigned int aDilSize)


  : BinaryImage(anImg)

{
  perform(this, anOrient, aDilSize);
}


// -------------------------------------------------------------------
// L I N E A R   D I L A T I O N S
// -------------------------------------------------------------------


void
LinDilatedBinaryImage::perform(BinaryImage* anImg,
			       QGEorientation anOrient,
			       unsigned int aDilSize)
{
  // Find out which construction function to use
  switch (anOrient)
    {
    case QGE_ORIENTATION_HOR:
      dilateHor(anImg, aDilSize);
      break;
    case QGE_ORIENTATION_VER:
      dilateVer(anImg, aDilSize);
      break;
    case QGE_ORIENTATION_DIAG_POS:
      dilatePdiag(anImg, aDilSize);
      break;
    case QGE_ORIENTATION_DIAG_NEG:
      dilateNdiag(anImg, aDilSize);
      break;
    case QGE_ORIENTATION_ALL:
      dilateAll(anImg, aDilSize);
    }
}


// -------------------------------------------------------------------

// HORIZONTAL DILATION


void
LinDilatedBinaryImage::dilateHor(BinaryImage* anImg,
				 unsigned int aDilSize)



{
  int linSize = (2 * aDilSize) + 1;  // Size of dilation segment
  int width   = anImg->width();      // Image width & height
  int height  = anImg->height();
  
  if (linSize > width)
    {
      std::ostringstream os;
      os << "Horizontal dilation size ("
	 << aDilSize
	 << " -> "
	 << linSize
	 << ") too large for image "
	 << width
	 << " X "
	 << height;
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "void qgar::LinDilatedBinaryImage::dilateHor(qgar::BinaryImage*, unsigned int)",
			    os.str());
    }

  // pointers on current row
  BinaryImage::pointer behind;
  BinaryImage::pointer ahead;

  int mask; // number of pixels to dilate
  int i;    // current line number
  int j;    // current pixel number in the line

  // loop on all possible lines

  for (i = 0; i < height ; ++i)
    {
    
      // work directly on the line
      behind = anImg->pRow(i);

      // the first aDilSize pixels
      for (j = mask = 0; j < (int)aDilSize; ++j, ++behind)
	{
	  // the next aDilSize pixels are function of these
	  if (*behind)
	    {
	      mask = j + 1;
	    }
	}


    // the next aDilSize pixels
    for (ahead = behind; 
	 (j < linSize - 1) && (j < (width - (int)aDilSize - 1));
	 ++j, ++ahead)
      {
	// a non-zero implies a dilation
	if (*ahead)
	  {
	    mask = aDilSize + 1;
	  }
	if (mask)
	  {
	    *ahead = 1; // dilation at right
	    --mask;
	  }
      }


    // the rest of the line exept the last aDilSize
    for (; j < (width - (int)aDilSize); ++j)
      {
	if (*ahead)
	  {
	    mask = aDilSize + 1;
	  }

	if (mask)
	  {
	    *behind = 1; // dilation at left
	    *ahead = 1;
	    --mask;
	  }

	++behind;
	++ahead;
      }

    // the last pixels
    for (; j < width ; j++)
      {
	if (*ahead)
	  {
	    mask = aDilSize + 1;
	  }

	if (mask)
	  {
	    *behind = 1;
	    --mask;
	  }

	++behind;
	++ahead;
      }

    } // END for i
}


// -------------------------------------------------------------------

// VERTICAL DILATION


void
LinDilatedBinaryImage::dilateVer(BinaryImage* anImg,
				 unsigned int aDilSize)



{
  int linSize = (2 * aDilSize) + 1;  // Size of dilation segment
  int width   = anImg->width();      // Image width & height
  int height  = anImg->height();
  
  if (linSize > height)
    {
      std::ostringstream os;
      os << "Vertical dilation size ("
	 << aDilSize
	 << " -> "
	 << linSize
	 << ") too large for image "
	 << width
	 << " X "
	 << height;
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "void qgar::LinDilatedBinaryImage::dilateVer(qgar::BinaryImage*, unsigned int)",
			    os.str());
    }
  
  // pointers on current row
  BinaryImage::pointer behind;
  BinaryImage::pointer ahead;

  int mask; // number of pixels to dilate
  int i; // current line number
  int j; // current pixel number in the line

  // loop on all possible lines

  for (i = 0; i < width; ++i)
    {

      // work directly on the line
      behind = anImg->pColumn(i);

      // the first aDilSize pixels
      for (j = mask = 0; j < (int)aDilSize; ++j, behind += width)
	{
	  // the next aDilSize pixels are function of these
	  if (*behind)
	    {
	      mask = j + 1;
	    }
	}


    // the next aDilSize pixels
    for (ahead = behind; 
	 (j < linSize - 1) && (j < (height - (int)aDilSize - 1));
	 ++j, ahead += width)
      {
	// a non zero implies a dilation
	if (*ahead) mask = aDilSize + 1;
	if (mask)
	  {
	    *ahead = 1;
	    --mask;
	  }
      }


    // the rest of the line exect the last aDilSize        
    for (; j < (height - (int)aDilSize); ++j)
      {
	if (*ahead)
	  {
	    mask = aDilSize + 1;
	  }

	if (mask)
	  {
	    *behind = 1;
	    *ahead = 1;
	    --mask;
	  }

	behind += width;
	ahead += width;
      }


    // the last pixels
    for (; j < height ; ++j)
      {
      if (*ahead)
	{
	  mask = aDilSize + 1;
	}

      if (mask)
	{
	  *behind = 1;
	  --mask;
	}

      behind += width;
      ahead += width;
      }

    }// END for i   
}


// -------------------------------------------------------------------

// NE-SW DILATION


void
LinDilatedBinaryImage::dilatePdiag(BinaryImage* anImg,
				   unsigned int aDilSize)



{
  int linSize = (2 * aDilSize) + 1;  // Size of dilation segment
  int width   = anImg->width();      // Image width & height
  int height  = anImg->height();
  
  int diagSize = (2 * linSize) / 3;
  if ((diagSize > height) || (diagSize > width))
    {
      std::ostringstream os;
      os << "NE-SW dilation size ("
	 << aDilSize
	 << " -> "
	 << linSize
	 << ") too large for image "
	 << width
	 << " X "
	 << height;
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "void qgar::LinDilatedBinaryImage::dilatePDiag(qgar::BinaryImage*, unsigned int)",
			    os.str());
    }

  // pointers on current row
  BinaryImage::pointer behind;
  BinaryImage::pointer ahead;

  // the last line of image
  BinaryImage::pointer end = anImg->pRow(height - 1) + 1;

  int mask; // number of pixels to dilate
  int i; // current line number
  int j; // current pixel number in the line

  int length; // current line size

  // loop on all possible lines

  for (i = linSize; i < height + width - 1 - linSize; ++i)
    {
    
      // work directly on the line
    
      if (i < height)
	{
	  behind = anImg->pRow(i);
	  length = (width > i + 1 ? i + 1 : width);
	}
      else
	{
	  behind = end;
	  ++end;
	  length = ((width - i + height - 1) > height
		    ? height
		    : width - i + height - 1);
	}


    // the first aDilSize pixels
    for (j = mask = 0; j < (int)aDilSize; ++j, behind -= (width - 1))
      {
	// the next aDilSize pixels are function of these
	if (*behind)
	  {
	    mask = j + 1;
	  }
      }


    // the next aDilSize pixels
    for (ahead = behind; 
	 (j < linSize - 1) && (j < (length - (int)aDilSize - 1));
	 ++j, ahead -= (width - 1))
      {
      
	// a non zero implies a dilation
	if (*ahead)
	  {
	    mask = aDilSize + 1;
	  }

      if (mask)
	{
	  *ahead = 1; // dilation at right
	 --mask;
	}
      }

        
    // the rest of the line exect the last aDilSize
    for (; j < (length - (int)aDilSize); ++j)
      {
	if (*ahead)
	  {
	    mask = aDilSize + 1;
	  }

	if (mask)
	  {
	    *behind = 1; // dilation at left
	    *ahead = 1;
	    --mask;
	  }

	behind -= (width - 1);
	ahead -= (width - 1);
      }

    // the last pixels
    for (; j < length ; ++j)
      {
      if (*ahead)
	{
	  mask = aDilSize + 1;
	}

      if (mask)
	{
	  *behind = 1;
	  --mask;
	}

      behind -= (width - 1);
      ahead -= (width - 1);
      }

    } // END for i
}


// -------------------------------------------------------------------


// NW-SE DILATION

void
LinDilatedBinaryImage::dilateNdiag(BinaryImage* anImg,
				   unsigned int aDilSize)



{
  int linSize = (2 * aDilSize) + 1;  // Size of dilation segment
  int width   = anImg->width();      // Image width & height
  int height  = anImg->height();
  
  int diagSize = (2 * linSize) / 3;
  if ((diagSize > height) || (diagSize > width))
    {
      std::ostringstream os;
      os << "NW-SE dilation size ("
	 << aDilSize
	 << " -> "
	 << linSize
	 << ") too large for image "
	 << width
	 << " X "
	 << height;
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "void qgar::LinDilatedBinaryImage::dilateNDiag(qgar::BinaryImage*, unsigned int)",
			    os.str());
    }
  
  // pointers on current row
  BinaryImage::pointer behind;
  BinaryImage::pointer ahead;

  // the first line of image
  BinaryImage::pointer first = anImg->pRow(1) - linSize;

  int mask; // number of pixels to dilate
  int i; // current line number
  int j; // current pixel number in the line

  int length; // current line size


  // loop on all possible lines

  for (i = linSize; i < height + width - 1 - linSize; ++i)
    {
    
    // work directly on the line
    
    if (i < width)
      {
	behind = --first;
	length = (i + 1 > height ? height : i + 1);
      }
    else
      {
	behind = anImg->pRow(i - width + 1);
	length = (height - (i - width + 1) > width ? width : height - (i - width + 1));
      }


    // the first aDilSize pixels
    for (j = mask = 0; j < (int)aDilSize; ++j, behind += (width + 1))
      {
	// the next aDilSize pixels are function of these
	if (*behind)
	  {
	    mask = j + 1;
	  }
      }


    // the next aDilSize pixels
    for (ahead = behind; 
	 (j < linSize - 1) && (j < (length - (int)aDilSize - 1));
	 ++j, ahead += (width + 1))
      {      
	// a non zero implies a dilation
	if (*ahead)
	  {
	    mask = aDilSize + 1;
	  }

      if (mask)
	{
	  *ahead = 1; // dilation at right
	  --mask;
	}
      }


    // the rest of the line exect the last aDilSize
    for (; j < (length - (int)aDilSize); ++j)
      {
	if (*ahead)
	  {
	    mask = aDilSize + 1;
	  }

      if (mask)
	{
	  *behind = 1; // dilation at left
	  *ahead = 1;
	  --mask;
	}

      behind += (width + 1);
      ahead += (width + 1);
      }


    // the last pixels
    for (; j < length ; ++j)
      {
      if (*ahead)
	{
	  mask = aDilSize + 1;
	}

      if (mask)
	{
	  *behind = 1;
	  --mask;
	}
      
      behind += (width + 1);
      ahead += (width + 1);
      }
    
    } // END for i
}


// -------------------------------------------------------------------


// ALL-ORIENTATIONS DILATION

void
LinDilatedBinaryImage::dilateAll(BinaryImage* anImg,
				 unsigned int aDilSize)



{
  int linsize = (2 * aDilSize) + 1;  // Size of dilation segment
  int width   = anImg->width();      // Image width & height
  int height  = anImg->height();
  
  int diagSize = (2 * linsize) / 3;
  if ((diagSize > height) || (diagSize > width))
    {
      std::ostringstream os;
      os << "All-orientations dilation size ("
	 << aDilSize
	 << " -> "
	 << linsize
	 << ") too large for image "
	 << width
	 << " X "
	 << height;
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "void qgar::LinDilatedBinaryImage::dilateAll(qgar::BinaryImage*, unsigned int)",
			    os.str());
    }
  
  BinaryImage img2(*anImg);

  // Allocate a table for current input rows
  BinaryImage::pointer crow = new BinaryImage::value_type [anImg->width() * linsize];

  // Allocate a table for current output row
  BinaryImage::pointer orow = new BinaryImage::value_type [anImg->width()];
  
  BinaryImage::pointer p;
  BinaryImage::pointer q;
  

  // Now loop on all possible lines

  int i = 0;   // current line number in input image
  int l = aDilSize; // current line number in output image

  for ( ; l < (anImg->height() - (int)aDilSize) ; ++l, ++i)
    {

      int ii = i; // current line number while loading current rows

      for (q = crow ; ii < i + linsize ; ++ii, q += anImg->width())
	{
	  anImg->row(ii, q); // load rows into crow
	}

      int j = aDilSize;
      anImg->row(l, orow); // initialize orow with old values
      
      for (p = orow + aDilSize, q = crow + aDilSize ;
	   j < (anImg->width() - (int)aDilSize) ; ++j, ++q)
	{
	  // On all columns which can be processed
	  BinaryImage::value_type curhoriz = 0; // start with minimum for all
	  BinaryImage::value_type curverti = 0;
	  BinaryImage::value_type curpdiag = 0;
	  BinaryImage::value_type curndiag = 0;

	  BinaryImage::pointer sl = q;
	  int k = 0;
	  
	  for ( ; k < linsize ; ++k, sl += anImg->width())
	    {
	      if (*(sl - aDilSize + k) != 0)
		{
		  curndiag = 1;
		}

	      if (*sl != 0)
		{
		  curverti = 1;
		}

	      if (*(sl + aDilSize -k) != 0)
		{
		  curpdiag = 1;
		}

	      if (k == (int)aDilSize) // if we are on the medium line
		{
		  BinaryImage::pointer ssl = sl - aDilSize;
		  int kk = 0;
		  for ( ; kk < linsize ; ++kk, ++ssl)
		    {
		      if (*ssl != 0)
			{
			  curhoriz = 1;	// found a one
			  break; // no need to continue
			}
		    }
		}
	    } // END for k

	  *p = ((curndiag != 0) && (curpdiag != 0) &&
		(curhoriz != 0) && (curverti != 0)) ? 1 : 0;	// write result
	  ++p;
	} // END for p

      // Write result
      img2.setRow(l, orow);

    } // END for l

  for (i = 0; i < anImg->height(); ++i)
    {
      img2.row(i, orow);
      anImg->setRow(i, orow);
    }

  // Clean up
  delete [] crow;
  delete [] orow;
}

// -------------------------------------------------------------------

} // namespace qgar
