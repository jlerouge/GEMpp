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


#ifndef __DILATEDIMAGE_H_INCLUDED__
#define __DILATEDIMAGE_H_INCLUDED__


/**
 * @file DilatedImage.h
 *
 * @brief Header file of class qgar::DilatedImage.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date   August 5, 2002  17:39
 * @since  Qgar 2.0
 */



// For RCS/CVS use: Do not delete
/* $Id: DilatedImage.h,v 1.18 2006/07/04 13:37:39 masini Exp $ */



// QGAR
#include "GenImage.h"
#include "QgarErrorDomain.h"



namespace qgar
{

/**
 * @ingroup IMGPROC_MORPH
 *
 * @class DilatedImage DilatedImage.h "qgarlib/DilatedImage.h"
 *
 * @brief Dilate a grey-level image using morphological operators.
 * 
 * The 2D dilation is a composition of two linear dilations,
 * one vertical and the other horizontal, using a segment
 * whose length is \f$ (2 \times dilation_size) + 1 \f$.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date   August 5, 2002  17:39
 * @since  Qgar 2.0
 */
class DilatedImage

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
   * @brief Reference to qgar::DilatedImage::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::DilatedImage::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::DilatedImage::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::DilatedImage::value_type.
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
   * @brief Construct the dilation of a grey-level image.
   *
   * @param anImg     image to be dilated
   * @param aDilSize  dilation size
   *
   * @exception qgar::QgarErrorDomain  dilation size too large for image
   */
  DilatedImage(GreyLevelImage& anImg, unsigned int aDilSize = 1)
   ;

  //@}


  /** @name Dilation */
  //        ========
  //@{

  /**
   * @brief Perform a dilation on a given grey-level image. 
   *
   * <b>To be used to perform a dilation without preserving
   * the initial image.</b>
   *
   * @param anImg     image to be dilated
   * @param aDilSize  dilation size
   */
  static void perform(GreyLevelImage* anImg, unsigned int aDilSize = 1);

  //@}

// -------------------------------------------------------------------
}; // class DilatedImage


} // namespace qgar 


#endif /* __DILATEDIMAGE_H_INCLUDED__ */
