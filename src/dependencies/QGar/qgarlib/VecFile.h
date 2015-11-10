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


#ifndef __VECFILE_H_INCLUDED__
#define __VECFILE_H_INCLUDED__


/**
 * @file VecFile.h
 *
 * @brief Header file of class qgar::VecFile.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   November 08, 2005  15:15
 * @since  Qgar 2.2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: VecFile.h,v 1.5 2007/02/14 17:34:05 masini Exp $ */



// QGAR
#include "AbstractGraphicsFile.h"
#include "ConnectedComponents.h"
#include "primitives.h"
#include "QgarErrorDeveloper.h"
#include "QgarErrorIO.h"
#include "QgarErrorUser.h"


namespace qgar
{
  // Avoid #include's when not necessary
  class BoundingBox;
  template <class T> class AbstractGenPointChain;
}



namespace qgar
{

/**
 * @ingroup IO_FILE
 *
 * @class VecFile VecFile.h "qgarlib/VecFile.h"
 *
 * @brief File containing primitives in VEC format.
 *
 * The VEC format has been defined for the Second International Graphics
 * Recognition Contest by Atul Chhabra and Ihsin Phillips
 * [<a href="Chhabra-and-Phillips-1998" target="_blank">Chhabra&nbsp;and&nbsp;Phillips,&nbsp;1998</a>]
 * as a very simple format which should be suitable for evaluation purposes.
 * You may also see the
 * <a href="http://symbcontestgrec05.loria.fr/formatvec.php" target="blank">GREC 2005 web site</a>.
 *
 * A line of the file must not exceed
 * qgar::VecFile::s_vec_line_size_ characters.
 *
 * All syntactical features and tokens of the VEC format
 * are given in section <b>VEC syntactical features</b>.
 *
 *
 * <b><i>1&nbsp; THE HEADER</i></b>
 *
 *
 * The first line looks like:
@code
%VEC-1.0 xsize ysize [dpi]
@endcode
 * - <b>VEC-1.0</b> is the character string representing the VEC version
 *   used to encode the file. Its length must not exceed
 *   qgar::VecFile::s_vec_version_size_ characters.
 *   The version currently supported by Qgar is given
 *   by function qgar::VecFile::version.
 * - <b>xsize</b> (resp. <b>ysize</b>) is the maximum X (resp. Y) coordinate
 *   of the primitives contained by the file.
 * - If <b>dpi</b> is provided, <b>xsize</b> and <b>ysize</b> are expressed in
 *   pixels, and <b>dpi</b> gives the resolution of the initial image
 *   (in dots per inch). If <b>dpi</b> is omitted, its value is substituted
 *   for the value given by function qgar::VecFile::dpiUnknown.
 *   In this case, <b>xsize</b> and <b>ysize</b> are expressed in a specific
 *   unit, which is supposed to be known by the users of the file.
 *
 * Each line following the header represents the description of a primitive:
 * line segment, circle, arc of circle, or textual region.
 * 
 *
 * <b><i>2&nbsp; DESCRIPTION OF THE PRIMITIVES</i></b>
 *
@verbatim
   O
    +---------------> X
    |\    |
    | \ <-'
    |  \    angle (in degrees)
    |   \
    |
    V

    Y
@endverbatim
 * <b>Warning:</b>
 * - the origin of the coordinate system is at top left corner,
 * - angles are clockwise from the X axis,
 * - coordinates are postive and are given in pixels,
 * - angles are postive and are given in degrees.
 *
 *
 * <b><i>2.1&nbsp; Line segments</i></b>
@code
L C|D x1 y1 x2 y2 width
@endcode
 * - <b>L</b> (qgar::VecFile::s_vec_prim_segment_)
 *   introduces a line segment,
 *   <b>C</b>ontinuous (qgar::VecFile::s_vec_outline_continuous_)
 *   or <b>D</b>ashed (qgar::VecFile::s_vec_outline_dashed_).
 * - <b>(x1,y1)</b> and <b>(x2,y2)</b>
 *   are the two endpoints of the line segment.
 * - <b>width</b> is the thickness of the drawing.
 *
 *
 * <b><i>2.2&nbsp; Circles</i></b>
@code
C C|D xcenter ycenter radius width
@endcode
 * - <b>C</b> (qgar::VecFile::s_vec_prim_circle_) introduces a circle,
 *   <b>C</b>ontinuous (qgar::VecFile::s_vec_outline_continuous_)
 *   or <b>D</b>ashed (qgar::VecFile::s_vec_outline_dashed_).
 * - <b>(xcenter,ycenter)</b> are the coordinates of the center.
 * - <b>radius</b> is self-explanatory.
 * - <b>width</b> is the thickness of the drawing.
 *
 *
 * <b><i>2.3&nbsp; Arc of circle</i></b>
@code
A C|D xcenter ycenter radius start_angle end_angle width
@endcode
 * - <b>A</b> (qgar::VecFile::s_vec_prim_arc_) introduces an arc of circle,
 *   <b>C</b>ontinuous (qgar::VecFile::s_vec_outline_continuous_)
 *   or <b>D</b>ashed (qgar::VecFile::s_vec_outline_dashed_).
 * - <b>(xcenter,ycenter)</b> are the coordinates of the center.
 * - <b>radius</b> is self-explanatory.
 * - <b>start_angle</b> (resp. <b>end_angle</b>) is the angle formed
 *   by the X axis and the vector joining the center to the starting
 *   (resp. ending) point of the arc.
@verbatim
   O                                 O
    +----------------------> X        +----------------------> X
    | center                          |           ----
    |      +-------+ end              |          /    \
    |       \      |                  |     arc |      v
    |        \    / arc               |         |   +--+ end
    |   start +<-                     |          \ / c
    |                                 |           +   
    V                                 V      start

    Y                                 Y
@endverbatim
 *   The move from <b>start_angle</b> to <b>end_angle</b> is clockwise and
 *   determines the way to draw the arc.
 * - <b>width</b> is the thickness of the drawing.
 *
 *
 * <b><i>2.4&nbsp; Textual region</i></b>
@code
T x1 y1 x2 y2 orientation fontHeight fontWidthFactor fontStrokeWidth %TEXT
@endcode
 * - <b>T</b> (qgar::VecFile::s_vec_prim_text_) introduces a textual region.
 * - <b>(x1,y1)</b> and <b>(x2,y2)</b> are diagonally opposite
 *   corners of the bounding box of the text string. In fact,
 *   <b>(x1,y1)</b> is supposed to be the insertion point of the
 *   left-justified text.
 * - <b>orientation</b> is the angle formed by the X axis and the baseline
 *   of the text.
 * - <b>fontHeight</b>, <b>fontWidthFactor</b> and <b>fontStrokeWidth</b>
 *   are used for rendering text. They may be unknown and, in this case,
 *   are set to the value returned by function
 *   qgar::VecFile::textUnknownFeature (qgar::VecFile::s_vec_text_unknown_).
 * - <b>%</b> (qgar::VecFile::s_vec_comment_)
 *   introduces the text string, which may be left blank;
 *   <b>%</b> must nevertheless be included in this case.
 *   The string must not include any blank character, and the string
 *   length must not exceed qgar::VecFile::s_vec_text_size_ characters.
 *
 *
 * <b><i>3&nbsp; INPUT</i></b>
 *
 * Global features about the file are available once the file is open.
 * They can be retrieved using member functions of section
 * <b>Access to file features</b>
 *
 * Primitives are consecutively input one by one, using function
 * <b>qgar::VecFile::read</b>. See this function.
 *
 * The features of the last input primitive can be retrieved using member
 * functions of sections <b>Queries about last input primitive</b> and
 * <b>Access to last input primitive</b>.
 * Warning:
 * The value returned by these functions is irrelevant when
 * the corresponding feature is not part of the last input primitive.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   November 08, 2005  15:15
 * @since  Qgar 2.2.1
 */
class VecFile

  : public AbstractGraphicsFile

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S :   V E C
// -------------------------------------------------------------------
public:

// ___________________________________________________________________
//
// To bring (concrete) functions 'write' inherited from class
// qgar::AbstractGraphicsFile into the scope of the class

  using AbstractGraphicsFile::write;

// ___________________________________________________________________


  /** @name About VEC */
  //        =========
  //@{

  /**
   * @brief Return the VEC version supported by Qgar.
   */
  inline const char* const version() const;

  /**
   * @brief Return the substitution value for an unknown
   *  (or useless) text feature.
   */
  inline double textUnknownFeature() const;

  //@}


// -------------------------------------------------------------------
// P U B L I C    M E M B E R S :
// C O N S T R U C T O R S   &   D E S T R U C T O R
// -------------------------------------------------------------------


  /** @name Constructors */
  //        ============
  //@{

  /**
   * @brief To be used to read data from an existing file.
   *
   * @param aFileName name of the file
   */
  explicit VecFile(const char* aFileName);

  /**
   * @brief To be typically used to write data in a new file.
   *
   * @param aFileName  name of the file
   * @param aWidth     maximal Y coordinate of the primitives
   *                   to be stored in the file (<i>i.e.</i> image width)
   * @param aHeight    maximal X coordinate of the primitives
   *                   to be stored in the file (<i>i.e.</i> image height)
   * @param aDpi       resolution of the corresponding image,
   *                   in dots per inch (default <b>unknown</b>)
   */
  VecFile(const char* aFileName,
	  int aWidth,
	  int aHeight,
	  int aDpi = s_vec_dpi_unknown_);

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  virtual ~VecFile();

  //@}


// -------------------------------------------------------------------
// P U B L I C    M E M B E R S :   A C C E S S
// -------------------------------------------------------------------


  /** @name Access to file features */
  //        =======================
  //@{

  /**
   * @brief Get the VEC version used for the file.
   */
  inline const char* const fileVersion() const;

  /**
   * @brief Get the maximum X coordinate of the primtives
   *   of the file (<i>i.e.</i> image width).
   */
  inline int width() const;

  /**
   * @brief Get the maximum Y coordinate of the primtives
   *   of the file (<i>i.e.</i> image height).
   */
  inline int height() const;

  /**
   * @brief Get the resolution of the initial image
   * (in dots per inch), or value provided by function
   * qgar::VecFile::dpiUnknown if unknown.
   */
  inline int dpi() const;

  /**
   * @brief Return substitution value used for the
   * initial resolution when it is unknown
   * (qgar::VecFile::s_vec_dpi_unknown_).
   */
  inline int dpiUnknown() const;

  /**
   * @brief Return <b>true</b> if resolution is known.
   */
  inline bool isDpiKnown() const;

  /**
   * @brief Return <b>true</b> if end of file is reached.
   */
  inline bool eof() const;

  //@}


  /** @name Queries about last input primitive */
  //        ==================================
  //@{

  /**
   * @brief Return <b>true</b> if no primitive is input yet.
   */
  inline bool isNone() const;

  /**
   * @brief Return <b>true</b> if the last input primitive
   *   is a line segment.
   */
  inline bool isSegment() const;

  /**
   * @brief Return <b>true</b> if the last input primitive
   *   is a circle.
   */
  inline bool isCircle() const;

  /**
   * @brief Return <b>true</b> if the last input primitive
   *   is an arc of circle.
   */
  inline bool isArc() const;

  /**
   * @brief Return <b>true</b> if the last input primitive
   *   is a textual region.
   */
  inline bool isText() const;

  /**
   * @brief Return <b>true</b> if font height is known.
   *
   * The result is relevant only when the last input primitive
   * is a textual region.
   */
  inline bool isFontHeightKnown() const;

  /**
   * @brief Return <b>true</b> if font width factor is known.
   *
   * The result is relevant only when the last input primitive
   * is a textual region.
   */
  inline bool isFontWidthFactorKnown() const;

  /**
   * @brief Return <b>true</b> if font stroke width is known.
   *
   * The result is relevant only when the last input primitive
   * is a textual region.
   */
  inline bool isFontStrokeWidthKnown() const;

  //@}


  /** @name Access to last input primitive */
  //        ==============================
  //@{

  /**
   * @brief Get the type (<i>i.e.</i> VEC code)
   *   of the last input primitive.
   *
   * See section <b>VEC syntactical features</b> for the list 
   * of codes (the function returns qqgar::VecFile::s_vec_prim_unknown_
   * when no primitive is input yet).
   */
  inline char lastPrimitive() const;

  /**
   * @brief Get drawing thickness.
   *
   * The result is relevant only when the last input primitive is
   * a line segment, a circle, or an arc of circle.
   */
  inline int thickness() const;

  /**
   * @brief Get drawing outline.
   *
   * The result is relevant only when the last input primitive is
   * a line segment, a circle, or an arc of circle.
   *
   * Returns:
   * - qgar::QGE_OUTLINE_SOLID, when VEC outline is <b>continuous</b>
   *   (qgar::VecFile::s_vec_outline_continuous_)
   * - qgar::QGE_OUTLINE_DASH_REGULAR, when VEC outline is <b>dashed</b>
   *   (qgar::VecFile::s_vec_outline_dashed_)
   */
  inline QGEoutline outline() const;

  /**
   * @brief Get X coordinate of source point.
   *
   * The result is relevant only when the last input primitive is
   * a line segment.
   */
  inline double xSource() const;

  /**
   * @brief Get Y coordinate of source point.
   *
   * The result is relevant only when the last input primitive is
   * a line segment.
   */
  inline double ySource() const;

  /**
   * @brief Get X coordinate of target point.
   *
   * The result is relevant only when the last input primitive is
   * a line segment.
   */
  inline double xTarget() const;

  /**
   * @brief Get Y coordinate of target point.
   *
   * The result is relevant only when the last input primitive is
   * a line segment.
   */
  inline double yTarget() const;

  /**
   * @brief Get X coordinate of center point.
   *
   * The result is relevant only when the last input primitive is
   * a circle or an arc of circle.
   */
  inline double xCenter() const;

  /**
   * @brief Get Y coordinate of center point.
   *
   * The result is relevant only when the last input primitive is
   * a circle or an arc of circle.
   */
  inline double yCenter() const;

  /**
   * @brief Get radius.
   *
   * The result is relevant only when the last input primitive is
   * a circle or an arc of circle.
   */
  inline double radius() const;

  /**
   * @brief Get ource angle (start angle, in VEC terminology).
   *
   * The result is relevant only when the last input primitive is
   * a circle.
   */
  inline double sourceAngleDegrees() const;

  /**
   * @brief Get target angle (end angle, in VEC terminology).
   *
   * The result is relevant only when the last input primitive is
   * a circle.
   */
  inline double targetAngleDegrees() const;

  /**
   * @brief Get X coordinate of first corner.
   *
   * The result is relevant only when the last input primitive is
   * a textual region.
   */
  inline double xCorner1() const;

  /**
   * @brief Get Y coordinate of first corner.
   *
   * The result is relevant only when the last input primitive is
   * a textual region.
   */
  inline double yCorner1() const;

  /**
   * @brief Get X coordinate of second corner.
   *
   * The result is relevant only when the last input primitive is
   * a textual region.
   */
  inline double xCorner2() const;

  /**
   * @brief Get Y coordinate of second corner.
   *
   * The result is relevant only when the last input primitive is
   * a textual region.
   */
  inline double yCorner2() const;

  /**
   * @brief Get orientation.
   *
   * The result is relevant only when the last input primitive is
   * a textual region.
   */
  inline double orientationDegrees() const;

  /**
   * @brief Get the font height, or value provided by function
   * qgar::VecFile::textUnknownFeature if unknown.
   *
   * The result is relevant only when the last input primitive is
   * a textual region.
   */
  inline double fontHeight() const;

  /**
   * @brief Get font width factor, or value provided by function
   * qgar::VecFile::textUnknownFeature if unknown.
   *
   * The result is relevant only when the last input primitive is
   * a textual region.
   */
  inline double fontWidthFactor() const;

  /**
   * @brief Get font stroke width, or value provided by function
   * qgar::VecFile::textUnknownFeature if unknown.
   *
   * The result is relevant only when the last input primitive is
   * a textual region.
   */
  inline double fontStrokeWidth() const;

  /**
   * @brief Get text string (possibly blank).
   *
   * The result is relevant only when the last input primitive is
   * a textual region.
   */
  inline const char* text() const;

  //@}


// -------------------------------------------------------------------
// P U B L I C    M E M B E R S :   H E A D E R   &   F O O T E R
// -------------------------------------------------------------------


  /** @name Header */
  //        ======
  //@{

  /**
   * @brief Read file header.
   *
   * @exception qgar::QgarErrorIO   bad header
   * @exception qgar::QgarErrorIO   junk in file
   * @exception qgar::QgarErrorUser VEC version not supported
   */
  virtual void readHeader();

  /**
   * @brief Write file header.
   */
  virtual void writeHeader();

  //@}


// -------------------------------------------------------------------
// P U B L I C   M E M B E R S :   I N P U T
// -------------------------------------------------------------------


  /** @name Input primitives */
  //        ================
  //@{

  /**
   * @brief Input next primitive in file.
   *
   * The function returns the type (<i>i.e.</i> VEC code)
   * of the input primitive, or <b>EOF</b> if end of file is reached.
   *
   * The primitive features, as given by the VEC description,
   * are stored in data members. They can be retrieved using functions
   * described in sections <b>Access to last input primitive</b>
   * and <b>Queries about last input primitive</b>.
   *
   * @exception qgar::QgarErrorIO  unknown primitive
   * @exception qgar::QgarErrorIO  bad text string
   * @exception qgar::QgarErrorIO  junk after last primitive feature
   */
  char read();

  //@}


// -------------------------------------------------------------------
// P U B L I C    M E M B E R S :   O U T P U T
// -------------------------------------------------------------------


  /** @name Output line segments */
  //        ====================
  //@{

  /**
   * @brief Output a segment with coordinates of type <b>int</b>.
   *
   * - Argument <b>aColor</b> is not (yet) taken into account,
   *   as it is not supported by the supported VEC format, 
   *   given by function qgar::VecFile::version.
   * - The given outline is converted to a VEC outline
   *   using function qgar::VecFile::toVecOutline.
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
		     QGEcolor   aColor     = QGE_COLOR_BLACK,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  /**
   * @brief Output a segment with coordinates of type <b>float</b>.
   *
   * - The segment coordinates are converted to <b>int</b> numbers
   *   before output.
   * - Argument <b>aColor</b> is not (yet) taken into account,
   *   as it is not supported by the supported VEC format,
   *   given by function qgar::VecFile::version.
   * - The given outline is converted to a VEC outline
   *   using function qgar::VecFile::toVecOutline.
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
		     int aThickness       = 1,
		     QGEcolor aColor      = QGE_COLOR_BLACK,
		     QGEoutline anOutline = QGE_OUTLINE_DEFAULT);

  /**
   * @brief Output a segment with coordinates of type <b>double</b>.
   *
   * - The segment coordinates are converted to <b>int</b> numbers
   *   before output.
   * - Argument <b>aColor</b> is not (yet) taken into account,
   *   as it is not supported by the supported VEC format,
   *   given by function qgar::VecFile::version.
   * - The given outline is converted to a VEC outline
   *   using function qgar::VecFile::toVecOutline.
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
		     QGEcolor   aColor     = QGE_COLOR_BLACK,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  //@}


  /** @name Output circles */
  //        ==============
  //@{

  /**
   * @brief Output a circle with coordinates of type <b>int</b>.
   *
   * - Argument <b>aColor</b> is not (yet) taken into account,
   *   as it is not supported by the supported VEC format,
   *   given by function qgar::VecFile::version.
   * - The given outline is converted to a VEC outline
   *   using function qgar::VecFile::toVecOutline.
   *
   * @param aXCenter    X coordinate of the center
   * @param aYCenter    Y coordinate of the center
   * @param aRadius     radius
   * @param aThickness  thickness  (default <b>1</b>)
   * @param aColor      color      (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline    (default qgar::QGE_OUTLINE_DEFAULT)
   */
  virtual void write(int aXCenter,
		     int aYCenter,
		     double aRadius,
		     int        aThickness = 1,
		     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  /**
   * @brief Output a circle with coordinates of type <b>float</b>.
   *
   * - The center coordinates and the radius are converted
   *   to <b>int</b> numbers before output.
   * - Argument <b>aColor</b> is not (yet) taken into account,
   *   as it is not supported by the supported VEC format,
   *   given by function qgar::VecFile::version.
   * - The given outline is converted to a VEC outline
   *   using function qgar::VecFile::toVecOutline.
   *
   * @param aXCenter    X coordinate of the center
   * @param aYCenter    Y coordinate of the center
   * @param aRadius     radius of the circle
   * @param aThickness  thickness (default <b>1</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  virtual void write(float aXCenter,
		     float aYCenter,
		     double aRadius,
		     int        aThickness = 1,
		     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  /**
   * @brief Output a circle with coordinates of type <b>double</b>.
   *
   * - The center coordinates and the radius are converted
   *   to <b>int</b> numbers before output.
   * - Argument <b>aColor</b> is not (yet) taken into account,
   *   as it is not supported by the supported VEC format,
   *   given by function qgar::VecFile::version.
   * - The given outline is converted to a VEC outline
   *   using function qgar::VecFile::toVecOutline.
   *
   * @param aXCenter    X coordinate of the center
   * @param aYCenter    Y coordinate of the center
   * @param aRadius     radius of the circle
   * @param aThickness  thickness  (default <b>1</b>)
   * @param aColor      color      (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline    (default qgar::QGE_OUTLINE_DEFAULT)
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
   * @brief Output an arc with coordinates of type <b>int</b>.
   *
   * - Argument <b>aColor</b> is not (yet) taken into account,
   *   as it is not supported by the supported VEC format,
   *   given by function qgar::VecFile::version.
   * - The given outline is converted to a VEC outline
   *   using function qgar::VecFile::toVecOutline.
   *
   * @param aXSource    X coordinate of the source point
   * @param aYSource    Y coordinate of the source point
   * @param aXTarget    X coordinate of the target point
   * @param aYTarget    Y coordinate of the target point
   * @param aXCenter    X coordinate of the center
   * @param aYCenter    Y coordinate of the center
   * @param aThickness  thickne/ss of the drawing (default <b>1</b>)
   * @param aColor      color of the drawing      (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline of the drawing    (default qgar::QGE_OUTLINE_DEFAULT)
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
   * @brief Output an arc with coordinates of type <b>float</b>.
   *
   * - The arc coordinates are converted to <b>int</b> numbers before output.
   * - Argument <b>aColor</b> is not (yet) taken into account,
   *   as it is not supported by the supported VEC format,
   *   given by function qgar::VecFile::version.
   * - The given outline is converted to a VEC outline
   *   using function qgar::VecFile::toVecOutline.
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
   * @brief Output an arc with coordinates of type <b>double</b>.
   *
   * - The arc coordinates are converted to <b>int</b> numbers before output.
   * - Argument <b>aColor</b> is not (yet) taken into account,
   *   as it is not supported by the supported VEC format,
   *   given by function qgar::VecFile::version.
   * - The given outline is converted to a VEC outline
   *   using function qgar::VecFile::toVecOutline.
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
  void write(double aXSource,
	     double aYSource,
	     double aXTarget,
	     double aYTarget,
	     double aXCenter,
	     double aYCenter,
	     int        aThickness = 1,
	     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
	     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  //@}


  /** @name Output textual regions */
  //        ======================
  //@{

  /**
   * @brief Output a textual region.
   *
   * @param aXInsert         X coordinate of the top left corner of the box bounding the text
   * @param aYInsert         Y coordinate of the top left corner of the box bounding the text
   * @param aXOpposite       X coordinate of the top left corner of the box bounding the text
   * @param aYOpposite       Y coordinate of the top left corner of the box bounding the text
   * @param anOrientationDegrees angle of the base line of the text   
   * @param aText            text string (default <b>blank</b>)
   * @param aFontHeight      text font height (default <b>unknown</b>)
   * @param aFontWidth       text font width (default <b>unknown</b>)
   * @param aFontStrokeWidth text font stroke width (default <b>unknown</b>)
   */
  void write(int aXInsert,
	     int aYInsert,
	     int aXOpposite,
	     int aYOpposite,
	     double anOrientationDegrees,
	     const char* aText       = "",
	     double aFontHeight      = s_vec_text_unknown_,
	     double aFontWidth       = s_vec_text_unknown_,
	     double aFontStrokeWidth = s_vec_text_unknown_);

  //@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S :   F I L E   D A T A
// -------------------------------------------------------------------
protected:


  /** @name File features */
  //        =============
  //@{

  /**
   * @brief I/O buffer.
   */
  char* inBuf_;

  /**
   * @brief VEC version used for the file.
   */
  char* fileVersion_;

  /**
   * @brief Maximum X coordinate of the primtives of the file.
   */
  int xsize_;

  /**
   * @brief Maximum Y coordinate of the primtives of the file.
   */
  int ysize_;

  /**
   * @brief Resolution of the initial image, in dots per inch
   * (qgar::VecFile::s_vec_dpi_unknown_ when unknown).
   */
  int dpi_;

  /**
   * @brief EOF flag.
   */
  bool eof_flag_;

  //@}


  /** @name Last input primitive features */
  //        =============================
  //@{

  /**
   * @brief Type (<i>i.e.</i> VEC code) of the last primitive
   *   input from the file.
   *
   * Contains qqgar::VecFile::s_vec_prim_unknown_
   * when no primitive is input yet.
   * See section <b>VEC syntactical features</b>
   * for the primitive codes.
   */
  char lastPrimitive_;

  /**
   * @brief Thickness of the last input primitive.
   *
   * This feature is relevant
   * for line segments, circles and arcs of circle only.
   */
  int thickness_;

  /**
   * @brief Outline of the last input primitive.
   *
   * The value may be:
   * - qgar::QGE_OUTLINE_SOLID, when VEC outline is <b>continuous</b>
   *   (qgar::VecFile::s_vec_outline_continuous_).
   * - qgar::QGE_OUTLINE_DASH_REGULAR, when VEC outline is <b>dashed</b>
   *   (qgar::VecFile::s_vec_outline_dashed_).
   *
   * This feature is relevant
   * for line segments, circles and arcs of circle only.
   */
  QGEoutline outline_;

  /**
   * @brief X coordinate of a particular point of the last input primitive.
   *
   * This particular point is:
   * - the source point for line segments,
   * - the center point for circles and arcs of circle,
   * - the first corner for textual regions.
   */
  double x1_;

  /**
   * @brief Y coordinate of a particular point of the last input primitive.
   *
   * This particular point is:
   * - the source point for line segments,
   * - the center point for circles and arcs of circle,
   * - the first corner for textual regions.
   */
  double y1_;

  /**
   * @brief X coordinate of a particular point of the last input primitive.
   *
   * This particular point is:
   * - the target point for line segments,
   * - the second corner for textual regions,
   * - irrelevant for circles and arcs of circle.
   */
  double x2_;

  /**
   * @brief Y coordinate of a particular point of the last input primitive.
   *
   * This particular point is:
   * - the target point for line segments,
   * - the second corner for textual regions,
   * - irrelevant for circles and arcs of circle.
   */
  double y2_;

  /**
   * @brief Radius, for circles and arcs of circle only.
   */
  double radius_;

  /**
   * @brief Start angle (source angle, in Qgar terminology),
   *   for arcs of circle only.
   */
  double startAngleDegrees_;

  /**
   * @brief End angle (target angle, in Qgar terminology),
   *   for arcs of circle only.
   */
  double endAngleDegrees_;

  /**
   * @brief Angle of the base line of the text, for textual regions only.
   */
  double orientationDegrees_;

  /**
   * @brief Font height, for textual regions only.
   *
   * The value is qgar::VecFile::s_vec_text_unknown_ if unknown.
   */
  double fontHeight_;

  /**
   * @brief Font width factor, for textual regions only.
   *
   * The value is qgar::VecFile::s_vec_text_unknown_ if unknown.
   */
  double fontWidthFactor_;

  /**
   * @brief Font stroke width, for textual regions only.
   *
   * The value is qgar::VecFile::s_vec_text_unknown_ if unknown.
   */
  double fontStrokeWidth_;

  /**
   * @brief Text string, for textual regions only!
   *
   * May be blank.
   */
  char* text_;

  //@}


// ---------------------------------------------------------------------
// PROTECTED DATA: VEC SYNTACTICAL FEATURES
// ---------------------------------------------------------------------
protected:


  /** @name VEC syntactical features */
  //        ========================
  //@{

  /**
   * @brief Maximum length of a line in the file.
   */
  static const int s_vec_line_size_;

  /**
   * @brief Maximum length of the version string.
   */
  static const int s_vec_version_size_;

  /**
   * @brief VEC version number supported by Qgar.
   */
  static const char* const s_vec_version_nb_;

  /**
   * @brief Token introducing a comment in the file.
   */
  static const char s_vec_comment_;

  /**
   * @brief Value of the initial resolution when unknown
   *   (<b>Qgar-specific</b>).
   */
  static const int s_vec_dpi_unknown_;

  /**
   * @brief <b>Qgar-specific</b> primitive type:
   *   no input primitive.
   */
  static const char s_vec_prim_none_;

  /**
   * @brief Primitive type: arc of circle.
   */
  static const char s_vec_prim_arc_;

  /**
   * @brief Primitive type: circle.
   */
  static const char s_vec_prim_circle_;

  /**
   * @brief Primitive type: line segment.
   */
  static const char s_vec_prim_segment_;

  /**
   * @brief Primitive type: textual region.
   */
  static const char s_vec_prim_text_;

  /**
   * @brief Outline: continuous.
   */
  static const char s_vec_outline_continuous_;

  /**
   * @brief Outline: dashed.
   */
  static const char s_vec_outline_dashed_;

  /**
   * @brief Value of an unknown text feature.
   */
  static const double s_vec_text_unknown_;

  /**
   * @brief Maximum length of the text string.
   */
  static const int s_vec_text_size_;

  //@}


// ---------------------------------------------------------------------
// P R O T E C T E D   F U N C T I O N S :   A U X I L I A R I E S
// ---------------------------------------------------------------------
protected:


  /** @name Auxiliaries */
  //        ===========
  //@{

  /**
   * @brief Convert a Qgar outline to a VEC outline.
   *
   * - qgar::QGE_OUTLINE_NONE,
   *   qgar::QGE_OUTLINE_DEFAULT and
   *   qgar::QGE_OUTLINE_SOLID
   *   are converted into <b>continuous</b>
   *   (qgar::VecFile::s_vec_outline_continuous_)
   * - all the other outlines are converted to <b>dashed</b>
   *   (qgar::VecFile::s_vec_outline_dashed_)
   *
   * @param anOutline  a Qgar outline
   */
  char toVecOutline(QGEoutline anOutline) const;

  /**
   * @brief Get an outline from the file.
   *
   * - <b>continuous</b> (qgar::VecFile::s_vec_outline_continuous_)
   *   is converted to qgar::QGE_OUTLINE_SOLID
   * - <b>dashed</b> (qgar::VecFile::s_vec_outline_dashed_)
   *   is converted to qgar::QGE_OUTLINE_DASH_REGULAR
   *
   * The resulting outline is stored in data member
   * qgar::VecFile::outline_.
   *
   * @param anIStream  an input string stream
   *
   * @exception qgar::QgarErrorIO  unknown outline
   */
  void getOutline(std::istringstream& anIStream);

  //@}


// ---------------------------------------------------------------------
// P R I V A T E    F U N C T I O N S
// ---------------------------------------------------------------------
private:

  //  ============================================================
  /** @name Not yet implemented
      These functions are not yet implemented  because the
      corresponding primitives are not supported by the current
      VEC format. They belong to a private section in order to
      forbid any use by clients.
  */
  //  ============================================================
  //@{

  // *************
  // OUTPUT POINTS
  // *************

  /**
   * @brief Output a point with coordinates of type <b>int</b>.
   *
   * This is just the implementation of the pure virtual function
   * defined in base class qgar::AbstractGraphicsFile.
   * It just throws an exception as points are not supported by the
   * current VEC format, given by function qgar::VecFile::version.
   *
   * @param aX          X coordinate of the point
   * @param aY          Y coordinate of the point
   * @param aThickness  thickness (default <b>3</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   *
   * @exception qgar::QgarErrorDeveloper
   *            points not supported by current VEC format
   */
  virtual void write(int aX,
		     int aY,
		     int aThickness  = 3,
		     QGEcolor aColor = QGE_COLOR_DEFAULT)
   ;

  /**
   * @brief Output a point with coordinates of type <b>float</b>.
   *
   * This is just the implementation of the pure virtual function
   * defined in base class qgar::AbstractGraphicsFile.
   * It just throws an exception as points are not supported by the
   * current VEC format, given by function qgar::VecFile::version.
   *
   * @param aX          X coordinate of the point
   * @param aY          Y coordinate of the point
   * @param aThickness  thickness (default <b>3</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   *
   * @exception qgar::QgarErrorDeveloper
   *            points not supported by current VEC format
   */
  virtual void write(float aX,
		     float aY,
		     int aThickness  = 3,
		     QGEcolor aColor = QGE_COLOR_DEFAULT)
   ;

  /**
   * @brief Output a point with coordinates of type <b>double</b>.
   *
   * This is just the implementation of the pure virtual function
   * defined in base class qgar::AbstractGraphicsFile.
   * It just throws an exception as points are not supported by the
   * current VEC format, given by function qgar::VecFile::version.
   *
   * @param aX          X coordinate of the point
   * @param aY          Y coordinate of the point
   * @param aThickness  thickness (default <b>3</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   *
   * @exception qgar::QgarErrorDeveloper
   *            points not supported by current VEC format
   */
  virtual void write(double aX,
		     double aY,
		     int aThickness  = 3,
		     QGEcolor aColor = QGE_COLOR_DEFAULT)
   ;

  // ***********************
  // OUTPUT CHAINS OF POINTS
  // ***********************

  /**
   * @brief Output a chain of points with coordinates of type <b>int</b>.
   *
   * This is just the implementation of the pure virtual function
   * defined in base class qgar::AbstractGraphicsFile.
   * It just throws an exception as points are not supported by the
   * current VEC format, given by function qgar::VecFile::version.
   *
   * @param aChain      a chain
   * @param aThickness  thickness (default <b>3</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   *
   * @exception qgar::QgarErrorDeveloper
   *            chains of points not supported by current VEC format
   */
  virtual void write(AbstractGenPointChain<int>& aChain,
		     int aThickness  = 3,
		     QGEcolor aColor = QGE_COLOR_DEFAULT)
   ;

  /**
   * @brief Output a chain of points with coordinates of type <b>float</b>.
   *
   * This is just the implementation of the pure virtual function
   * defined in base class qgar::AbstractGraphicsFile.
   * It just throws an exception as points are not supported by the
   * current VEC format, given by function qgar::VecFile::version.
   *
   * @param aChain      a chain
   * @param aThickness  thickness (default <b>3</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   *
   * @exception qgar::QgarErrorDeveloper
   *            chains of points not supported by current VEC format
   */
  virtual void write(AbstractGenPointChain<float>& aChain,
		     int aThickness  = 3,
		     QGEcolor aColor = QGE_COLOR_DEFAULT)
   ;

  /**
   * @brief Output a chain of points with coordinates of type <b>double</b>.
   *
   * This is just the implementation of the pure virtual function
   * defined in base class qgar::AbstractGraphicsFile.
   * It just throws an exception as points are not supported by the
   * current VEC format, given by function qgar::VecFile::version.
   *
   * @param aChain      a chain
   * @param aThickness  thickness (default <b>3</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   *
   * @exception qgar::QgarErrorDeveloper
   *            chains of points not supported by current VEC format
   */
  virtual void write(AbstractGenPointChain<double>& aChain,
		     int aThickness  = 3,
		     QGEcolor aColor = QGE_COLOR_DEFAULT)
   ;

  // ****************
  // OUTPUT POLYLINES
  // ****************

  /**
   * @brief Output a polyline with coordinates of type <b>int</b>.
   *
   * This is just the implementation of the pure virtual function
   * defined in base class qgar::AbstractGraphicsFile.
   * It just throws an exception as points are not supported by the
   * current VEC format, given by function qgar::VecFile::version.
   *
   * @param aPoly      a polyline
   * @param aThickness thickness (default <b>1</b>)
   * @param aColor     color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline  outline   (default qgar::QGE_OUTLINE_DEFAULT)
   *
   * @exception qgar::QgarErrorDeveloper
   *            polylines not supported by current VEC format
   */
  void write(const GenPolyline<int>& aPoly,
	     int        aThickness = 1,
	     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
	     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT)
   ;

  /**
   * @brief Output a polyline with coordinates of type <b>float</b>.
   *
   * This is just the implementation of the pure virtual function
   * defined in base class qgar::AbstractGraphicsFile.
   * It just throws an exception as points are not supported by the
   * current VEC format, given by function qgar::VecFile::version.
   *
   * @param aPoly      a polyline
   * @param aThickness thickness (default <b>1</b>)
   * @param aColor     color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline  outline   (default qgar::QGE_OUTLINE_DEFAULT)
   *
   * @exception qgar::QgarErrorDeveloper
   *            polylines not supported by current VEC format
   */
  void write(const GenPolyline<float>& aPoly,
	     int        aThickness = 1,
	     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
	     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT)
   ;

  /**
   * @brief Output a polyline with coordinates of type <b>double</b>.
   *
   * This is just the implementation of the pure virtual function
   * defined in base class qgar::AbstractGraphicsFile.
   * It just throws an exception as points are not supported by the
   * current VEC format, given by function qgar::VecFile::version.
   *
   * @param aPoly      a polyline
   * @param aThickness thickness (default <b>1</b>)
   * @param aColor     color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline  outline   (default qgar::QGE_OUTLINE_DEFAULT)
   *
   * @exception qgar::QgarErrorDeveloper
   *            polylines not supported by current VEC format
   */
  void write(const GenPolyline<double>& aPoly,
	     int        aThickness = 1,
	     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
	     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT)
   ;

  // *********************
  // OUTPUT BOUNDING BOXES
  // *********************

  /**
   * @brief Output a bounding box with coordinates of type <b>int</b>.
   *
   * This is just the implementation of the pure virtual function
   * defined in base class qgar::AbstractGraphicsFile.
   * It just throws an exception as points are not supported by the
   * current VEC format, given by function qgar::VecFile::version.
   *
   * @param aBox        a bounding box
   * @param aThickness  thickness (default <b>1</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline   (default qgar::QGE_OUTLINE_DEFAULT)
   *
   * @exception qgar::QgarErrorDeveloper
   *            bounding boxes not supported by current VEC format
   */
  void write(const BoundingBox& aBox,
	     int        aThickness = 1,
	     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
	     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT)
   ;

  // *****************************
  // OUTPUT (CONNECTED) COMPONENTS
  // *****************************

  /**
   * @brief Output a (connected) component.
   *
   * This is just the implementation of the pure virtual function
   * defined in base class qgar::AbstractGraphicsFile.
   * It just throws an exception as points are not supported by the
   * current VEC format, given by function qgar::VecFile::version.
   *
   * @param aPNode      pointer to the node of the component tree
   *                    including the component
   * @param aThickness  thickness (default <b>1</b>)
   * @param aColor      color     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline   (default qgar::QGE_OUTLINE_DEFAULT)
   *
   * @exception qgar::QgarErrorDeveloper
   *            connected components not supported by current VEC format
   */
  virtual void write(const ConnectedComponents::node_type* const aPNode,
		     int        aThickness = 1,
		     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT)
   ;

  //@}

// -------------------------------------------------------------------

}; // class VecFile




// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// I N L I N E   F U N C T I O N S   I M P L E M E N T A T I O N 
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII


// =========
// ABOUT VEC
// =========


// RETURN THE VEC VERSION SUPPORTED BY QGAR

inline const char* const
VecFile::version() const
{
  return s_vec_version_nb_;
}


// RETURN THE VALUE OF AN UNKNOWN FEATURE

inline double
VecFile::textUnknownFeature() const
{
  return s_vec_text_unknown_;
}


// ====================
// ACCESS FILE FEATURES
// ====================


// GET THE VEC VERSION USED FOR THE CURRENT FILE

inline const char* const
VecFile::fileVersion() const
{
  return fileVersion_;
}


// GET THE MAXIMUM X COORDINATE OF THE PRIMTIVES THE FILE (IMAGE WIDTH)

inline int
VecFile::width() const
{
  return xsize_;
}


// GET THE MAXIMUM Y COORDINATE OF THE PRIMTIVES OF THE FILE (IMAGE HEIGHT)

inline int
VecFile::height() const
{
  return ysize_;
}


// GET THE RESOLUTION OF THE INITIAL IMAGE (DOTS PER INCH)

inline int
VecFile::dpi() const
{
  return dpi_;
}


// IS RESOLUTION KNOWN?

inline bool
VecFile::isDpiKnown() const
{
  return (dpi_ != s_vec_dpi_unknown_);;
}


// IS END OF FILE REACHED?

inline bool
VecFile::eof() const
{
  return eof_flag_;
}


// ==================================
// QUERIES ABOUT LAST INPUT PRIMITIVE
// ==================================


// IS NO PRIMITIVE INPUT YET?

inline bool
VecFile::isNone() const
{
  return (lastPrimitive_ == s_vec_prim_none_);
}


// IS LAST INPUT PRIMITIVE A LINE SEGMENT?

inline bool
VecFile::isSegment() const
{
  return (lastPrimitive_ == s_vec_prim_segment_);
}


// IS LAST INPUT PRIMITIVE A CIRCLE?

inline bool
VecFile::isCircle() const
{
  return (lastPrimitive_ == s_vec_prim_circle_);
}


// IS LAST INPUT PRIMITIVE AN ARC OF CIRCLE?

inline bool
VecFile::isArc() const
{
  return (lastPrimitive_ == s_vec_prim_arc_);
}


// IS LAST INPUT PRIMITIVE A TEXTUAL REGION?

inline bool
VecFile::isText() const
{
  return (lastPrimitive_ == s_vec_prim_text_);
}


// IS FONT HEIGHT KNOWN?

inline bool
VecFile::isFontHeightKnown() const
{
  return (fontHeight_ != s_vec_text_unknown_);
}


// IS FONT WIDTH FACTOR KNOWN?

inline bool
VecFile::isFontWidthFactorKnown() const
{
  return (fontWidthFactor_ != s_vec_text_unknown_);
}


// IS FONT STROKE WIDTH KNOWN?

inline bool
VecFile::isFontStrokeWidthKnown() const
{
  return (fontStrokeWidth_ != s_vec_text_unknown_);
}


// ===========================
// ACCESS LAST INPUT PRIMITIVE
// ===========================


// GET THE TYPE OF THE LAST INPUT PRIMITIVE

inline char
VecFile::lastPrimitive() const
{
  return lastPrimitive_;
}


// GET THE THICKNESS OF THE DRAWING

inline int
VecFile::thickness() const
{
  return thickness_;
}


// GET THE OUTLINE 

inline QGEoutline
VecFile::outline() const
{
  return outline_;
}


// GET THE X COORDINATE OF THE SOURCE POINT
// WHEN THE LAST INPUT PRIMITIVE IS A LINE SEGMENT

inline double
VecFile::xSource() const
{
  return x1_;
}


// GET THE Y COORDINATE OF THE SOURCE POINT
// WHEN THE LAST INPUT PRIMITIVE IS A LINE SEGMENT

inline double
VecFile::ySource() const
{
  return y1_;
}


// GET THE X COORDINATE OF THE TARGET POINT
// WHEN THE LAST INPUT PRIMITIVE IS A LINE SEGMENT

inline double
VecFile::xTarget() const
{
  return x2_;
}


// GET THE Y COORDINATE OF THE TARGET POINT
// WHEN THE LAST INPUT PRIMITIVE IS A LINE SEGMENT

inline double
VecFile::yTarget() const
{
  return y2_;
}


// GET THE X COORDINATE OF THE CENTER POINT
// WHEN THE LAST INPUT PRIMITIVE IS A CIRCLE OR AN ARC OF CIRCLE

inline double
VecFile::xCenter() const
{
  return x1_;
}


// GET THE Y COORDINATE OF THE CENTER POINT
// WHEN THE LAST INPUT PRIMITIVE IS A CIRCLE OR AN ARC OF CIRCLE

inline double
VecFile::yCenter() const
{
  return y1_;
}


// GET THE RADIUS
// WHEN THE LAST INPUT PRIMITIVE IS A CIRCLE OR AN ARC OF CIRCLE

inline double
VecFile::radius() const
{
  return radius_;
}


// GET THE SOURCE (START, IN VEC TERMINOLOGY) ANGLE
// WHEN THE LAST INPUT PRIMITIVE IS AN ARC OF CIRCLE

inline double
VecFile::sourceAngleDegrees() const
{
  return startAngleDegrees_;
}


// GET THE TARGET (END, IN VEC TERMINOLOGY) ANGLE
// WHEN THE LAST INPUT PRIMITIVE IS AN ARC OF CIRCLE

inline double
VecFile::targetAngleDegrees() const
{
  return endAngleDegrees_;
}


// GET THE X COORDINATE OF THE FIRST CORNER
// WHEN THE LAST INPUT PRIMITIVE IS A TEXTUAL REGION

inline double
VecFile::xCorner1() const
{
  return x1_;
}


// GET THE Y COORDINATE OF THE FIRST CORNER
// WHEN THE LAST INPUT PRIMITIVE IS A TEXTUAL REGION

inline double
VecFile::yCorner1() const
{
  return y1_;
}


// GET THE X COORDINATE OF THE SECOND CORNER
// WHEN THE LAST INPUT PRIMITIVE IS A TEXTUAL REGION

inline double
VecFile::xCorner2() const
{
  return x2_;
}


// GET THE Y COORDINATE OF THE SECOND CORNER
// WHEN THE LAST INPUT PRIMITIVE IS A TEXTUAL REGION

inline double
VecFile::yCorner2() const
{
  return y2_;
}


// GET THE ORIENTATION
// WHEN THE LAST INPUT PRIMITIVE IS A TEXTUAL REGION

inline double
VecFile::orientationDegrees() const
{
  return orientationDegrees_;
}


// GET THE FONT HEIGHT
// WHEN THE LAST INPUT PRIMITIVE IS A TEXTUAL REGION

inline double
VecFile::fontHeight() const
{
  return fontHeight_;
}


// GET THE FONT WIDTH FACTOR
// WHEN THE LAST INPUT PRIMITIVE IS A TEXTUAL REGION

inline double
VecFile::fontWidthFactor() const
{
  return fontWidthFactor_;
}


// GET THE FONT STROKE WIDTH
// WHEN THE LAST INPUT PRIMITIVE IS A TEXTUAL REGION

inline double
VecFile::fontStrokeWidth() const
{
  return fontStrokeWidth_;
}


// GET THE TEXT (POSSIBLY BLANK)
// WHEN THE LAST INPUT PRIMITIVE IS A TEXTUAL REGION

inline const char*
VecFile::text() const
{
  return text_;
}


// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII


} // namespace qgar


#endif /* __VECFILE_H_INCLUDED__ */
