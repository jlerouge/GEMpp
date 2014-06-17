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


#ifndef __GEODESICRECEROBINARYIMAGE_H_INCLUDED__
#define __GEODESICRECEROBINARYIMAGE_H_INCLUDED__


/**
 * @file GeodesicRecEroBinaryImage.h
 *
 * @brief Header file of class qgar::GeodesicRecEroBinaryImage.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date   August 13, 2002  14:57
 * @since  Qgar 2.0
 */



// For RCS/CVS use: Do not delete
/* $Id: GeodesicRecEroBinaryImage.h,v 1.16 2006/07/04 13:37:42 masini Exp $ */



// QGAR
#include "GenImage.h"
#include "QgarErrorDomain.h"



namespace qgar
{

/**
 * @ingroup IMGPROC_MORPH
 *
 * @class GeodesicRecEroBinaryImage GeodesicRecEroBinaryImage.h "qgarlib/GeodesicRecEroBinaryImage.h"
 *
 * @brief Complete geodesic reconstruction of a binary image by erosion.
 * 
 * Implementation based on a queue-based algorithm from L. Vincent
 * [<a href="Bibliography.html#Vincent-1993">Vincent-1993</a>].
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date   August 6, 2002  17:20
 * @since  Qgar 2.0
 */
class GeodesicRecEroBinaryImage

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
   * @brief Reference to qgar::GeodesicRecEroBinaryImage::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::GeodesicRecEroBinaryImage::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::GeodesicRecEroBinaryImage::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::GeodesicRecEroBinaryImage::value_type.
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
   * @brief Construct in given result image from given marker image.
   *
   * The geodesic reconstruction first collects the boundaries of the
   * marker image (in raster order first, then in raster reverse order),
   * and then propagates them in the relevant connected components
   * of the resulting image.
   *
   * @param aMarkImg  image to be reconstructed
   * @param aResImg   result image
   *
   * @exception qgar::QgarErrorDomain
   *   marker image size does not match result image size
   */
  GeodesicRecEroBinaryImage(BinaryImage& aMarkImg, BinaryImage& aResImg)
   ;

  //@}


  /** @name Geodesic reconstruction */
  //        =======================
  //@{

  /**
   * @brief Perform a geodesic reconstruction in given result image
   *        from given marker image.
   *
   * <b>To be used to perform a geodesic reconstruction
   * without creating any image.</b>
   *
   * @param aMarkImg  pointer to image to be reconstructed
   * @param aResImg   pointer to result image
   */
  static void perform(BinaryImage* aMarkImg, BinaryImage* aResImg);

  //@}

// -------------------------------------------------------------------
}; // class GeodesicRecEroBinaryImage


} // namespace qgar


#endif /* __GEODESICRECEROBINARYIMAGE_H_INCLUDED__ */
