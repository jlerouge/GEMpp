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
 * @file LinDilatedImage.cpp
 *
 * @brief Implementation of class qgar::LinDilatedImage.
 *
 * See file LinDilatedImage.h for the interface.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date   August 5, 2002  16:52
 * @since  Qgar 2.0
 */



// STD
#include <algorithm>
#include <sstream>
// QGAR
#include "GenImage.h"
#include "LinDilatedImage.h"
#include "QgarErrorDomain.h"



namespace qgar
{

// -------------------------------------------------------------------
// C O N S T R U C T O R
// -------------------------------------------------------------------

LinDilatedImage::LinDilatedImage(GreyLevelImage& anImg,
				 QGEorientation anOrient,
				 unsigned int aDilSize)


 : GreyLevelImage(anImg)

{
  perform(this, anOrient, aDilSize);
}

// -------------------------------------------------------------------
// L I N E A R   D I L A T I O N S
// -------------------------------------------------------------------
  

void LinDilatedImage::perform(GreyLevelImage* anImg,
			      QGEorientation anOrient,
			      unsigned int aDilSize)
{
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

void LinDilatedImage::dilateHor(GreyLevelImage* anImg,
				unsigned int aDilSize)



{
  int linsize = (2 * aDilSize) + 1;  // Size of dilation segment
  int width   = anImg->width();      // Image width & height
  int height  = anImg->height();
  
  if (linsize > width)
    {
      std::ostringstream os;
      os << "Horizontal dilation size ("
	 << aDilSize
	 << " -> "
	 << linsize
	 << ") too large for image "
	 << width
	 << " X "
	 << height;
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "void qgar::LinDilatedImage::dilateHor(qgar::GreyLevelImage*, unsigned int)",
			    os.str());
    }
  
  // Allocate a table for left propagated maximums
  GreyLevelImage::pointer outRow = new GreyLevelImage::value_type [width];
  
  GreyLevelImage::pointer pOutRow; // pointer on maximum's table
  GreyLevelImage::pointer inRow;   // pointers on current row
  GreyLevelImage::pointer pInRow;

  int l = 0;   // current line number
 
  // if width % linsize isn't equal to zero, we have to
  // simulate missing pixels at the end of each line

  int overPixels = width % linsize; // pixels in excess

  // and now we can process through each line

  for (; l < height ; ++l)
    {
        GreyLevelImage::value_type maximum = 0; // current local maximum
	int firstPixel; // first pixel number in current window
	int window; // the window of linsize pixels
      
    
	/*** propagation of maximums to the left ***/
    
	pInRow = anImg->pRow(l) + width - 1 - overPixels;
	pOutRow = outRow + width - 1 - overPixels;
    
	for ( firstPixel = overPixels; 
	      firstPixel < width;
	      firstPixel += linsize)
	  {

	    *pOutRow = *pInRow--;
	    maximum = *pOutRow--;

	    for (window = 1; window < linsize ; ++window, --pInRow)
	      {
		if (maximum < *pInRow) maximum = *pInRow;
		*pOutRow-- = maximum;
	      }
	  }

	// correction of the last overPixels if needed
    
	if (overPixels)
	  {
	    pInRow = anImg->pRow(l) + width - 1;
	    pOutRow = outRow + width - 1;
	    *pOutRow = *pInRow--;
	    maximum = *pOutRow--;
      
	    for (firstPixel = 1; firstPixel < linsize; ++firstPixel, --pInRow)
	      {
		if (maximum < *pInRow) maximum = *pInRow;
		*pOutRow-- = maximum;
	      }
	  }

	// PROPAGATION OF MAXIMUMS TO THE RIGHT,
	// WITH DIRECT COMPUTATION OF RESULT

	// first sequence:

	// we keep the first aDilSize pixels
	pInRow = anImg->pRow(l);
	inRow = pInRow + aDilSize;

	pOutRow = outRow;

	for (firstPixel = 0, maximum = *pInRow; 
	     firstPixel < (int)aDilSize; 
	     ++firstPixel, ++pInRow)
	  {
	    if (maximum < *pInRow)
	      {
		maximum = *pInRow;
	      }
	  }

	for (++firstPixel ; firstPixel < linsize; ++firstPixel, ++pInRow)
	  {
	    if (maximum < *pInRow)
	      {
		maximum = *pInRow;
	      }
	  }

	// the first result...
	if (maximum < *pInRow)
	  {
	    maximum = *pInRow;
	  }
	++pOutRow;
	++pInRow;
	*inRow++ = maximum;
      
	// first sequence complete, now we can run the process
	for ( ; firstPixel < width - overPixels; firstPixel += linsize)
	  {
	    maximum = *pInRow++;
	    *inRow = (*pOutRow < maximum ? maximum : *pOutRow);
	    ++inRow;
	    ++pOutRow;
	
	    for (window = 1;
		 window < linsize; 
		 ++window, ++pInRow, ++pOutRow, ++inRow)
	      {
		if (maximum < *pInRow)
		  {
		    maximum = *pInRow;
		  }
		*inRow = (*pOutRow < maximum ? maximum : *pOutRow);
	      }
	  }
      
	// we have to do the overPixels...
      
	if (overPixels)
	  {
	
	    for (maximum = *pInRow;
		 firstPixel < width;
		 ++firstPixel, ++pInRow, ++pOutRow, ++inRow)
	      {
		if (maximum < *pInRow)
		  {
		    maximum = *pInRow;
		  }
		*inRow = (*pOutRow < maximum ? maximum : *pOutRow);
	      }
	  }
    }
  
  // Clean up
  delete [] outRow;

}

// -------------------------------------------------------------------
// VERTICAL DILATION

void LinDilatedImage::dilateVer(GreyLevelImage* anImg,
				 unsigned int aDilSize)



{
  int linsize = (2 * aDilSize) + 1;  // Size of dilation segment
  int width   = anImg->width();      // Image width & height
  int height  = anImg->height();
  
  if (linsize > height)
    {
      std::ostringstream os;
      os << "Vertical dilation size ("
	 << aDilSize
	 << " -> "
	 << linsize
	 << ") too large for image "
	 << width
	 << " X "
	 << height;
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "void qgar::LinDilatedImage::dilateVer(qgar::GreyLevelImage*, unsigned int)",
			    os.str());
    }

  // Allocate a table for left propagated maximums
  GreyLevelImage::pointer outRow = new GreyLevelImage::value_type [height];
  
  GreyLevelImage::pointer pOutRow; // pointer on maximum's table
  GreyLevelImage::pointer inRow;   // pointers on current row
  GreyLevelImage::pointer pInRow;

  int l = 0;   // current line number
 
  // if width % linsize isn't equal to zero, we have to
  // simulate missing pixels at the end of each line

  int overPixels = height % linsize; // pixels in excess
  
  // and now we can process through each line

  for (; l < width ; l++)
    {
      GreyLevelImage::value_type maximum = 0; // current local maximum
      int firstPixel; // first pixel number in current window
      int window; // the window of linsize pixels

      // PROPAGATION OF MAXIMUMS TO THE LEFT
    
      pInRow = anImg->pColumn(l) + width * (height - 1 - overPixels);
      pOutRow = outRow + height - 1 - overPixels;
    
      for (firstPixel = overPixels; firstPixel < height; firstPixel += linsize)
	{

	  *pOutRow = *pInRow;
	  pInRow -= width;
	  maximum = *pOutRow--;

	  for (window = 1; window < linsize; ++window, pInRow -= width)
	    {
	      if (maximum < *pInRow)
		{
		  maximum = *pInRow;
		}
	      *pOutRow-- = maximum;
	    }
	}

    // correction of the last overPixels if needed
    
    if (overPixels)
      {
	pInRow = anImg->pColumn(l) + width * (height - 1);
	pOutRow = outRow + height - 1;
	*pOutRow = *pInRow;
	pInRow -= width;
	maximum = *pOutRow--;
      
	for (firstPixel = 1; firstPixel < linsize; ++firstPixel, pInRow -= width)
	  {
	    if (maximum < *pInRow)
	      {
		maximum = *pInRow;
	      }
	    *pOutRow-- = maximum;
	  }
      }
      
    // PROPAGATION OF MAXIMUMS TO THE RIGHT,
    // WITH DIRECT COMPUTATION OF RESULT
    
    // first sequence:

    // we keep the first aDilSize pixels
    pInRow = anImg->pColumn(l);
    inRow = pInRow + aDilSize * width;

    pOutRow = outRow;

    for (firstPixel = 0, maximum = *pInRow; 
	 firstPixel < (int)aDilSize; 
	 ++firstPixel, pInRow += width)
      {
	if (maximum < *pInRow)
	  {
	    maximum = *pInRow;
	  }
      } 
    
    for (++firstPixel; firstPixel < linsize; ++firstPixel, pInRow += width)
      {
	if (maximum < *pInRow)
	  {
	    maximum = *pInRow;
	  }
      } 

    // the first result...
    if (maximum < *pInRow)
      {
	maximum = *pInRow;
      }
    ++pOutRow;
    pInRow += width;
    *inRow = maximum;
    inRow += width;
  
    // first sequence complete, now we can run the process
    for ( ; firstPixel < height - overPixels; firstPixel += linsize)
      {
	maximum = *pInRow;
	pInRow += width;
	*inRow = (*pOutRow < maximum ? maximum : *pOutRow);
	inRow += width;
	*pOutRow++;

      for (window = 1; 
	   window < linsize; 
	   ++window, pInRow += width, ++pOutRow, inRow += width)
	{
	  if (maximum < *pInRow)
	    {
	      maximum = *pInRow;
	    }
	  *inRow = (*pOutRow < maximum ? maximum : *pOutRow);
	}
      }
    
    // we have to do the overPixels...
    
    if (overPixels)
      {
	for (maximum = *pInRow;
	     firstPixel < height;
	     ++firstPixel, pInRow += width, ++pOutRow, inRow += width)
	  {
	    if (maximum < *pInRow)
	      {
		maximum = *pInRow;
	      }
	    *inRow = (*pOutRow < maximum ? maximum : *pOutRow);
	  }
      }
    }

  // Clean up
  delete [] outRow;
}

// -------------------------------------------------------------------
// NE-SW DILATION

void
LinDilatedImage::dilatePdiag(GreyLevelImage* anImg,
			     unsigned int aDilSize)



{
  int linsize = (2 * aDilSize) + 1;  // Size of dilation segment
  int width   = anImg->width();      // Image width & height
  int height  = anImg->height();
  
  // Approximative length of the projection of the dilation size
  // on one of the coordinate axis
  int diagSize = (2 * linsize) / 3;
  if ((diagSize > height) || (diagSize > width))
    {
      std::ostringstream os;
      os << "NE-SW dilation size ("
	 << aDilSize
	 << " -> "
	 << linsize
	 << ") too large for image "
	 << width
	 << " X "
	 << height;
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "void qgar::LinDilatedImage::dilatePDiag(qgar::GreyLevelImage*, unsigned int)",
			    os.str());
    }
  
  int i = (width > height ? width : height);

  // Allocate a table for left propagated maximums
  GreyLevelImage::pointer outRow = new GreyLevelImage::value_type [i];

  // Allocate a table for current line
  GreyLevelImage::pointer diagRow = new GreyLevelImage::value_type [i];
  
  GreyLevelImage::pointer pOutRow; // pointer on maximum's table

  GreyLevelImage::pointer inRow;
  GreyLevelImage::pointer pInRow;  // pointers on current row

  // the last line of image
  GreyLevelImage::pointer end = anImg->pRow(height - 1) + 1;

  int l = linsize;   // current line number

  int length; // current line size
 
  // if width % linsize isn't equal to zero, we have to
  // simulate missing pixels at the end of each line

  int overPixels;
      
  GreyLevelImage::value_type maximum = 0; // current local maximum
  int firstPixel; // first pixel number in current window
  int window; // the window of linsize pixels

  // and now we can process through each line

  for ( ; l < height + width - 1 - linsize; ++l)
    {
    
      if (l < height)
	{
	  inRow = anImg->pRow(l);
	  length = (width > l + 1 ? l + 1 : width);
	}
      else
	{
	  inRow = end;
	  i = width - l + height - 1;
	  length = (i > height ? height : i);
	}

      pInRow = diagRow;

      // load the current line
      for (i = 0 ; i < length; ++i)
	{
	  *pInRow++ = *inRow;
	  inRow -= (width - 1);
	}

      overPixels = length % linsize; // pixels in excess
    
      /*** propagation of maximums to the left ***/
    
      pInRow = diagRow + length - 1 - overPixels;
      pOutRow = outRow + length - 1 - overPixels;
    
      for (firstPixel = overPixels; firstPixel < length; firstPixel += linsize)
	{
	  *pOutRow = *pInRow--;
	  maximum = *pOutRow--;

	  for(window = 1; window < linsize ; ++window, --pInRow)
	    {
	      if (maximum < *pInRow)
		{
		  maximum = *pInRow;
		}
	      *pOutRow-- = maximum;
	    }
	}

    // correction of the last overPixels if needed
    
    if (overPixels)
      {
	pInRow = diagRow + length - 1;
	pOutRow = outRow + length - 1;
	*pOutRow = *pInRow--;
	maximum = *pOutRow--;
      
	for (firstPixel = 1; firstPixel < linsize; ++firstPixel, --pInRow)
	  {
	    if (maximum < *pInRow)
	      {
		maximum = *pInRow;
	      }
	    *pOutRow-- = maximum;
	  }
      }
      
    /*** propagation of maximums to the right, ***/ 
    /***   with direct computation of result.  ***/

    // first sequence:

    // we keep the first aDilSize pixels
    pInRow = diagRow;
    inRow = pInRow + aDilSize;

    pOutRow = outRow;

    for (firstPixel = 0, maximum = *pInRow; 
	 firstPixel < (int)aDilSize; 
	 ++firstPixel, ++pInRow)
      {
	if (maximum < *pInRow)
	  {
	    maximum = *pInRow;
	  }
      }

    for (++firstPixel; 
	 firstPixel < linsize;
	 ++firstPixel, ++pInRow)
      {
	if (maximum < *pInRow)
	  {
	    maximum = *pInRow;
	  }
      }

    // the first result...
    if (maximum < *pInRow)
      {
	maximum = *pInRow;
      }
    ++pOutRow;
    ++pInRow;
    *inRow++ = maximum;
           
      
    // first sequence complete, now we can run the process
    for ( ; firstPixel < length - overPixels; firstPixel += linsize)
      {
	maximum = *pInRow++;
	*inRow = (*pOutRow < maximum ? maximum : *pOutRow);
	++inRow;
	++pOutRow;
	
	for (window = 1; window < linsize; ++window, ++pInRow, ++pOutRow, ++inRow)
	  {
	    if (maximum < *pInRow)
	      {
		maximum = *pInRow;
	      }
	    *inRow = (*pOutRow < maximum ? maximum : *pOutRow);
	  }
      }
      
    // we have to do the overPixels...
    
    if (overPixels)
      {
	for (maximum = *pInRow;
	     firstPixel < length;
	     ++firstPixel, ++pInRow, ++pOutRow, ++inRow)
	  {
	    if (maximum < *pInRow)
	      {
		maximum = *pInRow;
	      }
	    *inRow = (*pOutRow < maximum ? maximum : *pOutRow);
	  }
      }

    // save the current line
    if (l < height)
      {
	inRow = anImg->pRow(l);
      }
    else
      {
	inRow = ++end;
      }

    pInRow = diagRow;

    for (i = 0 ; i < length ; ++i)
      {
	*inRow = *pInRow++;
	inRow -= (width - 1);
      }
    
    }
  
  // Clean up
  delete [] outRow;
  delete [] diagRow;
}

// -------------------------------------------------------------------
// NW-SE DILATION

void LinDilatedImage::dilateNdiag(GreyLevelImage* anImg,
				 unsigned int aDilSize)



{
  int linsize = (2 * aDilSize) + 1;  // Size of dilation segment
  int width   = anImg->width();      // Image width & height
  int height  = anImg->height();
  
  // Approximative length of the projection of the dilation size
  // on one of the coordinate axis
  int diagSize = (2 * linsize) / 3;
  if ((diagSize > height) || (diagSize > width))
    {
      std::ostringstream os;
      os << "NW-SE dilation size ("
	 << aDilSize
	 << " -> "
	 << linsize
	 << ") too large for image "
	 << width
	 << " X "
	 << height;
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "void qgar::LinDilatedImage::dilateNDiag(qgar::GreyLevelImage*, unsigned int)",
			    os.str());
    }
  
  int i = (width > height ? width : height);

  // Allocate a table for left propagated maximums
  GreyLevelImage::pointer outRow = new GreyLevelImage::value_type [i];

  // Allocate a table for current line
  GreyLevelImage::pointer diagRow = new GreyLevelImage::value_type [i];
  
  GreyLevelImage::pointer pOutRow; // pointer on maximum's table

  GreyLevelImage::pointer inRow;
  GreyLevelImage::pointer pInRow;  // pointers on current row

  // the first line of image
  GreyLevelImage::pointer first = anImg->pRow(1) - linsize - 1;

  int l = linsize;   // current line number

  int length; // current line size
 
  // if width % linsize isn't equal to zero, we have to
  // simulate missing pixels at the end of each line

  int overPixels;
      
  GreyLevelImage::value_type maximum = 0; // current local maximum
  int firstPixel; // first pixel number in current window
  int window; // the window of linsize pixels

  // and now we can process through each line

  for ( ; l < height + width - 1 - linsize; ++l)
    {
    
      if (l < width)
	{
	  inRow = first;
	  length = (l + 1 > height ? height : l + 1);
	}
      else
	{
	  inRow = anImg->pRow(l - width + 1);
	  i = height - (l - width + 1);
	  length = (i > width ? width : i);
	}

      pInRow = diagRow;

      // load the current line
      for (i = 0 ; i < length; ++i)
	{
	  *pInRow++ = *inRow;
	  inRow += (width + 1);
	}
  
      overPixels = length % linsize; // pixels in excess
      
      /*** propagation of maximums to the left ***/
    
      pInRow = diagRow + length - 1 - overPixels;
      pOutRow = outRow + length - 1 - overPixels;
    
      for (firstPixel = overPixels; firstPixel < length; firstPixel += linsize)
	{
	  *pOutRow = *pInRow--;
	  maximum = *pOutRow--;

	  for (window = 1; window < linsize; ++window, --pInRow)
	    {
	      if (maximum < *pInRow)
		{
		  maximum = *pInRow;
		}
	      *pOutRow-- = maximum;
	    }
	}

    // correction of the last overPixels if needed
    
    if (overPixels)
      {
	pInRow = diagRow + length - 1;
	pOutRow = outRow + length - 1;
	*pOutRow = *pInRow--;
	maximum = *pOutRow--;
      
	for (firstPixel = 1; firstPixel < linsize; ++firstPixel, --pInRow)
	  {
	    if (maximum < *pInRow)
	      {
		maximum = *pInRow;
	      }
	    *pOutRow-- = maximum;
	  }
      }

    /*** propagation of maximums to the right, ***/ 
    /***   with direct computation of result.  ***/

    // first sequence:

    // we keep the first aDilSize pixels
    pInRow = diagRow;
    inRow = pInRow + aDilSize;

    pOutRow = outRow;

    for (firstPixel = 0, maximum = *pInRow; 
	 firstPixel < (int)aDilSize; 
	 ++firstPixel, ++pInRow)
      {
	if (maximum < *pInRow)
	  {
	    maximum = *pInRow;
	  }
      }

    for (++firstPixel; firstPixel < linsize; ++firstPixel, ++pInRow)
      {
	if (maximum < *pInRow)
	  {
	    maximum = *pInRow;
	  }
      }

    // the first result...
    if (maximum < *pInRow)
      {
	maximum = *pInRow;
      }
    ++pOutRow;
    ++pInRow;
    *inRow++ = maximum;
      
    // first sequence complete, now we can run the process
    for ( ; firstPixel < length - overPixels; firstPixel += linsize)
      {
	maximum = *pInRow++;
	*inRow = (*pOutRow < maximum ? maximum : *pOutRow);
	++inRow;
	++pOutRow;
	
	for (window = 1; window < linsize; ++window, ++pInRow, ++pOutRow, ++inRow)
	  {
	    if (maximum < *pInRow)
	      {
		maximum = *pInRow;
	      }
	    *inRow = (*pOutRow < maximum ? maximum : *pOutRow);
	  }
      }
      
    // we have to do the overPixels...
      
    if (overPixels)
      {
	for (maximum = *pInRow;
	     firstPixel < length;
	     ++firstPixel, ++pInRow, ++pOutRow, ++inRow)
	  {
	    if (maximum < *pInRow)
	      {
		maximum = *pInRow;
	      }
	    *inRow = (*pOutRow < maximum ? maximum : *pOutRow);
	  }
      }

    // save the current line
    
    if (l < width)
      {
	inRow = --first;
      }
    else
      {
	inRow = anImg->pRow(l - width + 1);
      }
   
    pInRow = diagRow;

    for (i = 0 ; i < length ; ++i)
      {
	*inRow = *pInRow++;
	inRow += (width + 1);
      }

    }

  // Clean up
  delete [] outRow;
  delete [] diagRow;
}

// -------------------------------------------------------------------
// ALL-ORIENTATIONS DILATION

void LinDilatedImage::dilateAll(GreyLevelImage* anImg,
				  unsigned int aDilSize)



{
  int linsize = (2 * aDilSize) + 1;  // Size of dilation segment
  int width   = anImg->width();      // Image width & height
  int height  = anImg->height();
  
  // Approximative length of the projection of the dilation size
  // on one of the coordinate axis
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
			    "void qgar::LinDilatedImage::dilateAll(qgar::GreyLevelImage*, unsigned int)",
			    os.str());
    }
  
  GreyLevelImage work(*anImg);

  // Allocate a table for current input rows
  GreyLevelImage::pointer crow = new GreyLevelImage::value_type [anImg->width() * linsize];

  // Allocate a table for current output row
  GreyLevelImage::pointer orow = new GreyLevelImage::value_type [anImg->width()];
  
  GreyLevelImage::pointer p;
  GreyLevelImage::pointer q;
  
  // Now loop on all possible lines

  int i = 0;   // current line number in input image
  int l = aDilSize; // current line number in output image

  for ( ; l < height - (int)aDilSize ; ++l, ++i)
    {
      int ii = i; // current line number while loading current rows

      for (q = crow ; ii < i + linsize ; ++ii, q += width)
	{
	  anImg->row(ii, q); // load rows into crow
	}

      int j = aDilSize;
      anImg->row(l, orow); // initialize orow with old values
      
      for (p = orow + aDilSize, q = crow + aDilSize ;
	   j < width - (int)aDilSize ;
	   ++j, ++q)
	{
	  // On all columns which can be processed
	  GreyLevelImage::value_type curhoriz = 0; // start with minimum for all
	  GreyLevelImage::value_type curverti = 0;
	  GreyLevelImage::value_type curpdiag = 0;
	  GreyLevelImage::value_type curndiag = 0;

	  GreyLevelImage::pointer sl = q;
	  int k = 0;
	  
	  for ( ; k < linsize ; ++k, sl += width)
	    {
	      if (*(sl - aDilSize + k) > curndiag)
		{
		  curndiag = *(sl - aDilSize +k);
		}

	      if (*sl > curverti)
		{
		  curverti = *sl;
		}

	      if (*(sl + (int)aDilSize - k) > curpdiag)
		{
		  curpdiag = *(sl + aDilSize - k);
		}

	      if (k == (int)aDilSize) // if we are on the medium line
		{
		  GreyLevelImage::pointer ssl = sl - aDilSize;

		  for (int kk = 0 ; kk < linsize ; ++kk, ++ssl)
		    {
		      if (*ssl > curhoriz)
			{
			  curhoriz = *ssl; // found a new maximum
			}
		    }
		}
	    }

	  // write result
	  *p++ = std::min(std::min(curndiag, curpdiag), std::min(curhoriz, curverti));
	}

      // Write result
      work.setRow(l, orow);
    }
  
  for (i = 0; i < height; ++i)
    {
      work.row(i, crow);
      anImg->setRow(i, crow);
    }

  // Clean up
  delete [] crow;
  delete [] orow;
}

// -------------------------------------------------------------------

} // namespace qgar
