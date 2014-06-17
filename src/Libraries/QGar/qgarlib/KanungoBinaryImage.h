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


#ifndef __KANUNGOBINARYIMAGE_H_INCLUDED__
#define __KANUNGOBINARYIMAGE_H_INCLUDED__


/**
 * @file KanungoBinaryImage.h
 *
 * @brief Header file of class qgar::KanungoBinaryImage.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Perrin & Kheder">Julien Perrin & Sami Kheder</a>
 * @date   March 24,  2003  16:16
 * @since  Qgar 2.1.1
 */


/* $Id: KanungoBinaryImage.h,v 1.10 2006/07/04 13:37:42 masini Exp $ */

#if defined(WIN32) || defined(WIN64) // Windows platform
    #include <io.h>
#elif defined(LINUX) && (__GNUC__ >= 4) // Linux platform
    #include <unistd.h>
#endif

// QGAR
#include "GenImage.h"

namespace qgar
{

/**
 * @ingroup IMGPROC_DEG
 *
 * @class KanungoBinaryImage KanungoBinaryImage.h "qgarlib/KanungoBinaryImage.h"
 *
 * @brief Degradation of a binary image,
 * using Kanungo <i>et al</i>&nbsp;'s method.
 *
 * See
 * [<a href="Bibliography.html#Kanungo-et-al-2000">Kanungo&nbsp;et&nbsp;al,&nbsp;2000</a>]
 * for full details about the method.
 *
 * @todo To be documented!...
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Perrin & Kheder">Julien Perrin & Sami Kheder</a>
 * @date   March 24,  2003  16:16
 * @since  Qgar 2.1.1
 */
class KanungoBinaryImage

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
   * @brief Reference to qgar::KanungoBinaryImage::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::KanungoBinaryImage::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::KanungoBinaryImage::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::KanungoBinaryImage::value_type.
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
   * @brief Construct a degraded image from a given binary image.
  *
   * If the provided structural element size
   * (argument <b>structEltSize</b>) is <b>0</b>, the final closing,
   * as described in Kanungo's method, is not performed.
   *
   * @param  anImg          image to be degraded
   * @param  alpha0         see Kanungo's method (default <b>1</b>)
   * @param  alpha          see Kanungo's method (default <b>2</b>)
   * @param  beta0          see Kanungo's method (default <b>1</b>)
   * @param  beta           see Kanungo's method (default <b>2</b>)
   * @param  eta            see Kanungo's method (default <b>0</b>)
   * @param  structEltSize  size of the square structutal element
   *   of the final closing (default <b>3</b>)
   */
  explicit KanungoBinaryImage(BinaryImage& anImg,
                  double alpha0 = 1.0,
                  double alpha  = 2.0,
                  double beta0  = 1.0,
                  double beta   = 2.0,
                  double eta    = 0.0,
                  int structEltSize = 3);

  //@}

// -------------------------------------------------------------------
}; // class KanungoBinaryImage


} // namespace qgar





// HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// H  E  L  P  E  R  S
// HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH


namespace qgar
{


/** @name Kanungo degradation helper functions */
//        ====================================
//@{

/**
 * @ingroup GLOB_HELPER
 *
 * @brief Degrade a given image.
 *
 * If the provided structural element size is <b>0</b>
 * (argument <b>structEltSize</b>), the final closing,
 * as described in Kanungo's method, is not performed.
 *
 * @param  anImg          image to be degraded
 * @param  alpha0         see Kanungo's method (default <b>1</b>)
 * @param  alpha          see Kanungo's method (default <b>2</b>)
 * @param  beta0          see Kanungo's method (default <b>1</b>)
 * @param  beta           see Kanungo's method (default <b>2</b>)
 * @param  eta            see Kanungo's method (default <b>0</b>)
 * @param  structEltSize  size of the square structutal element
 *   of the final closing (default <b>3</b>)
 *
 * @exception
 * qgar::QgarErrorInvalidArg  structural element size cannot be negative
 */
  void qgKanungoDegradation(BinaryImage& anImg,
                double alpha0 = 1.0,
                double alpha  = 2.0,
                double beta0  = 1.0,
                double beta   = 2.0,
                double eta    = 0.0,
                int structEltSize = 3)
   ;

//@}


} // namespace qgar


// HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH


#endif /* __KANUNGOBINARYIMAGE_H_INCLUDED__ */

