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


#ifndef __TGIFFILE_H_INCLUDED__
#define __TGIFFILE_H_INCLUDED__


/**
 * @file TgifFile.h
 *
 * @brief Header file of class qgar::TgifFile.
 *
 * Adapted by Gerald Masini from the previous release
 * by Christian Ah-Soon and Karl Tombre. 
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gerald Masini">Gérald Masini</a>
 * @date   Jul, 3  2001  18:21
 * @since  Qgar 1.0
 */



// For RCS/CVS use: Do not delete
/* $Id: TgifFile.h,v 1.24 2006/06/23 15:22:15 gerald Exp $ */



// QGAR
#include "AbstractGraphicsFile.h"
#include "ConnectedComponents.h"
namespace qgar
{
  // Avoid #include's when not necessary
  class BoundingBox;
  class Component;
  class QgarErrorDeveloper;
  template <class T> class AbstractGenPointChain;
  template <class T> class GenArc;
  template <class T> class GenPoint;
  template <class T> class GenPolyline;
  template <class T> class GenSegment;
  template <class T> class GenTreeNode;
}



namespace qgar
{

/**
 * @ingroup IO_FILE
 *
 * @class TgifFile TgifFile.h "qgarlib/TgifFile.h"
 *
 * @brief File including Tgif graphics
 * (designed for Tgif version 3.0, patchlevel 17). 
 *
 * All information (coordinates, thickness, length, etc.) manipulated
 * by Tgif is integer (<b>int</b>).
 *
 * File extension must be <b>.obj</b>.
 * For more information about Tgif, see the
 * <a href="http://bourbon.cs.ucla.edu:8001/tgif/" target="_blank">Tgif home page</a>.
 *
 * When using X Window, your Tgif environment will be consistent with
 * that used in Qgar (especially for colors) if you initialize Tgif variables
 * in the <b>.Xdefaults</b> file of your home directory as follows:
@verbatim
  Tgif*MaxColors: 20
  Tgif*Color0:  #000000
  Tgif*Color1:  #707070
  Tgif*Color2:  #a0a0a0
  Tgif*Color3:  #d0d0d0
  Tgif*Color4:  #ffffff
  Tgif*Color5:  #ff00ff
  Tgif*Color6:  #cc00cc
  Tgif*Color7:  #00ffff
  Tgif*Color8:  #00aaee
  Tgif*Color9:  #0000ff
  Tgif*Color10: #888800
  Tgif*Color11: #008800
  Tgif*Color12: #00ff00
  Tgif*Color13: #ffff00
  Tgif*Color14: #ff8000
  Tgif*Color15: #ff0000
  Tgif*Color16: #ff4080
  Tgif*Color17: #ff8080
  Tgif*Color18: #bb7020
  Tgif*Color19: #a02000
  Tgif*BackGround: white
  Tgif*Foreground: black
  Tgif*SplineTolerance: 13
  Tgif*InitialFont: Helvetica
  Tgif*InitialFontStyle: Roman
  Tgif*InitialFontJust: Center
  Tgif*InitialFontSize: 12
  Tgif*GridSystem: Metric
  Tgif*InitialGrid: -1
  Tgif*InitialSnapOn: false
@endverbatim
 *
 *
 * @warning
 * Functions to read a Tgif file, <i>i.e.</i> to get Qgar objects
 * from Tgif ones, are not available.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gerald Masini">Gerald Masini</a>
 * @date   Jul, 3  2001  18:21
 * @since  Qgar 1.0
 */
class TgifFile

  : public AbstractGraphicsFile

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:


// ___________________________________________________________________
//
// To bring (concrete) functions 'write' inherited from class
// qgar::AbstractGraphicsFile into the scope of the class

  using AbstractGraphicsFile::write;

// ___________________________________________________________________



  /** @name Constructors */
  //        ============
  //@{

  /**
   * @brief Initialize with given name.
   *
   * @warning A file must be opened to be used.
   */
  explicit TgifFile(char* aFileName);

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  virtual ~TgifFile();

  //@}


// -------------------------------------------------------------------
// P U B L I C    M E M B E R S :   O U T P U T
// -------------------------------------------------------------------
public:


  /** @name Output points */
  //        =============
  //@{

  /**
   * @brief Write a point with coordinates of type <b>int</b>.
   *
   * @param aPt         a point
   * @param aThickness  thickness of the drawing (default <b>3</b>)
   * @param aColor      color of the drawing     (default qgar::QGE_COLOR_DEFAULT)
   */
  virtual void write(const GenPoint<int>& aPt,
		     int aThickness  = 3,
		     QGEcolor aColor = QGE_COLOR_DEFAULT);

  /**
   * @brief Write a point with coordinates of type <b>float</b>.
   *
   * @param aPt         a point
   * @param aThickness  thickness of the drawing (default <b>3</b>)
   * @param aColor      color of the drawing     (default qgar::QGE_COLOR_DEFAULT)
   */
  virtual void write(const GenPoint<float>& aPt,
		     int aThickness  = 3,
		     QGEcolor aColor = QGE_COLOR_DEFAULT);

  /**
   * @brief Write a point with coordinates of type <b>double</b>.
   *
   * @param aPt         a point
   * @param aThickness  thickness of the drawing (default <b>3</b>)
   * @param aColor      color of the drawing    (default qgar::QGE_COLOR_DEFAULT)
   */
  virtual void write(const GenPoint<double>& aPt,
		     int aThickness  = 3,
		     QGEcolor aColor = QGE_COLOR_DEFAULT);

  //@}


  /** @name Output chains of points */
  //        =======================
  //@{

  /**
   * @brief Write a chain of points with coordinates of type <b>int</b>.
   *
   * @param aChain      a chain of points
   * @param aThickness  thickness of the drawing (default <b>3</b>)
   * @param aColor      color of the drawing     (default qgar::QGE_COLOR_DEFAULT)
   */
  virtual void write(AbstractGenPointChain<int>& aChain,
		     int aThickness  = 3,
		     QGEcolor aColor = QGE_COLOR_DEFAULT);

  /**
   * @brief Write a chain of points with coordinates of type <b>float</b>.
   *
   * @param aChain      a chain of points
   * @param aThickness  thickness of the drawing (default <b>3</b>)
   * @param aColor      color of the drawing     (default qgar::QGE_COLOR_DEFAULT)
   */
  virtual void write(AbstractGenPointChain<float>& aChain,
		     int aThickness  = 3,
		     QGEcolor aColor = QGE_COLOR_DEFAULT);

  /**
   * @brief Write a chain of points with coordinates of type <b>double</b>.
   *
   * @param aChain      a chain of points
   * @param aThickness  thickness of the drawing (default <b>3</b>)
   * @param aColor      color of the drawing     (default qgar::QGE_COLOR_DEFAULT)
   */
  virtual void write(AbstractGenPointChain<double>& aChain,
		     int aThickness  = 3,
		     QGEcolor aColor = QGE_COLOR_DEFAULT);

  //@}


  /** @name Output segments */
  //        ===============
  //@{

  /**
   * @brief Write a segment with coordinates of type <b>int</b>.
   *
   * @param aXSource    X coordinate of the source point of the segment
   * @param aYSource    Y coordinate of the source point of the segment
   * @param aXTarget    X coordinate of the target point of the segment
   * @param aYTarget    Y coordinate of the target point of the segment
   * @param aThickness  thickness of the drawing (default <b>1</b>)
   * @param aColor      color of the drawing     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline of the drawing   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  virtual void write(int aXSource,
		     int aYSource,
		     int aXTarget,
		     int aYTarget,
		     int        aThickness = 1,
		     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  /**
   * @brief Write a segment with coordinates of type <b>float</b>.
   *
   * @param aXSource    X coordinate of the source point of the segment
   * @param aYSource    Y coordinate of the source point of the segment
   * @param aXTarget    X coordinate of the target point of the segment
   * @param aYTarget    Y coordinate of the target point of the segment
   * @param aThickness  thickness of the drawing (default <b>1</b>)
   * @param aColor      color of the drawing     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline of the drawing   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  virtual void write(float aXSource,
		     float aYSource,
		     float aXTarget,
		     float aYTarget,
		     int        aThickness = 1,
		     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  /**
   * @brief Write a geometrical segment with coordinates of type <b>double</b>.
   *
   * @param aXSource    X coordinate of the source point of the segment
   * @param aYSource    Y coordinate of the source point of the segment
   * @param aXTarget    X coordinate of the target point of the segment
   * @param aYTarget    Y coordinate of the target point of the segment
   * @param aThickness  thickness of the drawing (default <b>1</b>)
   * @param aColor      color of the drawing     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline of the drawing   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  virtual void write(double aXSource,
		     double aYSource,
		     double aXTarget,
		     double aYTarget,
		     int        aThickness = 1,
		     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  //@}


  /** @name Output circles */
  //        ==============
  //@{

  /**
   * @brief Write a circle with coordinates of type <b>int</b>.
   *
   * @param aXCenter    X coordinate of the center
   * @param aYCenter    Y coordinate of the center
   * @param aRadius     radius of the circle
   * @param aThickness  thickness              (default <b>1</b>)
   * @param aColor      color                  (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline of the drawing (default qgar::QGE_OUTLINE_DEFAULT)
   */
  virtual void write(int aXCenter,
		     int aYCenter,
		     double aRadius,
		     int        aThickness = 1,
		     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  /**
   * @brief Write a circle with coordinates of type <b>float</b>.
   *
   * @param aXCenter    X coordinate of the center
   * @param aYCenter    Y coordinate of the center
   * @param aRadius     radius of the circle 
   * @param aThickness  thickness              (default <b>1</b>)
   * @param aColor      color                 (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline of the drawing (default qgar::QGE_OUTLINE_DEFAULT)
   */
  virtual void write(float aXCenter,
		     float aYCenter,
		     double aRadius,
		     int        aThickness = 1,
		     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  /**
   * @brief Write a circle with coordinates of type <b>double</b>.
   *
   * @param aXCenter    X coordinate of the center
   * @param aYCenter    Y coordinate of the center
   * @param aRadius     radius of the circle
   * @param aThickness  thickness              (default <b>1</b>)
   * @param aColor      color                  (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline of the drawing (default qgar::QGE_OUTLINE_DEFAULT)
   */
  virtual void write(double aXCenter,
		     double aYCenter,
		     double aRadius,
		     int        aThickness = 1,
		     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  //@}


  /** @name Output arcs of circle */
  //        =====================
  //@{

  /**
   * @brief Write an arc with coordinates of type <b>int</b>.
   *
   * @param aXSource    X coordinate of the source point
   * @param aYSource    Y coordinate of the source point
   * @param aXTarget    X coordinate of the target point
   * @param aYTarget    Y coordinate of the target point
   * @param aXCenter    X coordinate of the center
   * @param aYCenter    Y coordinate of the center
   * @param aThickness  thickness of the drawing (default <b>1</b>)
   * @param aColor      color of the drawing     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline of the drawing   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  virtual void write(int aXSource,
		     int aYSource,
		     int aXTarget,
		     int aYTarget,
		     int aXCenter,
		     int aYCenter,
		     int        aThickness = 1,
		     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  /**
   * @brief Write an arc with coordinates of type <b>float</b>.
   *
   * @param aXSource    X coordinate of the source point
   * @param aYSource    Y coordinate of the source point
   * @param aXTarget    X coordinate of the target point
   * @param aYTarget    Y coordinate of the target point
   * @param aXCenter    X coordinate of the center
   * @param aYCenter    Y coordinate of the center
   * @param aThickness  thickness of the drawing (default <b>1</b>)
   * @param aColor      color of the drawing     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline of the drawing   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  virtual void write(float aXSource,
		     float aYSource,
		     float aXTarget,
		     float aYTarget,
		     float aXCenter,
		     float aYCenter,
		     int        aThickness = 1,
		     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  /**
   * @brief Write an arc with coordinates of type <b>double</b>.
   *
   * @param aXSource    X coordinate of the source point
   * @param aYSource    Y coordinate of the source point
   * @param aXTarget    X coordinate of the target point
   * @param aYTarget    Y coordinate of the target point
   * @param aXCenter    X coordinate of the center
   * @param aYCenter    Y coordinate of the center
   * @param aThickness  thickness of the drawing (default <b>1</b>)
   * @param aColor      color of the drawing     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline of the drawing   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  virtual void write(double aXSource,
		     double aYSource,
		     double aXTarget,
		     double aYTarget,
		     double aXCenter,
		     double aYCenter,
		     int        aThickness = 1,
		     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  //@}


  /** @name Output polylines */
  //        ================
  //@{

  /**
   * @brief Write a polyline with coordinates of type <b>int</b>.
   *
   * @param aPoly       a polyline
   * @param aThickness  thickness of the drawing (default <b>1</b>)
   * @param aColor      color of the drawing     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline of the drawing   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  virtual void write(const GenPolyline<int>& aPoly,
		     int        aThickness = 1,
		     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  /**
   * @brief Write a polyline with coordinates of type <b>float</b>.
   *
   * @param aPoly       a polyline
   * @param aThickness  thickness of the drawing (default <b>1</b>)
   * @param aColor      color of the drawing     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline of the drawing   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  virtual void write(const GenPolyline<float>& aPoly,
		     int        aThickness = 1,
		     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  /**
   * @brief Write a polyline with coordinates of type <b>double</b>.
   *
   * @param aPoly       a polyline
   * @param aThickness  thickness of the drawing (default <b>1</b>)
   * @param aColor      color of the drawing     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline of the drawing   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  virtual void write(const GenPolyline<double>& aPoly,
		     int        aThickness = 1,
		     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  //@}


  /** @name Output bounding boxes */
  //        =====================
  //@{

  /**
   * @brief Write a bounding box with coordinates of type <b>int</b>.
   *
   * @param aBox        a bounding box
   * @param aThickness  thickness of the drawing (default <b>1</b>)
   * @param aColor      color of the drawing     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline of the drawing   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  virtual void write(const BoundingBox& aBox,
		     int        aThickness = 1,
		     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  //@}


  /** @name Output (connected) components */
  //        =============================
  //@{

  /**
   * @brief Write the contour of a (connected) component and of all
   * included components (i.e. children in the component tree).
   *
   * @param aPNode      pointer to the node of the component tree
   *                    including the component
   * @param aThickness  thickness of the drawing (default <b>1</b>)
   * @param aColor      color of the drawing     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline of the drawing   (default qgar::QGE_OUTLINE_DEFAULT)
   *
   * @see class qgar::Component
   */
  virtual void write(const ConnectedComponents::node_type* const aPNode,
		     int        aThickness = 1,
		     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  //@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:


  /** @name Tgif specific information */
  //        =========================
  //@{

  /**
   * @brief Current Tgif version.
   */
  static const char* s_tgif_version_;

  /**
   * @brief Table of Tgif colors (see enum type qgar::QGEcolor).
   */
  static const char* s_tgif_colors_[21];

  /**
   * @brief Table of Tgif outline types (see enum type qgar::QGEoutline).
   */
  static const unsigned char s_tgif_outlines_[10];

  /**
   * @brief Tgif resolution: Number of pixels per inch.
   */
  static const int s_tgif_pix_per_inch_;

  /**
   * @brief Tgif A4 page width (in pixels).
   */
  static const float s_tgif_a4_page_width_;

  /**
   * @brief Tgif A4 page height (in pixels).
   */
  static const float s_tgif_a4_page_height_;

  /**
   * @brief Number of objects in the file.
   */
  int tgifObjectCnt_;

  //@}


  /** @name Header */
  //        ======
  //@{

  /**
   * @brief Write file header.
   */
  void writeHeader();

  /**
   * @brief Write file footer (nothing to do).
   */
  void writeFooter();

  //@}


  /** @name Save predicates describing Tgif objects */
  //        =======================================
  //@{

  /**
   * @brief Save the predicate describing a chain of points
   *        with coordinates of type <b>T</b>.
   *
   * As points are not Tgif objects, the chain is described by
   * a polyline whose vertices are the points of the chain.
   *
   * @param aChain      a chain
   * @param aThickness  thickness of the drawing
   * @param aColor      color of the drawing
   *
   * @todo
   *   Argument <b>aChain</b> cannot be declared <b>const</b>
   *   because iterating on a list occasions some modifications 
   *   in the list (see function <b>setInitialPosition()</b> of class
   *   qgar::GenChain, for example). Class <b>AbstractGenPointChain</b>
   *   and its descendants should be modified by declaring some data
   *   members as <b>mutable</b>.
   */
  template <class T>
  void
  saveChain(AbstractGenPointChain<T>& aChain,
	    int aThickness,
	    QGEcolor aColor);

  /**
   * @brief Save the predicate describing a point.
   *
   * As a point is not a Tgif object, it is described by
   * a polyline including only one vertice (integer coordinates).
   *
   * @param aX          X coordinate of the point
   * @param aY          Y coordinate of the point
   * @param aThickness  thickness of the drawing
   * @param aColor      color of the drawing
   */
  void savePoint(int aX,
		 int aY,
		 int aThickness,
		 QGEcolor aColor);

  /**
   * @brief Save the predicate describing a segment.
   *
   * As a segment is not a Tgif object, it is described
   * by a polyline including two points (the source and target
   * of the segment).
   *
   * @param aXSource   X coordinate of the source point
   * @param aYSource   Y coordinate of the source point
   * @param aXTarget   X coordinate of the target point
   * @param aYTarget   Y coordinate of the target point
   * @param aThickness thickness of the drawing
   * @param aColor     color of the drawing
   * @param anOutline  outline of the drawing
   */
  void saveSegment(int aXSource,
		   int aYSource,
		   int aXTarget,
		   int aYTarget,
		   int aThickness,
		   QGEcolor aColor,
		   QGEoutline anOutline);

  /**
   * @brief Save the predicate describing a Tgif circle.
   *
   * @param aXCenter    X coordinate of the center
   * @param aYCenter    Y coordinate of the center
   * @param aRadius     radius
   * @param aThickness  thickness of the drawing
   * @param aColor      color of the drawing
   * @param anOutline   outline of the drawing
   */
  void saveCircle(int aXCenter,
		  int aYCenter,
		  int aRadius,
		  int aThickness,
		  QGEcolor aColor,
		  QGEoutline anOutline);

  /**
   * @brief Save the predicate describing a Tgif arc.
   *
   * @param aXSource     X coordinate of source point
   * @param aYSource     Y coordinate of source point
   * @param aXTarget     X coordinate of target point
   * @param aYTarget     Y coordinate of target point
   * @param aXCenter     X coordinate of the center
   * @param aYCenter     Y coordinate of the center
   * @param aThickness   thickness of the drawing
   * @param aColor       color of the drawing
   * @param anOutline    outline of the drawing
   */
  void saveArc(int aXSource,
	       int aYSource,
	       int aXTarget,
	       int aYTarget,
	       int aXCenter,
	       int aYCenter,
	       int aThickness,
	       QGEcolor aColor,
	       QGEoutline anOutline);

  /**
   * @brief Save the predicate describing a polyline
   *        with coordinates of type <b>T</b>.
   *
   * @param aPoly       a polyline
   * @param aThickness  thickness of the drawing
   * @param aColor      color of the drawing
   * @param anOutline   outline of the drawing
   */
  template <class T>
  void
  savePolyline(const GenPolyline<T>& aPoly,
	       int aThickness,
	       QGEcolor aColor,
	       QGEoutline anOutline);

  /**
   * @brief Save the beginning part of the predicate
   *   describing a Tgif polyline.
   *
   * @param aVerticesCnt  number of vertices of the polyline
   * @param aColor       color of the drawing
   */
  void savePolylineBegin(int aVerticesCnt, QGEcolor aColor);

  /**
   * @brief Save the ending part of the predicate
   *   describing a Tgif polyline.
   *
   * @param aVerticesCnt  number of vertices of the polyline
   * @param aThickness    thickness of the drawing
   * @param anOutline     outline of the drawing
   */
  void savePolylineEnd(int aVerticesCnt,
		       int aThickness,
		       QGEoutline anOutline);

  /**
   * @brief Save the predicate describing a Tgif box.
   *
   * @param aXTopLeft      X coordinate of top left point
   * @param aYTopLeft      Y coordinate of top left point
   * @param aXBottomRight  X coordinate of bottom right point
   * @param aYBottomRight  Y coordinate of bottom right point
   * @param aThickness     thickness of the drawing
   * @param aColor         color of the drawing
   * @param anOutline      outline of the drawing
   */
  void saveBox(int aXTopLeft,
	       int aYTopLeft,
	       int aXBottomRight,
	       int aYBottomRight,
	       int aThickness,
	       QGEcolor aColor,
	       QGEoutline anOutline);

  //@}


// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

  //  ============================================================
  /** @name Not yet implemented
      These functions belong to the private section
      as they are not yet implemented and thus should not be used.
  */
  //  ============================================================
  //@{

  /**
   * @brief Read file header.
   *
   * @warning Not yet implemented.
   * @exception qgar::QgarErrorDeveloper  not yet implemented
   *
   * @todo Implement qgar::TgifFile::readHeader()
   */
  void readHeader();

  //@}


  /** @name AUXILIARIES */
  //        ===========
  //@{

  /**
   * @brief Write the contour of a (connected) component and of all
   * included components (i.e. children in the component tree).
   *
   * @param aPNode     pointer to the node of the component tree
   *                   including the component
   * @param aThickness thickness of the drawing
   * @param aColor     color of the drawing
   * @param anOutline  outline of the drawing
   *
   * @see class qgar::Component
   */
  void
  PRIVATEwriteComponent(const ConnectedComponents::node_type* const aPNode,
			int aThickness,
			QGEcolor aColor,
			QGEoutline anOutline);

  //@}


// -------------------------------------------------------------------
}; // class TgifFile




// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// T E M P L A T E   I M P L E M E N T A T I O N 
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


// =======================================
// SAVE PREDICATES DESCRIBING TGIF OBJECTS
// =======================================


// A POLYLINE (INTEGER COORDINATES)
// aPoly       a polyline
// aColor      color of the drawing
// aThickness  thickness of the drawing
// anOutline   outline of the drawing

template <class T>
void
TgifFile::savePolyline(const GenPolyline<T>& aPoly,
		       int aThickness,
		       QGEcolor aColor,
		       QGEoutline anOutline)
{
   std::deque< GenPoint<T> > vDeq = aPoly.accessVertices();
   int pointCnt = vDeq.size();

   savePolylineBegin(pointCnt, aColor);

   int idx;

   for (idx = 0 ; idx < (pointCnt - 1) ; ++idx)
     {
       fstream_ << (int) vDeq[idx].x()
		   << ','
		   << (int) vDeq[idx].y()
		   << ',';
     }

   // Last point
   fstream_ << (int) vDeq[idx].x()
	       << ','
	       << (int) vDeq[idx].y();

   savePolylineEnd(pointCnt, aThickness, anOutline);
}


// A CHAIN OF POINTS (COORDINATES OF TYPE 'T')
// aChain     a chain
// aColor    color of the drawing
// aThickness thickness of the drawing

template <class T>
void
TgifFile::saveChain(AbstractGenPointChain<T>& aChain,
		    int aThickness,
		    QGEcolor aColor)

{
  if (!aChain.empty())
    {
      int pointCnt = aChain.size();
      savePolylineBegin(pointCnt, aColor);

      aChain.setToBegin();
      fstream_ << (int) (aChain.accessCurrent()).x()
		  << ','
		  << (int) (aChain.accessCurrent()).y();

      int lineCnt = 1;

      while(aChain.hasNext())
	{
	  lineCnt++;
	  if (lineCnt > 8)
	    {
	      lineCnt = 1;
	      fstream_ << ",\n\t";
	    }
	  else
	    {
	      fstream_ << ',';
	    }

	  aChain.moveNext();
	  fstream_ << (int) (aChain.accessCurrent()).x()
		   << ','
		   << (int) (aChain.accessCurrent()).y();
	}

      savePolylineEnd(pointCnt, aThickness, QGE_OUTLINE_SOLID);
    }
}


// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// END OF TEMPLATE IMPLEMENTATION
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


} // namespace qgar

#endif /* __TGIFFILE_H_INCLUDED__ */
