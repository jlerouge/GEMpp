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


#ifndef __GENPOINTCHAIN_H_INCLUDED__
#define __GENPOINTCHAIN_H_INCLUDED__


/**
 * @file GenPointChain.h
 *
 * @brief Header file of class qgar::GenPointChain.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>,
 *         from previous work by Karl Tombre
 * @date   December 15, 2003  16:16
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: GenPointChain.h,v 1.16 2006/07/04 13:37:42 masini Exp $ */



// STD
#include <list>
// QGAR
#include "AbstractGenPointChain.h"
#include "primitives.h"



namespace qgar
{

/**
 * @ingroup DS_POINT
 *
 * @class GenPointChain GenPointChain.h "qgarlib/GenPointChain.h"
 *
 * @brief Chain of points having coordinates of type <b>T</b>.
 *
 * A point is an instance of class qgar::GenPoint<T>.
 * New points can only be inserted to the beginning or to the end of the chain.
 *
 * Such a chain is implemented by a STL list of points with an iterator that
 * allows bidirectional traversal of the chain. The validity of the iterator
 * is preserved by any legal operation on the chain, unless the chain is empty.
 *
 * <b>Warning: Such a chain cannot be used in the STL way. The beginning
 * (resp. end) of the chain is the first (resp. last) point of the chain,
 * which is returned by functions qgar::GenPointChain::accessFront
 * and qgar::GenPointChain::front (resp. GenPointChain::back and
 * qgar::GenPointChain::back). In other words, the iterator <i>always</i>
 * points to a particular point in the chain (unless empty).</b>
 *
 * To use the chain in the Qgar way:
 * - To set the iterator to the beginning (resp. end) of the chain,
 *   function qgar::GenPointChain::setToBegin
 *   (resp. qgar::GenPointChain::setToEnd)
 * - To test if the iterator points to the beginning (resp. end)
 *   of the chain, function qgar::GenPointChain::isAtBegin
 *   (resp. qgar::GenPointChain::isAtEnd)
 * - To test if the chain includes at least one point after (resp. before)
 *   the current point,  function qgar::GenPointChain::hasNext
 *   (resp. qgar::GenPointChain::hasPrevious)
 * - To move to the next (resp. previous) point, function
 *   qgar::GenPointChain::moveNext (resp. qgar::GenPointChain::movePrevious)
 * - To get the current point, functions qgar::GenPointChain::current
 *   or qgar::GenPointChain::accessCurrent
 * - To get the next (resp. previous) point, functions
 *   qgar::GenPointChain::next or qgar::GenPointChain::accessNext
 *   (resp. qgar::GenPointChain::previous or qgar::GenPointChain::accessPrevious)
 * - To insert a new point at the beginning (resp. end) of the chain,
 *   function qgar::GenPointChain::push_front
 *   (resp. qgar::GenPointChain::push_back)

 * To use the chain in the STL way:
 * - Functions qgar::GenPointChain::pointList and
 *   qgar::GenPointChain::accessPointList return the STL list of the points
 *   representing the chain,
 * - STL iterators and functions may then be used to directly manage this list.
 *
 * <b>Predefined types:</b>
 * <br> &nbsp; &nbsp; &nbsp; &nbsp; See submodule
 * <a href="group__DS__POINT.html"><b>Points & chains of points</b></a>
 * for details.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>,
 *         from previous work by Karl Tombre
 * @date   December 15, 2003  16:16
 * @since  Qgar 2.1.1
 */
template <class T> class GenPointChain

  : public AbstractGenPointChain<T>

{
// -------------------------------------------------------------------
// T Y P E   D E F I N I T I O N S
// -------------------------------------------------------------------
public:

  /** @name Types */
  //        =====
  //@{

  /**
   * @brief Type of the coordinates of the points.
   */
  typedef T value_type;

  /**
   * @brief Reference to qgar::GenPointChain::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::GenPointChain::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::GenPointChain::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::GenPointChain::value_type.
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
   * @brief Default constructor.
   *
   * The STL list of points is empty and the value of the iterator
   * is undefined.
   */
  GenPointChain<value_type>();

  /**
   * @brief Copy constructor.
   *
   * @param aPtChain  a chain of points
   *
   * @warning The internal iterator points to the beginning of the chain.
   */
  GenPointChain<value_type>(const GenPointChain<value_type>& aPtChain);

  /**
   * @brief Construct from a given point, that becomes the current point.
   *
   * The internal iterator points to the beginning of the chain.
   *
   * @param aPoint  a point
   */
  explicit GenPointChain<value_type>(const GenPoint<value_type>& aPoint);

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  virtual ~GenPointChain<T>();

  //@}


  /** @name Access to chain characteristics */
  //        ===============================
  //@{

  /**
   * @brief Is current chain empty?
   */
  virtual bool empty() const;

  /**
   * @brief Get chain size (number of points).
   */
  virtual int size() const;

 //@}

  
  /** @name Iterator */
  //        ========
  //@{

  /**
   * @brief Make the internal iterator point to the beginning
   *        (first point) of the chain.
   *
   * @warning The chain is supposed not to be empty.
   */
  virtual void setToBegin();

  /**
   * @brief Make the internal iterator point to the end
   *        (last point) of the chain.
   *
   * @warning The chain is supposed not to be empty.
   */
  virtual void setToEnd();

  /**
   * @brief Does internal iterator points to the beginning of the chain?
   */
  virtual bool isAtBegin() const;

  /**
   * @brief Does internal iterator points to the end of the chain?
   */
  virtual bool isAtEnd() const;

  /**
   * @brief Is there a point after the current point?
   *
   * @warning The chain is supposed not to be empty.
   */
  virtual bool hasNext() const;

  /**
   * @brief Is there a point before the current point?
   *
   * @warning The chain is supposed not to be empty.
   */
  virtual bool hasPrevious() const;

  /**
   * @brief Move to next point, that becomes the current point.
   *
   * @warning The chain is supposed not to be empty.
   */
  virtual void moveNext();

  /**
   * @brief Move to previous point, that becomes the current point.
   *
   * @warning The chain is supposed not to be empty.
   */
  virtual void movePrevious();

  //@}


  /** @name Access to points */
  //        ================
  //@{

  /**
   * @brief Get first point.
   *
   * @warning The chain is supposed not to be empty.
   */
  virtual const GenPoint<value_type>& accessFront() const;

   /**
   * @brief Get a copy of first point.
   *
   * @warning The chain is supposed not to be empty.
   */
  virtual GenPoint<value_type> front() const;

  /**
   * @brief Get last point.
   *
   * @warning The chain is supposed not to be empty.
   */
  virtual const GenPoint<value_type>& accessBack() const;

  /**
   * @brief Get a copy of last point.
   *
   * @warning The chain is supposed not to be empty.
   */
  virtual GenPoint<value_type> back() const;

  /**
   * @brief Get the current point.
   *
   * @warning The chain is supposed not to be empty.
   */
  virtual const GenPoint<value_type>& accessCurrent() const;

  /**
   * @brief Get a copy of the current point.
   *
   * @warning The chain is supposed not to be empty.
   */
  virtual GenPoint<value_type> current() const;

  /**
   * @brief Get the successor of the current point.
   *
   * @warning The chain is supposed not to be empty,
   * and the iterator is supposed not to point to the last point.
   */
  const GenPoint<value_type>& accessNext();

  /**
   * @brief Get a copy of the successor of the current point.
   *
   * @warning The chain is supposed not to be empty,
   * and the iterator is supposed not to point to the last point.
   */
  virtual GenPoint<value_type> next();

  /**
   * @brief Get the predecessor of the current point.
   *
   * @warning The chain is supposed not to be empty,
   * and the iterator is supposed not to point to the first point.
   */
  const GenPoint<value_type>& accessPrevious();

  /**
   * @brief Get a copy of the predecessor of the current point.
   *
   * @warning The chain is supposed not to be empty,
   * and the iterator is supposed not to point to the first point.
   */
  virtual GenPoint<value_type> previous();

  //@}


  /** @name Access to the list of points */
  //        ============================
  //@{

  /**
   * @brief Get the STL list implementing the chain of points.
   *
   * The function returns a <b>const</b> result, so that the user
   * cannot directly transform the list.
   */
  inline const std::list< GenPoint<value_type> >& accessPointList() const;

  /**
   * @brief Get the STL list implementing the chain of points.
   *
   * @warning The function does not return a <b>const</b> result,
   * allowing the client to directly transform the internal structure
   * of the chain, without using functions of the interface.
   *
   * @todo Maybe this kind of function should not be provided!
   */
  inline std::list< GenPoint<value_type> >& pointList();

  //@}


  /** @name Insertion */
  //        =========
  //@{

  /**
   * @brief Insert a point at the beginning of the chain.
   *
   * The internal iterator remains valid after the operation.
   *
   * @param aPt  a point
   */
  virtual void push_front(const GenPoint<value_type>& aPt);

  /**
   * @brief Insert a point at the end of the chain.
   *
   * The internal iterator remains valid after the operation.
   *
   * @param aPt  a point
   */
  virtual void push_back(const GenPoint<value_type>& aPt);

  //@}


  /** @name Transformations */
  //        ===============
  //@{

  /**
   * @brief Reverse the order of elements in the list.
   *
   * @warning The validity of the internal iterator to the chain
   * is preserved.
   */
  virtual void reverse();

  //@}


  /** @name Conversions */
  //        ===========
  //@{

  /**
   * @brief Convert into a (STL) list of points.
   */
  virtual std::list< GenPoint<value_type> > toPointList() const;

  //@}


  /** @name Operators */
  //        =========
  //@{

  /**
   * @brief Assignment.
   *
   * @param aPtChain  a chain of points
   *
   * @warning The internal iterator points to the beginning of the chain.
   */
  GenPointChain<value_type>&
  operator=(const GenPointChain<value_type>& aPtChain);

  //@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:


  /** @name Implementation of a chain of points */
  //        ===================================
  //@{

  /**
   * @brief List of the points.
   */
  std::list< GenPoint<value_type> > _chain;

  /**
   * @brief Iterator on the list of points.
   */
  typename std::list< GenPoint<value_type> >::iterator _iter;

  //@}

// -------------------------------------------------------------------

}; // Class GenPointChain


} // namespace qgar




// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// I M P L E M E N T A T I O N
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII

#include "GenPointChain.tcc"

// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII




// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// P R E D E F I N E D    P O I N T C H A I N    T Y P E S
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


namespace qgar
{


/** @name Point chain type names */
//        ======================
//@{

/**
 * @ingroup DS_POINT
 *
 * @brief Chain of points with <b>integer</b> coordinates.
 *
 * @see IPointChain
 */
typedef GenPointChain<int> PointChain;

/**
 * @ingroup DS_POINT
 *
 * @brief Chain of points with <b>integer</b> coordinates.
 *
 * @see PointChain
 */
typedef GenPointChain<int> IPointChain;

/**
 * @ingroup DS_POINT
 *
 * @brief Chain of points with <b>float</b> coordinates.
 */
typedef GenPointChain<float> FPointChain;

/**
 * @ingroup DS_POINT
 *
 * @brief Chain of points with <b>double</b> coordinates.
 */
typedef GenPointChain<double> DPointChain;

//@}


} // namespace qgar


// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


#endif /* __GENPOINTCHAIN_H_INCLUDED__ */
