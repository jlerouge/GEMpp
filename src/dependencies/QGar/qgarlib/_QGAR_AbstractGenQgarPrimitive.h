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


#ifndef ___QGAR_ABSTRACTGENQGARPRIMITIVE_H_INCLUDED__
#define ___QGAR_ABSTRACTGENQGARPRIMITIVE_H_INCLUDED__


/**
 * @file     _QGAR_AbstractGenQgarPrimitive.h
 * @brief    Header file of class qgar::AbstractGenQgarPrimitive.
 *
 * @warning <b>Not to be used as include file!</b>
 * <br>When working with primitives, use header file primitives.h.
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date    December 14, 2004  15:15
 * @since   Qgar 2.2
 */


// For RCS/CVS use: Do not delete
/* $Id: _QGAR_AbstractGenQgarPrimitive.h,v 1.4 2005/11/23 17:08:31 masini Exp $ */



namespace qgar
{


/**
 * @ingroup DS_PRIM_QGAR
 *
 * @class AbstractGenQgarPrimitive _QGAR_AbstractGenQgarPrimitive.h "qgarlib/primitives.h"
 *
 * @brief Graphical primitives, typically resulting from vectorization,
 * with coordinates of type <b>T</b>.
 * 
 * Such a primitive is provided with:
 * <ul>
 * <li>Attributes: color, thickness, and outline.</li>
 * <li>A geometrical primitive as implementation, to be defined
 *     in derived classes: Functions giving access to this implementation,
 *     qgar::accessGeomStructure and qgar::geomStructure, are pure virtual.</li>
 * <li>A so-called source point (head) and
 *     a so-called target point (tail), that are the source and target
 *     points of the geometrical primitive.</li>
 * </ul>
 *
 * <b>Predefined types:</b>
 * - qgar::QgarPrimitive  (primitive with <b>int</b> coordinates)
 * - qgar::IQgarPrimitive (primitive with <b>int</b> coordinates)
 * - qgar::FQgarPrimitive (primitive with <b>float</b> coordinates)
 * - qgar::DQgarPrimitive (primitive with <b>double</b> coordinates)
 *
 * @warning
 * <ul>
 * <li>
 * This is an abstract class: It cannot be instantiated.
 * Pure virtual functions are
 * qgar::AbstractGenQgarPrimitive::accessGeomStructure,
 * qgar::AbstractGenQgarPrimitive::getGeomStructure,
 * qgar::AbstractGenQgarPrimitive::clone.
 * </li>
 * <li>
 * When the coordinates of its source and/or target are modified using
 * functions in section <b>Set source and/or target with update</b>, the
 * complete data structure of a primitive is supposed to be subsequently
 * updated.
 * See class qgar::AbstractGenPrimitive.
 * </li>
 * </ul>
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date     June 20, 2003  15:15
 * @since    Qgar 2.1
 */
template <class T> class AbstractGenQgarPrimitive
{
// -------------------------------------------------------------------
// T Y P E   D E F I N I T I O N S
// -------------------------------------------------------------------
public:


  /** @name Types */
  //        =====
  //@{

  /**
   * @brief Type of a point of a primitive.
   */
  typedef T value_type;

  /**
   * @brief Reference to qgar::AbstractGenQgarPrimitive::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::AbstractGenQgarPrimitive::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::AbstractGenQgarPrimitive::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::AbstractGenQgarPrimitive::value_type.
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
   * @param aThickness  thickness (default <b>1</b>)
   * @param aColor      color (default qgar::QGE_COLOR_BLACK)
   * @param anOutline   outline (default qgar::QGE_OUTLINE_SOLID)
   */
  AbstractGenQgarPrimitive(int        aThickness = 1,
			   QGEcolor   aColor     = QGE_COLOR_BLACK,
			   QGEoutline anOutline  = QGE_OUTLINE_SOLID);

  /**
   * @brief Copy constructor.
   *
   * @param aQPrim  Qgar primitive to be copied
   */
  AbstractGenQgarPrimitive(const AbstractGenQgarPrimitive<T>& aQPrim);

  //@}


  /**@name Destructor */
  //       ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  virtual ~AbstractGenQgarPrimitive();

  //@}


  /**@name Copy */
  //       ====
  //@{
  /**
   * @brief Create a dynamically allocated deep copy of the
   * primitive.
   */
  virtual AbstractGenQgarPrimitive<value_type>* clone() const = 0;
  //@}
  

  /**@name Geometrical aspect */
  //       ==================
  //@{
  /**

   * @brief Get the structure implementing
   *   the geometrical aspect of the primitive.
   */
  virtual const AbstractGenPrimitive<value_type>&
  accessGeomStructure() const = 0;

  //@}


  /**@name Access to attributes */
  //       ====================
  //@{

  /**
   * @brief Get thickness.
   */
  inline int thickness() const;

  /**
   * @brief Get color.
   */
  inline QGEcolor color() const;

  /**
   * @brief Get outline.
   */
  inline QGEoutline outline() const;

  //@}


  /**@name Access to source and target */
  //       ===========================
  //@{

  /**
   * @brief Get source point.
   */
  inline const GenPoint<value_type>& accessSource() const;

  /**
   * @brief Get a copy of the source point.
   */
  inline GenPoint<value_type> source() const;

  /**
   * @brief Get target point.
   */
  inline const GenPoint<value_type>& accessTarget() const;

  /**
   * @brief Get a copy of the target point.
   */
  inline GenPoint<value_type> target() const;

  //@}


  /**@name Access to separate coordinates */
  //       ==============================
  //@{

  /**
   * @brief Get X coordinate of the source point.
   */
  inline value_type xSource() const;

  /**
   * @brief Get X coordinate of the target point.
   */
  inline value_type xTarget() const;

  /**
   * @brief Get Y coordinate of the source point.
   */
  inline value_type ySource() const;

  /**
   * @brief Get Y coordinate of the target point.
   */
  inline value_type yTarget() const;

  //@}


  /** @name Access to geometrical characteristics */
  //        =====================================
  //@{

  /**
   * @brief Difference between target and source X coordinates.
   */
  inline value_type dx() const;

  /**
   * @brief Difference between target and source Y coordinates.
   */
  inline value_type dy() const;

  //@}
 

  /**@name Set attributes */
  //       ==============
  //@{

  /**
   * @brief Set thickness.
   *
   * @param aThickness  a thickness
   */
  inline void setThickness(int aThickness);

  /**
   * @brief Set color.
   *
   * @param aColor  a color
   */
  inline void setColor(QGEcolor aColor);

  /**
   * @brief Set outline.
   *
   * @param anOutline  an outline
   */
  inline void setOutline(QGEoutline anOutline);

  //@}


  /**@name Set source and/or target without update */
  //       =======================================
  //@{

  /**
   * @brief Set source point.
   *
   * @param aX  new X coordinate of the source point
   * @param aY  new Y coordinate of the source point
   *
   * @warning <b>The data structure of the primitive
   * is not subsequently updated</b>.
   */
  inline void setSource(value_type aX, value_type aY);

  /**
   * @brief Set source point.
   *
   * @param aPt  a point
   *
   * @warning <b>The data structure of the primitive
   * is not subsequently updated</b>.
   */
  inline void setSource(const GenPoint<value_type>& aPt);

  /**
   * @brief Set target point.
   *
   * @param aX  new X coordinate of the target point
   * @param aY  new Y coordinate of the target point
   *
   * @warning <b>The data structure of the primitive
   * is not subsequently updated</b>.
   */
  inline void setTarget(value_type aX, value_type aY);

  /**
   * @brief Set target point.
   *
   * @param aPt  a point
   *
   * @warning <b>The data structure of the primitive
   * is not subsequently updated</b>.
   */
  inline void setTarget(const GenPoint<value_type>& aPt);

  /**
   * @brief Set both source and target points.
   *
   * @param aXSource  new X coordinate of the source point
   * @param aYSource  new Y coordinate of the source point
   * @param aXTarget  new X coordinate of the target point
   * @param aYTarget  new Y coordinate of the target point
   *
   * @warning <b>The data structure of the primitive
   * is not subsequently updated</b>.
   */
  inline void setSourceTarget(value_type aXSource,
			      value_type aYSource,
			      value_type aXTarget,
			      value_type aYTarget);

  /**
   * @brief Set both source and target points.
   *
   * @param aSource  source point
   * @param aTarget  target point
   *
   * @warning <b>The data structure of the primitive
   * is not subsequently updated</b>.
   */
  inline void setSourceTarget(const GenPoint<value_type>& aSource,
			      const GenPoint<value_type>& aTarget);

  //@}


  /**@name Set source and/or target with update */
  //       ====================================
  //@{

  /**
   * @brief Set source point.
   *
   * @param aX  new X coordinate of the source point
   * @param aY  new Y coordinate of the source point
   *
   * @warning <b>Function qgar::AbstractGenPrimitive::updateSource
   *   is called after the modification of the source point.</b>
   */
  inline void fixSource(value_type aX, value_type aY);

  /**
   * @brief Set source point.
   *
   * @param aPt  a point
   *
   * @warning <b>Function qgar::AbstractGenPrimitive::updateSource
   *   is called after the modification of the source point.</b>
   */
  inline void fixSource(const GenPoint<value_type>& aPt);

  /**
   * @brief Set target point.
   *
   * @param aX  new X coordinate of the target point
   * @param aY  new Y coordinate of the target point
   *
   * @warning <b>Function qgar::AbstractGenPrimitive::updateTarget
   *   is called after the modification of the target point.</b>
   */
  inline void fixTarget(value_type aX, value_type aY);

  /**
   * @brief Set target point.
   *
   * @param aPt  a point
   *
   * @warning <b>Function qgar::AbstractGenPrimitive::updateTarget
   *   is called after the modification of the target point.</b>
   */
  inline void fixTarget(const GenPoint<value_type>& aPt);

  /**
   * @brief Set both source and target points.
   *
   * @param aXSource  new X coordinate of the source point
   * @param aYSource  new Y coordinate of the source point
   * @param aXTarget  new X coordinate of the target point
   * @param aYTarget  new Y coordinate of the target point
   *
   * @warning <b>Function qgar::AbstractGenPrimitive::updateTarget
   *   is called after the modification of the source target.</b>
   */
  inline void fixSourceTarget(value_type aXSource,
			      value_type aYSource,
			      value_type aXTarget,
			      value_type aYTarget);

  /**
   * @brief Set both source and target points.
   *
   * @param aSource  source point
   * @param aTarget  target point
   *
   * @warning <b>Function qgar::AbstractGenPrimitive::updateTarget
   *   is called after the modification of the source target.</b>
   */
  inline void fixSourceTarget(const GenPoint<value_type>& aSource,
			      const GenPoint<value_type>& aTarget);

  //@}


  /**@name Set separate (source and target) coordinates without update */
  //       ===========================================================
  //@{

  /**
   * @brief Set X coordinate of the source point.
   *
   * @param aX  new X coordinate of the source point
   *
   * @warning <b>The data structure of the primitive
   * is not subsequently updated</b>.
   */
  inline void setXSource(value_type aX);

  /**
   * @brief Set X coordinate of the target point.
   *
   * @param aX  new X coordinate of the target point
   *
   * @warning <b>The data structure of the primitive
   * is not subsequently updated</b>.
   */
  inline void setXTarget(value_type aX);

  /**
   * @brief Set Y coordinate of the source point.
   *
   * @param aY  new Y coordinate of the source point
   *
   * @warning <b>The data structure of the primitive
   * is not subsequently updated</b>.
   */
  inline void setYSource(value_type aY);

  /**
   * @brief Set Y coordinate of the target point.
   *
   * @param aY  new Y coordinate of the target point
   *
   * @warning <b>The data structure of the primitive
   * is not subsequently updated</b>.
   */
  inline void setYTarget(value_type aY);

  //@}


  /**@name Set separate (source and target) coordinates with update */
  //       ========================================================
  //@{

  /**
   * @brief Set X coordinate of the source point.
   *
   * @param aX  new X coordinate of the source point
   *
   * @warning <b>Function qgar::AbstractGenPrimitive::updateSource
   *   is called after the modification of the source point.</b>
   */
  void fixXSource(value_type aX);

  /**
   * @brief Set X coordinate of the target point.
   *
   * @param aX  new X coordinate of the target point
   *
   * @warning <b>Function qgar::AbstractGenPrimitive::updateTarget
   *   is called after the modification of the target point.</b>
   */
  void fixXTarget(value_type aX);

  /**
   * @brief Set Y coordinate of the source point.
   *
   * @param aY  new Y coordinate of the source point
   *
   * @warning <b>Function qgar::AbstractGenPrimitive::updateSource
   *   is called after the modification of the source point.</b>
   */
  void fixYSource(value_type aY);

  /**
   * @brief Set Y coordinate of the target point.
   *
   * @param aY  new Y coordinate of the target point
   *
   * @warning <b>Function qgar::AbstractGenPrimitive::updateTarget
   *   is called after the modification of the target point.</b>
   */
  void fixYTarget(value_type aY);

  //@}


  /** @name Operators */
  //        =========
  //@{
  /**
   * @brief Assignment.
   *
   * @param aQPrim  a Qgar primitive
   */
  AbstractGenQgarPrimitive<value_type>&
  operator=(const AbstractGenQgarPrimitive<value_type>& aQPrim);
  //@}


  /** @name Geometry: Translation */
  //        =====================
  //@{

  /**
   * @brief Translate along X and Y axis.
   *
   * @param aTransX  X translation factor
   * @param aTransY  Y translation factor
   */
  inline void translate(value_type aTransX, value_type aTransY);

  //@}


//   /** @name Geometry: Symmetry */
//   //        ==================
//   //@{

//   /**
//    * @brief Apply a central symmetry to the current primitive, using
//    *   the point of given coordinates as the symmetry center.
//    * @param aX  X coordinate of the symmetry center
//    * @param aY  Y coordinate of the symmetry center
//    * 
//    */
//   inline void symmetry(value_type aX, value_type aY);

//   /**
//    * @brief Apply a central symmetry to the current primitive, using
//    *   the given point as the symmetry center.
//    * @param aCenter  a point representing the center of the symmetry
//    */
//   inline void symmetry(const GenPoint<value_type>& aCenter);

//   /**
//    * @brief Apply a mirror symmetry to the current primitive, using
//    *   the line passing through the two given points for the symmetry.
//    * @param aPt1  a point
//    * @param aPt2  a point
//    *
//    * @warning This function applies to primitives
//    *   having coordinates of type <b>double</b> only.
//    */
//   inline void symmetry(const GenPoint<double>& aPt1,
// 		       const GenPoint<double>& aPt2);

//   /**
//    * @brief Apply a mirror symmetry to the current primitive, using
//    *   the line supporting the given segment for the symmetry.
//    * @param aSeg  a segment 
//    *
//    * @warning This function applies to primitives
//    *   having coordinates of type <b>double</b> only.
//    */
//   inline void symmetry(const GenSegment<double>& aSeg);

//   //@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:


  /** @name Attributes */
  //        ==========
  //@{

  /**
   * @brief Thickness of the outline.
   */
  int _thickness;

  /**
   * @brief Color of the outline.
   */
  QGEcolor _color;

  /**
   * @brief Type of outline.
   *
   * @see Enum type qgar::QGEoutline
   */
  QGEoutline _outline;

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
  virtual AbstractGenPrimitive<value_type>& getGeomStructure() = 0;

  //@}


// -------------------------------------------------------------------
}; // class AbstractGenQgarPrimitive




// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// P R E D E F I N E D    P R I M I T I V E    T Y P E S
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


/** @name Qgar abstract primitives type names */
//        ===================================
// @{

/**
 * @ingroup DS_PRIM
 *
 * @brief Qgar primitive with <b>integer</b> coordinates.
 *
 * @see qgar::IQgarPrimitive
 */
typedef AbstractGenQgarPrimitive<int> QgarPrimitive;

/**
 * @ingroup DS_PRIM
 *
 * @brief Qgar primitive with <b>integer</b> coordinates.
 *
 * @see qgar::QgarPrimitive
 */
typedef AbstractGenQgarPrimitive<int> IQgarPrimitive;

/**
 * @ingroup DS_PRIM
 *
 * @brief Qgar primitive with <b>float</b> coordinates.
 */
typedef AbstractGenQgarPrimitive<float> FQgarPrimitive;

/**
 * @ingroup DS_PRIM
 *
 * @brief Qgar primitive with <b>double</b> coordinates.
 */
typedef AbstractGenQgarPrimitive<double> DQgarPrimitive;

// @}


// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


} // namespace qgar


#endif /* ___QGAR_ABSTRACTGENQGARPRIMITIVE_H_INCLUDED__ */
