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
 * @file AbstractGradientImage.cpp
 *
 * @brief Implementation of class qgar::AbstractGradientImage.
 *
 * See file AbstractGradientImage.h for the interface.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masin</a>
 * @date   April 30, 2003  18:38
 */


// QGAR
#include "AbstractGradientImage.h"
#include "AbstractMultiImage.h"
#include "GenImage.h"



namespace qgar
{


// -------------------------------------------------------------------
// C O N S T R U C T O R S
// -------------------------------------------------------------------


// DEFAULT CONSTRUCTOR

AbstractGradientImage::AbstractGradientImage()

  : AbstractMultiImage(0, 0), _dxImg(0, 0), _dyImg(0, 0)

{
  // VOID
}


// COPY CONSTRUCTOR
// PERFORM A DEEP COPY

AbstractGradientImage::AbstractGradientImage(const AbstractGradientImage& anImg)
 
  : AbstractMultiImage(anImg),
    _dxImg(anImg._dxImg),
    _dyImg(anImg._dyImg)

{
  // VOID
}


// INITIALIZE FROM A GREY-LEVEL IMAGE

AbstractGradientImage::AbstractGradientImage(const GreyLevelImage& anImg)

  : AbstractMultiImage(anImg.width(), anImg.height()),
    // ==========================================
    // No FloatImage constructor is used to avoid
    // running over the given image two times
    // _dxImg(anImg), _dyImg(anImg)
    // ==========================================
    _dxImg(anImg.width(), anImg.height()),
    _dyImg(anImg.width(), anImg.height())

{
  float* pDxPixMap       = _dxImg.pPixMap();
  float* pDyPixMap       = _dyImg.pPixMap();
  unsigned char* pAnImgPixMap =  anImg.pPixMap();
  int size               = _width * _height;
  float pixVal;

  for (int iCnt = 0 ; iCnt < size ; iCnt++)
    {
      pixVal       = (float) *pAnImgPixMap++;
      *pDxPixMap++ = pixVal;
      *pDyPixMap++ = pixVal;
    }
}


// INITIALIZE FROM A FLOAT IMAGE

AbstractGradientImage::AbstractGradientImage(const FloatImage& anImg)

  : AbstractMultiImage(anImg.width(), anImg.height()),
    // ==========================================
    // No FloatImage constructor is used to avoid
    // running over the given image two times
    // _dxImg(anImg), _dyImg(anImg)
    // ==========================================
    _dxImg(anImg.width(), anImg.height()),
    _dyImg(anImg.width(), anImg.height())

{
  float* pDxPixMap    = _dxImg.pPixMap();
  float* pDyPixMap    = _dyImg.pPixMap();
  float* pAnImgPixMap = anImg.pPixMap();
  int size            = _width * _height;
  float pixVal;

  for (int iCnt = 0 ; iCnt < size ; iCnt++)
    {
      pixVal       = *pAnImgPixMap++;
      *pDxPixMap++ = pixVal;
      *pDyPixMap++ = pixVal;
    }
}


// INITIALIZE FROM A DOUBLE IMAGE

AbstractGradientImage::AbstractGradientImage(const DoubleImage& anImg)

  : AbstractMultiImage(anImg.width(), anImg.height()),
    // ==========================================
    // No FloatImage constructor is used to avoid
    // running over the given image two times
    // _dxImg(anImg), _dyImg(anImg)
    // ==========================================
    _dxImg(anImg.width(), anImg.height()),
    _dyImg(anImg.width(), anImg.height())

{
  float*  pDxPixMap    = _dxImg.pPixMap();
  float*  pDyPixMap    = _dyImg.pPixMap();
  double* pAnImgPixMap = anImg.pPixMap();
  int size             = _width * _height;
  float pixVal;

  for (int iCnt = 0 ; iCnt < size ; iCnt++)
    {
      pixVal       = (float) *pAnImgPixMap++;
      *pDxPixMap++ = pixVal;
      *pDyPixMap++ = pixVal;
    }
}


// INITIALIZE USING GIVEN WIDTH AND HEIGHT

AbstractGradientImage::AbstractGradientImage(int aWidth, int aHeight)

  : AbstractMultiImage(aWidth, aHeight),
    _dxImg(aWidth, aHeight),
    _dyImg(aWidth, aHeight)

{
  // VOID
}


// INITIALIZE FROM ALL DATA

AbstractGradientImage::AbstractGradientImage(int aWidth,
					     int aHeight,
					     FloatImage aDxImg,
					     FloatImage aDyImg)

  : AbstractMultiImage(aWidth, aHeight),
    _dxImg(aDxImg),
    _dyImg(aDyImg)

{
  // VOID
}


// -------------------------------------------------------------------
// O P E R A T O R S 
// -------------------------------------------------------------------


// ASSIGNMENT: SAME AS COPY CONSTRUCTOR

AbstractGradientImage&
AbstractGradientImage::operator=(const AbstractGradientImage& anImg)
{
  // Are left hand side and right hand side different objects?
  if (this != &anImg)
    {
      AbstractMultiImage::operator=(anImg);
      _dxImg  = anImg._dxImg;
      _dyImg  = anImg._dyImg;
    }

  return *this;
}

// -------------------------------------------------------------------

} // namespace qgar
