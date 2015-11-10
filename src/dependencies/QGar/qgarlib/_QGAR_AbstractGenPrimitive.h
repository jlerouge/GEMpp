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


#ifndef ___QGAR_ABSTRACTGENPRIMITIVE_H_INCLUDED__
#define ___QGAR_ABSTRACTGENPRIMITIVE_H_INCLUDED__


/**
 * @file    _QGAR_AbstractGenPrimitive.h
 * @brief   Header file of class qgar::AbstractGenPrimitive.
 *
 * @warning <b>Not to be used as include file!</b>
 * <br>When working with primitives, use file primitives.h.
 *
 * @author  <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date    December 14, 2004  14:14
 * @since   Qgar 2.2
 */


// For RCS/CVS use: Do not delete
/* $Id: _QGAR_AbstractGenPrimitive.h,v 1.4 2005/11/23 17:08:31 masini Exp $ */



namespace qgar
{


/**
 * @ingroup DS_PRIM_GEOM
 *
 * @class AbstractGenPrimitive _QGAR_AbstractGenPrimitive.h "qgarlib/primitives.h"
 *
 * @brief Geometrical primitives with coordinates of type <b>T</b>.
 * 
 * Such a primitive is provided with a so-called source point (head)
 * and a so-called target point (tail), arbitrarily defined.
 *
 * When the coordinates of its source and/or target are modified using
 * functions in section <b>Set source and/or target with update</b>, the
 * complete data structure of a primitive is supposed to be subsequently
 * updated to remain coherent.
 *
 * <b>Predefined types:</b>
 * <br> &nbsp; &nbsp; &nbsp; &nbsp; See submodule
 * <a href="group__DS__PRIM.html"><b>Primitives & abstract primitives</b></a>
 * for details.
 *
 * @warning
 * This is an abstract class: It cannot be instantiated.
 *
 * Pure virtual functions:
 * <ul>
 * <li>
 * qgar::AbstractGenPrimitive::updateSource,
 * qgar::AbstractGenPrimitive::updateTarget,
 * qgar::AbstractGenPrimitive::updateSourceTarget.
 * These functions are designed to update the data structure
 * of a primitive when the coordinates of the source and/or target
 * of the primitive are modified using specified functions.
 * </li>
 * <li>
 * qgar::AbstractGenPrimitive::clone,
 * which performs a deep copy (of the current primitive).
 * </li>
 * <li>
 * qgar::AbstractGenPrimitive::translate,
 * which performs the same-named geometrical transformation.
 * </li>
 * </ul>
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   June 20, 2003  18:08
 * @since  Qgar 2.1.1
 */

template <class T>
class AbstractGenPrimitive
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
   * @brief Reference to qgar::AbstractGenPrimitive::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::AbstractGenPrimitive::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::AbstractGenPrimitive::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::AbstractGenPrimitive::value_type.
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
   * Source and target at <b>(0, 0)</b>.
   */
  AbstractGenPrimitive<value_type>();

  /**
   * @brief Copy constructor.
   * @param aPrim  primitive to be copied
   */
  AbstractGenPrimitive<value_type>(const AbstractGenPrimitive<value_type>& aPrim);

  /**
   * @brief Initialize from source and target.
   *
   * @param aSource  source point
   * @param aTarget  target point
   */
  AbstractGenPrimitive<value_type>(const GenPoint<value_type> aSource,
				   const GenPoint<value_type> aTarget);

  /**
   * @brief Initialize from coordinates
   *
   * @param aXSource  X coordinate of source point
   * @param aYSource  Y coordinate of source point
   * @param aXTarget  X coordinate of target point
   * @param aYTarget  Y coordinate of target point
   */
  AbstractGenPrimitive<value_type>(value_type aXSource,
				   value_type aYSource,
				   value_type aXTarget,
				   value_type aYTarget);

  //@}


  /**@name Destructor */
  //       ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  virtual ~AbstractGenPrimitive();

  //@}


  /**@name Copy */
  //       ====
  //@{

  /**
   * @brief Perform a deep copy.
   */  
  virtual AbstractGenPrimitive<value_type>* clone() const = 0;

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
  void setSourceTarget(value_type aXSource,
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
  void setSourceTarget(const GenPoint<value_type>& aSource,
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
   * is called after the modification of the source point.</b>
   */
  void fixSource(value_type aX, value_type aY);

  /**
   * @brief Set source point.
   *
   * @param aPt  a point
   *
   * @warning <b>Function qgar::AbstractGenPrimitive::updateSource
   * is called after the modification of the source point.</b>
   */
  void fixSource(const GenPoint<value_type>& aPt);

  /**
   * @brief Set target point.
   *
   * @param aX  new X coordinate of the target point
   * @param aY  new Y coordinate of the target point
   *
   * @warning <b>Function qgar::AbstractGenPrimitive::updateTarget
   * is called after the modification of the target point.</b>
   */
  void fixTarget(value_type aX, value_type aY);

  /**
   * @brief Set target point.
   *
   * @param aPt  a point
   *
   * @warning <b>Function qgar::AbstractGenPrimitive::updateTarget
   * is called after the modification of the source target.</b>
   */
  void fixTarget(const GenPoint<value_type>& aPt);

  /**
   * @brief Set both source and target points.
   *
   * @param aXSource  new X coordinate of the source point
   * @param aYSource  new Y coordinate of the source point
   * @param aXTarget  new X coordinate of the target point
   * @param aYTarget  new Y coordinate of the target point
   *
   * @warning <b>Function qgar::AbstractGenPrimitive::updateSourceTarget
   *   is called after the modification of the source and target points.</b>
   */
  void fixSourceTarget(value_type aXSource,
		       value_type aYSource,
		       value_type aXTarget,
		       value_type aYTarget);

  /**
   * @brief Set both source and target points.
   *
   * @param aSource  source point
   * @param aTarget  target point
   *
   * @warning <b>Function qgar::AbstractGenPrimitive::updateSourceTarget
   *   is called after the modification of the source and target points.</b>
   */
  void fixSourceTarget(const GenPoint<value_type>& aSource,
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
   * @param aPrim  a geometrical primitive
   */
  AbstractGenPrimitive<value_type>&
  operator=(const AbstractGenPrimitive<value_type>& aPrim);
  //@}


  /** @name Geometry: Translation */
  //        =====================
  //@{

  /**
   * @brief Translate current primitive along X and Y axis.
   *
   * @param aX  X translation factor
   * @param aY  Y translation factor
   *
   * @warning This is a pure virtual function.
   */
  virtual void translate(value_type aX, value_type aY) = 0;

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
//    * @warning <b>This function applies to primitives
//    *   having coordinates of type <i>double</i> only.</b>
//    */
//   inline void symmetry(const GenPoint<double>& aPt1,
// 		       const GenPoint<double>& aPt2);

//   /**
//    * @brief Apply a mirror symmetry to the current primitive, using
//    *   the line supporting the given segment for the symmetry.
//    * @param aSeg  a segment 
//    *
//    * @warning <b>This function applies to primitives
//    *   having coordinates of type <i>double</i> only.</b>
//    */
//   inline void symmetry(const GenSegment<double>& aSeg);

//   //@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:


  /** @name Source and target */
  //        =================
  //@{

  /**
   * @brief Source point.
   */
  GenPoint<value_type> _source;

  /**
   * @brief Target point.
   */
  GenPoint<value_type> _target;

  //@}


  /** @name Updates subsequent to source and target modifications */
  //        =====================================================
  //@{

  /**
   * @brief Update the geometrical structure
   *   when the source point is modified.
   *
   * @warning This is a pure virtual function.
   */
  virtual void updateSource() = 0;

  /**
   * @brief Update the geometrical structure
   *   when the target point is modified.
   *
   * @warning This is a pure virtual function.
   */
  virtual void updateTarget() = 0;

  /**
   * @brief Update the geometrical structure
   *   when both source and targets points are modified.
   *
   * @warning This is a pure virtual function.
   */
  virtual void updateSourceTarget() = 0;

  //@}


// -------------------------------------------------------------------
}; // class AbstractGenPrimitive




// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// P R E D E F I N E D    P R I M I T I V E    T Y P E S
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


/**@name Abstract primitive type names */
//       =============================
//@{

/**
 * @ingroup DS_PRIM
 *
 * @brief Primitive with <b>integer</b> coordinates.
 *
 * @see qgar::IPrimitive
 */
typedef AbstractGenPrimitive<int> Primitive;

/**
 * @ingroup DS_PRIM
 *
 * @brief Primitive with <b>integer</b> coordinates.
 *
 * @see qgar::Primitive
 */
typedef AbstractGenPrimitive<int> IPrimitive;

/**
 * @ingroup DS_PRIM
 *
 * @brief Primitive with <b>float</b> coordinates.
 */
typedef AbstractGenPrimitive<float> FPrimitive;

/**
 * @ingroup DS_PRIM
 *
 * @brief Primitive with <b>double</b> coordinates.
 */
typedef AbstractGenPrimitive<double> DPrimitive;

//@}


// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


} // namespace qgar


#endif /* ___QGAR_ABSTRACTGENPRIMITIVE_H_INCLUDED__ */
