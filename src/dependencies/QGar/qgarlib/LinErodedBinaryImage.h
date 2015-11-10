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


#ifndef __LINERODEDBINARYIMAGE_H_INCLUDED__
#define __LINERODEDBINARYIMAGE_H_INCLUDED__


/**
 * @file LinErodedBinaryImage.h
 *
 * @brief Header file of class qgar::LinErodedBinaryImage.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date   August 5, 2002  16:08
 * @since  Qgar 2.0
 */



// For RCS/CVS use: Do not delete
/* $Id: LinErodedBinaryImage.h,v 1.19 2006/07/04 13:37:43 masini Exp $ */



// QGAR
#include "GenImage.h"
#include "QgarErrorDomain.h"



namespace qgar
{

/**
 * @ingroup IMGPROC_MORPH
 *
 * @class LinErodedBinaryImage LinErodedBinaryImage.h "qgarlib/LinErodedBinaryImage.h"
 *
 * @brief Binary image linearly eroded, using a segment.
 *
 * The length of the segment is <b>2 * aDilSize + 1</b>.
 * The algorithm is very simple: Two pointers follow the current line,
 * at a <b>aDilSize</b> distance from each other. When the first pointer
 * meets a zero pixel or when the second pointer meets a non-zero pixel,
 * the next <b>aDilSize</b> pixels are set to zero.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date   August 5, 2002  16:08
 * @since  Qgar 2.0
 */
class LinErodedBinaryImage

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
   * @brief Reference to qgar::LinErodedBinaryImage::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::LinErodedBinaryImage::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::LinErodedBinaryImage::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::LinErodedBinaryImage::value_type.
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
   * Orientation qgar::QGE_ORIENTATION_ALL corresponds to the
   * maximum of the 4 possible erosions.
   *
   * @param anImg      image to be eroded
   * @param anOrient   erosion orientation
   *                   (default qgar::QGE_ORIENTATION_HOR)
   * @param anEroSize  erosion size (default <b>1</b>)
   *
   * @exception qgar::QgarErrorDomain  erosion size too large for image
   */
  explicit LinErodedBinaryImage(const BinaryImage& anImg,
				QGEorientation anOrient = QGE_ORIENTATION_HOR,
				unsigned int anEroSize = 1)
   ;

  //@}


  /** @name Linear erosion */
  //        ==============
  //@{

  /**
   * @brief Perform a linear erosion on a given binary image.
   *
   * <b>To be used to perform a linear erosion without preserving
   * the initial image.</b>
   *
   * @param  anImg      image to be eroded
   * @param  anOrient   erosion orientation
   * @param  anEroSize  erosion size (default <b>1</b>)
   */
  static void perform(BinaryImage* anImg,
		      QGEorientation anOrient,
		      unsigned int anEroSize = 1);

  //@}

// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

  /** @name Oriented erosions */
  //        =================
  //@{

  /**
   * @brief Horizontal erosion.
   *
   * @param anImg      image to be eroded
   * @param anEroSize  erosion size
   *
   * @exception qgar::QgarErrorDomain  erosion size too large for image
   */
  static void erodeHor(BinaryImage* anImg, unsigned int anEroSize)
   ;

  /**
   * @brief Vertical erosion.
   *
   * @param anImg      image to be eroded
   * @param anEroSize  erosion size
   *
   * @exception qgar::QgarErrorDomain  erosion size too large for image
   */
  static void erodeVer(BinaryImage* anImg, unsigned int anEroSize)
   ;

  /**
   * @brief NE-SW erosion.
   *
   * @param anImg      image to be eroded
   * @param anEroSize  erosion size
   *
   * @exception qgar::QgarErrorDomain  erosion size too large for image
   */
  static void erodePdiag(BinaryImage* anImg, unsigned int anEroSize)
   ;
  
  /**
   * @brief NW-SE erosion.
   *
   * @param anImg      image to be eroded
   * @param anEroSize  erosion size
   *
   * @exception qgar::QgarErrorDomain  erosion size too large for image
   */
  static void erodeNdiag(BinaryImage* anImg, unsigned int anEroSize)
   ;

  /**
   * @brief Maximum of the 4 erosions.
   *
   * @param anImg      image to be eroded
   * @param anEroSize  erosion size
   *
   * @exception qgar::QgarErrorDomain  erosion size too large for image
   */
  static void erodeAll(BinaryImage* anImg, unsigned int anEroSize)
   ;

  //@}

// -------------------------------------------------------------------
}; // class LinErodedBinaryImage


} // namespace qgar


#endif /* __LINERODEDBINARYIMAGE_H_INCLUDED__ */
