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


#ifndef __ULTIMATEERODEDBINARYIMAGE_H_INCLUDED__
#define __ULTIMATEERODEDBINARYIMAGE_H_INCLUDED__


/**
 * @file   UltimateErodedBinaryImage.h
 * @brief  Header file of class qgar::UltimateErodedBinaryImage.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date   August 13, 2002  18:04
 * @since  Qgar 2.0
 */



// For RCS/CVS use: Do not delete
/* $Id: UltimateErodedBinaryImage.h,v 1.11 2005/10/14 17:05:48 masini Exp $ */



// QGAR
#include "GenImage.h"



namespace qgar
{


/**
 * @ingroup IMGPROC_MORPH
 *
 * @class UltimateErodedBinaryImage UltimateErodedBinaryImage.h "qgarlib/UltimateErodedBinaryImage.h"
 *
 * @brief Compute the ultimate eroded set of a binary image
 * 
 * <b>ULT(X) = RMAX[D(X)]</b>, where
 * <b>X</b> is the given image,
 * <b>RMAX</b> its regional maxima, and
 * <b>D</b> a distance function.
 *
 * @warning Due to the distance transformation when performing the
 * erosion, images containing black components bigger than <b>510*510</b>
 * are not correctly supported.
 * See class qgar::Dist8cBlackCCImage for more details.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date   August 13, 2002  18:04
 * @since  Qgar 2.0
 */
class UltimateErodedBinaryImage

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
   * @brief Reference to qgar::UltimateErodedBinaryImage::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::UltimateErodedBinaryImage::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::UltimateErodedBinaryImage::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::UltimateErodedBinaryImage::value_type.
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
   * @brief Construct from a binary image.
   *
   * @param img image to be eroded
   *
   */
  UltimateErodedBinaryImage(BinaryImage& img);

  //@}


  /** @name Transformation */
  //        ==============
  //@{

  /**
   * @brief Perform an ultimate erosion on a given binary image.
   *
   * <b>To be used to perform an erosion without preserving
   * the initial image.</b>
   *
   * @param img image to be eroded
   */
  static void perform(BinaryImage* img);

  //@}

// -------------------------------------------------------------------
}; // class UltimateErodedBinaryImage


} // namespace qgar


#endif /* __ULTIMATEERODEDBINARYIMAGE_H_INCLUDED__ */
