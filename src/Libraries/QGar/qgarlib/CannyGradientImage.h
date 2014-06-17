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


#ifndef __CANNYGRADIENTIMAGE_H_INCLUDED__
#define __CANNYGRADIENTIMAGE_H_INCLUDED__


/**
 * @file CannyGradientImage.h
 *
 * @brief Header file of class qgar::CannyGradientImage.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date   July 2, 2001  15:09
 * @since  Qgar 1.0
 */


// For RCS/CVS use: Do not delete
/* $Id: CannyGradientImage.h,v 1.13 2006/07/04 15:10:15 masini Exp $ */



// QGAR
#include "AbstractGradientImage.h"
#include "GenImage.h"



namespace qgar
{

/**
 * @ingroup IMGPROC_GRAD
 *
 * @class CannyGradientImage CannyGradientImage.h "qgarlib/CannyGradientImage.h"
 *
 * @brief Canny Gradient image.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date   July 2, 2001  15:09
 * @since  Qgar 1.0
 */
class CannyGradientImage

  : public AbstractGradientImage

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
  typedef AbstractGradientImage::value_type value_type;

  /**
   * @brief Reference to qgar::CannyGradientImage::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::CannyGradientImage::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::CannyGradientImage::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::CannyGradientImage::value_type.
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
  CannyGradientImage(const GreyLevelImage& anImg, double aSigma = 1.0);

  /**
   * @brief Construct from given float image.
   */
  CannyGradientImage(const FloatImage& anImg, double aSigma = 1.0);

  //@}

// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

  /** @name Auxiliaries */
  //        ===========
  //@{

  /**
   * @brief The effective construction of the Canny contour image.
   */
  void PRIVATE_CannyImage(double aSigma);

  //@}

// -------------------------------------------------------------------
}; // class CannyGradientImage


} // namespace qgar


#endif /* __CANNYGRADIENTIMAGE_H_INCLUDED__ */
