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
 * @file LinErodedBinaryImage.cpp
 *
 * @brief Implementation of class qgar::LinErodedBinaryImage.
 *
 * See file LinErodedBinaryImage.h for the interface.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date   August 5, 2002  16:08
 * @since  Qgar 2.0
 */



// STD
#include <sstream>
// QGAR
#include "GenImage.h"
#include "LinErodedBinaryImage.h"
#include "QgarErrorDomain.h"



namespace qgar
{

// -------------------------------------------------------------------
// C O N S T R U C T O R
// -------------------------------------------------------------------

LinErodedBinaryImage::LinErodedBinaryImage(const BinaryImage& anImg,
					   QGEorientation anOrient,
					   unsigned int anEroSize)



  : BinaryImage(anImg)

{
  perform(this, anOrient, anEroSize);
}


// -------------------------------------------------------------------
// O R I E N T E D    E R O S I O N S
// -------------------------------------------------------------------

// DISPATCHING

void LinErodedBinaryImage::perform(BinaryImage* anImg,
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

void LinErodedBinaryImage::erodeHor(BinaryImage* anImg,
				    unsigned int anEroSize)



{
  int linsize = (2 * anEroSize) + 1;  // Size of erosion segment
  int width   = anImg->width();
  int height  = anImg->height();
  
  if (linsize > width)
    {
      std::ostringstream os;
      os << "Horizontal erosion size "
	 << anEroSize
	 << " -> "
	 << linsize
	 << " too large for image "
	 << width
	 << " X "
	 << height;
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "void qgar::LinErodedBinaryImage::erodeHor(qgar::BinaryImage*, unsigned int)",
			    os.str());
    }
  
  // pointers on current row
  BinaryImage::pointer behind;
  BinaryImage::pointer ahead;

  int mask, i, j;

  for (i = 0; i < height ; ++i)
    {
      behind = anImg->pRow(i);
      
      for (j = mask = 0; j < (int)anEroSize; ++j, ++behind)
	{
	  if (!*behind)
	    {
	      mask = j + 1;
	    }
	  // XXXXXXXXXXXXXXXXXXXXXXXXX
	  // Laurent Fritz, 4 Sep 2006
	  // Erode pixel at beginning
	  else
	    {
	      *behind = 0;
	    }
	  // XXXXXXXXXXXXXXXXXXXXXXXXX
	}

      for (ahead = behind; 
	   (j < linsize - 1) && (j < width - (int)anEroSize - 1);
	   ++j, ++ahead)
	{
	  if (!*ahead)
	    {
	      mask = anEroSize + 1;
	    }
	  if (mask)
	    {
	      *ahead = 0;
	      --mask;
	    }
	}
        
      for (/* VOID */ ; j < width - (int)anEroSize ; ++j)
	{
	  if (!*ahead)
	    {
	      mask = anEroSize + 1;
	    }

	  if (mask)
	    {
	      *behind = 0;
	      *ahead = 0;
	      --mask;
	    }
	  ++behind;
	  ++ahead;
	}

      for (/* VOID */ ; j < width; ++j)
	{
	  if (!*ahead)
	    {
	      mask = anEroSize + 1;
	    }
	  // XXXXXXXXXXXXXXXXXXXXXXXXX
	  // Laurent Fritz, 4 Sep 2006
	  // Erode pixel at end
	  else
	    {
	      *ahead = 0;
	    }
	  // XXXXXXXXXXXXXXXXXXXXXXXXX

	  if (mask)
	    {
	      *behind = 0;
	      --mask;
	    }
	  ++behind;
	  ++ahead;
	}
    }
}

// -------------------------------------------------------------------
// VERTICAL EROSION

void LinErodedBinaryImage::erodeVer(BinaryImage* anImg,
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
			    "void qgar::LinErodedBinaryImage::erodeVer(qgar::BinaryImage*, unsigned int)",
			    os.str());
    }
  
  // pointers on current row
  BinaryImage::pointer behind;
  BinaryImage::pointer ahead;

  int mask, i, j;

  for (i = 0; i < width; ++i)
    {
      behind = anImg->pColumn(i);

      for (j = mask = 0; j < (int)anEroSize; ++j, behind += width)
	{
	  if (!*behind)
	    {
	      mask = j + 1;
	    }
	  // XXXXXXXXXXXXXXXXXXXXXXXXX
	  // Laurent Fritz, 4 Sep 2006
	  // Erode pixel at beginning
	  else
	    {
	      *behind = 0;
	    }
	  // XXXXXXXXXXXXXXXXXXXXXXXXX
	}

    for (ahead = behind; 
	 (j < linsize - 1) && (j < height - (int)anEroSize - 1);
	  ++j, ahead += width)
      {
      if (!*ahead)
	{
	  mask = anEroSize + 1;
	}
      if (mask)
	{
	  *ahead = 0;
	  --mask;
	}
      }
        
    for (; j < height - (int)anEroSize; ++j)
      {
	if (!*ahead)
	  {
	    mask = anEroSize + 1;
	  }

	if (mask)
	  {
	    *behind = 0;
	    *ahead = 0;
	    --mask;
	  }
	behind += width;
	ahead += width;
      }

    for (/* VOID */ ; j < height ; ++j)
      {
	if (!*ahead)
	  {
	    mask = anEroSize + 1;
	  }
	// XXXXXXXXXXXXXXXXXXXXXXXXX
	// Laurent Fritz, 4 Sep 2006
	// Erode pixel at end
	else
	  {
	    *ahead = 0;
	  }
	// XXXXXXXXXXXXXXXXXXXXXXXXX

	if (mask)
	  {
	    *behind = 0;
	    --mask;
	  }

	behind += width;
	ahead += width;
      }
    }
}

// -------------------------------------------------------------------
// NE-SW EROSION

void
LinErodedBinaryImage::erodePdiag(BinaryImage* anImg,
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
			    "void qgar::LinErodedBinaryImage::erodePDiag(qgar::BinaryImage*, unsigned int)",
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

  for (i = linsize; i < height + width - 1 - linsize; ++i)
    {
      // work directly on the line
    
      if (i < height)
	{
	  behind = anImg->pRow(i);
	  length = (width > i + 1 ? i + 1 : width);
	}
      else
	{
	  behind = ++end;
	  length = (width - i + height - 1> height ? height : width - i + height - 1);
	}

    // the first anEroSize pixels
      for (j = mask = 0; j < (int)anEroSize; ++j, behind -= (width - 1))
	{
	  // the next anEroSize pixels are function of these
	  if (!*behind)
	    {
	      mask = j + 1;
	    }
	  // XXXXXXXXXXXXXXXXXXXXXXXXX
	  // Laurent Fritz, 4 Sep 2006
	  // Erode pixel at beginning
	  else
	    {
	      *behind = 0;
	    }
	  // XXXXXXXXXXXXXXXXXXXXXXXXX
	}

      // the next anEroSize pixels
      for ( ahead = behind; 
	    (j < linsize - 1) && (j < length - (int)anEroSize - 1);
	    ++j, ahead -= (width - 1))
	{
	  // a non zero implies a dilatation
	  if (!*ahead)
	    {
	      mask = anEroSize + 1;
	    }
	  if (mask)
	    {
	      *ahead = 0; // dilatation at right
	      --mask;
	    }
	}
        
    // the rest of the line exect the last anEroSize
    for (/* VOID */ ; j < length - (int)anEroSize; ++j)
      {
	if (!*ahead)
	  {
	    mask = anEroSize + 1;
	  }

	if (mask)
	  {
	    *behind = 0; // dilatation at left
	    *ahead = 0;
	    --mask;
	  }
	behind -= (width - 1);
	ahead -= (width - 1);
      }

    // the last pixels
    for (/* VOID */ ; j < length ; ++j)
      {
	if (!*ahead)
	  {
	    mask = anEroSize + 1;
	  }
	// XXXXXXXXXXXXXXXXXXXXXXXXX
	// Laurent Fritz, 4 Sep 2006
	// Erode pixel at end
	else
	  {
	    *ahead = 0;
	  }
	// XXXXXXXXXXXXXXXXXXXXXXXXX

	if (mask)
	  {
	    *behind = 0;
	    --mask;
	  }
	behind -= (width - 1);
	ahead -= (width - 1);
      }

    }
  
}

// -------------------------------------------------------------------
// NW-SE EROSION

void LinErodedBinaryImage::erodeNdiag(BinaryImage* anImg,
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
			    "void qgar::LinErodedBinaryImage::erodeNDiag(qgar::BinaryImage*, unsigned int)",
			    os.str());
    }

  // pointers on current row
  BinaryImage::pointer behind;
  BinaryImage::pointer ahead;

  // the first line of image
  BinaryImage::pointer first = anImg->pRow(1) - linsize;

  int mask; // number of pixels to dilate
  int i; // current line number
  int j; // current pixel number in the line

  int length; // current line size

  // loop on all possible lines

  for (i = linsize; i < height + width - 1 - linsize; ++i)
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

      // the first anEroSize pixels
      for (j = mask = 0; j < (int)anEroSize; ++j, behind += (width + 1))
	{
	  // the next anEroSize pixels are function of these
	  if (!*behind)
	    {
	      mask = j + 1;
	    }
	  // XXXXXXXXXXXXXXXXXXXXXXXXX
	  // Laurent Fritz, 4 Sep 2006
	  // Erode pixel at beginning
	  else
	    {
	      *behind = 0;
	    }
	  // XXXXXXXXXXXXXXXXXXXXXXXXX
	}

    // the next anEroSize pixels
      for (ahead = behind; 
	   (j < linsize - 1) && (j < length - (int)anEroSize - 1);
	   ++j, ahead += (width + 1))
	{
      
	  // a non zero implies a dilatation
	  if (!*ahead)
	    {
	      mask = anEroSize + 1;
	    }
	  if (mask)
	    {
	      *ahead = 0; // dilatation at right
	      --mask;
	    }
	}
        
      // the rest of the line exect the last anEroSize
      for (/* VOID */ ; j < length - (int)anEroSize; ++j)
	{
	  if (!*ahead)
	    {
	      mask = anEroSize + 1;
	    }
	  
	  if (mask)
	    {
	      *behind = 0; // dilatation at left
	      *ahead = 0;
	      --mask;
	    }
	  behind += (width + 1);
	  ahead += (width + 1);
	}

      // the last pixels
      for (/* VOID */ ; j < length ; ++j)
	{
	  
	  if (!*ahead)
	    {
	      mask = anEroSize + 1;
	    }
	  // XXXXXXXXXXXXXXXXXXXXXXXXX
	  // Laurent Fritz, 4 Sep 2006
	  // Erode pixel at end
	  else
	    {
	      *ahead = 0;
	    }
	  // XXXXXXXXXXXXXXXXXXXXXXXXX

	  if (mask)
	    {
	      *behind = 0;
	      --mask;
	    }
	  behind += (width + 1);
	  ahead += (width + 1);
	}
      
    }

}

// -------------------------------------------------------------------
// ALL-ORIENTATIONS DILATION

void
LinErodedBinaryImage::erodeAll(BinaryImage* anImg,
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
			    "void qgar::LinErodedBinaryImage::erodeAll(qgar::BinaryImage*, unsigned int)",
			    os.str());
    }

  BinaryImage img2(*anImg);

  // Allocate a table for current input rows
  BinaryImage::pointer crow = new BinaryImage::value_type [width * linsize];

  // Allocate a table for current output row
  BinaryImage::pointer orow = new BinaryImage::value_type [width];
  
  BinaryImage::pointer p;
  BinaryImage::pointer q;
  
  // Now loop on all possible lines

  int i = 0;   // current line number in input image
  int l = anEroSize; // current line number in output image

  for (/* VOID */ ; l < height - (int)anEroSize ; ++l, ++i)
    {
      int ii = i; // current line number while loading current rows

      for (q = crow ; ii < i + linsize ; ++ii, q += width)
	{
	  anImg->row(ii, q); // load rows into crow
	}

      int j = anEroSize;
      anImg->row(l, orow); // initialize orow with old values
      
      for (p = orow + anEroSize, q = crow + anEroSize ;
	   j < width - (int)anEroSize ; ++j, ++q)
	{              // On all columns which can be processed
	  BinaryImage::value_type curhoriz = 1; // start with minimum for all
	  BinaryImage::value_type curverti = 1;
	  BinaryImage::value_type curpdiag = 1;
	  BinaryImage::value_type curndiag = 1;

	  BinaryImage::pointer sl = q;
	  int k = 0;
	  
	  for (/* VOID */ ; k < linsize ; ++k, sl += width)
	    {
	      if (*(sl - anEroSize + k) == 0)
		{
		  curndiag = 0;
		}
	      if (*sl == 0)
		{
		  curverti = 0;
		}
	      if (*(sl + anEroSize -k) == 0)
		{
		  curpdiag = 0;
		}
	      if (k == (int)anEroSize) // if we are on the medium line
		{
		  BinaryImage::pointer ssl = sl - anEroSize;
		  int kk = 0;
		  for (/* VOID */ ; kk < linsize ; ++kk, ++ssl)
		    {
		      if (*ssl == 0)
			{
			  curhoriz = 0;	// found a zero
			  break; // no need to continue
			}
		    } // END for kk
		}
	    } // END for k

          // Write result
	  *p++ = ((curndiag == 0) && (curpdiag == 0) &&
		  (curhoriz == 0) && (curverti == 0)) ? 0 : 1;
	}

      // Write result
      img2.setRow(l, orow);
    }

  for (i = 0; i < height; ++i)
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
