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


#ifndef __CLEANEDBINARYIMAGE_H_INCLUDED__
#define __CLEANEDBINARYIMAGE_H_INCLUDED__


/**
 * @file CleanedBinaryImage.h
 *
 * @brief Header file of class qgar::CleanedBinaryImage.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>,
 *         from previous work by Adlane Habed and Karl Tombre
 * @date   July 4, 2001  17:29
 * @since  Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: CleanedBinaryImage.h,v 1.12 2006/07/04 13:37:39 masini Exp $ */



// QGAR
#include "GenImage.h"



namespace qgar
{

/**
 * @ingroup IMGPROC_CONVOL
 *
 * @class CleanedBinaryImage CleanedBinaryImage.h "qgarlib/CleanedBinaryImage.h"
 *
 * @brief A binary image in which black and white components are cleaned
 * of one-pixel barbs and one-pixel holes.
 *
 * Cleaning operations:
 *
 * <ul>
 * <li>
 * Set center to <b>WHITE</b> in following cases:
@verbatim
B B B    B w w    w w w    w w B    w w w
w B w    B B w    w B w    w B B    w B w
w w w    B w w    B B B    w w B    w w w
@endverbatim
 * </li>
 * <li>
 * Set center to <b>BLACK</b> in following cases:
@verbatim
w w w    w B B    B B B    B B w    * B *
B w B    w w B    B w B    B w w    B w B
B B B    w B B    w w w    B B w    * B *
@endverbatim
 * </li>
 * </ul>
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>,
 *         from previous work by Adlane Habed and Karl Tombre
 * @date   July 4, 2001  17:29
 * @since  Qgar 2.1
 */
class CleanedBinaryImage

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
   * @brief Reference to qgar::CleanedBinaryImage::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::CleanedBinaryImage::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::CleanedBinaryImage::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::CleanedBinaryImage::value_type.
   */
  typedef const value_type* const_pointer;

  //@}


// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  /** @name CONSTRUCTORS */
  //        ============
  //@{

  /**
   * @brief Construct from given binary image.
   *
   * @param aBinImg  a binary image
   */

  DLL_EXPORT explicit CleanedBinaryImage(const BinaryImage& aBinImg);

  //@}

// -------------------------------------------------------------------
}; // class CleanedBinaryImage

} // namespace qgar 


#endif /* __CLEANEDBINARYIMAGE_H_INCLUDED__ */
