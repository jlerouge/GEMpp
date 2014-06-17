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


#ifndef ___QGAR_GENQGARPOLYGON_H_INCLUDED__
#define ___QGAR_GENQGARPOLYGON_H_INCLUDED__


/**
 * @file _QGAR_GenQgarPolygon.h
 *
 * @brief Header file of class qgar::GenQgarPolygon.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   December 14, 2004  17:27
 * @since  Qgar 2.2
 */


// For RCS/CVS use: Do not delete
/* $Id: _QGAR_GenQgarPolygon.h,v 1.8 2007/02/14 17:34:06 masini Exp $ */



// STD
#include <deque>
#include <iosfwd>  // Avoid including classes when not necessary
#include <list>
#include <vector>
// QGAR
#include "ISerializable.h"
#include "QgarErrorUser.h"



namespace qgar
{


/**
 * @ingroup DS_PRIM_QGAR
 *
 * @class GenQgarPolygon _QGAR_GenQgarPolygon.h "qgarlib/primitives.h"
 *
 * @brief Graphical polygon, so-called <i>Qgar polygon</i>,
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
 * The origin of the coordinate system is at top left corner.
 * Angles are clockwise from the X axis.
 * </li>
 *
 * <li>
 * A Qgar polygon is a series of points (implemented as a STL <b>deque</b>)
 * defining a closed geometrical shape: Each point represents a vertex
 * and two consecutive points represent a side.
 * </li>
 *
 * </li>
 * <li>A Qgar polygon must always be provided with at least 3 vertices.
 * </li>
 *
 * <li>
 * A Qgar polygon is oriented: It is provided with a so-called
 * <i>source</i> vertex (first of the series) and a so-called
 * <i>target</i> vertex (last of the series).
 * </li>
 *
 * <li>
 * A Qgar polygon is provided with attributes: thickness, color,
 * and outline. When such features are useless, see class
 * qgar::GenPolygon (for geometrical Polygons).
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
 * <ul>
 * <li>
 * A Qgar polygon should not be provided with crossing sides.
 * Otherwise, the correctness of the effects and results of
 * certain operations, like qgar::GenQgarPolygon::area, is
 * not valid. In particular:
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
 * <b>The coherence of the data structure of a Qgar polygon
 * after modifications of its source and/or its target
 * and/or its other vertices is the user's responsibility!</b>
 * </li>
 * </ul>
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   March 23, 2004  22:45
 * @since  Qgar 2.1
 */
template <class T>
class GenQgarPolygon

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
   * @brief Type of the vertices coordinates.
   */
  typedef T value_type;

  /**
   * @brief Reference to qgar::GenQgarPolygon::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::GenQgarPolygon::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::GenQgarPolygon::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::GenQgarPolygon::value_type.
   */
  typedef const value_type* const_pointer;

  /**
   * @brief Type of the vertices container.
   */
  typedef std::deque< GenPoint<value_type> > vertices_type;

  /**
   * @brief Reference to qgar::GenQgarPolygon::vertices_type.
   */
  typedef vertices_type& vertices_reference;

  /**
   * @brief Constant reference to qgar::GenQgarPolygon::vertices_type.
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
   * @brief Default constructor: The vertices <b>deque</b> is empty.
   *
   * @param aThickness  thickness (default <b>1</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline   (default qgar::QGE_OUTLINE_DEFAULT) 
   *
   * @todo The vertices should at least be 3!
   */
  GenQgarPolygon(int        aThickness = 1,
		 QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		 QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  /**
   * @brief Copy constructor.
   *
   * @param aQPoly  a Qgar polygon
   */
  GenQgarPolygon(const GenQgarPolygon<T>& aQPoly);

  /**
   * @brief Initialize from a geometrical polygon.
   *
   * @param aPoly       a (geometrical) polygon
   * @param aThickness  thickness (default <b>1</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline   (default qgar::QGE_OUTLINE_DEFAULT) 
   */
  GenQgarPolygon(const GenPolygon<value_type>& aPoly,
		 int        aThickness = 1,
		 QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		 QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  /**
   * @brief Initialize from a STL list of at least 3 points.
   *
   * @param aPtList     a list of at least two points
   * @param aThickness  thickness (default <b>1</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline   (default qgar::QGE_OUTLINE_DEFAULT) 
   *
   * @exception qgar::QgarErrorUser
   *   cannot create a polygon with less than 3 vertices
   */
  GenQgarPolygon(const std::list< GenPoint<value_type> >& aPtList,
		 int        aThickness = 1,
		 QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		 QGEoutline anOutline  = QGE_OUTLINE_DEFAULT)
   ;

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  virtual ~GenQgarPolygon();

  //@}


  /**@name Copy */
  //       ====
  //@{

  /**
   * @brief Perform a deep copy.
   */
  virtual GenQgarPolygon<value_type>* clone() const;

  //@}


  /** @name Operators */
  //        =========
  //@{

  /**
   * @brief Assignment.
   *
   * @param aQPoly  a Qgar polygon
   */
  GenQgarPolygon<value_type>&
  operator=(const GenQgarPolygon<value_type>& aQPoly);

  //@}


  /**@name Access to the geometrical structure */
  //       ===================================
  //@{

  /**
   * @brief Get the structure implementing
   * the geometrical aspect of a Qgar polygon.
   */
  inline const GenPolygon<value_type>& accessGeomStructure() const;

  //@}


  /** @name Area */
  //        ====
  //@{

  /**
   * @brief Get signed area.
   */
  inline double signedArea();

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
  GenQgarPolygon<value_type>&
  appendSource(const GenPoint<value_type>& aPt);

  /**
   * @brief Insert a point as new target.
   *
   * @param aPt  a point
   */
  GenQgarPolygon<value_type>&
  appendTarget(const GenPoint<value_type>& aPt);

  /**
   * @brief Appends a set of vertices to a Qgar polygon.
   *
   * The given vertices are inserted after the target vertex.
   * The order of the given vertices is preserved
   * in the resulting polygon.
   * The last vertex of the vector becomes the new target.
   *
   * @param aPtVect  STL vector of vertices to be appended
   *
   * @return a reference on the polygon.
   */
  GenQgarPolygon<value_type>&
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
  GenQgarPolygon<value_type>&
  remove(const GenPoint<value_type>& aPt)
   ;

  //@}


  /** @name Conversion of the vertices */
  //        ==========================
  //@{

  /**
   * @brief Get a vector of points from the vertices.
   */
  inline std::vector< GenPoint<value_type> > toPointVector();

  /**
   * @brief Get a STL list of (geometrical) segments from the vertices.
   */
  inline std::list< GenSegment<value_type> > toSegList();

  /**
   * @brief Get a STL list of Qgar segments,
   *
   * The resulting segments are provided with the same thickness,
   * color and outline as the current polygon.
   */
  inline std::list< GenQgarSegment<value_type> > toQgarSegList();

  //@}


  /**@name Geometry: Translation */
  //       =====================
  //@{

  /**
   * @brief Translate current segment along X and Y axis.
   * @param aX  X translation factor
   * @param aY  Y translation factor
   */
  virtual void translate(value_type aX, value_type aY);

  //@}


  /** @name Serialization/deserialization */
  //        =============================
  //@{

  /**
   * @brief Deserializes the current polygon from an input stream.
   *
   * A serialized Qgar polygon is represented as:
@verbatim
QgarPolygon(<GEOMETRICAL STRUCTURE>)(<THICKNESS>)(<COLOR>)(<OUTLINE>)
@endverbatim
   *
   * @param anInStream  the input stream
   */
  virtual std::istream& read(std::istream& anInStream);

  /**
   * @brief Serializes the current polygon to an input stream.
   *
   * A serialized Qgar polygon is represented as:
@verbatim
QgarPolygon(<GEOMETRICAL STRUCTURE>)(<THICKNESS>)(<COLOR>)(<OUTLINE>)
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


  /** @name Geometrical structure of a Qgar polygon */
  //        ========================================
  //@{

  /**
   * @brief Geometrical structure.
   */
  GenPolygon<value_type> _geomStructure;

  //@}


  /**@name Non-protected access to the geometrical aspect */
  //       ==============================================
  //@{

  /**
   * @brief Return the geometrical aspect, which may then be modified
   * using appropriate function members.
   */
  inline AbstractGenPrimitive<value_type>& getGeomStructure();

  //@}


// -------------------------------------------------------------------
}; // class GenQgarPolygon




// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// P R E D E F I N E D    Q G A R    P O L Y L I N E    T Y P E S
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


/** @name Qgar Polygon type names */
//        =======================
//@{

/**
 * @ingroup DS_PRIM_QGAR
 *
 * @brief Qgar polygon with <b>integer</b> coordinates.
 *
 * @see qgar::IQgarPolygon
 */
typedef GenQgarPolygon<int> QgarPolygon;

/**
 * @ingroup DS_PRIM_QGAR
 *
 * @brief Qgar polygon with <b>integer</b> coordinates.
 *
 * @see qgar::QgarPolygon
 */
typedef GenQgarPolygon<int> IQgarPolygon;

/**
 * @ingroup DS_PRIM_QGAR
 *
 * @brief Qgar polygon with <b>float</b> coordinates.
 */
typedef GenQgarPolygon<float> FQgarPolygon;

/**
 * @ingroup DS_PRIM_QGAR
 *
 * @brief Qgar polygon with <b>double</b> coordinates.
 */
typedef GenQgarPolygon<double> DQgarPolygon;

//@}


// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


} // namespace qgar 


#endif /* ___QGAR_GENQGARPOLYGON_H_INCLUDED__ */
