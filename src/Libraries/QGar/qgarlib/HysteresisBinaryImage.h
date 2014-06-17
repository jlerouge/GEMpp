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


#ifndef __HYSTERESISBINARYIMAGE_H_INCLUDED__
#define __HYSTERESISBINARYIMAGE_H_INCLUDED__


/**
 * @file HysteresisBinaryImage.h
 *
 * @brief Header file of class qgar::HysteresisBinaryImage.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date   July 3, 2001  16:24
 * @since  Qgar 1.0
 */



// For RCS/CVS use: Do not delete
/* $Id: HysteresisBinaryImage.h,v 1.2 2006/07/04 13:37:42 masini Exp $ */



// QGAR
#include "GenImage.h"
namespace qgar
{
  // Avoid #include's when not necessary
  class GradientLocalMaxImage;
}



namespace qgar
{


/**
 * @ingroup IMGPROC_BIN
 *
 * @class HysteresisBinaryImage HysteresisBinaryImage.h "qgarlib/HysteresisBinaryImage.h"
 *
 * @brief Binary image created from the local maxima of a gradient
 *        using a hysteresis thresholding.
 *
 * The implementation of the hysteresis algorithm is strongly inspired
 * by the work by Simon A.J. Winder in the IMG* Image Processing Toolset
 * and C Library.
 * See the copyright notice in file <i>HysteresisBinaryImage.cpp</i>.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date   July 3, 2001  16:24
 * @since  Qgar 1.0
 */
class HysteresisBinaryImage

  : public BinaryImage

{
// -------------------------------------------------------------------
// T Y P E   D E F I N I T I O N S
// -------------------------------------------------------------------
public:

  /** @name Types */
  //        =====
  //@{

  /**
   * @brief Type of the elements stored in the pixel map.
   */
  typedef BinaryImage::value_type value_type;

  /**
   * @brief Reference to qgar::HysteresisBinaryImage::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::HysteresisBinaryImage::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::HysteresisBinaryImage::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::HysteresisBinaryImage::value_type.
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
   * @brief Construct a binary image from the local maxima
   * of a gradient using a hysteresis thresholding
   *
   * @param aGradImg    image of gradient local maxima
   * @param aLowThrsl   low threshold
   * @param aHighThrsl  high threshold
   *
   * @warning The value of a pixel of such a binary image
   * is either <b>0</b> or <b>1</b>.
   *
   * @todo
   * - Look at lines like 'val == 0.0', where 'val' is a float!
   * - Use pointers to pixel maps instead of nested loops
   *   to run through images.
   */
  HysteresisBinaryImage(const GradientLocalMaxImage& aGradImg,
			unsigned int aLowThrsl,
			unsigned int aHighThrsl);

  //@}

// -------------------------------------------------------------------
}; // class HysteresisBinaryImage


} // namespace qgar


#endif /* __HYSTERESISBINARYIMAGE_H_INCLUDED__ */
