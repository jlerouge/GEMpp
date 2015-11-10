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


#ifndef __TTBINARYIMAGE_H_INCLUDED__
#define __TRIERTAXTBINARYIMAGE_H_INCLUDED__


/**
 * @file TTBinaryImage.h
 *
 * @brief Header file of class qgar::TTBinaryImage.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   July 18, 2005  15:15
 * @since  Qgar 2.2
 */



// For RCS/CVS use: Do not delete
/* $Id: TTBinaryImage.h,v 1.4 2006/03/31 09:32:19 gerald Exp $ */



// QGAR
#include "GenImage.h"



namespace qgar
{


/**
 * @ingroup IMGPROC_BIN
 *
 * @class TTBinaryImage TTBinaryImage.h "qgarlib/TTBinaryImage.h"
 *
 * @brief Binary image created from a grey-level image, using binarization
 * method designed by Trier and Taxt
 * [<a href="Bibliography.html#Trier-and-Taxt-1995">Trier&nbsp;and&nbsp;Taxt,&nbsp;1995</a>]
 * from White and Rohrer's method.
 *
 * Canny's operator, instead of Sobel's one, is used for edges detection.
 *
 * @warning
 * <ul>
 * <li>The image to be binarized must have at least 3 rows and
 * 3 columns.</li>
 * <li>As the first and last rows (resp. first and last columns) of the
 * image are arbitrarily set to <b>white</b> by the algorithm used to
 * construct connected components (see class qgar::ConnectedComponents),
 * they are filled with a copy of their adjacent row (resp. column)
 * in the binarized image.</li>
 * </ul>
 *
 *
 * @todo
 * Introduce BLACK and WHITE values as parameters of the computation
 * of the connected components: In this way, there will be no need
 * to duplicate an image if 4-connected black components are needed.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   July 18, 2005  15:15
 * @since  Qgar 2.2
 */
class TTBinaryImage

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
   * @brief Reference to qgar::TTBinaryImage::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::TTBinaryImage::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::TTBinaryImage::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::TTBinaryImage::value_type.
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
   * @brief Construct a binary image from a given grey-level image.
   *
   * See the paper cited in class header for details.
   *
   * @param aGreyLevelImg  a grey-level image
   * @param aSigma         smoothing coefficient    (default <b>1.</b>, i.e. none)
   * @param anActThrs      activity threshold       (default <b>40.</b>)
   * @param aPostThrs      postprocessing threshold (default <b>30.</b>)
   */
  explicit TTBinaryImage(const GreyLevelImage& aGreyLevelImg, 
			 const double aSigma     =  1.0,
			 const double anActThrs  = 40.0,
			 const double aPostThrs  = 30.0); 

  //@}

// -------------------------------------------------------------------
}; // class TTBinaryImage


} // namespace qgar 


#endif /* TTBINARYIMAGE_H_INCLUDED */
