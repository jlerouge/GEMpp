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


#ifndef __GENCONVOLIMAGE_H_INCLUDED__
#define __GENCONVOLIMAGE_H_INCLUDED__


/**
 * @file GenConvolImage.h
 *
 * @brief Header file of class qgar::GenConvolImage.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   January 5, 2004  11:05
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: GenConvolImage.h,v 1.20 2006/07/04 15:10:15 masini Exp $ */



// QGAR
#include "GenImage.h"
#include "GenMask1d.h"
#include "GenMask2d.h"



namespace qgar
{


/**
 * @ingroup IMGPROC_CONVOL
 *
 * @class GenConvolImage GenConvolImage.h "qgarlib/GenConvolImage.h"
 *
 * @brief Convolution of an image by a 1D or 2D mask.
 *
 * The code implementing this class is an adaptation of code written by
 * Carsten Steger at TU Muenchen, Germany.
 * Here is the corresponding copyright notice:
@verbatim
 +----------------------------------------------------------------------+
 | Copyright (C) 1996 Carsten Steger                                    |
 |                                                                      |
 | This program is free software; you can redistribute it and/or modify |
 | it under the terms of the GNU General Public License as published by |
 | the Free Software Foundation; either version 2, or (at your option)  |
 | any later version.                                                   |
 |                                                                      |
 | This program is distributed in the hope that it will be useful, but  |
 | WITHOUT ANY WARRANTY; without even the implied warranty of           |
 | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    |
 | General Public License for more details.                             |
 |                                                                      |
 | You should have received a copy of the GNU General Public License    |
 | along with this program; if not, write to the Free Software          |
 | Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.            |
 +----------------------------------------------------------------------+
@endverbatim
 *
 * All computation uses <b>double</b> numbers.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date   January 5, 2004  15:28
 * @since  Qgar 2.1.1
 */
template
<
  class T,
  template<class> class CheckingPolicy = GenImage_NoCheck
>
class GenConvolImage

  : public GenImage<T, CheckingPolicy>

{
// -------------------------------------------------------------------
// T Y P E   D E F I N I T I O N S
// -------------------------------------------------------------------
public:


  /** @name Types */
  //        =====
  //@{

  /**
   * @brief Type of the elements stored in the pixmap.
   */
  typedef T value_type;

  /**
   * @brief Reference to qgar::GenConvolImage::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::GenConvolImage::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::GenConvolImage::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::GenConvolImage::value_type.
   */
  typedef const value_type* const_pointer;

  //@}


// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:


  /** @name Constructors */
  //        ============
  //@{

  /**
   * @brief Convolution of an image and a 1D mask.
   *
   * @param anImg   image to be convolved
   * @param aMask   convolution mask
   * @param anAxis  axis (default qgar::QGE_AXIS_X)
   */
  template
  <
    class ImageType, 
    template<class> class ImageCheckPolicy, 
    class MaskType
  >
  GenConvolImage(const GenImage<ImageType, ImageCheckPolicy>& anImg,
		 const GenMask1d<MaskType>& aMask,
		 QGEaxis anAxis);

  /**
   * @brief Convolution of an image and a 1D mask.
   *
   * Specialization of the general template constructor. 
   *
   * @param anImg   image to be convolved
   * @param aMask   convolution mask
   * @param anAxis  axis (default qgar::QGE_AXIS_X)
   */
  template
  <
    class ImageType, 
    template<class> class ImageCheckPolicy
  >
  GenConvolImage(const GenImage<ImageType, ImageCheckPolicy>& anImg,
		 const GenMask1d<double>& aMask,
		 QGEaxis anAxis);

  /**
   * @brief Convolution of an image and a 2D mask.
   *
   * Specialization of the general template constructor. 
   *
   * @param anImg  image to be convolved
   * @param aMask  convolution mask
   */
  template
  <
    class ImageType, 
    template<class> class ImageCheckPolicy, 
    class MaskType
  >
  GenConvolImage(const GenImage<ImageType, ImageCheckPolicy>& anImg,
		 const GenMask2d<MaskType>& aMask);

  /**
   * @brief Convolution of an image and a 2D mask.
   *
   * Specialization of the general template constructor. 
   *
   * @param anImg  image to be convolved
   * @param aMask  convolution mask
   */
  template
  <
    class ImageType, 
    template<class> class ImageCheckPolicy
  >
  GenConvolImage(const GenImage<ImageType, ImageCheckPolicy>& anImg,
		 const GenMask2d<double>& aMask);

  /**
   * @brief Copy constructor.
   *
   * @param other another instance of the class
   */
  GenConvolImage(const GenConvolImage& other);

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  virtual ~GenConvolImage();

  //@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:


  /** @name 1D convolutions */
  //        ===============
  //@{

  /**
   * @brief Convolve and image along X axis with a 1D mask.
   *
   * @param anImg  image to be convolved
   * @param aMask  1D convolution mask
   */
  template
  <
    class ImageType, 
    template<class> class ImageCheckPolicy
  >
  void xconvol(const GenImage<ImageType,ImageCheckPolicy>& anImg,
	       const DMask1d& aMask);


  /**
   * @brief Convolve along Y axis with a 1D mask.
   *
   * @param anImg  image to be convolved
   * @param aMask  1D convolution mask
   */
  template
  <
    class ImageType, 
    template<class> class ImageCheckPolicy
  >
  void yconvol(const GenImage<ImageType,ImageCheckPolicy>& anImg,
	       const DMask1d& aMask);

  //@}


  /** @name 2D convolutions */
  //        ===============
  //@{

  /**
   * @brief Convolve with a 2D mask.
   *
   * @param anImg  image to be convolved
   * @param aMask  2D convolution mask
   */
  template
  <
    class ImageType, 
    template<class> class ImageCheckPolicy
  >
  void convol(const GenImage<ImageType,ImageCheckPolicy>& anImg,
	      const DMask2d& aMask);

  /**
   * @brief Compute the convolution of an image and a mask
   * for a given pixel using row and column mirroring.
   * 
   * @param img     image to be convolved
   * @param mask    mask to perform the convolution with
   * @param imgRow  row index of the point to apply the mask
   * @param imgCol  column index of the point to apply the mask
   */
  template
  <
    class ImageType,
    template<class> class OtherCheckPolicy
  >
  double applyMaskWithRowAndColMirroring
    (const GenImage<ImageType,OtherCheckPolicy>& img,
     const DMask2d& mask,
     int imgRow,
     int imgCol);


  /**
   * @brief Compute the convolution of an image and a mask
   * for a given pixel using row mirroring.
   * 
   * @param img     image to be convolved
   * @param mask    mask to perform the convolution with
   * @param imgRow  row index of the point to apply the mask
   * @param imgCol  column index of the point to apply the mask
   */
  template
  <
    class ImageType,
    template<class> class OtherCheckPolicy
  >
  double
  applyMaskWithRowMirroring
    (const GenImage<ImageType,OtherCheckPolicy>& img,
     const DMask2d mask,
     int imgRow,
     int imgCol);


  /**
   * @brief Compute the convolution of an image and a mask
   * for a given pixel using column mirroring.
   * 
   * @param img     image to be convolved
   * @param mask    mask to perform the convolution with
   * @param imgRow  row index of the point to apply the mask
   * @param imgCol  column index of the point to apply the mask
   */
  template
  <
    class ImageType,
    template<class> class OtherCheckPolicy
  >
  double
  applyMaskWithColMirroring(const GenImage<ImageType,OtherCheckPolicy>& img,
			    const DMask2d mask,
			    int imgRow,
			    int imgCol);


  /**
   * @brief Compute the convolution of an image and a mask
   * for a given pixel.
   * 
   * @param img     image to be convolved
   * @param mask    mask to perform the convolution with
   * @param imgRow  row index of the point to apply the mask
   * @param imgCol  column index of the point to apply the mask
   */
  template
  <
    class ImageType,
    template<class> class OtherCheckPolicy
  >
  double
  applyMask(const GenImage<ImageType,OtherCheckPolicy>& img,
	    const DMask2d mask,
	    int imgRow,
	    int imgCol);

  //@}


// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

  //
  /** @name Disabled */
  //        ========
  //@{

  /**
   * @brief Assignment operator.
   *
   * @param rhs an instance of the class
   */
  GenConvolImage& operator=(const GenConvolImage& rhs);

  //@}

// -------------------------------------------------------------------
}; // class GenConvolImage


} // namespace qgar




// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// I M P L E M E N T A T I O N
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII

#include "GenConvolImage.tcc"

// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII




// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// P R E D E F I N E D   C O N V O L U T I O N   I M A G E   T Y P E S
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


namespace qgar
{


  /** @name Predefined convolution types */
  //        ============================
  //@{

  /**
   * @ingroup IMGPROC_CONVOL
   *
   * @brief Convolution of an image of integer pixels.
   */
  typedef GenConvolImage<int> IConvolImage;

  /**
   * @ingroup IMGPROC_CONVOL
   *
   * @brief Convolution of an image of <b>float</b> pixels.
   */
  typedef GenConvolImage<float> FConvolImage;

  /**
   * @ingroup IMGPROC_CONVOL
   *
   * @brief Convolution of an image of <b>double</b> pixels.
   *
   * @see qgar::ConvolImage
   */
  typedef GenConvolImage<double> DConvolImage;

  /**
   * @ingroup IMGPROC_CONVOL
   *
   * @brief Convolution of an image of <b>double</b> pixels.
   *
   * @see qgar::DConvolImage
   */
  typedef GenConvolImage<double> ConvolImage;

  //@}


} // namespace qgar


// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


#endif /* __GENCONVOLIMAGE_H_INCLUDED__ */
