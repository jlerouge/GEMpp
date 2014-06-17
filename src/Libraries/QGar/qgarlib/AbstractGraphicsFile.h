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


#ifndef __ABSTRACTGRAPHICSFILE_H_INCLUDED__
#define __ABSTRACTGRAPHICSFILE_H_INCLUDED__


/**
 * @file AbstractGraphicsFile.h
 *
 * @brief Header file of class qgar::AbstractGraphicsFile.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gerald Masini">Gérald Masini</a>
 * @date   June, 27  2003  16:21
 * @since  Qgar 2.1
 */

// For RCS/CVS use: Do not delete
/* $Id: AbstractGraphicsFile.h,v 1.16 2006/06/23 15:22:12 gerald Exp $ */



// QGAR
#include "AbstractFile.h"
#include "ConnectedComponents.h"
#include "primitives.h"
namespace qgar
{
  // Avoid #include's when not necessary
  template <class T> class AbstractGenPointChain;
  template <class T> class GenTreeNode;
  class BoundingBox;
}



namespace qgar
{


/**
 * @ingroup IO_FILE
 *
 * @class AbstractGraphicsFile AbstractGraphicsFile.h "qgarlib/AbstractGraphicsFile.h"
 *
 * @brief Basic function to read/write graphical and geometrical
 * primitives in graphics files like Tgif files, DXF files, etc.
 *
 * <b>Pure virtual functions</b>
 * <ul>
 *
 * <li>To write points:
 * <ul>
 * <li>qgar::AbstractGraphicsFile::write(int, int, int, QGEcolor)</li>
 * <li>qgar::AbstractGraphicsFile::write(float, float, int, QGEcolor)</li>
 * <li>qgar::AbstractGraphicsFile::write(double, double, int, QGEcolor)</li>
 * </ul>
 * </li>
 *
 * <li>To write chains of points:
 * <ul>
 * <li>qgar::AbstractGraphicsFile::write(AbstractGenPointChain<int>&, int, QGEcolor)</li>
 * <li>qgar::AbstractGraphicsFile::write(AbstractGenPointChain<float>&, int, QGEcolor)</li>
 * <li>qgar::AbstractGraphicsFile::write(AbstractGenPointChain<double>&, int, QGEcolor)</li>
 * </ul>
 * </li>
 *
 * <li>To write line segments:
 * <ul>
 * <li>qgar::AbstractGraphicsFile::write(int, int, int, int, int, QGEcolor, QGEoutline)</li>
 * <li>qgar::AbstractGraphicsFile::write(float, float, float, float, int, QGEcolor, QGEoutline)</li>
 * <li>qgar::AbstractGraphicsFile::write(double, double, double, double, int, QGEcolor, QGEoutline)</li>
 * </ul>
 * </li>
 *
 * <li>To write circles:
 * <ul>
 * <li>qgar::AbstractGraphicsFile::write(int, int, double, int, QGEcolor, QGEoutline)</li>
 * <li>qgar::AbstractGraphicsFile::write(float, float, double, int, QGEcolor, QGEoutline)</li>
 * <li>qgar::AbstractGraphicsFile::write(double, double, double, int, QGEcolor, QGEoutline)</li>
 * </ul>
 * </li>
 *
 * <li>To write arcs of circle:
 * <ul>
 * <li>qgar::AbstractGraphicsFile::write(int, int, int, int, int, int, int, QGEcolor, QGEoutline)</li>
 * <li>qgar::AbstractGraphicsFile::write(float, float, float, float, float, float, int, QGEcolor, QGEoutline)</li>
 * <li>qgar::AbstractGraphicsFile::write(double, double, double, double, double, double, int, QGEcolor, QGEoutline)</li>
 * </ul>
 * </li>
 *
 * <li>To write polylines:
 * <ul>
 * <li>qgar::AbstractGraphicsFile::write(const GenPolyline<int>&, int, QGEcolor, QGEoutline)</li>
 * <li>qgar::AbstractGraphicsFile::write(const GenPolyline<float>&, int, QGEcolor, QGEoutline)</li>
 * <li>qgar::AbstractGraphicsFile::write(const GenPolyline<double>&, int, QGEcolor, QGEoutline)</li>
 * </ul>
 * </li>
 *
 * <li>To write bounding boxes:
 * <ul>
 * <li>qgar::AbstractGraphicsFile::write(const BoundingBox&, int, QGEcolor, QGEoutline)</li>
 * </ul>
 * </li>
 *
 * <li>To write (connected) components:
 * <ul>
 * <li>qgar::AbstractGraphicsFile::write(const ConnectedComponents::node_type* const, int, QGEcolor, QGEoutline)</li>
 * </ul>
 * </li>
 *
 * </ul>
 *
 * @warning
 * <ul>
 * <li>This is an abstract class: It cannot be instantiated.</li>
 * <li><b>The class is provided with both pure virtual and concrete
 * definitions of function qgar::AbstractGraphicsFile::write.
 * To get the concrete functions into the scope of a derived class
 * which implements the pure virtual functions, a <i>using</i>
 * declaration is required in the derived class.</b>
 * See class qgar::DxfFile for an example.</li>
 * </ul>
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gerald Masini">Gerald Masini</a>
 * @date   June, 27  2003  16:21
 * @since  Qgar 2.1
 */
class AbstractGraphicsFile

  : public AbstractFile

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  /** @name Constructors */
  //        ============
  //@{

  /**
   * @brief Initialize with given name.
   *
   * @warning A file must be opened to be used.
   */
  AbstractGraphicsFile(const char* aFileName);

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  virtual ~AbstractGraphicsFile();

  //@}


  /** @name Output points */
  //        =============
  //@{

  /**
   * @brief Output a point with coordinates of type <b>int</b>.
   *
   * @param aPt         a point
   * @param aThickness  thickness  (default <b>3</b>)
   * @param aColor      color      (default qgar::QGE_COLOR_DEFAULT)
   */
  inline void write(const GenPoint<int>& aPt,
		    int aThickness  = 3,
		    QGEcolor aColor = QGE_COLOR_DEFAULT);

  /**
   * @brief Output a point with coordinates of type <b>int</b>.
   *
   * @param aX          X coordinate of the point
   * @param aY          Y coordinate of the point
   * @param aThickness  thickness  (default <b>3</b>)
   * @param aColor      color      (default qgar::QGE_COLOR_DEFAULT)
   */
  virtual void write(int aX,
		     int aY,
		     int aThickness  = 3,
		     QGEcolor aColor = QGE_COLOR_DEFAULT)
    = 0;

  /**
   * @brief Output a point with coordinates of type <b>float</b>.
   *
   * @param aPt         a point
   * @param aThickness  thickness (default <b>3</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   */
  inline void write(const GenPoint<float>& aPt,
		    int aThickness  = 3,
		    QGEcolor aColor = QGE_COLOR_DEFAULT);

  /**
   * @brief Output a point with coordinates of type <b>float</b>.
   *
   * @param aX          X coordinate of the point
   * @param aY          Y coordinate of the point
   * @param aThickness  thickness  (default <b>3</b>)
   * @param aColor      color      (default qgar::QGE_COLOR_DEFAULT)
   */
  virtual void write(float aX,
		     float aY,
		     int aThickness  = 3,
		     QGEcolor aColor = QGE_COLOR_DEFAULT)
    = 0;

  /**
   * @brief Output a point with coordinates of type <b>double</b>.
   *
   * @param aPt         a point
   * @param aThickness  thickness (default <b>3</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   */
  inline void write(const GenPoint<double>& aPt,
		    int aThickness  = 3,
		    QGEcolor aColor = QGE_COLOR_DEFAULT);

  /**
   * @brief Output a point with coordinates of type <b>double</b>.
   *
   * @param aX          X coordinate of the point
   * @param aY          Y coordinate of the point
   * @param aThickness  thickness  (default <b>3</b>)
   * @param aColor      color      (default qgar::QGE_COLOR_DEFAULT)
   */
  virtual void write(double aX,
		     double aY,
		     int aThickness  = 3,
		     QGEcolor aColor = QGE_COLOR_DEFAULT)
    = 0;

  //@}


  /** @name Output chains of points */
  //        =======================
  //@{

  /**
   * @brief Output a chain of points with coordinates of type <b>int</b>.
   *
   * @param aChain      a chain
   * @param aThickness  thickness (default <b>3</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   *
   * @todo
   *   Parameter <b>aChain</b> cannot be declared <b>const</b> because
   *   functions qgar::AbstractGenPointChain::setToBegin
   *   and qgar::AbstractGenPointChain::moveNext are not declared <b>const</b>.
   *   In particular, their implementation in class qgar::GenLinkedChain modify
   *   data member 
   *   qgar::GenLinkedChain::_iter, that should be declared as <b>mutable</b>.
   */
  virtual void write(AbstractGenPointChain<int>& aChain,
		     int aThickness  = 3,
		     QGEcolor aColor = QGE_COLOR_DEFAULT)
    = 0;

  /**
   * @brief Output a chain of points with coordinates of type <b>float</b>.
   *
   * @param aChain      a chain
   * @param aThickness  thickness (default <b>3</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   *
   * @todo
   *   Parameter <b>aChain</b> cannot be declared <b>const</b> because
   *   functions qgar::AbstractGenPointChain::setToBegin
   *   and qgar::AbstractGenPointChain::moveNext are not declared <b>const</b>.
   *   In particular, their implementation in class qgar::GenLinkedChain modify
   *   data member 
   *   qgar::GenLinkedChain::_iter, that should be declared as <b>mutable</b>.
   */
  virtual void write(AbstractGenPointChain<float>& aChain,
		     int aThickness  = 3,
		     QGEcolor aColor = QGE_COLOR_DEFAULT)
    = 0;

  /**
   * @brief Output a chain of points with coordinates of type <b>double</b>.
   *
   * @param aChain      a chain
   * @param aThickness  thickness (default <b>3</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   *
   * @todo
   *   Parameter <b>aChain</b> cannot be declared <b>const</b> because
   *   functions qgar::AbstractGenPointChain::setToBegin
   *   and qgar::AbstractGenPointChain::moveNext are not declared <b>const</b>.
   *   In particular, their implementation in class qgar::GenLinkedChain modify
   *   data member 
   *   qgar::GenLinkedChain::_iter, that should be declared as <b>mutable</b>.
   */
  virtual void write(AbstractGenPointChain<double>& aChain,
		     int aThickness  = 3,
		     QGEcolor aColor = QGE_COLOR_DEFAULT)
    = 0;

  //@}


  /** @name Output line segments */
  //        ====================
  //@{

  /**
   * @brief Output a segment with coordinates of type <b>int</b>.
   *
   * @param aSeg        a segment
   * @param aThickness  thickness (default <b>1</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  inline void write(const GenSegment<int>& aSeg,
		    int        aThickness = 1,
		    QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		    QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  /**
   * @brief Output a segment with coordinates of type <b>int</b>.
   *
   * @param aXSource    X coordinate of the source point of the segment
   * @param aYSource    Y coordinate of the source point of the segment
   * @param aXTarget    X coordinate of the target point of the segment
   * @param aYTarget    Y coordinate of the target point of the segment
   * @param aThickness  thickness (default <b>1</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  virtual void write(int aXSource,
		     int aYSource,
		     int aXTarget,
		     int aYTarget,
		     int        aThickness = 1,
		     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT)
    = 0;

  /**
   * @brief Output a segment with coordinates of type <b>float</b>.
   *
   * @param aSeg        a segment
   * @param aThickness  thickness (default <b>1</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  inline void write(const GenSegment<float>& aSeg,
		    int        aThickness = 1,
		    QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		    QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  /**
   * @brief Output a segment with coordinates of type <b>float</b>.
   *
   * @param aXSource    X coordinate of the source point of the segment
   * @param aYSource    Y coordinate of the source point of the segment
   * @param aXTarget    X coordinate of the target point of the segment
   * @param aYTarget    Y coordinate of the target point of the segment
   * @param aThickness  thickness (default <b>1</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  virtual void write(float aXSource,
		     float aYSource,
		     float aXTarget,
		     float aYTarget,
		     int        aThickness = 1,
		     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT)
    = 0;

  /**
   * @brief Output a segment with coordinates of type <b>double</b>.
   *
   * @param aSeg        a segment
   * @param aThickness  thickness (default <b>1</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  inline void write(const GenSegment<double>& aSeg,
		    int        aThickness = 1,
		    QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		    QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  /**
   * @brief Output a segment with coordinates of type <b>double</b>.
   *
   * @param aXSource    X coordinate of the source point of the segment
   * @param aYSource    Y coordinate of the source point of the segment
   * @param aXTarget    X coordinate of the target point of the segment
   * @param aYTarget    Y coordinate of the target point of the segment
   * @param aThickness  thickness (default <b>1</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  virtual void write(double aXSource,
		     double aYSource,
		     double aXTarget,
		     double aYTarget,
		     int        aThickness = 1,
		     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT)
    = 0;

  /**
   * @brief Output a Qgar segment with coordinates of type <b>int</b>.
   *
   * @param aQSeg       a Qgar segment
   * @param aThickness  thickness to be output (default <b>-1</b>, i.e. current)
   * @param aColor      color to be output     (default qgar::QGE_COLOR_NONE, i.e. current)
   * @param anOutline   outline to be output   (default qgar::QGE_OUTLINE_NONE, i.e. current)
   */
  void write(const GenQgarSegment<int>& aQSeg,
	     int        aThickness = -1,
	     QGEcolor   aColor     = QGE_COLOR_NONE,
	     QGEoutline anOutline  = QGE_OUTLINE_NONE);

  /**
   * @brief Output a Qgar segment with coordinates of type <b>float</b>.
   *
   * @param aQSeg       a Qgar segment
   * @param aThickness  thickness to be output (default <b>-1</b>, i.e. current)
   * @param aColor      color to be output     (default qgar::QGE_COLOR_NONE, i.e. current)
   * @param anOutline   outline to be output   (default qgar::QGE_OUTLINE_NONE, i.e. current)
   */
  void write(const GenQgarSegment<float>& aQSeg,
	     int        aThickness = -1,
	     QGEcolor   aColor     = QGE_COLOR_NONE,
	     QGEoutline anOutline  = QGE_OUTLINE_NONE);

  /**
   * @brief Output a Qgar segment with coordinates of type <b>double</b>.
   *
   * @param aQSeg       a Qgar segment
   * @param aThickness  thickness to be output (default <b>-1</b>, i.e. current)
   * @param aColor      color to be output     (default qgar::QGE_COLOR_NONE, i.e. current)
   * @param anOutline   outline to be output   (default qgar::QGE_OUTLINE_NONE, i.e. current)
    */
  void write(const GenQgarSegment<double>& aQSeg,
	     int        aThickness = -1,
	     QGEcolor   aColor     = QGE_COLOR_NONE,
	     QGEoutline anOutline  = QGE_OUTLINE_NONE);

  //@}


  /** @name Output circles */
  //        ==============
  //@{

  /**
   * @brief Output a circle with coordinates of type <b>int</b>.
   *
   * @param aCenter     center
   * @param aRadius     radius
   * @param aThickness  thickness (default <b>1</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  inline void write(const GenPoint<int>& aCenter,
		    double aRadius,
		    int        aThickness = 1,
		    QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		    QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  /**
   * @brief Output a circle with coordinates of type <b>int</b>.
   *
   * @param aXCenter    X coordinate of the center
   * @param aYCenter    Y coordinate of the center
   * @param aRadius     radius
   * @param aThickness  thickness (default <b>1</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  virtual void write(int aXCenter,
		     int aYCenter,
		     double aRadius,
		     int        aThickness = 1,
		     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT)
    = 0;

  /**
   * @brief Output a circle with coordinates of type <b>float</b>.
   *
   * @param aCenter     center
   * @param aRadius     radius
   * @param aThickness  thickness (default <b>1</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  inline void write(const GenPoint<float>& aCenter,
		    double aRadius,
		    int        aThickness = 1,
		    QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		    QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  /**
   * @brief Output a circle with coordinates of type <b>float</b>.
   *
   * @param aXCenter    X coordinate of the center
   * @param aYCenter    Y coordinate of the center
   * @param aRadius     radius
   * @param aThickness  thickness (default <b>1</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  virtual void write(float aXCenter,
		     float aYCenter,
		     double aRadius,
		     int        aThickness = 1,
		     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT)
    = 0;

  /**
   * @brief Output a circle with coordinates of type <b>double</b>.
   *
   * @param aCenter     center
   * @param aRadius     radius
   * @param aThickness  thickness (default <b>1</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  inline void write(const GenPoint<double>& aCenter,
		    double aRadius,
		    int        aThickness = 1,
		    QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		    QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  /**
   * @brief Output a circle with coordinates of type <b>double</b>.
   *
   * @param aXCenter    X coordinate of the center
   * @param aYCenter    Y coordinate of the center
   * @param aRadius     radius
   * @param aThickness  thickness (default <b>1</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  virtual void write(double aXCenter,
		     double aYCenter,
		     double aRadius,
		     int        aThickness = 1,
		     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT)
    = 0;

  //@}


  /** @name Output arcs of circle */
  //        =====================
  //@{

  /**
   * @brief Output an arc with coordinates of type <b>int</b>.
   *
   * @param anArc       an arc
   * @param aThickness  thickness (default <b>1</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  inline void write(const GenArc<int>& anArc,
		    int        aThickness = 1,
		    QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		    QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  /**
   * @brief Output an arc with coordinates of type <b>int</b>.
   *
   * @param aXSource    X coordinate of the source point
   * @param aYSource    Y coordinate of the source point
   * @param aXTarget    X coordinate of the target point
   * @param aYTarget    Y coordinate of the target point
   * @param aXCenter    X coordinate of the center
   * @param aYCenter    Y coordinate of the center
   * @param aThickness  thickness (default <b>1</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  virtual void write(int aXSource,
		     int aYSource,
		     int aXTarget,
		     int aYTarget,
		     int aXCenter,
		     int aYCenter,
		     int        aThickness = 1,
		     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT)
    = 0;

  /**
   * @brief Output an arc with coordinates of type <b>float</b>.
   *
   * @param anArc       an arc
   * @param aThickness  thickness (default <b>1</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  inline void write(const GenArc<float>& anArc,
		    int        aThickness = 1,
		    QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		    QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  /**
   * @brief Output an arc with coordinates of type <b>float</b>.
   *
   * @param aXSource    X coordinate of the source point
   * @param aYSource    Y coordinate of the source point
   * @param aXTarget    X coordinate of the target point
   * @param aYTarget    Y coordinate of the target point
   * @param aXCenter    X coordinate of the center
   * @param aYCenter    Y coordinate of the center
   * @param aThickness  thickness (default <b>1</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  virtual void write(float aXSource,
		     float aYSource,
		     float aXTarget,
		     float aYTarget,
		     float aXCenter,
		     float aYCenter,
		     int        aThickness = 1,
		     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT)
    = 0;

  /**
   * @brief Output an arc with coordinates of type <b>double</b>.
   *
   * @param anArc       an arc
   * @param aThickness  thickness (default <b>1</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  inline void write(const GenArc<double>& anArc,
		    int        aThickness = 1,
		    QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		    QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  /**
   * @brief Output an arc with coordinates of type <b>double</b>.
   *
   * @param aXSource    X coordinate of the source point
   * @param aYSource    Y coordinate of the source point
   * @param aXTarget    X coordinate of the target point
   * @param aYTarget    Y coordinate of the target point
   * @param aXCenter    X coordinate of the center
   * @param aYCenter    Y coordinate of the center
   * @param aThickness  thickness (default <b>1</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  virtual void write(double aXSource,
		     double aYSource,
		     double aXTarget,
		     double aYTarget,
		     double aXCenter,
		     double aYCenter,
		     int        aThickness = 1,
		     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT)
    = 0;

  /**
   * @brief Output a Qgar arc with coordinates of type <b>int</b>.
   *
   * @param aQArc       a Qgar arc
   * @param aThickness  thickness to be output (default <b>-1</b>, i.e. current)
   * @param aColor      color to be output     (default qgar::QGE_COLOR_NONE, i.e. current)
   * @param anOutline   outline to be output   (default qgar::QGE_OUTLINE_NONE, i.e. current)
   */
  void write(const GenQgarArc<int>& aQArc,
	     int        aThickness = -1,
	     QGEcolor   aColor     = QGE_COLOR_NONE,
	     QGEoutline anOutline  = QGE_OUTLINE_NONE);

  /**
   * @brief Output a Qgar arc with coordinates of type <b>float</b>.
   *
   * @param aQArc       a Qgar arc
   * @param aThickness  thickness to be output (default <b>-1</b>, i.e. current)
   * @param aColor      color to be output     (default qgar::QGE_COLOR_NONE, i.e. current)
   * @param anOutline   outline to be output   (default qgar::QGE_OUTLINE_NONE, i.e. current)
   */
  void write(const GenQgarArc<float>& aQArc,
	     int        aThickness = -1,
	     QGEcolor   aColor     = QGE_COLOR_NONE,
	     QGEoutline anOutline  = QGE_OUTLINE_NONE);

  /**
   * @brief Output a Qgar arc with coordinates of type <b>double</b>.
   *
   * @param aQArc       a Qgar arc
   * @param aThickness  thickness to be output (default <b>-1</b>, i.e. current)
   * @param aColor      color to be output     (default qgar::QGE_COLOR_NONE, i.e. current)
   * @param anOutline   outline to be output   (default qgar::QGE_OUTLINE_NONE, i.e. current)
   */
  void write(const GenQgarArc<double>& aQArc,
	     int        aThickness = -1,
	     QGEcolor   aColor     = QGE_COLOR_NONE,
	     QGEoutline anOutline  = QGE_OUTLINE_NONE);

  //@}


  /** @name Output polylines */
  //        ================
  //@{

  /**
   * @brief Output a polyline with coordinates of type <b>int</b>.
   *
   * @param aPoly       a polyline
   * @param aThickness  thickness to be output (default <b>1</b>)
   * @param aColor      color to be output     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline to be output   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  virtual void write(const GenPolyline<int>& aPoly,
		     int        aThickness = 1,
		     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT)
    = 0;

  /**
   * @brief Output a polyline with coordinates of type <b>float</b>.
   *
   * @param aPoly       a polyline
   * @param aThickness  thickness to be output (default <b>1</b>)
   * @param aColor      color to be output     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline to be output   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  virtual void write(const GenPolyline<float>& aPoly,
		     int        aThickness = 1,
		     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT)
    = 0;

  /**
   * @brief Output a polyline with coordinates of type <b>double</b>.
   *
   * @param aPoly       a polyline
   * @param aThickness  thickness to be output (default <b>1</b>)
   * @param aColor      color to be output     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline to be output   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  virtual void write(const GenPolyline<double>& aPoly,
		     int        aThickness = 1,
		     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT)
    = 0;

  /**
   * @brief Output a Qgar polyline with coordinates of type <b>int</b>.
   *
   * @param aQPoly      a Qgar polyline
   * @param aThickness  thickness to be output (default <b>-1</b>, i.e. current)
   * @param aColor      color to be output     (default qgar::QGE_COLOR_NONE, i.e. current)
   * @param anOutline   outline to be output   (default qgar::QGE_OUTLINE_NONE, i.e. current)
   */
  DLL_EXPORT void write(const GenQgarPolyline<int>& aQPoly,
	     int        aThickness = -1,
	     QGEcolor   aColor     = QGE_COLOR_NONE,
	     QGEoutline anOutline  = QGE_OUTLINE_NONE);

  /**
   * @brief Output a Qgar polyline with coordinates of type <b>float</b>.
   *
   * @param aQPoly      a Qgar polyline
   * @param aThickness  thickness to be output (default <b>-1</b>, i.e. current)
   * @param aColor      color to be output     (default qgar::QGE_COLOR_NONE, i.e. current)
   * @param anOutline   outline to be output   (default qgar::QGE_OUTLINE_NONE, i.e. current)
   */
  void write(const GenQgarPolyline<float>& aQPoly,
	     int        aThickness = -1,
	     QGEcolor   aColor     = QGE_COLOR_NONE,
	     QGEoutline anOutline  = QGE_OUTLINE_NONE);

  /**
   * @brief Output a Qgar polyline with coordinates of type <b>double</b>.
   *
   * @param aQPoly      a Qgar polyline
   * @param aThickness  thickness to be output (default <b>-1</b>, i.e. current)
   * @param aColor      color to be output     (default qgar::QGE_COLOR_NONE, i.e. current)
   * @param anOutline   outline to be output   (default qgar::QGE_OUTLINE_NONE, i.e. current)
   */
  void write(const GenQgarPolyline<double>& aQPoly,
	     int        aThickness = -1,
	     QGEcolor   aColor     = QGE_COLOR_NONE,
	     QGEoutline anOutline  = QGE_OUTLINE_NONE);
  //@}


  /** @name Output bounding boxes */
  //        =====================
  //@{

  /**
   * @brief Output a bounding box
   * @param aBox        a bounding box with coordinates of type <b>int</b>.
   *
   * @param aThickness  thickness (default <b>1</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  virtual void write(const BoundingBox& aBox,
		     int        aThickness = 1,
		     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT)
    = 0;

  //@}


  /** @name Output (connected) components */
  //        =============================
  //@{

  /**
   * @brief Output a (connected) component.
   *
   * A component is represented by its contour and the contours
   * of included components.
   *
   * @param aPNode      pointer to the node of the component tree
   *                    including the component
   * @param aThickness  thickness (default <b>1</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  virtual void write(const ConnectedComponents::node_type* const aPNode,
		     int        aThickness = 1,
		     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT)
    = 0;

  //@}


// -------------------------------------------------------------------
}; // class AbstractGraphicsFile




// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// D E F I N I T I O N S   O F   I N L I N E    F U N C T I O N S
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII


// =============
// OUTPUT POINTS
// =============


// OUTPUT A POINT WITH COORDINATES OF TYPE 'int'

inline void
AbstractGraphicsFile::write(const GenPoint<int>& aPt,
			    int aThickness,
			    QGEcolor aColor)
{
  write(aPt.x(), aPt.y(), aThickness, aColor);
}


// OUTPUT A POINT WITH COORDINATES OF TYPE 'float'

inline void
AbstractGraphicsFile::write(const GenPoint<float>& aPt,
			    int aThickness,
			    QGEcolor aColor)
{
  write(aPt.x(), aPt.y(), aThickness, aColor);
}


// OUTPUT A POINT WITH COORDINATES OF TYPE 'double'

inline void
AbstractGraphicsFile::write(const GenPoint<double>& aPt,
			    int aThickness,
			    QGEcolor aColor)
{
  write(aPt.x(), aPt.y(), aThickness, aColor);
}


// ====================
// OUTPUT LINE SEGMENTS
// ====================


// OUTPUT A SEGMENT WITH COORDINATES OF TYPE 'int'

inline void
AbstractGraphicsFile::write(const GenSegment<int>& aSeg,
			    int aThickness,
			    QGEcolor aColor,
			    QGEoutline anOutline)
{
  write(aSeg.xSource(),
	aSeg.ySource(),
	aSeg.xTarget(),
	aSeg.yTarget(),
	aThickness,
	aColor,
	anOutline);
}


// OUTPUT A SEGMENT WITH COORDINATES OF TYPE 'float'

inline void
AbstractGraphicsFile::write(const GenSegment<float>& aSeg,
			    int aThickness,
			    QGEcolor aColor,
			    QGEoutline anOutline)
{
  write(aSeg.xSource(),
	aSeg.ySource(),
	aSeg.xTarget(),
	aSeg.yTarget(),
	aThickness,
	aColor,
	anOutline);
}


// OUTPUT A SEGMENT WITH COORDINATES OF TYPE 'double'

inline void
AbstractGraphicsFile::write(const GenSegment<double>& aSeg,
			    int aThickness,
			    QGEcolor aColor,
			    QGEoutline anOutline)
{
  write(aSeg.xSource(),
	aSeg.ySource(),
	aSeg.xTarget(),
	aSeg.yTarget(),
	aThickness,
	aColor,
	anOutline);
}


// ==============
// OUTPUT CIRCLES
// ==============


// OUTPUT A CIRCLE WITH COORDINATES OF TYPE 'int'

inline void
AbstractGraphicsFile::write(const GenPoint<int>& aCenter,
			    double aRadius,
			    int aThickness,
			    QGEcolor aColor,
			    QGEoutline anOutline)
{
  write(aCenter.x(),
	aCenter.y(),
	aRadius,
	aThickness,
	aColor,
	anOutline);
}


// OUTPUT A CIRCLE WITH COORDINATES OF TYPE 'float'

inline void
AbstractGraphicsFile::write(const GenPoint<float>& aCenter,
			    double aRadius,
			    int aThickness,
			    QGEcolor aColor,
			    QGEoutline anOutline)
{
  write(aCenter.x(),
	aCenter.y(),
	aRadius,
	aThickness,
	aColor,
	anOutline);
}


// OUTPUT A CIRCLE WITH COORDINATES OF TYPE 'double'

inline void
AbstractGraphicsFile::write(const GenPoint<double>& aCenter,
			    double aRadius,
			    int aThickness,
			    QGEcolor aColor,
			    QGEoutline anOutline)
{
  write(aCenter.x(),
	aCenter.y(),
	aRadius,
	aThickness,
	aColor,
	anOutline);
}


// =====================
// OUTPUT ARCS OF CIRCLE
// =====================


// OUTPUT AN ARC WITH COORDINATES OF TYPE 'int'

inline void
AbstractGraphicsFile::write(const GenArc<int>& anArc,
			    int aThickness,
			    QGEcolor aColor,
			    QGEoutline anOutline)
{
  write(anArc.xSource(),
	anArc.ySource(),
	anArc.xTarget(),
	anArc.yTarget(),
	anArc.xCenter(),
	anArc.yCenter(),
	aThickness,
	aColor,
	anOutline);
}


// OUTPUT AN ARC WITH COORDINATES OF TYPE 'float'

inline void
AbstractGraphicsFile::write(const GenArc<float>& anArc,
			    int aThickness,
			    QGEcolor aColor,
			    QGEoutline anOutline)
{
  write(anArc.xSource(),
	anArc.ySource(),
	anArc.xTarget(),
	anArc.yTarget(),
	anArc.xCenter(),
	anArc.yCenter(),
	aThickness,
	aColor,
	anOutline);
}


// OUTPUT AN ARC WITH COORDINATES OF TYPE 'double'

inline void
AbstractGraphicsFile::write(const GenArc<double>& anArc,
			    int aThickness,
			    QGEcolor aColor,
			    QGEoutline anOutline)
{
  write(anArc.xSource(),
	anArc.ySource(),
	anArc.xTarget(),
	anArc.yTarget(),
	anArc.xCenter(),
	anArc.yCenter(),
	aThickness,
	aColor,
	anOutline);
}


// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII


} // namespace qgar


#endif /* __ABSTRACTGRAPHICSFILE_H_INCLUDED__ */
