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


#ifndef __GENMASK1D_H_INCLUDED__
#define __GENMASK1D_H_INCLUDED__


/**
 * @file GenMask1d.h
 *
 * @brief Header file of class qgar::GenMask1d.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gerald Masini">Gérald Masini</a>
 * @date   Apr 18, 2003  17:47
 * @since  Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: GenMask1d.h,v 1.20 2006/07/04 13:37:42 masini Exp $ */



namespace qgar
{

/**
 * @ingroup DS_MASK
 *
 * @class GenMask1d GenMask1d.h "qgarlib/GenMask1d.h"

 * @brief Generic 1D mask with coefficients of type <b>T</b>.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gerald Masini">Gérald Masini</a>
 * @date   Apr 18, 2003  17:47
 * @since  Qgar 2.1
 */
template <class T> class GenMask1d
{
// -------------------------------------------------------------------
// T Y P E   D E F I N I T I O N S
// -------------------------------------------------------------------
public:

  /** @name Types */
  //        =====
  //@{

  /**
   * @brief Type of the mask coefficients.
   */
  typedef T value_type;

  /**
   * @brief Reference to qgar::GenMask1d::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::GenMask1d::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::GenMask1d::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::GenMask1d::value_type.
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
   * @brief Default constructor: set <b>0</b> to mask width,
   * to pointer to the coefficient map, and to reference counter.
   */
  GenMask1d();

  /**
   * @brief Copy constructor.
   *
   * See also qgar::GenMask1d::operator=,
   *          qgar::GenMask1d::deepCopy,
   *      and qgar::GenMask1d::shallowCopy.
   *
   * @warning Perform a <b>deep copy</b>: the coefficent map
   * of the source mask is duplicated.
   */
  GenMask1d(const GenMask1d<value_type>& aMask);

  /**
   * @brief Conversion from another mask.
   *
   * See also qgar::GenMask1d::operator=,
   *          qgar::GenMask1d::shallowCopy.
   *
   * @warning Perform a <b>deep copy</b>: the coefficent map
   * of the source mask is duplicated.
   */
  template <class U>
  explicit
  GenMask1d(const GenMask1d<U>& aMask);

  /**
   * @brief Initialize with given width and value.
   * @param aWidth  mask width
   * @param aValue  value to fill the mask with (default <b>0</b>)
   *
   * All the coefficients are set to the given value.
   */
  explicit GenMask1d(unsigned int aWidth,
		     value_type aValue = static_cast<value_type>(0));

  /**
   * @brief Create a mask from an array of values.
   *
   * The passed array is duplicated using a raw memcopy.
   *
   * @param aWidth The width of the array
   * @param pVals A pointer to the values.
   */
  GenMask1d(unsigned int aWidth, const_pointer const pVals);

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief virtual destructor.
   *
   * Free space allocated to the coefficient map
   * if and only if the reference counter is null.
   */
  virtual ~GenMask1d();

  //@}


  /** @name Access to mask characteristics */
  //        ==============================
  //@{

  /**
   * @brief Get mask width.
   */
  inline int width() const;

  //@}


  /** @name Access to coefficient values */
  //        ============================
  //@{

  /**
   * @brief Get a coefficient value.
   * @param anIdx  index of the coefficient in the coefficient map
   */
  value_type coeff(int anIdx) const;

  //@}


 /** @name Access to direct transformations of the coefficient map */
  //       =======================================================
  //@{

  /**
   * @brief Get the pointer to the coefficient map.
   */
  inline pointer pCoeffMap() const;

  //@}


  /** @name Transformation */
  //        ==============
  //@{

  /**
   * @brief Set coefficient at given index.
   *
   * @param anIdx   index in the coefficient map
   * @param aCoeff  coefficient value
   */
  void setCoeff(int anIdx, value_type aCoeff);

  //@}


  /** @name Copy */
  //        ====
  //@{

  /**
   * @brief Shallow copy: the coefficient map of the source mask
   * is <b>not</b> duplicated.
   *
   * See also qgar::GenMask1d(Genmask1d<t>&),
   *          qgar::GenMask1d::operator=,
   *
   * @warning Before the copy is performed, the destination mask
   * is not supposed to have the same dimensions as the source mask.
   * When the copy is completed, the pixel map of the destination
   * mask is the same memory space as the pixel map of the source
   * mask.
   */
  GenMask1d<T>* shallowCopy();

  //@}


  /** @name Operators */
  //        =========
  //@{

  /**
   * @brief Assignment.
   *
   * See also qgar::GenMask1d(Genmask1d<t>&),
   *      and qgar::GenMask1d::shallowCopy.
   *
   * @param aMask mask to assign
   *
   * @warning Perform a <b>deep copy</b>: the coefficient map 
   * of the source mask is duplicated. Before the copy is performed, 
   * the destination mask is not supposed to have the same size
   * as the destination mask.
   */
  GenMask1d<T>& operator=(const GenMask1d<T>& aMask);

  //@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:


  /** @name Shallow copy constructor */
  //        ========================
  //@{

  /**
   * @brief Disguised copy constructor sharing value array between the
   * passed and the created instance.
   *
   * This constructor declares a fake <b>int</b> parameter
   * to avoid ambiguous call between itself and the copy constructor.
   * It builds a shallow copy of a mask instance.
   *
   * @param rhs A mask instance to create a copy from
   */
  GenMask1d(const GenMask1d& rhs, int);

  //@}


  /** @name Representation of a mask */
  //        ========================
  //@{

  /**
   * @brief Reference counter.
   *
   * Its value represent the number of other masks
   * with which the current mask shares its coefficient map.
   */
  int* pRefCnt_;

  /**
   * @brief Mask width.
   */
  int width_;

  /**
   * @brief Pointer to the memory space of the mask.
   */
  pointer pCoeffMap_;

  //@}


// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:


  /** @name Auxiliaries */
  //        ===========
  //@{

  /**
   * @brief Store a deep copy of a given mask into the current mask.
   *
   * @param aMask  mask to be copied
   */
  void PRIVATEdeepCopy(const GenMask1d<value_type>& aMask);

  //@}


// -------------------------------------------------------------------
}; // class GenMask1d


} // namespace qgar




// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// I M P L E M E N T A T I O N
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII

#include "GenMask1d.tcc"

// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII




// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// P R E D E F I N E D    M A S K    T Y P E S
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


namespace qgar
{


/**
 * @name 1D Masks
 * @ingroup DS_MASK
 */
//@{

/**
 * @brief 1D mask with coefficients of type <b>int</b>.
 *
 * @see qgar::Mask1d::IMask1d
 */
typedef GenMask1d<int> Mask1d;

/**
 * @brief 1D mask with coefficients of type <b>int</b>.
 *
 * @see qgar::Mask1d::Mask1d
 */
typedef GenMask1d<int> IMask1d;

/**
 * @brief 1D mask with coefficients of type <b>float</b>.
 */
typedef GenMask1d<float> FMask1d;

/**
 * @brief 1D mask with coefficients of type <b>double</b>.
 */
typedef GenMask1d<double> DMask1d;

//@}


} // namespace qgar


// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


#endif /* __GENMASK1D_H_INCLUDED__ */
