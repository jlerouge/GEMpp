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


#ifndef __LINDILATEDIMAGE_H_INCLUDED__
#define __LINDILATEDIMAGE_H_INCLUDED__


/**
 * @file LinDilatedImage.h
 *
 * @brief Header file of class qgar::LinDilatedImage.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date   August 5, 2002  16:52
 * @since  Qgar 2.0
 */



// For RCS/CVS use: Do not delete
/* $Id: LinDilatedImage.h,v 1.18 2006/07/04 13:37:43 masini Exp $ */



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
 * @class LinDilatedImage LinDilatedImage.h "qgarlib/LinDilatedImage.h"
 *
 * @brief Grey-level image dilated using a segment.
 *
 * The length of the segment is <b>2 * aDilSize + 1</b>.
 * The algorithm is derived from
 * [<a href="Bibliography.html#van-Herk-1992">van Herk,&nbsp;1992</a>].
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date   August 5, 2002  16:52
 * @since  Qgar 2.0
 */
class LinDilatedImage

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
   * @brief Reference to qgar::LinDilatedImage::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::LinDilatedImage::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::LinDilatedImage::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::LinDilatedImage::value_type.
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
   *
   * Orientation qgar::QGE_ORIENTATION_ALL corresponds to the
   * maximum of the 4 possible dilations.
   *
   * @param anImg     image to be dilated
   * @param anOrient  dilation orientation
   *                  (default qgar::QGE_ORIENTATION_HOR)
   * @param aDilSize  dilation size
   *
   * @exception qgar::QgarErrorDomain  dilation size too large for image
   */
  explicit LinDilatedImage(GreyLevelImage& anImg,
			   QGEorientation anOrient = QGE_ORIENTATION_HOR,
			   unsigned int aDilSize = 1)
   ;

  //@}


  /** @name Linear dilation */
  //        ===============
  //@{

  /**
   * @brief Perform a linear dilation on the given grey-level image.
   *
   * <b>To be used to perform a linear dilation without preserving
   * the initial image.</b>
   *
   * Orientation qgar::QGE_ORIENTATION_ALL corresponds to the
   * maximum of the 4 possible dilations.
   *
   * @param anImg     image to be dilated
   * @param anOrient  dilation orientation
   * @param aDilSize  dilation size
   */
  static void perform(GreyLevelImage* anImg,
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
  static void dilateHor(GreyLevelImage* anImg, unsigned int aDilSize)
   ;

  /**
   * @brief Vertical dilation.
   *
   * @param anImg     image to be dilated
   * @param aDilSize  dilation size
   *
   * @exception qgar::QgarErrorDomain  dilation size too large for image
   */
  static void dilateVer(GreyLevelImage* anImg, unsigned int aDilSize)
   ;

  /**
   * @brief NE-SW dilation.
   *
   * @param anImg     image to be dilated
   * @param aDilSize  dilation size
   *
   * @exception qgar::QgarErrorDomain  dilation size too large for image
   */
  static void dilatePdiag(GreyLevelImage* anImg, unsigned int aDilSize)
   ;

  /**
   * @brief NW-SE dilation.
   *
   * @param anImg     image to be dilated
   * @param aDilSize  dilation size
   *
   * @exception qgar::QgarErrorDomain  dilation size too large for image
   */
  static void dilateNdiag(GreyLevelImage* anImg, unsigned int aDilSize)
   ;

  /**
   * @brief Maximum of the 4 possible dilations.
   *
   * @param anImg     image to be dilated
   * @param aDilSize  dilation size
   *
   * @exception qgar::QgarErrorDomain  dilation size too large for image
   */
  static void dilateAll(GreyLevelImage* anImg, unsigned int aDilSize)
   ;

  //@}

// -------------------------------------------------------------------
}; // class LinDilatedImage


} // namespace qgar


#endif /* __LINDILATEDIMAGE_H_INCLUDED__ */

