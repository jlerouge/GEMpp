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


#ifndef __ARRAY_H_INCLUDED__
#define __ARRAY_H_INCLUDED__


/**
 * @file array.h
 *
 * @brief Definitions of global utilities for arrays.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   December 06 2004  17:28
 * @since  Qgar 2.2
 */


// For RCS/CVS use: Do not delete
/* $Id: array.h,v 1.8 2007/02/14 18:32:45 vasconcv Exp $ */



// STD
#include <cstdlib>
#include <cstring>



using namespace std;



namespace qgar
{

// -------------------------------------------------------------------
// I N D E X E S
// -------------------------------------------------------------------


/** @name Global functions about array indexes */
//        ====================================
//@{

/**
 * @ingroup GLOB_ARRAY
 *
 * @brief Return the index of a value in a subrange of an array.
 *
 * The subrange is defined as <b>[aFirstIdx, aLastIdx]</b>.
 * The function returns <b>-1</b> if the value is not found.
 *
 * @param anArray    an array
 * @param aFirstIdx  lower index of the elements to be examined
 * @param aLastIdx   upper index of the elements to be examined
 * @param aValue     a value to be searched in the array
 *
 * @warning
 * - Operator '=' must be defined for objects of type <b>T</b>
 * - The behavior of the function is undefined in case of
 *   wrong range <b>[aFirstIdx, aLastIdx]</b>
 */
template <class T>
int
qgFind(const T* const anArray, int aFirstIdx, int aLastIdx, T aValue)
{
  int found = -1;

  for (int idx = aFirstIdx ; idx <= aLastIdx ; ++idx)
    {
      if (anArray[idx] = aValue)
	{
	  found = idx;
	}
    }

  return found;
}


/**
 * @ingroup GLOB_ARRAY
 *
 * @brief Return the index of the minimum element
 *   of a subrange of an array.
 *
 * The subrange is defined as <b>[aFirstIdx, aLastIdx]</b>.
 *
 * @param anArray    an array
 * @param aFirstIdx  lower index of the elements to be examined
 * @param aLastIdx   upper index of the elements to be examined
 *
 * @warning
 * - Operator '<' must be defined on objects of type <b>T</b>
 * - The behavior of the function is undefined in case of
 *   wrong range <b>[aFirstIdx, aLastIdx]</b>
 */
template <class T>
int
qgMinElement(const T* const anArray, int aFirstIdx, int aLastIdx) 
{
  T   min    = anArray[aFirstIdx];
  int idxMin = aFirstIdx;

  for (int idx = aFirstIdx + 1 ; idx <= aLastIdx ; ++idx)
    {
      if (anArray[idx] < min)
	{
	  min = anArray[idx];
	  idxMin = idx;
	}
    }

  return idxMin;
}


/**
 * @ingroup GLOB_ARRAY
 *
 * @brief Return the index of the minimum element of an array.
 *
 * @param anArray  an array
 * @param aSize    size of the array
 *
 * @warning
 * - Operator '<' must be defined for objects of type <b>T</b>
 * - The behavior of the function is undefined in case of wrong size
 */
template <class T>
inline int
qgMinElement(const T* const anArray, int aSize) 
{
  return qgMinElement(anArray, 0, aSize - 1);
}


/**
 * @ingroup GLOB_ARRAY
 *
 * @brief Return the index of the maximum element
 *   of a subrange of an array.
 *
 * The subrange is defined as <b>[aFirstIdx, aLastIdx]</b>.
 *
 * @param anArray    an array
 * @param aFirstIdx  lower index of the elements to be examined
 * @param aLastIdx   upper index of the elements to be examined
 *
 * @warning
 * - Operator '<' must be defined for objects of type <b>T</b>
 * - The behavior of the function is undefined in case of
 *   wrong range <b>[aFirstIdx, aLastIdx]</b>
 */
template <class T>
int
qgMaxElement(const T* const anArray, int aFirstIdx, int aLastIdx)
{
  T   max    = anArray[aFirstIdx];
  int idxMax = aFirstIdx;

  for (int idx = aFirstIdx + 1 ; idx <= aLastIdx ; ++idx)
    {
      if (anArray[idx] > max)
	{
	  max = anArray[idx];
	  idxMax = idx;
	}
    }

  return idxMax;
}


/**
 * @ingroup GLOB_ARRAY
 *
 * @brief Return the index of the maximum element of an array.
 *
 * @param anArray  an array
 * @param aSize    size of the array
 *
 * @warning
 * - Operator '>' must be defined for objects of type <b>T</b>
 * - The behavior of the function is undefined in case of wrong size
 */
template <class T>
int
qgMaxElement(const T* const anArray, int aSize)
{
  return qgMaxElement(anArray, 0, aSize - 1);
}


/**
 * @ingroup GLOB_ARRAY
 *
 * @brief Return the index of a value in an array.
 *
 * Return <b>-1</b> if the value is not found in the array.
 *
 * @param anArray  an array
 * @param aSize    size of the array
 * @param aValue   a value to be searched in the array
 *
 * @warning
 * - Operator '=' must be defined for objects of type <b>T</b>
 * - The behavior of the function is undefined in case of wrong size
 */
template <class T>
int
qgFind(const T* const anArray, int aSize, T aValue)
{
  return qgFind(anArray, 0, aSize - 1, aValue);
}

//@}


// -------------------------------------------------------------------
// I N I T I A L I Z A T I O N S
// -------------------------------------------------------------------


/** @name Global functions for array initialization */
//        =========================================
//@{

/**
 * @ingroup GLOB_ARRAY
 *
 * @brief Set each element of a subrange of an array.
 *
 * The subrange is defined as <b>[aFirstIdx, aLastIdx]</b>.
 *
 * @param anArray    an array
 * @param aFirstIdx  lower index of the elements to be set
 * @param aLastIdx   upper index of the elements to be set
 * @param aValue     value to set
 *
 * @warning
 * The behavior of the function is undefined in case of
 * wrong range <b>[aFirstIdx, aLastIdx]</b>.
 */
template <class T>
void
qgFill(T* anArray, int aFirstIdx, int aLastIdx, T aValue)
{
  T* pArray = anArray;

  for (int iCnt = aFirstIdx; iCnt <= aLastIdx; ++iCnt)
    {
      *pArray = aValue;
      ++pArray;
    }
}


/**
 * @ingroup GLOB_ARRAY
 *
 * @brief Set all elements of an array to a value.
 *
 * @param anArray  an array
 * @param aSize    size of the array
 * @param aValue   value to assign to each element of the array
 *
 * @warning The behavior of the function is undefined
 *   in case of wrong size.
 */
template <class T>
inline void
qgFill(T* anArray, int aSize, T aValue)
{
  qgFill(anArray, 0, aSize - 1, aValue);
}


/**
 * @ingroup GLOB_ARRAY
 *
 * @brief Set all bytes of an array to <b>0</b>.
 *
 * The operation is performed using a low level <b>memset</b>.
 *
 * @param anArray  array to be set
 * @param aSize    size of the array
 *
 * @warning
 * The behavior of the function is undefined in case of wrong size.
 */
template<class T>
inline void
qgMemSet0(T* anArray, int aSize)
{
  memset(anArray, 0, aSize * sizeof(T));
}


/**
 * @ingroup GLOB_ARRAY
 *
 * @brief Set all bytes of an array to <b>0</b>.
 *
 * The subrange is defined as <b>[aFirstIdx, aLastIdx]</b>.
 * The operation is performed using a low level <b>memset</b>.
 *
 * @param anArray  array to be set
 * @param aFirstIdx  lower index of the elements to be set
 * @param aLastIdx   upper index of the elements to be set
 *
 * @warning
 * The behavior of the function is undefined in case
 * of wrong range <b>[aFirstIdx, aLastIdx]</b>.
 */
template<class T>
inline void
qgMemSet0(T* anArray, int aFirstIdx, int aLastIdx)
{
  memset(anArray + aFirstIdx, 0, (aLastIdx - aFirstIdx + 1) * sizeof(T));
}

//@}


// -------------------------------------------------------------------
// M A P P I N G   F U N C T I O N S
// -------------------------------------------------------------------


/** @name Global mapping functions on arrays */
//        ==================================
//@{
/**
 * @ingroup GLOB_ARRAY
 *
 * @brief Apply a given function to pairs of elements
 *  from a subrange of two arrays.
 *
 * - The two arguments and the result of the function must have
 *   the same type as the elements of the arrays.
 * - For each index in the range <b>[aFirstIdx, aLastIdx]</b>,
 *   the function is applied to the elements at current index
 *   <b>i</b> in both arrays: <b>anOperation(aSource[i], aDest[i])</b>.
 *   The value returned by the function is then stored at the current
 *   index in the destination array.
 *
 * @param aSource      source array (not modified)
 * @param aDest        destination array (modified)
 * @param aFirstIdx    lower index of the elements to be used
 * @param aLastIdx     upper index of the elements to be used
 * @param anOperation  operation to apply to the elements of the arrays
 *
 * @warning
 * The behavior of the function is undefined in case of wrong range
 * <b>[aFirstIdx, aLastIdx]</b> or in case of overlaping arrays.
 */
template <class T>
void
qgForEach(T* const aSource,
	  T*  aDest,
	  int aFirstIdx,
	  int aLastIdx,
	  T (*anOperation)(const T&, const T&))				    
{
  T* pSource = aSource + aFirstIdx;
  T* pDest   = aDest + aFirstIdx;

  for (int iCnt = aFirstIdx; iCnt <= aLastIdx; ++iCnt)
    {
      *pDest = (*anOperation)(*pSource, *pDest);
      ++pDest;
      ++pSource;
    }
}

/**
 * @ingroup GLOB_ARRAY
 *
 * @brief Apply a function to pairs of elements from two arrays.
 *
 * - Both arrays must have the same size.
 * - The two arguments and the result of the function must have
 *   the same type as the elements of the arrays.
 * - For each index in the range determined by the given size,
 *   the function is applied to the elements at current index
 *   <b>i</b> in both arrays: <b>anOperation(aSource[i], aDest[i])</b>.
 *   The value returned by the function is then stored at the current
 *   index in the destination array.
 *
 * @param aSource      source array (not modified)
 * @param aDest        destination array (modified)
 * @param aSize        size of the arrays
 * @param anOperation  operation to apply to the elements of the arrays
 *
 * @warning
 * The behavior of the function is undefined in case of wrong size
 * or in case of overlaping arrays.
 */
template <class T>
inline void
qgForEach(T* const aSource,
	  T*  aDest,
	  int aSize,
	  T (*anOperation)(const T&, const T&))				    
{
  qgForEach(aSource, aDest, 0, aSize - 1, anOperation);
}

//@}


// -------------------------------------------------------------------

} // namespace qgar


#endif /* __ARRAY_H_INCLUDED__ */
