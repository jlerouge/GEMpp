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
 * @file   GenConvolImage.tcc
 * @brief  Implementation of function members of class qgar::GenConvolImage.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   January 27, 2005  20:54
 * @since  Qgar 2.2
 */



// QGAR
#include "GenImage.h"
#include "GenMask1d.h"
#include "GenMask2d.h"



namespace qgar
{


// -------------------------------------------------------------------
// C O N S T R U C T O R S
// -------------------------------------------------------------------


// CONSTRUCTOR FROM AN IMAGE AND A 1D MASK

template<class T, template<class> class CheckingPolicy>
template
<
  class ImageType, 
  template<class> class ImageCheckPolicy, 
  class MaskType
>
GenConvolImage<T, CheckingPolicy>::GenConvolImage(
  const GenImage<ImageType, ImageCheckPolicy>& anImg,
  const GenMask1d<MaskType>& aMask,
  QGEaxis anAxis)

  : GenImage<T, CheckingPolicy>(anImg.width(), anImg.height())

{
  // Convert mask to a mask of doubles.
  DMask1d mask(aMask);

  if (anAxis == QGE_AXIS_X)
    {
      xconvol(anImg, mask);
    }
  else
    {
      yconvol(anImg, mask);
    }  
}


// CONSTRUCTOR SPECIALIZATION WITH A DOUBLE 1D MASK
//
// Since the mask coeffs are already in double format, there is no
// need for converting it before calling the convolution

template<class T, template<class> class CheckingPolicy>
template
<
  class ImageType, 
  template<class> class ImageCheckPolicy
>
GenConvolImage<T, CheckingPolicy>::GenConvolImage(
  const GenImage<ImageType, ImageCheckPolicy>& anImg,
  const GenMask1d<double>& aMask,
  QGEaxis anAxis)

  : GenImage<T, CheckingPolicy>(anImg.width(), anImg.height())

{
  if (anAxis == QGE_AXIS_X)
    {
      xconvol(anImg, aMask);
    }
  else
    {
      yconvol(anImg, aMask);
    }  
}



// 2D CONVOLUTION

template<class T, template<class> class CheckingPolicy>
template
<
  class ImageType, 
  template<class> class ImageCheckPolicy, 
  class MaskType
>
GenConvolImage<T, CheckingPolicy>::GenConvolImage(
  const GenImage<ImageType, ImageCheckPolicy>& anImg,
  const GenMask2d<MaskType>& aMask)

  : GenImage<T, CheckingPolicy>(anImg.width(), anImg.height())

{
  // Convert mask to a mask of doubles.
  DMask2d mask(aMask);

  convol(anImg, mask);
}


// CONSTRUCTOR SPECIALIZATION WITH A DOUBLE 2D MASK
//
// Since the mask coeffs are already in double format, there is no
// need for converting it before calling the convolution

template<class T, template<class> class CheckingPolicy>
template
<
  class ImageType, 
  template<class> class ImageCheckPolicy
>
GenConvolImage<T, CheckingPolicy>::GenConvolImage(
  const GenImage<ImageType, ImageCheckPolicy>& anImg,
  const GenMask2d<double>& aMask)

  : GenImage<T, CheckingPolicy>(anImg.width(), anImg.height())

{
  convol(anImg, aMask);
}


// COPY CONSTRUCTOR

template<class T, template<class> class CheckingPolicy>
GenConvolImage<T, CheckingPolicy>::GenConvolImage(const GenConvolImage& other)

  : GenImage<T, CheckingPolicy>(other)

{
  // EMPTY
}


// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------


template<class T, template<class> class CheckingPolicy>
GenConvolImage<T, CheckingPolicy>::~GenConvolImage()
{
  // EMPTY
}


// -------------------------------------------------------------------
// 1 D   C O N V O L U T I O N S
// -------------------------------------------------------------------


// X AXIS

template<class T, template<class> class CheckingPolicy>
template
<
  class ImageType, 
  template<class> class ImageCheckPolicy
>
void 
GenConvolImage<T, CheckingPolicy>::xconvol(
  const GenImage<ImageType, ImageCheckPolicy>& anImg,
  const DMask1d& aMask)
{
  int r = 0;
  int c = 0;
  int sizeMask = aMask.width() / 2;

  // Inner region
  for (/* EMPTY */ ; r < this->_height ; ++r) 
    {
      ImageType *p = anImg.pPixMap() + r * this->_width;
      T         *q = this->_pPixMap + r * this->_width + sizeMask;
      for (c = sizeMask ; c < this->_width - sizeMask; ++c, ++p)
	{
	  double sum = 0.0;
	  ImageType * pp = p;
	  double* mm = aMask.pCoeffMap();
	  for (int j = 0 ; j < aMask.width() ; ++j)
	    {
	      sum += *pp * *mm;
	      ++pp;
	      ++mm;
	    }
	  *q = static_cast<T>(sum);
	  ++q;
	}
    }

  // Border regions
  for (r = 0 ; r < this->_height; ++r)
    {
      T         *q = this->_pPixMap + r * this->_width;
      ImageType *p = anImg.pPixMap() + r * this->_width;
      for (c = 0 ; c < sizeMask ; ++c)
	{
	  double sum = 0.0;
	  double * mm = aMask.pCoeffMap();
	  int cc = c - sizeMask;
	  for (int j = 0 ; j < aMask.width() ; ++j, ++cc)
	    {
	      sum += *(p + this->borderCols(cc)) * *mm;
	      ++mm;
	    }
	  *q = static_cast<T>(sum);
	  ++q;
	}

      // Reset
      q = this->_pPixMap + r * this->_width + this->_width - sizeMask;

      for (c = this->_width - sizeMask ; c < this->_width ; ++c) 
	{
	  double sum = 0.0;
	  double * mm = aMask.pCoeffMap();
	  int cc = c - sizeMask;
	  for (int j = 0 ; j < aMask.width() ; ++j, ++cc)
	    {
	      sum += *(p + this->borderCols(cc)) * *mm;
	      ++mm;
	    }
	  *q = static_cast<T>(sum);
	  ++q;
	}
    }
}


// Y AXIS

template<class T, template<class> class CheckingPolicy>
template
<
  class ImageType, 
  template<class> class ImageCheckPolicy
>
void 
GenConvolImage<T, CheckingPolicy>::yconvol(
  const GenImage<ImageType, ImageCheckPolicy>& anImg,
  const DMask1d& aMask)
{
  int c = 0;
  int sizeMask = aMask.width() / 2;
  int r = sizeMask;

  // Inner region
  for ( ; r < this->_height - sizeMask ; ++r) 
    {
      ImageType *p = anImg.pPixMap() + (r - sizeMask) * this->_width;
      T         *q = this->_pPixMap + r * this->_width;
      for ( c = 0 ; c < this->_width; ++c, ++p)
	{
	  double sum = 0.0;
	  ImageType * pp = p;
	  double * mm = aMask.pCoeffMap();
	  for (int j = 0 ; j < aMask.width() ; ++j, pp += this->_width)
	    {
	      sum += *pp * *mm;
	      ++mm;
	    }
	  *q = static_cast<T>(sum);
	  ++q;
	}
    }

  // Border regions
  for (r = 0 ; r < sizeMask ; ++r)
    {
      T *q = this->_pPixMap + r * this->_width;
      for (c = 0 ; c < this->_width ; ++c)
	{
	  double sum = 0.0;
	  double * mm = aMask.pCoeffMap();
	  int l = r - sizeMask;
	  for (int j = 0 ; j < aMask.width() ; ++j, ++l)
	    {
	      sum +=
		*(anImg.pPixMap() + this->borderRows(l) * this->_width + c) * *mm;
	      ++mm;
	    }
	  *q = static_cast<T>(sum);
	  ++q;
	}
    }

  for (r = this->_height - sizeMask ; r < this->_height ; ++r)
    {
      T *q = this->_pPixMap + r * this->_width;
      for (c = 0 ; c < this->_width ; ++c)
	{
	  double sum = 0.0;
	  double * mm = aMask.pCoeffMap();
	  int l = r - sizeMask;
	  for (int j = 0 ; j < aMask.width() ; ++j, ++l)
	    {
	      sum += 
		*(anImg.pPixMap() + this->borderRows(l) * this->_width + c) * *mm;
	      ++mm;
	    }
	  *q = static_cast<T>(sum);
	  ++q;
	}
    }
}


// -------------------------------------------------------------------
// 2 D   C O N V O L U T I O N S
// -------------------------------------------------------------------


template<class T, template<class> class CheckingPolicy>
template
<
  class ImageType,
  template<class> class OtherCheckPolicy
>
double
GenConvolImage<T, CheckingPolicy>::applyMaskWithRowAndColMirroring
  (const GenImage<ImageType,OtherCheckPolicy>& img,
   const DMask2d& mask,
   int imgRow,
   int imgCol)
{
  double sum = 0.;
  double * pMask = mask.pCoeffMap();

  for (int row=0; row < mask.height(); ++row)
    {
      ImageType * pRow = img.pRow(img.borderRows(imgRow + row));
      
      for(int col=0; col < mask.width(); ++col)
 	{
 	  sum += pRow[img.borderCols(imgCol + col)] * (*pMask);
	  ++pMask;
 	}
    }
  
  return sum;
}



template<class T, template<class> class CheckingPolicy>
template
<
  class ImageType,
  template<class> class OtherCheckPolicy
>
double
GenConvolImage<T, CheckingPolicy>::applyMaskWithColMirroring
  (const GenImage<ImageType,OtherCheckPolicy>& img,
   const DMask2d mask,
   int imgRow,
   int imgCol)
{
  double sum = 0.;
  double * pMask = mask.pCoeffMap();
  
  for (int row=0; row < mask.height(); ++row)
    {
      ImageType * pRow = img.pRow(imgRow + row);
      
      for(int col=0; col < mask.width(); ++col)
 	{
 	  sum += pRow[img.borderCols(imgCol + col)] * (*pMask);
	  ++pMask;
 	}
    }
  return sum;
}



template<class T, template<class> class CheckingPolicy>
template
<
  class ImageType,
  template<class> class OtherCheckPolicy
>
double
GenConvolImage<T, CheckingPolicy>::applyMaskWithRowMirroring
  (const GenImage<ImageType,OtherCheckPolicy>& img,
   const DMask2d mask,
   int imgRow,
   int imgCol)
{
  double sum = 0.;  
  double * pMask = mask.pCoeffMap();

  for (int row=0; row < mask.height(); ++row)
    {
      ImageType * pPix = img.pPixel(img.borderRows(imgRow + row), imgCol);
      
      for (int col = 0 ; col < mask.width() ; ++col)
	{
	  sum += (*pPix) * (*pMask);
	  ++pPix;
	  ++pMask;
	}
      
    }
  return sum;
}
  


template<class T, template<class> class CheckingPolicy>
template
<
  class ImageType,
  template<class> class OtherCheckPolicy
>
double
GenConvolImage<T, CheckingPolicy>::applyMask
 (const GenImage<ImageType,OtherCheckPolicy>& img,
  const DMask2d mask,
  int imgRow,
  int imgCol)
{
  double sum = 0.;
  double * pMask = mask.pCoeffMap();

  for (int row=0; row < mask.height(); ++row)
    {
      ImageType * pPix = img.pPixel(imgRow + row, imgCol);      

      for (int col=0; col < mask.width(); ++col)
	{
	  sum += (*pPix) * (*pMask);
	  ++pPix;
	  ++pMask;
	}      
    }  
  return sum;
}



template<class T, template<class> class CheckingPolicy>
template
<
  class ImageType, 
  template<class> class ImageCheckPolicy
>
void 
GenConvolImage<T, CheckingPolicy>::convol(
  const GenImage<ImageType, ImageCheckPolicy>& anImg,
  const DMask2d& aMask)
{
  //-- Init

  int row; // The current row
  int col; // The current column

  int maskWd = aMask.width()  / 2; // Half of the mask width
  int maskHt = aMask.height() / 2; // Half of the mask height

  unsigned int blockBeginRow = -maskHt;
  unsigned int blockBeginCol = -maskWd;

  T* imgPtr = this->_pPixMap;

  //-- Lines between 0 and half of the mask height

  for (row=0; row < maskHt; ++row, ++blockBeginRow)
    {
      blockBeginCol = -maskWd;
      // Cols in [0..mask_size/2[ (need border mirroring up and left)
      for(col=0; col < maskWd; ++col, ++blockBeginCol)
 	{
	  *imgPtr = 
	    static_cast<T>(applyMaskWithRowAndColMirroring(anImg,
							   aMask,
							   blockBeginRow,
							   blockBeginCol));
	  ++imgPtr;
	}


      // Inner Cols apply (need border mirroring up).
      for(/* EMPTY */; col < (this->_width - maskWd); ++col, ++blockBeginCol)
	{
	  *imgPtr = 
	    static_cast<T>(applyMaskWithRowMirroring(anImg,
						     aMask,
						     blockBeginRow,
						     blockBeginCol));
	  ++imgPtr;
	}

      // Cols in [_width - maskWd.. _width] (need border mirroring up
      // and right
      for(/* EMPTY */; col < this->_width; ++col, ++blockBeginCol)
	{
	  *imgPtr = 
	    static_cast<T>(applyMaskWithRowAndColMirroring(anImg,
							   aMask,
							   blockBeginRow,
							   blockBeginCol));
	  ++imgPtr;
	}
    }


  //-- Lines between [maskHt..height - maskHt[

  for (/* EMPTY */; row < (this->_height - maskHt); ++row, ++blockBeginRow)
    {
      blockBeginCol = -maskWd;

      // Cols in [0..mask_size/2[ (need border mirroring up and left)
      for(col=0; col < maskWd; ++col, ++blockBeginCol)
	{
	  *imgPtr = 
	    static_cast<T>(applyMaskWithColMirroring(anImg,
						     aMask,
						     blockBeginRow,
						     blockBeginCol));
	  ++imgPtr;
	}
      
      // Inner Cols apply (need border mirroring up).
      for(/* EMPTY */; col < (this->_width - maskWd); ++col, ++blockBeginCol)
	{
  	  *imgPtr = 
  	    static_cast<T>(applyMask(anImg,
  				     aMask,
  				     blockBeginRow,
 				     blockBeginCol));
	  ++imgPtr;
	}

      // Cols in [_width - maskWd.. _width]
      for(/* EMPTY */; col < this->_width; ++col, ++blockBeginCol)
	{
	  *imgPtr = 
	    static_cast<T>(applyMaskWithColMirroring(anImg,
						     aMask,
						     blockBeginRow,
						     blockBeginCol));
	  ++imgPtr;
	}
    }


  //-- Lines between [height - maskHt..height[
  
  for(/* EMPTY */; row < this->_height; ++row, ++blockBeginRow)
    {
      blockBeginCol = -maskWd;

     // Cols in [0..mask_size/2[ (need border mirroring up and left)
      for(col=0; col < maskWd; ++col, ++blockBeginCol)
	{
	  *imgPtr = 
	    static_cast<T>(applyMaskWithRowAndColMirroring(anImg,
							   aMask,
							   blockBeginRow,
							   blockBeginCol));
	  ++imgPtr;
	}


      // Inner Cols apply (need border mirroring up).
      for(/* EMPTY */; col < (this->_width - maskWd); ++col, ++blockBeginCol)
	{
	  *imgPtr = 
	    static_cast<T>(applyMaskWithRowMirroring(anImg,
						     aMask,
						     blockBeginRow,
						     blockBeginCol));
	  ++imgPtr;
	}

      // Cols in [_width - maskWd.. _width]
      for(/* EMPTY */; col < this->_width; ++col, ++blockBeginCol)
	{
	  *imgPtr = 
	    static_cast<T>(applyMaskWithRowAndColMirroring(anImg,
							   aMask,
							   blockBeginRow,
							   blockBeginCol));
	  ++imgPtr;
	}
    }
}


// -------------------------------------------------------------------


} // namespace qgar
