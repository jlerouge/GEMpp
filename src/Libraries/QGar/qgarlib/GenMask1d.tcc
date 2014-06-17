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
 * @file GenMask1d.tcc
 *
 * @brief Implementation of function members of class qgar::GenMask1d.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   January 27, 2005  21:55
 * @since  Qgar 2.2
 */



// STD
#include <cstring>
// QGAR
#include "array.h"



using namespace std;



namespace qgar
{


// -------------------------------------------------------------------
// C O N S T R U C T O R S
// -------------------------------------------------------------------


// DEFAULT CONSTRUCTOR

template <class T>
GenMask1d<T>::GenMask1d()

  : pRefCnt_   (new int(0)),
    width_     (0),
    pCoeffMap_ (0)

{
  // VOID
}


// COPY CONSTRUCTOR

template <class T>
GenMask1d<T>::GenMask1d(const GenMask1d<T>& aMask)

  : pRefCnt_ (new int(0)),
    width_   (aMask.width())

{
  pCoeffMap_ = new T[width_];
  memcpy(pCoeffMap_, aMask.pCoeffMap(), width_ * sizeof(T));
}


// CONVERSION CONSTRUCTOR

template <class T>
template <class U>
GenMask1d<T>::GenMask1d(const GenMask1d<U>& aMask)

  : pRefCnt_ (new int(0)),
    width_   (aMask.width())

{
  pCoeffMap_ = new T[width_];

  for (int i=0; i < width_; i++)
    {
      pCoeffMap_[i] = static_cast<T>(aMask.pCoeffMap()[i]);
    }
}


// INITIALIZE WITH GIVEN WIDTH AND VALUE

template <class T>
GenMask1d<T>::GenMask1d(unsigned int aWidth, T aValue)

  : pRefCnt_ (new int(0)),
    width_   (aWidth)

{
  pCoeffMap_ = new T[width_];
  qgFill(pCoeffMap_, width_, aValue);
}


// INITIALIZE WITH GIVEN WIDTH AND VAL ARRAY

template <class T>
GenMask1d<T>::GenMask1d(unsigned int aWidth, const T * const pVals)

  : pRefCnt_ (new int(0)),
    width_   (aWidth)

{
  pCoeffMap_ = new T[aWidth];
  memcpy(pCoeffMap_, pVals, aWidth * sizeof(T));
}


// SHALLOW COPY CONSTRUCTOR

template <class T>
GenMask1d<T>::GenMask1d(const GenMask1d& rhs, int)

  : pRefCnt_   (rhs.pRefCnt_),
    width_     (rhs.width_), 
    pCoeffMap_ (rhs.pCoeffMap_)

{
  (*pRefCnt_)++;
}


// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------


// FREE SPACE ALLOCATED TO THE COEFFICIENT MAP

template <class T>
GenMask1d<T>::~GenMask1d()
{
  if (*pRefCnt_ == 0)
    {
      // The space allocated to the coefficient map
      // is not shared with another object
      delete [] pCoeffMap_;
      delete pRefCnt_;
    }
  else
    {
      // The space allocated to the coefficient map is shared
      // with at least one other object: Just decrement
      // the reference counter
      (*pRefCnt_)--;
    }
}


// -------------------------------------------------------------------
// A C C E S S   T O   M A S K   C H A R A C T E R I S T I C S
// -------------------------------------------------------------------


// GET MASK WIDTH

template <class T>
inline int
GenMask1d<T>::width() const
{
  return width_;
}


// -------------------------------------------------------------------
// A C C E S S   T O   C O E F F I C I E N T   V A L U E S
// -------------------------------------------------------------------


// GET A COEFFICIENT VALUE

template <class T>
T
GenMask1d<T>::coeff(int anIdx) const
{
  return *(pCoeffMap_ + anIdx);
}


// -------------------------------------------------------------------
// ACCESS TO DIRECT TRANSFORMATIONS OF THE COEFFICIENT MAP
// -------------------------------------------------------------------


// GET THE POINTER TO THE COEFFICIENT MAP

template <class T>
inline T*
GenMask1d<T>::pCoeffMap() const
{
  return pCoeffMap_;
}


// -------------------------------------------------------------------
// T R A N S F O R M A T I O N
// -------------------------------------------------------------------


// SET COEFFICIENT AT GIVEN INDEX

template <class T>
void
GenMask1d<T>::setCoeff(int anIdx, T aCoeff)
{
  *(pCoeffMap_ + anIdx) = aCoeff;
}


// -------------------------------------------------------------------
// C O P Y
// -------------------------------------------------------------------


// SHALLOW COPY: THE COEFFICIENT MAP OF THE SOURCE MASK IS NOT DUPLICATED.
// When the copy is completed, the pixel map of the destination
// mask is the same memory space as the pixel map of the source mask.

template <class T>
GenMask1d<T>*
GenMask1d<T>::shallowCopy()
{
  return new GenMask1d(*this, 0);
}


// AUXILIARY: STORE A DEEP COPY OF A GIVEN MASK INTO THE CURRENT MASK

template <class T>
void
GenMask1d<T>::PRIVATEdeepCopy(const GenMask1d<T>& aMask)
{
  // Are source and destination the same object?
  if (this != &aMask)
    {
      pRefCnt_ = new int(0);
      width_   = aMask.width_;

      // Free space allocated to the coefficent map of the destination mask
      delete [] pCoeffMap_;
      // Allocate space to the coefficent map
      pCoeffMap_ = new T[width_];
      // Copy the coefficients
      memcpy(pCoeffMap_, aMask.pCoeffMap(), width_ * sizeof(T));
    }
}


// -------------------------------------------------------------------
// O P E R A T O R S
// -------------------------------------------------------------------


// ASSIGNMENT

template <class T>
GenMask1d<T>&
GenMask1d<T>::operator=(const GenMask1d<T>& aMask)
{
  PRIVATEdeepCopy(aMask);
  return *this;
}


// -------------------------------------------------------------------


} // namespace qgar
