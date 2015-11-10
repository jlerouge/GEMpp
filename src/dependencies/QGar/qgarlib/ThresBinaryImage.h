/*---------------------------------------------------------------------*
 | Library QgarLib, graphics analysis and recognition                  |
 | Copyright (C) 2005  Qgar Project, LORIA                             |
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
 | http://www.gnu.org/licenses/lgpl.html for the terms of the license. |
 | To receive a paper copy, write to the Free Software Foundation,     |
 | Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.       |
 |                                                                     |
 | Contact Project Qgar for any information:                           |
 |   LORIA - équipe Qgar                                               |
 |   B.P. 239, 54506 Vandoeuvre-lès-Nancy Cedex, France                |
 |   email: qgar-contact@loria.fr                                      |
 |   http://www.qgar.org/                                              |
 *---------------------------------------------------------------------*/


#ifndef __THRESBINARYIMAGE_H_INCLUDED__
#define __THRESBINARYIMAGE_H_INCLUDED__


/**
 * @file   ThresBinaryImage.h
 * @brief  Header file of class qgar::ThresBinaryImage.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   July 4, 2005  09:23
 * @since  Qgar 2.2
 */


// For RCS/CVS use: Do not delete
/* $Id: ThresBinaryImage.h,v 1.1 2005/10/14 17:05:48 masini Exp $ */



// QGAR
#include "GenImage.h"



namespace qgar
{

/**
 * @ingroup IMGPROC_BIN
 *
 * @class ThresBinaryImage ThresBinaryImage.h "qgarlib/ThresBinaryImage.h"
 *
 * @brief Elementary binarization, using a constant threshold.
 *
 * All pixels above the given threshold are set to <b>white</b>,
 * pixels below the threshold are set to <b>black</b>.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   July 4, 2005  09:23
 * @since  Qgar 2.2
 */
class ThresBinaryImage

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
   * @brief Type of the elements stored in the pixmap.
   */
  typedef BinaryImage::value_type value_type;

  /**
   * @brief Reference to qgar::ThresBinaryImage::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::ThresBinaryImage::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::ThresBinaryImage::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::ThresBinaryImage::value_type.
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
 * @brief Default constructor.
 *
 * @param anImg    the greylevel input image
 * @param aThres   the threshold value
 */
  ThresBinaryImage(const GreyLevelImage& anImg, int aThres);

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Virtual destructor.
 */
  virtual ~ThresBinaryImage();

//@}

// -------------------------------------------------------------------
}; // class ThresBinaryImage


} // namespace qgar





// HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// H  E  L  P  E  R  S
// HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH


namespace qgar
{


/** @name Binarization helper functions */
//        =============================
//@{

/**
 * @ingroup GLOB_HELPER
 *
 * @brief Returns a binary image, result of the binarization
 *   of the given grey-level image, using a constant threshold.
 *
 * @param anImg   grey-level image
 * @param aThres  constant binarization threshold
 */
ThresBinaryImage
qgThresBinarization(const GreyLevelImage& anImg, int aThres);

//@}


} // namespace qgar 


// HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH


#endif /* __THRESBINARYIMAGE_H_INCLUDED__ */
