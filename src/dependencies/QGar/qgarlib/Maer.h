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


#ifndef __MAER_H_INCLUDED__
#define __MAER_H_INCLUDED__


/**
 * @file Maer.h
 * @brief Header file of template class qgar::Maer.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   May 13, 2004  11:30
 * @since  Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: Maer.h,v 1.17 2006/07/04 13:37:43 masini Exp $ */



// STD
#include <list>
// QGAR
#include "primitives.h"
namespace qgar
{
  // Avoid #include's when not necessary
  class FreemanChain;
}



namespace qgar
{


/**
 * @ingroup TOOL_MAER
 *
 * @class Maer Maer.h "qgarlib/Maer.h"
 *
 * @brief Minimum-Area Encasing Rectangle (MAER).
 *
 * Compute a MAER
 * from a given list of points, typically supposed
 * to determine the contour of an image component.
 * See
 * [<a href="Bibliography.html#Freeman-and-Shapira-1975">Freeman&nbsp;and&nbsp;Shapira,&nbsp;1975</a>]
 *
 * <ul>
 * <li>
 * When only a single point is given, the MAER is a rectangle
 * whose 4 corners are this very point.
 * </li>
 * <li>
 * When 2 points or a series of aligned points are given,
 * the MAER is a rectangle with 2 pairs of identical corners,
 * corresponding to the extremities of the series. For example:
@verbatim
   Y
    ^
    |
  1 -  +  +  +     +         MAER = (1,1) (1,1) (5,1) (5,1)
    |
    +--|--|--|--|--|--->
   0   1  2  3  4  5    X
@endverbatim
 * </li>
 * </ul>
 *
 * In both cases, the MAER area is equal to <b>0</b>.
 *
 * The computing is performed using <b>double</b> numbers, and
 * the MAER features are also stored as <b>double</b> numbers.
 *
 *
 * @warning No default constructor is provided.
 *
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date     May 13, 2004  11:30
 * @since    Qgar 2.1
 */
class Maer
{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  /** @name Constructors */
  //        ============
  //@{

  /**
   * @brief Create from a list of points
   * having a type different from <b>double</b>.
   *
   * @param aPtList  a list of points
   *
   * @warning Computing is performed using <b>double</b> numbers.
   * Thus, when the type of the given points is not <b>double</b>,
   * each given point is converted into a point having <b>double</b>
   * coordinates, <i>i.e.</i> the given list is duplicated.
   *
   * @todo <b>When implemented out of the class, the linkage aborts
   * because of a <i>multiple definition</i> error!</b>
   */
  template <class T>
  explicit
  Maer(const std::list< GenPoint<T> >& aPtList);

  /**
   * @brief Create from a Freeman chain
   *   (representing the contour of an image component).
   *
   * @param aCh  a Freeman Chain
   */
  explicit Maer(const FreemanChain& aCh);

  /**
   * @brief Copy constructor.
   *
   * @param aMaer  a MAER
   */
  Maer(const Maer& aMaer);

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Non-virtual destructor:
   * the class is not supposed to be derived.
   */
  ~Maer();

  //@}


  /** @name Access */
  //        ======
  //@{

  /**
   * @brief Get the list including the 4 corners of the MAER.
   */
  const std::list<DPoint>& accessVertices() const;
  
  /**
   * @brief Get a copy of the list including the 4 corners of the MAER.
   */
  std::list<DPoint> vertices() const;
  
  /**
   * @brief Get area, in pixels.
   */
  inline double areaPx() const; 
 
  //@}


  /** @name Operators */
  //        =========
  //@{

  /**
   * @brief Assignment.
   *
   * @param aMaer  a Minimum-Area Enclosing Rectangle
   */
  Maer& operator=(const Maer& aMaer);

  //@}

// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /** @name MAER features */
  //        =============
  //@{

  /**
   * @brief The four corners.
   */
  std::list<DPoint> vertices_;

  /**
   * @brief Area, in pixels.
   */
  double areaPx_;

  //@}

// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

  /** @name Disabled */
  //        ========
  //@{

  /**
   * @brief Disabled default constructor.
   *
   * The default constructor belongs to the private section
   * so that clients cannot use it.
   */
  Maer();

  //@}


  /** @name MAER computing */
  //        ==============

  /**
   * @brief Auxiliary function to compute the MAER from a list
   *        of points having <b>double</b> coordinates.
   *
   * @param aPtList  a list of <b>double</b> points
   */
  void PRIVATEcomputeMaer(const std::list<DPoint>& aPtList);

  //@}

// -------------------------------------------------------------------
}; // class Maer




// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// T E M P L A T E   I M P L E M E N T A T I O N
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


// ============
// CONSTRUCTORS
// ============


// CREATE FROM A LIST OF POINTS
// (HAVING COORDINATES TYPE DIFFERENT FROM double)

template <class T>
Maer::Maer(const std::list< GenPoint<T> >& aPtList)
{
  std::list< GenPoint<double> > dList;

  for (typename std::list< GenPoint<T> >::const_iterator itPL
	 = aPtList.begin();
       itPL != aPtList.end();
       ++itPL)
    {
      dList.push_back(GenPoint<double>(*itPL));
    }

  PRIVATEcomputeMaer(dList);
}


// CONSTRUCTOR SPECIALIZATION FOR double POINTS

template <>
inline
Maer::Maer(const std::list< GenPoint<double> >& aPtList)
{
  PRIVATEcomputeMaer(aPtList);
}


// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// END OF TEMPLATE IMPLEMENTATION
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT




// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// I N L I N E    F U N C T I O N S    I M P L E M E N T A T I O N
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII


// ======
// ACCESS
// ======

// GET AREA

inline double
Maer::areaPx() const
{
  return areaPx_;
}


// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// END OF INLINE FUNCTIONS IMPLEMENTATION
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII


} // namespace qgar 


#endif /* __MAER_H_INCLUDED__ */
