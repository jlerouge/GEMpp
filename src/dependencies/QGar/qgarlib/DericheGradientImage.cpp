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
 * @file DericheGradientImage.cpp
 *
 * @brief Implementation of class qgar::DericheGradientImage.
 *
 * See file DericheGradientImage.h for the interface.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>,
 *   from previous work by Karl Tombre
 * @date   July 3, 2001  11:35
 * @since  Qgar 1.0
 */



// STD
#include <cmath>
// QGAR
#include "DericheGradientImage.h"
#include "GenImage.h"



using namespace std;



namespace qgar
{


// -------------------------------------------------------------------
// C O N S T R U C T O R S
// -------------------------------------------------------------------


// CONSTRUCT FROM GIVEN GREY-LEVEL IMAGE

DericheGradientImage::DericheGradientImage(const GreyLevelImage& anImg,
                       double anAlpha,
                       double aW,
                       bool aNorm)

  : AbstractGradientImage(anImg)

{
  PRIVATE_Gradient(anAlpha, aW, aNorm);
}


// CONSTRUCT FROM A FLOAT IMAGE

DericheGradientImage::DericheGradientImage(const FloatImage& anImg,
                       double anAlpha,
                       double aW,
                       bool aNorm)

    : AbstractGradientImage(anImg)

  {
    Q_UNUSED(anAlpha);
    Q_UNUSED(aW);
    Q_UNUSED(aNorm);
    //    PRIVATE_Gradient(anAlpha, aW, aNorm);
  }


// -------------------------------------------------------------------
// A U X I L I A R I E S
// -------------------------------------------------------------------


// =======================
// COMPUTE GRADIENT IMAGES
// =======================


void
DericheGradientImage::PRIVATE_Gradient(double alpha,
                       double w,
                       bool norm)
{
  //     ************
  // [1] COEFFICIENTS
  //     ************


   const float c0     = (alpha * alpha) + (w * w);
   const float sinW   = sin(w);
   const float cosW   = cos(w);
   const float expMA  = exp(-alpha);
   const float expSIN = expMA * sinW;

   // Derivation coefficients
   const float b1 = -2. * expMA * cosW;
   const float b2 = exp(-2. * alpha);

   const float bb = 1. + b1 + b2;

   // Normalization coefficient for smoothing
   const float n = bb / ((2. * alpha * expSIN) + (w * (1. - b2)));

   // Normalization coefficient for derivation
   const float a0 = n * w;

   // Smoothing coefficients
   // WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
   // WARNING: STRANGE NORMALIZATION!
   // Shouldn't we *divide* by c0?
   // WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
   const float a = (norm) ? (-n * expSIN * c0 * c0) : (-bb);
   //                        ^^^^^^^^^^^^^^^^^^^^^
   // WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW

   const float a1 = n * expMA * ((alpha * sinW) - (w * cosW));
   const float a2 = a1 - (a0 * b1);
   const float a3 = -a0 * b2;


  //     *********************
  // [2] CONSTANTS AND BUFFERS
  //     *********************


  // Various useful constants
  const int QG_width_X_2       = _width + _width;
  const int QG_width_M_1       = _width  - 1;
  const int QG_width_M_3       = _width  - 3;
  const int QG_height_M_1      = _height - 1;
  const int QG_height_M_3      = _height - 3;
  const int QG_offset_last_row = QG_height_M_1 * _width;

  int size = max(_width, _height);

  // Buffers for rows and columns
  float* buf    = new float[size];
  float* bufRev = new float[size];

  // Buffer used to save 2 multiplications for each pixel processing
  // when deriving along X and Y axis
  float* bufMul = new float[size];


  //     ********
  // [3] X FILTER
  //     ********


  // Pointer to pixel map of X derivatives
  float* pDxMap = _dxImg.pPixMap();


  // [3.1] DERIVE ALONG X AXIS
  //       *******************


  // FOR EACH ROW
  for (int rowCnt = 0 ; rowCnt < _height ; ++rowCnt, pDxMap += _width)
    {

      // FROM LEFT TO RIGHT
      // ------------------

      float* pbuf = buf;
      float* pmul = bufMul;
      // The pixel map of X derivatives is initialized
      // with the pixels of the initial given image
      float* pdx  = pDxMap;

      // 1st pixel
      float v = *pdx;
      *pbuf = v;
      *pmul = v * a;
      ++pbuf;
      ++pmul;
      ++pdx;

      // 2nd pixel
      v = *pdx;
      *pbuf = v;
      *pmul = v * a;
      ++pbuf;
      ++pmul;
      ++pdx;

      // Loop on next pixels using recurrence formula
      for (int cnt = 2 ; cnt < _width ; ++cnt, ++pbuf, ++pmul, ++pdx)
    {
      *pmul = *pdx * a;
      *pbuf =
        *(pmul - 1)
        - (*(pbuf - 1) * b1)
        - (*(pbuf - 2) * b2);
    }


      // FROM RIGHT TO LEFT
      // ------------------

      float* prev = bufRev + QG_width_M_1;
             pbuf = buf    + QG_width_M_1;
             pdx  = pDxMap + QG_width_M_1;

      // Last pixel
      *prev = *pdx;
      *pdx += *pbuf;  // Store value in the map of X derivatives
      --prev;
      --pbuf;
      --pdx;

      // Last but one pixel
      *prev = *pdx;
      *pdx += *pbuf;  // Store value in the map of X derivatives
      --prev;
      --pbuf;
      --pdx;

      // Loop on previous pixels using recurrence formula
      pmul = bufMul + QG_width_M_3;

      for (int cnt = QG_width_M_3;
       cnt >= 0 ;
       --cnt, --prev, --pbuf, --pmul, --pdx)
    {
      float g =
        - *(pmul + 1)
        - (*(prev + 1) * b1)
        - (*(prev + 2) * b2);

      *prev = g;
      *pdx  = g + *pbuf; // Store value in the map of X derivatives
    }

    } // END FOR EACH ROW


  // [3.2] SMOOTH ALONG Y AXIS
  //       *******************


  // Pointer to pixel map of X derivatives
  pDxMap = _dxImg.pPixMap();


  // FOR EACH COLUMN
  for (int colCnt = 0 ; colCnt < _width ; ++colCnt, ++pDxMap)
    {

      // FROM TOP TO BOTTOM
      // ------------------

      float* pbuf = buf;
      float* pdx  = pDxMap;

      // 1st pixel
      *pbuf = *pdx;
      ++pbuf;
      pdx += _width;

      // 2nd pixel
      *pbuf = *pdx;
      ++pbuf;
      pdx += _width;

      // Loop on next pixels using recurrence formula
      for (int cnt = 2 ; cnt < _height ; ++cnt, ++pbuf, pdx += _width)
    {
      *pbuf =
        (*pdx * a0)
        + (*(pdx - _width) * a1)
        - (*(pbuf - 1) * b1)
        - (*(pbuf - 2) * b2);
    }

      // FROM BOTTOM TO TOP
      // ------------------

      float* prev = bufRev + QG_height_M_1;
             pdx  = pDxMap + QG_offset_last_row;

      // Last pixel
      *prev = *pdx;
      --prev;
      //     --pbuf;
      pdx -= _width;

      // Last but one pixel
      *prev = *pdx;
      --prev;
      //      --pbuf;
      pdx -= _width;

      // Loop on previous pixels using recurrence formula
      for (int cnt = QG_height_M_3;
       cnt >= 0 ;
       --cnt, --prev, pdx -= _width)
    {
      float g =
        (*(pdx + _width) * a2)
        + (*(pdx + QG_width_X_2) * a3)
        - (*(prev + 1) * b1)
        - (*(prev + 2) * b2);

      *prev = g;
    }

      // SUM VALUES
      // ----------

      pbuf = buf;
      prev = bufRev;
      pdx  = pDxMap;

      for (int cnt = 0 ;
       cnt < _height ;
       ++cnt, ++prev, ++pbuf, pdx += _width)
    {
      *pdx = *pbuf + *prev;  // Store in map of X derivatives
    }

    } // END FOR EACH COLUMN


  //     ********
  // [4] Y FILTER
  //     ********


  // Pointer to pixel map of Y derivatives
  float* pDyMap = _dyImg.pPixMap();


  // [4.1] DERIVE ALONG Y AXIS
  //       *******************


  // FOR EACH COLUMN
  for (int colCnt = 0 ; colCnt < _width ; ++colCnt, ++pDyMap)
    {
      // FROM TOP TO BOTTOM
      // ------------------

      float* pbuf = buf;
      float* pmul = bufMul;
      // The pixel map of Y derivatives is initialized
      // with the pixels of the initial given image
      float* pdy = pDyMap;

      // 1st pixel
      float v = *pdy;
      *pbuf = v;
      *pmul = v * a;
      ++pbuf;
      ++pmul;
      pdy += _width;

      // 2nd pixel
      v = *pdy;
      *pbuf = v;
      *pmul = v * a;
      ++pbuf;
      ++pmul;
      pdy += _width;

      // Loop on next pixels using recurrence formula
      for (int cnt = 2 ;
       cnt < _height ;
       ++cnt, ++pbuf, ++pmul, pdy += _width)
    {
      *pmul = *pdy * a;
      *pbuf =
        *(pmul - 1)
        - (*(pbuf - 1) * b1)
        - (*(pbuf - 2) * b2);
    }

      // FROM BOTTOM TO TOP
      // ------------------

      float* prev = bufRev + QG_height_M_1;
             pbuf = buf    + QG_height_M_1;
             pdy  = pDyMap + QG_offset_last_row;

      // Last pixel
      *prev = *pdy;
      *pdy += *pbuf;  // Store value in the map of Y derivatives
      --prev;
      --pbuf;
      pdy -= _width;

      // Last but one pixel
      *prev = *pdy;
      *pdy += *pbuf;  // Store value in the map of Y derivatives
      --prev;
      --pbuf;
      pdy -= _width;

      // Loop on previous pixels using recurrence formula
      pmul = bufMul + QG_height_M_3;

      for (int cnt = QG_height_M_3;
       cnt >= 0 ;
       --cnt, --prev, --pbuf, --pmul, pdy -= _width)
    {
      float g =
        - *(pmul + 1)
        - (*(prev + 1) * b1)
        - (*(prev + 2) * b2);

      *prev = g;
      *pdy  = g + *pbuf; // Store value in the map of X derivatives
    }

    } // END FOR EACH COLUMN


  // [4.2] SMOOTH ALONG X AXIS
  //       *******************


  // Pointer to pixel map of Y derivatives
  pDyMap = _dyImg.pPixMap();


  // FOR EACH ROW
  for (int rowCnt = 0 ; rowCnt < _height ; ++rowCnt, pDyMap += _width)
    {

      // FROM LEFT TO RIGHT
      // ------------------

      float* pbuf = buf;
      float* pdy  = pDyMap;

      // 1st pixel
      *pbuf = *pdy;
      ++pbuf;
      ++pdy;

      // 2nd pixel
      *pbuf = *pdy;
      ++pbuf;
      ++pdy;

      //  Loop on next pixels using recurrence formula
      for (int cnt = 2 ; cnt < _width ; ++cnt, ++pbuf, ++pdy)
    {
      *pbuf =
        (*pdy * a0)
        + (*(pbuf - 1) * a1)
        - (*(pbuf - 1) * b1)
        - (*(pbuf - 2) * b2);
    }

      // FROM RIGHT TO LEFT
      // ------------------

      float* prev = bufRev + QG_width_M_1;
             pdy  = pDyMap + QG_width_M_1;

      // Last pixel
      *prev = *pdy;
      --prev;
      --pdy;

      // Last but one pixel
      *prev = *pdy;
      --prev;
      --pdy;

      // Loop on previous pixels using recurrence formula
      for (int cnt = QG_width_M_3;
       cnt >= 0 ;
       --cnt, --prev, --pbuf, --pdy)
    {
      *prev =
        (*(pdy + 1) * a2)
        + (*(pdy + 2) * a3)
        - (*(prev + 1) * b1)
        - (*(prev + 2) * b2);
    }

      // SUM VALUES
      // ----------

      pbuf = buf;
      prev = bufRev;
      pdy  = pDyMap;

      for (int cnt = 0 ;
       cnt < _width ;
       ++cnt, ++pbuf, ++prev, ++pdy)
    {
      *pdy = *pbuf + *prev;  // Store in map of Y derivatives
    }

    } // END FOR EACH ROW


  //     ********
  // [5] CLEANING
  //     ********


  delete [] buf;
  delete [] bufRev;
  delete [] bufMul;

}


// -------------------------------------------------------------------

} // namespace qgar
