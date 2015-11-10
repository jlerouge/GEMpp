/*---------------------------------------------------------------------*
 | Library QgarLib, graphics analysis and recognition                  |
 | Copyright (C) 2004  Qgar Project, LORIA                             |
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
 | http://www.gnu.org/licenses/lgpl.html for the terms of the license. |
 | To receive a paper copy, write to the Free Software Foundation,     |
 | Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.       |
 |                                                                     |
 | Contact Project Qgar for any information:                           |
 |   LORIA - équipe Qgar                                               |
 |   B.P. 239, 54506 Vandoeuvre-lès-Nancy Cedex, France                |
 |   email: qgar-contact@loria.fr                                      |
 |   http://www.qgar.org/                                              |
 *---------------------------------------------------------------------*/


#ifndef __GENCONVEXHULL_H_INCLUDED__
#define __GENCONVEXHULL_H_INCLUDED__


/**
 * @file GenConvexHull.h
 *
 * @brief Header file of class qgar::GenConvexHull.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   March 24, 2004  11:24
 * @since  Qgar 2.1.1
 */



// For RCS/CVS use: Do not delete.
/* $Id: GenConvexHull.h,v 1.24 2006/07/04 13:37:41 masini Exp $ */



// STD
#include <iosfwd> // Avoid including classes when not necessary
#include <list>
#include <set>
// QGAR
#include "ISerializable.h"
#include "primitives.h"



namespace qgar
{


/**
 * @ingroup TOOL_HULL
 *
 * @class GenConvexHull GenConvexHull.h "qgarlib/GenConvexHull.h"
 *
 * @brief A convex hull represented by a series of points with
 *   coordinates of type <b>T</b>.
 *
 * The hull is constructed from a set of points using Graham's scan
 * <a href="Bibliography.html#Graham-1972">[Graham,&nbsp;1972]</a>.
 * This algorithm works in three steps:
 * <ol>
 * <li>
 * Find an extreme point, the so-called <i>pivot</i>, which is guaranteed
 * to be on the hull: Here, it is chosen as the point with the minimum Y
 * coordinate. In case of equality, the point with the minimum X coordinate is
 * selected.
 * </li>
 * <li>
 * Sort the points in order of increasing angles about the pivot.
 * The result is a star-shaped polygon, in which the pivot can <i>see</i>
 * the whole polygon.
 * </li>
 * <li>
 * Build the hull by marching around the star-shaped polygon, adding edges
 * at right turns, and backtracking at left turns.
 * </li>
 * </ol>
 *
 * Such a hull may be empty.
 * It is implemented by:
 * - a point representing the pivot (qgar::GenConvexHull::_pivot),
 * - a STL list of the vertices of the polygon constituting the hull
 *   (qgar::GenConvexHull::_vertices). The first vertex of the list is
 *   always the pivot,
 * - a STL multiset including STL pairs associating each vertex with its angle
 *   about the pivot (qgar::GenConvexHull::_hull). The pivot does not belong to
 *   the multiset. The pairs are sorted according to increasing angles.
 *
 * <b>The GenConvexHull class is not supposed to be derived: No function member
 * (destructor or whatever else) is virtual.</b>
 * Predefined instances of the class are
 * qgar::ConvexHull,
 * qgar::IConvexHull,
 * qgar::FConvexHull,
 * and qgar::DConvexHull.
 *
 * @warning <b>The hull is not guaranteed to be valid when constructed
 *   from an initial set of points including duplicates.</b>
 *
 * @todo Class to be completed: In particular, insertion and removal
 *   of points are not implemented.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   March 24, 2004  11:24
 * @since  Qgar 2.1.1
 */
template <class T> class GenConvexHull

  : public ISerializable

{
// -------------------------------------------------------------------
// T Y P E   D E F I N I T I O N S
// -------------------------------------------------------------------
public:

  /** @name Types */
  //        =====
  //@{

  /**
   * @brief Type of the points.
   */
  typedef T value_type;

  /**
   * @brief Reference to qgar::GenConvexHull::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::GenConvexHull::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::GenConvexHull::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::GenConvexHull::value_type.
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
 * Construct an empty hull.
 */
GenConvexHull();

/**
 * @brief Copy constructor.
 *
 * @param aCHull  a convex hull
 */
GenConvexHull(const GenConvexHull<value_type>& aCHull);

/**
 * @brief Construct from a STL list of points.
 *
 * The convex hull is constructed using <i>Graham's scan</i>.
 * <b>Duplicate points are eliminated.</b>
 *
 * @param aPtList  a STL list of points
 */
explicit GenConvexHull(const std::list< GenPoint<value_type> >& aPtList);

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Non-virtual destructor: The class is not supposed to be derived.
 */
~GenConvexHull();

//@}


/** @name Access to characteristics */
//        =========================
//@{

/**
 * @brief Is hull empty?
 */
inline bool empty() const;

/**
 * @brief Get number of vertices.
 */
inline int size() const;

//@}


/** @name Access to vertices */
//        ==================
//@{

/**
 * @brief Get vertices.
 */
const std::list< GenPoint<value_type> >& accessVertices() const;

/**
 * @brief Get a copy of the vertices.
 */
std::list< GenPoint<value_type> > vertices() const;

/**
 * @brief Get pivot.
 */
const GenPoint<value_type>& accessPivot() const;

/**
 * @brief Get a copy of the pivot.
 */
GenPoint<value_type> pivot() const;

//@}


/** @name Operators */
//        =========
//@{

/**
 * @brief Assignment operator.
 * @param aCHull  a hull
 */
GenConvexHull<value_type>& operator=(const GenConvexHull<value_type>& aCHull);

//@}


/** @name Serialization/deserialization */
//        =============================
//@{

/**
 * @brief Deserializes the current hull from an input stream.
 *
 * A serialized hull is represented by:
@verbatim
  ConvexHull(<VERTICES COUNT>)(<VERTICE 1>)...(<VERTICE n>)
@endverbatim
 *
 * @param anInStream  the input stream
 */
virtual std::istream& read(std::istream& anInStream);

/**
 * @brief Serializes the current hull to an input stream.
 *
 * A serialized hull is represented by:
@verbatim
  ConvexHull(<VERTICES COUNT>)(<VERTICE 1>)...(<VERTICE n>)
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

/** @name Type definitions */
//        ================
//@{

/**
 * @brief Pair associating a vertex with its angle about the pivot.
 */
typedef std::pair< double, GenPoint<value_type> > QGDpair;

//@}


/** @name Auxiliary structure */
//        ===================
//@{

/**
 * @brief To compare angles about the pivot when sorting points
 * to construct their hull.
 */
struct _sortPred
{
  /**
   * @brief Compares angles about the pivot when sorting points to
   * construct their hull.
   *
   * When angles are equal, pairs are sorted according to decreasing
   * Y coordinates of the corresponding points, and, when Y coordinates
   * are equal, according to increasing X coordinates:
   * <b>The pivot is thus guaranteed to be the leftmost point of minimum
   * Y coordinate.</b>
   *
   * @param aPair1 The lhs parameter of the comparison.
   * @param aPair2 The rhs parameter of the comparison.
   */
  bool operator()(const std::pair< double, GenPoint<T> >& aPair1,
		  const std::pair< double, GenPoint<T> >& aPair2)
  {
    return
             // increasing angles...
             ( (aPair1.first) < (aPair2.first) )
          ||
             // ...OR, if angles are equal...
             (    ( (aPair1.first) == (aPair2.first) )
               &&
		     // ...decreasing Y coordinates...
		  (    ( (aPair1.second.y()) > (aPair2.second.y()) )
                    ||
		            // ...OR, if y coordinates are equal...
                       (    ( (aPair1.second.y()) == (aPair2.second.y()) )
                         &&
			     // ...increasing X coordinates
                             ( (aPair1.second.x()) < (aPair2.second.x()) )
		       )
		  )
	     );
  }
};

//@}


/** @name The hull */
//        ========
//@{

/**
 * @brief The list of the vertices of the hull.
 *
 * The first point of the list is the pivot.
 */
std::list< GenPoint<value_type> > _vertices;

/**
 * @brief Sorted STL multiset of STL pairs associating a vertex (of the hull)
 * with the angle between the X axis and the vector joining the pivot
 * and the vertex.
 *
 * Pairs are sorted in order of increasing angles.
 */
std::multiset<QGDpair, _sortPred> _hull;

/**
 * @brief The pivot.
 *
 * It is the initial given point of minimum ordinate,
 * which is guaranteed to belong to the hull.
 */
GenPoint<value_type> _pivot;

//@}

// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

/** @name Auxiliary functions */
//        ===================
//@{

/**
 * @brief Perfom Graham's scan to construct the convex hull from 
 * a given list of points.
 *
 * @param aPtList  the initial list of points, from which to construct
 *                 the convex hull
 */
void PRIVATEgraham_sScan(const std::list< GenPoint<value_type> >& aPtList);

//@}

// -------------------------------------------------------------------

}; // class GenConvexHull


} // namespace qgar




// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// I M P L E M E N T A T I O N
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII

#include "GenConvexHull.tcc"

// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII




// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// P R E D E F I N E D    H U L L    T Y P E S
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


namespace qgar
{


/**
 * @name Predefined Convex Hulls Types
 * @ingroup TOOL_HULL
 */
//{@

/**
 * @brief Hull with integer coordinates.
 *
 * @see qgar::IConvexHull
 */
typedef GenConvexHull<int> ConvexHull;

/**
 * @brief Hull with integer coordinates.
 *
 * @see qgar::ConvexHull
 */
typedef GenConvexHull<int> IConvexHull;

/**
 * @brief Hull with <b>float</b> coordinates.
 */
typedef GenConvexHull<float> FConvexHull;

/**
 * @brief Hull with <b>double</b> coordinates.
 */
typedef GenConvexHull<double> DConvexHull;

//@}


} // namespace qgar


// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


#endif /* __GENCONVEXHULL_H_INCLUDED__ */

