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


#ifndef __NIBLACKBINARYIMAGE_H_INCLUDED__
#define __NIBLACKBINARYIMAGE_H_INCLUDED__


/**
 * @file   NiblackBinaryImage.h
 * @brief  Header file of class qgar::NiblackBinaryImage.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date   July 3, 2001  15:01
 * @since  Qgar 2.0
 */



// For RCS/CVS use: Do not delete
/* $Id: NiblackBinaryImage.h,v 1.17 2006/03/31 09:32:17 gerald Exp $ */



// QGAR
#include "Component.h"
#include "GenImage.h"



namespace qgar
{


/**
 * @ingroup IMGPROC_BIN
 *
 * @class NiblackBinaryImage NiblackBinaryImage.h "qgarlib/NiblackBinaryImage.h"
 *
 * @brief Binary image created by adaptive thresholding of a grey-level image.
 *
 * The thresholding is based on the method proposed by W. Niblack 
 * in [<a href="Bibliography.html#Niblack-1986">Niblack,&nbsp;1986</a>].
 * As suggested by Trier and Jain in
 * [<a href="Bibliography.html#Trier-and-Jain-1995">Trier&nbsp;and&nbsp;Jain,&nbsp;1995</a>],
 * this basic method is completed with the postprocessing step first
 * proposed by S.D. Yanowitz and A.M. Bruckstein in
 * [<a href="Bibliography.html#Yanowitz-and-Bruckstein-1989">Yanowitz&nbsp;and&nbsp;Bruckstein,&nbsp;1989</a>].
 *
 * Two extra global thresholds are used, so that adaptive binarization is
 * replaced by global thresholding for all pixels which are very bright
 * or very dark.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date   July 3, 200  15:01
 * @since  Qgar 2.0
 */
class NiblackBinaryImage

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
   * @brief Reference to qgar::NiblackBinaryImage::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::NiblackBinaryImage::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::NiblackBinaryImage::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::NiblackBinaryImage::value_type.
   */
  typedef const value_type* const_pointer;

  //@}

// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  /** @name CONSTRUCTORS */
  //        ============
  //@{

  /**
   * @brief Construct from a grey-level image.
   *
   * Niblack's method itself relies on computing the local mean
   * <b>m</b> and the local standard deviation <b>s</b>
   * in a <b>aMaskSize X aMaskSize</b> neighborhood and on setting
   * the dynamic threshold at each point to <b>m + aK * s</b>.
   * The default values are those suggested by Trier and Jain.
   *
   * The postprocessing step proposed by Yanowitz and Bruckstein 
   * removes components for which the average gradient of the edge
   * pixels is below the threshold <b>aPostThres</b> (its default
   * value is <b>0</b>, which corresponds to no postprocessing).
   *
   * No local threshold is used if a pixel is darker than
   * <b>aLowThres</b> or brighter than <b>aHighThres</b>.
   *
   * @param anImg       input grey-level image
   * @param aLowThres   low threshold (default <b>20</b>)
   * @param aHighThres  high threshold (default <b>150</b>)
   * @param aMaskSize   mask size (default <b>15</b>)
   * @param aK          constant to set the dynamic threshold
   *                    (default <b>-0.2</b>)
   * @param aPostThres  postprocessing threshold (default <b>0</b>)
   */
  explicit NiblackBinaryImage(const GreyLevelImage& anImg,
			      const int aLowThres = 20,
			      const int aHighThres = 150,
			      const int aMaskSize = 15,
			      const float aK = -0.2,
			      const float aPostThres = 0.0);

  //@}

// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

  /** @name Auxiliaries */
  //        ===========
  //@{

  /**
   * @brief Get a line of labels from a component image and set pixels
   *   from WHITE components to <b>0</b>.
   *
   * @param aPMapCCImg  pointer to the pixel map
   *                    of an image of connected components
   * @param aBuffer     pointer to a buffer
   */
  void PRIVATEgetBlackLabels(Component::label_type* aPMapCCImg,
			     Component::label_type* aBuffer);

  //@}

// -------------------------------------------------------------------
}; // class NiblackBinaryImage


} // namespace qgar 

#endif /* __NIBLACKBINARYIMAGE_H_INCLUDED__ */
