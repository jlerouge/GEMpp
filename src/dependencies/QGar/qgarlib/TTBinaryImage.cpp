 /*---------------------------------------------------------------------*
  | Library QgarLib, graphics analysis and recognition                  |
  | Copyright (C) 2004  Qgar Project, LORIA                             |
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
  | http://www.gnu.org/licenses/lgpl.html for the terms of the license. |
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
 * @file  TTBinaryImage.cpp
 * @brief Implementation of class qgar::TTBinaryImage.
 *
 * See file TTBinaryImage.h for the interface.
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   July 18, 2005  15:15
 * @since  Qgar 2.2
 */



// QGAR
#include "array.h"
#include "BoundingBox.h"
#include "CannyGradientImage.h"
#include "Component.h"
#include "ConnectedComponents.h"
#include "GenConvolImage.h"
#include "GenImage.h"
#include "GenMask2d.h"
#include "GradientModuleImage.h"
#include "LaplacianOfGaussianImage.h"
#include "primitives.h"
#include "TTBinaryImage.h"



using namespace std;



namespace qgar
{


// LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
//
// L O C A L   A U X I L I A R I E S
//
// LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL


namespace
{

// =======================
// LABELS '-', '0' and '+'
// =======================

// WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
// WARNING: See section (4)
// Do not change the following values, because they are used
// to increment the count of labels '-' and '+' in the border
// of a WHITE component (table tabPlusMinus)
// WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW

static const BinaryImage::value_type LABEL_MINUS = 0;
static const BinaryImage::value_type LABEL_ZERO  = 1;
static const BinaryImage::value_type LABEL_PLUS  = 2;

} // unnamed namespace


// LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
//
// E N D   O F   L O C A L   A U X I L I A R I E S
//
// LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL




// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------


TTBinaryImage::TTBinaryImage(const GreyLevelImage& aGreyLevelImg, 
			     const double aSigma,
			     const double anActThrs,
			     const double aPostThrs)

  : BinaryImage(aGreyLevelImg.width(), aGreyLevelImg.height())

{
  // DIMENSIONS OF THE INITIAL IMAGE
  const int imgWidth        = aGreyLevelImg.width();
  const int imgHeight       = aGreyLevelImg.height();
  const int imgWidthMinus2  = imgWidth  - 2;
  const int imgWidthMinus1  = imgWidth  - 1;
  const int imgWidthPlus1   = imgWidth  + 1;
  const int imgWidthPlus4   = imgWidth  + 4;
  const int imgWidthX2      = imgWidth  * 2;
  const int imgHeightMinus2 = imgHeight - 2;
  const int imgHeightPlus4  = imgHeight + 4;
  const int imgSize         = imgWidth * imgHeight;

  // POINTERS TO PIXEL MAPS
  // pActImg     : activity
  // pBinImg     : first temporary binary image built from activity
  // pCompImg    : components
  // pGradModImg : Gradient module
  // pLapImg     : Laplacian
  // pLblImg     : labels {-,0,+}
  // pNegCompImg : negative components
  // pNegImg     : negative binary image
  // pResImg     : final binary image
  LaplacianOfGaussianImage::pointer pActImg;
  BinaryImage::pointer              pBinImg;
  GradientModuleImage::pointer      pGradModImg;
  LaplacianOfGaussianImage::pointer pLapImg;
  BinaryImage::pointer              pLblImg;
  Component::label_type*            pCompImg;
  Component::label_type*            pNegCompImg;
  BinaryImage::pointer              pNegImg;
  BinaryImage::pointer              pResImg;

  // Total number of (connected) components
  int compCnt;


  // WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
  // In the image of (labels of) components, the first and last rows,
  // and the first and last columns are considered as parts of the
  // background, with label 0 (see class qgar::ConnectedComponents).
  // => They are generally not taken into account when dealing with
  // images in the following:
  //
  //   0  0    0    0    0    0    0    0    0    0  0
  //   0  F -> * -> * -> * -> * -> * -> * -> * -> *  0
  //   0  * -> ...                         ... -> *  0
  //   0  * -> * -> * -> * -> * -> * -> * -> * -> L  0
  //   0  0    0    0    0    0    0    0    0    0  0
  // 
  // F: first pixel to be processed
  // L:  last pixel to be processed
  // WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW


  // ===================================================================
  // (1) ACTIVITY
  // ===================================================================

  // (1.1) Compute the Gradient using Canny's operator,
  // ===== instead of Sobel's one (used in Trier & Taxt's method)

  CannyGradientImage*  gradImg    = new CannyGradientImage(aGreyLevelImg, aSigma);
  GradientModuleImage* gradModImg = new GradientModuleImage(*gradImg);

  // (1.2) Delete useless Gradient image
  // =====
  delete gradImg;

  /*
   * (1.3) The activity of a given pixel is the sum of the Gradient
   * ===== modules of the pixels around:
   *             
   *  +--------------> X              i = x+1  j = y+1  
   *  | g g g g g g g                  __       __
   *  | g g G G G g g                  \        \  
   *  | g g G A G g g        A(x,y) =  /        /   gradModImg(i,j)
   *  | g g G G G g g                  --       --
   *  | g g g g g g g                 i = x-1  j = y-1
   *  v
   *  Y
   *
   * => Convolve the Gradient module image
   *    using a 3x3 mask with all coefficients set to 1
   *
   * Class ConvolImage should be used to perform the convolution:
   *
   * FConvolImage* actImg = new FConvolImage(*gradModImg, FMask2d(3,3,1.0));
   *
   * but multiplications by the mask coefficients would consume
   * a substantial amount of time.
   */

  GenImage<LaplacianOfGaussianImage::value_type>*
    actImg = new GenImage<LaplacianOfGaussianImage::value_type>(imgWidth, imgHeight);

  // pActImg     : first pixel to be processed in the activity image
  // pGradModImg : corresponding pixel in the Gradient image
  pActImg     = actImg->pPixMap()     + imgWidthPlus1;
  pGradModImg = gradModImg->pPixMap() + imgWidthPlus1;

  for (int rowIdx = 0 ; rowIdx < imgHeightMinus2 ; ++rowIdx)
    {
      for (int colIdx = 0 ; colIdx < imgWidthMinus2 ; ++colIdx)
	{
	  *pActImg =   *(pGradModImg - imgWidthMinus1) // nw  |  |  |  |
	             + *(pGradModImg - imgWidth)       // n  -+--+--+--+-
	             + *(pGradModImg - imgWidthPlus1)  // ne  |nw| n|ne|
	             + *(pGradModImg - 1)              // w  -+--+--+--+-
	             + *pGradModImg                    // A   | w| A| e|
	             + *(pGradModImg + 1)              // e  -+--+--+--+-
	             + *(pGradModImg + imgWidthMinus1) // sw  |sw| s|se|
	             + *(pGradModImg + imgWidth)       // s  -+--+--+--+-
	             + *(pGradModImg + imgWidthPlus1); // se  |  |  |  |
	  ++pActImg;
	  ++pGradModImg;
	}
      pActImg     += 2;
      pGradModImg += 2;
    }


  // ===================================================================
  // (2) IMAGE OF LABELS AND CORRESPONDING BINARY IMAGE
  // ===================================================================

  // (2.1) Each pixel is associated with a label among {-,0,+}, stored
  // ===== at same coordinates in the current image (this), such as:
  //
  //          | 0  if  A(x,y) <  anActThrs
  // L(x,y) = | +  if  A(x,y) >= anActThrs  and  Laplacian(x,y) >= 0
  //          | -  if  A(X,Y) >= anActThrs  and  Laplacian(x,y) <  0
  //  
  // Simultaneously, binary image binImg is constructed, such as
  // a WHITE (resp. BLACK) pixel corresponds to a pixel labelled '0'
  // (resp. '+' or '-') at same coordinates in the current image (this)

  // WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
  // WARNING: the current image (this) is used to store L(x,y)
  // WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW

  BinaryImage* binImg = new BinaryImage(imgWidth, imgHeight);
  LaplacianOfGaussianImage*
    lapImg = new LaplacianOfGaussianImage(aGreyLevelImg, aSigma);
  
  pBinImg = binImg->pPixMap() + imgWidthPlus1;
  pActImg = actImg->pPixMap() + imgWidthPlus1;
  pLapImg = lapImg->pPixMap() + imgWidthPlus1;
  pLblImg =   this->pPixMap() + imgWidthPlus1;

  for (int rowIdx = 0 ; rowIdx < imgHeightMinus2 ; ++rowIdx)
    {
      for (int colIdx = 0 ; colIdx < imgWidthMinus2 ; ++colIdx)
	{
	  if (*pActImg < anActThrs)
	    {
	      *pBinImg = QGE_BW_WHITE;  // label '0' => WHITE
	      *pLblImg = LABEL_ZERO;
	    }
	  else
	    {
	      *pBinImg = QGE_BW_BLACK;  // label '+' or '-' => BLACK

	      if (*pLapImg < 0.)
		{
		  *pLblImg = LABEL_MINUS;
		}
	      else
		{
		  *pLblImg = LABEL_PLUS;
		}
	    } // END if

	  // Next pixel in row
	  ++pBinImg;
	  ++pActImg;
	  ++pLapImg;
	  ++pLblImg;
	} // END for colIdx

      // Next row
      pBinImg += 2;
      pActImg += 2;
      pLapImg += 2;
      pLblImg += 2;
    } // END for rowIdx


  // (2.2) Delete useless images: Activity and Laplacian
  // =====
  delete actImg;
  delete lapImg;


  // ===================================================================
  // (3) CONNECTED COMPONENTS OF THE LABEL IMAGE
  // ===================================================================

  // (3.1) Connected components are computed from binary image binImg:
  // ===== * WHITE pixels correspond to pixels labelled '0'
  //       * BLACK pixels correspond to pixels labelled '+' and '-'
  //
  // WARNING:
  //
  //      b b b                    . w .
  //      b B b                    w W w
  //      b b b                    . w .
  //
  // 8-connectivity            4-connectivity
  //    for BLACK                for WHITE

  ConnectedComponents* components = new ConnectedComponents(*binImg);

  // The component image
  const ConnectedComponents::image_type&
    compImg = components->accessComponentImage();

  // (3.2) Delete useless temporary binary image
  // =====
  delete binImg;


  // ===================================================================
  // (4) BORDERS OF WHITE COMPONENTS
  // ===================================================================

  // colCnt : number of pixels in a row
  // colIdx : index of the current pixel in the current row
  int colCnt = imgWidthMinus2;
  int colIdx = 1;

  // rowCnt : total number of rows to be processed
  // rowIdx : index of the row being processed
  int rowCnt = imgHeightMinus2;
  int rowIdx = 1;

  // pCompImg : pointer to the pixel map of the image of components
  // pLblImg  : pointer to the pixel map of the image of labels {-,0,+}
  // They point to the same (x,y) location in both pixel maps
  pCompImg  = compImg.pPixMap() + imgWidthPlus1;
  pLblImg   = this->pPixMap()   + imgWidthPlus1;

  //                   0  1  2        compCnt - 1
  //                 +--+--+--+- - - -+--+
  // tabPlusMinus    |  |  |  |       |  |   initialized to 0
  //                 +--+--+--+- - - -+--+
  // 
  // * compCnt is the total number of components
  // * tabPlusMinus(i) is incremented (resp. decremented) by 1 for
  //   each pixel labelled '+' (resp. '-') in the border of component i
  compCnt = components->componentCnt();
  int* tabPlusMinus = new int[compCnt];
  qgMemSet0(tabPlusMinus, compCnt);

  // Loop condition
  bool notLastPixel = true;

  while(notLastPixel)
    {
    // -----------------------------------------------------------------
    // WHILE each pixel of the component image is not processed
    // -----------------------------------------------------------------

      // Component (label) of the current pixel
      Component::label_type compC = *pCompImg;

      if ((compC != 0) && (*pLblImg == LABEL_ZERO))
	{
	  // ############################################################
	  // Process only 0-labelled components, if not background
	  // ############################################################
	  //
	  //    0      i-2 i-1  i  i+1 i+2
	  //     +----|---|---|---|---|---|---->
	  //     |
	  //     |
	  //     -   -|---|---|---|---|---|-
	  // j-1 |    |   | nw| n | ne|nee|
	  //     -   -|---|---#=============
	  // j   |    | ww| w # C | e |   |
	  //     =   =========#---|---|---|-
	  // j+1 |    |   | sw| s | se|   |
	  //     -   -|---|---|---|---|---|-
	  //     |
	  //     v
	  //
	  // * Current pixel:
	  //   - is pointed by pCompImg
	  //   - belongs to component C (which is not a white component)
	  // * Pixels belonging to components nw, n, ne, nee, ww, and w
	  //   are already processed
	  //
	  // ############################################################
	  // IF component e (resp. sw, s, se) is the same component as C,
	  // THEN the corresponding pixel does not belong to the border
	  //      of (current) component C: nothing to do
	  // ############################################################


	  // PIXEL BELONGING TO COMPONENT e
          // ##############################
	  if (*(pCompImg + 1) != compC)  // e != c
	    {
	      //  -|---|---|---|---|---|-
	      //   |   | nw| n | ne|nee|
	      //  -|---|---#=============
	      //   | ww| w # c | e |   |
	      //  =========#---|---|---|-
	      //   |   | sw| s | se|   |
	      //  -|---|---|---|---|---|-
	      //
	      // * Values of pointers to access pixels of components:
	      //     - n  :  PIX_MAP_POINTER - imgWidth
	      //     - ne :  PIX_MAP_POINTER - imgWidth + 1
	      //     - nee:  PIX_MAP_POINTER - imgWidth + 2
	      //     - c  :  PIX_MAP_POINTER
	      //     - e  :  PIX_MAP_POINTER + 1
	      //   By construction (see beginning of the present section 4),
	      //   all these values determine valid pointers
	      //
	      // * IF component n, ne, and nee are different from c
	      //   THEN the pixel of component e has not been taken
	      //        into account for component c
	      
	      Component::label_type* pCompImgTmp = pCompImg - imgWidth;

	      if (   (*pCompImgTmp       != compC)   // n   != c
                  && (*(pCompImgTmp + 1) != compC)   // ne  != c
		  && (*(pCompImgTmp + 2) != compC))  // nee != c
		{
		  // Update count of +/- pixels of component c: labels
		  // are coded so that the label has just to be added to
		  // the current count
		  tabPlusMinus[compC] += *(pLblImg + 1) - 1;
		  // NOTE: component e is necessarily BLACK
		  // (i.e. labelled '+' or '-' in the current image)
		  // as WHITE components are 4-connected
		}
	    } // END pixel e


	  // PIXEL BELONGING TO COMPONENT sw
          // ###############################
	  if (*(pCompImg + imgWidthMinus1) != compC)  // sw != c
	    {
	      //  -|---|---|---|---|---|-
	      //   |   | nw| n | ne|nee|
	      //  -|---|---#=============
	      //   | ww| w # c | e |   |
	      //  =========#---|---|---|-
	      //   |   | sw| s | se|   |
	      //  -|---|---|---|---|---|-
	      //
	      // * Values of pointers to access pixels of components:
	      //     - ww :  PIX_MAP_POINTER - 2
	      //     - w  :  PIX_MAP_POINTER - 1
	      //     - c  :  PIX_MAP_POINTER
	      //     - sw :  PIX_MAP_POINTER + imgWidth - 1
	      //   By construction (see beginning of the present section 4),
	      //   all these values determine valid pointers
	      //
	      // * IF components ww and w are different from c
	      //   THEN the pixel of component sw has not been taken
	      //        into account for component c

	      if (   (*(pCompImg - 2) != compC)   // ww != c
		  && (*(pCompImg - 1) != compC))  // w  != c
		{
		  // Update count of +/- pixels of component c: labels
		  // are coded so that the label has just to be added to
		  // the current count
		  tabPlusMinus[compC] += *(pLblImg + imgWidthMinus1) - 1;
		  // NOTE: component sw is not necessarily BLACK
		  // (i.e. labelled '+' or '-' in the current image)
		  // as WHITE components are 4-connected
		}
	    } // END pixel sw


	  // PIXEL BELONGING TO COMPONENT s
          // ##############################
	  if ((*pCompImg + imgWidth) != compC)  // s != c
	    {
	      //  -|---|---|---|---|---|-
	      //   |   | nw| n | ne|   |
	      //  -|---|---#=============
	      //   | ww| w # c | e |   |
	      //  =========#---|---|---|-
	      //   |   | sw| s | se|   |
	      //  -|---|---|---|---|---|-
	      //
	      // * Values of pointers to access pixels of components:
	      //     - w  :  PIX_MAP_POINTER - 1
	      //     - c  :  PIX_MAP_POINTER
	      //     - s  :  PIX_MAP_POINTER + imgWidth
	      //   By construction (see beginning of the present section 4),
	      //   all these values determine valid pointers
	      //
	      // * IF component w is different from c
	      //   THEN the pixel of component s has not been taken
	      //        into account for component c

	      if (*(pCompImg - 1) != compC)   // w != c
		{
		  // Update count of +/- pixels of component c: labels
		  // are coded so that the label has just to be added to
		  // the current count
		  tabPlusMinus[compC] += *(pLblImg + imgWidth) - 1;
		  // NOTE: component s is necessarily BLACK
		  // (i.e. labelled '+' or '-' in the current image)
		  // as WHITE components are 4-connected
		}
	    } // END pixel s


	  // PIXEL BELONGING TO COMPONENT se
          // ###############################
	  if (*(pCompImg + imgWidthPlus1) != compC)  // se != c
	    {
	      //  -|---|---|---|---|---|-
	      //   |   | nw| n | ne|   |
	      //  -|---|---#=============
	      //   | ww| w # c | e |   |
	      //  =========#---|---|---|-
	      //   |   | sw| s | se|   |
	      //  -|---|---|---|---|---|-
	      //
	      // * Values of pointers to access pixels of components:
	      //     - c  :  PIX_MAP_POINTER
	      //     - se :  PIX_MAP_POINTER + imgWidth + 1
	      //   By construction (see beginning of the present section 4),
	      //   all these values determine valid pointers
	      //
	      // * From now on, this pixel has never been taken into account

	      // Update count of +/- pixels of component c: labels
	      // are coded so that the label has just to be added to
	      // the current count
	      tabPlusMinus[compC] += *(pLblImg + imgWidthPlus1) - 1;
	      // NOTE: component se is not necessarily BLACK
	      // (i.e. labelled '+' or '-' in the current image)
	      // as WHITE components are 4-connected
	    } // END pixel se

	} // END if component is white
          // #########################


      // -------------
      // LOOP features
      // -------------
      if (colIdx == colCnt)
	{
	  // THE CURRENT ROW IS PROCESSED...
	  if (rowIdx == rowCnt)
	    {
	      // ...AND ALL THE ROWS ARE PROCESSED
	      notLastPixel = false;
	    }
	  else
	    {
	      // ...AND ALL THE ROWS ARE NOT PROCESSED
	      // Next row
	      ++rowIdx;
	      colIdx = 1;
	      // Update pointers in pixel maps
	      pCompImg += 3;
	      pLblImg  += 3;	      
	    }
	}
      else
	{
	  // THE CURRENT ROW IS NOT PROCESSED
	  // Next pixel
	  ++colIdx;
	  // Update pointers in pixel maps
	  ++pCompImg;
	  ++pLblImg;
	} // END loop features

    } // -----------------------------------------------------------------
      // END while notLastPixel
      // -----------------------------------------------------------------


  // ===================================================================
  // (5) CONSTRUCTION OF THE RESULTING BINARY IMAGE
  // ===================================================================

  // (5.1) Transform the current image into a true binary image
  // =====
  // Pointer to the pixel map:
  // pLblImg  : image of labels {-,0,+} (current image)
  // pCompImg : component image
  pLblImg  = this->pPixMap();
  pCompImg = compImg.pPixMap();

  for (int pixIdx = 0 ; pixIdx < imgSize ; ++pixIdx, ++pLblImg, ++pCompImg)
    {

       if (*pCompImg == 0)
 	{
 	  // Current pixel belongs to the background => WHITE
 	  *pLblImg = QGE_BW_WHITE;
 	}
       else
 	{
	  if (*pLblImg == LABEL_PLUS)
	    {
	      // Current pixel is labelled '+'  => BLACK
	      *pLblImg = QGE_BW_BLACK;
	    }
	  else if (*pLblImg == LABEL_MINUS)
	    {
	      // Current pixel is labelled '-'  => WHITE
	      *pLblImg = QGE_BW_WHITE;	      
	    }
	  else if (tabPlusMinus[*pCompImg] > 0)
	    {
	      // Current pixel is labelled '0' and N+ > N-  => BLACK
	      *pLblImg = QGE_BW_BLACK;
	    }
	  else
	    {
	      // Current pixel is labelled '0' and N+ <= N-  => WHITE
	      *pLblImg = QGE_BW_WHITE;
	    }
 	} // END if

    } // END for


  // (5.2) Delete useless objects
  // =====
  delete components;
  delete [] tabPlusMinus;


  // ===================================================================
  // (6) POST-PROCESSING
  // ===================================================================

  // (6.1) Create a binary image with 2 extra rows/columns around it
  // =====
  //
  // WARNING: In the image of (labels of) components, the first and
  // last rows, as well as the first and last columns are always set
  // to the background (see class qgar::ConnectedComponents). 
  // If 2 extra rows and columns of BLACK pixels (B below) are added
  // around the image. In that way, WHITE regions touching the image
  // borders (w) do not belong to the background (W) in the resulting
  // component image:
  //
  //
  //  B B B B B B B ...                               W W W W W W W ...
  //  B B B B B B B ...                               W B B B B B B ...
  //  B B b w w b b ...  -- connected components -->  W B b w w b b ...
  //  B B w w w w b ...                               W B w w w w b ...
  //  B B b b b b b ...                               W B b b b b b ...
  //  . . . . . . . ...                               . . . . . . . ...

  // negImg  : the (negative) binary image
  // pNegImg : pointer to its pixel map
  BinaryImage negImg(imgWidthPlus4, imgHeightPlus4);
  pNegImg = negImg.pPixMap();

  for (int colIdx = 0 ; colIdx < (imgWidthX2 + 8) ; ++colIdx)
    {
      *pNegImg = QGE_BW_BLACK;
      ++pNegImg;
    }
  for (int rowIdx = 0 ; rowIdx < imgHeight ; ++rowIdx)
    {
      *pNegImg = QGE_BW_BLACK;
      ++pNegImg;
      *pNegImg = QGE_BW_BLACK;
      pNegImg += imgWidthPlus1;
      *pNegImg = QGE_BW_BLACK;
      ++pNegImg;
      *pNegImg = QGE_BW_BLACK;
      ++pNegImg;
    }
  for (int colIdx = 0 ; colIdx < (imgWidthX2 + 8) ; ++colIdx)
    {
      *pNegImg = QGE_BW_BLACK;
      ++pNegImg;
    }


  // (6.2) Construct the negative of the current image
  // =====
  // pNegImg : pointer to the pixel map of the negative image
  // pResImg : pointer to the pixel map of the final image
  pNegImg = negImg.pPixMap() + imgWidthX2 + 10;
  pResImg = this->pPixMap();

  for (int rowIdx = 0 ; rowIdx < imgHeight ; ++rowIdx)
    {
      for (int colIdx = 0 ; colIdx < imgWidth ; ++colIdx)
	{
	  *pNegImg = (*pResImg == QGE_BW_WHITE) ? QGE_BW_BLACK : QGE_BW_WHITE;

	  ++pResImg; // Next pixel in the source (positive) image
	  ++pNegImg; // Next pixel in the destination (negative) image
	}
      pNegImg += 4 ; // Next row in the destination (negative) image
    } // END for rowIdx


  // (6.3) Connected components of the negative image
  // ===== WHITE components are 4-connected
  //       => BLACK components of the initial image are 4-connected

  ConnectedComponents negComponents(negImg);

  // The image of components and the total number of components
  const ConnectedComponents::image_type&
    negCompImg = negComponents.accessComponentImage();
  compCnt = negComponents.componentCnt();


  // (6.4) Process WHITE components
  // =====
  // NOTE: there's no need to process component 0, i.e. background

  for (int compIdx = 1 ; compIdx < compCnt ; ++compIdx)
    // -------------------------------------------------------------------
    // FOR each component
    // -------------------------------------------------------------------
    {
      // The current component
      Component& comp = negComponents[compIdx];


      if (comp.color() == QGE_BW_WHITE)
	{
	  // THE COMPONENT IS WHITE (i.e. INITIALLY BLACK) 
	  // #############################################

	  // The bounding box of the component
	  const BoundingBox& bb = comp.accessBoundingBox();
	  int bbWidth  = bb.width();
	  int bbHeight = bb.height();

	  // Offsets of the top left pixel of the component:
	  // offTopL    : in the Gradient image
	  // offTopLNeg : in the (negative) component image
	  int offTopL    = ((comp.yTopLeftPix() - 2) * imgWidth) + comp.xTopLeftPix() - 2;
	  int offTopLNeg = (comp.yTopLeftPix() * imgWidthPlus4) + comp.xTopLeftPix();

	  // Pointers to the pixel map:
	  // pGradModImg : Gradient image
	  // pNegCompImg : (negative) component image
	  pGradModImg = gradModImg->pPixMap() + offTopL;
	  pNegCompImg = negCompImg.pPixMap()  + offTopLNeg;

	  // Offsets to go to next row:
	  // offNextRow    : in the Gradient image
	  // offNextRowNeg : in the (negative) component image
	  int offNextRow    = imgWidth - bbWidth;
	  int offNextRowNeg = offNextRow + 4;

	  // (6.4.1) Compute the average sum of the Gradient modules
	  // ======= of the contour pixels of the current component

	  // contourCnt : number of pixels of the contour
	  // gradSum    : sum of the Gradient modules
	  GradientModuleImage::value_type contourCnt = 0;
	  GradientModuleImage::value_type gradSum    = 0;

	  // Offset of the top left pixel of the component in the bounding box
	  int colIdx = comp.xTopLeftPix() - bb.xTopLeft();
	  
	  for (int rowIdx = 0 ; rowIdx < bbHeight ; ++rowIdx)
	    {
	      while (colIdx < bbWidth)
		{
		  // 4-connectivity:
		  //   . n .
		  //   w C e
		  //   . s .
		  //
		  // C is the current pixel (in component compIdx).
		  // Pixel map pointer offsets to point to:
		  //   * n: -(imgWidth + 4)  4 extra columns in the negative image
		  //   * w: -1
		  //   * e: +1
		  //   * s: +(imgWidth + 4)  4 extra columns in the negative image
		  // These pointers are always valid,
		  // by construction of the component image

		  if ((*pNegCompImg == compIdx) // C in current component
		      &&
                      (   (*(pNegCompImg - imgWidthPlus4) != compIdx)   // n != C
                       || (*(pNegCompImg - 1)             != compIdx)   // w != C
                       || (*(pNegCompImg + 1)             != compIdx)   // e != C
		       || (*(pNegCompImg + imgWidthPlus4) != compIdx))) // s != C
		    {
		      // The current pixel is in the border
		      ++contourCnt;
		      gradSum += *pGradModImg;
		    }
		  ++colIdx;
		  ++pNegCompImg;
		  ++pGradModImg;
		}

	      // Next row of the bounding box
	      colIdx = 0;
	      pNegCompImg += offNextRowNeg;
	      pGradModImg += offNextRow;
	    } // END for each row of the bounding box
	      // (6.4.1) ============================


	  // (6.4.2) If the average sum is less than argument aPostThrs,
	  // ======= the component becomes WHITE in the final image

	  if ((gradSum / contourCnt) < aPostThrs)
	    {
	      // pNegCompImg : pointer to the pixel map of the component image
	      // offTopLNeg  : offset of the top left pixel of the component
	      //               in the component image
	      pNegCompImg = negCompImg.pPixMap() + offTopLNeg;

	      // pResImg : pointer to the pixel map of the final image
	      // offTopL : offset of the top left pixel of the component
	      //           in the final image
	      pResImg = this->pPixMap() + offTopL;

	      // Offset of the top left pixel of the component
	      // in the bounding box
	      colIdx = comp.xTopLeftPix() - bb.xTopLeft();
	  
	      for (int rowIdx = 0 ; rowIdx < bbHeight ; ++rowIdx)
		{
		  while (colIdx < bbWidth)
		    {
		      if ((*pNegCompImg) == compIdx)
			{
			  // The current pixel belongs to the current component
			  // => it becomes WHITE in the final image
			  *pResImg = QGE_BW_WHITE;
			}
		      ++colIdx;
		      ++pNegCompImg;
		      ++pResImg;
		    }

		  // Next row of the bounding box
		  colIdx = 0;
		  pNegCompImg += offNextRowNeg;
		  pResImg     += offNextRow;
		} // END for each row of the bounding box
	  
	    } // END if average sum
              // (6.4.2) ==========

	} // END if current component is WHITE
          // #################################
      
    } // --------------------------------
      // END for each component (compIdx)
      // --------------------------------


  // (6.5) Delete useless Gradient module image
  // =====
  delete gradModImg;


  // ===================================================================
  // (7) FIRST AND LAST ROWS / FIRST AND LAST COLUMNS
  // ===================================================================
  // These rows and columns are set to WHITE when connected components
  // are constructed (see class qgar::ConnectedComponents)
  // => fill each of these rows (resp. columns) with its adjacent row
  //    (resp. column) in the final image

  // Pointer to the pixel map of the final image
  pResImg = this->pPixMap() + imgWidthPlus1;

  // TOP LEFT CORNER:    +------           +------
  //                     | . . .           | B . .
  //                     | . B      ==>    | B B<--- starting pixel
  //                     | .               | .

  if (*pResImg == QGE_BW_BLACK)
    {
      *(pResImg - 1)             = QGE_BW_BLACK;
      *(pResImg - imgWidthPlus1) = QGE_BW_BLACK;
    }

  // FIRST ROW
  for (int colIdx = 1 ; colIdx < imgWidthMinus1 ; ++colIdx)
    {
      *(pResImg - imgWidth) = *pResImg;
      ++pResImg;
    }

  // TOP RIGHT CORNER: same principle as top left corner
  if (*(pResImg - 1) == QGE_BW_BLACK)
    {
      *pResImg              = QGE_BW_BLACK;
      *(pResImg - imgWidth) = QGE_BW_BLACK;
    }

  // FIRST AND LAST COLUMNS
  for (int rowIdx = 1 ; rowIdx < (imgHeight - 3) ; ++rowIdx)
    {
      ++pResImg;
      *pResImg = *(pResImg + 1);
      pResImg += imgWidthMinus1;
      *pResImg = *(pResImg - 1);
    }

  // BOTTOM RIGHT CORNER: same principle as top left corner
  pResImg += 2;
  if (*pResImg == QGE_BW_BLACK)
    {
      *(pResImg - 1)              = QGE_BW_BLACK;
      *(pResImg + imgWidthMinus1) = QGE_BW_BLACK;
    }

  // LAST ROW
  for (int colIdx = 1 ; colIdx < imgWidthMinus1 ; ++colIdx)
    {
      *(pResImg + imgWidth) = *pResImg;
      ++pResImg;
    }

  // BOTTOM RIGHT CORNER: same principle as top left corner
  if (*(pResImg - 1) == QGE_BW_BLACK)
    {
      *pResImg              = QGE_BW_BLACK;
      *(pResImg + imgWidth) = QGE_BW_BLACK;
    }


  // ===================================================================
  // END of the constructor
  // ===================================================================
}


// ---------------------------------------------------------------------


} // namespace qgar
