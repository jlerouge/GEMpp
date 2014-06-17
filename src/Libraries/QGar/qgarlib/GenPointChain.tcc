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
 * @file GenPointChain.tcc
 *
 * @brief Implementation of function members of class qgar::GenPointChain.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   January 27, 2005  22:22
 * @since  Qgar 2.2
 */



// STD
#include <list>
// QGAR
#include "primitives.h"



namespace qgar
{


// -------------------------------------------------------------------
// C O N S T R U C T O R S
// -------------------------------------------------------------------


// DEFAULT CONSTRUCTOR

template <class T>
GenPointChain<T>::GenPointChain() : _chain()
{
  // Set iterator to end of chain
  _iter = _chain.end();
}


// COPY CONSTRUCTOR

template <class T>
GenPointChain<T>::GenPointChain(const GenPointChain<T>& aPtChain)

  : _chain(aPtChain._chain)

{
  // Set the iterator to the beginning of the chain
  _iter = _chain.begin();
}


// CONSTRUCT FROM A GIVEN POINT

template <class T>
GenPointChain<T>::GenPointChain(const GenPoint<T>& aPoint) 

  : _chain()

{
  _chain.push_back(aPoint);
  // Set iterator to the beginning of the chain
  _iter = _chain.begin();
}


// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------


template <class T>
GenPointChain<T>::~GenPointChain()
{
  // VOID
}


// -------------------------------------------------------------------
// A C C E S S   T O   C H A I N   C H A R A C T E R I S T I C S
// -------------------------------------------------------------------


// IS CURRENT CHAIN EMPTY?

template <class T>
bool
GenPointChain<T>::empty() const
{
  return _chain.empty();
}


// GET CHAIN SIZE (number of points)

template <class T>
int
GenPointChain<T>::size() const
{
  return _chain.size();
}


// -------------------------------------------------------------------
// I T E R A T O R
// -------------------------------------------------------------------


// SET ITERATOR TO THE FIRST POINT IN CHAIN

template <class T>
void GenPointChain<T>::setToBegin()
{
  _iter = _chain.begin();
}


// SET ITERATOR TO THE LAST POINT IN CHAIN

template <class T>
void GenPointChain<T>::setToEnd()
{
  _iter = _chain.end();
  --_iter;
}


// IS THERE A POINT AFTER THE CURRENT POINT?

template <class T>
bool
GenPointChain<T>::hasNext() const
{
  typename std::list< GenPoint<T> >::iterator itAux = _iter;
  return (++itAux != _chain.end());
}


// IS THERE A POINT BEFORE THE CURRENT POINT?

template <class T>
bool
GenPointChain<T>::hasPrevious() const
{
  return (_iter != _chain.begin());
}


// DOES INTERNAL ITERATOR POINTS TO THE BEGINNING OF THE CHAIN?

template <class T>
bool
GenPointChain<T>::isAtBegin() const
{
  return _iter == _chain.begin();
}


// DOES INTERNAL ITERATOR POINTS TO THE END OF THE CHAIN?

template <class T>
bool
GenPointChain<T>::isAtEnd() const
{
  return _iter == _chain.end();
}


// INCREMENT ITERATOR

template <class T>
void GenPointChain<T>::moveNext()
{
  ++_iter;
}


// DECREMENT ITERATOR

template <class T>
void GenPointChain<T>::movePrevious()
{
  --_iter;
}


// -------------------------------------------------------------------
// A C C E S S   T O   P O I N T S
// -------------------------------------------------------------------


// GET FIRST POINT

template <class T>
const GenPoint<T>&
GenPointChain<T>::accessFront() const
{
  return _chain.front();
}

// GET A COPY OF THE FIRST POINT

template <class T>
GenPoint<T>
GenPointChain<T>::front() const
{
  return _chain.front();
}

// GET LAST POINT

template <class T>
const GenPoint<T>&
GenPointChain<T>::accessBack() const
{
  return _chain.back();
}

// GET A COPY OF THE LAST POINT

template <class T>
GenPoint<T> GenPointChain<T>::back() const
{
  return _chain.back();
}


// GET THE CURRENT POINT

template <class T>
const GenPoint<T>&
GenPointChain<T>::accessCurrent() const
{
  return *_iter;
}


// GET A COPY OF THE CURRENT POINT

template <class T>
GenPoint<T> GenPointChain<T>::current() const
{
  return *_iter;
}


// GET THE SUCCESSOR OF THE CURRENT POINT

template <class T>
const GenPoint<T>&
GenPointChain<T>::accessNext()
{
  _iter++;
  return *_iter;
}

// GET A COPY OF THE SUCCESSOR OF THE CURRENT POINT

template <class T>
GenPoint<T>
GenPointChain<T>::next()
{
  _iter++;
  return *_iter;
}


// GET THE PREDECESSOR OF THE CURRENT POINT

template <class T>
const GenPoint<T>&
GenPointChain<T>::accessPrevious()
{
  _iter--;
  return *_iter;
}


// GET A COPY OF THE PREDECESSOR OF THE CURRENT POINT

template <class T>
GenPoint<T> GenPointChain<T>::previous()
{
  _iter--;
  return *_iter;
}


// -------------------------------------------------------------------
// A C C E S S   T O   T H E   L I S T   O F   P O I N T S
// -------------------------------------------------------------------


// GET THE STL LIST IMPLEMENTING THE CHAIN OF POINTS

template <class T>
inline const std::list< GenPoint<T> >&
GenPointChain<T>::accessPointList() const
{
  return _chain;
}


// GET THE STL LIST IMPLEMENTING THE CHAIN OF POINTS
// The result is not const

template <class T>
inline std::list< GenPoint<T> >&
GenPointChain<T>::pointList()
{
  return _chain;
}


// -------------------------------------------------------------------
// I N S E R T I O N
// -------------------------------------------------------------------


// INSERT A POINT AT THE BEGINNING OF THE CHAIN

template <class T>
void GenPointChain<T>::push_front(const GenPoint<T>& aPt)
{
  _chain.push_front(aPt);
}


// INSERT A POINT AT THE END OF THE CHAIN

template <class T>
void GenPointChain<T>::push_back(const GenPoint<T>& aPt)
{
  _chain.push_back(aPt);
}


// -------------------------------------------------------------------
// T R A N S F O R M A T I O N S
// -------------------------------------------------------------------


// REVERSE THE ORDER OF THE POINTS IN THE LIST

template <class T>
void GenPointChain<T>::reverse()
{
  _chain.reverse();
}


// -------------------------------------------------------------------
// C O N V E R S I O N S
// -------------------------------------------------------------------


// CONVERT INTO A STL LIST OF POINTS

template <class T>
std::list< GenPoint<T> >
GenPointChain<T>::toPointList() const
{
  return _chain;
}


// -------------------------------------------------------------------
// O P E R A T O R S
// -------------------------------------------------------------------


// ASSIGNMENT

template <class T>
GenPointChain<T>&
GenPointChain<T>::operator=(const GenPointChain<T>& aPtChain)
{
  // Are left hand side and right hand side different objects?
  if (this != &aPtChain)
    {
      _chain = aPtChain._chain;

      // Set the iterator to the beginning of the chain
      _iter = _chain.begin();
    }

  return *this;
}


// -------------------------------------------------------------------


} // namespace qgar
