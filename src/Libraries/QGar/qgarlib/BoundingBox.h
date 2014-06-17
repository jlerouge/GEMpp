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


#ifndef __BOUNDINGBOX_H_INCLUDED__
#define __BOUNDINGBOX_H_INCLUDED__


/**
 * @file BoundingBox.h
 *
 * @brief Header file of class qgar::BoundingBox.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   February 23, 2004  16:08
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: BoundingBox.h,v 1.23 2007/02/14 17:34:04 masini Exp $ */


// STD
#include <iosfwd> // Avoid including classes when not necessary
// QGAR
#include "ISerializable.h"
#include "primitives.h"
#include "QgarErrorDomain.h"



namespace qgar
{


/**
 * @ingroup DS_MISC
 *
 * @class BoundingBox BoundingBox.h "qgarlib/BoundingBox.h"
 *
 * @brief A bounding box.
 *
 * A bounding box is a rectangle with sides parallel
 * to the coordinate system axis. It is represented
 * by its top left and bottom right corners.
 *
@verbatim
   0
    +---------------------------------------> X
    |
    |            <---- length ---->
    |   top left o----------------+  ^
    |            |                |  |
    |            |  Bounding Box  |height
    |            |                |  |
    |            +----------------o  v
    V                            bottom right

    Y
@endverbatim
 * @warning
 * <ul>
 * <li>A bounding box is supposed to be used
 *   within an <b>integer</b> coordinate system only.</li>
 * <li><b>As the origin of the coordinates system in images
 *   is at the top left corner of the plane, the top left and bottom
 *   right corners of the box are topographically upside down for
 *   more convenience.</b></li>
 * <li>The borders of a bounding box are part of the bounding box.
 *   In particular, the corresponding pixels are taken into account
 *   to compute the geometrical characteristics of the box:
 *   width, height, area...</li>
 * </ul>
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   February 23, 2004  16:08
 * @since  Qgar 2.1.1
 */
class BoundingBox

  : public ISerializable

{
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
   * One-unit-length and one-unit-width bounding box located
   * at the origin of the coordinate system.
   */
  BoundingBox();

  /**
   * @brief Copy constructor.
   *
   * @param aBox  a bounding box
   */
  DLL_EXPORT BoundingBox(const BoundingBox& aBox);

  /**
   * @brief Initialize from two points.
   *
   * The two given points, <b>aPt1</b> and <b>aPt2</b>, are supposed
   * to be two opposite corners (top left and bottom right, or top right
   * and bottom left) of the resulting bounding box. The corresponding
   * coordinates of top left and bottom right corners are automatically
   * computed.
   *
   * @param aPt1  a point
   * @param aPt2  a point
   */
  BoundingBox(const GenPoint<int>& aPt1, const GenPoint<int>& aPt2);
  
  /**
   * @brief Initialize from coordinates of two points.
   *
   * The two given points are supposed to be two opposite corners (top
   * left and bottom right, or top right and bottom left) of the
   * resulting bounding box. The corresponding coordinates of top left
   * and bottom right corners are automatically computed.
   *
   * @param aX1  X coordinate of first point
   * @param aY1  Y coordinate of first point
   * @param aX2  X coordinate of second point
   * @param aY2  Y coordinate of second point
   */
  DLL_EXPORT BoundingBox(int aX1, int aY1, int aX2, int aY2);
  
  /**
   * @brief Initialize from top left corner, length and height.
   *
   * The length and the height must be greater than 0.
   *
   * @param aTopLeft top left corner of the resulting bounding box
   * @param aLength  length of the resulting bounding box
   * @param aHeight  height of the resulting bounding box
   *
   * @exception qgar::QgarErrorDomain  length must be greater than 0
   * @exception qgar::QgarErrorDomain  heigth must be greater than 0
   */
  BoundingBox(const GenPoint<int>& aTopLeft, int aLength, int aHeight)
   ;
  
  /**
   * @brief Initialize from bottom right corner, length and height.
   *
   * The length and the height must be greater than 0.
   *  
   * @param aLength       length of the resulting bounding box
   * @param aHeight       height of the resulting bounding box
   * @param aBottomRight  bottom right corner of the resulting bounding box
   *
   * @exception qgar::QgarErrorDomain  length must be greater than 0
   * @exception qgar::QgarErrorDomain  heigth must be greater than 0
   */
  BoundingBox(int aLength, int aHeight, const GenPoint<int>& aBottomRight)
   ;

  //@}
  
  
  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Non-virtual destructor.
   */
  DLL_EXPORT ~BoundingBox();

  //@}
  
  
  /** @name Access to corners */
  //        =================
  //@{

  /**
   * @brief Get top left corner.
   */
  inline const GenPoint<int>& accessTopLeft() const;

  /**
   * @brief Get a copy of the top left corner.
   */
  GenPoint<int> topLeft() const;
  
  /**
   * @brief Get bottom right corner.
   */
  inline const GenPoint<int>& accessBottomRight() const;

  /**
   * @brief Get a copy of the bottom right corner.
   */
  inline GenPoint<int> bottomRight() const;

  //@}
  
  
  /** @name Access to coordinates */
  //        =====================
  //@{

  /**
   * @brief Get X coordinate of top left corner.
   */
  inline int xTopLeft() const;

  /**
   * @brief Get Y coordinate of top left corner.
   */
  inline int yTopLeft() const;
  
  /**
   * @brief Get X coordinate of bottom right corner.
   */
  inline int xBottomRight() const;

  /**
   * @brief Get Y coordinate of bottom right corner.
   */
  inline int yBottomRight() const;

  //@}
  

  /** @name Access to dimensions */
  //        ====================
  //@{

  /**
   * @brief Same as qgar::BoundingBox::width.
   */
  inline int length() const;

  /**
   * @brief Get width.
   *
   * @warning As the pixels of the borders belong to the box,
   * the width is
   * \f$ X_{bottom-right-corner} - X_{top-left-corner} + 1 \f$
   */
  inline int width() const;

  /**
   * @brief Get height.
   *
   * @warning As the pixels of the borders belong to the box,
   * the width is
   * \f$ Y_{bottom-right-corner} - Y_{top-left-corner} + 1 \f$
   */
  inline int height() const;

  /**
   * @brief Get area.
   *
   * @warning The pixels of the borders belong to the box,
   * and thus are counted in the area.
   */
  inline int area() const;

  //@}


  /** @name Geometrical predicates */
  //        ======================
  //@{

  /**
   * @brief Return <b>true</b> if the given point belongs to
   *   the current bounding box, including borders.
   *
   * @param aPt   a point with <b>integer</b> coordinates
   */
  inline bool contains(const GenPoint<int>& aPt) const;

  /**
   * @brief Return <b>true</b> if the point defined
   *   by the given coordinates belongs to the current
   *   bounding box, including borders.
   *
   * @param aX    an <b>integer</b> X coordinate
   * @param aY    an <b>integer</b> Y coordinate
   */
  bool contains(int aX, int aY) const;

  /**
   * @brief Return <b>true</b> if the current bounding box
   *   contains the given bounding box.
   *
   * @param aBox  a bounding box
   */
  inline bool contains(const BoundingBox& aBox) const;

  /**
   * @brief Return <b>true</b> if the current bounding box
   *   intersects the given bounding box.
   *
   * @param aBox  a bounding box
   */
  bool intersects(const BoundingBox& aBox) const;

  //@}


  /** @name Geometrical operations */
  //        ======================
  //@{

  /**
   * @brief Intersection
   *   between the current and given bounding boxes.
   *
   * If the two bounding boxes intersect, returns a pointer
   * to the bounding box representing the intersection.
   * <b>If the two bounding boxes do not intersect, returns
   * a null pointer.</b>
   *
   * @param aBox  a bounding box
   */
  BoundingBox* intersection(const BoundingBox& aBox) const;

  //@}


  /** @name Set corners */
  //        ===========
  //@{

  /**
   * @brief Set top left corner using a point.
   *
   * @param aPt  a point
   *
   * @warning If the new corner (point <b>aPt</b>) does not match
   * the current bottom right corner, the function raises an exception.
   *
   * @exception qgar::QgarErrorDomain  new corner does not fit box
   */
  void setTopLeft(const GenPoint<int>& aPt);

  /**
   * @brief Set top left corner using X and Y coordinates.
   *
   * @param aX  X coordinate
   * @param aY  Y coordinate
   *
   * @warning If the new corner does not match the current bottom
   * right corner, the function raises an exception.
   *
   * @exception qgar::QgarErrorDomain  new corner does not fit box
   */
  void setTopLeft(int aX, int aY);

  /**
   * @brief Set X coordinate of top left corner.
   *
   * @param aX  X coordinate
   *
   * @warning If the new corner does not match the current bottom
   * right corner, the function raises an exception.
   *
   * @exception qgar::QgarErrorDomain  new corner does not fit box
   */
  void setXTopLeft(int aX);

  /**
   * @brief Set Y coordinate of top left corner.
   *
   * @param aY  Y coordinate
   *
   * @warning If the new corner does not match the current top left
   * corner, the function raises an exception.
   *
   * @exception qgar::QgarErrorDomain  new corner does not fit box
   */
  void setYTopLeft(int aY);

  /**
   * @brief Set bottom right corner using a point.
   *
   * @param aPt  a point
   *
   * @warning If the new corner (point <b>aPt</b>) does not match
   * the current top left corner, the function raises an exception.
   *
   * @exception qgar::QgarErrorDomain  new corner does not fit box
   */
  void setBottomRight(const GenPoint<int>& aPt);

  /**
   * @brief Set bottom right corner using X and Y coordinates.
   *
   * @param aX  X coordinate
   * @param aY  Y coordinate
   *
   * @warning If the new corner does not match the current top left
   * corner, the function raises an exception.
   *
   * @exception qgar::QgarErrorDomain  new corner does not fit box
   */
  void setBottomRight(int aX, int aY);

  /**
   * @brief Set X coordinate of bottom right corner.
   *
   * @param aX  X coordinate
   *
   * @warning If the new corner does not match the top left corner,
   * the function raises an exception.
   *
   * @exception qgar::QgarErrorDomain  new corner does not fit box
   */
  void setXBottomRight(int aX);

  /**
   * @brief Set Y coordinate of bottom right corner.
   *
   * @param aY  Y coordinate
   *
   * @warning If the new corner does not match the current top left
   * corner, the function raises an exception.
   *
   * @exception qgar::QgarErrorDomain  new corner does not fit box
   */
  void setYBottomRight(int aY);

  /**
   * @brief Set both top left and bottom right corners from two points.
   *
   * The two given points, <b>aPt1</b> and <b>aPt2</b>, are supposed
   * to be two opposite corners (top left and bottom right, or top
   * right and bottom left) of the resulting bounding box.
   * The corresponding coordinates of top left and bottom right
   * corners are automatically computed.
   *
   * @param aPt1  a point
   * @param aPt2  a point
   */
  void setCorners(const GenPoint<int>& aPt1, const GenPoint<int>& aPt2);

  /**
   * @brief Set both top left and bottom right corners
   * from coordinates of two points.
   *
   * The two given points are supposed to be two opposite corners
   * (top left and bottom right, or top right and bottom left)
   * of the resulting bounding box. The corresponding coordinates
   * of top left and bottom right corners are automatically computed.
   *
   * @param aX1  X coordinate of first corner
   * @param aY1  Y coordinate of first corner
   * @param aX2  X coordinate of second corner
   * @param aY2  Y coordinate of second corner
   */
  void setCorners(int aX1, int aY1, int aX2, int aY2);

  //@}


  /** @name Operators */
  //        =========
  //@{

  /**
   * @brief Assign the given bounding box to the current bounding box.
   *
   * @param aBox  a bounding box
   */
  BoundingBox& operator=(const BoundingBox& aBox);

  /**
   * @brief Same as function qgar::BoundingBox::eq.
   *
   * @param aBox  a bounding box
   */
  inline bool operator==(const BoundingBox& aBox) const;

  /**
   * @brief Same as function qgar::BoundingBox::NotEq.
   *
   * @param aBox  a bounding box
   */
  inline bool operator!=(const BoundingBox& aBox) const;

  //@}


  /**@name Functional operators */
  //       ====================
  //@{

   /**
   * @brief Equality.
   *
   * Return <b>true</b> if the current bounding box
   * and the given bounding box have the same coordinates.
   *
   * @param aBox  a bounding box
   */
  bool eq(const BoundingBox& aBox) const;

  /**
   * @brief Inequality.
   *
   * Return <b>true</b> if the current bounding box
   * and the given bounding box have different coordinates.
   *
   * @param aBox  a bounding box
   */
  bool notEq(const BoundingBox& aBox) const;

  //@}


  /** @name Serialization/deserialization */
  //        =============================
  //@{

  /**
   * @brief Deserializes the current box from an input stream.
   *
   * A serialized bounding box is represented as:
@verbatim
   BoundingBox(<TOP LEFT CORNER>)(<BOTTOM RIGHT CORNER>)
@endverbatim
   *
   * @param anInStream  the input stream
   */
  virtual std::istream& read(std::istream& anInStream);

  /**
   * @brief Serializes the current box to an input stream.
   *
   * A serialized bounding boxi is represented as:
@verbatim
   BoundingBox(<TOP LEFT CORNER>)(<BOTTOM RIGHT CORNER>)
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


  /** @name Representation of a bounding box */
  //        ================================
  //@{

  /**
   * @brief Top left corner.
   */
  GenPoint<int> topLeft_;

  /**
   * @brief Bottom right corner.
   */
  GenPoint<int> bottomRight_;

  //@}

// -------------------------------------------------------------------

}; // class BoundingBox




// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// I N L I N E   F U N C T I O N S   I M P L E M E N T A T I O N
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII


// =================
// ACCESS TO CORNERS
// =================


// GET TOP LEFT CORNER

inline const GenPoint<int>& 
BoundingBox::accessTopLeft() const
{
  return topLeft_;
}


// GET A COPY OF THE TOP LEFT CORNER

inline GenPoint<int> 
BoundingBox::topLeft() const
{
  return topLeft_;
}


// GET BOTTOM RIGHT CORNER

inline const GenPoint<int>& 
BoundingBox::accessBottomRight() const
{
  return bottomRight_;
}


// GET A COPY OF THE BOTTOM RIGHT CORNER

inline GenPoint<int> 
BoundingBox::bottomRight() const
{
  return bottomRight_;
}


// =====================
// ACCESS TO COORDINATES
// =====================


// GET X COORDINATE OF TOP LEFT CORNER

inline int 
BoundingBox::xTopLeft() const
{
  return topLeft_.x();
}


// GET Y COORDINATE OF TOP LEFT CORNER

inline int
BoundingBox::yTopLeft() const
{
  return topLeft_.y();
}


// GET X COORDINATE OF BOTTOM RIGHT CORNER

inline int
BoundingBox::xBottomRight() const
{
  return bottomRight_.x();
}


// GET Y COORDINATE OF BOTTOM RIGHT CORNER

inline int
BoundingBox::yBottomRight() const
{
  return bottomRight_.y();
}


// ====================
// ACCESS TO DIMENSIONS
// ====================


// SAME AS qgar::BoundingBox::width

inline int
BoundingBox::length() const
{
  return width();
}


// GET WIDTH

inline int
BoundingBox::width() const
{
  return bottomRight_.x() - topLeft_.x() + 1;
}


// GET HEIGHT

inline int
BoundingBox::height() const
{
  return bottomRight_.y() - topLeft_.y() + 1;
}


// GET AREA

inline int
BoundingBox::area() const
{
  return length() * height();
}


// ===========================================
// G E O M E T R I C A L   P R E D I C A T E S
// ===========================================


// DOES THE GIVEN POINT BELONG TO THE CURRENT BOUNDING BOX?

inline bool
BoundingBox::contains(const GenPoint<int>& aPt) const
{
  return this->contains(aPt.x(), aPt.y());
}


// DOES THE CURRENT BOUNDING BOX CONTAIN THE GIVEN BOUNDING BOX?

inline bool
BoundingBox::contains(const BoundingBox& aBox) const
{
  return (this->contains(aBox.topLeft()))
    && (this->contains(aBox.bottomRight()));
}


// =========
// OPERATORS
// =========


// EQUALITY

inline bool
BoundingBox::operator==(const BoundingBox& aBox) const
{
  return eq(aBox);
}


// INEQUALITY

inline bool
BoundingBox::operator!=(const BoundingBox& aBox) const
{
  return notEq(aBox);
}


// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII


} // namespace qgar


#endif /* __BOUNDINGBOX_H_INCLUDED__ */
