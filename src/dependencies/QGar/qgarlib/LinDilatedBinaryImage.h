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


#ifndef __LINDILATEDBINARYIMAGE_H_INCLUDED__
#define __LINDILATEDBINARYIMAGE_H_INCLUDED__


/**
 * @file LinDilatedBinaryImage.h
 *
 * @brief Header file of class qgar::LinDilatedBinaryImage.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date   August 5, 2002  16:41
 * @since  Qgar 2.0
 */



// For RCS/CVS use: Do not delete
/* $Id: LinDilatedBinaryImage.h,v 1.18 2006/07/04 13:37:43 masini Exp $ */



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
 * @class LinDilatedBinaryImage LinDilatedBinaryImage.h "qgarlib/LinDilatedBinaryImage.h"
 *
 * @brief Binary image dilated using a segment.
 *
 * The length of the segment is <b>2 * aDilSize + 1</b>.
 * The algorithm is very simple: Two pointers follow the current line,
 * at a <b>aDilSize</b> distance from each other. When the first pointer
 * meets a non-zero pixel or when the second pointer meets a zero pixel,
 * the next <b>aDilSize</b> pixels are set to non-zero.
 * 
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date   August 5, 2002  16:41
 * @since  Qgar 2.0
 */
class LinDilatedBinaryImage

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
   * @brief Reference to qgar::LinDilatedBinaryImage::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::LinDilatedBinaryImage::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::LinDilatedBinaryImage::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::LinDilatedBinaryImage::value_type.
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
   * maximum of the 4 possible dilations.
   *
   * @param anImg     image to be dilated
   * @param anOrient  dilation orientation (default qgar::QGE_ORIENTATION_HOR)
   * @param aDilSize  dilation size (default <b>1</b>)
   *
   * @exception qgar::QgarErrorDomain  dilation size too large for image
   */
  explicit LinDilatedBinaryImage(BinaryImage& anImg,
				 QGEorientation anOrient = QGE_ORIENTATION_HOR,
				 unsigned int aDilSize = 1)
   ;

  //@}


  /** @name Linear dilation */
  //        ===============
  //@{

  /**
   * @brief Perform a linear dilation on the given binary image.
   *
   * <b>To be used to perform a linear dilation without preserving
   * the initial image.</b>
   *
   * @param anImg     image to be dilated
   * @param anOrient  dilation orientation
   * @param aDilSize  dilation size (default <b>1</b>)
   */
  static void perform(BinaryImage* anImg,
		      QGEorientation anOrient,
		      unsigned int aDilSize = 1);

  //@}

// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

  /** @name Oriented dilations */
  //        ==================
  //@{

  /**
   * @brief Horizontal dilation.
   *
   * @param anImg     image to be dilated
   * @param aDilSize  dilation size
   *
   * @exception qgar::QgarErrorDomain  dilation size too large for image
   */
  static void dilateHor(BinaryImage* anImg, unsigned int aDilSize)
   ;

  /**
   * @brief Vertical dilation.
   *
   * @param anImg     image to be dilated
   * @param aDilSize  dilation size
   *
   * @exception qgar::QgarErrorDomain  dilation size too large for image
   */
  static void dilateVer(BinaryImage* anImg, unsigned int aDilSize)
   ;

  /**
   * @brief NE-SW dilation.
   *
   * @param anImg     image to be dilated
   * @param aDilSize  dilation size
   *
   * @exception qgar::QgarErrorDomain  dilation size too large for image
   */
  static void dilatePdiag(BinaryImage* anImg, unsigned int aDilSize)
   ;

  /**
   * @brief NW-SE dilation.
   *
   * @param anImg     image to be dilated
   * @param aDilSize  dilation size
   *
   * @exception qgar::QgarErrorDomain  dilation size too large for image
   */
  static void dilateNdiag(BinaryImage* anImg, unsigned int aDilSize)
   ;

  /**
   * @brief Maximum of the 4 possible dilations.
   *
   * @param anImg     image to be dilated
   * @param aDilSize  dilation size
   *
   * @exception qgar::QgarErrorDomain  dilation size too large for image
   */
  static void dilateAll(BinaryImage* anImg, unsigned int aDilSize)
   ;

  //@}

// -------------------------------------------------------------------
}; // class LinDilatedBinaryImage


} // namespace qgar


#endif /* __LINDILATEDBINARYIMAGE_H_INCLUDED__ */
