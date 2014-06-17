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


#ifndef __GRADIENTMODULEIMAGE_H_INCLUDED__
#define __GRADIENTMODULEIMAGE_H_INCLUDED__


/**
 * @file GradientModuleImage.h
 *
 * @brief Header file of class qgar::GradientModuleImage.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date   July 3,  2001  15:21
 * @since  Qgar 1.0
 */



// For RCS/CVS use: Do not delete
/* $Id: GradientModuleImage.h,v 1.13 2006/07/04 13:37:42 masini Exp $ */



// QGAR
#include "GenImage.h"
namespace qgar
{
  // Avoid #include's when not necessary
  class AbstractGradientImage;
}



namespace qgar
{


/** 
 * @ingroup IMGPROC_GRAD
 *
 * @class GradientModuleImage GradientModuleImage.h "qgarlib/GradientModuleImage.h"
 *
 * @brief Module of the Gradient of an image.
 */
class GradientModuleImage

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
   * @brief Reference to qgar::GenImage::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::GenImage::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::GenImage::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::GenImage::value_type.
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
   * @brief Construct from given gradient image.
   *
   * @param aGradImg a Gradient image
   */
  explicit GradientModuleImage(AbstractGradientImage& aGradImg);

  //@}

// -------------------------------------------------------------------
}; // class GradientModuleImage


} // namespace qgar 


#endif /* __GRADIENTMODULEIMAGE_H_INCLUDED__ */
