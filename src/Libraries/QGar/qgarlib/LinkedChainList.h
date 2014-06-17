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


#ifndef __LINKEDCHAINLIST_H_INCLUDED__
#define __LINKEDCHAINLIST_H_INCLUDED__


/**
 * @file LinkedChainList.h
 *
 * @brief Header file of class qgar::LinkedChainList.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date   July 3,  2001  16:14
 * @since  Qgar 1.0
 */


// For RCS/CVS use: Do not delete
/* $Id: LinkedChainList.h,v 1.18 2006/07/04 13:37:43 masini Exp $ */



// STL
#include <list>
// QGAR
#include "GenImage.h"
#include "GenPointChain.h"
#include "QgarErrorDeveloper.h"
namespace qgar
{
  // Avoid #include's when not necessary
  class LabeledSkeletonImage;
}



namespace qgar
{


/**
 * @ingroup DS_POINT
 *
 * @class LinkedChainList LinkedChainList.h "qgarlib/LinkedChainList.h"
 *
 * @brief List of linked chains of <b>integer</b> points.
 *
 *
 * @todo This class should not derive from class <b>std::list</b>,
 * but should be its client!
 * The current implementation may be/is the cause of memory losses
 * due to the use of dynamically allocated objects by the function
 * members...
 *
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date     July 3,  2001  16:14
 * @since    Qgar 1.0
 */
class LinkedChainList

  : public std::list< GenPointChain<int> >

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  /** @name Constructors */
  //        ============
  //@{

  /**
   * @brief Build from given binary image.
   *
   * Build chains of points from a binary image, using an algorithm
   * designed by Salvatore Tabbone, and slightly improved by Karl
   * Tombre.
   *
   * - Chains of length smaller than threshold <b>minChainlength</b>
   *   are removed.
   * - Cycles of length smaller than threshold <b>minCycleLength</b>
   *   are not taken into account.
   */
  DLL_EXPORT explicit LinkedChainList(const BinaryImage& img,
			   unsigned int minChainLength = 3,
			   unsigned int minCycleLength = 4);

  /**
   * @brief Build from a labeled skeleton.
   *
   * This function builds chains of points from a labeled skeleton image.
   * The algorithm used here takes advantage of the properties of a
   * labeled skeleton to construct chains taking junctions into account.
   *
   * @exception qgar::QgarErrorDeveloper  strange things happen!
   */
  DLL_EXPORT explicit LinkedChainList(const LabeledSkeletonImage& skel)
   ;

  /**
   * @brief Build with given minimal length parameters.
   * 
   * For temporary use...
   *
   * @todo
   * - Karl's note: for temporary use.
   * - G!'s note: make it actually temporary!
   */
  LinkedChainList(unsigned int minChainLength = 0,
		  unsigned int minCycleLength = 0);

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  DLL_EXPORT virtual ~LinkedChainList();

  //@}

// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

  /** @name Auxiliary data */
  //        ==============
  //@{

  /**
   * @brief Minimum length of a valid chain.
   */
  int _minChainLength;

  /**
   * @brief Minimum length of a valid cycle.
   */
  int _minCycleLength;

  //@}


  /** @name Auxiliary functions */
  //       ====================
  //@{

  /**
   * @brief Recursive function for chaining.
   */
  PointChain* aChain(PointChain* ch,
		     int l,
		     int c,
		     GreyLevelImage& wkImg);

  //@}

// -------------------------------------------------------------------
}; // class LinkedChainList


} // namespace qgar


#endif /* __LINKEDCHAINLIST_H_INCLUDED__ */
