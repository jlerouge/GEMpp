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


#ifndef __CONTRASTENHANCEDIMAGE_H_INCLUDED__
#define __CONTRASTENHANCEDIMAGE_H_INCLUDED__


/**
 * @file   ContrastEnhancedImage.h
 * @brief  Header file of class qgar::ContrastEnhancedImage.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   July 3, 2003  17:08
 * @since  Qgar 1.0
 */

// For RCS/CVS use: Do not delete
/* $Id: ContrastEnhancedImage.h,v 1.13 2006/03/30 12:49:39 masini Exp $ */



// QGAR
#include "GenImage.h"
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
 * @class ContrastEnhancedImage ContrastEnhancedImage.h "qgarlib/ContrastEnhancedImage.h"
 *
 * @brief Morphologically contrast enhanced image.
 *
 * A point of such an image has the value of the dilation if its value
 * is closer to the dilated image than to the eroded image at that
 * point, and the value of the erosion in the other case.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   July 3, 2003  17:08
 * @since  Qgar 1.0
 */
class ContrastEnhancedImage

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
   * @brief Type of the elements stored in the pixel map.
   */
  typedef GreyLevelImage::value_type value_type;

  /**
   * @brief Reference to qgar::GreyLevelImage::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::GreyLevelImage::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::GreyLevelImage::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::GreyLevelImage::value_type.
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
   *
   * @param anImg      a grey-level image
   * @param aMaskSize  size of the square mask to be used
   *
   * @exception qgar::QgarErrorDomain  mask size too large for image
   */
  ContrastEnhancedImage(GreyLevelImage& anImg,
			unsigned int aMaskSize = 1)
   ;

  //@}

// -------------------------------------------------------------------
}; // class ContrastEnhancedImage


} // namespace qgar 

#endif /* __CONTRASTENHANCEDIMAGE_H_INCLUDED__ */
