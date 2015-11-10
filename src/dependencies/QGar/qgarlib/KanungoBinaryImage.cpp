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
 * @file KanungoBinaryImage.cpp
 *
 * @brief Implementation of class KanungoBinaryImage.
 *
 * See file KanungoBinaryImage.h for the interface.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Perrin & Kheder">Julien Perrin & Sami Kheder</a>
 * @date   March 24,  2003  16:16
 * @since  Qgar 2.1.1
 */



// STD
#include <cmath>
#include <cstdlib>
#include <sstream>

#ifdef _WIN32
  #include <ctime>
  #include <process.h>
#endif

// QGAR
#include "CloseBinaryImage.h"
#include "Dist34Image.h"
#include "GenImage.h"
#include "KanungoBinaryImage.h"



using namespace std;



namespace qgar
{

// -------------------------------------------------------------------
// C O N S T R U C T O R
// -------------------------------------------------------------------


KanungoBinaryImage::KanungoBinaryImage(BinaryImage& anImg, 
				       double alpha0, 
				       double alpha, 
				       double beta0, 
				       double beta, 
				       double eta, 
				       int structEltSize)

  : BinaryImage(anImg)

{
  qgKanungoDegradation(*this, alpha0, alpha, beta0, beta, eta, structEltSize);
}


// -------------------------------------------------------------------
// G L O B A L   F U N C T I O N S
// -------------------------------------------------------------------


void
qgKanungoDegradation(BinaryImage& anImg, 
		     double alpha0, 
		     double alpha, 
		     double beta0, 
		     double beta, 
		     double eta, 
		     int structEltSize)

  

{
  // CHECK ARGUMENTS
  // ===============

  if (structEltSize < 0)
    {
      ostringstream os;
      os << "Structural element size cannot be negative ("
	 << structEltSize
	 << ')';
      throw QgarErrorInvalidArg(__FILE__, __LINE__,
				"void qgar::qgKanungoDegradation(qgar::BinaryImage&, double, double, double, double, double, int)",
				os.str());
    }

  // DISTANCE TRANSFORM
  // ==================

  Dist34Image* tmpDistImg = new Dist34Image(anImg);

  // PROBABILISTIC TRANSFORM
  // =======================

  // Random number generator initialization
  srand(time(0) + GETPID() * 1000);

  // Pointers to pixel maps of initial and distance images 
  BinaryImage::pointer pMapImg  = anImg.pPixMap();
  Dist34Image::pointer pMapDist = tmpDistImg->pPixMap();

  // Image size
  int size = (anImg.width()) * (anImg.height());

  // From each pixel (top to bottom, left to right)...

  for (int iCnt = 0 ; iCnt < size ; ++iCnt, ++pMapImg, ++pMapDist)
    { 
      double proba;

      if (*pMapImg == QGE_BW_WHITE)
	{
	  // White pixel
	  proba =
	    (beta0 * exp(-beta * pow((((double) *pMapDist) / 3.), 2.)))
	    + eta;

	  // Random test
	  if (((double) rand() / (double) RAND_MAX) < proba)
	    {
	      *pMapImg = QGE_BW_BLACK;  // Swap pixel value
	    }
	}
      else 
	{
	  // Black pixel
	  proba =
	    (alpha0 * exp(-alpha * pow((((double) *pMapDist) / 3.), 2.)))
	    + eta;

	  // Random test
	  if (((double) rand() / (double) RAND_MAX) < proba)
	    {
	      *pMapImg = QGE_BW_WHITE;  // Swap pixel value
	    }
	}
    } // END for iCnt

  // DELETE TEMPORARY IMAGE
  // ======================

  delete tmpDistImg;

  // CLOSING
  // =======

  if (structEltSize != 0) 
    {
      CloseBinaryImage::perform(&anImg, structEltSize);
    }
}

// ----------------------------------------------------------------------

} // namespace qgar









