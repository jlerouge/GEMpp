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


#ifndef __CLOSEIMAGE_H_INCLUDED__
#define __CLOSEIMAGE_H_INCLUDED__


/**
 * @file   CloseImage.h
 * @brief  Header file of class qgar::CloseImage.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date   July 26, 2002  11:45
 * @since  Qgar 2.0
 */


// For RCS/CVS use: Do not delete
/* $Id: CloseImage.h,v 1.17 2006/03/31 09:32:15 gerald Exp $ */


// QGAR
#include "GenImage.h"
#include "QgarErrorDomain.h"



namespace qgar
{

/**
 * @ingroup IMGPROC_MORPH
 *
 * @class CloseImage CloseImage.h "qgarlib/CloseImage.h"
 *
 * @brief Close a greylevel image using morphological operators.
 * 
 * The closing structural element is a square.
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date   July 26, 2002  11:45
 * @since  Qgar 2.0
 */
class CloseImage

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
   * @brief Reference to qgar::CloseImage::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::CloseImage::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::CloseImage::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::CloseImage::value_type.
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
   * @brief Construct the closing of a grey-level image.
   *
   * @param anImg         image to be closed
   * @param aClosingSize  closing size
   * 
   * @exception qgar::QgarErrorDomain  closing size too large for image
   */
  explicit CloseImage(GreyLevelImage& anImg,
		      unsigned int aClosingSize = 1)

   ;
  //@}
  
  /** @name Closing */
  //        =======
  //@{

  /**
   * @brief Perform a closing of a given grey-level image.
   *
   * <b>To be used to perform a closing without preserving
   * the initial image.</b>
   *
   * @param anImg         image to be closed
   * @param aClosingSize  closing size
   */
  static void perform(GreyLevelImage* anImg,
		      unsigned int aClosingSize = 1);

  //@}

// -------------------------------------------------------------------
}; // class CloseImage


} // namespace qgar


#endif /* __CLOSEIMAGE_H_INCLUDED__ */
