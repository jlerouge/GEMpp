/*---------------------------------------------------------------------+
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


#ifndef __DIST34IMAGE_H_INCLUDED__
#define __DIST34IMAGE_H_INCLUDED__


/**
 * @file Dist34Image.h
 *
 * @brief Header file of class qgar::Dist34Image.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Perrin & Kheder">Julien Perrin & Sami Kheder</a>
 * @date   March 24,  2003  16:16
 * @since  Qgar 2.1.1
 */

// For RCS/CVS use: Do not delete
/* $Id: Dist34Image.h,v 1.3 2006/07/04 13:37:40 masini Exp $ */

#include <limits.h>
// QGAR
#include "GenImage.h"



namespace qgar
{

/** 
 * @ingroup IMGPROC_DIST
 *
 * @class Dist34Image Dist34Image.h "qgarlib/Dist34Image.h"
 *
 * @brief Distance transformation of all (black and white) components
 *   of a binary image, using 3-4 Chamfer distance
 *
 * The result is stored in an image of <b>integer</b> numbers:
 * For a given pixel, the maximum value of the distance is the maximum
 * value of an <b>integer</b> number.
 *
 * @warning
 * The content of the rows and columns contiguous to the borders
 * of the resulting image is not relevant
 * (all these pixels have a value equal to <b>INT_MAX</b>)
 *
 * @todo
 * - In the constructor code, use pixel map pointers instead of nested
 *   loops (for iCnt and for jCnt) to get less tests (and thus save time).
 * - The constructor performs a copy of the given image: If it is a
 *   deep copy, is it really necessary?
 * - The way the distance is computed is rather weird:
 *   See class qgar::Dist8cBlackCCImage for example!
 * - Given binary image <b>must</b> exclusively contain 0's and 1's.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Perrin & Kheder">Julien Perrin & Sami Kheder</a>
 * @date   March 24,  2003  16:16
 * @since  Qgar 2.1.1
 */
class Dist34Image

  : public IntImage

{
// -------------------------------------------------------------------
// T Y P E   D E F I N I T I O N S
// -------------------------------------------------------------------
public:


  /** @name Types */
  //        =====
  //@{

  /**
   * @brief Type of the elements stored in the marker map.
   */
  typedef IntImage::value_type value_type;

  /**
   * @brief Reference to qgar::Dist34Image::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::Dist34Image::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::Dist34Image::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::Dist34Image::value_type.
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
   * @brief Construct from given binary image.
   *
   * @param anImg a binary image
   */
  explicit Dist34Image(const BinaryImage& anImg);

  //@}
  
// -------------------------------------------------------------------
}; // class Dist34Image


} // namespace qgar


#endif /* __DIST34IMAGE_H_INCLUDED__ */
