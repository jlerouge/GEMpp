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
 * @file GeodesicRecBinaryImage.cpp
 *
 * @brief Implementation of class qgar::GeodesicRecBinaryImage.
 *
 * See file GeodesicRecBinaryImage.h for the interface.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date   August 6, 2002  17:20
 * @since  Qgar 2.0
 */



// STD
#include <queue>
#include <sstream>
// QGAR
#include "GenImage.h"
#include "GeodesicRecBinaryImage.h"
#include "QgarErrorDomain.h"



using namespace std;


namespace qgar
{

// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

GeodesicRecBinaryImage::GeodesicRecBinaryImage(BinaryImage& aMarkImg,
					       BinaryImage& aResImg)

  : BinaryImage(aMarkImg)
{
  if (   (aMarkImg.width()  != aResImg.width())
      || (aMarkImg.height() != aResImg.height()))
    {
      std::ostringstream os;
      os << "Marker image size ("
	 << aMarkImg.width()
	 << " X "
	 << aMarkImg.height()
	 << ") does not match result image size ("
	 << aResImg.width()
	 << " X "
	 << aResImg.height()
	 << ')';
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "qgar::GeodesicRecBinaryImage::GeodesicRecBinaryImage(qgar::BinaryImage&, qgar::BinaryImage&)",
			    os.str());
    }

  perform(this, &aResImg);
}


// -------------------------------------------------------------------
// G E O D E S I C   R E C O N S T R U C T I O N 
// -------------------------------------------------------------------

void GeodesicRecBinaryImage::perform(BinaryImage* aMarkImg,
				     BinaryImage* aResImg)
{

  int width = aMarkImg->width();    // Just some shortcuts
  int height = aMarkImg->height();

  // first enqueue the boundaries of marker image.

  // as we have to compare marker and goal image in the same time,
  // we won't enqueue the pointers on marker's pixels, but their
  // indice in pixMap (which are the same in goal's pixMap)
  queue<long> boundary;
  
  long indice; // indice in the queue

  int i,j,k,l; // here we have four imbricated loop...

  BinaryImage::pointer Jp; // pointer on marker image
  BinaryImage::pointer Ip; // pointer on goal image
  BinaryImage::pointer Jq; // pointer on current boundary pixel
  BinaryImage::pointer Iq; // pointer on current goal boundary pixel

  BinaryImage::pointer markerPixMap = aMarkImg->pPixMap(); // just some shortcuts
  BinaryImage::pointer goalPixMap = aResImg->pPixMap();
 
  Jp = markerPixMap;
  Ip = goalPixMap;

  int minK, minL;
  int maxK, maxL;

  for (i = 0; i < height; ++i)
    {

      for (j = 0; j < width; ++j, ++Jp, ++Ip)
	{
      
	  if (*Jp && *Ip)
	    {
	
	      // is this pixel in the boundary of marker image?

	      /*** definition of current pixel's neighborhood ***/

	      // between the first and the last line
	      if ( (i > 0) && (i < height - 1) )
		{
		  minK = -1;
		  maxK = 2;

		  // first pixel
		  if (!j)
		    {
		      minL = 0;
		      maxL = 2;
		    }
		  // between these two pixels
		  else if (j < width - 1)
		    {
		      minL = -1;
		      maxL = 2;
		    }
		  else
		    {
		      minL = -1;
		      maxL = 1;
		    }
		}
	      // first pixel
	      else if (Jp == markerPixMap)
		{
		  minK = 0;
		  minL = 0;
		  maxK = 2;
		  maxL = 2;
		}
	      // before last pixel of first line
	      else if (Jp < markerPixMap + width - 1)
		{
		  minK = 0;
		  minL = -1;
		  maxK = 2;
		  maxL = 2;
		}
	      // last pixel of first line
	      else if (Jp ==  markerPixMap + width - 1)
		{
		  minK = 0;
		  minL = -1;
		  maxK = 2;
		  maxL = 1;
		}
	      // first pixel of last line
	      else if (!j)
		{
		  minK = -1;
		  minL = 0;
		  maxK = 1;
		  maxL = 2;
		}
	      // before last pixel of last line
	      else if (j < width - 1)
		{
		  minK = -1;
		  minL = -1;
		  maxL = 2;
		  maxK = 1;
		}
	      // last pixel
	      else
		{
		  minL = -1;
		  minK = -1;
		  maxL = 1;
		  maxK = 1;
		}

	      for (k = minK; k < maxK; ++k)
		{
		  for (l = minL ; l < maxL; ++l)
		    {
		      Jq = Jp + k*width + l;
	  
		      if ( !*Jq )
			{
			  boundary.push(Jp - markerPixMap);
			  k = 2;
			  break;
			}
		    } // end for l
		} // end for k

	    } //endif

	}
    } // end of scan
  

  /*** propagation ***/
  
  //**** APPARENTLY NOT USED!
  //**** BinaryImage::value_type *minIndice = markerPixMap;
  //**** BinaryImage::value_type *maxIndice = minIndice + width*height - 1;

  while (!boundary.empty())
    {
      indice = boundary.front();
      boundary.pop();
    
      Jp = markerPixMap + indice;
      Ip = goalPixMap + indice;

      /*** definition of current pixel's neighborhood ***/

      // between the first and the last line
      if ( (Jp > markerPixMap + width - 1) && 
	   (Jp < markerPixMap + (height - 1)*width) )
	{
	  minK = -1;
	  maxK = 2;
	  
	  // first pixel
	  if ((Jp - markerPixMap) % width == 0)
	    {
	      minL = 0;
	      maxL = 2;
	    }
	  // last pixel
	  else if ((Jp - markerPixMap) % width == width - 1)
	    {
	      minL = -1;
	      maxL = 1;
	    }
	  // between these two pixels
	  else
	    {
	      minL = -1;
	      maxL = 2;
	    }
	}
      // first pixel
      else if (Jp == markerPixMap)
	{
	  minK = minL = 0;
	  maxK = maxL = 2;
	}
      // before last pixel of first line
      else if (Jp < markerPixMap + width - 1)
	{
	  minK = 0;
	  minL = -1;
	  maxK = 2;
	  maxL = 2;
	}
      // last pixel of first line
      else if (Jp ==  markerPixMap + width - 1)
	{
	  minK = 0;
	  minL = -1;
	  maxK = 2;
	  maxL = 1;
	}
      // first pixel of last line
      else if (Jp == markerPixMap + (height - 1)*width) 
	{
	  minK = -1;
	  minL = 0;
	  maxK = 1;
	  maxL = 2;
	}
      // before last pixel of last line
      else if (Jp < markerPixMap + height*width - 1)
	{
	  minK = -1;
	  minL = -1;
	  maxL = 2;
	  maxK = 1;
	}
      // last pixel
      else
	{
	  minL = -1;
	  minK = -1;
	  maxL = 1;
	  maxK = 1;
	}
      
      for (k = minK; k < maxK; ++k)
	{
	  
	  for (l = minL ; l < maxL; ++l)
	    {
	      indice = k*width + l;
	      Jq = Jp + indice;
	      Iq = Ip + indice;
	      
	      if ( (!*Jq) && *Iq )
		{
		  *Jq = 1;
		  boundary.push(Jq - markerPixMap);
		}
	    } // END for l
	} // END for k
      
    }
  
}

// ----------------------------------------------------------------------

} // namespace qgar
