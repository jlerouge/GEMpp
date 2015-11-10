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


#ifndef __WDSEGMENTLIST_H_INCLUDED__
#define __WDSEGMENTLIST_H_INCLUDED__


/**
 * @file WDSegmentList.h
 *
 * @brief Header file of class qgar::WDSegmentList.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date   July 3, 2001  09:56
 * @since  Qgar 1.0
 */


// For RCS/CVS use: Do not delete
/* $Id: WDSegmentList.h,v 1.7 2007/02/14 17:34:05 masini Exp $ */



// STD
#include <list>
// QGAR
#include "image.h"
#include "primitives.h"
namespace qgar
{
  // Avoid #include's when not necessary
  template <class T> class AbstractGenPointChain;
  template <class T> class GenPoint;
}



using namespace std;



namespace qgar
{

/*---------------------------------------------------------------------*
 |                                                                     |
 |             C  L  A  S  S      W  D  S  E  G  M  E  N  T            |
 |                                                                     |
 *---------------------------------------------------------------------*/

/**
 * @ingroup GRAPHPROC_POLYAPPROX
 *
 * @class WDSegment WDSegmentList.h
 *
 * @brief A segment resulting from a polygonal approximation
 *   performed according to Wall and Danielsson's method.
 *
 * @todo Dirty: Take a look at functions qgar::WDSegmentList::set(),
 * and conversions from WDSegments to Segments.
 * Find a way to remove this class!
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date   July 3, 2001  09:56
 * @since  Qgar 1.0
 */
class WDSegment

  : public GenSegment<int>

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  /** @name Constructors */
  //        ============
  //@{

  /**
   * @brief Default constructor: Creation of a null segment.
   */
  WDSegment();

  /**
   * @brief Construct from full data (used during approximation).
   *
   * @param orig   origin point
   * @param deltaX displacement to end point (\f$\Delta_x\f$)
   * @param deltaY displacement to end point (\f$\Delta_y\f$)
   * @param d      direction of segment
   */
  WDSegment(GenPoint<int>& orig,
	    int deltaX,
	    int deltaY,
	    QGEdirection d);

  /**
   * @brief Copy constructor.
   */
  WDSegment(const WDSegment& aSeg);

  //@}


  /** @name Access */
  //        ======
  //@{

  /**
   * @brief Get approximation factor.
   */
  inline int approxFactor() const;

  /**
   * @brief Get square length.
   */
  inline int sqrLength() const;

  /**
   * @brief Get general direction.
   */
  inline QGEdirection direction() const;

  /**
   * @brief Get length of segment.
   */
  inline double length() const;

  //@}


  /** @name Transformation */
  //        ==============
  //@{

  /**
   * @brief Set approximation factor.
   */
  inline void setApproxFactor(int af);

  /**
   * @brief Set square length.
   */
  inline void setSqrLength(int sl);

  /**
   * @brief Set general direction.
   */
  inline void setDirection(QGEdirection d);

  /**
   * @brief Translate extremum point with given point.
   */
  void translateTarget(GenPoint<int>&);

  /**
   * @brief Set segment from an other segment (member-to-member copy).
   */
  void set(const WDSegment& aSeg);

  /**
   * Set segment from given data.
   *
   * @param orig    origin point
   * @param deltaX  displacement to end point (\f$\Delta_{x}\f$)
   * @param deltaY  displacement to end point (\f$\Delta_{y}\f$)
   * @param d       direction of segment
   */
  void set(GenPoint<int>& orig, int deltaX, int deltaY, QGEdirection d);

  //@}


  /** @name Operators */
  //        =========
  //@{

  /**
   * @brief Assignment.
   */
  WDSegment& operator=(const WDSegment& w);

  /**
   * @brief Equality.
   */
  inline int operator==(const WDSegment s) const;

  /**
   * @brief Inequality.
   */
  inline int operator!=(const WDSegment s) const;

  //@}

// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /** @name Representation of a segment */
  //        ===========================
  //@{

  /**
   * @brief Square length.
   */
  int _sqrLength;

  /**
   * @brief Approximation factor.
   *
   * In the Wall & Danielsson's method, it is a measure of the
   * algebraic area between the segment and the approximated curve.
   */
  int _approxFactor;

  /**
   * @brief Direction of the segment.
   */
  QGEdirection _direction;

  //@}

// -------------------------------------------------------------------
}; // class WDSegment




// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// I N L I N E   F U N C T I O N S   I M P L E M E N T A T I O N 
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII


//  ======
//  ACCESS
//  ======


// GET APPROXIMATION FACTOR

inline int
WDSegment::approxFactor() const
{
  return _approxFactor;
}


// GET SQUARE LENGTH

inline int
WDSegment::sqrLength() const
{
  return _sqrLength;
}


// GET GENERAL DIRECTION

inline QGEdirection
WDSegment::direction() const
{
  return _direction;
}


// GET SEGMENT LENGTH

inline double
WDSegment::length() const
{
  return sqrt((double) _sqrLength);
}


// ==============
// TRANSFORMATION
// ==============


// SET APPROXIMATION FACTOR

inline void
WDSegment::setApproxFactor(int af)
{
  _approxFactor = af;
}


// SET SQUARE LENGTH

inline void
WDSegment::setSqrLength(int sl)
{
  _sqrLength = sl;
}


// SET DIRECTION

inline void
WDSegment::setDirection(QGEdirection d)
{
  _direction = d;
}


// =========
// OPERATORS
// =========


// EQUALITY

inline int
WDSegment::operator==(const WDSegment s) const
{
  return (Segment) (*this) == (Segment) s;
}


// INEQUALITY

inline int
WDSegment::operator!=(const WDSegment s) const
{
  return (Segment) (*this) != (Segment) s;
}


// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII






/*---------------------------------------------------------------------*
 |                                                                     |
 |       C  L  A  S  S      W  D  S  E  G  M  E  N  T  L  I  S  T      |
 |                                                                     |
 *---------------------------------------------------------------------*/

/** 
 * @ingroup GRAPHPROC_POLYAPPROX
 *
 * @class WDSegmentList WDSegmentList.h "qgarlib/WDSegmentList.h"
 *
 * @brief Polygonal approximation of a chain of points,
 *   using Wall & Danielsson's method.
 *
 * The method is described in
 * [<a href="Bibliography.html#Wall-and-Danielsson-1984">Wall&nbsp;and&nbsp;Danielsson,&nbsp;1984</a>].
 *
 * @todo The class should be a client of STL class list, instead of
 * deriving from it!
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date   July 3, 2001  09:56
 * @since  Qgar 1.0
 */
class WDSegmentList

  : public std::list<WDSegment>

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  /** @name Constructors */
  //        ============
  //@{

  /**
   * @brief Construct from given chain, using given threshold.
   */
  WDSegmentList(AbstractGenPointChain<int>& chain, int wdThreshold);

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  virtual ~WDSegmentList();

  //@}

// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

  /** @name Auxiliary functions */
  //        ===================
  //@{

  /**
   * @brief Perform polygonal approximation.
   */
  void PRIVATEperform(AbstractGenPointChain<int>&, int);

  //@}


  /** @name Auxiliary data */
  //        ==============
  //@{

  /**
   * @brief Used for angular points processing.
   */
  WDSegment _cutSeg;

  /**
   * @brief Used for angular points processing.
   */
  WDSegment _newSeg;

  //@}

// -------------------------------------------------------------------
}; // class WDSegmentList


} // namespace qgar


#endif /* __WDSEGMENTLIST_H_INCLUDED__ */
