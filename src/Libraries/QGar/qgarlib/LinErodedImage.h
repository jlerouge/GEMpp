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


#ifndef __LINERODEDIMAGE_H_INCLUDED__
#define __LINERODEDIMAGE_H_INCLUDED__


/**
 * @file LinErodedImage.h
 *
 * @brief Header file of class qgar::LinErodedImage.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date   August 5, 2002  17:16
 * @since  Qgar 2.0
 */


// For RCS/CVS use: Do not delete
/* $Id: LinErodedImage.h,v 1.21 2006/07/04 13:37:43 masini Exp $ */



// QGAR
#include "GenImage.h"
#include "QgarErrorDomain.h"



namespace qgar
{
/**
 * @ingroup IMGPROC_MORPH
 *
 * @class LinErodedImage LinErodedImage.h "qgarlib/LinErodedImage.h"
 *
 * @brief Grey-level image linearly eroded, using a segment.
 * 
 * The length of the segment is <b>2 * aDilSize + 1</b>.
 * The algorithm is derived from
 * [<a href="Bibliography.html#van-Herk-1992">van&nbsp;Herk,&nbsp;1992</a>].
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date   August 5, 2002  17:16
 * @since  Qgar 2.0
 */
class LinErodedImage

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
   * @brief Reference to qgar::LinErodedImage::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::LinErodedImage::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::LinErodedImage::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::LinErodedImage::value_type.
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
   * @brief Construct from a grey-level image. 
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
  explicit LinErodedImage(GreyLevelImage& anImg,
			  QGEorientation anOrient = QGE_ORIENTATION_HOR,
			  unsigned int anEroSize = 1)
   ;

  //@}


  /** @name Linear erosion */
  //        ==============
  //@{

  /**
   * @brief Perform a linear erosion on a given grey-level image.
   *
   * <b>To be used to perform a linear erosion without preserving
   * the initial image.</b>
   *
   * @param  anImg      image to be eroded
   * @param  anOrient   erosion orientation
   * @param  anEroSize  erosion size (default <b>1</b>)
   */
  static void perform(GreyLevelImage* anImg,
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
  static void erodeHor(GreyLevelImage* anImg, unsigned int anEroSize)
   ;

  /**
   * @brief Vertical erosion.
   *
   * @param anImg      image to be eroded
   * @param anEroSize  erosion size
   *
   * @exception qgar::QgarErrorDomain  erosion size too large for image
   */
  static void erodeVer(GreyLevelImage* anImg, unsigned int anEroSize)
   ;

  /**
   * @brief NE-SW erosion.
   *
   * @param anImg      image to be eroded
   * @param anEroSize  erosion size
   *
   * @exception qgar::QgarErrorDomain  erosion size too large for image
   */
  static void erodePdiag(GreyLevelImage* anImg, unsigned int anEroSize)
   ;
  
  /**
   * @brief NW-SE erosion.
   *
   * @param anImg      image to be eroded
   * @param anEroSize  erosion size
   *
   * @exception qgar::QgarErrorDomain  erosion size too large for image
   */
  static void erodeNdiag(GreyLevelImage* anImg, unsigned int anEroSize)
   ;

  /**
   * @brief Maximum of the 4 erosions.
   *
   * @param anImg      image to be eroded
   * @param anEroSize  erosion size
   *
   * @exception qgar::QgarErrorDomain  erosion size too large for image
   */
  static void erodeAll(GreyLevelImage* anImg, unsigned int anEroSize)
   ;

  //@}


// -------------------------------------------------------------------
}; // class LinErodedImage


} // namespace qgar


#endif /* __LINERODEDIMAGE_H_INCLUDED__ */
