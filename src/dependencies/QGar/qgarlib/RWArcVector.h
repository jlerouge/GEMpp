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


#ifndef __RWARCVECTOR_H_INCLUDED__
#define __RWARCVECTOR_H_INCLUDED__


/**
 * @file RWArcVector.h
 *
 * @brief Header file of class qgar::RWArcVector.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Christian Ah-Soon">Christian Ah-Soon</a>
 * @date   July 3, 2001  16:29
 * @since  Qgar 1.0
 */


// For RCS/CVS use: Do not delete
/* $Id: RWArcVector.h,v 1.4 2006/03/31 09:32:18 gerald Exp $ */



// STD
#include <vector>
// QGAR
#include "primitives.h"
namespace qgar
{
  // Avoid #include's when not necessary
  class RWSegmentVector;
}



namespace qgar
{


/** 
 * @ingroup GRAPHPROC_POLYAPPROX
 *
 * @class RWArcVector RWArcVector.h "qgarlib/RWArcVector.h"
 *
 * @brief A vector containing Qgar arcs.
 *
 * @todo Why "Qgar arcs" (from class qgar::GenQgarArc),
 *   instead of "arcs" (from class qgar::GenArc)?
 * @todo Anyway, this class was designed when STL was not available.
 *   To be removed!
 *
 *
 * @author  <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Christian Ah-Soon">Christian Ah-Soon</a>
 * @date    July 3, 2001  16:29
 * @since   Qgar 1.0
 */
class RWArcVector

  : public std::vector<QgarArc>

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:
  
  /** @name Constructors */
  //        ============
  //@{

  /**
   * @brief Construct from a vector of segments provided
   *   by the Rosin & West's method. 
   *
   * @param  aRWvector  the vector of segments
   * @param  thres      threshold: when high, the arc can be
   *                    far from the segments
   */
  explicit RWArcVector(RWSegmentVector& aRWvector,
		       int thres = 50);

  /**
   * @brief Construct from two vectors of segments provided
   *   by the Rosin & West's method.
   *
   * @param aRWvector1  first vector of segments
   * @param aRWvector2  second vector of segments
   * @param thres       threshold: when high, the arc can be far
    *                   from the segments
   *
   * @warning The two vectors must have one common extremity.
   */
  RWArcVector(RWSegmentVector& aRWvector1,
	      RWSegmentVector& aRWvector2,
	      int thres = 50);
  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Non-virtual destructor.
   */
  virtual ~RWArcVector();

  //@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:


  /** @name Thresholds */
  //        ==========
  //@{

  /**
   * @brief Threshold to estimate the dispersion
   *   of the potential centers of an arc.
   */
  int _centerDispersionThreshold;

  //@}


// -------------------------------------------------------------------
}; // Class RWArcVector


} // namespace qgar


#endif /* __RWARCVECTOR_H_INCLUDED__ */

