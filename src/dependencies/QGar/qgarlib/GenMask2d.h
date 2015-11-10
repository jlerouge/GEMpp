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


#ifndef __GENMASK2D_H_INCLUDED__
#define __GENMASK2D_H_INCLUDED__


/**
 * @file GenMask2d.h
 *
 * @brief Header file of class qgar::GenMask2d.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gerald Masini">Gérald Masini</a>
 * @date   Apr 11, 2003  15:17
 * @since  Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: GenMask2d.h,v 1.17 2006/07/04 13:37:42 masini Exp $ */



namespace qgar
{


/**
 * @ingroup DS_MASK
 *
 * @class GenMask2d GenMask2d.h "qgarlib/GenMask2d.h"
 *
 * @brief Generic 2D mask with coefficients of type <b>T</b>.
 * 
 * @warning A mask is stored as <b>consecutive rows</b> im memory space.
 * The top-left corner of the mask has coordinates <b>(0,0)</b>.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gerald Masini">Gérald Masini</a>
 * @date   Apr 11, 2003  15:17
 * @since  Qgar 2.1
 */
template <class T> class GenMask2d
{
// -------------------------------------------------------------------
// T Y P E   D E F I N I T I O N S
// -------------------------------------------------------------------
public:

  /** @name Types related to 2D masks */
  //        =========================
  //@{
  /**
   * @brief Type of the mask coefficients.
   */
  typedef T value_type;

  /**
   * @brief Reference to qgar::GenMask2d::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::GenMask2d::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::GenMask2d::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::GenMask2d::value_type.
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
   * @brief Default constructor: Set <b>0</b> to mask width and height,
   * to pointer to the coefficient map, and to reference counter.
   */
  GenMask2d();

  /**
   * @brief Copy constructor.
   *
   * See also qgar::GenMask2d::operator=
   *      and qgar::GenMask2d::shallowCopy.
   *
   * @warning Perform a deep copy:
   * The coefficent map of the source mask is duplicated.
   */
  GenMask2d(const GenMask2d<value_type>& aMask);

  /**
   * @brief Initialize with given width, height and value.
   *
   * All the coefficients are set to the given value.
   *
   * @param aWidth   mask width
   * @param aHeight  mask height
   * @param aValue   value to fill the mask with (default <b>0</b>)
   */
  GenMask2d(unsigned int aWidth,
	    unsigned int aHeight,
	    value_type aValue = static_cast<value_type>(0));

  /**
   * @brief Builds a mask from an array of values.
   *
   * @param aWidth
   * @param aHeight
   * @param valArray
   */
  GenMask2d(unsigned int aWidth,
	    unsigned int aHeight,
	    const_pointer const valArray);

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Non-virtual destructor.
   *
   * Free space allocated to the coefficient map
   * if and only if the reference counter is null.
   */
  ~GenMask2d();

  //@}


  /** @name Access to mask characteristics */
  //        ==============================
  //@{

  /**
   * @brief Get mask width.
   */
  inline int width() const;

  /**
   * @brief Get mask height.
   */
  inline int height() const;

  //@}


  /** @name Access to coefficient values */
  //        ============================
  //@{

  /**
   * @brief Get a coefficient value.
   *
   * @param aX  X coordinate (column index) of the coefficient
   * @param aY  Y coordinate (row index) of the coefficient
   */
  value_type coeff(int aX, int aY) const;

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
   * @brief Set coefficient at given position.
   *
   * @param aX      X coordinate (column index) of the coefficient
   * @param aY      Y coordinate (row index) of the coefficient
   * @param aCoeff  coefficient value
   */
  void setCoeff(int aX, int aY, value_type aCoeff);

  //@}


  /** @name Copy */
  //        ====
  //@{

  /**
   * @brief Shallow copy: The coefficient map of the source mask
   * is <b>not</b> duplicated.
   *
   * See also qgar::GenMask2d::operator=
   *      and qgar::GenMask2d::shallowCopy.
   *
   * @warning Before the copy is performed, the destination mask
   * is not supposed to have the same dimensions as the source mask.
   * When the copy is completed, the pixel map of the destination
   * mask is the same memory space as the pixel map of the source mask.
   */
  GenMask2d<value_type> shallowCopy();

  //@}


  /** @name Operators */
  //        =========
  //@{

  /**
   * @brief Assignment.
   *
   * See also qgar::GenMask2d::operator=,
   *      and qgar::GenMask2d::shallowCopy.
   *
   * @param aMask mask to assign
   *
   * @warning Perform a <b>deep copy</b>: The coefficient map 
   * of the source mask is duplicated. Before the copy is performed, 
   * the destination mask is not supposed to have the same dimensions
   * as the destination mask.
   */
  GenMask2d<value_type>& operator=(const GenMask2d<value_type>& aMask);

  //@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:


  /** @name Shallow copy constructor */
  //        ========================
  //@{

  /**
   * @brief Shallow copy constructor.
   *
   * This constructor declares an unused <b>integer</b> parameter
   * to avoid ambiguous calls to the copy constructor.
   * It builds a shallow copy of a mask instance.
   *
   * @param rhs A mask instance to create a copy from.
   */
  GenMask2d(const GenMask2d<value_type>& rhs, int);

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
  int* _pRefCnt;

  /**
   * @brief Mask width.
   */
  int _width;

  /**
   * @brief Mask height.
   */
  int _height;

  /**
   * @brief Pointer to the memory space of the mask.
   */
  pointer _pCoeffMap;

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
  void PRIVATEdeepCopy(const GenMask2d<T>& aMask);

  //@}


// -------------------------------------------------------------------
}; // class GenMask2d


} // namespace qgar




// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// I M P L E M E N T A T I O N
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII

#include "GenMask2d.tcc"

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
 * @name 2D Masks
 * @ingroup DS_MASK
 */
//@{

/**
 * @brief 2D mask with coefficients of type <b>int</b>.
 *
 * @see qgar::GenMask2d::IMask2d
 */
typedef GenMask2d<int> Mask2d;

/**
 * @brief 2D mask with coefficients of type <b>int</b>.
 *
 * @see qgar::GenMask2d::Mask2d
 */
typedef GenMask2d<int> IMask2d;

/**
 * @brief 2D mask with coefficients of type <b>float</b>.
 */
typedef GenMask2d<float> FMask2d;

/**
 * @brief 2D mask with coefficients of type <b>double</b>.
 */
typedef GenMask2d<double> DMask2d;

//@}


} // namespace qgar


// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


#endif /* __GENMASK2D_H_INCLUDED__ */
