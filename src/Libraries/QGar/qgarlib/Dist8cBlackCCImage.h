/*---------------------------------------------------------------------*
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


#ifndef __DIST8CBLACKCCIMAGE_H_INCLUDED__
#define __DIST8CBLACKCCIMAGE_H_INCLUDED__


/**
 * @file Dist8cBlackCCImage.h
 *
 * @brief Header file of class qgar::Dist8cBlackCCImage.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date   August 14, 2002  15:04
 * @since  Qgar 2.0
 */


// For RCS/CVS use: Do not delete
/* $Id: Dist8cBlackCCImage.h,v 1.3 2006/07/04 13:37:40 masini Exp $ */


// QGAR
#include "GenImage.h"



namespace qgar
{

/**
 * @ingroup IMGPROC_DIST
 *
 * @class Dist8cBlackCCImage Dist8cBlackCCImage.h "qgarlib/Dist8cBlackCCImage.h"
 *
 * @brief 8-connected distance transformation of a binary image,
 * for black components only.
 *
 * @warning The result is stored in a grey-level image:
 * As grey-level images are coded with <b>256</b> levels, images
 * containing black components bigger than <b>510*510</b> are not
 * correctly supported.
 *
 * @todo
 * - In constructor code, use pixel map pointers instead of nested
 *   loops (for iCnt and for jCnt) to get less tests (and thus save time).
 * - The constructor performs a copy of the given image: If it is a
 *   deep copy, is it really necessary?
 * - Given binary image <b>must</b> exclusively contain 0's and 1's.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date   August 14, 2002  15:04
 * @since  Qgar 2.0
 */
class Dist8cBlackCCImage

  : public GreyLevelImage

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
  typedef GreyLevelImage::value_type value_type;

  /**
   * @brief Reference to qgar::Dist8cBlackCCImage::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::Dist8cBlackCCImage::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::Dist8cBlackCCImage::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::Dist8cBlackCCImage::value_type.
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
   * @param anImg  a binary image
   */
  explicit Dist8cBlackCCImage(const BinaryImage& anImg);

  //@}

// -------------------------------------------------------------------
}; // class Dist8cBlackCCImage

} // namespace qgar


#endif /* __DIST8CBLACKCCIMAGE_H_INCLUDED__ */
