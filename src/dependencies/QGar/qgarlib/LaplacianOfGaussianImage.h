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


#ifndef __LAPLACIANOFGAUSSIANIMAGE_H_INCLUDED__
#define __LAPLACIANOFGAUSSIANIMAGE_H_INCLUDED__


/**
 * @file LaplacianOfGaussianImage.h
 *
 * @brief Header file of class qgar::LaplacianOfGaussianImage.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date   July 3, 2001  14:56
 * @since  Qgar 1.0
 */


// For RCS/CVS use: Do not delete
/* $Id: LaplacianOfGaussianImage.h,v 1.17 2006/07/04 15:10:15 masini Exp $ */



// QGAR
#include "GenImage.h"



namespace qgar
{


/**
 * @ingroup IMGPROC_GRAD
 *
 * @class LaplacianOfGaussianImage LaplacianOfGaussianImage.h "qgarlib/LaplacianOfGaussianImage.h"
 *
 * @brief Laplacian of Gaussian image.
 *
 * @todo
 * - Check the correctness of the constructor from a float image.
 *   It converts a float image to a greylevel image.
 * - function qgar::LaplacianOfGaussianImage::PRIVATEbuildLOGImage
 *   returns a float image, which is then duplicated in constructors!
 *
 *
 * @author  <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date    July 3, 2001  14:56
 * @since   Qgar 1.0
 */
class LaplacianOfGaussianImage

  : public FloatImage

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
  typedef FloatImage::value_type value_type;

  /**
   * @brief Reference to qgar::LaplacianOfGaussianImage::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::LaplacianOfGaussianImage::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::LaplacianOfGaussianImage::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::LaplacianOfGaussianImage::value_type.
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
   * @brief Construct from given grey-level image.
   */
  explicit LaplacianOfGaussianImage(const GreyLevelImage& img,
				    double sigma = 1.0);
  
  /**
   * @brief Construct from given float image.
   */
  explicit LaplacianOfGaussianImage(const FloatImage& img,
				    double sigma = 1.0) ;

  //@}


// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:


  /** @name Auxiliaries */
  //        ===========
  //@{

  /**
   * @brief The effective construction of the image.
   */
  static FloatImage PRIVATEbuildLOGImage(const GreyLevelImage& img,
					 double sigma);

  //@}


// -------------------------------------------------------------------
}; // class LaplacianOfGaussianImage


} // namespace qgar


#endif /* __LAPLACIANOFGAUSSIANIMAGE_H_INCLUDED__ */
