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


#ifndef __DIST34BLACKCCIMAGE_H_INCLUDED__
#define __DIST34BLACKCCIMAGE_H_INCLUDED__


/**
 * @file Dist34BlackCCImage.h
 *
 * @brief Header file of class qgar::Dist34BlackCCImage
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date   July 3, 2001  15:03
 * @since  Qgar 1.0
 */

// For RCS/CVS use: Do not delete
/* $Id: Dist34BlackCCImage.h,v 1.9 2007/02/14 17:34:04 masini Exp $ */



// QGAR
#include "GenImage.h"



namespace qgar
{

/**
 * @ingroup IMGPROC_DIST
 *
 * @class DistanceTransform34Image Dist34BlackCCImage.h "qgarlib/Dist34BlackCCImage.h"
 *
 *
 * @brief Distance transformation of a binary image, using 3-4 Chamfer
 * distance, for black components only.
 *
 * The result is stored in an <b>integer</b> image.
 *
 * @warning
 * - Only black components (i.e. having pixels equal to <b>QGE_BW_BLACK</b>)
 *   of the given binary image are processed.
 * - For a given pixel, the maximum value of the distance is supposed
 *   to be around <b>127</b>.
 * - To compute the distance transform on all the components,
 *   see class qgar::Dist34Image.
 *
 *
 * @todo The warning section has to be corrected. As the pixels of such
 * an image now are integer values, the maximum value of the distance
 * is supposed to be more than <b>127</b>.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date   July 3, 2001  15:03
 * @since  Qgar 1.0
 */
class Dist34BlackCCImage

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
   * @brief Type of the elements stored in the distance image.
   */
  typedef IntImage::value_type value_type;

  /**
   * @brief Reference to qgar::Dist34BlackCCImage::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::Dist34BlackCCImage::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::Dist34BlackCCImage::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::Dist34BlackCCImage::value_type.
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
  DLL_EXPORT explicit Dist34BlackCCImage(const BinaryImage& anImg);

  /**
   * @brief Copy constructor.
   *
   * Perform a <b>deep copy</b>:
   * the pixel map of the source image is duplicated.
   *
   * @param anImg  a (3,4)-distance image
   */
  Dist34BlackCCImage(const Dist34BlackCCImage& anImg);

  //@}

// -------------------------------------------------------------------
}; // class Dist34BlackCCImage

} // namespace qgar 


#endif /* __DIST34BLACKCCIMAGE_H_INCLUDED__ */
