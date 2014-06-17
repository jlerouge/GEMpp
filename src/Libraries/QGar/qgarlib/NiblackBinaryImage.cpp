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
 * @file   NiblackBinaryImage.cpp
 * @brief  Implementation of class qgar::NiblackBinaryImage.
 *
 * See file NiblackBinaryImage.h for the interface.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date     July 3, 200  15:01
 * @since    Qgar 2.0
 */



// QGAR
#include "CannyGradientImage.h"
#include "Component.h"
#include "ConnectedComponents.h"
#include "ErodedBinaryImage.h"
#include "GenImage.h"
#include "GradientModuleImage.h"
#include "NiblackBinaryImage.h"
#include "StandardDeviationImage.h"



namespace qgar
{

// -------------------------------------------------------------------
// C O N S T R U C T O R
// -------------------------------------------------------------------

NiblackBinaryImage::NiblackBinaryImage(const GreyLevelImage& anImg,
				       const int aLowThres,
				       const int aHighThres,
				       const int aMaskSize,
				       const float aK,
				       const float aPostThres)

  : BinaryImage(anImg.width(), anImg.height())

{
  // Pointer to mean image
  FloatImage* pMeanImg = 0;

  // Compute standard deviation and mean
  StandardDeviationImage stdImg(FloatImage(anImg), pMeanImg, aMaskSize);

  // Rows to exchange data
  GreyLevelImage::pointer bRow = new GreyLevelImage::value_type [_width];
  GreyLevelImage::pointer gRow = new GreyLevelImage::value_type [_width];

  float* mRow = new float [_width];
  float* sRow = new float [_width];
  
  // Binarize
  for (int i = 0 ; i < _height ; ++i)
    {
      // Read means
      pMeanImg->row(i, mRow);
      // Read deviations
      stdImg.row(i, sRow);
      // Read original
      anImg.row(i, gRow);

      // Pointers
      float* m = mRow;
      float* s = sRow;
      GreyLevelImage::pointer g = gRow;
      GreyLevelImage::pointer b = bRow;

      // Dynamic thresholding
      for (int j = 0 ; j < _width ; ++j, ++b, ++g)
	{
	  if (*g < aLowThres)
	    {
	      *b = 1;
	    }
	  else if (*g > aHighThres)
	    {
	      *b = 0;
	    }
	  else if (*g < (GreyLevelImage::value_type) (*m++ + aK * *s++))
	    {
	      *b = 1;
	    }
	  else
	    {
	      *b = 0;
	    }
	}

      // Save line
      setRow(i, bRow);
    }

  // Post-processing
  if (aPostThres > 0)
    {
      // Copy reference image
      BinaryImage* contours = new BinaryImage(*this);

      // Extract connected components
      ConnectedComponents* compConnexes = new ConnectedComponents(*contours);

      // Prepare tables
      int labCnt = compConnexes->componentCnt();
      // Tables for the sums of the means of the gradient
      float* gsum = new float [labCnt];
      qgFill(gsum, labCnt, 0.f);
      // Tables for the numbers of points -- for the mean
      int* psum = new int [labCnt];
      qgFill(psum, labCnt, 0);

      // Table of labels
      Component::label_type* labRow = new Component::label_type[_width];
      // By construction, first and last pixels are always WHITE
      labRow[1] = 0;
      labRow[_width - 1] = 0;

      // Compute the module of Canny gradient
      CannyGradientImage* gradImg = new CannyGradientImage(anImg);
      GradientModuleImage gradModImg(*gradImg);
      delete gradImg;

      // Construct the image of the contours of the black components
      // which thus includes the interesting pixels
      ErodedBinaryImage* eroImg = new ErodedBinaryImage(*contours);
      (*contours) -= (*eroImg);
      delete eroImg;

      // Create a line of floats
      float* fRow = new float [_width];

      // Pointer to the pixel map of the component image
      Component::label_type* pMapCCImg =
	(compConnexes->accessComponentImage()).pPixMap() + _width;

      for (int i = 1 ; i < (_height - 1) ; ++i)
	{
	  // Get a line of labels from the component image
	  // and set pixels from white components to 0
	  pMapCCImg += 2;
	  PRIVATEgetBlackLabels(pMapCCImg, labRow);

	  // Read the corresponding line in the contours
	  contours->row(i, bRow);

	  // Read the corresponding line in the module of the gradient
	  gradModImg.row(i, fRow);
	  Component::label_type* p = labRow;
	  GreyLevelImage::pointer q = bRow;
	  float* r = fRow;
	  for (int j = 0 ; j < _width ; ++j, ++p, ++q, ++r)
	    {
	      if (*q != 0)  // We are on a contour
		{
		  gsum[(int)(*p)] += *r;
		  psum[(int)(*p)] += 1;
		}
	    } // END for j
	} // END for i

      delete contours;
 
     // Compute the means
      for (int i = 0 ; i < labCnt ; ++i)
	{
	  if (psum[i] != 0)
	    {
	      gsum[i] /= psum[i];
	    }
	} // END for
  
      // Pointer to the pixel map of the component image
      pMapCCImg = (compConnexes->accessComponentImage()).pPixMap() + _width;
      // Delete fake black components
      for (int i = 1 ; i < _height - 1 ; ++i)
	{
	  // Read the current line of components
	  pMapCCImg += 2;
	  PRIVATEgetBlackLabels(pMapCCImg, labRow);

	  // Read the corresponding line in the binary image
	  row(i, bRow);

	  // Examine components and delete
	  Component::label_type* p = labRow;
	  GreyLevelImage::pointer pb = bRow;
	  for (int j = 0 ; j < _width ; ++j, ++p, ++pb)
	    {
	      if (((*pb) != 0) && (gsum[(int)(*p)] < aPostThres))
		{
		  *pb = 0;
		}
	    }

	  // Save this line
	  setRow(i, bRow);
	} // END for

      // Clean up
      delete [] fRow;
      delete [] psum;
      delete [] gsum;
      delete compConnexes;
    }

  // And clean up
  delete [] bRow;
  delete [] gRow;
  delete [] mRow;
  delete [] sRow;
}

// -------------------------------------------------------------------
// P R I V A T E    F U N C T I O N S
// -------------------------------------------------------------------

// Get a line of labels from the component image
// and set pixels from WHITE components to 0

void
NiblackBinaryImage::PRIVATEgetBlackLabels(Component::label_type* aPMapCCImg,
					  Component::label_type* aBuffer)
{
  // By construction, first pixel of each line is WHITE
  // and the color of the current pixel changes when the label changes

  Component::label_type prevLabel = 0;
  bool currColorIsWhite = true;

  for (int idx = 1 ; idx < (_width - 2) ; ++idx, ++aPMapCCImg)
    {
      Component::label_type currLabel = *aPMapCCImg;

      if (currLabel != prevLabel)
	{
	  currColorIsWhite = !currColorIsWhite;
	  prevLabel = currLabel;
	}

      if (currColorIsWhite)
	{
	  aBuffer[idx] = 0;
	}
      else
	{
	  aBuffer[idx] = currLabel;
	}
    }
}

// -------------------------------------------------------------------

} // namespace qgar
