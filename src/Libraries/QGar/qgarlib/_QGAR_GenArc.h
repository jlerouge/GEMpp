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


#ifndef ___QGAR_GENARC_H_INCLUDED__
#define ___QGAR_GENARC_H_INCLUDED__


/**
 * @file   _QGAR_GenArc.h
 * @brief  Header file of class qgar::GenArc.
 *
 * @warning <b>Not to be used as include file!</b>
 * <br>When working with primitives, use header file primitives.h.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date    January 28, 20045  15:51
 * @since   Qgar 2.2
 */


// For RCS/CVS use: Do not delete
/* $Id: _QGAR_GenArc.h,v 1.6 2005/11/23 17:08:31 masini Exp $ */



// STD
#include <iosfwd>  // Avoid including classes when not necessary
// QGAR
#include "ISerializable.h"



namespace qgar
{


/**
 * @class GenArc _QGAR_GenArc.h "qgarlib/primitives.h"
 * @ingroup DS_PRIM_GEOM
 * @brief Arc of circle, with coordinates of type <b>T</b>.
 *
 * <ul>
 *
 * <li>
@verbatim
   O
    +---------------> X
    |\    |
    | \ <-'
    |  \    angle (in radians, unless specified)
    |   \
    |
    V

    Y
@endverbatim
 * The origin of the coordinate system is at top left corner and
 * angles are clockwise from the X axis.
 * </li>
 *
 * <li>
@verbatim
   O                                 O
    +----------------------> X        +----------------------> X
    | center                          | 
    |      +       +  source          |           -----
    |              |                  |     arc /       \
    |             / arc               |         |   +    v
    | target  +<-                     |         \        + target
    |                                 |          +
    V                                 V        source

    Y                                 Y
@endverbatim
 * An arc is oriented: It is provided with a so-called <i>source point</i>
 * and a so-called <i>target point</i>, which determine the part of the
 * circle supporting the arc.
 *</li>
 *
 * <li>
 * An arc has no attribute. For <i>graphical</i> arcs, typically
 * resulting from vectorization and provided with attributes
 * (thickness, color, outline), see class qgar::GenQgarArc.
 * </li>
 *
 * </ul>
 *
 * <b>Predefined types:</b>
 * <br> &nbsp; &nbsp; &nbsp; &nbsp; See submodule
 * <a href="group__DS__PRIM__GEOM.html"><b>Geometrical primitives</b></a>
 * for details.
 *
 * @warning
 *   <b>The coherence of the data structure of an arc after
 *   modifications of its source and/or its target and/or its
 *   center is the user's responsibility!</b>
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   June 20, 2003  19:23
 * @since  Qgar 2.1
 */
template <class T> class GenArc

  : public AbstractGenPrimitive<T>,
    public ISerializable

{
// -------------------------------------------------------------------
// T Y P E   D E F I N I T I O N S
// -------------------------------------------------------------------
public:


  /** @name Types */
  //        =====
  //@{

  /**
   * @brief Type of the coordinates of the source, target and center.
   */
  typedef T value_type;

  /**
   * @brief Reference to qgar::GenArc::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::GenArc::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::GenArc::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::GenArc::value_type.
   */
  typedef const value_type* const_pointer;

  //@}


// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:


  /**@name Constructors */
  //       ============
  //@{

  /**
   * @brief Default constructor.
   *
   * Zero-length arc located at the origin of the coordinate system.
   *
   * @todo Such an arc does not conform the definition of an arc!
   */
  GenArc();

  /**
   * @brief Copy constructor.
   */
  GenArc(const GenArc<value_type>& anArc);

  /**
   * @brief Initialize from a Qgar arc.
   *
   * @param aQArc  a Qgar arc
   *
   * @warning This kind of conversion must be explicitely
   *   specified by the client.
   */
  explicit GenArc(const GenQgarArc<value_type>& aQArc);

  /**
   * @brief Initialize from three points.
   *
   * @param aSource     source point
   * @param aTarget     target point
   * @param aCenter     center point
   */
  GenArc(const GenPoint<value_type>& aSource,
	 const GenPoint<value_type>& aTarget,
	 const GenPoint<value_type>& aCenter);

  //@}
  
  
  /**@name Destructor */
  //       ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  virtual ~GenArc();

  //@}


  /**@name Copy */
  //       ====
  //@{

  /**
   * @brief Return a deep copy of the current arc.
   */  
  virtual GenArc<value_type>* clone() const;

  //@}  
  

  /** @name Access to geometrical features */
  //        ==============================
  //@{

  /**
   * @brief Get radius.
   */
  inline double radius() const;

  /**
   * @brief Get arc length.
   */
  double length() const;

  /**
   * @brief Get arc angle, in [0, 2PI] radians.
   *
   * Always positive.
   */
  double angle() const;

  /**
   * @brief Get arc angle, in [0, 360] degrees.
   *
   * Always positive.
   */
  inline double angleDegrees() const;

  /**
   * @brief Get the so-called source angle.
   *
   * It is the angle between the vector joining the center to
   * the source point and the X axis, in <b>[0, 2PI]</b> radians.
   */
  inline double sourceAngle() const;

  /**
   * @brief Get the source angle, in <b>[0, 360]</b> degrees.
   */
  inline double sourceAngleDegrees() const;

  /**
   * @brief Get the so-called target angle.
   *
   * It is the angle between the vector joining the center to
   * the target point and the X axis, in <b>[0, 2PI]</b> radians.
   */
  inline double targetAngle() const;

   /**
   * @brief Get the target angle, in <b>[0, 360]</b> degrees.
   */
  inline double targetAngleDegrees() const;

  //@}


  /** @name Center */
  //        ======
  //@{

  /**
   * @brief Get the center point.
   */
  inline const GenPoint<value_type>& accessCenter() const;

  /**
   * @brief Get a copy of the center point.
   */
  inline GenPoint<value_type> center() const;

  /**
   * @brief Get X coordinate of center point.
   */
  inline value_type xCenter() const;

  /**
   * @brief Get Y coordinate of center point.
   */
  inline value_type yCenter() const;

  /**
   * @brief Set X coordinate of the center point.
   *
   * @param aX  new X coordinate
   */
  inline void setXCenter(value_type aX);

  /**
   * @brief Set Y coordinate of the center point.
   *
   * @param aY  new Y coordinate
   */
  inline void setYCenter(value_type aY);

  /**
   * @brief Set the center point.
   *
   * @param aX  X coordinate of the new center
   * @param aY  Y coordinate of the new center
   */
  inline void setCenter(value_type aX, value_type aY);

  /**
   * @brief Set the center point.
   *
   * @param aCenter  point representing the new center
   */
  inline void setCenter(const GenPoint<value_type>& aCenter);

  //@}


  /** @name Operators */
  //        =========
  //@{

  /**
   * @brief Assignment.
   *
   * @param anArc  an arc
   */
  GenArc<value_type>& operator=(const GenArc<value_type>& anArc);

  /**
   * @brief Same as function qgar::GenArc::eq
   */
  inline bool operator==(const GenArc<value_type>& anArc) const;

  /**
   * @brief Same as function qgar::GenArc::notEq.
   */
  inline bool operator!=(const GenArc<value_type>& anArc) const;

  //@}
  
  
  /**@name Functional operators */
  //       ====================
  //@{

   /**
   * @brief Equality.
   *
   * Return <b>true</b> if the current arc
   * and the given arc have the same coordinates.
   *
   * @param anArc  an arc
   */
  bool eq(const GenArc<value_type>& anArc) const;

  /**
   * @brief Inequality.
   *
   * Return <b>true</b> if the coordinates of the current
   * and given arcs are different.
   *
   * @param anArc an arc
   */
  bool notEq(const GenArc<value_type>& anArc) const;

  //@}


  /**@name Geometry: Translation */
  //       =====================
  //@{

  /**
   * @brief Translate current arc along X and Y axis.
   *
   * @param aTransX  X translation factor
   * @param aTransY  Y translation factor
   */
  virtual void translate(value_type aTransX, value_type aTransY);

  //@}


  /** @name Serialization/deserialization */
  //        =============================
  //@{

  /**
   * @brief Deserializes the current arc from an input stream.
   *
   * A serialized arc is represented as:
@verbatim
Arc(<SOURCE>)(<TARGET>)(<CENTER>)
@endverbatim
   *
   * @param anInStream The input stream
   */
  virtual std::istream& read(std::istream& anInStream);

  /**
   * @brief Serializes the current arc to an input stream.
   *
   * A serialized arc is represented as:
@verbatim
Arc(<SOURCE>)(<TARGET>)(<CENTER>)
@endverbatim
   *
   * @param anOutStream The output stream
   */
  virtual std::ostream& write(std::ostream& anOutStream) const;

  //@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:


  /** @name Structure of an arc */
  //        ===================
  //@{

  /**
   * @brief Center of the circle supporting the arc.
   */
  GenPoint<value_type> _center;

  //@}


  /** @name Implementation of pure virtual functions */
  //        ========================================
  //@{

  /**
   * @brief Update the geometrical structure
   *   when the source has been changed.
   *
   * Inherited from qgar::AbstractGenPrimitive.
   */
  virtual void updateSource();

  /**
   * @brief Update the geometrical structure
   *   when the target has been changed.
   *
   * Inherited from qgar::AbstractGenPrimitive.
   */
  virtual void updateTarget();

  /**
   * @brief Update the geometrical structure
   *   when both source and target have been changed.
   *
   * Inherited from qgar::AbstractGenPrimitive.
   */
  virtual void updateSourceTarget();

  //@}


// -------------------------------------------------------------------
}; // class GenArc




// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// P R E D E F I N E D    A R C    T Y P E S
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


/** @name Arc type names */
//        ==============
//@{

/**
 * @ingroup DS_PRIM_GEOM
 *
 * @brief Arc with <b>integer</b> coordinates.
 *
 * @see qgar::IArc
 */
typedef GenArc<int> Arc;

/**
 * @ingroup DS_PRIM_GEOM
 *
 * @brief Arc with <b>integer</b> coordinates.
 *
 * @see qgar::Arc
 */
typedef GenArc<int> IArc;

/**
 * @ingroup DS_PRIM_GEOM
 *
 * @brief Arc with <b>float</b> coordinates.
 */
typedef GenArc<float> FArc;

/**
 * @ingroup DS_PRIM_GEOM
 *
 * @brief Arc with <b>double</b> coordinates.
 */
typedef GenArc<double> DArc;

//@}


// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


} // namespace qgar


#endif /* ___QGAR_GENARC_H_INCLUDED__ */
