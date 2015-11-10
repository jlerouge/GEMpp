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
 * @file GenMask2d.tcc
 *
 * @brief Implementation of function members of class qgar::GenMask2d.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   January 27, 2005  22:02
 * @since  Qgar 2.2
 */



// STD
#include <cstring>
// QGAR
#include "array.h"



namespace qgar
{


// -------------------------------------------------------------------
// C O N S T R U C T O R S
// -------------------------------------------------------------------


// DEFAULT CONSTRUCTOR

template <class T>
GenMask2d<T>::GenMask2d()

  : _pRefCnt(new int(0)),
    _width(0),
    _height(0),
    _pCoeffMap(0)

{
  // VOID
}


// COPY CONSTRUCTOR

template <class T>
GenMask2d<T>::GenMask2d(const GenMask2d<T>& aMask)

  : _pRefCnt(new int(0)),
    _width(aMask._width),
    _height(aMask._height)

{
  int size = _width * _height;
  _pCoeffMap = new T[size];

  memcpy(_pCoeffMap, aMask.pCoeffMap(), size * sizeof(T));
}


// INITIALIZE WITH GIVEN WIDTH, HEIGHT AND VALUE

template <class T>
GenMask2d<T>::GenMask2d(unsigned int aWidth,
			unsigned int aHeight,
			T aValue)

  : _pRefCnt(new int(0)),
    _width(aWidth),
    _height(aHeight)

{
  int size = _width * _height;
  _pCoeffMap = new T[size];
  qgFill(_pCoeffMap, size, aValue);
}


// INITIALIZE FROM A GIVEN ARRAY OF VALUES

template <class T>
GenMask2d<T>::GenMask2d(unsigned int aWidth,
			unsigned int aHeight,
			const T * const valArray)

  : _pRefCnt(new int(0)),
    _width(aWidth),
    _height(aHeight)

{
  int size = _width * _height;
  _pCoeffMap = new T[size];
  memcpy(_pCoeffMap, valArray, size * sizeof(T));
}


// SHALLOW COPY CONSTRUCTOR

template <class T>
GenMask2d<T>::GenMask2d(const GenMask2d& rhs, int)

  : _pRefCnt(rhs._pRefCnt),
    _width(rhs._width),
    _height(rhs._height),
    _pCoeffMap(rhs._pCoeffMap)

{
  (*_pRefCnt)++;
  
}


// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------


template <class T>
GenMask2d<T>::~GenMask2d()
{
  if (*_pRefCnt == 0)
    {
      // The space allocated to the coefficient map
      // is not shared with another object
      delete [] _pCoeffMap;
      delete _pRefCnt;
    }
  else
    {
      // The space allocated to the coefficient map is shared
      // with at least one other object: Just decrement
      // the reference counter
      (*_pRefCnt)--;
    }
}


// -------------------------------------------------------------------
// A C C E S S   T O   M A S K   C H A R A C T E R I S T I C S
// -------------------------------------------------------------------


// GET MASK WIDTH

template <class T>
inline int
GenMask2d<T>::width() const
{
  return _width;
}


// GET MASK HEIGHT

template <class T>
inline int
GenMask2d<T>::height() const
{
  return _height;
}


// -------------------------------------------------------------------
// A C C E S S   T O   C O E F F I C I E N T   V A L U E S
// -------------------------------------------------------------------


// GET A COEFFICIENT VALUE

template <class T>
T
GenMask2d<T>::coeff(int aX, int aY) const
{
  return *(_pCoeffMap + (aY * _width) + aX);
}


// -------------------------------------------------------------------
// ACCESS TO DIRECT TRANSFORMATIONS OF THE COEFFICIENT MAP
// -------------------------------------------------------------------


// GET THE POINTER TO THE COEFFICIENT MAP

template <class T>
inline T*
GenMask2d<T>::pCoeffMap() const
{
  return _pCoeffMap;
}


// -------------------------------------------------------------------
// T R A N S F O R M A T I O N
// -------------------------------------------------------------------


// SET COEFFICIENT AT GIVEN POSITION

template <class T>
void
GenMask2d<T>::setCoeff(int aX, int aY, T aCoeff)
{
  *(_pCoeffMap + (aY * _width) + aX) = aCoeff;
}


// -------------------------------------------------------------------
// C O P Y
// -------------------------------------------------------------------


// SHALLOW COPY: THE COEFFICIENT MAP OF THE SOURCE MASK IS NOT DUPLICATED
// When the copy is completed, the pixel map of the destination
// mask is the same memory space as the pixel map of the source mask

template <class T>
GenMask2d<T> GenMask2d<T>::shallowCopy()
{
  return GenMask2d(*this, 0);
}


// AUXILIARY: STORE A DEEP COPY OF A GIVEN MASK INTO THE CURRENT MASK

template <class T>
void
GenMask2d<T>::PRIVATEdeepCopy(const GenMask2d<T>& aMask)
{
  // Are source and destination the same object?
  if (this != &aMask)
    {
      _pRefCnt = new int(0);
      _width   = aMask._width;
      _height  = aMask._height;

      // Free space allocated to the coefficent map of the destination mask
      delete [] _pCoeffMap;
 
     // Allocate space to the coefficent map
      int size = _width * _height;
      _pCoeffMap = new T[size];

      // Copy the coefficients
      memcpy(_pCoeffMap, aMask.pCoeffMap(), size * sizeof(T));
    }
}


// -------------------------------------------------------------------
// O P E R A T O R S
// -------------------------------------------------------------------


// ASSIGNMENT

template <class T>
GenMask2d<T>&
GenMask2d<T>::operator=(const GenMask2d<T>& aMask)
{
  PRIVATEdeepCopy(aMask);
  return *this;
}


// -------------------------------------------------------------------


} // namespace qgar
