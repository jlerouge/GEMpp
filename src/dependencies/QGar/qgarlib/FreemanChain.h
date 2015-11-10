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


#ifndef __FREEMANCHAIN_H_INCLUDED__
#define __FREEMANCHAIN_H_INCLUDED__


/**
 * @file FreemanChain.h
 *
 * @brief Header file of class qgar::FreemanChain.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   December 19, 2003  17:30
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: FreemanChain.h,v 1.19 2007/02/14 17:34:04 masini Exp $ */



// STD
#include <list>
// QGAR
#include "AbstractGenPointChain.h"
#include "FreemanCode.h"
namespace qgar
{
  // Avoid #include's when not necessary
  template <class T> class GenPoint;
}



namespace qgar
{


/**
 * @ingroup DS_POINT
 *
 * @class FreemanChain FreemanChain.h "qgarlib/FreemanChain.h"
 *
 * @brief Chain of Freeman codes.
 *
 * A Freeman chain represents a series of consecutive points,
 * <b>in an integer (<i>i.e.</i> discrete) coordinate system</b>.
 * It is coded as a series of <b>integer</b> vectors,
 * defined by pairs (direction, length), starting from a point
 * of given coordinates:
@verbatim
                                     etc.
                                      *
                                     *
                            POINT-2 @ ^
                                    * |
                                    * |
                                  ^ * |
                                  | * |
                      DIRECTION-2 | * LENGTH-2
                                  | * |
                                    * |
                                    * |
  (STARTING)      DIRECTION-1 -->   * |
    POINT-0  @**********************@ V
             <------ LENGTH-1 ------> POINT-1
@endverbatim
 *
 * A direction is coded using predefined enum type qgar::QGEdirection.
 * As the origin of the coordinates system in images is at top left
 * corner, North and South are upside down for more convenience:
@verbatim
  (0,0) +---------------------------------------------> X
        |
        |                 QGE_DIRECTION_N
        |                        |  
        |     QGE_DIRECTION_NW \ | / QGE_DIRECTION_NE
        |                       \|/
        |   QGE_DIRECTION_W -----+----- QGE_DIRECTION_E
        |                       /|\
        |     QGE_DIRECTION_SW / | \ QGE_DIRECTION_SE
        |                        |
        |                 QGE_DIRECTION_S
      Y V
@endverbatim
 *
 * A Freeman chain is implemented using a STL list of Freeman codes,
 * instances of class qgar::FreemanCode:
@verbatim
                                     _iter  (current point)
                                       |
                                       V
               +-----+    +----+    +----+             +----+
               |North|    | D1 |    | D2 |             | Dn |
     _chain    +-----+<==>+----+<==>+----+<==> ... <==>+----+
               |  0  |    | L1 |    | L2 |             | Ln |
               +-----+    +----+    +----+             +----+

@endverbatim
 * The direction of the first code is always North (qgar::QGE_DIRECTION_N,
 * the first value of the qgar::QGEdirection predefined enum type)
 * and the length of the first code is always <b>0</b>: The first code
 * represents the first point of the chain (a null vector from the given
 * starting point). In this way, the complete chain of points is
 * consistently coded, which allows easier algorithm implementations.
 *
 * An (internal) iterator, qgar::FreemanChain::_iter, allows bidirectional
 * traversal of the chain. The validity of the iterator is preserved by any
 * legal operation on the chain, unless the chain is empty.
 *
 * Three points are permanently available as effective points, <i>i.e.</i>
 * instances of class qgar::GenPoint<int>:
 * - the starting/first point of the chain (qgar::FreemanChain::_first),
 * - the current point of the chain (qgar::FreemanChain::_current),
 *   that is pointed by iterator qgar::FreemanChain::_iter
 * - the last point of the chain (qgar::FreemanChain::_last)
 *
 * Use cases of a Freeman chain:
 * - To set the iterator to the beginning (resp. end) of the chain,
 *   function qgar::FreemanChain::setToBegin
 *   (resp. qgar::FreemanChain::setToEnd)
 * - To test if the iterator points to the beginning (resp. end)
 *   of the chain, function qgar::FreemanChain::isAtBegin
 *   (resp. qgar::FreemanChain::isAtEnd)
 * - To test if the chain includes at least one point after (resp. before)
 *   the current point,  function qgar::FreemanChain::hasNext
 *   (resp. qgar::FreemanChain::hasPrevious)
 * - To move to the next (resp. previous) point, function
 *   qgar::FreemanChain::moveNext (resp. qgar::FreemanChain::movePrevious)
 * - To get the current point, functions qgar::FreemanChain::current
 *   or qgar::FreemanChain::accessCurrent
 * - To get the next (resp. previous) point, functions
 *   qgar::FreemanChain::next or qgar::FreemanChain::accessNext
 *   (resp. qgar::FreemanChain::previous or qgar::FreemanChain::accessPrevious)
 * - To insert a new point at the beginning (resp. end) of the chain,
 *   function qgar::FreemanChain::push_front
 *   (resp. qgar::FreemanChain::push_back)
 *
 *
 * @warning
 * No default constructor is provided.
 *
 * @warning
 * <b>A Freeman chain is not an appropriate way of representing
 * a chain of points if efficiency is required for insertions or chain
 * traversals.</b> Class qgar::GenPointChain should be better used in this
 * case. A STL list of the points coded by a Freeman chain can be also
 * obtained using function qgar::FreemanChain::pointList.
 *
 *
 * @author  <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>,
 *          from previous work by Karl Tombre
 * @date    December 19, 2003  17:30
 * @since   Qgar 2.1.1
 */
class FreemanChain

  : public AbstractGenPointChain<int>

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  /** @name Constructors */
  //        ============
  //@{

  /**
   * @brief Construct from a point, which becomes the current point.
   *
   * @param aPt  a point (integer coordinates)
   *
   * The iterator points to this point.
   */
  explicit FreemanChain(const GenPoint<int>& aPt);

  /**
   * @brief Construct from given point, direction and length.
   *
   * The iterator points to the end of the chain.
   *
   * @param aPt       a point (integer coordinates)
   * @param aDir      direction code of the initial part of chain
   * @param aLength   length of the initial part of chain
   *
   * @warning The given length is supposed to be different from zero.
   * Otherwise, the validity of the resulting chain is absolutely not
   * guaranteed.
   */
  FreemanChain(const GenPoint<int>& aPt,
	       QGEdirection aDir,
	       unsigned int aLength);

  /**
   * @brief Copy constructor.
   *
   * @param aFreemanCh  a Freeman chain
   *
   * @warning The iterator points to the beginning of the chain.
   */
  FreemanChain(const FreemanChain& aFreemanCh);

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  virtual ~FreemanChain();

  //@}


  /** @name Access to chain characteristics */
  //        ===============================
  //@{

  /**
   * @brief Is current chain empty?
   */
  virtual bool empty() const;
  
  /**
   * @brief Get chain length (number of points).
   */
  virtual int size() const;

  //@}


  /** @name Iterator */
  //        ========
  //@{

  /**
   * @brief Make the internal iterator point to the beginning
   *        (first point) of the chain, that becomes the current point.
   *
   * @warning The chain is supposed not to be empty.
   */
  virtual void setToBegin();

  /**
   * @brief Make the internal iterator point to the end
   *        (last point) of the chain, that becomes the current point.
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
   * @brief Get the first point.
   *
   * @warning The chain is supposed not to be empty.
   */
  virtual const GenPoint<int>& accessFront() const;

  /**
   * @brief Get a copy of the first point.
   *
   * @warning The chain is supposed not to be empty.
   */
  virtual GenPoint<int> front() const;

  /**
   * @brief Get the last point.
   *
   * @warning The chain is supposed not to be empty.
   */
  virtual const GenPoint<int>& accessBack() const;

  /**
   * @brief Get a copy of the last point.
   *
   * @warning The chain is supposed not to be empty.
   */
  virtual GenPoint<int> back() const;

  /**
   * @brief Get the current point.
   *
   * @warning The chain is supposed not to be empty.
   */
  virtual const GenPoint<int>& accessCurrent() const;

  /**
   * @brief Get a copy of the current point.
   *
   * @warning The chain is supposed not to be empty.
   */
  virtual GenPoint<int> current() const;

  /**
   * @brief Get the successor of the current point.
   *
   * @warning The chain is supposed not to be empty,
   * and the iterator is supposed not to point to the last point.
   */
  virtual const GenPoint<int>& accessNext();

  /**
   * @brief Get a copy of the successor of the current point.
   *
   * @warning The chain is supposed not to be empty,
   * and the iterator is supposed not to point to the last point.
   */
  virtual GenPoint<int> next();

  /**
   * @brief Get the predecessor of the current point.
   *
   * @warning The chain is supposed not to be empty,
   * and the iterator is supposed not to point to the first point.
   */
  virtual const GenPoint<int>& accessPrevious();

  /**
   * @brief Get a copy of the predecessor of the current point.
   *
   * @warning The chain is supposed not to be empty,
   * and the iterator is supposed not to point to the first point.
   */
  virtual GenPoint<int> previous();

  //@}


  /** @name Access to Freeman codes */
  //        =======================
  //@{

  /**
   * @brief Get the (STL) list of Freeman codes.
   *
   * The first element is an extra code including <b>qgar::QGE_DIRECTION_N</b>
   * as direction and <b>0</b> as length:
@verbatim
+-----+      +----+      +----+               +----+
|North|      | D1 |      | D2 |               | Dn |
+-----+ <==> +----+ <==> +----+ <==> ... <==> +----+
|  0  |      | L1 |      | L2 |               | Ln |
+-----+      +----+      +----+               +----+
@endverbatim
   * This implementation allows an easier implementation of algorithms.
   *
   * Using this function to traverse the chain is much more efficient
   * than using appropriate member functions like
   * qgar::FreemanChain::setToBegin, qgar::FreemanChain::hasNext,
   * qgar::FreemanChain::moveNext, etc. In particular, the points
   * represented by the chain may be obtained by applying the successive
   * Freeman codes of the chain to a point initialized to the first point
   * of the chain, in the following way:
@code
const std::list<FreemanCode>& lFC = myChain.accessCodesList();
GenPoint<int> p = myChain.first();

for (std::list<FreemanCode>::const_iterator it = lFC.begin();
     it != lFC.end();
     ++it)
  {
    // Current point
    p = (*it).toPoint(p);

    // Processing...
    ...
  }
@endcode
   */
  const std::list<FreemanCode>& accessCodesList() const;

  //@}


  /** @name Insertion */
  //        =========
  //@{

  /**
   * @brief Insert a point at the beginning of the chain.
   *
   * @param aPt  a point
   *
   * @warning
   * - <b>When the chain is not empty, the new point is supposed
   *   to be consistent with the coding of the chain: All the points
   *   of the segment joining the first point of the chain to the
   *   new point must be strictly aligned along one of the 8 Freeman
   *   directions.</b>
   * - <b>A new point is always inserted in the chain, even when
   *   the given point is the same as the first point of the chain
   *   or is aligned with the first segment of the chain.</b>
   */
  virtual void push_front(const GenPoint<int>& aPt);

  /**
   * @brief Insert a point whose location is defined by the given
   *        Freeman code, starting from the first point of the chain.
   *
   * @param aCode  a Freeman code
   *
   * @warning
   * - <b>The chain is supposed not to be empty.</b>
   * - <b>A new point is always inserted in the chain, even when
   *   the direction of the given Freeman code is the same as
   *   the direction of the first Freeman code of the chain, or when
   *   it is the opposite of the direction of the first Freeman code
   *   of the chain.</b> 
   */
  void push_front(const FreemanCode& aCode);

  /**
   * @brief Insert a point at the end of the chain.
   *
   * @param aPt  a point
   *
   * @warning
   * - <b>When the chain is not empty, the new point is supposed
   *   to be consistent with the coding of the chain: All the points
   *   of the segment joining the last point of the chain to the
   *   new point must be strictly aligned along one of the 8 Freeman
   *   directions.</b>
   * - <b>A new point is always inserted in the chain, even when
   *   the given point is the same as the last point of the chain
   *   or is aligned with the last segment of the chain.</b>
   */
  virtual void push_back(const GenPoint<int>& aPt);

  /**
   * @brief Insert a point whose location is defined by the given
   *        Freeman code, starting from the last point of the chain.
   *
   * @param aCode  a Freeman code
   *
   * @warning
   * - <b>The chain is supposed not to be empty.</b>
   * - <b>A new point is always inserted in the chain, when
   *   the direction of the given Freeman code is the same as
   *   the direction of the last Freeman code of the chain, or when
   *   it is the opposite of the direction of the last Freeman code
   *   of the chain.</b>
   */
  void push_back(const FreemanCode& aCode);

  //@}


  /** @name Transformations */
  //        ===============
  //@{

  /**
   * @brief Reverse elements order in the list.
   *
   * @warning The internal iterator points to the same <i>element</i>
   * of the chain (but the content of this element has changed) once
   * the operation is completed.
   */
  virtual void reverse();

  //@}


  /** @name Conversions */
  //        ===========
  //@{

  /**
   * @brief Convert into a (STL) list of points having integer coordinates.
   */
  virtual std::list< GenPoint<int> > toPointList() const;

  /**
   * @brief Convert into a (STL) list of points having float coordinates.
   */
  virtual std::list< GenPoint<float> > toFPointList() const;

  /**
   * @brief Convert into a (STL) list of points having double coordinates.
   */
  virtual std::list< GenPoint<double> > toDPointList() const;

  //@}


  /** @name Operators */
  //        =========
  //@{

  /**
   * @brief Assignment.
   *
   * @param aFreemanCh  a Freeman chain
   *
   * @warning The internal iterator points to the beginning of the chain.
   */
  FreemanChain& operator=(const FreemanChain& aFreemanCh);

  //@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:


  /** @name Representation of a Freeman chain */
  //        =================================
  //@{

  /**
   * @brief The (STL) list of Freeman codes
   * defining the points of the chain.
   */
  std::list<FreemanCode> chain_;

  /**
   * @brief Iterator on the list of Freeman codes.
   */
  std::list<FreemanCode>::iterator iter_;

  //@}


  /** @name Pre-computed points */
  //        ===================
  //@{

  /**
   * @brief First point of the chain.
   */
  GenPoint<int> first_;

  /**
   * @brief Current point of the chain.
   */
  GenPoint<int> current_;

  /**
   * @brief Last point of the chain.
   */
  GenPoint<int> last_;

  //@}


// -------------------------------------------------------------------
// P R I V A T E   M E M B E R S
// -------------------------------------------------------------------
private:


  /** @name Constructors */
  //        ============
  //@{

  /**
   * @brief Disabled default constructor.
   *
   * The default constructor belongs to the private section
   * so that clients cannot use it.
   */
  FreemanChain();

  //@}

// -------------------------------------------------------------------
}; // class FreemanChain


} // namespace qgar


#endif /* __FREEMANCHAIN_H_INCLUDED__ */
