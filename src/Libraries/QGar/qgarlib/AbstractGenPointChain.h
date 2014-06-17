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


#ifndef __ABSTRACTGENPOINTCHAIN_H_INCLUDED__
#define __ABSTRACTGENPOINTCHAIN_H_INCLUDED__


/**
 * @file AbstractGenPointChain.h
 *
 * @brief Header file of class qgar::AbstractGenPointChain.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>,
 *         from previous work by Karl Tombre
 * @date   December 10, 2003  19:19
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: AbstractGenPointChain.h,v 1.13 2007/02/14 17:34:04 masini Exp $ */


// STD
#include <list>
// QGAR
namespace qgar
{
  // Avoid #include's when not necessary
  template <class T> class GenPoint;
}



namespace qgar
{

/**
 * @class AbstractGenPointChain AbstractGenPointChain.h "qgarlib/AbstractGenPointChain.h"
 * @ingroup DS_POINT
 * @brief Base class for chain of points having coordinates of type <b>T</b>.
 *
 * A point is an instance of class qgar::GenPoint<T>.
 * New points can only be inserted to the beginning or to the end of the chain.
 *
 * Such a chain is provided with some kind of internal ``iterator'',
 * that allows bidirectional traversal of the chain. The relevance
 * of this iterator is preserved by any of the public operations of the class.
 *
 * - To set the iterator to the beginning (resp. end) of the chain,
 *   use function qgar::AbstractGenPointChain::setToBegin
 *   (resp. qgar::AbstractGenPointChain::setToEnd)
 * - To test if the iterator points to the beginning (resp. end) of the
 *   chain, use function qgar::AbstractGenPointChain::isAtBegin
 *   (resp. qgar::AbstractGenPointChain::isAtEnd)
 * - To test if the chain includes at least one point after (resp. before)
 *   the current point, use function qgar::AbstractGenPointChain::hasNext
 *   (resp. qgar::AbstractGenPointChain::hasPrevious)
 * - To move to the next (resp. previous) point, use function
 *   qgar::AbstractGenPointChain::moveNext
 *   (resp. qgar::AbstractGenPointChain::movePrevious)
 * - To get the current point, use functions qgar::AbstractGenPointChain::current
 *   or qgar::AbstractGenPointChain::accessCurrent
 * - To get the next (resp. previous) point, use function
 *   qgar::AbstractGenPointChain::next
 *   or qgar::AbstractGenPointChain::accessNext
 *   (resp. qgar::AbstractGenPointChain::previous
 *   or qgar::AbstractGenPointChain::accessPrevious)
 * - To insert a new point at the beginning (resp. end) of the chain,
 *   function qgar::AbstractGenPointChain::push_front
 *   (resp. qgar::AbstractGenPointChain::push_back)
 *
 * <b>Predefined types:</b>
 * <br> &nbsp; &nbsp; &nbsp; &nbsp; See submodule
 * <a href="group__DS__POINT.html"><b>Points & chains of points</b></a>
 * for details.
 *
 * @warning
 * This is an abstract class: It cannot be instantiated.
 * Pure virtual functions are:
 * - qgar::AbstractGenPointChain::acessBack
 * - qgar::AbstractGenPointChain::accessCurrent
 * - qgar::AbstractGenPointChain::accessFront
 * - qgar::AbstractGenPointChain::accessNext
 * - qgar::AbstractGenPointChain::accessPrevious
 * - qgar::AbstractGenPointChain::back
 * - qgar::AbstractGenPointChain::current
 * - qgar::AbstractGenPointChain::empty
 * - qgar::AbstractGenPointChain::front
 * - qgar::AbstractGenPointChain::hasNext
 * - qgar::AbstractGenPointChain::hasPrevious
 * - qgar::AbstractGenPointChain::isAtBegin
 * - qgar::AbstractGenPointChain::isAtEnd
 * - qgar::AbstractGenPointChain::moveNext
 * - qgar::AbstractGenPointChain::movePrevious
 * - qgar::AbstractGenPointChain::next
 * - qgar::AbstractGenPointChain::previous
 * - qgar::AbstractGenPointChain::push_back
 * - qgar::AbstractGenPointChain::push_front
 * - qgar::AbstractGenPointChain::reverse
 * - qgar::AbstractGenPointChain::setToBegin
 * - qgar::AbstractGenPointChain::setToEnd
 * - qgar::AbstractGenPointChain::size
 * - qgar::AbstractGenPointChain::toPointList
 *
 * @author  <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>,
 *          from previous work by Karl Tombre
 * @date    December 10, 2003  19:19
 * @since   Qgar 2.1.1
 */
template <class T> class AbstractGenPointChain
{
// -------------------------------------------------------------------
// T Y P E   D E F I N I T I O N S
// -------------------------------------------------------------------
public:


  /** @name Types */
  //        =====
  //@{

  /**
   * @brief Type of the points stored in the chain.
   */
  typedef T value_type;

  /**
   * @brief Reference to qgar::AbstractGenPointChain::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::AbstractGenPointChain::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::AbstractGenPointChain::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::AbstractGenPointChain::value_type.
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
   */
  AbstractGenPointChain();

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  virtual ~AbstractGenPointChain();

  //@}


  /** @name Access to chain characteristics */
  //        ===============================
  //@{

  /**
   * @brief Is current chain empty?
   */
  virtual bool empty() const = 0;

  /**
   * @brief Get chain size (number of points).
   */
  virtual int size() const = 0;

  //@}


  /** @name Iterator */
  //        ========
  //@{

  /**
   * @brief Set internal iterator to the beginning of the chain.
   */
  virtual void setToBegin() = 0;

  /**
   * @brief Set internal iterator to the end of the chain.
   */
  virtual void setToEnd() = 0;

  /**
   * @brief Does internal iterator points to the beginning of the chain?
   */
  virtual bool isAtBegin() const = 0;

  /**
   * @brief Does internal iterator points to the end of the chain?
   */
  virtual bool isAtEnd() const = 0;

  /**
   * @brief Is there a point after the current point?
   */
  virtual bool hasNext() const = 0;

  /**
   * @brief Is there a point before the current point?
   */
  virtual bool hasPrevious() const = 0;

  /**
   * @brief Move to next point, that becomes the current point.
   */
  virtual void moveNext() = 0;

  /**
   * @brief Move to previous point, that becomes the current point.
   */
  virtual void movePrevious() = 0;

  //@}


  /** @name Access to points */
  //        ================
  //@{

  /**
   * @brief Get the first point.
   */
  virtual const GenPoint<value_type>& accessFront() const = 0;

 /**
   * @brief Get a copy of the first point.
   */
  virtual GenPoint<value_type> front() const = 0;

  /**
   * @brief Get the last point.
   */
  virtual const GenPoint<value_type>& accessBack() const = 0;

  /**
   * @brief Get a copy of the last point.
   */
  virtual GenPoint<value_type> back() const = 0;

  /**
   * @brief Get the current point.
   */
  virtual const GenPoint<value_type>& accessCurrent() const = 0;

  /**
   * @brief Get a copy of the current point.
   */
  virtual GenPoint<value_type> current() const = 0;

  /**
   * @brief Get the successor of the current point.
   */
  virtual const GenPoint<value_type>& accessNext() = 0;

  /**
   * @brief Get a copy of the successor of the current point.
   */
  virtual GenPoint<value_type> next() = 0;

  /**
   * @brief Get the predecessor of the current point.
   */
  virtual const GenPoint<value_type>& accessPrevious() = 0;

  /**
   * @brief Get a copy of the predecessor of the current point.
   */
  virtual GenPoint<value_type> previous() = 0;

  //@}


  /** @name Insertion */
  //        =========
  //@{

  /**
   * @brief Insert a point at the beginning of the chain.
   * @param aPt  a point
   *
   * The internal iterator remains valid after the operation.
   */
  virtual void push_front(const GenPoint<value_type>& aPt) = 0;

  /**
   * @brief Insert a point at the end of the chain.
   * @param aPt  a point
   *
   * The internal iterator remains valid after the operation.
   */
  virtual void push_back(const GenPoint<value_type>& aPt) = 0;

  //@}


  /** @name Transformations */
  //        ===============
  //@{

  /**
   * @brief Reverse the order of elements in the list.
   *
   * The internal iterator remains valid once the operation is completed.
   */
  virtual void reverse() = 0;

//  /**
//   * @brief Insert the elements of a given chain at the end of current chain.
//   * @param aPtChain  a chain of points
//   *
//   * The internal iterator remains valid once the operation is completed.
//   */
//  virtual void merge(AbstractGenPointChain<T>* aPtChain) = 0;

  //@}


  /** @name Conversions */
  //        ===========
  //@{

  /**
   * @brief Get a (STL) list of the points of the chain.
   */
  virtual std::list< GenPoint<value_type> > toPointList() const = 0;

  //@}


// -------------------------------------------------------------------

}; // class AbstractGenPointChain


} // namespace qgar




// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// F U N C T I O N    M E M B E R S    I M P L E M E N T A T I O N
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII

#include "AbstractGenPointChain.tcc"

// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII




// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// P R E D E F I N E D    C H A I N    T Y P E S
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


namespace qgar
{


/** @name Abstract point chain type names */
//        ===============================
//@{

/**
 * @ingroup DS_POINT
 *
 * @brief Abstract chain of points with <b>integer</b> coordinates.
 *
 * @see qgar::IChain
 */
typedef AbstractGenPointChain<int> AbstChain;

/** 
 * @ingroup DS_POINT
 *
 * @brief Abstract chain of points with <b>integer</b> coordinates.
 *
 * @see Chain
 */
typedef AbstractGenPointChain<int> IAbstChain;

/**
 * @ingroup DS_POINT
 *
 * @brief Abstract chain of points with <b>float</b> coordinates.
 */
typedef AbstractGenPointChain<float> FAbstChain;

/**
 * @ingroup DS_POINT
 *
 * @brief Abstract chain of points with <b>double</b> coordinates.
 */
typedef AbstractGenPointChain<double> DAbstChain;

//@}


// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT

} // namespace qgar


#endif /* __ABSTRACTGENPOINTCHAIN_H_INCLUDED__ */
