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


#ifndef __OPENBINARYIMAGE_H_INCLUDED__
#define __OPENBINARYIMAGE_H_INCLUDED__


/**
 * @file   OpenBinaryImage.h
 * @brief  Header file of class qgar::OpenBinaryImage.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date   July 18, 2002  15:48
 * @since  Qgar 2.0
 */



// For RCS/CVS use: Do not delete
/* $Id: OpenBinaryImage.h,v 1.14 2006/03/30 12:49:40 masini Exp $ */



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
 * @class OpenBinaryImage OpenBinaryImage.h "qgarlib/OpenBinaryImage.h"
 *
 * @brief Open a binary image using morphological operators.
 * 
 * The structural element is a square of size
 * <b>(2 * anOpenSize) + 1</b>.
 * 
 * @todo Allow the use of other structural elements, like disks, crosses...
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date   July 18, 2002  15:48
 * @since  Qgar 2.0
 */
class OpenBinaryImage

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
   * @brief Reference to qgar::OpenBinaryImage::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::OpenBinaryImage::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::OpenBinaryImage::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::OpenBinaryImage::value_type.
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
   * @param anImg       image to be opened
   * @param anOpenSize  opening size
   * 
   * @exception qgar::QgarErrorDomain  opening size too large for image
   */
  OpenBinaryImage(const BinaryImage& anImg, unsigned int anOpenSize = 1)
   ;

  //@}


  /** @name Opening */
  //        =======
  //@{

  /**
   * @brief Perform an opening on a given binary image.
   *
   * <b>To be used to perform an opening without preserving
   * the initial image.</b>
   *
   * @param anImg       pointer to the image to be opened
   * @param anOpenSize  opening size
   */
  static void perform(BinaryImage* anImg, unsigned int anOpenSize = 1);

  //@}

// -------------------------------------------------------------------
}; // class OpenBinaryImage


} // namespace qgar


#endif /* __OPENBINARYIMAGE_H_INCLUDED__ */
