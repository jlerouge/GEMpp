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
 * @file GeodesicRecImage.cpp
 *
 * @brief Implementation of class qgar::GeodesicRecImage.
 *
 * See file GeodesicRecImage.h for the interface.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date   August 7, 2002  16:22
 * @since  Qgar 2.0
 */



// STD
#include <queue>
#include <sstream>
// QGAR
#include "DilatedImage.h"
#include "GenImage.h"
#include "GeodesicRecImage.h"
#include "QgarErrorDomain.h"



using namespace std;


namespace qgar
{

// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
GeodesicRecImage::GeodesicRecImage(GreyLevelImage& aMarkImg,
				   GreyLevelImage& aResImg)

  : GreyLevelImage(aMarkImg)
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
			    "qgar::GeodesicRecImage::GeodesicRecImage(qgar::GreyLevelImage&, qgar::GreyLevelImage&)",
			    os.str());
    }

  perform(this, &aResImg);
}

// -------------------------------------------------------------------
// G E O D E S I C   R E C O N S T R U C T I O N
// -------------------------------------------------------------------

void GeodesicRecImage::perform(GreyLevelImage* aMarkImg,
			       GreyLevelImage* aResImg)
{
  int width  = aMarkImg->width(); // just some shortcuts
  int height = aMarkImg->height();

  // first enqueue the boundaries of marker image.

  // as we have to compare marker and goal image in the same time,
  // we won't enqueue the pointers on marker's pixels, but their
  // indice in pixMap (which are the same in goal's pixMap)
  queue< long > boundary;
  
  long indice; // indice in the queue
  GreyLevelImage::value_type maximum; // local maximum

  GreyLevelImage::pointer Jp; // pointer on marker image
  GreyLevelImage::pointer Ip; // pointer on goal image
  GreyLevelImage::pointer Jq; // pointer on current marker boundary pixel
  GreyLevelImage::pointer Iq; // pointer on current goal boundary pixel

  GreyLevelImage::pointer markerPixMap = aMarkImg->pPixMap(); // just some shortcuts
  GreyLevelImage::pointer goalPixMap   = aResImg->pPixMap();

  int minK, minL; // limits of current pixel's neighborhood
  int maxK, maxL;
 
  /*** scan in raster order: ***/

  Jp = markerPixMap;
  Ip = goalPixMap;

  for (int i = 0; i < height; ++i)
    {
      for (int j = 0; j < width; ++j, ++Jp, ++Ip)
	{
	  // point-wise minimum between max(p U Ng+(p)) and Ip
	  maximum = *Jp;

	  // after the first line
	  if (i != 0)
	    {
	      // first pixel
	      if (j == 0)
		{
		  Jq = Jp - width;
		  if (maximum < *Jq)
		    {
		      maximum = *Jq;
		    }
		  ++Jq;
		  if (maximum < *Jq)
		    {
		      maximum = *Jq;    
		    }
		}
	      // last pixel
	      else if (j == width - 1)
		{
		  Jq = Jp - 1;
		  if (maximum < *Jq)
		    {
		      maximum = *Jq;
		    }

		  Jq -= width;
		  if (maximum < *Jq)
		    {
		      maximum = *Jq;
		    }

		  ++Jq;
		  if (maximum < *Jq)
		    {
		      maximum = *Jq;   
		    }
		}
	      // between these two pixels
	      else
		{
		  for (int k = -1; k < 1; ++k)
		    {
		      for (int l = -1 ; l < 1 - k; ++l)
			{
			  Jq = Jp + k*width + l;
			  if (maximum < *Jq)
			    {
			      maximum = *Jq;
			    }
			} // END for l
		    } // END for k
		}
	    }
	  else if (j > 0)
	    {
	      Jq = Jp - 1;
	      if (maximum < *Jq)
		{
		  maximum = *Jq;
		}
	    }
      
	  *Jp = (maximum < *Ip ? maximum : *Ip);
	} // END for j
    } // END for i

  /*** scan in anti-raster order: ***/

  --Jp;
  --Ip;
  for (int i = 0 ; i < height ; ++i)
    {
      for (int j = 0; j < width; ++j, --Jp, --Ip)
	{
	  // point-wise minimum between max(p U Ng-(p)) and Ip
	  maximum = *Jp;

	  // after the first line
	  if (i != 0)
	    {
	      // first pixel
	      if (j == 0)
		{
		  Jq = Jp + width;
		  if (maximum < *Jq)
		    {
		      maximum = *Jq;
		    }

		  --Jq;
		  if (maximum < *Jq)
		    {
		      maximum = *Jq;
		    }

		  *Jp = (maximum < *Ip ? maximum : *Ip);
		  Jq = Jp + width;
		  Iq = Ip + width;
		  if ((*Jq < *Jp) && (*Jq < *Iq))
		    {
		      boundary.push(Jp - markerPixMap);
		    }
		  else
		    {
		      --Iq;
		      --Iq;
		      if ((*Jq < *Jp) && (*Jq < *Iq))
			{
			  boundary.push(Jp - markerPixMap);
			}
		    }
		} // END first pixel

	      // last pixel
	      else if (j == width - 1)
		{
		  Jq = Jp + 1;
		  if (maximum < *Jq)
		    {
		      maximum = *Jq;
		    }

		  Jq += width;
		  if (maximum < *Jq)
		    {
		      maximum = *Jq;
		    }

		  --Jq;
		  if (maximum < *Jq)
		    {
		      maximum = *Jq; 
		    }

		  *Jp = (maximum < *Ip ? maximum : *Ip);
		  Jq = Jp + 1;
		  Iq = Ip + 1;
		  if ((*Jq < *Jp) && (*Jq < *Iq))
		    {
		      boundary.push(Jp - markerPixMap);
		    }
		  else
		    {
		      Iq += width;
		      Iq += width;
		      if ((*Jq < *Jp) && (*Jq < *Iq))
			{
			  boundary.push(Jp - markerPixMap);
			}
		      else
			{
			  Iq--;
			  Iq--;
			  if ((*Jq < *Jp) && (*Jq < *Iq))
			    {
			      boundary.push(Jp - markerPixMap);
			    }
			}
		    }
		} // END last pixel

	      // between these two pixels
	      else
		{
		  for (int k = 1; k > -1; --k)
		    {
		      for (int l = 1 ; l > -(1 + k); --l)
			{
			  Jq = Jp + k*width + l;
			  if (maximum < *Jq)
			    {
			      maximum = *Jq;
			    }
			} // END for l
		    } // END for k

		  *Jp = (maximum < *Ip ? maximum : *Ip);
		  for (int k = 1; k > -1; --k)
		    {
		      for (int l = 1 ; l > -(1 + k); --l)
			{
			  indice = k*width + l;
			  Jq = Jp + indice;
			  Iq = Ip + indice;
			  if ((*Jq < *Jp) && (*Jq < *Iq))
			    {
			      boundary.push(Jp - markerPixMap);
			      // -------------------------------------------
			      // HORROR!  HORROR!  HORROR!  HORROR!  HORROR!
			      // -------------------------------------------
			      k = -1;
			      break;
			      // -------------------------------------------
			    }
			} // END for l
		    } // END for k
		}
	    } // END if i

	  else if (j > 0)
	    {
	      Jq = Jp + 1;
	      if (maximum < *Jq) maximum = *Jq;
	      *Jp = (maximum < *Ip ? maximum : *Ip);
	      Iq = Ip + 1;
	      if ((*Jq < *Jp) && (*Jq < *Iq))
		{
		  boundary.push(Jp - markerPixMap);
		}
	    }
	  else
	    {
	      *Jp = (maximum < *Ip ? maximum : *Ip);
	    }
	} // END for j
    } // END for i (end of scan)
  
  /*** propagation ***/

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
	  maxK = maxL = 2;
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
	  minK = minL = -1;
	  maxL = 2;
	  maxK = 1;
	}

      // last pixel
      else
	{
	  minL = minK = -1;
	  maxL = maxK = 1;
	}
	
      for (int k = minK; k < maxK; ++k)
	{
	  for (int l = minL ; l < maxL; ++l)
	    {
	      indice = k*width + l;
	      Jq = Jp + indice;
	      Iq = Ip + indice;
	      if ( (*Jq < *Jp) && (*Iq != *Jq) )
		{
		  *Jq = (*Jp < *Iq ? *Jp : *Iq);
		  boundary.push(Jq - markerPixMap);
		}
	    } // END for l
	} // END for k

  } // END while (end of propagation)
}

// ----------------------------------------------------------------------

} // namespace qgar
