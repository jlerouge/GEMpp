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


#ifndef ___QGAR_GENPOLYGON_H_INCLUDED__
#define ___QGAR_GENPOLYGON_H_INCLUDED__


/**
 * @file _QGAR_GenPolygon.h
 *
 * @brief Header file of class qgar::GenPolygon.
 *
 * @warning <b>Not to be used as include file!</b>
 * <br>When working with primitives, use file primitives.h.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   December 14, 2004  16:16
 * @since  Qgar 2.2
 */


// For RCS/CVS use: Do not delete
/* $Id: _QGAR_GenPolygon.h,v 1.8 2007/02/14 17:34:05 masini Exp $ */



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
 * @class GenPolygon _QGAR_GenPolygon.h "qgarlib/primitives.h"
 *
 * @brief Geometrical polygon, with coordinates of type <b>T</b>.
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
 * A polygon is a series of points (implemented as a STL <b>deque</b>)
 * defining a closed geometrical shape: Each point represents
 * a vertex and two consecutive points represent a side.
 * </li>
 *
 * <li>
 * A polygon must always be provided with at least 3 vertices.
 * </li>
 *
 * <li>
 * A polygon is oriented: It is provided with a so-called
 * <i>source</i> vertex (first of the series) and a so-called
 * <i>target</i> vertex (last of the series).
 * </li>
 *
 * <li>
 * A polygon has no attribute. For <i>graphical</i> polygons,
 * provided with attributes (thickness, color, outline),
 * see class qgar::GenQgarPolygon.
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
 * <ul>
 * <li>
 * A polygon should not be provided with crossing sides. Otherwise,
 * the correctness of the effects and results of certain operations,
 * like qgar::GenPolygon::area, is not guaranteed. In particular:
@verbatim
  1 +    + 3                               1 +     + 5
    |\  /|                                   |\ 6 /|
    | \/ |      must be represented as       | \_/ |  
    | /\ |                                   | / \ |
    |/  \|                                   |/ 3 \| 
  2 +    + 4                               2 +     + 4
@endverbatim
 * </li>
 * <li>
 * <b>The coherence of the data structure of a polygon after
 * modifications of its source and/or its target and/or its
 * other vertices is the user's responsibility!</b>
 * </li>
 * </ul>
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   March 23, 2004  15:15
 * @since  Qgar 2.0
 */
template <class T> class GenPolygon

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
   * @brief Reference to qgar::GenPolygon::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::GenPolygon::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::GenPolygon::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::GenPolygon::value_type.
   */
  typedef const value_type* const_pointer;

  /**
   * @brief Type of the vertices container.
   */
  typedef std::deque< GenPoint<value_type> > vertices_type;

  /**
   * @brief Reference to qgar::GenPolygon::vertices_type.
   */
  typedef vertices_type& vertices_reference;

  /**
   * @brief Constant reference to qgar::GenPolygon::vertices_type.
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
   * @todo The created polygon does not conform to the definition
   *   of a polygon: The vertices <b>deque</b> is empty whereas
   *   it should contain at least 3 elements!
   */
  GenPolygon();

  /**
   * @brief Copy constructor.
   *
   * @param aPoly  a polygon
   */
  GenPolygon(const GenPolygon<value_type>& aPoly);

  /**
   * @brief Initialize from a Qgar polygon.
   *
   * @param aQPoly  a Qgar polygon
   *
   * @warning This kind of conversion must be explicitely
   *   specified by the client.
   */
  explicit GenPolygon(const GenQgarPolygon<value_type>& aQPoly);

   /**
   * @brief Initialize from a STL list of at least 3 points.
   *
   * @param aPtList  a STL list of at least 3 points
   *
   * @warning This kind of conversion must be explicitely
   *   specified by the client.
   *
   * @exception qgar::QgarErrorUser
   *   cannot create a polygon with less than 3 vertices
   */
  explicit GenPolygon(const std::list< GenPoint<value_type> >& aPtList)
   ;

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  virtual ~GenPolygon();

  //@}


  /**@name Copy */
  //       ====
  //@{

  /**
   * @brief Perform a deep copy.
   */  
  virtual GenPolygon<value_type>* clone() const;

  //@}


  /** @name Operators */
  //        =========
  //@{

  /**
   * @brief Assignment.
   *
   * @param aPoly  a polygon
   */
  inline GenPolygon<value_type>&
  operator=(const GenPolygon<value_type>& aPoly);

  //@}


  /** @name Area */
  //        ====
  //@{

  /**
   * @brief Get signed area.
   */
  double signedArea();

  /**
   * @brief Get area.
   */
  inline double area();

  //@}


  /** @name Access to vertices */
  //        ==================
  //@{

  /**
   * @brief Get number of vertices.
   */
  inline int size() const;

  /**
   * @brief Get vertices.
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
  GenPolygon<value_type>&
  appendSource(const GenPoint<value_type>& aPt);

  /**
   * @brief Insert a point as new target.
   *
   * @param aPt  a point
   */
  GenPolygon<value_type>&
  appendTarget(const GenPoint<value_type>& aPt);

  /**
   * @brief Appends a set of vertices to a Qgar polygon.
   *
   * The given vertices are inserted after the target vertex.
   * The order of the given vertices is preserved
   * in the resulting polyline.
   * The last vertex of the vector becomes the new target.
   *
   * @param aPtVect  STL vector of vertices to be appended
   * @return a reference on the polygon.
   */
  GenPolygon<value_type>&
  append(const std::vector<GenPoint<value_type> >& aPtVect);

  //@}


  /** @name Remove vertices */
  //        ===============
  //@{

  /**
   * @brief Remove a vertex from the polygon.
   *
   * @param aPt  a point
   *
   * @exception qgar::QgarErrorUser
   *   no removal in a polygon with 3 vertices
   */
  GenPolygon<value_type>& remove(const GenPoint<value_type>& aPt)
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
   * @brief Get a STL list of (geometrical) segments from the vertices.
   */
  std::list< GenSegment<value_type> > toSegList();

  /**
   * @brief Get a STL list of Qgar segments, provided with given
   *   attributes, from the vertices.
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
   * @brief Deserializes the current polygon from an input stream.
   *
   * A serialized polygon is represented by:
@verbatim
Polygon(<SOURCE>)(<TARGET>)(<VERTICES COUNT>)(<VERTICE 1>)..(<VERTICE n>)
@endverbatim
   *
   * @param anInStream  the input stream
   */
  virtual std::istream& read(std::istream& anInStream);

  /**
   * @brief Serializes the current polygon to an input stream.
   *
   * A serialized polygon is represented by:
@verbatim
Polygon(<SOURCE>)(<TARGET>)(<VERTICES COUNT>)(<VERTICE 1>)..(<VERTICE n>)
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


  /** @name Structure of a polygon */
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
   *   when the source has been changed.
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
}; // class GenPolygon




// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// P R E D E F I N E D    P O L Y L I N E    T Y P E S
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


/**@name Polygon type names */
//       ==================
//@{

/**
 * @ingroup DS_PRIM_GEOM
 *
 * @brief Polygon with <b>int</b> coordinates.
 *
 * @see qgar::IPolygon
 */
typedef GenPolygon<int> Polygon;

/**
 * @ingroup DS_PRIM_GEOM
 *
 * @brief Polygon with <b>int</b> coordinates.
 *
 * @see qgar::Polygon
 */
typedef GenPolygon<int> IPolygon;

/**
 * @ingroup DS_PRIM_GEOM
 *
 * @brief Polygon with <b>float</b> coordinates.
 */
typedef GenPolygon<float> FPolygon;

/**
 * @ingroup DS_PRIM_GEOM
 *
 * @brief Polygon with <b>double</b> coordinates.
 */
typedef GenPolygon<double> DPolygon;

//@}


// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


} // namespace qgar 


#endif /* ___QGAR_GENPOLYGON_H_INCLUDED__ */
