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
 * @file   CannyGradientImage.cpp
 * @brief  Implementation of class qgar::CannyGradientImage.
 *
 *         See file CannyGradientImage.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date   Jul 4, 2001  15:17
 * @since  Qgar 1.0
 */


// QGAR
#include "AbstractGradientImage.h"
#include "CannyGradientImage.h"
#include "GenConvolImage.h"
#include "GenImage.h"
#include "Mask1dGaussD1.h"
#include "Mask1dGauss.h"



namespace qgar
{

// -------------------------------------------------------------------
// C O N S T R U C T O R S
// -------------------------------------------------------------------


// CONSTRUCT FROM GIVEN GREY-LEVEL IMAGE

CannyGradientImage::CannyGradientImage(const GreyLevelImage& anImg,
				       double aSigma) 

  : AbstractGradientImage(anImg)

{
  PRIVATE_CannyImage(aSigma);
}


// CONSTRUCT FROM GIVEN FLOAT IMAGE

CannyGradientImage::CannyGradientImage(const FloatImage& anImg,
				       double aSigma) 

    : AbstractGradientImage(anImg)

{
  PRIVATE_CannyImage(aSigma);
}


// -------------------------------------------------------------------
// A U X I L I A R I E S   ( P R I V A T E )
// -------------------------------------------------------------------


void
CannyGradientImage::PRIVATE_CannyImage(double aSigma)
{
  // When we start this function, we already know by construction
  // that _dxImg and _dyImg contain copies of the original image
  // to be derived.

  // Create Gaussian masks
  Mask1dGauss   sMask(aSigma); // smoothing mask
  Mask1dGaussD1 dMask(aSigma); // derivation mask

  FConvolImage* dx = new FConvolImage(_dxImg, dMask, QGE_AXIS_X);
  FConvolImage* dy = new FConvolImage(   *dx, sMask, QGE_AXIS_Y);

  // This was _dxImg
  _dxImg = *dy;

  delete dx;
  delete dy;

  dx = new FConvolImage(_dyImg, sMask, QGE_AXIS_X);
  dy = new FConvolImage(   *dx, dMask, QGE_AXIS_Y);

  // And this was _dyImg
  _dyImg = *dy;

  delete dx;
  delete dy;
}


// -------------------------------------------------------------------

} // namespace qgar
