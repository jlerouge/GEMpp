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


#ifndef ___QGAR_GENPOLYLINE_H_INCLUDED__
#define ___QGAR_GENPOLYLINE_H_INCLUDED__


/**
 * @file    _QGAR_GenPolyline.h
 * @brief   Header file of class qgar::GenPolyline.
 *
 * @warning <b>Not to be used as include file!</b>
 * <br>When working with primitives, use file primitives.h.
 *
 * @author  <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date    December 14, 2004  18:01
 * @since   Qgar 2.2
 */


// For RCS/CVS use: Do not delete
/* $Id: _QGAR_GenPolyline.h,v 1.7 2006/03/30 12:49:41 masini Exp $ */



// STD
#include <deque>
#include <iosfwd>  // Avoid including classes when not necessary
#include <list>
#include <vector>
// QGAR
#include "ISerializable.h"
namespace qgar
{
  // Avoid #include's when not necessary
  class QgarErrorUser;
}



namespace qgar
{

/**
 * @ingroup DS_PRIM_GEOM
 *
 * @class GenPolyline _QGAR_GenPolyline.h "qgarlib/primitives.h"
 *
 * @brief Geometrical polyline, with coordinates of type <b>T</b>.
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
 * The origin of the coordinate system is at top left corner.
 * Angles are clockwise from the X axis.
 * </li>
 *
 * <li>
 * A polyline is a series of points, implemented as a STL
 * <b>deque</b>): Each point represents a vertex and two
 * consecutive points represent a segment.
 * </li>
 *
 * <li>
 * A polyline must always be provided with at least 2 vertices.
 * </li>
 *
 * <li>
 * A polyline is oriented: It is provided with a so-called
 * <i>source</i> vertex (first of the series)
 * and a so-called <i>target</i> vertex (last of the series).
 * </li>
 *
 * <li>
 * A polyline does not define any closed geometrical shape,
 * like a polygon. In particular, the source and target vertices
 * do not define a segment.
 * </li>
 *
 * <li>
 * A polyline has no attribute. For <i>graphical</i> polylines,
 * typically resulting from vectorization and provided with attributes
 * (thickness, color, outline), see class qgar::GenQgarPolyline.
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
 *   <b>The coherence of the data structure of a polyline after
 *   modifications of its source and/or its target and/or its
 *   other vertices is the user's responsibility!</b>
 *
 *
 * @author  <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date    June 24, 2003  18:00
 * @since   Qgar 2.1
 */
template <class T> class GenPolyline

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
   * @brief Type of the vertices coordinates.
   */
  typedef T value_type;

  /**
   * @brief Reference to qgar::GenPolyline::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::GenPolyline::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::GenPolyline::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::GenPolyline::value_type.
   */
  typedef const value_type* const_pointer;

  /**
   * @brief Type of the vertices container.
   */
  typedef std::deque< GenPoint<value_type> > vertices_type;

  /**
   * @brief Reference to qgar::GenPolyline::vertices_type.
   */
  typedef vertices_type& vertices_reference;

  /**
   * @brief Constant reference to qgar::GenPolyline::vertices_type.
   */
  typedef const vertices_type& vertices_const_reference;

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
   * @todo The created polyline does not conform to the definition
   *   of a polyline: The vertices <b>deque</b> is empty whereas
   *   it should contain at least 2 elements!
   */
  GenPolyline();

  /**
   * @brief Copy constructor.
   *
   * @param aPoly  a polyline
   */
  GenPolyline(const GenPolyline<value_type>& aPoly);

  /**
   * @brief Initialize from a Qgar polyline.
   *
   * The order of the vertices is preserved in the resulting polyline.
   *
   * @param aQPoly  a Qgar polyline
   *
   * @warning This kind of conversion must be explicitely
   *   specified by the client.
   */
  explicit GenPolyline(const GenQgarPolyline<value_type>& aQPoly);

  /**
   * @brief Initialize from a Qgar segment.
   *
   * The source (resp. target) of the resulting polyline
   * is the source (resp. target) of the segment.
   *
   * @param aQSeg  a Qgar segment
   *
   * @warning This kind of conversion must be explicitely
   *   specified by the client.
   */
  explicit GenPolyline(const GenQgarSegment<value_type>& aQSeg);

  /**
   * @brief Initialize from a (geometrical) segment.
   *
   * The source (resp. target) of the resulting polyline
   * is the source (resp. target) of the segment.
   *
   * @param aSeg  a (geometrical) segment
   *
   * @warning This kind of conversion must be explicitely
   *   specified by the client.
   */
  explicit GenPolyline(const GenSegment<value_type>& aSeg);

  /**
   * @brief Initialize from two vertices: source and target.
   *
   * @param aSource  source vertex 
   * @param aTarget  target vertex
   */
  GenPolyline(const GenPoint<value_type>& aSource,
	      const GenPoint<value_type>& aTarget);

   /**
   * @brief Initialize from a list of at least two vertices.
   *
   * The order of the given vertices is preserved
   * in the resulting polyline.
   *
   * @param aPtList  a list of at least two vertices
   *
   * @warning This kind of conversion must be explicitely
   *   specified by the client.
   *
   * @exception qgar::QgarErrorUser
   *   cannot create a polyline with less than 2 vertices
   */
  explicit
  GenPolyline(const std::list< GenPoint<value_type> >& aPtList)
   ;

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  virtual ~GenPolyline();

  //@}


  /**@name Copy */
  //       ====
  //@{

  virtual GenPolyline<value_type>* clone() const;

  //@}  


  /** @name Operators */
  //        =========
  //@{

  /**
   * @brief Assignment.
   *
   * @param aPoly  a polyline
   */
  inline GenPolyline<value_type>&
  operator=(const GenPolyline<value_type>& aPoly);

  //@}


  /** @name Access to vertices */
  //        ==================
  //@{

  /**
   * @brief Get number of vertices.
   */
  inline int size() const;

  /**
   * @brief Get the vertices.
   */
  inline vertices_const_reference accessVertices() const;

  /**
   * @brief Give non-protected access to the vertices.
   *
   * Vertices may then be directly modified using appropriate
   * transformation function members.
   */
  inline vertices_reference getVertices();

  /**
   * @brief Get a copy of the vertices.
   */
  inline vertices_type vertices() const;

  //@}


  /** @name Insert vertices */
  //        ===============
  //@{

  /**
   * @brief Insert a point as new source.
   *
   * @param aPt  a point
   */
  GenPolyline<value_type>&
  appendSource(const GenPoint<value_type>& aPt);

  /**
   * @brief Insert a point as new target.
   *
   * @param aPt  a point
   */
  GenPolyline<value_type>&
  appendTarget(const GenPoint<value_type>& aPt);

  /**
   * @brief Appends a polyline.
   *
   * @param aPoly  the polyline to be appended
   *
   * @return a reference to the current polyline
   */
  GenPolyline<value_type>&
  append(const GenPolyline<value_type>& aPoly);

  /**
   * @brief Appends a Qgar polyline.
   *
   * @param aQPoly  the Qgar polyline to be appended
   *
   * @return a reference to the current polyline
   */
  GenPolyline<value_type>&
  append(const GenQgarPolyline<value_type>& aQPoly);

  /**
   * @brief Appends a set of vertices to a polyline.
   *
   * The given points are inserted after the target point.
   * The order of the given vertices is preserved
   * in the resulting polyline.
   * The last point of the vector becomes the new target.
   *
   * @param aPtVect  the vector of points to be appended
   *
   * @return a reference to the current polyline
   */
  GenPolyline<value_type>&
  append(const std::vector< GenPoint<value_type> >& aPtVect);

  //@}


  /** @name Remove vertices */
  //        ===============
  //@{

  /**
   * @brief Remove a vertex from the polyline.
   *
   * @param aPt  a point
   *
   * @exception qgar::QgarErrorUser
   *   no removal in a polyline with 2 vertices
   */
  GenPolyline<value_type>&
  remove(const GenPoint<value_type>& aPt)
   ;

  //@}


  /** @name Conversions of the vertices */
  //        ===========================
  //@{

  /**
   * @brief Get a vector of points from the vertices.
   */
  std::vector< GenPoint<value_type> > toPointVector();

  /**
   * @brief Get a <b>list</b> of (geometrical) segments
   *        from the vertices.
   */
  std::list< GenSegment<value_type> > toSegList();

  /**
   * @brief Get a <b>list</b> of Qgar segments, provided
   *   with given attributes, from the vertices.
   *
   * @param aThickness  thickness (default <b>1</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline   (default qgar::QGE_OUTLINE_DEFAULT) 
   */
  std::list< GenQgarSegment<value_type> > 
  toQgarSegList(int        aThickness = 1,
		QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  //@}


  /**@name Geometry: Translation */
  //       =====================
  //@{

  /**
   * @brief Translate current polyline along X and Y axis.
   * @param aTransX  X translation factor
   * @param aTransY  Y translation factor
   */
  virtual void translate(value_type aTransX, value_type aTransY);

  //@}


  /** @name Serialization/deserialization */
  //        =============================
  //@{

  /**
   * @brief Deserializes the current polyline from an input stream.
   *
   * A serialized polyline is represented as:
@verbatim
Polyline(<SOURCE>)(<TARGET>)(<VERTICES COUNT>)(<VERTICE 1>)..(<VERTICE n>)
@endverbatim
   *
   * @param anInStream  the input stream
   */
  inline virtual std::istream& read(std::istream& anInStream);

  /**
   * @brief Serializes the current polyline to an input stream.
   *
   * A serialized polyline is represented as:
@verbatim
Polyline(<SOURCE>)(<TARGET>)(<VERTICES COUNT>)(<VERTICE 1>)..(<VERTICE n>)
@endverbatim
   *
   * @param anOutStream  the output stream
   */
  inline virtual std::ostream& write(std::ostream& anOutStream) const;

  //@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:


  /** @name Structure of a polyline */
  //        =======================
  //@{

  /**
   * @brief Vertices.
   */
  vertices_type _vertices;

  //@}


  /** @name Updates subsequent to source and target modifications */
  //        =====================================================
  //@{

  /**
   * @brief Update the geometrical structure
   *        when the source has been changed.
   */
  virtual void updateSource();

  /**
   * @brief Update the geometrical structure
   *        when the target has been changed.
   */
  virtual void updateTarget();

  /**
   * @brief Update the geometrical structure
   *        when both source and target have been changed.
   */
  virtual void updateSourceTarget();

  //@}


// -------------------------------------------------------------------
}; // class GenPolyline




// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// P R E D E F I N E D    P O L Y L I N E    T Y P E S
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


/** @name Polyline type names */
//        ===================
//@{

/**
 * @ingroup DS_PRIM_GEOM
 *
 * @brief Polyline with <b>integer</b> coordinates.
 *
 * @see qgar::IPolyline
 */
typedef GenPolyline<int> Polyline;

/**
 * @ingroup DS_PRIM_GEOM
 *
 * @brief Polyline with <b>integer</b> coordinates.
 *
 * @see qgar::Polyline
 */
typedef GenPolyline<int> IPolyline;

/**
 * @ingroup DS_PRIM_GEOM
 *
 * @brief Polyline with <b>float</b> coordinates.
 */
typedef GenPolyline<float> FPolyline;

/**
 * @ingroup DS_PRIM_GEOM
 *
 * @brief Polyline with <b>double</b> coordinates.
 */
typedef GenPolyline<double> DPolyline;

//@}


// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


} // namespace qgar 


#endif /* ___QGAR_GENPOLYLINE_H_INCLUDED__ */
