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


#ifndef ___QGAR_GENPOINT_H_INCLUDED__
#define ___QGAR_GENPOINT_H_INCLUDED__


/**
 * @file _QGAR_GenPoint.h
 *
 * @brief Header file of class qgar::GenPoint.
 *
 * @warning <b>Not to be used as include file!</b>
 * <br>When working with primitives, use file primitives.h.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   December 15, 2004  15:55
 * @since  Qgar 2.2
 */


// For RCS/CVS use: Do not delete
/* $Id: _QGAR_GenPoint.h,v 1.7 2006/03/30 12:49:41 masini Exp $ */



// STD
#include <iosfwd>  // Avoid including classes when not necessary
// QGAR
#include "ISerializable.h"



namespace qgar
{


/**
 * @class GenPoint _QGAR_GenPoint.h "qgarlib/primitives.h"
 * @ingroup DS_POINT
 * @brief Point with coordinates of type <b>T</b>.
 *
 * <b>This class is not supposed to be derived: The destructor
 * (as any other function) is not virtual.</b>
 *
@verbatim
   O
    +---------------> X
    |\    |
    | \ <-'
    |  \    angle (in radians unless specified)
    |   \
    |
    V

    Y
@endverbatim
 * The origin of the coordinate system is at top left corner,
 * and angles are clockwise from the X axis.
 *
 * <b>Predefined types:</b>
 * <br> &nbsp; &nbsp; &nbsp; &nbsp; See submodule
 * <a href="group__DS__POINT.html"><b>Points</b></a> for details.
 *
 * @warning
 *   Most of the functions performing geometrical transformations work
 *   with points and primitives having <b>double</b> coordinates only.
 *
 * @author  <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date    July 4, 2001  14:07
 * @since   Qgar 1.0
 */
template <class T> class GenPoint
{
// -------------------------------------------------------------------
// T Y P E   D E F I N I T I O N S
// -------------------------------------------------------------------
public:


  /** @name Types */
  //        =====
  //@{

  /**
   * @brief Type of the coordinates.
   */
  typedef T value_type;

  /**
   * @brief Reference to qgar::GenPoint::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::GenPoint::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::GenPoint::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::GenPoint::value_type.
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
   * @brief Default constructor: Create a point at <b>(0,0)</b>.
   */
  GenPoint();

  /**
   * @brief Copy constructor.
   */
  GenPoint(const GenPoint<value_type>& aPt);

  /**
   * @brief Conversion of a point of a type different
   *        from the effective type.
   *
   * @param aPt  a point
   *
   * @warning This kind of conversion must be explicitely
   *   specified by the client.
   */
  template <class U>
  explicit GenPoint(const GenPoint<U>& aPt);

  /**
   * @brief Initialize from coordinates.
   */
  GenPoint(value_type aX, value_type aY);

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Non-virtual destructor (see the class header).
   */
  ~GenPoint();

  //@}


  /** @name Access to coordinates */
  //        =====================
  //@{

  /**
   * @brief Get X coordinate.
   */
  inline value_type x() const;

  /**
   * @brief Get Y coordinate.
   */
  inline value_type y() const;

  /**
   * @brief Get radius (<i>rho</i>) in polar coordinates.
   */
  inline double rho() const;

  /**
   * @brief Get angle (<i>theta</i>) in polar coordinates.
   */
  inline double theta() const;

  //@}


  /** @name Assign coordinates */
  //        ==================
  //@{

  /**
   * @brief Set X coordinate.
   *
   * @param aX  new X coordinate
   */
  inline void setX(value_type aX);

  /**
   * @brief Set Y coordinate.
   *
   * @param aY  new Y coordinate
   */
  inline void setY(value_type aY);

  /**
   * @brief Set both X and Y coordinates.
   *
   * @param aX  new X coordinate
   * @param aY  new Y coordinate
   */
  inline void setXY(value_type aX, value_type aY);

  //@}


  // ===================================================================
  /** @name Operators
   *
   * @warning Using stand-alone versions of operators
   * (<b>operator+</b>, <b>operator-</b>) is much less efficient then
   * using assignment versions (<b>operator+=</b>, <b>operator-=<b/>).
   * For example, an expression like:
@verbatim
  res = a + b - c;
@endverbatim
   * uses 2 temporary objects, one for each call to <b>operator+</b>
   * and <b>operator-</b>. These considerations also apply to functional
   * operators (see the corresponding section). To preserve efficiency,
   * the code should be written in this way:
@verbatim
  res = a;
  res += b;  // no temporary needed
  res -= c;  // no temporary needed
@endverbatim
   */
  // ===================================================================
  //@{

  /**
   * @brief Assignment.
   */
  inline GenPoint<value_type>&
  operator=(const GenPoint<value_type>& aPt);

  /**
   * @brief Same as function qgar::GenPoint::plus.
   */
  inline const GenPoint<value_type>
  operator+(const GenPoint<value_type>& aPt) const;

  /**
   * @brief Same as function qgar::GenPoint::plusEqual.
   */
  inline GenPoint<value_type>&
  operator+=(const GenPoint<value_type>& aPt);

  /**
   * @brief Same as function qgar::GenPoint::minus.
   */
  inline const GenPoint<value_type>
  operator-(const GenPoint<value_type>& aPt) const;

  /**
   * @brief Same as function qgar::GenPoint::minusEqual.
   */
  inline GenPoint<value_type>&
  operator-=(const GenPoint<value_type>& aPt);

  /**
   * @brief Same as function qgar::GenPoint::eq.
   */
  inline bool
  operator==(const GenPoint<value_type>& aPt) const;

  /**
   * @brief Same as function qgar::GenPoint::notEq.
   */
  inline bool
  operator!=(const GenPoint<value_type>& aPt) const;

  //@}


  // ===================================================================
  /** @name Functional operators
   *
   * @warning Using stand-alone versions of operators
   * (<b>plus</b>, <b>minus</b>) is much less efficient then
   * using assignment versions (<b>plusEqual</b>, <b>minusEqual</b>).
   * For example, an expression like:
@verbatim
  res = a.plus(b).minus(c);
@endverbatim
   * uses 2 temporary objects, one for each call to <b>plus</b>
   * and <b>minus</b>. These considerations also apply to operators
   * (see the corresponding section). To preserve efficiency, the code
   * should be written in this way:
@verbatim
  res = a;
  res.plusEqual(b);   // no temporary needed
  res.minusEqual(c);  // no temporary needed
@endverbatim
   *
   * Operators implementation uses Scott Meyers' tips from
   * [<a href="Bibliography.html#Meyer-1996">Meyer,&nbsp;1996</a>]:
   * item #22, pages 107-110.
   */
  // ===================================================================
  //@{

  /**
   * @brief Add coordinates of the given point to those
   * of the current point, and return them as a new point.
   *
   * @param aPt  a point
   */
  const GenPoint<value_type> plus(const GenPoint<value_type>& aPt) const;

  /**
   * @brief Add coordinates of the given point to those
   * of the current point.
   *
   * The current point is modified.
   *
   * @param aPt  a point
   */
  GenPoint<value_type>& plusEqual(const GenPoint<value_type>& aPt);

  /**
   * @brief Substract coordinates of the given point to those
   * of the current point, and return them as a new point.
   *
   * @param aPt  a point
   */
  const GenPoint<value_type> minus(const GenPoint<value_type>& aPt) const;

  /**
   * @brief Substract coordinates of the given point to those
   * of the current point.
   *
   * The current point is modified.
   *
   * @param aPt  a point
   */
  GenPoint<value_type>& minusEqual(const GenPoint<value_type>& aPt);

  /**
   * @brief Equality.
   *
   * Return <b>true</b> if the current point and the given point
   * have the same coordinates.
   *
   * @param aPt  a point
   */
  bool eq(const GenPoint<value_type>& aPt) const;

  /**
   * @brief Inequality.
   *
   * Return <b>true</b> if the coordinates of the current point
   * and of the given point are different.
   *
   * @param aPt  a point
   */
  bool notEq(const GenPoint<value_type>& aPt) const;

  //@}


  /** @name Geometry: projection */
  //        ====================
  //@{

  /**
   * @brief Orthogonal projection of the current point
   *   onto the line supporting the given segment.
   *
   * @param aSeg  a segment
   *
   * @warning This function applies only to points and
   *   segments having coordinates of type <b>double</b>.
   */
  inline void project(const GenSegment<value_type>& aSeg);

  /**
   * @brief Orthogonal projection of the current point
   *   onto the line supporting the given Qgar segment.
   *
   * @param aQSeg  a Qgar segment
  *
   * @warning This function applies only to points and
   *   Qgar segments having coordinates of type <b>double</b>.
   */
  inline void project(const GenQgarSegment<value_type>& aQSeg);

  //@}


  /** @name Geometry: translation */
  //        =====================
  //@{

  /**
   * @brief Translate current point along X and Y axis.
   *
   * @param aTransX  X translation factor
   * @param aTransY  Y translation factor
   */
  void translate(value_type aTransX, value_type aTransY);

  //@}


//   /** @name Geometry: rotation */
//   //        ==================
//   //@{

//   /**
//    * @brief Rotate by a given angle, using the origin
//    *   of the coordinates system as the rotation center.
//    * @param anAngle an angle 
//    *
//    * @warning This function applies only to points
//    *   having coordinates of type <b>double</b>.
//    */
//   void rotate(double anAngle);

//   /**
//    * @brief Rotate by a given angle,
//    *   using the given point as the rotation center.
//    * @param anAngle an angle 
//    * @param aPt     a point
//    *
//    * @warning This function applies only to points
//    *   having coordinates of type <b>double</b>.
//    */
//   void rotate(double anAngle, const GenPoint<T>& aPt);

//   /**
//    * @brief Rotate by \f$ \pi \f$/2, using the origin
//    *   of the coordinates system as the rotation center.
//    *
//    * @warning This function applies only to points
//    *   having coordinates of type <b>double</b>.
//    */
//   void rotate90();

//   /**
//    * @brief Rotate \f$ \pi \f$/2,
//    *   using the given point as the rotation center.
//    * @param  aPt  a point
//    *
//    * @warning This function applies only to points
//    *   having coordinates of type <b>double</b>.
//    */
//   void rotate90(const GenPoint<T>& aPt);

//   /**
//    * @brief Rotate by \f$ \pi \f$, using the origin
//    *   of the coordinates system as the rotation center.
//    *
//    * @warning This function applies only to points
//    *   having coordinates of type <b>double</b>.
//    */
//   inline void rotate180();

//   /**
//    * @brief Rotate by \f$ \pi \f$/2,
//    *   using the given point as the rotation center.
//    * @param  aPt  a point
//    *
//    * @warning This function applies only to points
//    *   having coordinates of type <b>double</b>.
//    */
//   inline void rotate180(const GenPoint<T>& aPt);


//   /**
//    * @brief Rotate by a 3\f$ \pi \f$/2, using the origin
//    *   of the coordinates system as the rotation center.
//    *
//    * @warning This function applies only to points
//    *   having coordinates of type <b>double</b>.
//    */
//   void rotate270();

//   /**
//    * @brief Rotate by 3\f$ \pi \f$/2,
//    *   using the given point as the rotation center.
//    * @param  aPt  a point
//    *
//    * @warning This function applies only to points
//    *   having coordinates of type <b>double</b>.
//    */
//   void rotate270(const GenPoint<T>& aPt);

//   //@}


//   /** @name Geometry: homothety */
//   //        ===================
//   //@{

//   /**
//    * @brief Homothety with respect to the origin of the
//    *   coordiantes system, using the given dilation factor.
//    * @param aDilFactor  dilation factor
//    *
//    * @warning This function applies only to points
//    *   having coordinates of type <b>double</b>.
//    */   
//   void homothety(double aDilFactor);

//   /**
//    * @brief Homothety with respect to the given point,
//    *   using the given dilation factor.
//    * @param aDilFactor  dilation factor
//    * @param aPt         a point
//    *
//    * @warning This function applies only to points
//    *   having coordinates of type <b>double</b>.
//    */
//   void homothety(double aDilFactor, const GenPoint<T>& aPt);

//   //@}


//   /** @name Geometry: symmetry */
//   //        ==================
//   //@{
  
//   /**
//    * @brief Apply a central symmetry to the current point, using
//    *   the origin of the coordinates system as the symmetry center.
//    */
//   void symmetry();

//   /**
//    * @brief Apply a central symmetry to the current point, using
//    *   the given point as the symmetry center.
//    * @param  aPt  a point, center of the symmetry
//    */
//   void symmetry(const GenPoint<T>& aPt);

//   /**
//    * @brief Apply a mirror symmetry to the current point, using
//    *   the line supporting the given segment for the symmetry.
//    * @param  aSeg  segment supporting the line used for the symmetry
//    *
//    * @warning This function applies only to points and segments
//    *   having coordinates of type <b>double</b>.
//    */
//   void symmetry(const GenSegment<T>& aSeg);

//   //@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:


  /** @name Representation of a point */
  //        =========================
  //@{

  /**
   * @brief X coordinate.
   */
  value_type x_;

  /**
   * @brief Y coordinate.
   */
  value_type y_;

  //@}


// -------------------------------------------------------------------

}; // class GenPoint




// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
// S E R I A L I Z A T I O N / D E S E R I A L I Z A T I O N
// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS


// ===============================================================
/** 
 * @name Point serialization/deserialization operators 
 *
 * @warning Class qgar::GenPoint does not derive from class
 * qgar::ISerializable to get a smaller implementation of a point,
 * and thus to save memory space when dealing with (lots of)
 * points; if points were serializable, they would be implemented
 * using an extra pointer to the table for virtual functions
 * (the destructor in this case).
 */
// ===============================================================
//@{

/**
 * @ingroup IO_SERIAL
 *
 * @brief Deserialize a point (read it from an input stream).
 *
 * A serialized point is represented as:
@verbatim
Point ( <X> ) ( <Y> )
@endverbatim
 *
 * @param anInStream  input stream
 * @param aPt         deserialized point
 *
 * @see qgar::qgReadObjName, qgar::qgReadObjData
 */
template <class T>
inline std::istream&
operator>>(std::istream& anInStream, GenPoint<T>& aPt);


/**
 * @ingroup IO_SERIAL 
 *
 * @brief Serialize a point (write it into an output stream).
 *
 * A serialized point is represented as:
@verbatim
Point ( <X> ) ( <Y> )
@endverbatim
 *
 * @param anOutStream  output stream
 * @param aPt          point to serialize
 */
template <class T>
inline std::ostream&
operator<<(std::ostream& anOutStream, const GenPoint<T>& aPt);

//@}


// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS




// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// P R E D E F I N E D    P O I N T    T Y P E S
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


/**@name Point type names */
//       ================
//@{

/**
 * @ingroup DS_POINT
 *
 * @brief Points with integer coordinates.
 *
 * @see qgar::IPoint
 */
typedef GenPoint<int> Point;

/**
 * @ingroup DS_POINT
 *
 * @brief Points with integer coordinates.
 *
 * @see qgar::Point
 */
typedef GenPoint<int> IPoint;

/**
 * @ingroup DS_POINT
 *
 * @brief Points with coordinates of type <b>float</b>.
 */
typedef GenPoint<float> FPoint;

/**
 * @ingroup DS_POINT
 *
 * @brief Points with coordinates of type <b>double</b>.
 */
typedef GenPoint<double> DPoint;

//@}


// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


} // namespace qgar


#endif /* ___QGAR_GENPOINT_H_INCLUDED__ */
