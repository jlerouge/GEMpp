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


#ifndef __CLOSEBINARYIMAGE_H_INCLUDED__
#define __CLOSEBINARYIMAGE_H_INCLUDED__


/**
 * @file     CloseBinaryImage.h
 * @brief    Header file of class qgar::CloseBinaryImage.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date     July 18, 2002  15:48
 * @since    Qgar 2.0
 */


// For RCS/CVS use: Do not delete
/* $Id: CloseBinaryImage.h,v 1.14 2006/03/30 12:49:39 masini Exp $ */


// QGAR
#include "GenImage.h"
#include "QgarErrorDomain.h"



namespace qgar
{

/**
 * @class CloseBinaryImage CloseBinaryImage.h "qgarlib/CloseBinaryImage.h"
 * @ingroup IMGPROC_MORPH
 * @brief Closing of a binary image, using morphological operators.
 * 
 * The closing structural element is a square.
 * 
 * @todo Allow the use of other structural elements, like disks or crosses.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Mathieu Baeumler">Mathieu Baeumler</a>
 * @date   July 18, 2002  15:48
 * @since  Qgar 2.0
 */
class CloseBinaryImage

  : public BinaryImage

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  /** @name Constructors */
  //        ============
  //@{
  /**
   * @brief Construct the closing of a binary image.
   * @param anImg         image to be closed
   * @param aClosingSize  closing size
   * 
   * @exception qgar::QgarErrorDomain  closing size too large for image
   */
  CloseBinaryImage(BinaryImage& anImg, unsigned int aClosingSize = 1)
   ;
  //@}

  /** @name Closing */
  //        =======
  //@{
  /**
   * @brief Perform a closing of a given binary image.
   * @param anImg         image to be closed
   * @param aClosingSize  closing size
   *
   * <b>To be used to perform a closing without preserving
   * the initial image.</b>
   */
  static void perform(BinaryImage* anImg, unsigned int aClosingSize = 1);
  //@}

// -------------------------------------------------------------------
}; // class CloseBinaryImage


} // namespace qgar


#endif /* __CLOSEBINARYIMAGE_H_INCLUDED__ */
