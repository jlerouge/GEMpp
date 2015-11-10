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
 * @file LaplacianOfGaussianImage.cpp
 *
 * @brief Implementation of class qgar::LaplacianOfGaussianImage.
 *
 * See file LaplacianOfGaussianImage.h for the interface.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date   July 3, 2001  15:01
 * @since  Qgar 1.0
 */



// QGAR
#include "GenConvolImage.h"
#include "GenImage.h"
#include "LaplacianOfGaussianImage.h"
#include "Mask1dGaussD2.h"
#include "Mask1dGauss.h"



namespace qgar
{


// -------------------------------------------------------------------
// C O N S T R U C T O R S
// -------------------------------------------------------------------


// CONSTRUCT FROM GIVEN GREY-LEVEL IMAGE

LaplacianOfGaussianImage::LaplacianOfGaussianImage(const GreyLevelImage& img,
						   double sigma) 

    : FloatImage(PRIVATEbuildLOGImage(img, sigma))

{
  // VOID
}


// CONSTRUCT FROM GIVEN FLOAT IMAGE


LaplacianOfGaussianImage::LaplacianOfGaussianImage(const FloatImage& img,
						   double sigma) 

    : FloatImage(PRIVATEbuildLOGImage(GreyLevelImage(img), sigma))

{
  // VOID
}



// -------------------------------------------------------------------
// A U X I L I A R I E S
// -------------------------------------------------------------------


FloatImage
LaplacianOfGaussianImage::PRIVATEbuildLOGImage(const GreyLevelImage& img, 
					       double aSigma)
{
  // By construction, the float image contains a copy of the original
  // image to be derived

  // Create Gaussian masks
  Mask1dGauss   sMask(aSigma);  // smoothing mask
  Mask1dGaussD2 dMask(aSigma);  // second derivative mask

  FConvolImage* dx = new FConvolImage(img, dMask, QGE_AXIS_X);
  FConvolImage imgx(*dx, sMask, QGE_AXIS_Y);
  delete dx;

  dx = new FConvolImage(img, sMask, QGE_AXIS_X);
  FConvolImage imgy(*dx, dMask, QGE_AXIS_Y);
  delete dx;

  // Add the two images
  imgx += imgy;
 
  return imgx;
}

// ----------------------------------------------------------------------

} // namespace qgar

