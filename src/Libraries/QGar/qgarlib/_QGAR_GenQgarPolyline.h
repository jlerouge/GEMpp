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


#ifndef ___QGAR_GENQGARPOLYLINE_H_INCLUDED__
#define ___QGAR_GENQGARPOLYLINE_H_INCLUDED__


/**
 * @file   _QGAR_GenQgarPolyline.h
 * @brief  Header file of class qgar::GenQgarPolyline.
 *
 * @warning <b>Not to be used as include file!</b>
 * <br>When working with primitives, use file primitives.h.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   December 14, 2004  18:18
 * @since  Qgar 2.2
 */


// For RCS/CVS use: Do not delete
/* $Id: _QGAR_GenQgarPolyline.h,v 1.6 2006/03/30 12:49:41 masini Exp $ */



// STD
#include <deque>
#include <iosfwd>  // Avoid including classes when not necessary
#include <list>
#include <vector>
// QGAR
#include "ISerializable.h"



namespace qgar
{


/**
 * @class GenQgarPolyline _QGAR_GenQgarPolyline.h "qgarlib/primitives.h"
 * @ingroup DS_PRIM_QGAR
 * @brief Graphical polyline, so-called <i>Qgar polyline</i>,
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
 * A Qgar polyline is a series of points, implemented as a STL
 * <b>deque</b>): Each point represents a vertex and two
 * consecutive points represent a segment.
 * </li>
 *
 * <li>
 * A Qgar polyline must always be provided with at least 2 vertices.
 * </li>
 *
 * <li>
 * A Qgar polyline is oriented: It is provided with a so-called
 * <i>source</i> vertex (first of the series)
 * and a so-called <i>target</i> vertex (last of the series).
 * </li>
 *
 * <li>
 * A Qgar polyline does not define any closed geometrical shape,
 * like a Qgar polygon. In particular, the source and target vertices
 * do not define a segment.
 * </li>
 *
 * <li>
 * A Qgar polyline is provided with attributes: thickness, color,
 * and outline. When such features are useless, see class
 * qgar::GenPolyline (for geometrical polylines).
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
 *   <b>The coherence of the data structure of a polyline after
 *   modifications of its source and/or its target and/or its
 *   other vertices is the user's responsibility!</b>
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   June 24, 2003  15:35
 * @since  Qgar 2.1
 */
template <class T>
class GenQgarPolyline

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
   * @brief Reference to qgar::GenQgarPolyline::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::GenQgarPolyline::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::GenQgarPolyline::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::GenQgarPolyline::value_type.
   */
  typedef const value_type* const_pointer;

  /**
   * @brief Type of the vertices container.
   */
  typedef std::deque< GenPoint<value_type> > vertices_type;

  /**
   * @brief Reference to qgar::GenQgarPolyline::vertices_type.
   */
  typedef vertices_type& vertices_reference;

  /**
   * @brief Constant reference to qgar::GenQgarPolyline::vertices_type.
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
   * @brief Default constructor: The series of vertices is empty.
   *
   * @param aThickness  thickness (default <b>1</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline   (default qgar::QGE_OUTLINE_DEFAULT) 
   *
   * @todo The created polyline does not conform to the definition
   *   of a polyline: The vertices deque is empty whereas it should
   *   contain at least 2 elements!
   */
  GenQgarPolyline(int        aThickness = 1,
		  QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		  QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  /**
   * @brief Copy constructor.
   *
   * @param aQPoly  a Qgar polyline
   */
  GenQgarPolyline(const GenQgarPolyline<value_type>& aQPoly);

  /**
   * @brief Initialize from a geometrical polyline.
   *
   * @param aPoly       a (geometrical) polyline
   * @param aThickness  thickness (default <b>1</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline   (default qgar::QGE_OUTLINE_DEFAULT) 
   *
   * @warning This kind of conversion must be explicitely
   *   specified by the client.
   */
  explicit GenQgarPolyline(const GenPolyline<value_type>& aPoly,
			   int        aThickness = 1,
			   QGEcolor   aColor     = QGE_COLOR_DEFAULT,
			   QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  /**
   * @brief Initialize from a Qgar segment.
   *
   * The created polyline has the same thickness, color and outline
   * as the given Qgar segment.
   *
   * @param aQSeg  a Qgar segment
   *
   * @warning This kind of conversion must be explicitely
   *   specified by the client.
   */
  explicit GenQgarPolyline(const GenQgarSegment<value_type>& aQSeg);

  /**
   * @brief Initialize from a (geometrical) segment.
   *
   * @param aSeg        a (geometrical) segment
   * @param aThickness  thickness (default <b>1</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline   (default qgar::QGE_OUTLINE_DEFAULT) 
   *
   * @warning This kind of conversion must be explicitely
   *   specified by the client.
   */
  explicit GenQgarPolyline(const GenSegment<value_type>& aSeg,
			   int        aThickness = 1,
			   QGEcolor   aColor     = QGE_COLOR_DEFAULT,
			   QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  /**
   * @brief Initialize from 2 vertices: source and target.
   *
   * @param aSource     source vertex 
   * @param aTarget     target vertex
   * @param aThickness  thickness (default <b>1</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline   (default qgar::QGE_OUTLINE_DEFAULT) 
   */
  GenQgarPolyline(const GenPoint<value_type>& aSource,
		  const GenPoint<value_type>& aTarget,
		  int        aThickness = 1,
		  QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		  QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  /**
   * @brief Initialize from a <b>list</b> of at least two points.
   *
   * @param aPtList     a list of at least two points
   * @param aThickness  thickness (default <b>1</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline   (default qgar::QGE_OUTLINE_DEFAULT) 
   *
   * @warning This kind of conversion must be explicitely
   *   specified by the client.
   *
   * @exception qgar::QgarErrorUser
   *   cannot create a polyline with less than 2 vertices
   */
  explicit GenQgarPolyline(const std::list< GenPoint<value_type> >& aPtList,
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
  virtual ~GenQgarPolyline();

  //@}


  /**@name Copy */
  //       ====
  //@{

  virtual GenQgarPolyline<value_type>* clone() const;

  //@}


  /** @name Operators */
  //        =========
  //@{

  /**
   * @brief Assignment.
   *
   * @param aQPoly  a Qgar polyline
   */
  GenQgarPolyline<value_type>&
  operator=(const GenQgarPolyline<value_type>& aQPoly);

  //@}


  /**@name Access to the geometrical structure */
  //       ===================================
  //@{

  /**
   * @brief Get the structure implementing
   *        the geometrical aspect of a Qgar polyline.
   */
  inline const GenPolyline<value_type>& accessGeomStructure() const;

  //@}


  /** @name Access to vertices */
  //        ==================
  //@{

  /**
   * @brief Get number of vertices.
   */
  inline int size() const;

  /**
   * @brief Get vertices in a <b>deque</b>.
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
   * @brief Get a copy of the vertices in a <b>deque</b>.
   */
  inline vertices_type vertices() const;

  //@}


  /** @name Insert vertices */
  //        ===============
  //@{

  /**
   * @brief Add a point as new source.
   *
   * @param aPt  a point
   */
  GenQgarPolyline<value_type>&
  appendSource(const GenPoint<value_type>& aPt);

  /**
   * @brief Append a point as new target.
   *
   * @param aPt  a point
   */
  GenQgarPolyline<value_type>&
  appendTarget(const GenPoint<value_type>& aPt);

  /**
   * @brief Appends a Qgar polyline.
   *
   * @param aQPoly the Qgar polyline to be appended
   * @return a reference on the current polyline
   *
   * @warning The thickness, color and outline of the current
   *   polyline always remain unchanged.
   */
  GenQgarPolyline<value_type>&
  append(const GenQgarPolyline<value_type>& aQPoly);

  /**
   * @brief Appends a polyline.
   *
   * @param aPoly the polyline to be appended
   * @return a reference on the current polyline
   */
  GenQgarPolyline<value_type>&
  append(const GenPolyline<value_type>& aPoly);

  /**
   * @brief Appends a set of point to a Qgar polyline.
   *
   * The last point of the vector becomes the new polyline target.
   *
   * @param aPtVect the vector of points to be appended
   * @return a reference on the current polyline
   */
  GenQgarPolyline<value_type>&
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
   * @warning The resulting polyline should be provided
   *          with at least two vertices.
   *
   * @exception qgar::QgarErrorUser
   *   no removal in a polyline with 2 vertices
   */
  GenQgarPolyline<value_type>&
  remove(const GenPoint<value_type>& aPt);

  //@}


  /** @name Conversion of the vertices */
  //        ==========================
  //@{

  /**
   * @brief Get a <b>vector</b> of points from the series of vertices.
   */
  inline std::vector< GenPoint<value_type> > toPointVector();

  /**
   * @brief Get a <b>list</b> of (geometrical) segments from the vertices.
   */
  inline std::list< GenSegment<value_type> > toSegList();

  /**
   * @brief Get a <b>list</b> of Qgar segments from the vertices.
   *
   * The resulting segments are provided with the same thickness,
   * color and outline as the current polyline.
   */
  inline std::list< GenQgarSegment<value_type> > toQgarSegList();

  //@}


  /**@name Geometry: Translation */
  //       =====================
  //@{

  /**
   * @brief Translate current polyline along X and Y axis.
   * @param aX  X translation factor
   * @param aY  Y translation factor
   */
  virtual void translate(value_type aX, value_type aY);

  //@}


  /** @name Serialization/Deserialization */
  //        =============================
  //@{

  /**
   * @brief Deserializes the current polyline from an input stream.
   *
   * A serialized Qgar polyline is represented as:
@verbatim
QgarPolyline(<GEOMETRICAL STRUCTURE>)(<THICKNESS>)(<COLOR>)(<OUTLINE>)
@endverbatim
   *
   * @param anInStream The input stream
   */
  inline virtual std::istream& read(std::istream& anInStream);

  /**
   * @brief Serializes the current polyline to an input stream.
   *
   * A serialized Qgar polyline is represented as:
@verbatim
QgarPolyline(<GEOMETRICAL STRUCTURE>)(<THICKNESS>)(<COLOR>)(<OUTLINE>)
@endverbatim
   *
   * @param anOutStream The output stream
   */
  inline virtual std::ostream& write(std::ostream& anOutStream) const;

  //@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:


  /** @name Geometrical structure of a Qgar polyline */
  //        ========================================
  //@{

  /**
   * @brief Geometrical structure.
   */
  GenPolyline<value_type> _geomStructure;

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
}; // class Polyline




// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// P R E D E F I N E D    Q G A R    P O L Y L I N E    T Y P E S
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


/** @name Qgar polyline type names */
//        ========================
//@{

/**
 * @ingroup DS_PRIM_QGAR
 *
 * @brief Qgar polyline with <b>integer</b> coordinates.
 *
 * @see qgar::IQgarPolyline
 */
typedef GenQgarPolyline<int> QgarPolyline;

/**
 * @ingroup DS_PRIM_QGAR
 *
 * @brief Qgar polyline with <b>integer</b> coordinates.
 *
 * @see qgar::QgarPolyline
 */
typedef GenQgarPolyline<int> IQgarPolyline;

/**
 * @ingroup DS_PRIM_QGAR
 *
 * @brief Qgar polyline with <b>float</b> coordinates.
 */
typedef GenQgarPolyline<float> FQgarPolyline;

/**
 * @ingroup DS_PRIM_QGAR
 *
 * @brief Qgar polyline with <b>double</b> coordinates.
 */
typedef GenQgarPolyline<double> DQgarPolyline;

//@}


// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


} // namespace qgar 


#endif /* ___QGAR_GENQGARPOLYLINE_H_INCLUDED__ */
