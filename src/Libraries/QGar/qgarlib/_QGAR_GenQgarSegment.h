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


#ifndef ___QGAR_GENQGARSEGMENT_H_INCLUDED__
#define ___QGAR_GENQGARSEGMENT_H_INCLUDED__


/**
 * @file     _QGAR_GenQgarSegment.h
 * @brief    Header file of class qgar::GenQgarSegment.
 *
 * @warning <b>Not to be used as include file!</b>
 * <br>When working with primitives, use file primitives.h.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date     December 15, 2004  14:14
 * @since    Qgar 2.2
 */


// For RCS/CVS use: Do not delete
/* $Id: _QGAR_GenQgarSegment.h,v 1.7 2005/11/23 17:08:31 masini Exp $ */



// STD
#include <iosfwd>  // Avoid including classes when not necessary
// QGAR
#include "ISerializable.h"
#include "math.h"



namespace qgar
{


/**
 * @class GenQgarSegment _QGAR_GenQgarSegment.h "qgarlib/primitives.h"
 * @ingroup DS_PRIM_QGAR
 * @brief Graphical segment, so-called <i>Qgar segment</i>,
 *   with coordinates of type <b>T</b>.
 *
 * It typically results from vectorization.
 *
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
 * The origin of the coordinate system is at top left corner
 * and angles are clockwise from the X axis.
 * </li>
 *
 * <li>
@verbatim
   O
    +---------------> X
    |
    |        + source
    |       /
    |      /
    |     v
    V    + target

    Y
@endverbatim
 * A Qgar segment is oriented: It is provided with a so-called
 * <i>source point</i> and a so-called <i>target point</i>,
 * which determine the orientation of the vector representing
 * the segment in geometrical computations.
 * </li>
 *
 * <li>
 * A Qgar segment is provided with attributes: thickness, color,
 * and outline. When such features are useless, see class
 * qgar::GenSegment (for geometrical segments).
 * </li>
 *
 * </ul>
 *
 * <b>Predefined types:</b>
 * <br> &nbsp; &nbsp; &nbsp; &nbsp; See submodule
 * <a href="group__DS__PRIM__QGAR.html"><b>Qgar (graphical) primitives</b></a>
 * for details.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date     July 2, 2001  18:07
 * @since    Qgar 2.1
 */
template <class T>
class GenQgarSegment

  : public AbstractGenQgarPrimitive<T>,
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
   * @brief Type of the source and target coordinates.
   */
  typedef T value_type;

  /**
   * @brief Reference to qgar::GenQgarSegment::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::GenQgarSegment::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::GenQgarSegment::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::GenQgarSegment::value_type.
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
   * @brief Default constructor.
   *
   * Zero-length segment located at <b>(0, 0)</b>.
   *
   * @param aThickness  thickness (default <b>1</b>)
   * @param aColor      color (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline (default qgar::QGE_OUTLINE_DEFAULT) 
   *
   * @todo The created Qgar segment does not conform
   *       to the definition of a segment!
   */
  GenQgarSegment(int        aThickness = 1,
                 QGEcolor   aColor     = QGE_COLOR_DEFAULT,		 
		 QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  /**
   * @brief Copy constructor.
   */
  GenQgarSegment(const GenQgarSegment<value_type>& aQSeg);

  /**
   * @brief Initialize from a geometrical segment.
   *
   * @param aSeg       a segment
   * @param aThickness thickness (default <b>1</b>)
   * @param aColor     color (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline  outline (default qgar::QGE_OUTLINE_DEFAULT)
   */
  explicit GenQgarSegment(const GenSegment<value_type>& aSeg,
			  int        aThickness = 1,
			  QGEcolor   aColor     = QGE_COLOR_DEFAULT,
			  QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  /**
   * @brief Initialize from source and target points.
   *
   * @param aSource    source point
   * @param aTarget    target point
   * @param aThickness thickness (default <b>1</b>)
   * @param aColor     color (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline  outline (default qgar::QGE_OUTLINE_DEFAULT)
   */
  GenQgarSegment(const GenPoint<value_type>& aSource,
		 const GenPoint<value_type>& aTarget,
		 int        aThickness = 1,
		 QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		 QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  /**
   * @brief Initialize from coordinates.
   *
   * @param aXSource   X coordinate of the source point
   * @param aYSource   Y coordinate of the source point
   * @param aXTarget   X coordinate of the target point
   * @param aYTarget   X coordinate of the target point
   * @param aThickness thickness (default <b>1</b>)
   * @param aColor     color (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline  outline (default qgar::QGE_OUTLINE_DEFAULT)
   */
  GenQgarSegment(value_type aXSource,
		 value_type aYSource,
		 value_type aXTarget,
		 value_type aYTarget,
		 int        aThickness = 1,
		 QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		 QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  virtual ~GenQgarSegment();

  //@}


  /** @name Copy */
  //        ====
  //@{

  virtual GenQgarSegment<value_type>* clone() const;

  //@}


  /** @name Access to geometrical features */
  //        ==============================
  //@{

  /**
   * @brief Get the structure implementing
   * the geometrical aspect of a Qgar segment.
   */
  inline const GenSegment<value_type>& accessGeomStructure() const;

  /**
   * @brief Get length of the segment.
   */
  inline double length() const;

  /**
   * @brief Get squared length of the segment.
   */
  inline double sqr_length() const;

  /**
   * @brief Distance between point <b>(0,0)</b> and its perpendicular
   * projection onto the line supporting the current segment.
   *
   * Always positive.
   */
  inline double rho() const;

  /**
   * @brief Angle between the X axis and the segment,
   *   in [0, 2PI[ radians.
   *
@verbatim
                                           ----->/
 O                             O          /     /
  +------------------> X        +---------|-------------> X
  |    \    |                   |         |   /  |
  |     \ <-' angle             |   angle \_ /__/
  |      \                      |           /
  |       + source              |          + target
  |        \                    |         ^
  |         \                   |        /
  |          v                  |       /
  v           + target          v      + source

  Y                             Y
@endverbatim
   *
   * @warning The current segment is assimilited to a vector
   *   joining its source to its target.
   */
  inline double theta() const;

  /**
   * @brief Same as qgar::GenQgarSegment::theta.
   */
  inline double angle() const;

  /**
   * @brief Angle between the X axis and the segment, in [0, PI[ radians.
   *
@verbatim
 O                           O
  +------------------> X      +-----------------> X
  |    \    |                 |    \    |
  |     \ <-' angle           |     \ <-' angle
  |      \                    |      \
  |       + source            |       + target
  |        \                  |        \
  |         \                 |         \
  |          \                |          \
  v           + target        v           + source

  Y                           Y
@endverbatim
   *
   * @warning The current segment is not assimilited to a vector.
   */
  inline double slope() const;

  /**
   * @brief Same as qgar::GenQgarSegment::theta,
   * but the result is given in <b>[0,360[</b> degrees.
   */
  inline double thetaDegrees() const;

  /**
   * @brief Same as qgar::GenQgarSegment::theta,
   * but the result is given in <b>[0,360[</b> degrees.
   */
  inline double angleDegrees() const;

  /**
   * @brief Same as qgar::GenQgarSegment::slope,
   * but the result is given in <b>[0,180[</b> degrees.
   */
  inline double slopeDegrees() const;

  //@}

  
  /**@name Geometrical predicates */
  //       ======================
  //@{

  /**
   * @brief Return <b>true</b> if the given point approximately
   *   belongs to the current Qgar segment.
   *
   * Here, ''to belong'' means to be at a distance smaller or equal
   * to the given threshold from some point between the source
   * and the target of the segment.
   *
   * @param c      a point
   * @param aDist  threshold used to decide whether the given point
   *   belongs to the segment (default qgar::Math::epsilonD)
   */
  inline bool
  contains(const GenPoint<T>& c, double aDist = Math::epsilonD());

  //@}

  
  /** @name Operators */
  //        =========
  //@{

  /**
   * @brief Assignment.
   *
   * @param aQSeg  a Qgar segment
   */
  GenQgarSegment<value_type>&
  operator=(const GenQgarSegment<value_type>& aQSeg);

  /**
   * @brief Same as function qgar::GenQgarSegment::eq
   */
  inline bool
  operator==(const GenQgarSegment<value_type>& aQSeg) const;

  /**
   * @brief Same as function qgar::GenQgarSegment::notEq.
   */
  inline bool
  operator!=(const GenQgarSegment<value_type>& aQSeg) const;

  //@}


  /**@name Functional operators */
  //       ====================
  //@{

   /**
   * @brief Equality.
   *
   * @param aQSeg  a segment
   *
   * @return <b>true</b> if the current segment
   * and the given segment have the same coordinates,
   * regardless other features.
   */
  inline bool eq(const GenQgarSegment<value_type>& aQSeg) const;

   /**
   * @brief Equality.
   *
   * @param aQSeg  a segment
   *
   * @return <b>true</b> if the current segment
   * and the given segment have the same coordinates and attributes.
   */
  bool equal(const GenQgarSegment<value_type>& aQSeg) const;

  /**
   * @brief Inequality.
   *
   * @param aQSeg a segment
   *
   * @return <b>true</b> if the coordinates
   * of the current segment and of the given segment are different,
   * regardless other features.
   */
  inline bool notEq(const GenQgarSegment<value_type>& aQSeg) const;

  /**
   * @brief Inequality.
   *
   * @param aQSeg a segment
   *
   * @return <b>true</b> if the coordinates or attributes
   * of the current segment and of the given segment are different.
   */
  bool notEqual(const GenQgarSegment<value_type>& aQSeg) const;

  //@}


  /** @name Serialization/deserialization */
  //        =============================
  //@{

  /**
   * @brief Deserializes the current segment from an input stream.
   *
   * A serialized Qgar segment is represented as:
@verbatim
QgarSegment(<GEOMETRICAL STRUCTURE>)(<THICKNESS>)(<COLOR>)(<OUTLINE>)
@endverbatim
   *
   * @param anInStream the input stream
   */
  virtual std::istream& read(std::istream& anInStream);


  /**
   * @brief Serializes an object to an input stream.
   *
   * A serialized Qgar segment is represented as:
@verbatim
QgarSegment(<GEOMETRICAL STRUCTURE>)(<THICKNESS>)(<COLOR>)(<OUTLINE>)
@endverbatim
   *
   * @param anOutStream  the output stream
   */
  virtual std::ostream& write(std::ostream& anOutStream) const;

  //@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:


  /** @name Geometrical structure of a Qgar segment */
  //        =======================================
  //@{

  /**
   * @brief Structure implementing the geometrical aspect.
   */
  GenSegment<value_type> _geomStructure;

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
  inline AbstractGenPrimitive<value_type>& getGeomStructure();

  //@}


// -------------------------------------------------------------------
}; // class GenQgarSegment




// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// P R E D E F I N E D    Q G A R    S E G M E N T    T Y P E S
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


/** @name Qgar Segment type names */
//        =======================
//@{

/**
 * @ingroup DS_PRIM_QGAR
 *
 * @brief Qgar segment with <b>integer</b> coordinates.
 *
 * @see qgar::IQgarSegment
 */
typedef GenQgarSegment<int> QgarSegment;

/**
 * @ingroup DS_PRIM_QGAR
 *
 * @brief Qgar segment with <b>integer</b> coordinates.
 *
 * @see qgar::QgarSegment
 */
typedef GenQgarSegment<int> IQgarSegment;

/**
 * @ingroup DS_PRIM_QGAR
 *
 * @brief Qgar segment with <b>float</b> coordinates.
 */
typedef GenQgarSegment<float> FQgarSegment;

/**
 * @ingroup DS_PRIM_QGAR
 *
 * @brief Qgar segment with <b>double</b> coordinates.
 */
typedef GenQgarSegment<double> DQgarSegment;

//@}


// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


} // namespace qgar


#endif /* ___QGAR_GENQGARSEGMENT_H_INCLUDED__ */
