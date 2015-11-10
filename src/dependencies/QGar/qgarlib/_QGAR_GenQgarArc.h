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


#ifndef ___QGAR_GENQGARARC_H_INCLUDED__
#define ___QGAR_GENQGARARC_H_INCLUDED__


/**
 * @file _QGAR_GenQgarArc.h
 *
 * @brief Header file of class qgar::GenQgarArc.
 *
 * @warning <b>Not to be used as include file!</b>
 * <br>When working with primitives, use file primitives.h.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   December 14, 2004  17:17
 * @since  Qgar 2.2
 */

// For RCS/CVS use: Do not delete
/* $Id: _QGAR_GenQgarArc.h,v 1.7 2007/02/14 17:34:06 masini Exp $ */



// STD
#include <iosfwd>  // Avoid including classes when not necessary
// QGAR
#include "ISerializable.h"



namespace qgar
 {


/**
 * @ingroup DS_PRIM_QGAR
 *
 * @class GenQgarArc _QGAR_GenQgarArc.h "qgarlib/primitives.h"
 *
 * @brief Arc of circle, so-called <i>Qgar arc</i>,
 * with coordinates of type <b>T</b>.
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
 * A Qgar arc is oriented: It is provided with a so-called
 * <i>source point</i> and a so-called <i>target point</i>,
 * which determine the part of the circle supporting the arc.
 *</li>
 *
 * <li>
 * A Qgar arc is provided with attributes: thickness, color, 
 * and outline. When such features are useless, see class
 * qgar::GenArc (for geometrical arcs).
 * </li>
 *
 * </ul>
 * 
 * <b>Predefined types:</b>
 * <br> &nbsp; &nbsp; &nbsp; &nbsp; See submodule
 * <a href="group__DS__PRIM__QGAR.html"><b>Qgar (graphical) primitives</b></a>
 * for details.
 *
 * @warning
 *   <b>The coherence of the data structure of a Qgar arc
 *   after modifications of its source and/or its target
 *   and/or its center is the user's responsibility!</b>
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   June 20, 2003  17:35
 * @since  Qgar 2.1
 */
template <class T> class GenQgarArc

  : public AbstractGenQgarPrimitive<T>,
    public ISerializable

{
// -------------------------------------------------------------------
// T Y P E   D E F I N I T I O N S
// -------------------------------------------------------------------
public:

  /** @name Types related to Qgar arcs */
  //        ==========================
  //@{

  /**
   * @brief Type of the coordinates of the source, target and center.
   */
  typedef T value_type;

  /**
   * @brief Reference to qgar::GenQgarArc::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::GenQgarArc::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::GenQgarArc::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::GenQgarArc::value_type.
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
   * @param aThickness  thickness (default <b>1</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline   (default qgar::QGE_OUTLINE_DEFAULT) 
   *
   * @todo The created arc does not conform
   *   to the definition of an arc!
   */
  GenQgarArc(int        aThickness = 1,
	     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
	     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  /**
   * @brief Copy constructor.
   */
  GenQgarArc(const GenQgarArc<value_type>& aQArc);

  /**
   * @brief Initialize from a geometrical arc.
   *
   * @param anArc      a geometrical arc
   * @param aThickness thickness (default <b>1</b>)
   * @param aColor     color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline  outline   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  GenQgarArc(const GenArc<value_type>& anArc,
	     int        aThickness = 1,
	     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
	     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  /**
   * @brief Initialize from three points.
   *
   * @param aSource     source point
   * @param aTarget     target point
   * @param aCenter     center point
   * @param aThickness  thickness (default <b>1</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline   (default qgar::QGE_OUTLINE_DEFAULT) 
   */
  GenQgarArc(const GenPoint<value_type>& aSource,
	     const GenPoint<value_type>& aTarget,
	     const GenPoint<value_type>& aCenter,
	     int        aThickness = 1,
	     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
	     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  //@}


  /**@name Destructor */
  //       ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  virtual ~GenQgarArc();

  //@}


  /**@name Copy */
  //       ====
  //@{

  virtual GenQgarArc<value_type>* clone() const;

  //@}


  /** @name Access to geometrical features */
  //        ==============================
  //@{

  /**
   * @brief Get the structure implementing
   *        the geometrical aspect of a Qgar arc.
   */
  inline const GenArc<value_type>& accessGeomStructure() const;

  /**
   * @brief Get the radius.
   */
  inline double radius() const;

  /**
   * @brief Get length of the arc.
   */
  inline double length() const;

  /**
   * @brief Get the angle of the arc, in [0, 2PI] radians.
   *
   * Always positive.
   */
  inline double angle() const;

  /**
   * @brief Get the angle of the arc, in [0, 360] degrees.
   *
   * Always positive.
   */
  inline double angleDegrees() const;

  /**
   * @brief Get the so-called source angle.
   *
   * It is the angle between the vector joining the center to
   * the source point and the X axis, in [0, 2PI] radians.
   */
  inline double sourceAngle() const;

  /**
   * @brief Get the source angle, in [0, 360] degrees.
   */
  inline double sourceAngleDegrees() const;

  /**
   * @brief Get the so-called target angle.
   *
   * Its is the angle between the vector joining the center to
   * the target point and the X axis, in [0, 2PI] radians.
   */
  inline double targetAngle() const;

   /**
   * @brief Get the target angle, in [0, 360] degrees.
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
  value_type xCenter() const;

  /**
   * @brief Get Y coordinate of center point.
   */
  value_type yCenter() const;

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
  void setCenter(value_type aX, value_type aY);

  /**
   * @brief Set the center point.
   *
   * @param aCenter  point representing the new center
   */
  void setCenter(const GenPoint<value_type>& aCenter);

  //@}


  /** @name Operators */
  //        =========
  //@{

  /**
   * @brief Assignment.
   *
   * @param aQArc  a Qgar arc
   */
  GenQgarArc<value_type>&
  operator=(const GenQgarArc<value_type>& aQArc);

  /**
   * @brief Same as function qgar::GenQgarArc::eq
   */
  inline bool
  operator==(const GenQgarArc<value_type>& aQArc) const;

  /**
   * @brief Same as function qgar::GenQgarArc::notEq.
   */
  inline bool
  operator!=(const GenQgarArc<value_type>& aQArc) const;

  //@}


  /**@name Functional operators */
  //       ====================
  //@{

  /**
   * @brief Equality.
   *
   * @param aQArc  a Qgar arc
   *
   * @return <b>true</b> if the current arc
   * and the given arc have the same coordinates,
   * regardless other features.
   */
  inline bool eq(const GenQgarArc<value_type>& aQArc) const;

   /**
   * @brief Equality.
   *
   * @param aQArc  a Qgar arc
   *
   * @return <b>true</b> if the current arc
   * and the given arc have the same coordinates and attributes.
   */
  bool equal(const GenQgarArc<value_type>& aQArc) const;

  /**
   * @brief Inequality.
   *
   * @param aQArc a Qgar arc
   *
   * @return <b>true</b> if the coordinates
   * of the current arc and of the given arc are different,
   * regardless other features.
   */
  inline bool notEq(const GenQgarArc<value_type>& aQArc) const;

  /**
   * @brief Inequality.
   *
   * @param aQArc a Qgar arc
   *
   * @return <b>true</b> if the coordinates or attributes
   * of the current arc and of the given arc are different.
   */
  bool notEqual(const GenQgarArc<value_type>& aQArc) const;

  //@}


  /** @name Serialization/deserialization */
  //        =============================
  //@{

  /**
   * @brief Deserializes the current arc from an input stream.
   *
   * A serialized Qgar arc is represented as:
@verbatim
QgarArc(<GEOMETRICAL STRUCTURE>)(<THICKNESS>)(<COLOR>)(<OUTLINE>)
@endverbatim
   *
   * @param anInStream The input stream
   */
  virtual std::istream& read(std::istream& anInStream);


  /**
   * @brief Serializes the current arc to an input stream.
   *
   * A serialized Qgar arc is represented as:
@verbatim
QgarArc(<GEOMETRICAL STRUCTURE>)(<THICKNESS>)(<COLOR>)(<OUTLINE>)
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


  /** @name Geometrical structure of a Qgar arc */
  //        ===================================
  //@{

  /**
   * @brief Geometrical structure.
   */
  GenArc<value_type> _geomStructure;

  //@}


  /**@name Non-protected access to the geometrical aspect */
  //       ==============================================
  //@{

  /**
   * @brief Return the geometrical aspect.
   *
   * It may then be modified using appropriate
   * transformation function members.
   */
  virtual AbstractGenPrimitive<value_type>& getGeomStructure();

  //@}


// -------------------------------------------------------------------
}; // class GenQgarArc




// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// P R E D E F I N E D    Q G A R    A R C    T Y P E S
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


/** @name Qgar arc type names */
//        ===================
//@{

/**
 * @ingroup DS_PRIM_QGAR
 *
 * @brief Qgar arc with <b>integer</b> coordinates.
 *
 * @see qgar::IQgarArc
 */
typedef GenQgarArc<int> QgarArc;

/**
 * @ingroup DS_PRIM_QGAR
 *
 * @brief Qgar arc with <b>integer</b> coordinates.
 *
 * @see qgar::QgarArc
 */
typedef GenQgarArc<int> IQgarArc;

/**
 * @ingroup DS_PRIM_QGAR
 *
 * @brief Qgar arc with <b>float</b> coordinates.
 */
typedef GenQgarArc<float> FQgarArc;

/**
 * @ingroup DS_PRIM_QGAR
 *
 * @brief Qgar arc with <b>double</b> coordinates.
 */
typedef GenQgarArc<double> DQgarArc;

//@}


// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


} // namespace qgar


#endif /* ___QGAR_GENQGARARC_H_INCLUDED__ */
