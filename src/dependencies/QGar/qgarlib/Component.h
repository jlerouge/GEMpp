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


#ifndef __COMPONENT_H_INCLUDED__
#define __COMPONENT_H_INCLUDED__


/**
 * @file Component.h
 *
 * @brief Header file of classes qgar::Component.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   March 17, 2004  17:17
 * @since  Qgar 2.1
 */



// For RCS/CVS use: Do not delete
/* $Id: Component.h,v 1.32 2007/02/14 17:34:04 masini Exp $ */



// STD
#include <list>
// QGAR
#include "GenImage.h"
#include "image.h"
namespace qgar
{
  // Avoid #include's when not necessary
  class BoundingBox;
  template <class T> class GenPoint;
  class Maer;
}



namespace qgar
{


/**
 * @ingroup GRAPHPROC_CC
 *
 * @class Component Component.h "qgarlib/Component.h"
 *
 * @brief A (connected) component.
 *
 * <a name="hd1"></a><b>1 &nbsp;REPRESENTATION OF A COMPONENT</b>
 *
 * - A pointer to the corresponding component image:
 *   qgar::Component::pCompImg_
 * - A label:
 *   qgar::Component::label_
 * - The label of the component in which the current component
 *   is included:
 *   qgar::Component::inLabel_
 * - A color (qgar::QGE_BW_::BLACK or qgar::QGE_BW_::WHITE):
 *   qgar::Component::color_
 * - The coordinates of the top left pixel of the component:
 *   qgar::Component::xTopLeftPix_
 * - The bounding box of the component:
 *   qgar::Component::boundingBox_
 * - The area of the component, in pixels:
 *   qgar::Component::areaPx_
 * - The MAER (see class qgar::Maer) of the component,
 *   computed when first accessed:
 *   qgar::Component::maer_
 * - The area of the MAER, in pixels:
 *   qgar::Component::maerAreaPx_
 * - The points of the external contour of the component
 *   (see <a href="#hd2">section 2</a> below:
 *   qgar::Component::contour_
 * - The perimeter of the component, in pixels
 *   (see <a href="#hd5">section 5</a> below:
 *   qgar::Component::perimeterPx_
 * - A table giving offsets to add to a given pixel pointer
 *   to get the successive 4-connected neighbors
 *   in a \f$3\times 3\f$ neighborhood:
 *   qgar::Component::offset3X3_4_
 * - A table giving offsets to add to a given pixel pointer
 *   to get the successive 8-connected neighbors
 *   in a \f$3\times 3\f$ neighborhood.
 *   qgar::Component::offset3X3_8_
 *
 *
 * <a name="hd2"></a><b>2 &nbsp;THE CONTOUR POINTS</b>
 *
 * The contour points of a component are computed
 * when first accessed,
 * or when the contour vertices are accessed,
 * or when the MAER is accessed,
 * or when the perimeter is accessed:
 *
 * - A contour is defined as a part of the corresponding component:
 *   contour points effectively belong to the component.
 * - Contour computation is based on 8-connectivity when the component
 *   is black, on 4-connectivity when the component is white.
 * - The first contour point is the top left point of the component. 
 * - The outside of the component is on the left side when
 *   traversing the contour points in the order the component
 *   supplies them.
 * - The contour of a one-pixel component includes a single point,
 *   the pixel in question.
 * - Contour points define a closed chain,
 *******************************************************************************
 * BEGIN: TO BE UPDATED
 *******************************************************************************
 *   <i>i.e.</i> last point is connected to the first point.
 * - The contour includes duplicate points when parts (or the whole)
 *   of the component are one-pixel thick, as the points of
 *   one-pixel-thick parts are traversed two times while following
 *   the corresponding contour pieces
 *   (see examples in <a href="#hd4">section 4</a> below).
 *
 *
 * <a name="hd4"></a><b>4 &nbsp;EXAMPLES</b>
 *
 * <ul>
 * <li><b>Black component (8-connectivity)</b>
@verbatim
. . . . . . . . . .
. . A b c d e f g .
. h . i j . . k . .     'A', 'b', 'c', etc.: pixels of the given component
. l . . m n o . . .                     'A': top left pixel of the component
. p . . . q . . . .                     '.': pixels of other components 
. . . . . r . . . .
. . . . . . . . . .
@endverbatim
 * - Contour points:
 *   A b c d e f g k o q r q m i A h l p l h
 * - Contour vertices:
 *   A g q r q A h p h
 * </li>
 *
 * <li><b>White component (4-connectivity)</b>
@verbatim
. . . . . . . . . .
. . A b c d e f g .
. h i j . . k l . .     'A', 'b', 'c', etc.: pixels of the given component
. . . m n o p . . .                     'A': top left pixel of the component
. . . . . q . . . .                     '.': pixels of other components 
. . . . . r . . . .
. . . . . . . . . .
@endverbatim
 * - Contour points:
 *   A b c d e f g f l k p o q r q o n m j i h i
 * - Contour vertices:
 *   A g f l k p o r o m j h i
 * </li>
 * </ul>
 *
 *
 *******************************************************************************
 * END: TO BE UPDATED
 *******************************************************************************
 * <a name="hd5"></a><b>5 &nbsp;THE PERIMETER</b>
 *
 * The perimeter of a component is computed
 * when first accessed,
 * or when the contour points are accessed,
 * or when the MAER is accessed:
 *
@verbatim
              (1)        (2)          (3)              (4)
             +---+    +---+---+    +---+---+        +---+---+
             |   |    |   |   |    |   |   |        |   |   |
             +---+    +---+---+    +---+---+    +---+---+---+
                                       |   |    |   |
                                       +---+    +---+
perimeter in
points (Pt):   1          2            3                3
pixels (Px):   4          6            8               10
@endverbatim
 * The perimeter may be obtained in two units:
 * - <i>points</i>: the perimeter then gives the number of points
 *   of the component contour (see function qgar::Component::perimeterPt),
 * - <i>pixels</i>: the perimeter gives the length of the component
 *   contour assuming a pixel is a unit-width-square
 *   (see function qgar::Component::perimeterPx).
 *
 * See <a href="#sec85">section 8.5</a> for full details
 * about the perimeter computation.
 *
 *
 * @warning No default constructor is provided.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   Mar 17, 2004  17:17
 * @since  Qgar 2.1
 */
class Component
{
// -------------------------------------------------------------------
// T Y P E   D E F I N I T I O N
// -------------------------------------------------------------------
public:

  /** @name Types related to a component */
  //        ============================
  //@{

  /**
   * @brief Type of a component label.
   */
  typedef int label_type;

  //@}


// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  /** @name Constructors */
  //        ============
  //@{

  /**
   * @brief Create from full data.
   *
   * @param aPCompImg      pointer to the corresponding component image
   * @param aLabel         label
   * @param anInLabel      label of comprising component
   * @param aBW            color (black or white)
   * @param aXTopLeftPix   X coordinate of the top left pixel
   * @param aYTopLeftPix   Y coordinate of the top left pixel
   * @param aXTopLeft      top left X coordinate of the bounding box
   * @param aYTopLeft      top left Y coordinate of the bounding box
   * @param aXBottomRight  bottom right X coordinate of the bounding box
   * @param aYBottomRight  bottom right Y coordinate of the bounding box
   * @param anAreaPx       area (in pixels)
   * @param aPOffset4      4-connectivity offsets of a 3X3 neighborhood
   * @param aPOffset8      8-connectivity offsets of a 3X3 neighborhood
   */
  Component(GenImage<label_type>* aPCompImg,
	    int   aLabel,
	    int   anInLabel,
	    QGEbw aBW,
	    int   aXTopLeftPix,
	    int   aYTopLeftPix,
	    int   aXTopLeft,
	    int   aYTopLeft,
	    int   aXBottomRight,
	    int   aYBottomRight,
	    int   anAreaPx,
	    int*  aPOffset4,
	    int*  aPOffset8);

  /**
   * @brief Copy constructor.
   *
   * @param aCComp  a connected component
   *
   * @warning Perform a deep copy: The whole data
   * of the given connected component is duplicated.
   */
  Component(const Component& aCComp);

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  virtual ~Component();

  //@}


  /** @name Labels */
  //        ======
  //@{

  /**
   * @brief Maximum label.
   *
   * @warning This is a <i>static</i> data member.
   */
  static const label_type LABEL_MAX_;

  /**
   * @brief Label for an object which is not yet labelled.
   *
   * @warning This is a <i>static</i> data member.
   */
  static const label_type LABEL_NO_;

  /**
   * @brief Label to mark the first pixel of the component contour.
   *
   * It is used during contour copnstruction.
   *
   * @warning This is a <i>static</i> data member.
   */
  static const label_type LABEL_START_;

  /**
   * @brief Label to mark a pixel belonging to the component contour.
   *
   * It is used during contour copnstruction.
   *
   * @warning This is a <i>static</i> data member.
   */
  static const label_type LABEL_CONTOUR_;

  /**
   * @brief Get component label.
   */
  inline label_type label() const;

  /**
   * @brief Get label of comprising component.
   */
  inline label_type inLabel() const;

  //@}


  /** @name Access to color */
  //        ===============
  //@{

  /**
   * @brief Get color.components
   */
  inline QGEbw color() const;

  //@}


  /** @name Access to coordinates */
  //        =====================
  //@{

  /**
   * @brief Get X coordinate of the top left pixel of the component.
   */
  inline int xTopLeftPix() const;

  /**
   * @brief Get Y coordinate of the top left pixel of the component.
   */
  inline int yTopLeftPix() const;

  /**
   * @brief Get bounding box.
   */
  DLL_EXPORT const BoundingBox& accessBoundingBox() const;

  /**
   * @brief Get a copy of the bounding box.
   */
  BoundingBox boundingBox() const;

  //@}


  /** @name Area */
  //        ====
  //@{

  /**
   * @brief Get component area (in pixels).
   */
  inline int areaPx() const;

  /**
   * @brief Get density with regard to the bounding box.
   *
   * The density is the ratio between the area (number of pixels)
   * of the component and the area of its bounding box.
   */
  double densityBox() const;

  //@}


  /** @name MAER (Minimum-Area Encasing Rectangle) */
  //        ======================================
  //@{

  /**
   * @brief Get the MAER.
   *
   * @warning
   * The MAER is computed and <i>stored</i>when first accessed.
   */
  const Maer& accessMaer();

  /**
   * @brief Get a copy of the MAER.
   *
   * @warning
   * The MAER is computed and <i>stored</i> when first accessed.
   */
  Maer maer();

  /**
   * @brief Get MAER area in pixels.
   *
   * @warning
   * The area of the MAER is calculated in the <b>continuous</b>
   * 2D space and is provided by the corresponding data of the
   * object representing the MAER:
   * <b>(aComponent.accessMaer()).area()</b>, for example.
   * As connected components are constructed in the 2D
   * <b>discrete</b> space, an <b>approximated value</b>
   * of the MAER area is also available in pixels.
   * @warning
   * The MAER is computed and <i>stored</i>when first accessed.
   */
  int maerAreaPx();

  /**
   * @brief Get density with regard to the MAER.
   *
   * The density is the ratio between the area (number of pixels)
   * of the component and the area of its MAER.
   *
   * @warning
   * The MAER is computed and <i>stored</i>when first accessed.
   */
  double densityMaer();

  //@}


  /** @name Contour */
  //        =======
  //@{

  /**
   * @brief Get the external contour points.
   *
   * See <a href="#hd3">section 3</a> of the class header
   * for detailed information about the contour.
   *
   * @warning
   * The contour is computed and <i>stored</i>when first accessed
   */
  const std::list<IPoint>& accessContour();

  /**
   * @brief Get a copy of the contour points.
   *
   * See <a href="#hd3">section 3</a> of the class header
   * for detailed information about the contour.
   *
   * @warning
   * The contour is computed and <i>stored</i>when first accessed
   */
  std::list<IPoint> contour();

  //@}


  /** @name Perimeter */
  //        =========
  //@{

  /**
   * @brief Get the perimeter in points.
   *
   * See <a href="#hd5">section 5</a> of the class header
   * for detailed information.
   *
   * @warning
   * The perimeter is computed and <i>stored</i>when first accessed
   */
  inline int perimeterPt();

  /**
   * @brief Get the perimeter in pixels.
   *
   * See <a href="#hd5">section 5</a> of the class header
   * for detailed information.
   *
   * @warning
   * The perimeter is computed and <i>stored</i>when first accessed
   */
  int perimeterPx();

  //@}


  /** @name Operators */
  //        =========
  //@{

  /**
   * @brief Assignment.
   *
   * @param aCComp  connected component to be assigned
   */
  Component& operator=(const Component& aCComp);

  //@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:


  /** @name Pixel map of the component image */
  //        ================================
  //@{

  /**
   * @brief Pointer to the corresponding component image.
   */
  GenImage<label_type>* pCompImg_;

  //@}


  /** @name Labels */
  //        ======
  //@{

  /**
   * @brief Label of the component.
   *
   * @warning
   * It <i>must</i> be an integer number.
   */
  label_type label_;

  /**
   * @brief Label of the comprising component.
   */
  label_type inLabel_;

  //@}


  /** @name Color */
  //        =====
  //@{

  /**
   * @brief Color.
   */
  QGEbw color_;

  //@}


  /** @name Coordinates */
  //        ===========
  //@{

  /**
   * @brief X coordinate of the top left pixel of the component.
   */
  int xTopLeftPix_;

  /**
   * @brief Y coordinate of the top left pixel of the component.
   */
  int yTopLeftPix_;

  /**
   * @brief Bounding box.
   */
  BoundingBox boundingBox_;

  //@}


  /** @name Area */
  //        ====
  //@{

  /**
   * @brief Component effective area (in pixels).
   */
  int areaPx_;

  //@}


  /** @name MAER (Minimum-Area Encasing Rectangle) */
  //        ======================================
  //@{

  /**
   * @brief Minimum-Area Enclosing Rectangle (MAER).
   */
  Maer* maer_;

  /**
   * @brief Minimum-Area Enclosing Rectangle (MAER).
   */
  int maerAreaPx_;

  //@}


  /** @name Contour */
  //        =======
  //@{

  /**
   * @brief List of the contour points (<b>integer</b> coordinates).
   *
   * See <a href="#hd2">section 2</a> of the class header
   * for detailed information.
   */
  std::list<IPoint> contour_;

  /**
   * @brief Perimeter of the contour, in pixels.
   *
   * See <a href="#hd5">section 5</a> of the class header
   * for detailed information.
   */
  int perimeterPx_;

  //@}


  /** @name 3X3 neighborhood */
  //        ================
  //@{

  /**
   * @brief Offsets to add to a pixel pointer to get the successive
   * 4-connected neighbors in a \f$3\times 3\f$ neighborhood.
   *
@verbatim
     +---+---+---+
     | * | n0| * |
     +---+---+---+   contour
(1)  --n6--c | n2|-> direction     SEARCH LIST: n0 - n2 - n4 - n6
     +---+---+---+   (East)
     | * | n4| * |
     +---+---+---+


     +---+-|-+---+
     | * | n0| * |
     +---+-|-+---+
(2)  | n6| c | n2|                 SEARCH LIST: n2 - n4 - n6 - n0
     +---+---+---+
     | * | n4| * |
     +---+---+---+
           |
           V
contour direction (South)


entry for figure 1 --+       +-- entry for figure 2
                     |       |
                     V       V
contour      N       E       S       W
direction    0   1   2   3   4   5   6   7   8   9  10  11  12 
           +---+---+---+---+---+---+---+---+---+---+---+---+---+
           | -1| * | -w| * | 1 | * | w | * | -1| * |-w | * | 1 |
           +---+---+---+---+---+---+---+---+---+---+---+---+---+

                            w = pixel map width
@endverbatim
   *
   * The table is used when following the contour of a component:
   * let <b>c</b> be the current contour pixel,
   * and <b>currDir</b> be the so-called <i>contour direction</i>,
   * that is to say the direction of the contour part being
   * constructed, whose <b>c</b> is the current end.
   * Directions are coded clockwise, from North to North-West:
   * see enum type qgar::QGEdirection.
   *
   * <b>currDir</b> determines the index to enter the table:
   * <b>2</b> (East) and <b>4</b> (South) on figures 1 and 2,
   * respectively. The 4 consecutive pertinent values
   * (excepting those marked '<b>*</b>') available from the entry
   * index provide the offsets to add to the pointer to <b>c</b>
   * in order to get the pointers to the 4 successive pertinent
   * neighbors of <b>c</b>.
   * Odd-indexed values have no use and just exist to preserve
   * the correspondance between the current direction code and the
   * entry index.
   *
   * Neighbors are provided clockwise: see
   * <a href="#sec41">Contour following of 4-connected components</a>
   * for full details.
   * 
   *
   * @see also qgar::ConnectedComponentsImpl::offset3X3_4_
   */
   int* offset3X3_4_;

  /**
   * @brief Offsets to add to a pixel pointer to get the successive
   * 8-connected neighbors in a \f$3\times 3\f$ neighborhood.
   *
@verbatim
     +---+---+---+
     | * | n0| n1|
     +---+---+---+   contour
(1)  --n6--c | n2|-> direction     SEARCH LIST: n0 - n2 - n1 - n4 - n3 - n6
     +---+---+---+   (East)
     | * | n4| n3|
     +---+---+---+

     \---+---+---+
     | n7| * | n1|
     +---\---+---+
(2)  | *   c | n2|                 SEARCH LIST: n2 - n1 - n4 - n3 - n5 - n7
     +---+---+---+
     | n5| n4| n3|
     +---+---+---+
                  \ contour direction (South-East)
                   

		     search rank
                     0    1    2    3    4    5
                  +----+----+----+----+----+----+
           / N  0 | -1 | -w |-w-1|  1 |-w+1|  w |
           |      +----+----+----+----+----+----+
           | NE 1 | -w |-w-1|  1 |-w+1| w+1| w-1|
           |      +----+----+----+----+----+----+
           | E  2 | -w |  1 |-w+1|  w | w+1| -1 | <- figure 1
           |      +----+----+----+----+----+----+
           | SE 3 |  1 |-w+1|  w | w+1| w-1|-w-1| <- figure 2
 contour  <       +----+----+----+----+----+----+
direction  | S  4 |  1 |  w | w+1| -1 | w-1| -w |
           |      +----+----+----+----+----+----+
           | SW 5 |  w | w+1| -1 | w-1|-w-1|-w+1|
           |      +----+----+----+----+----+----+
           | W  6 |  w | -1 | w-1| -w |-w-1|  1 |
           |      +----+----+----+----+----+----+
           \ NW 7 | -1 | w-1| -w |-w-1|-w+1| w+1|
                  +----+----+----+----+----+----+

                        w = pixel map width
@endverbatim
   * 
   * The table is used when following the contour of a component:
   * let <b>c</b> be the current contour pixel,
   * and <b>currDir</b> be the so-called <i>contour direction</i>,
   * that is to say the direction of the contour part being
   * constructed, whose <b>c</b> is the current end.
   * Directions are coded clockwise, from North to North-West:
   * see enum type qgar::QGEdirection.
   *
   * <b>currDir</b> determines the row to be used:
   * <b>2</b> (East) and <b>3</b> (South-east) on figures 1 and 2,
   * respectively. The successive values of the row provide the
   * offsets to add to the pointer to <b>c</b> in order to get
   * the pointers to the (6) successive pertinent neighbors of
   * <b>c</b>, which are provided clockwise: see
   * <a href="#sec81">Contour following of 8-connected components</a>
   * for full details.
   *
   * @see also qgar::ConnectedComponentsImpl::offset3X3_8_
   *
   *
   * <b>Warning</b>
   * For more efficiency, the 2-dimensional table is implemented
   * as a 1-dimensional array!
   */
   int* offset3X3_8_;

  //@}


// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

  /** @name Constructors */
  //        ============
  //@{

  /**
   * @brief Disabled default constructor.
   *
   * The default constructor belongs to the private section
   * so that clients cannot use it.
   */
  Component();

  //@}


  // =================================================================
  /** @name Contour following of 4-connected components

<a name="sec41"></a><b>4.1 &nbsp;DIRECTION CODING</b>
  
@verbatim
N  NE  E  SE  S  SW  W  NW
0  1   2  3   4  5   6  7
@endverbatim
  
Directions are coded clockwise, from <b>N</b>(orth) to
<b>N</b>(orth-)<b>W</b>(est): see enum type qgar::QGEdirection.


<a name="sec42"></a><b>4.2 &nbsp;SEARCHING FOR THE NEW CONTOUR POINT</b>
  
@verbatim
     +---+---+---+
     | * | n0| * |
     +---+---+---+   contour
(1)  --n6--c | n2|-> direction      SEARCH LIST: n0 - n2 - n4 - n6
     +---+---+---+   (East)                RANK:  0    2    4    6
     | * | n4| * |
     +---+---+---+

     +---+-|-+---+
     | * | n0| * |
     +---+-|-+---+
(2)  | n6| c | n2|                  SEARCH LIST: n2 - n4 - n6 - n0
     +---+---+---+                         RANK:  0    2    4    6
     | * | n4| * |
     +---+---+---+
           |
           V
contour direction (South)
@endverbatim
  
- <b>currDir</b> is the so-called <i>contour direction</i>,
  that is to say the direction of the contour part being
  constructed, whose <b>c</b> is the current end.
- The outside of the component is always on the left side when
  moving along the contour direction.
- The new contour point is searched clockwise among the 4 neighbors
  of <b>c</b>, starting from the point left-perpendicular to
  <b>currDir</b>:
  <b>n0</b> and <b>n2</b> on figures 1 and 2, respectively.
- The elements of the search list are successively ranked
  <b>0 - 2 - 4 - 6</b> for more convenience, as shown in next sections.


<a name="sec43"></a><b>4.3 &nbsp;COORDINATES OF NEIGHBORS</b>
  
@verbatim
       entry for figure 1 --+     +-- entry for figure 2
                            |     |
                            V     V
            currDir   N     E     S     W
                      0  1  2  3  4  5  6  7  8  9 10 11 12 
                    +--+--+--+--+--+--+--+--+--+--+--+--+--+
        s_4_incr_x_ |-1| *| 0| *| 1| *| 0| *|-1| *| 0| *| 1|
                    +--+--+--+--+--+--+--+--+--+--+--+--+--+
                    +--+--+--+--+--+--+--+--+--+--+--+--+--+
        s_4_incr_y_ | 0| *|-1| *| 0| *| 1| *| 0| *|-1| *| 0|
                    +--+--+--+--+--+--+--+--+--+--+--+--+--+
                    +--+--+--+--+--+--+--+--+--+--+--+--+--+
       offset3X3_4_ |-1| *|-w| *| 1| *| w| *|-1| *|-w| *| 1| w == image width
                    +--+--+--+--+--+--+--+--+--+--+--+--+--+
nghIdx for figure 1         0     2     4     6
nghIdx for figure 2               0     2     4     6
@endverbatim
  
- Contour direction <b>currDir</b> determines the index to enter
  each table: <b>2</b> (East) and <b>4</b> (South) on figures
  1 and 2, respectively. 
- <b>nghIdx</b> is the relative index of the 4 consecutive
  pertinent values (excepting those marked '<b>*</b>') available
  from this entry.
- In table qgar::Component::s_4_incr_x_
  (resp. qgar::Component::s_4_incr_y_), these values provide the X
  (resp. Y) increments to add to the X (resp. Y) coordinate of
  <b>c</b> in order to get the X (resp. Y) coordinates of the 4
  neighbors of <b>c</b> in the appropriate order, as explained in
  <a href="#sec42">section 4.2</a>.
  In fact, odd-indexed values have no use and just exist to preserve
  the correspondance between the current direction code and the
  entry index.
- The new contour point is found at index <b>newIdx</b>,
  computed as <b>currDir + nghIdx</b>.
- In the same way, table qgar::Component::offset3X3_4_ provides
  the offsets to add to the <i>pointer</i> to <b>c</b> in order
  to get the <i>pointers</i> to the 4 neighbors.


<a name="sec44"></a><b>4.4 &nbsp;THE NEW CONTOUR DIRECTION</b>
  
@verbatim
      entry for figure 1 --+     +-- entry for figure 2
                           |     |
                           V     V
           currDir   N     E     S     W
                     0  1  2  3  4  5  6  7  8  9 10 11 12 
                   +--+--+--+--+--+--+--+--+--+--+--+--+--+
       s_4_incr_x_ |-1| *| 0| *| 1| *| 0| *|-1| *| 0| *| 1|
                   +--+--+--+--+--+--+--+--+--+--+--+--+--+
                                       | newIdx
                                       V
                   +--+--+--+--+--+--+--+--+--+--+--+--+--+
      s_4_new_dir_ | W| *| N| *| E| *| S| *| W| *| N| *| E|
                   +--+--+--+--+--+--+--+--+--+--+--+--+--+
@endverbatim
  
- Once the new contour point is found, its index <b>newIdx</b>
  determines the entry in table qgar::Component::s_4_new_dir_
  to get the new contour direction.

For example, on figure 1, when the new contour point is <b>n4</b>:
<b>nghIdx == 4</b>, <b>newIdx == currDir + nghIdx == 2 + 4</b>,
and <b>s_4_new_dir_[6]</b> gives South as new direction.
On figure 2, when the new contour point is <b>n4</b>:
<b>nghIdx == 2</b>, <b>newIdx == currDir + nghIdx == 4 + 2</b>,
and the new contour direction is South again.


<a name="sec45"></a><b>4.5 &nbsp;THE PERIMETER</b>
  
@verbatim
nghIdx          0                 2                 4                 6
increment      +0                +1                +2                +3

          +---+-|-+---+     +---+-|-+---+     +---+-|-+---+     +---X-|-+---+
          | * | n0| * |     | * | n0| * |     | * | n0| * |     | * | n0| * |
          +---+-|-+---X     +---+-|-+---+     +---+-|-+---+     +---+-|-+---+
          | n6| c---n2|     | n6| c | n2|     | n6--c | n2|     | n6| c | n2|
          +---+---O---+     +---+-|-O---+     X---+---O---+     +---+---O---+
          | * | n4| * |     | * | n4| * |     | * | n4| * |     | * | n4| * |
          +---+---+---+     +---+---X---+     +---+---+---+     +---+---+---+
                |                 |                 |                 |      
                V                 V                 V                 V      
                               contour direction (South)

                            SEARCH LIST: n2 - n4 - n6 - n0
                                 nghIdx: 0    2    4    6
@endverbatim

- A pixel is supposed to be a <i>unit-width-square</i>.
- The current so-called <i>perimeter in pixels</i> is the length
  between the top left corner of the starting pixel and the top right
  (relatively to the current contour direction)
  corner of the current pixel.
- Once the new contour point is found, the value to add to the current
  perimeter is equal to <b>nghIdx / 2</b>.

The figure above shows the case of figure 2, when the contour direction
is South.
<b>O</b> represents the top right corner of the current contour pixel,
and <b>X</b> represents the top right corner of the new contour pixel.



  */
  // =================================================================
  //@{

  /**
   * @brief Table of X coordinates increments.
   *
   * See
   * <a href="#sec41">Contour following of 4-connected components</a>
   * for full details.
   *
   * @warning This is a <i>static</i> data member.
   */
  static const int s_4_incr_x_[13];

  /**
   * @brief Table of Y coordinates increments.
   *
   * See
   * <a href="#sec41">Contour following of 4-connected components</a>
   * for full details.
   *
   * @warning This is a <i>static</i> data member.
   */
  static const int s_4_incr_y_[13];

  /**
   * @brief Table of new contour directions.
   *
   * See
   * <a href="#sec41">Contour following of 4-connected components</a>
   * for full details.
   *
   * @warning This is a <i>static</i> data member.
   */
  static const int s_4_new_dir_[13];

  //@}


  // =================================================================
  /** @name Contour following of 8-connected components

<a name="sec81"></a><b>8.1 &nbsp;DIRECTION CODING</b>
  
@verbatim
N  NE  E  SE  S  SW  W  NW
0  1   2  3   4  5   6  7
@endverbatim
  
Directions are coded clockwise, from <b>N</b>(orth) to
<b>N</b>(orth-)<b>W</b>(est): see enum type qgar::QGEdirection.


<a name="sec82"></a><b>8.2 &nbsp;SEARCHING FOR THE NEW CONTOUR POINT</b>
  
@verbatim
      +---+---+---+                     +---+---+---+           +---+---+---+
      | * | n0| n1|                     | w | w | b |           | w | w | w |
      +---+---+---+   contour           +---+---+---+           +---+---+---+
  (1) --n6--c | n2|-> direction    (1a) --b---b | b |->    (1b) --b---b | w |->
      +---+---+---+   (East)            +---+---+---+           +---+---+---+
      | * | n4| n3|                     | b | b | b |           | b | w | w |
      +---+---+---+                     +---+---+---+           +---+---+---+

      SEARCH LIST:
n0 - n2 - n1 - n4 - n3 - n6


      \---+---+---+                     \---+---+---+           \---+---+---+
      | n7| * | n1|                     | b | w | b |           | b | w | w |
      +---\---+---+                     +---\---+---+           +---\---+---+
  (2) | * | c | n2|                (2a) | w | b | b |      (2b) | b | b | w |
      +---+---+---+                     +---+---+---+           +---+---+---+
      | n5| n4| n3|                     | w | b | b |           | w | w | w |
      +---+---+---+                     +---+---+---+           +---+---+---+
                   \ contour                         \                       \
        	    direction            
                   (South-East)         b: black pixel          b: black pixel
                                        w: white pixel          w: white pixel
      SEARCH LIST:
n2 - n1 - n4 - n3 - n5 - n7
@endverbatim

- <b>currDir</b> is the so-called <i>contour direction</i>,
  that is to say the direction of the contour part being
  constructed, whose <b>c</b> is the current end.
- The outside of the component is always on the left side when
  moving along the contour direction.
- The new contour point is searched clockwise among the 8 neighbors
  of <b>c</b>, starting from the point left-perpendicular to
  <b>currDir</b>:
  <b>n0</b> and <b>n1</b> on figures 1 and 2, respectively.

Thus, the search list <i>a priori</i> is
<b>n0 - n1 - n2 - n3 - n4 - n5 - n6 - n7</b> for figure 1, and
<b>n1 - n2 - n3 - n4 - n5 - n6 - n7 - n0</b> for figure 2.

However, a 4-connected neighbor must be examined <i>before</i> the
neighbor of previous diagonal direction, in order to get
<i>all</i> the contour points. Otherwise, on figures 1a and 2a,
the new contour point would be <b>n1</b>, and point <b>n2</b>
would be missed. Thus, the search list becomes
<b>n0 - n2 - n1 - n4 - n3 - n6 - n5 - n7</b> for figure 1, and
<b>n2 - n1 - n4 - n3 - n6 - n5 - n0 - n7</b> for figure 2.

Moreover, by construction, <b>n5</b> and <b>n7</b>
on figure 1 and <b>n6</b> and <b>n0</b> on figure 2
(6th and 8th neighbors of the initial lists)
cannot be contour points. Thus, the final search list is
<b>n0 - n2 - n1 - n4 - n3 - n6</b> for figure 1, and
<b>n2 - n1 - n4 - n3 - n5 - n7</b> for figure 2.


<a name="sec83"></a><b>8.3 &nbsp;COORDINATES OF NEIGHBORS</b>

@verbatim
                       <------ nghIdx ----->
                       0   1   2   3   4   5
                     +---+---+---+---+---+---+
              / N  0 |-1 | 0 |-1 | 1 | 1 | 0 |
              |      +---+---+---+---+---+---+
              | NE 1 | 0 |-1 | 1 | 1 | 1 |-1 |
              |      +---+---+---+---+---+---+
              | E  2 | 0 | 1 | 1 | 0 | 1 |-1 | <- figure 1
              |      +---+---+---+---+---+---+
              | SE 3 | 1 | 1 | 0 | 1 |-1 |-1 | <- figure 2
     currDir <       +---+---+---+---+---+---+
              | S  4 | 1 | 0 | 1 |-1 |-1 | 0 |
              |      +---+---+---+---+---+---+
              | SW 5 | 0 | 1 |-1 |-1 |-1 | 1 |
              |      +---+---+---+---+---+---+
              | W  6 | 0 |-1 |-1 | 0 |-1 | 1 |
              |      +---+---+---+---+---+---+
              \ NW 7 |-1 |-1 | 0 |-1 | 1 | 1 |
                     +---+---+---+---+---+---+
                            s_8_incr_x_


                       <------ nghIdx ----->
                       0   1   2   3   4   5
                     +---+---+---+---+---+---+
              / N  0 | 0 |-1 |-1 | 0 |-1 | 1 |
              |      +---+---+---+---+---+---+
              | NE 1 |-1 |-1 | 0 |-1 | 1 | 1 |
              |      +---+---+---+---+---+---+
              | E  2 |-1 | 0 |-1 | 1 | 1 | 0 | <- figure 1
              |      +---+---+---+---+---+---+
              | SE 3 | 0 |-1 | 1 | 1 | 1 |-1 | <- figure 2
     currDir <       +---+---+---+---+---+---+
              | S  4 | 0 | 1 | 1 | 0 | 1 |-1 |
              |      +---+---+---+---+---+---+
              | SW 5 | 1 | 1 | 0 | 1 |-1 |-1 |
              |      +---+---+---+---+---+---+
              | W  6 | 1 | 0 | 1 |-1 |-1 | 0 |
              |      +---+---+---+---+---+---+
              \ NW 7 | 0 | 1 |-1 |-1 |-1 | 1 |
                     +---+---+---+---+---+---+
                            s_8_incr_y_
@endverbatim
  
- Contour direction <b>currDir</b> determines the row to be used in
  each table: rows <b>2</b> (East) and <b>3</b> (South-East)
  on figures 1 and 2, respectively.
- The successive values in a row of table qgar::Component::s_8_incr_x_
  (resp. qgar::Component::s_8_incr_y_) provide the X (resp. Y)
  increments to add to the X (resp. Y) coordinate of <b>c</b>
  in order to get the X (resp. Y) coordinates of the 6 possible
  new contour points in the appropriate order,
  as explained in <a href="#sec82">section 8.2</a>.
- In the same way, table qgar::Component::offset3X3_8_ provides
  the offsets to add to the <i>pointer</i> to <b>c</b> in order
  to get the <i>pointers</i> to the 6 neighbors.
- <b>nghIdx</b> be the column index corresponding to the new
  contour point.

  
<a name="sec84"></a><b>8.4 &nbsp;THE NEW CONTOUR DIRECTION</b>

@verbatim
                       <------ nghIdx ----->
                       0   1   2   3   4   5
                     +---+---+---+---+---+---+
              / N  0 | W | N |NW | E |NE | S |
              |      +---+---+---+---+---+---+
              | NE 1 | N |NW | E |NE |SE |SW |
              |      +---+---+---+---+---+---+
              | E  2 | N | E |NE | S |SE | W | <- figure 1
              |      +---+---+---+---+---+---+
              | SE 3 | E |NE | S |SE |SW |NW | <- figure 2
     currDir <       +---+---+---+---+---+---+
              | S  4 | E | S |SE | W |SW | N |
              |      +---+---+---+---+---+---+
              | SW 5 | S |SE | W |SW |NW |NE |
              |      +---+---+---+---+---+---+
              | W  6 | S | W |SW | N |NW | E |
              |      +---+---+---+---+---+---+
              \ NW 7 | W |SW | N |NW |NE |SE |
                     +---+---+---+---+---+---+
                            s_8_new_dir_
@endverbatim

- Once the new contour point is found, table
  qgar::Component::s_8_new_dir_ provides the new contour direction.
- <b>currDir</b> determines the row to be used: rows <b>2</b>
  (East) and <b>3</b> (South-East) on figures 1 and 2, respectively.
- Index <b>nghIdx</b> determines the column to be used.

For example, on figure 1, if the new contour point is <b>n3</b>,
<b>currDir == 2</b>, <b>nghIdx == 4</b>, and the new contour
direction is provided by <b>s_8_new_dir_[2][4]</b>: South-East.
On figure 2, if the new contour point is <b>n3</b>,
<b>currDir == 3</b>, <b>nghIdx == 3</b>, and the new contour
direction is provided by <b>s_8_new_dir_[3][3]</b>: South-East,
again.


<a name="sec85"></a><b>8.5 &nbsp;THE PERIMETER</b>

@verbatim
nghIdx          0                1                2
          \---+---+---+    \---+---X---+    \---+---+---+
          | n7|   |   |    | n7|   | n1|    | n7|   |   |
          +---\---O---X    +---\---O---+    +---\---O---+
          |   | c---n2|    |   | c |   |    |   | c |   |
          +---+---+---+    +---+---+---+    +---+-|-+---+
          |   |   |   |    |   |   |   |    |   | n4|   |
          +---+---+---+    +---+---+---+    +---+---X---+
increment       +1     \         +1     \         +2     \ currDir (South-East)


nghIdx          3                4                5
          \---+---+---+    \---+---+---+    \---+---+---+
          | n7|   |   |    | n7|   |   |    | n7|   |   |
          +---\---O---+    +---\---O---+    X---\---O---+
          |   | c |   |    |   | c |   |    |   | c |   |
          +---+---\---X    +---/---+---+    +---+---+---+
          |   |   | n3|    | n5|   |   |    |   |   |   |
          +---+---+---+    +---X---+---+    +---+---+---+
increment       +2     \         +3     \         +4     \ currDir (South-East)


SEARCH LIST (figure 2): n2 - n1 - n4 - n3 - n5 - n7
                nghIdx: 0    1    2    3    4    5
@endverbatim

- A pixel is supposed to be a <i>unit-width-square</i>.
- The current so-called <i>perimeter in pixels</i> is the length
  between the top left corner of the starting pixel and the top right
  (relatively to the current contour direction)
  corner of the current pixel.

The figure above shows the values to add to the current perimeter
for each possible neighbor of current contour point <b>c</b>
when the contour direction is South-East (case of figure 2):
<b>O</b> represents the top right corner of the current
contour pixel, and <b>X</b> represents the top right corner
of the new contour pixel.

@verbatim
                       <------ nghIdx ----->
                       0   1   2   3   4   5
                     +---+---+---+---+---+---+
              / N  0 | 0 | 1 | 1 | 2 | 2 | 3 |
              |      +---+---+---+---+---+---+
              | NE 1 | 1 | 1 | 2 | 2 | 3 | 4 |
              |      +---+---+---+---+---+---+
              | E  2 | 0 | 1 | 1 | 2 | 2 | 3 | <- figure 1
              |      +---+---+---+---+---+---+
              | SE 3 | 1 | 1 | 2 | 2 | 3 | 4 | <- figure 2
     currDir <       +---+---+---+---+---+---+
              | S  4 | 0 | 1 | 1 | 2 | 2 | 3 |
              |      +---+---+---+---+---+---+
              | SW 5 | 1 | 1 | 2 | 2 | 3 | 4 |
              |      +---+---+---+---+---+---+
              | W  6 | 0 | 1 | 1 | 2 | 2 | 3 |
              |      +---+---+---+---+---+---+
              \ NW 7 | 1 | 1 | 2 | 2 | 3 | 4 |
                     +---+---+---+---+---+---+
                        s_8_incr_perimeter_
@endverbatim

- Table qgar::Component::s_8_incr_perimeter gives the value
  to increment the current perimeter in pixels.
- Contour direction <b>currDir</b> determines the row to be used:
  rows <b>2</b> (East) and <b>3</b> (South-East) on figures 1 and 2,
  respectively.
- <b>nghIdx</b> determines the column to be used.

For example, on figure 1, if the new contour point is <b>n3</b>,
<b>currDir == 2</b>, <b>nghIdx == 4</b>, and the perimeter increment
is provided by <b><b>s_8_incr_perimeter_[2][4]</b>: <b>2</b>.
On figure 2, if the new contour point is <b>n3</b>, 
<b>currDir == 3</b>, <b>nghIdx == 3</b>, and the perimeter increment
is provided by <b><b>s_8_incr_perimeter_[3][3]</b>: <b>2</b>, again.

  */
  // =================================================================
  //@{

  /**
   * @brief Number of pertinent neighbors in a \f$3\times 3\f$
   * neighborhood when working with 8-connectivity.
   *
   * It is used to access 2-dimensional tables
   * qgar::Component::s_8_incr_x_,
   * qgar::Component::s_8_incr_y_,
   * qgar::Component::s_8_incr_perimeter_,
   * qgar::Component::s_8_new_dir_,
   * and
   * qgar::Component::offset3X3_8_,
   * which are implemented as 1-dimensional tables
   * for more efficiency!
   */
  static const int s_8_ngh_cnt_;

  /**
   * @brief Table of X coordinates increments.
   *
   * See
   * <a href="#sec81">Contour following of 8-connected components</a>
   * for full details.
   *
   * @warning
   * This is a <i>static</i> data member.
   * @warning
   * For more efficiency, the 2-dimensional table is implemented
   * as a 1-dimensional array!
   */
  static const int s_8_incr_x_[48];

  /**
   * @brief Table of Y coordinates increments.
   *
   * See
   * <a href="#sec81">Contour following of 8-connected components</a>
   * for full details.
   *
   * @warning
   * This is a <i>static</i> data member.
   * @warning
   * For more efficiency, the 2-dimensional table is implemented
   * as a 1-dimensional array!
   */
  static const int s_8_incr_y_[48];

  /**
   * @brief Table of perimeter increments.
   *
   * See
   * <a href="#sec81">Contour following of 8-connected components</a>
   * for full details.
   *
   * @warning
   * This is a <i>static</i> data member.
   * @warning
   * For more efficiency, the 2-dimensional table is implemented
   * as a 1-dimensional array!
   */
  static const int s_8_incr_perimeter_[48];

  /**
   * @brief Table of new contour directions.
   *
   * See
   * <a href="#sec81">Contour following of 8-connected components</a>
   * for full details.
   *
   * @warning
   * This is a <i>static</i> data member.
   * @warning
   * For more efficiency, the 2-dimensional table is implemented
   * as a 1-dimensional array!
   */
  static const int s_8_new_dir_[48];

  //@}


  /** @name Auxiliary functions */
  //        ===================
  //@{

  /**
   * @brief Compute the contour points.
   *
   * 8-connectivity is used when the component is black,
   * 4-connectivity is used when the component is white.
   *
   * See sections <a href="#hd2>sections 2, 3 & 4</a>
   * of the class header for detailed information about contours.
   */
  void PRIVATEcomputeContour();

  /**
   * @brief Compute the contour points,
   * using 8-connectivity.
   *
   * See sections <a href="#hd2">sections 2, 3 & 4</a>
   * of the class header for detailed information about contours.
   */
  void PRIVATEcontour8();

  /**
   * @brief Compute the contour points,
   * using 4-connectivity.
   *
   * See sections <a href="#hd2">sections 2, 3 & 4</a>
   * of the class header for detailed information about contours.
   */
  void PRIVATEcontour4();

  /**
   * @brief Compute the MAER (Minimum-Area Encasing Rectangle).
   */
  void
  PRIVATEcomputeMaer();

  //@}

// -------------------------------------------------------------------
}; // class Component




// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// I N L I N E    F U N C T I O N S    I M P L E M E N T A T I O N
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII


// =====
// LABEL
// =====

// GET COMPONENT LABEL

inline Component::label_type
Component::label() const
{
  return label_;
}

// GET COMPRISING COMPONENT LABEL

inline Component::label_type
Component::inLabel() const
{
  return inLabel_;
}


// ======
// COLOR
// ======

// GET COLOR.

inline QGEbw
Component::color() const
{
  return color_;
}

// ===========
// COORDINATES
// ===========

// GET X COORDINATE OF THE TOP LEFT PIXEL

inline int
Component::xTopLeftPix() const
{
  return xTopLeftPix_;
}

// GET Y COORDINATE OF THE TOP LEFT PIXEL

inline int
Component::yTopLeftPix() const
{
  return yTopLeftPix_;
}


// ====
// AREA
// ====

// GET COMPONENT AREA.

inline int
Component::areaPx() const
{
  return areaPx_;
}


// =========
// PERIMETER
// =========


// GET THE PERIMETER IN POINTS

inline int
Component::perimeterPt()
{
  return (int) accessContour().size();
}


// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// END OF INLINE FUNCTIONS IMPLEMENTATION
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII


} // namespace qgar 


#endif /* __COMPONENT_H_INCLUDED__ */
