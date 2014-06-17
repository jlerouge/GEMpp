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


/**
 * @file FreemanChain.cpp
 *
 * @brief Implementation of class qgar::FreemanChain.
 *
 * See file FreemanChain.h for the interface.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   December 19, 2003  17:30
 * @since  Qgar 2.1.1
 */



// STD
#include <cstdlib>
#include <list>
// QGAR
#include "FreemanChain.h"
#include "FreemanCode.h"
#include "image.h"
#include "primitives.h"
#include "QgarErrorDeveloper.h"



using namespace std;


namespace qgar
{


// -------------------------------------------------------------------
// C O N S T R U C T O R S 
// -------------------------------------------------------------------


// ___________________________________________________________________
//
// WARNING: the default constructor belongs to the private section
// so that clients cannot use it

FreemanChain::FreemanChain()
{
  throw QgarErrorDeveloper(__FILE__, __LINE__,
			   "qgar::FreemanChain::FreemanChain()",
			   "Disabled constructor: should not be used!");
}
// ___________________________________________________________________



// COPY CONSTRUCTOR

FreemanChain::FreemanChain(const FreemanChain& aFreemanCh)

  : chain_  (aFreemanCh.chain_),
    first_  (aFreemanCh.first_),
    current_(aFreemanCh.current_),
    last_   (aFreemanCh.last_)

{
  // Set the iterator to the beginning of the chain
  iter_ = chain_.begin();
}


// CONSTRUCT FROM A POINT

FreemanChain::FreemanChain(const GenPoint<int>& aPt)

  : chain_  (1, FreemanCode(QGE_DIRECTION_N, 0)),
    first_  (aPt),
    current_(aPt),
    last_   (aPt)

{
  // Set the iterator to the beginning of the chain
  iter_ = chain_.begin();
}


// CONSTRUCT FROM A POINT, A DIRECTION AND A LENGTH

FreemanChain::FreemanChain(const GenPoint<int>& aPt,
			   QGEdirection aDir,
			   unsigned int aLength)

  : chain_(1, FreemanCode(QGE_DIRECTION_N, 0)),
    first_(aPt)

{
  // Set the iterator to the beginning of the chain
  iter_ = chain_.begin();

  FreemanCode code(aDir, aLength);
  // Second point
  chain_.push_back(code);
  current_ = code.toPoint(aPt);
  last_ = current_;
  iter_++;
}


// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------


FreemanChain::~FreemanChain()
{
  // VOID
}


// -------------------------------------------------------------------
// A C C E S S   T O   C H A I N   C H A R A C T E R I S T I C S 
// -------------------------------------------------------------------


// IS CURRENT CHAIN EMPTY?

bool
FreemanChain::empty() const
{
  return chain_.empty();
}


// CHAIN LENGTH (NUMBER OF POINTS)

int
FreemanChain::size() const
{
  return chain_.size();
}


// -------------------------------------------------------------------
// I T E R A T O R 
// -------------------------------------------------------------------


// MAKE THE INTERNAL ITERATOR POINT TO THE FIRST POINT OF THE CHAIN,
// THAT BECOMES THE CURRENT POINT

void
FreemanChain::setToBegin()
{ 
  iter_ = chain_.begin();
  current_ = first_;
}


// MAKE THE INTERNAL ITERATOR POINT TO THE LAST POINT OF THE CHAIN,
// THAT BECOMES THE CURRENT POINT

void
FreemanChain::setToEnd()
{
  iter_ = chain_.end();
  iter_--;
  current_ = last_;
}


// DOES INTERNAL ITERATOR POINTS TO THE BEGINNING OF THE CHAIN?

bool
FreemanChain::isAtBegin() const
{
  return iter_ == chain_.begin();
}


// DOES INTERNAL ITERATOR POINTS TO THE END OF THE CHAIN?

bool
FreemanChain::isAtEnd() const
{
  return iter_ == chain_.end();
}


// IS THERE A POINT AFTER THE CURRENT POINT?

bool
FreemanChain::hasNext() const
{
  std::list<FreemanCode>::iterator itAux = iter_;
  return (++itAux != chain_.end());
}


// IS THERE A POINT BEFORE THE CURRENT POINT?

bool
FreemanChain::hasPrevious() const
{
  return (iter_ != chain_.begin());
}


// MOVE TO NEXT POINT, THAT BECOMES THE CURRENT POINT

void
FreemanChain::moveNext()
{

  iter_++;
  current_ = iter_->toPoint(current_);
}


// MOVE TO PREVIOUS POINT, THAT BECOMES THE CURRENT POINT

void
FreemanChain::movePrevious()
{
  current_ = iter_->toOppositePoint(current_);
  iter_--;
}


// -------------------------------------------------------------------
// A C C E S S   T O   F R E E M A N   C O D E S
// -------------------------------------------------------------------


// GET THE (STL) LIST OF FREEMAN CODES

const std::list<FreemanCode>&
FreemanChain::accessCodesList() const
{
  return chain_;
}


// -------------------------------------------------------------------
// A C C E S S   T O   P O I N T S 
// -------------------------------------------------------------------


// GET THE FIRST POINT

const GenPoint<int>&
FreemanChain::accessFront() const
{
  return first_;
}

// GET A COPY OF THE FIRST POINT

GenPoint<int>
FreemanChain::front() const
{
  return first_;
}

// GET THE LAST POINT

const GenPoint<int>&
FreemanChain::accessBack() const
{
  return last_;
}

// GET A COPY OF THE LAST POINT

GenPoint<int>
FreemanChain::back() const
{
  return last_;
}

// GET THE CURRENT POINT

const GenPoint<int>&
FreemanChain::accessCurrent() const
{
  return current_;
}

// GET A COPY OF THE CURRENT POINT

GenPoint<int>
FreemanChain::current() const
{
  return current_;
}

// GET THE SUCCESSOR OF THE CURRENT POINT

const GenPoint<int>&
FreemanChain::accessNext()
{
  moveNext();
  return current_;
}

// GET A COPY OF THE SUCCESSOR OF THE CURRENT POINT

GenPoint<int>
FreemanChain::next()
{
  moveNext();
  return current_;
}

// GET THE PREDECESSOR OF THE CURRENT POINT

const GenPoint<int>&
FreemanChain::accessPrevious()
{
  movePrevious();
  return current_;
}

// GET A COPY OF THE PREDECESSOR OF THE CURRENT POINT

GenPoint<int>
FreemanChain::previous()
{
  movePrevious();
  return current_;
}


// -------------------------------------------------------------------
// I N S E R T I O N 
// -------------------------------------------------------------------


// INSERT A POINT AT THE BEGINNING OF THE CHAIN
//
// WARNING
// - When the chain is not empty, the new point is supposed
//   to be consistent with the coding of the chain: All the points
//   of the segment joining the first point of the chain to the
//   new point must be strictly aligned along one of the 8 Freeman
//   directions.
// - A new point is always inserted in the chain, even when
//   the given point is the same as the first point of the chain
//   or is aligned with the first segment of the chain.

void
FreemanChain::push_front(const GenPoint<int>& aPt)
{
 if (chain_.empty())
    {
      // EMPTY CHAIN
      // -----------

      // Insert new point in chain
      chain_.push_back(FreemanCode(QGE_DIRECTION_N, 0));
      // Update first, current and last points in chain
      first_   = aPt;
      current_ = aPt;
      last_    = aPt;
      // Set iterator to the beginning of chain
      iter_ = chain_.begin();
    }
  else
    {
      // NON-EMPTY CHAIN
      // ---------------
      
      int dx = aPt.x() - first_.x();
      int dy = aPt.y() - first_.y();

      // Insert new point as the beginning of the chain
      FreemanCode& code = chain_.front();
      code.setDirLength(qgDirection(dx, dy), (dx == 0) ? abs(dy) : abs(dx));

      // New beginning of the list representing the chain
      chain_.push_front(FreemanCode(QGE_DIRECTION_N, 0));
      // Update first point in chain
      first_ = aPt;
    }
}


// INSERT A POINT DEFINED BY A FREEMAN CODE
// AT THE BEGINNING OF THE CHAIN
//
// WARNING
// - The chain is supposed not to be empty.
// - A new point is always inserted in the chain, even when
//   the direction of the given Freeman code is the same as
//   the direction of the first Freeman code of the chain, or when
//   it is the opposite of the direction of the first Freeman code
//   of the chain.

void
FreemanChain::push_front(const FreemanCode& aCode)
{
  // Insert new point as the beginning of the chain
  FreemanCode& code = chain_.front();
  code.setDirLength(qgOpposite(aCode.direction()), aCode.length());

  // New beginning of the list representing the chain
  chain_.push_front(FreemanCode(QGE_DIRECTION_N, 0));

  // Update first point in chain
  first_ = aCode.toPoint(first_);
}


// INSERT A POINT AT THE END OF THE CHAIN
//
// WARNING
// - When the chain is not empty, the new point is supposed
//   to be consistent with the coding of the chain: All the points
//   of the segment joining the last point of the chain to the
//   new point must be strictly aligned along one of the 8 Freeman
//   directions.
// - A new point is always inserted in the chain, even when
//   the given point is the same as the last point of the chain
//   or is aligned with the last segment of the chain.

void
FreemanChain::push_back(const GenPoint<int>& aPt)
{
  if (chain_.empty())
    {
      // EMPTY CHAIN
      // -----------
      // Insert new point in chain
      chain_.push_back(FreemanCode(QGE_DIRECTION_N, 0));
      // Update first, current and last points in chain
      first_   = aPt;
      current_ = aPt;
      last_    = aPt;
      // Update iterator
      iter_ = chain_.begin();
    }
  else
    {
      // NON-EMPTY CHAIN
      // ---------------
      
      int dx = last_.x() - aPt.x();
      int dy = last_.y() - aPt.y();

      // Insert new point as the end of the chain
      chain_.push_back
	(FreemanCode(qgDirection(dx, dy), (dx == 0) ? abs(dy) : abs(dx)));
      // Update last point in chain
      last_ = aPt;
    }
}


// INSERT A POINT DEFINED BY A FREEMAN CODE AT THE END OF THE CHAIN
//
// @warning
// - The chain is supposed not to be empty.
// - A new point is always inserted in the chain, when
//   the direction of the given Freeman code is the same as
//   the direction of the last Freeman code of the chain, or when
//   it is the opposite of the direction of the last Freeman code
//   of the chain.

void
FreemanChain::push_back(const FreemanCode& aCode)
{
  chain_.push_back(aCode);
  // Update last point
  last_ = aCode.toPoint(last_);
}


// -------------------------------------------------------------------
// T R A N S F O R M A T I O N S 
// -------------------------------------------------------------------


// REVERSE ELEMENTS ORDER IN THE CHAIN
// NOTHING TO DO IF THE CHAIN DOES NOT INCLUDE AT LEAST TWO POINTS

void
FreemanChain::reverse()
{
  int chLg = chain_.size();
  if (chLg > 1)
    {
// Starting from both ends of the chain (first element excepted),
// swap elements after having changed each direction for its opposite.
//
//              +-----+    +----+    +----+     +----+    +----+
// first_ = P0  |North|    | D1 |    | D2 |     |Dn-1|    | Dn |
// last_  = Pn  +-----+<==>+----+<==>+----+ ... +----+<==>+----+
//              |  0  |    | L1 |    | L2 |     |Ln-1|    | Ln |
//              +-----+    +----+    +----+     +----+    +----+
//                           ^                               ^
//                           |       dx = opposite(Dx)       |
//                           |_______________________________|
//                                           |
//                                           V
//              +-----+    +----+    +----+     +----+    +----+
// first_ = Pn  |North|    | dn |    |dn-1|     | d2 |    | d1 |
// last_  = P0  +-----+<==>+----+<==>+----+ ... +----+<==>+----+
//              |  0  |    | Ln |    |Ln-1|     | L2 |    | L1 |
//              +-----+    +----+    +----+     +----+    +----+

      QGEdirection dir;
      int lg;

      int iCntEnd = (chLg - 1) / 2;

      std::list<FreemanCode>::iterator it = chain_.begin();
      it++;
      std::list<FreemanCode>::iterator itRev = chain_.end();
      itRev--;

      for (int iCnt = 1 ; iCnt <= iCntEnd ; iCnt++, it++, itRev--)
	{
	  dir = qgOpposite(it->direction());
	  lg  = it->length();

	  it->setDirLength(qgOpposite(itRev->direction()), itRev->length());
	  itRev->setDirLength(dir, lg);
	}

      // Invert direction of the last element if necessary
      if (((chLg + 1) % 2) == 1)
	{
	  it->setDir(qgOpposite(it->direction()));
	}

      // Update first and last points
      int x = last_.x();
      int y = last_.y();
      last_ = first_;
      first_.setXY(x, y);

      // Update current point
      current_ = first_;
      it = chain_.begin();
      bool loop = true;
      while (loop)
	{
	  current_ = it->toPoint(current_);

	  if (it == iter_)
	    {
	      loop = false;
	    }
	  else
	    {
	      it++;
	    }
	} // END while
    }
}


// -------------------------------------------------------------------
// C O N V E R S I O N S 
// -------------------------------------------------------------------


// CONVERT INTO A (STL) LIST OF POINTS HAVING INTEGER COORDINATES

std::list< GenPoint<int> >
FreemanChain::toPointList() const
{
  std::list< GenPoint<int> > ptList;
  GenPoint<int> pt = first_;

  for (std::list<FreemanCode>::const_iterator itCh = chain_.begin();
       itCh != chain_.end();
       ++itCh)
    {
      pt = itCh->toPoint(pt);
      ptList.push_back(pt);
    }

  return ptList;
}

// CONVERT INTO A (STL) LIST OF POINTS HAVING FLOAT COORDINATES

std::list< GenPoint<float> >
FreemanChain::toFPointList() const
{
  std::list< GenPoint<float> > ptList;
  GenPoint<float> pt = (GenPoint<float>)first_;

  for (std::list<FreemanCode>::const_iterator itCh = chain_.begin();
       itCh != chain_.end();
       ++itCh)
    {
      pt = itCh->toPoint(pt);  // Implicit conversion
      ptList.push_back(pt);
    }

  return ptList;
}

// CONVERT INTO A (STL) LIST OF POINTS HAVING DOUBLE COORDINATES

std::list< GenPoint<double> >
FreemanChain::toDPointList() const
{
  std::list< GenPoint<double> > ptList;
  GenPoint<double> pt = (GenPoint<double>)first_;

  for (std::list<FreemanCode>::const_iterator itCh = chain_.begin();
       itCh != chain_.end();
       ++itCh)
    {
      pt = itCh->toPoint(pt);  // Implicit conversion
      ptList.push_back(pt);
    }

  return ptList;
}


// -------------------------------------------------------------------
// O P E R A T O R S 
// -------------------------------------------------------------------


// ASSIGNMENT

FreemanChain&
FreemanChain::operator=(const FreemanChain& aFreemanCh)
{
  // Are left hand side and right hand side different objects?
  if (this != &aFreemanCh)
    {
      chain_ = aFreemanCh.chain_;
      // Set iterator to the beginning of the chain
      iter_ = chain_.begin();

      first_   = aFreemanCh.first_;
      current_ = aFreemanCh.current_;
      last_    = aFreemanCh.last_;
    }

  return *this;
}


// -------------------------------------------------------------------


} // namespace qgar
