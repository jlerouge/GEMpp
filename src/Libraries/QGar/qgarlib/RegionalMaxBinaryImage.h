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


#ifndef __REGIONALMAXBINARYIMAGE_H_INCLUDED__
#define __REGIONALMAXBINARYIMAGE_H_INCLUDED__


/**
 * @file RegionalMaxBinaryImage.h
 *
 * @brief Header file of class qgar::RegionalMaxBinaryImage.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date   August 12, 2002  17:16
 * @since  Qgar 2.0
 */



// For RCS/CVS use: Do not delete
/* $Id: RegionalMaxBinaryImage.h,v 1.13 2006/03/31 09:32:18 gerald Exp $ */



// QGAR
#include "ErodedBinaryImage.h"
namespace qgar
{
  // Avoid #include's when not necessary
  class QgarErrorDomain;
}



namespace qgar
{


/**
 * @ingroup IMGPROC_MORPH
 *
 * @class RegionalMaxBinaryImage RegionalMaxBinaryImage.h "qgarlib/RegionalMaxBinaryImage.h"
 *
 * @brief Regional maxima of given image
 * 
 * <b>RMAX(f) = f - R(f,E(f))</b>, where
 * <b>f</b> is the given image, 
 * <b>E</b> its erosion, and
 * <b>R(a,b)</b> the reconstruction by dilatation of <b>b</b> using <b>a</b>.
 * 
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date   August 12, 2002  17:16
 * @since  Qgar 2.0
 */
class RegionalMaxBinaryImage

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
   * @brief Reference to qgar::RegionalMaxBinaryImage::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::RegionalMaxBinaryImage::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::RegionalMaxBinaryImage::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::RegionalMaxBinaryImage::value_type.
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
   * @brief Construct in given image.
   *
   * The maxima can be found by considering the algebraic difference
   * between img and the reconstruction of img erosion with img itself
   * as a mask.
   *
   * @param anImg image in which to extract maxima
   */
  explicit RegionalMaxBinaryImage(BinaryImage& anImg);

  //@}


  /** @name Transformation */
  //        ==============
  //@{

  /**
   * @brief Construct in given image.
   *
   * static method to avoid copy of <b>img</b> when used by other classes.
   * Use it when you do not need to preserve the original image.
   *
   * @param anImg  image in which to extract maxima
   */
  static void perform(BinaryImage* anImg);

  //@}

// -------------------------------------------------------------------
}; // class RegionalMaxBinaryImage

} // namespace qgar


#endif /* __REGIONALMAXBINARYIMAGE_H_INCLUDED__ */
