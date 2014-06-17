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


#ifndef __ABSTRACTGRADIENTIMAGE_H_INCLUDED__
#define __ABSTRACTGRADIENTIMAGE_H_INCLUDED__


/**
 * @file    AbstractGradientImage.h
 * @brief   Header file of class qgar::AbstractGradientImage.
 *
 * @author  <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date    July 3, 2001  10:12
 * @since   Qgar 1.0
 */


// For RCS/CVS use: Do not delete
/* $Id: AbstractGradientImage.h,v 1.13 2007/02/14 17:34:04 masini Exp $ */



// STD
#include <cmath>
// QGAR
#include "AbstractMultiImage.h"
#include "GenImage.h"



using namespace std;



namespace qgar
{


/**
 * @ingroup IMGPROC_GRAD
 *
 * @class AbstractGradientImage AbstractGradientImage.h "qgarlib/AbstractGradientImage.h"
 *
 * @brief Base class to define gradient images.
 *
 * A pixel of such an image represents a gradient value,
 * i.e. a pair of floats corresponding to derivatives in x and y
 * directions.
 *
 * @warning This is an abstract class. It cannot be instantiated.
 *
 * @see qgar::LocalGradientMaxima
 */
class AbstractGradientImage

  : public AbstractMultiImage

{
// -------------------------------------------------------------------
// T Y P E   D E F I N I T I O N S
// -------------------------------------------------------------------
public:


  /** @name Types */
  //        =====
  //@{

  /**
   * @brief Type of the elements stored in the pixmaps.
   */
  typedef float value_type;

  /**
   * @brief Reference to qgar::AbstractGradientImage::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::AbstractGradientImage::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::AbstractGradientImage::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::AbstractGradientImage::value_type.
   */
  typedef const value_type* const_pointer;

  //@}


// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  virtual ~AbstractGradientImage()
  {
    // VOID
  }

  //@}


  /** @name Access */
  //        ======
  //@{

  /**
   * @brief Get copy of x derivatives image.
   */
  inline FloatImage dxImg() const;

  /**
   * @brief Get image of x derivatives.
   */
  inline const FloatImage& accessDxImg() const;

  /**
   * @brief Get copy of y derivatives image.
   */
  inline FloatImage dyImg() const;

  /**
   * @brief Get copy of y derivatives image.
   */
  inline const FloatImage& accessDyImg() const;

  /**
   * @brief Get x derivative value of a pixel.
   * @param aX  X coordinate (column index) of the pixel
   * @param aY  Y coordinate (row index) of the pixel
   */
  inline float dxPixel(int aX, int aY) const;

  /**
   * @brief Get y derivative value of a pixel.
   * @param aX  X coordinate (column index) of the pixel
   * @param aY  Y coordinate (row index) of the pixel
   */
  inline float dyPixel(int aX, int aY) const;

  /**
   * @brief Get the gradient module of a pixel.
   * @param aX  X coordinate (column index) of the pixel
   * @param aY  Y coordinate (row index) of the pixel
   */
  inline float gradientModule(int aX, int aY) const;

  //@}


  /** @name Operators */
  //        =========
  //@{

  /**
   * @brief Assignment (same as copy constructor).
   *
   * The current image is not supposed to initially have the same
   * dimensions as the given image.
   *
   * @param anImg  image to assign to the current image
   *
   * @warning Perform a <b>deep copy</b>: The x and y <b>pixel maps</b>
   * of the deritave images (qgar::AbstractGradientImage::_dxImg and
   * qgar::AbstractGradientImage::_dyImg) of the given image are
   * duplicated.
   */
  AbstractGradientImage& operator=(const AbstractGradientImage& anImg);

  //@}


  /** @name Copy the current image */
  //        ======================
  //@{
  /**
   * @brief Shallow copy: The x and y <b>pixel maps</b> of the deritave
   * images (qgar::AbstractGradientImage::_dxImg and
   * qgar::AbstractGradientImage::_dyImg) of the given image are
   * <b>not duplicated</b>.
   *
   * @see qgar::AbstractGradientImage::operator= and copy constructor.
   *
   * @warning When the copy is completed, the x and y <b>pixel maps</b>
   * of the deritave images of the new image share their memory space
   * with the pixel maps of the current image.
   */
  inline AbstractGradientImage shallowCopy();
  //@}

// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:


  //  ============================================
  /** @name Constructors
      Constructors belong to the protected section
      so that the class cannot be instantiated.
   */
  //  ============================================
  //@{

  /**
   * @brief Default constructor.
   */
  AbstractGradientImage();

  /**
   * @brief Copy constructor: Initialize from given gradient image.
   *
   * @param anImg image to be copied
   *
   * @warning Perform a <b>deep copy</b>: The x and y deritave
   * images of the given multi-layered image are duplicated.
   */
  AbstractGradientImage(const AbstractGradientImage& anImg);

  /**
   * @brief Initialize from given grey-level image.
   *
   * @param anImg image to be copied into the x and y
   *        derivative pixel maps
   */
  AbstractGradientImage(const GreyLevelImage& anImg);

  /**
   * @brief Initialize from given float image.
   * @param anImg image to be copied into the x and y
   *              derivative pixel maps
   */
  AbstractGradientImage(const FloatImage& anImg);

  /**
   * @brief Initialize from given double image.
   *
   * @param anImg image to be copied into the x and y
   *              derivative pixel maps
   */
  AbstractGradientImage(const DoubleImage& anImg);

  /**
   * @brief Initialize using given width and height.
   *
   * @param aWidth       width of the image
   * @param aHeight      height of the image
   */
  AbstractGradientImage(int aWidth, int aHeight);

  /**
   * @brief Initialize from all data.
   *
   * @param aWidth   width of the image
   * @param aHeight  height of the image
   * @param aDxImg   image of X derivatives
   * @param aDyImg   image of Y derivatives
   */
  AbstractGradientImage(int aWidth,
			int aHeight,
			FloatImage aDxImg,
			FloatImage aDyImg);

  //@}


  /** @name Representation of a gradient image */
  //        ==================================
  //@{

  /**
   * @brief Image of x derivatives.
   */
  FloatImage _dxImg;
  /**
   * @brief Image of y derivatives.
   */
  FloatImage _dyImg;

  //@}

// -------------------------------------------------------------------
}; // class AbstractGradientImage




// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// I N L I N E   F U N C T I O N S   I M P L E M E N T A T I O N 
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// ======
// ACCESS
// ======


// GET COPY OF X DERIVATIVES IMAGE

inline FloatImage
AbstractGradientImage::dxImg() const
{
  return _dxImg;
}


// GET X DERIVATIVES IMAGE

inline const FloatImage&
AbstractGradientImage::accessDxImg() const
{
  return _dxImg;
}


// GET COPY OF Y DERIVATIVES IMAGE

inline FloatImage
AbstractGradientImage::dyImg() const
{
  return _dyImg;
}


// GET Y DERIVATIVES IMAGE

inline const FloatImage&
AbstractGradientImage::accessDyImg() const
{
  return _dyImg;
}


// GET X DERIVATIVE VALUE OF A PIXEL

inline float
AbstractGradientImage::dxPixel(int aX, int aY) const
{
  return _dxImg.pixel(aX, aY);
}


// GET Y DERIVATIVE VALUE OF A PIXEL

inline float
AbstractGradientImage::dyPixel(int aX, int aY) const
{
  return _dyImg.pixel(aX, aY);
}


// GET THE GRADIENT MODULE OF A PIXEL

inline float
AbstractGradientImage::gradientModule(int aX, int aY) const
{
  return (float)
    hypot((double) dxPixel(aX,aY), (double) dyPixel(aX,aY));
}


// ====
// COPY
// ====


// SHALLOW COPY: THE X AND Y PIXEL MAPS OF THE DERITAVE IMAGES
// OF THE CURRENT IMAGE ARE NOT DUPLICATED

inline AbstractGradientImage
AbstractGradientImage::shallowCopy()
{
  return AbstractGradientImage(_width,
			       _height,
			       _dxImg.shallowCopy(),
			       _dyImg.shallowCopy());
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


}  // namespace qgar 


#endif /* __ABSTRACTGRADIENTIMAGE_H_INCLUDED__ */
