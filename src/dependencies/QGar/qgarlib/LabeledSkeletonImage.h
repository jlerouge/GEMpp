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


#ifndef __LABELEDSKELETONIMAGE_H_INCLUDED__
#define __LABELEDSKELETONIMAGE_H_INCLUDED__


/**
 * @file LabeledSkeletonImage.h
 *
 * @brief Header file of class qgar::LabeledSkeletonImage.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Sebastien Taghite">Sébastien Taghite</a>
 *   from previous work by Adlane Habed and Karl Tombre
 * @date  July 3, 2001  16:46
 * @since Qgar 1.0
 */


// For RCS/CVS use: Do not delete
/* $Id: LabeledSkeletonImage.h,v 1.26 2007/02/14 17:34:05 masini Exp $ */



// STD
#include <vector>
// QGAR
#include "GenImage.h"
namespace qgar
{
  // Avoid #include's when not necessary
  class Dist34BlackCCImage;
  template <class T> class GenPoint;
}



namespace qgar
{


/** 
 * @ingroup IMGPROC_SKEL
 *
 * @class LabeledSkeletonImage LabeledSkeletonImage.h "qgarlib/LabeledSkeletonImage.h"
 *
 *
 * @brief Skeleton computed using the (3,4)-distance transform.
 *
 * As described by Gabriella Sanniti di Baja in
 * [<a href="Bibliography.html#Sanniti-di-Baja-1994">Sanniti&nbsp;di&nbsp;Baja,&nbsp;1994</a>]
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Sebastien Taghite">Sébastien Taghite</a>
 *   from previous work by Adlane Habed and Karl Tombre
 * @date  July 3, 2001  16:46
 * @since Qgar 1.0
 */
class LabeledSkeletonImage

  : public GreyLevelImage

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  /** @name Constructors */
  //        ============
  //@{

  /**
   * @brief Construct from given (3,4)-distance transform image.
   *
   * @param img   3-4 distance transform image
   *   from which the skeleton is created
   * @param maxPruning maximum number of peripheral rows and/or columns
   *   which may be missed (default <b>0</b>, no pruning)
   */
  DLL_EXPORT explicit LabeledSkeletonImage(const Dist34BlackCCImage& img,
				int maxPruning = 0);

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  DLL_EXPORT virtual ~LabeledSkeletonImage();

  //@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /** @name The skeleton image */
  //        ==================
  //@{

  /**
   * @brief The marker map.
   */
  unsigned char* _pPixMap2;

  //@}


// -------------------------------------------------------------------
}; // class LabeledSkeletonImage


} // namespace qgar


#endif /* __LABELEDSKELETONIMAGE_H_INCLUDED__ */

