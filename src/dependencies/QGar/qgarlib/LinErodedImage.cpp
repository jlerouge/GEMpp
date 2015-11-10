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
 * @file LinErodedImage.cpp
 *
 * @brief Implementation of class qgar::LinErodedImage.
 *
 * See file LinErodedImage.h for the interface.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date   August 5, 2002  17:16
 * @since  Qgar 2.0
 */



// STD
#include <algorithm>
#include <sstream>
// QGAR
#include "GenImage.h"
#include "LinErodedImage.h"
#include "QgarErrorDomain.h"



using namespace std;


namespace qgar
{

// -------------------------------------------------------------------
// C O N S T R U C T O R
// -------------------------------------------------------------------

LinErodedImage::LinErodedImage(GreyLevelImage& anImg,
			       QGEorientation anOrient,
			       unsigned int anEroSize)



  : GreyLevelImage(anImg)

{
  perform(this, anOrient, anEroSize);
}

// -------------------------------------------------------------------
// O R I E N T E D    E R O S I O N S
// -------------------------------------------------------------------

// DISPATCHING

void LinErodedImage::perform(GreyLevelImage* anImg,
			     QGEorientation anOrient,
			     unsigned int anEroSize)
{
  switch (anOrient)
    {
    case QGE_ORIENTATION_HOR:
      erodeHor(anImg, anEroSize);
      break;
    case QGE_ORIENTATION_VER:
      erodeVer(anImg, anEroSize);
      break;
    case QGE_ORIENTATION_DIAG_POS:
      erodePdiag(anImg, anEroSize);
      break;
    case QGE_ORIENTATION_DIAG_NEG:
      erodeNdiag(anImg, anEroSize);
      break;
    case QGE_ORIENTATION_ALL:
      erodeAll(anImg, anEroSize);
    }
}

// -------------------------------------------------------------------
// HORIZONTAL EROSION

void LinErodedImage::erodeHor(GreyLevelImage* anImg,
			      unsigned int anEroSize)



{
  int linsize = (2 * anEroSize) + 1;  // Size of erosion segment
  int width   = anImg->width();
  int height  = anImg->height();
  
  if (linsize > width)
    {
      std::ostringstream os;
      os << "Horizontal erosion size ("
	 << anEroSize
	 << " -> "
	 << linsize
	 << ") too large for image "
	 << width
	 << " X "
	 << height;
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "void qgar::LinErodedImage::erodeHor(qgar::GreyLevelImage*, unsigned int)",
			    os.str());
    }
  
  // Allocate a table for left propagated minimums
  GreyLevelImage::pointer outRow = new GreyLevelImage::value_type [width];
  
  GreyLevelImage::pointer pOutRow; // pointer on minimum's table
  GreyLevelImage::pointer inRow;   // pointers on current row
  GreyLevelImage::pointer pInRow;

  int l = 0;   // current line number
 
  // if width % linsize isn't equal to zero, we have to
  // simulate missing pixels at the end of each line

  int overPixels = width % linsize; // pixels in excess

  // and now we can process through each line

  for (; l < height; ++l)
    {
      
    GreyLevelImage::value_type minimum = 0; // current local minimum
    int firstPixel; // first pixel number in current window
    int window; // the window of linsize pixels
      
    
    /*** propagation of minimums to the left ***/
    
    pInRow = anImg->pRow(l) + width - 1 - overPixels;
    pOutRow = outRow + width - 1 - overPixels;
    
    for ( firstPixel = overPixels; 
	  firstPixel < width;
	  firstPixel += linsize)
      {
	*pOutRow = *pInRow--;
	minimum = *pOutRow--;

	for (window = 1; 
	     window < linsize ; 
	     ++window, --pInRow)
	  {
	    if (minimum > *pInRow)
	      {
		minimum = *pInRow;
	      }
	    *pOutRow-- = minimum;
	  }
      }

    // correction of the last overPixels if needed
    
    if (overPixels)
      {      
	pInRow = anImg->pRow(l) + width - 1;
	pOutRow = outRow + width - 1;
	*pOutRow = *pInRow--;
	minimum = *pOutRow--;
      
	for (firstPixel = 1; 
	     firstPixel < linsize; 
	     ++firstPixel, --pInRow)
	  {
	    if (minimum > *pInRow)
	      {
		minimum = *pInRow;
	      }
	    *pOutRow-- = minimum;
	  }
    }
      
    /*** propagation of minimums to the right, ***/ 
    /***   with direct computation of result.  ***/

    // first sequence:

    // we keep the first anEroSize pixels
    pInRow = anImg->pRow(l);
    inRow = pInRow + anEroSize;

    pOutRow = outRow;

    for ( firstPixel = 0, minimum = *pInRow; 
	  firstPixel < (int)anEroSize; 
	  ++firstPixel, ++pInRow) {
      if (minimum > *pInRow) minimum = *pInRow;
    }

    for ( ++firstPixel; 
	  firstPixel < linsize;
	  ++firstPixel, ++pInRow) {
      if (minimum > *pInRow) minimum = *pInRow;
    }

    // the first result...
    if (minimum > *pInRow) minimum = *pInRow;
    ++pOutRow;
    ++pInRow;
    *inRow++ = minimum;
           
      
    // first sequence complete, now we can run the process
    for ( ;
	  firstPixel < width - overPixels;
	  firstPixel += linsize) {
      minimum = *pInRow++;
      *inRow = (*pOutRow > minimum ? minimum : *pOutRow);
      ++inRow;
      ++pOutRow;
	
      for ( window = 1; 
	    window < linsize; 
	    ++window, ++pInRow, ++pOutRow, ++inRow){
	if (minimum > *pInRow) minimum = *pInRow;
	*inRow = (*pOutRow > minimum ? minimum : *pOutRow);
      }
    }
      
    // we have to do the overPixels...
      
    if (overPixels) {
	
      for ( minimum = *pInRow;
	    firstPixel < width;
	    ++firstPixel, ++pInRow, ++pOutRow, ++inRow) {
	if (minimum > *pInRow) minimum = *pInRow;
	*inRow = (*pOutRow > minimum ? minimum : *pOutRow);
      }
    }
  }
  
  // Clean up
  delete [] outRow;

}

// -------------------------------------------------------------------
// VERTICAL EROSION

void LinErodedImage::erodeVer(GreyLevelImage* anImg,
			      unsigned int anEroSize)



{
  int linsize = 2*anEroSize + 1;  // size of segment
  int width   = anImg->width();
  int height  = anImg->height();
  
  if (linsize > height)
    {
      std::ostringstream os;
      os << "Vertical erosion size ("
	 << anEroSize
	 << " -> "
	 << linsize
	 << ") too large for image "
	 << width
	 << " X "
	 << height;
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "void qgar::LinErodedImage::erodeVer(qgar::GreyLevelImage*, unsigned int)",
			    os.str());
    }

  // Allocate a table for left propagated minimums
  GreyLevelImage::pointer outRow = new GreyLevelImage::value_type [height];
  
  GreyLevelImage::pointer pOutRow; // pointer on minimum's table

  GreyLevelImage::pointer inRow;
  GreyLevelImage::pointer pInRow; // pointers on current row

  int l = 0;   // current line number
 
  // if width % linsize isn't equal to zero, we have to
  // simulate missing pixels at the end of each line

  int overPixels = height % linsize; // pixels in excess
  
  // and now we can process through each line

  for (; l < width ; ++l) {
      
    GreyLevelImage::value_type minimum = 0; // current local minimum
    int firstPixel; // first pixel number in current window
    int window; // the window of linsize pixels
         
 
    /*** propagation of minimums to the left ***/
    
    pInRow = anImg->pColumn(l) + width * (height - 1 - overPixels);
    pOutRow = outRow + height - 1 - overPixels;
    
    for ( firstPixel = overPixels; 
	  firstPixel < height;
	  firstPixel += linsize) {    

      *pOutRow = *pInRow;
      pInRow -= width;
      minimum = *pOutRow--;

      for ( window = 1; 
	    window < linsize; 
	    ++window, pInRow -= width) {
	if (minimum > *pInRow) minimum = *pInRow;
	*pOutRow-- = minimum;
      }
    }

    // correction of the last overPixels if needed
    
    if (overPixels) {
      
      pInRow = anImg->pColumn(l) + width * (height - 1);
      pOutRow = outRow + height - 1;
      *pOutRow = *pInRow;
      pInRow -= width;
      minimum = *pOutRow--;
      
      for ( firstPixel = 1; 
	    firstPixel < linsize; 
	    ++firstPixel, pInRow -= width) {
	if (minimum > *pInRow) minimum = *pInRow;
	*pOutRow-- = minimum;
      }
    }
      

    /*** propagation of minimums to the right, ***/ 
    /***   with direct computation of result.  ***/

    
    // first sequence:

    // we keep the first anEroSize pixels
    pInRow = anImg->pColumn(l);
    inRow = pInRow + anEroSize * width;

    pOutRow = outRow;

    for ( firstPixel = 0, minimum = *pInRow; 
	  firstPixel < (int)anEroSize; 
	  ++firstPixel, pInRow += width) {
      if (minimum > *pInRow) minimum = *pInRow;
    }    
    
    for ( ++firstPixel; 
	  firstPixel < linsize;
	  ++firstPixel, pInRow += width) {
      if (minimum > *pInRow) minimum = *pInRow;
    }    

    
    // the first result...
    if (minimum > *pInRow) minimum = *pInRow;
    ++pOutRow;
    pInRow += width;
    *inRow = minimum;
    inRow += width;
  
    
  
    // first sequence complete, now we can run the process
    for ( ;
	  firstPixel < height - overPixels;
	  firstPixel += linsize) {
      
      minimum = *pInRow;
      pInRow += width;
      *inRow = (*pOutRow > minimum ? minimum : *pOutRow);
      inRow += width;
      *pOutRow++;

      for ( window = 1; 
	    window < linsize; 
	    ++window, pInRow += width, ++pOutRow, inRow += width){
	if (minimum > *pInRow) minimum = *pInRow;
	*inRow = (*pOutRow > minimum ? minimum : *pOutRow);
      }
    }
    
    // we have to do the overPixels...
    
    if (overPixels) {

      for ( minimum = *pInRow;
	    firstPixel < height;
	    ++firstPixel, pInRow += width, ++pOutRow, inRow += width) {
	if (minimum > *pInRow) minimum = *pInRow;
	*inRow = (*pOutRow > minimum ? minimum : *pOutRow);
      }
    }
  }

  // Clean up
  delete [] outRow;
   
}

// -------------------------------------------------------------------
// NE-SW EROSION

void LinErodedImage::erodePdiag(GreyLevelImage* anImg,
				unsigned int anEroSize)



{
  int linsize = (2 * anEroSize) + 1;  // size of segment
  int width   = anImg->width();
  int height  = anImg->height();
  
  int diagSize = (2 * linsize) / 3;
  if ((diagSize > height) || (diagSize > width))
    {
      std::ostringstream os;
      os << "NE-SW erosion size ("
	 << anEroSize
	 << " -> "
	 << linsize
	 << ") too large for image "
	 << width
	 << " X "
	 << height;
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "void qgar::LinErodedImage::erodePDiag(qgar::GreyLevelImage*, unsigned int)",
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
      
  GreyLevelImage::value_type minimum = 0; // current local minimum
  int firstPixel; // first pixel number in current window
  int window; // the window of linsize pixels

  // and now we can process through each line

  for (; l < height + width - 1 - linsize; ++l) {
    
    if (l < height) {
      inRow = anImg->pRow(l);
      length = (width > l + 1 ? l + 1 : width);
    }
    else {
      inRow = end;
      i = width - l + height - 1;
      length = (i > height ? height : i);
    }

    pInRow = diagRow;

    // load the current line
    for (i = 0 ; i < length; ++i) {
      *pInRow++ = *inRow;
      inRow -= (width - 1);
    }


    overPixels = length % linsize; // pixels in excess
      
    
    /*** propagation of minimums to the left ***/
    
    pInRow = diagRow + length - 1 - overPixels;
    pOutRow = outRow + length - 1 - overPixels;
    
    for ( firstPixel = overPixels; 
	  firstPixel < length;
	  firstPixel += linsize) {

      *pOutRow = *pInRow--;
      minimum = *pOutRow--;

      for (window = 1; 
	   window < linsize ; 
	   ++window, --pInRow) {
	if (minimum > *pInRow) minimum = *pInRow;
	*pOutRow-- = minimum;
      }
    }

    // correction of the last overPixels if needed
    
    if (overPixels) {
      
      pInRow = diagRow + length - 1;
      pOutRow = outRow + length - 1;
      *pOutRow = *pInRow--;
      minimum = *pOutRow--;
      
      for ( firstPixel = 1; 
	    firstPixel < linsize; 
	    ++firstPixel, --pInRow) {
	if (minimum > *pInRow) minimum = *pInRow;
	*pOutRow-- = minimum;
      }
    }
      

    /*** propagation of minimums to the right, ***/ 
    /***   with direct computation of result.  ***/


    // first sequence:

    // we keep the first anEroSize pixels
    pInRow = diagRow;
    inRow = pInRow + anEroSize;

    pOutRow = outRow;

    for ( firstPixel = 0, minimum = *pInRow; 
	  firstPixel < (int)anEroSize; 
	  ++firstPixel, ++pInRow) {
      if (minimum > *pInRow) minimum = *pInRow;
    }

    for ( ++firstPixel; 
	  firstPixel < linsize;
	  ++firstPixel, ++pInRow) {
      if (minimum > *pInRow) minimum = *pInRow;
    }

    // the first result...
    if (minimum > *pInRow) minimum = *pInRow;
    ++pOutRow;
    ++pInRow;
    *inRow++ = minimum;
           
      
    // first sequence complete, now we can run the process
    for ( ;
	  firstPixel < length - overPixels;
	  firstPixel += linsize) {
      minimum = *pInRow++;
      *inRow = (*pOutRow > minimum ? minimum : *pOutRow);
      ++inRow;
      ++pOutRow;
	
      for ( window = 1; 
	    window < linsize; 
	    ++window, ++pInRow, ++pOutRow, ++inRow){
	if (minimum > *pInRow) minimum = *pInRow;
	*inRow = (*pOutRow > minimum ? minimum : *pOutRow);
      }
    }
      
    // we have to do the overPixels...
      
    if (overPixels) {
	
      for ( minimum = *pInRow;
	    firstPixel < length;
	    ++firstPixel, ++pInRow, ++pOutRow, ++inRow) {
	if (minimum > *pInRow) minimum = *pInRow;
	*inRow = (*pOutRow > minimum ? minimum : *pOutRow);
      }
    }

    // save the current line
    if (l < height)
      inRow = anImg->pRow(l);
    else
      inRow = ++end;

    pInRow = diagRow;
 
    for (i = 0 ; i < length ; ++i) {
      *inRow = *pInRow++;
      inRow -= (width - 1);
    }
    

  }
  
  // Clean up
  delete [] outRow;
  delete [] diagRow;
}

// -------------------------------------------------------------------
// NW-SE EROSION

void LinErodedImage::erodeNdiag(GreyLevelImage* anImg,
				unsigned int anEroSize)



{
  int linsize = 2*anEroSize + 1;  // size of segment
  int width   = anImg->width();
  int height  = anImg->height();
  
  int diagSize = (2 * linsize) / 3;
  if ((diagSize > height) || (diagSize > width))
    {
      std::ostringstream os;
      os << "NW-SE erosion size ("
	 << anEroSize
	 << " -> "
	 << linsize
	 << ") too large for image "
	 << width
	 << " X "
	 << height;
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "void qgar::LinErodedImage::erodeNDiag(qgar::GreyLevelImage*, unsigned int)",
			    os.str());
    }
  
  int i = (width > height ? width : height);

  // Allocate a table for left propagated minimums
  GreyLevelImage::pointer outRow = new GreyLevelImage::value_type [i];

  // Allocate a table for current line
  GreyLevelImage::pointer diagRow = new GreyLevelImage::value_type [i];
  
  GreyLevelImage::pointer pOutRow; // pointer on minimum's table

  GreyLevelImage::pointer inRow;
  GreyLevelImage::pointer pInRow;  // pointers on current row

  // the first line of image
  GreyLevelImage::pointer first = anImg->pRow(1) - linsize - 1;

  int l = linsize;   // current line number

  int length; // current line size
 
  // if width % linsize isn't equal to zero, we have to
  // simulate missing pixels at the end of each line

  int overPixels;
      
  GreyLevelImage::value_type minimum = 0; // current local minimum
  int firstPixel; // first pixel number in current window
  int window; // the window of linsize pixels

  // and now we can process through each line

  for (; l < height + width - 1 - linsize; ++l) {
    
    if (l < width) {
      inRow = first;
      length = (l + 1 > height ? height : l + 1);
    }
    else {
      inRow = anImg->pRow(l - width + 1);
      i = height - (l - width + 1);
      length = (i > width ? width : i);
    }

    pInRow = diagRow;

    // load the current line
    for (i = 0 ; i < length; ++i) {
      *pInRow++ = *inRow;
      inRow += (width + 1);
    }
  
    overPixels = length % linsize; // pixels in excess
      
    
    /*** propagation of minimums to the left ***/
    
    pInRow = diagRow + length - 1 - overPixels;
    pOutRow = outRow + length - 1 - overPixels;
    
    for ( firstPixel = overPixels; 
	  firstPixel < length;
	  firstPixel += linsize) {

      *pOutRow = *pInRow--;
      minimum = *pOutRow--;

      for (window = 1; 
	   window < linsize ; 
	   ++window, --pInRow) {
	if (minimum > *pInRow) minimum = *pInRow;
	*pOutRow-- = minimum;
      }
    }

    // correction of the last overPixels if needed
    
    if (overPixels) {
      
      pInRow = diagRow + length - 1;
      pOutRow = outRow + length - 1;
      *pOutRow = *pInRow--;
      minimum = *pOutRow--;
      
      for ( firstPixel = 1; 
	    firstPixel < linsize; 
	    ++firstPixel, --pInRow) {
	if (minimum > *pInRow) minimum = *pInRow;
	*pOutRow-- = minimum;
      }
    }
      

    /*** propagation of minimums to the right, ***/ 
    /***   with direct computation of result.  ***/


    // first sequence:

    // we keep the first anEroSize pixels
    pInRow = diagRow;
    inRow = pInRow + anEroSize;

    pOutRow = outRow;

    for ( firstPixel = 0, minimum = *pInRow; 
	  firstPixel < (int)anEroSize; 
	  ++firstPixel, ++pInRow) {
      if (minimum > *pInRow) minimum = *pInRow;
    }

    for ( ++firstPixel; 
	  firstPixel < linsize;
	  ++firstPixel, ++pInRow) {
      if (minimum > *pInRow) minimum = *pInRow;
    }

    // the first result...
    if (minimum > *pInRow) minimum = *pInRow;
    ++pOutRow;
    ++pInRow;
    *inRow++ = minimum;
           
      
    // first sequence complete, now we can run the process
    for ( ;
	  firstPixel < length - overPixels;
	  firstPixel += linsize) {
      minimum = *pInRow++;
      *inRow = (*pOutRow > minimum ? minimum : *pOutRow);
      ++inRow;
      ++pOutRow;
	
      for ( window = 1; 
	    window < linsize; 
	    ++window, ++pInRow, ++pOutRow, ++inRow){
	if (minimum > *pInRow) minimum = *pInRow;
	*inRow = (*pOutRow > minimum ? minimum : *pOutRow);
      }
    }
      
    // we have to do the overPixels...
      
    if (overPixels) {
	
      for ( minimum = *pInRow;
	    firstPixel < length;
	    ++firstPixel, ++pInRow, ++pOutRow, ++inRow) {
	if (minimum > *pInRow) minimum = *pInRow;
	*inRow = (*pOutRow > minimum ? minimum : *pOutRow);
      }
    }

    // save the current line
    
    if (l < width) inRow = first--;
    else inRow = anImg->pRow(l - width + 1);
   
    pInRow = diagRow;

    for (i = 0 ; i < length ; ++i) {
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

void LinErodedImage::erodeAll(GreyLevelImage* anImg,
				 unsigned int anEroSize)



{
  int linsize =  (2 * anEroSize) + 1;  // size of segment
  int diagSize = (2 * linsize) / 3;
  int width   = anImg->width();
  int height  = anImg->height();

  if ((diagSize > height) || (diagSize > width))
    {
      std::ostringstream os;
      os << "All-orientations erosion size ("
	 << anEroSize
	 << " -> "
	 << linsize
	 << ") too large for image "
	 << width
	 << " X "
	 << height;
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "void qgar::LinErodedImage::erodeAll(qgar::GreyLevelImage*, unsigned int)",
			    os.str());
    }

  GreyLevelImage work(*anImg);

  // Allocate a table for current input rows
  GreyLevelImage::pointer crow = new GreyLevelImage::value_type [width * linsize];

  // Allocate a table for current output row
  GreyLevelImage::pointer orow = new GreyLevelImage::value_type [width];
  
  GreyLevelImage::pointer p;
  GreyLevelImage::pointer q;
  
  // Now loop on all possible lines

  int i = 0;   // current line number in input image
  int l = anEroSize; // current line number in output image

  for ( ; l < height - (int)anEroSize ; ++l, ++i)
    {
      int ii = i; // current line number while loading current rows

      for (q = crow ; ii < i + linsize ; ++ii, q += width)
	anImg->row(ii, q); // load rows into crow

      int j = anEroSize;
      anImg->row(l, orow); // initialize orow with old values
      
      for (p = orow + anEroSize, q = crow + anEroSize ;
	   j < width - (int)anEroSize ; ++j, ++q)
	{
	  // On all columns which can be processed
	  // start with minimum for all
	  GreyLevelImage::value_type curhoriz = 255;
	  GreyLevelImage::value_type curverti = 255;
	  GreyLevelImage::value_type curpdiag = 255;
	  GreyLevelImage::value_type curndiag = 255;

	  GreyLevelImage::pointer sl = q;
	  int k = 0;
	  
	  for ( ; k < linsize ; ++k, sl += width)
	    {
	      if (*(sl - anEroSize + k) < curndiag)
		{
		  curndiag = *(sl - anEroSize + k);
		}
	      if (*sl < curverti)
		{
		  curverti = *sl;
		}
	      if (*(sl + anEroSize - k) < curpdiag)
		{
		  curpdiag = *(sl + anEroSize - k);
		}
	      if (k == (int)anEroSize) // if we are on the medium line
		{
		  GreyLevelImage::pointer ssl = sl - anEroSize;
		  int kk = 0;
		  for ( ; kk < linsize ; ++kk, ++ssl)
		    {
		      if (*ssl < curhoriz)
			{
			  curhoriz = *ssl;	// new minimum
			}
		    }
		}
	    }

	  // write result
	  *p++ = max(max(curndiag, curpdiag), max(curhoriz, curverti));
	}

      // Save result
      work.setRow(l, orow);
    }
  
  for (i = 0; i < height; ++i) {
    work.row(i, crow);
    anImg->setRow(i, crow);
  }

  // Clean up
  delete [] crow;
  delete [] orow;
}

// -------------------------------------------------------------------

} // namespace qgar
