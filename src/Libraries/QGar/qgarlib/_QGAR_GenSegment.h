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


#ifndef ___QGAR_GENSEGMENT_H_INCLUDED__
#define ___QGAR_GENSEGMENT_H_INCLUDED__


/**
 * @file   _QGAR_GenSegment.h
 * @brief  Header file of class qgar::GenSegment.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   December 14, 2004  18:28
 * @since  Qgar 2.2
 */


// For RCS/CVS use: Do not delete
/* $Id: _QGAR_GenSegment.h,v 1.7 2005/11/23 17:08:31 masini Exp $ */



// STD
#include <iosfwd>  // Avoid including classes when not necessary
// QGAR
#include "ISerializable.h"
#include "math.h"



namespace qgar
{


/**
 * @class GenSegment _QGAR_GenSegment.h "qgarlib/GenSegment.h"
 * @ingroup DS_PRIM_GEOM
 * @brief Geometrical segment, with coordinates of type <b>T</b>.
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
    v

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
    |    + target
    v

    Y
@endverbatim
 * A segment is oriented: It is provided with a so-called
 * <i>source point</i> and a so-called <i>target point</i>,
 * which determine the orientation of the vector representing
 * the segment in geometrical computations.
 *
 * Computational geometry equations can be found in the FAQ section
 * of comp.graphics.algorithms and are based on
 * [<a href="Bibliography.html#Kirk-1992">Kirk,&nbsp;1992</a>],
 * pages 199-202, and
 * [<a href="Bibliography.html#ORourke-1994">O'Rourke,&nbsp;1994</a>],
 * pages 249-51.
 * </li>
 *
 * <li>
 * A segment has no attribute. For <i>graphical</i> segments,
 * typically resulting from vectorization and provided with attributes
 * (thickness, color, outline), see class qgar::GenQgarSegment.
 * </li>
 *
 * </ul>
 *
 * <b>Predefined types:</b>
 * <br> &nbsp; &nbsp; &nbsp; &nbsp; See submodule
 * <a href="group__DS__PRIM__GEOM.html"><b>Geometrical primitives</b></a>
 * for details.
 *
 * @author  <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date    June 23, 2003  15:05
 * @since   Qgar 1.0
 */
template <class T> class GenSegment

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
   * @brief Type of the source and target coordinates.
   */
  typedef T value_type;

  /**
   * @brief Reference to qgar::GenSegment::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::GenSegment::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::GenSegment::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::GenSegment::value_type.
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
   * Zero-length segment located at the origin of the coordinate system.
   *
   * @todo The created segment does not conform
   *       to the definition of a segment!
   */
  GenSegment();

  /**
   * @brief Copy constructor.
   */
  GenSegment(const GenSegment<value_type>& aSeg);

  /**
   * @brief Initialize from a Qgar segment.
   *
   * @param aQSeg a Qgar segment
   *
   * @warning This kind of conversion must be explicitely
   *   specified by the client.
   */
  explicit GenSegment(const GenQgarSegment<value_type>& aQSeg);

  /**
   * @brief Initialize from source and target points.
   *
   * @param aSource  source point
   * @param aTarget  target point
   */
  GenSegment(const GenPoint<value_type>& aSource,
	     const GenPoint<value_type>& aTarget);

  /**
   * @brief Initialize from coordinates.
   *
   * @param aXSource  X coordinate of the source point
   * @param aYSource  Y coordinate of the source point
   * @param aXTarget  X coordinate of the target point
   * @param aYTarget  X coordinate of the target point
   */
  GenSegment(const value_type aXSource,
	     const value_type aYSource,
	     const value_type aXTarget,
	     const value_type aYTarget);

  //@}


  /**@name Destructor */
  //       ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  virtual ~GenSegment();

  //@}


  /**@name Copy */
  //       ====
  //@{

  /**
   * @brief Return a deep copy of the surrent segment.
   */  
  virtual GenSegment<value_type>* clone() const;

  //@}


  /** @name Access to geometrical features */
  //        ==============================
  //@{

  /**
   * @brief Get length of the segment.
   */
  inline double length() const;

  /**
   * @brief Get squared length of the segment.
   */
  double sqr_length() const;

  /**
   * @brief Distance between point <b>(0,0)</b> and its perpendicular
   *   projection onto the line supporting the segment.
   *
   * Always positive.
   */
  double rho() const;

  /**
   * @brief Angle between the X axis and the segment,
   * in <b>[0,2PI[</b> radians.
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
   * @brief Same as qgar::GenSegment::theta.
   */
  inline double angle() const;

  /**
   * @brief Angle between the X axis and the segment,
   *   in <b>[0,PI[</b> radians.
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
   * @brief Same as qgar::GenSegment::theta,
   *   but the result is given in <b>[0,360[</b> degrees.
   */
  inline double thetaDegrees() const;

  /**
   * @brief Same as qgar::GenSegment::theta,
   *   but the result is given in <b>[0,360[</b> degrees.
   */
  inline double angleDegrees() const;

  /**
   * @brief Same as qgar::GenSegment::slope,
   *   but the result is given in <b>[0,180[</b> degrees.
   */
  inline double slopeDegrees() const;

  //@}


  /**@name Geometrical predicates */
  //       ======================
  //@{

  /**
   * @brief Return <b>true</b> if the given point approximately
   *   belongs to the current segment.
   *
   * Here, ''to belong'' means to be at a distance smaller or equal
   * to the given threshold from somed point between the source
   * and the target of the segment.
   *
   * @param c      a point
   * @param aDist  threshold used to decide whether the given point
   *   belongs to the segment (default qgar::Math::epsilonD)
   *
   * @todo Use values computed for 'r' to get the distance between
   * the point and the segment, instead of using function qgar::qgDist,
   * which computes again these values.
   */
  inline bool
  contains(const GenPoint<T>& c, double aDist = Math::epsilonD());
  
  //@}


  /**@name Operators */
  //       =========
  //@{

  /**
   * @brief Assignment.
   *
   * @param aSeg  a segment
   */
  inline GenSegment<value_type>&
  operator=(const GenSegment<value_type>& aSeg);

  /**
   * @brief Same as function qgar::GenSegment::eq
   */
  inline bool
  operator==(const GenSegment<value_type>& aSeg) const;

  /**
   * @brief Same as function qgar::GenSegment::notEq.
   */
  inline bool
  operator!=(const GenSegment<value_type>& aSeg) const;

  //@}
  

  /**@name Functional operators */
  //       ====================
  //@{

   /**
   * @brief Equality.
   *
   * @param aSeg  a segment
   *
   * @return <b>true</b> if the current segment
   * and the given segment have the same coordinates.
   */
  bool eq(const GenSegment<value_type>& aSeg) const;

  /**
   * @brief Inequality.
   *
   * @param aSeg a segment
   *
   * @return <b>true</b> if the coordinates of the current
   * and given segments are different.
   */
  bool notEq(const GenSegment<value_type>& aSeg) const;

  //@}


  /**@name Geometry: Translation */
  //       =====================
  //@{

  /**
   * @brief Translate current segment along X and Y axis.
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
   * @brief Deserializes the current segment from an input stream.
   *
   * A serialized segment is represented as:
@verbatim
  Segment(<SOURCE>)(<TARGET>)
@endverbatim
   *
   * @param anInStream  the input stream
   *
   * @see qgar::qgReadObjName, qgar::qgReadObjData
   */
  virtual std::istream& read(std::istream& anInStream);

  /**
   * @brief Serializes the current segment to an input stream.
   *
   * A serialized segment is represented as:
@verbatim
  Segment(<SOURCE>)(<TARGET>)
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
  

  /** @name Updates subsequent to source and target modifications */
  //        =====================================================
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
   */
  virtual void updateTarget();

  /**
   * @brief Update the geometrical structure
   *   when both source and target have been changed.
   */
  virtual void updateSourceTarget();

  //@}


// -------------------------------------------------------------------
};  // class GenSegment




// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// P R E D E F I N E D    S E G M E N T    T Y P E S
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


/** @name Segment type names */
//        ==================
//@{

/**
 * @ingroup DS_PRIM_GEOM 
 *
 * @brief Segment with <b>integer</b> coordinates.
 *
 * @see qgar::ISegment
 */
typedef GenSegment<int> Segment;

/**
 * @ingroup DS_PRIM_GEOM 
 *
 * @brief Segment with <b>integer</b> coordinates.
 *
 * @see qgar::Segment
 */
typedef GenSegment<int> ISegment;

/**
 * @ingroup DS_PRIM_GEOM 
 *
 * @brief Segment with <b>float</b> coordinates.
 */
typedef GenSegment<float> FSegment;

/**
 * @ingroup DS_PRIM_GEOM 
 *
 * @brief Segment with <b>double</b> coordinates.
 */
typedef GenSegment<double> DSegment;

//@}


// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


} // namespace qgar 


#endif /* ___QGAR_GENSEGMENT_H_INCLUDED__ */
