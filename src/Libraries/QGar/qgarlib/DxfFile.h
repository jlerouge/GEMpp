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


#ifndef __DXFFILE_H_INCLUDED__
#define __DXFFILE_H_INCLUDED__


/**
 * @file DxfFile.h
 *
 * @brief Header file of class qgar::DxfFile.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date   Jul, 3  2001  16:15
 * @since  Qgar 1.0
 */


// For RCS/CVS use: Do not delete
/* $Id: DxfFile.h,v 1.39 2007/02/14 17:34:04 masini Exp $ */


// STD
#include <algorithm>
#include <list>
// QGAR
#include "AbstractGraphicsFile.h"
#include "ConnectedComponents.h"
#include "GenPointChain.h"
#include "primitives.h"
#include "QgarErrorDeveloper.h"
#include "QgarErrorIO.h"
#include "stl.h"
namespace qgar
{
  // Avoid #include's when not necessary
  class BoundingBox;
  template <class T> class AbstractGenPointChain;
}



using namespace std;



namespace qgar
{


/**
 * @ingroup IO_FILE
 *
 * @class DxfFile DxfFile.h "qgarlib/DxfFile.h"
 *
 * @brief File including Dxf graphics.
 *
 * @warning
 * To enable access to the primitives contained in a DXF file,
 * function qgar::DxfFile::read(bool) must first be called on the file:
@verbatim
  #include <algorithm>
  #include <list>

  #include "DxfFile.h"
  #include "primitives.h"
  #include "stl.h"

  using namespace qgar;
  using namespace std;

  ...

  // Open an existing DXF file
  dxfFile.openRONLY();

  // Read the primitives contained in the file
  dxfFile.read();

  // Close the file when useless
  dxfFile.close();

  // Get and use primitives...
  ...
  list<GenQgarSegment<int>*> qgarSegList;
  dxfFile.segments(qgarSegList);
  ...

  // Delete primitives when useless
  for_each(qgarSegList.begin(), qgarSegList.end(), qstlDeleteObject());
  ...
@endverbatim
 *
 * @todo
 * <ul>
 * <li>The code in .cpp file has to be completely revised (and optimized).</li>
 * <li>Implement a member function to write a (connected) component:
 *     qgar::DxfFile::write(const Component&, int, QGEcolor, QGEoutline).</li>
 * </ul>
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date   July, 3  2001  16:15
 * @since  Qgar 1.0
 */
class DxfFile

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
   * @brief Initialize with given file name.
   *
   * @param aFileName name of the file
   */
  explicit DxfFile(const char* aFileName);

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  virtual ~DxfFile();

  //@}


  /** @name Image size */
  //        ==========
  //@{

  /**
   * @brief Get the maximal X coordinate of the image.
   */
  inline int sizeX() const;

  /**
   * @brief Get the maximal Y coordinate of the image.
   */
  inline int sizeY() const;

  //@}


  /** @name Header */
  //        ======
  //@{

  /**
   * @brief Read the header of a DXF file.
   *
   * @warning To be used only with DXF files created by Qgar.
   *
   * @exception qgar::QgarErrorIO  bad header
   */
  void readHeader();

  /**
   * @brief Write the header of a DXF file.
   */
  void writeHeader();

  //@}


  /** @name Footer */
  //        ======
  //@{

  /**
   * @brief Write the footer of a DXF file.
   */
  void writeFooter();

  //@}


  /** @name Access to the primitives of the file */
  //        ====================================
  //@{

  /**
   * @brief Get the chains of points contained in the file.
   */
  inline const list<GenPointChain<int>*>&
  accessChains() const;

  /**
   * @brief Get a copy of the chains of points contained in the file.
   *
   * The available chains are <b>appended</b> to the given list.
   *
   * @param aChainList  list to store the chains
   *
   * @warning
   * <ul>
   * <li>Chains are not available if function
   *     qgar::DxfFile::read(bool) has not been called previously.</li>
   * <li>The chains should be explicitely deleted once useless.</li>
   * </ul>
   */
  inline void
  chains(list<GenPointChain<int>*>& aChainList) const;

  /**
   * @brief Get the (Qgar) segments contained in the file.
   */
  inline const list<GenQgarSegment<int>*>&
  accessSegments() const;

  /**
   * @brief Get a copy of the (Qgar) segments contained in the file.
   *
   * The available segments are <b>appended</b> to the given list.
   *
   * @param aQSegList  list to store the (Qgar) segments
   *
   * @warning
   * <ul>
   * <li>Segments are not available if function
   *     qgar::DxfFile::read(bool) has not been called previously.</li>
   * <li>The segments should be explicitely deleted once useless.</li>
   * </ul>
   */
  inline void
  segments(list<GenQgarSegment<int>*>& aQSegList) const;

  /**
   * @brief Get the (Qgar) arcs contained in the file.
   */
  inline const list<GenQgarArc<int>*>&
  accessArcs() const;

  /**
   * @brief Get a copy of the (Qgar) arcs contained in the file.
   *
   * The available arcs are <b>appended</b> to the given list.
   *
   * @param aQArcList  list to store the (Qgar) arcs
   *
   * @warning
   * <ul>
   * <li>Arcs are not available if function
   *     qgar::DxfFile::read(bool) has not been called previously.</li>
   * <li>The arcs should be explicitely deleted once useless.</li>
   * </ul>
   */
  inline void
  arcs(list<GenQgarArc<int>*>& aQArcList) const;

  /**
   * @brief Get the (Qgar) polylines contained in the file.
   */
  inline const list<GenQgarPolyline<int>*>&
  accessPolylines() const;

  /**
   * @brief Get a copy of the (Qgar) polylines contained in the file.
   *
   * The available polylines are <b>appended</b> to the given list.
   *
   * @param aQPolylineList  list to store the (Qgar) polylines
   *
   * @warning
   * <ul>
   * <li>Polylines are not available if function
   *     qgar::DxfFile::read(bool) has not been called previously.</li>
   * <li>The polylines should be explicitely deleted once useless.</li>
   * </ul>
   */
  inline void
  polylines(list<GenQgarPolyline<int>*>& aQPolylineList) const;

  //@}


  /** @name Buffered input */
  //        ==============
  //@{

  /**
   * @brief Read all DXF entities contained in the file.
   *
   * The DXF entities are transformed into (Qgar) primitives
   * and are stored in the internal buffers of the file.
   *
   * @param convertPolylines  convert polylines into segments (default <b>true</b>)
   *
   * @exception qgar::QgarErrorIO  junk in file
   */
  void read(bool convertPolylines = true);

  //@}


// -------------------------------------------------------------------
// P U B L I C    M E M B E R S :   O U T P U T
// -------------------------------------------------------------------
public:


  /** @name Output chains of points */
  //        =======================
  //@{

  /**
   * @brief Write a chain of points with coordinates of type <b>int</b>.
   *
   * @param aChain      a chain
   * @param aThickness  thickness of the drawing (default <b>3</b>
   * @param aColor      color of the drawing     (default qgar::QGE_COLOR_DEFAULT)
   */
  virtual void write(AbstractGenPointChain<int>& aChain,
		     int aThickness  = 3,
		     QGEcolor aColor = QGE_COLOR_DEFAULT);

  /**
   * @brief Write a chain of points with coordinates of type <b>float</b>.
   *
   * @param aChain      a chain
   * @param aThickness  thickness of the drawing (default <b>3</b>
   * @param aColor      color of the drawing     (default qgar::QGE_COLOR_DEFAULT)
   */
  virtual void write(AbstractGenPointChain<float>& aChain,
		     int aThickness  = 3,
		     QGEcolor aColor = QGE_COLOR_DEFAULT);

  /**
   * @brief Write a chain of points with coordinates of type <b>double</b>.
   *
   * @param aChain      a chain
   * @param aThickness  thickness of the drawing (default <b>3</b>
   * @param aColor      color of the drawing     (default qgar::QGE_COLOR_DEFAULT)
   */
  virtual void write(AbstractGenPointChain<double>& aChain,
		     int aThickness  = 3,
		     QGEcolor aColor = QGE_COLOR_DEFAULT);

  //@}


  /** @name Output line segments */
  //        ====================
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
		     int aThickness       = 1,
		     QGEcolor aColor      = QGE_COLOR_BLACK,
		     QGEoutline anOutline = QGE_OUTLINE_DEFAULT);

  /**
   * @brief Write a segment with coordinates of type <b>double</b>.
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

  /**
   * @brief Write a list of Qgar segments with integer coordinates.
   *
   * @param aQSegList   a list of Qgar segments
   * @param aThickness  thickne/ss of the drawing (default <b>1</b>)
   * @param aColor      color of the drawing     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline of the drawing   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  void write(const list<GenQgarSegment<int>*>& aQSegList,
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

  /**
   * @brief Write a list of Qgar arcs with integer coordinates.
   *
   * @param aQArcList  a list of Qgar arcs
   * @param aThickness thickness of the drawing (default <b>1</b>)
   * @param aColor     color of the drawing     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline  outline of the drawing   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  void write(list<GenQgarArc<int>*>& aQArcList,
	     int        aThickness = 1,
	     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
	     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  //@}


  /** @name Output polylines */
  //        ================
  //@{

  /**
   * @brief Write a geometrical polyline with coordinates of type <b>int</b>.
   *
   * @param aPoly      a polyline
   * @param aThickness thickness of the drawing (default <b>1</b>)
   * @param aColor     color of the drawing     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline  outline of the drawing   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  void write(const GenPolyline<int>& aPoly,
	     int        aThickness = 1,
	     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
	     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  /**
   * @brief Write a geometrical polyline with coordinates of type <b>float</b>.
   *
   * @param aPoly      a polyline
   * @param aThickness thickness of the drawing (default <b>1</b>)
   * @param aColor     color of the drawing     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline  outline of the drawing   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  void write(const GenPolyline<float>& aPoly,
	     int        aThickness = 1,
	     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
	     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  /**
   * @brief Write a geometrical polyline with coordinates of type
   * <b>double</b>.
   *
   * @param aPoly      a polyline
   * @param aThickness thickness of the drawing (default <b>1</b>)
   * @param aColor     color of the drawing     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline  outline of the drawing   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  void write(const GenPolyline<double>& aPoly,
	     int        aThickness = 1,
	     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
	     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  //@}


  /** @name Output polygons */
  //        ===============
  //@{

  /**
   * @brief Write a polygon.
   *
   * @param aPolygon    a polygon 
   * @param aThickness  thickness of the drawing (default <b>1</b>)
   * @param aColor      color of the drawing     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline of the drawing   (default qgar::QGE_OUTLINE_DEFAULT)
   */
  void write(GenPolygon<int>* aPolygon,
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
  void write(const BoundingBox& aBox,
	     int        aThickness = 1,
	     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
	     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

  //@}


//  //  /** @name Output Qgar primitives */
//  //            ======================
//  //@{
//
//  /**
//   * @brief Write a list of Qgar primitives with integer coordinates.
//   *
//   * @param aQPrimList a list of Qgar primitives
//   * @param aThickness thickness of the drawing (default <b>1</b>)
//   * @param aColor     color of the drawing     (default qgar::QGE_COLOR_DEFAULT)
//   * @param anOutline  outline of the drawing   (default qgar::QGE_OUTLINE_DEFAULT)
//   */
//  void write(list<AbstractGenQgarPrimitive<int>*>& aQPrimList,
//	     int        aThickness = 1,
//	     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
//	     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);
//
//   //@}


  /** @name Output texts */
  //        ============
  //@{

  /**
   * @brief Write a text.
   *
   * @param aText    a text
   * @param aX       X coordinate of the top left corner of the box bounding the text
   * @param aY       Y coordinate of the top left corner of the box bounding the text
   * @param aHeight  font size of the text
   * @param aColor   color of the text (default qgar::QGE_COLOR_DEFAULT)
   */
  void write(const char* aText,
	     int aX,
	     int aY,
	     int aHeight,
	     QGEcolor aColor = QGE_COLOR_DEFAULT);

  //@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /** @name DXF Colors */
  //        ==========
  //@{

  /**
   * @brief Table to convert Qgar colors into DXF colors.
   *
   * <table cellpadding="2" cellspacing="1">
   * <tr><td><b>Qgar color</b>                </td><td><b>DXF color</b></td></tr>
   * <tr><td>qgar::QGE_COLOR_NONE             </td><td>black           </td></tr>
   * <tr><td>qgar::QGE_COLOR_DEFAULT          </td><td>black           </td></tr>
   * <tr><td>qgar::QGE_COLOR_BLACK            </td><td>black           </td></tr>
   * <tr><td>qgar::QGE_COLOR_DARK_GRAY        </td><td>gray            </td></tr>
   * <tr><td>qgar::QGE_COLOR_GRAY             </td><td>gray            </td></tr>
   * <tr><td>qgar::QGE_COLOR_LIGHT_GRAY       </td><td>gray            </td></tr>
   * <tr><td>qgar::QGE_COLOR_WHITE            </td><td>white           </td></tr>
   * <tr><td>qgar::QGE_COLOR_MAGENTA          </td><td>magenta         </td></tr>
   * <tr><td>qgar::QGE_COLOR_PURPLE           </td><td>magenta         </td></tr>
   * <tr><td>qgar::QGE_COLOR_CYAN             </td><td>cyan            </td></tr>
   * <tr><td>qgar::QGE_COLOR_MEDIUM_BLUE      </td><td>blue            </td></tr>
   * <tr><td>qgar::QGE_COLOR_BLUE             </td><td>blue            </td></tr>
   * <tr><td>qgar::QGE_COLOR_OLIVE_GREEN      </td><td>green           </td></tr>
   * <tr><td>qgar::QGE_COLOR_DARK_GREEN       </td><td>green           </td></tr>
   * <tr><td>qgar::QGE_COLOR_GREEN            </td><td>green           </td></tr>
   * <tr><td>qgar::QGE_COLOR_YELLOW           </td><td>yellow          </td></tr>
   * <tr><td>qgar::QGE_COLOR_ORANGE           </td><td>red             </td></tr>
   * <tr><td>qgar::QGE_COLOR_RED              </td><td>red             </td></tr>
   * <tr><td>qgar::QGE_COLOR_PINK             </td><td>red             </td></tr>
   * <tr><td>qgar::QGE_COLOR_SALMON_PINK      </td><td>red             </td></tr>
   * <tr><td>qgar::QGE_COLOR_BROWN            </td><td>black           </td></tr>
   * <tr><td>qgar::QGE_COLOR_CHOCOLATE_BROWN  </td><td>black           </td></tr>
   * </table>
   */
  static const int _s_dxf_colors[22];

  //@}


  /** @name DXF codes */
  //        =========
  //@{

  /** @brief Comment (999)                      */ static const int _s_dxf_code_com;
  /** @brief Identifier (0)                     */ static const int _s_dxf_code_ident;
  /** @brief Name (2)                           */ static const int _s_dxf_code_name;
  /** @brief Color (62)                         */ static const int _s_dxf_code_color;
  /** @brief X1 (10)                            */ static const int _s_dxf_code_x1;
  /** @brief X2 (11)                            */ static const int _s_dxf_code_x2;
  /** @brief Y1 (20)                            */ static const int _s_dxf_code_y1;
  /** @brief Y2 (21)                            */ static const int _s_dxf_code_y2;
  /** @brief Thickness (39)                     */ static const int _s_dxf_code_thick;
  /** @brief Radius / total pattern length (40) */ static const int _s_dxf_code_radius;
  /** @brief Start angle (50)                   */ static const int _s_dxf_code_start;
  /** @brief End angle (51)                     */ static const int _s_dxf_code_end;
  /** @brief Standard flag value (70)           */ static const int _s_dxf_code_flag;
  /** @brief Descriptive text for linetype (3)  */ static const int _s_dxf_code_lintp;
  /** @brief Alignment code (72)                */ static const int _s_dxf_code_algt;
  /** @brief Number of dash length items (73)   */ static const int _s_dxf_code_dash;
  /** @brief Ltype name (6)                     */ static const int _s_dxf_code_ltp;
  /** @brief Layer name (8)                     */ static const int _s_dxf_code_layer;
  /** @brief Elevation (38)                     */ static const int _s_dxf_code_elev;
  /** @brief Vertices flag (66)                 */ static const int _s_dxf_code_vertflag;
  /** @brief Text height (40)                   */ static const int _s_dxf_code_txthght;
  /** @brief Text value (1)                     */ static const int _s_dxf_code_txt;

  //@}


  /** @name DXF TAGS */
  //        ========
  //@{

  /** @brief SECTION     */ static const char* const _s_dxf_tag_sec;
  /** @brief TABLES      */ static const char* const _s_dxf_tag_tbs;
  /** @brief TABLE       */ static const char* const _s_dxf_tag_tbl;
  /** @brief LAYER       */ static const char* const _s_dxf_tag_layer;
  /** @brief LTYPE       */ static const char* const _s_dxf_tag_ltp;
  /** @brief ENTITIES    */ static const char* const _s_dxf_tag_ent;
  /** @brief ARC         */ static const char* const _s_dxf_tag_arc;
  /** @brief LINE        */ static const char* const _s_dxf_tag_seg;
  /** @brief POLYLINE    */ static const char* const _s_dxf_tag_polyl;
  /** @brief VERTEX      */ static const char* const _s_dxf_tag_vert;
  /** @brief EOF         */ static const char* const _s_dxf_tag_eof;
  /** @brief ENDSEC      */ static const char* const _s_dxf_tag_end;
  /** @brief ENDTAB      */ static const char* const _s_dxf_tag_etb;
  /** @brief SEQEND      */ static const char* const _s_dxf_tag_esq;
  /** @brief TEXT        */ static const char* const _s_dxf_tag_txt;

  //@}


  /** @name DXF comments */
  //        ============
  //@{

  /** @brief Created by Qgar on    */ static const char* const _s_dxf_com_create;
  /** @brief Definitions           */ static const char* const _s_dxf_com_def;
  /** @brief Linetype definitions  */ static const char* const _s_dxf_com_ltp;
  /** @brief Layer definitions     */ static const char* const _s_dxf_com_layer;
  /** @brief Entities              */ static const char* const _s_dxf_com_ent;
  /** @brief Segment               */ static const char* const _s_dxf_com_seg;
  /** @brief Arc                   */ static const char* const _s_dxf_com_arc;
  /** @brief Dividing wall         */ static const char* const _s_dxf_com_dwall;
  /** @brief Bearing wall          */ static const char* const _s_dxf_com_bwall;
  /** @brief Simple window         */ static const char* const _s_dxf_com_swind;
  /** @brief Double window         */ static const char* const _s_dxf_com_dwind;
  /** @brief Door                  */ static const char* const _s_dxf_com_door;
  /** @brief Stairs                */ static const char* const _s_dxf_com_stairs;
  /** @brief Pipe                  */ static const char* const _s_dxf_com_pipe;
  /** @brief Chaine                */ static const char* const _s_dxf_com_chain;
  /** @brief Polyline              */ static const char* const _s_dxf_com_polyl;
  /** @brief Texte                 */ static const char* const _s_dxf_com_txt;

  //@}


  /** @name DXF defaults */
  //        ============
  //@{

  /** @brief Linetype for contnuous lines (CONTINUOUS") */ static const char*  const _s_dxf_default_cont;
  /** @brief Linetype for dashed lines (DASHED)         */ static const char*  const _s_dxf_default_dash;
  /** @brief Descriptive for LTYPE (----)               */ static const char*  const _s_dxf_default_dltp;
  /** @brief Number of LTYPE (1)                        */ static const int    _s_dxf_default_ltp;
  /** @brief Flag value for LAYER (2)                   */ static const int    _s_dxf_default_fly;
  /** @brief Number of LAYERS (8)                       */ static const int    _s_dxf_default_layer;
  /** @brief Flag value for LTYPE (64)                  */ static const int    _s_dxf_default_flt;
  /** @brief Aligment value for LTYPE (65)              */ static const int    _s_dxf_default_alg;
  /** @brief Dash length for continuous lines (0)       */ static const int    _s_dxf_default_dash1;
  /** @brief Dash length for dashed lines (2)           */ static const int    _s_dxf_default_dash2;
  /** @brief Length pattern for continuous lines (0.0)  */ static const double _s_dxf_default_pat1;
  /** @brief Length pattern for dashed lines (2.0)      */ static const double _s_dxf_default_pat2;
  /** @brief Default width for POLYLINE (1)             */ static const int    _s_dxf_default_wpo;
  /** @brief Vertices follow POLYLINE definition (1)    */ static const int    _s_dxf_default_vfg;
  /** @brief Polylines are opened (0)                   */ static const int    _s_dxf_default_pfgo;
  /** @brief Polylines are closed (1)                   */ static const int    _s_dxf_default_pfgc;

  //@}


  /** @name DXF layers */
  //        ==========
  //@{

  /** @brief PRIMITIVE  */ static const char* const _s_dxf_layer_prm;
  /** @brief DIVWALL    */ static const char* const _s_dxf_layer_dwall;
  /** @brief BEARWALL   */ static const char* const _s_dxf_layer_bwall;
  /** @brief SIMWINDOW  */ static const char* const _s_dxf_layer_swind;
  /** @brief DOUWINDOW  */ static const char* const _s_dxf_layer_dwind;
  /** @brief DOOR       */ static const char* const _s_dxf_layer_door;
  /** @brief STAIRS     */ static const char* const _s_dxf_layer_stairs;
  /** @brief PIPE       */ static const char* const _s_dxf_layer_pipe;
  /** @brief CHAINE     */ static const char* const _s_dxf_layer_chain;
  /** @brief POLYLINE   */ static const char* const _s_dxf_layer_polyl;
  /** @brief TEXT       */ static const char* const _s_dxf_layer_txt;

  //@}


  /** @name DXF features */
  //        ============
  //@{

  /**
   * @brief Maximum length of a DXF field (<b>256</b>).
   */
  static const unsigned int _s_dxf_maxbuf;

  //@}


  /** @name Image size */
  //        ==========
  //@{

  /**
   * @brief Maximal X coordinate.
   */
  int _maxX;

  /**
   * @brief Maximal Y coordinate.
   */
  int _maxY;

  //@}


  /** @name Last group read */
  //        ===============
  //@{

  /**
   * @brief Code of last group read.
   */
  int _lastGroupCode;

  /**
   * @brief Value of last group read.
   */
  char* _lastGroup;

  //@}


  /** @name Buffers to store primitives contained in the file */
  //        =================================================
  //@{

  /**
   * @brief Segments contained in the file.
   */
  list<GenQgarSegment<int>*> _segmentList;

  /**
   * @brief Arcs contained in the file.
   */
  list<GenQgarArc<int>*> _arcList;

  /**
   * @brief Chains of points contained in the file.
   */
  list<GenPointChain<int>*> _chainList;

  /**
   * @brief Polylines contained in the file.
   */
  list<GenQgarPolyline<int>*> _polylineList;

  //@}


  /** @name Save DXF entities in the file */
  //        =============================
  //@{

  /**
   * @brief Save a DXF group into the file.
   *
   * @param aCode
   * @param aGroup
   */
  template <class T>
  void
  saveDxfGroup(int aCode, const T aGroup);

  /**
   * @brief Save a DXF layer into the file.
   *
   * @param aName
   * @param aFlag
   * @param aColor
   * @param aLType
   */
  void saveDxfLayer(const char* aName,
		    int         aFlag,
		    int         aColor,
		    const char* aLType);

  /**
   * @brief Save DXF features into the file.
   *
   * @param aLayer
   * @param aThickness  thickness of the drawing
   * @param aColor      color of the drawing
   * @param isDashed    (default <b>false</b>)
   */
  void saveDxfFeatures(const char* aLayer,
		       int         aThickness,
		       QGEcolor    aColor,
		       bool        isDashed);

  //@}


  /** @name Save primitives in the file */
  //        ===========================
  //@{

  /**
   * @brief Save a chain of points.
   *
   * @param aChain     a chain
   * @param aThickness thickness of the drawing
   * @param aColor     color of the drawing
   */
  template <class T>
  void
  saveChain(AbstractGenPointChain<T>& aChain,
	    int aThickness,
	    QGEcolor aColor);

  /**
   * @brief Save a segment with <b>integer</b> coordinates.
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
   * @brief Save an arc with <b>integer</b> coordinates.
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
   * @brief Save a polyline.
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
   * @brief Save a bounding box.
   *
   * @param aXTopLeft      X coordinate of top left corner
   * @param aYTopLeft      Y coordinate of top left corner
   * @param aXBottomRight  X coordinate of bottom right corner
   * @param aYBottomRight  Y coordinate of bottom right corner
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


  /** @name Retrieve DXF entities from the file */
  //        ===================================
  //@{

  /**
   * @brief Retrieve a DXF Group from the file.
   *
   * Return the code of the group which has been retrieved, and store
   * the corresponding value in the qgar::DxfFile::lastGroup
   * data member as a chain of characters.
   * Comments are ignored.
   */
  int retrieveDxfGroup();

  //@}


  /** @name Retrieve a primitive from the file and append it to a list */
  //        ==========================================================
  //@{

  /**
   * @brief Retrieve a (Qgar) segment from the file.
   *
   * The segment is added to the end of the given list.
   *
   * @param aQSegList list to store the segment
   *
   * @exception qgar::QgarErrorIO  junk in file
   */
  void
  retrieveQgarSegment(list<GenQgarSegment<int>*>& aQSegList)
   ;

  /**
   * @brief Retrieve a (Qgar) arc from the file.
   *
   * The arc is added to the end of the given list.
   *
   * @param aQArcList list to store the arc that is read
   *
   * @exception qgar::QgarErrorIO  junk in file
   */
  void retrieveQgarArc(list<GenQgarArc<int>*>& aQArcList)
   ;

  /**
   * @brief Retrieve a chain of points or a (Qgar) polyline
   *   from the file.
   *
   * @param aChainList  when the entity is a chain,
   *                    it is added to the end of this list
   * @param aQPolyList  when the entity is a polyline,
   *                    it is added to the end of this list
   *
   * @exception qgar::QgarErrorIO  junk in file
   */
  void
  retrieveChainOrQgarPolyline(list<GenPointChain<int>*>& aChainList,
			      list<GenQgarPolyline<int>*>& aQPolyList)
   ;

  /**
   * @brief Retrieve points (vertices of a polyline) from the file.
   *
   * @param aPointList   list to store the vertices of the polyline
   * @param aThickness   only significant when the function is called
   *                     to construct a Qgar polyline
   * @param isDashed
   */
  void retrievePoints(list<Point>& aPointList,
		      int* aThickness,
		      bool* isDashed);
  //@}


  /** @name Get a pointer to a primitive of the file */
  //        ========================================
  //@{

  /**
   * @brief Get a pointer to a (Qgar) segment from the file.
   */
  GenQgarSegment<int>* retrievePQgarSegment();

  /**
   * @brief Get a pointer to a (Qgar) arc from the file.
   */
  GenQgarArc<int>* retrievePQgarArc();

  /**
   * @brief Get a pointer to a (Qgar) polyline from the file.
   */
  GenQgarPolyline<int>* retrievePQgarPolyline();

  /**
   * @brief Get a pointer to a chain of points from the file.
   */
  GenPointChain<int>* retrievePChain();

  //@}


// ---------------------------------------------------------------------
// P R I V A T E    F U N C T I O N S
// ---------------------------------------------------------------------
private:

  //  ============================================================
  /** @name Not yet implemented
      These functions belong to the private section
      as they are not yet implemented and thus should not be used.
  */
  //  ============================================================
  //@{

  // *************
  // OUTPUT POINTS
  // *************

  /**
   * @brief Write a point with coordinates of type <b>int</b>.
   *
   * @param aX          X coordinate of the point
   * @param aY          Y coordinate of the point
   * @param aThickness  thickness of the drawing (default <b>3</b>)
   * @param aColor      color of the drawing     (default qgar::QGE_COLOR_DEFAULT)
   *
   * @warning Not yet implemented.
   *
   * @exception qgar::QgarErrorDeveloper  not yet implemented
   *
   * @todo To be implemented!
   */
  void write(int aX,
	     int aY,
	     int aThickness  = 3,
	     QGEcolor aColor = QGE_COLOR_DEFAULT)
   ;

  /**
   * @brief Write a point with coordinates of type <b>float</b>.
   *
   * @param aX          X coordinate of the point
   * @param aY          Y coordinate of the point
   * @param aThickness  thickness of the drawing (default <b>3</b>)
   * @param aColor      color of the drawing     (default qgar::QGE_COLOR_DEFAULT)
   *
   * @warning Not yet implemented.
   *
   * @exception qgar::QgarErrorDeveloper  not yet implemented
   *
   * @todo To be implemented!
   */
  void write(float aX,
	     float aY,
	     int aThickness    = 3,
	     QGEcolor aColor = QGE_COLOR_DEFAULT)
   ;

  /**
   * @brief Write a point with coordinates of type <b>double</b>.
   *
   * @param aX          X coordinate of the point
   * @param aY          Y coordinate of the point
   * @param aThickness  thickness of the drawing (default <b>3</b>)
   * @param aColor      color of the drawing     (default qgar::QGE_COLOR_DEFAULT)
   *
   * @warning Not yet implemented.
   *
   * @exception qgar::QgarErrorDeveloper  not yet implemented
   *
   * @todo To be implemented!
   */
  void write(double aX,
	     double aY,
	     int aThickness  = 3,
	     QGEcolor aColor = QGE_COLOR_DEFAULT)
   ;


  // **************
  // Output circles
  // **************

  /**
   * @brief Write a circle with coordinates of type <b>int</b>.
   *
   * @param aXCenter    X coordinate of the center
   * @param aYCenter    Y coordinate of the center
   * @param aRadius     radius of the circle
   * @param aThickness  thickness of the drawing (default <b>1</b>)
   * @param aColor      color of the drawing     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline of the drawing   (default qgar::QGE_OUTLINE_DEFAULT)
   *
   * @warning Not yet implemented.
   *
   * @exception qgar::QgarErrorDeveloper  not yet implemented
   *
   * @todo To be implemented!
   */
  virtual void write(int aXCenter,
		     int aYCenter,
		     double aRadius,
		     int        aThickness = 1,
		     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT)
   ;

  /**
   * @brief Write a circle with coordinates of type <b>float</b>.
   *
   * @param aXCenter    X coordinate of the center
   * @param aYCenter    Y coordinate of the center
   * @param aRadius    radius of the circle
   * @param aThickness thickness of the drawing (default <b>1</b>)
   * @param aColor     color of the drawing     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline  outline of the drawing   (default qgar::QGE_OUTLINE_DEFAULT)
   *
   * @warning Not yet implemented.
   *
   * @exception qgar::QgarErrorDeveloper  not yet implemented
   *
   * @todo To be implemented!
   */
  virtual void write(float aXCenter,
		     float aYCenter,
		     double aRadius,
		     int        aThickness = 1,
		     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT)
   ;

  /**
   * @brief Write a circle with coordinates of type <b>double</b>.
   *
   * @param aXCenter    X coordinate of the center
   * @param aYCenter    Y coordinate of the center
   * @param aRadius    radius of the circle
   * @param aThickness thickness of the drawing (default <b>1</b>)
   * @param aColor     color of the drawing     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline  outline of the drawing   (default qgar::QGE_OUTLINE_DEFAULT)
   *
   * @warning Not yet implemented.
   *
   * @exception qgar::QgarErrorDeveloper  not yet implemented
   *
   * @todo To be implemented!
   */
  virtual void write(double aXCenter,
		     double aYCenter,
		     double aRadius,
		     int        aThickness = 1,
		     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT)
   ;


  // *****************************
  // OUTPUT (CONNECTED) COMPONENTS
  // *****************************

  /**
   * @brief Write a (connected) component.
   *
   * A component is represented by its contour and the contours
   * of included components.
   *
   * @param aPNode      pointer to the node of the component tree
   *                    including the component
   * @param aThickness  thickness of the drawing (default <b>1</b>)
   * @param aColor      color of the drawing     (default qgar::QGE_COLOR_DEFAULT)
   * @param anOutline   outline of the drawing   (default qgar::QGE_OUTLINE_DEFAULT)
   *
   * @warning Not yet implemented.
   *
   * @exception qgar::QgarErrorDeveloper  not yet implemented
   *
   * @todo To be implemented!
   */
  virtual void write(const ConnectedComponents::node_type* const aPNode,
		     int        aThickness = 1,
		     QGEcolor   aColor     = QGE_COLOR_DEFAULT,
		     QGEoutline anOutline  = QGE_OUTLINE_DEFAULT)
   ;

  //@}



// -------------------------------------------------------------------

}; // class DxfFile




// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// T E M P L A T E   I M P L E M E N T A T I O N 
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


// ============================================
// AUXILIARIES: SAVE DXF ENTITIES INTO THE FILE
// ============================================


// SAVE A DXF GROUP

template <class T>
void
DxfFile::saveDxfGroup(int aCode, const T aGroup)
{
  char buf[4];

  sprintf(buf, "%3d", aCode);
  fstream_ << buf
	   << endl
	   << aGroup
	   << endl;
}


// ========================================
// AUXILIARIES: SAVE PRIMITIVES IN THE FILE
// ========================================


// SAVE A CHAIN OF POINTS WITH COORDINATES OF TYPE 'T'


template <class T>
void
DxfFile::saveChain(AbstractGenPointChain<T>& aChain,
		   int aThickness,
		   QGEcolor aColor)
{
  // 1 - Header of the polyline

  saveDxfGroup(_s_dxf_code_com,   _s_dxf_com_chain);
  saveDxfGroup(_s_dxf_code_ident, _s_dxf_tag_polyl);

  saveDxfFeatures(_s_dxf_layer_chain,
		  aThickness,
		  aColor,
		  false);

  saveDxfGroup(_s_dxf_code_vertflag, _s_dxf_default_vfg);
  saveDxfGroup(_s_dxf_code_flag,     _s_dxf_default_pfgo);

  // 2 - Vertices of the polyline

  aChain.setToBegin();

  while (!aChain.isAtEnd())
    {
      const GenPoint<T>& currPoint = aChain.accessCurrent();

      saveDxfGroup(_s_dxf_code_ident, _s_dxf_tag_vert);
      saveDxfGroup(_s_dxf_code_x1, (int) currPoint.x());
      saveDxfGroup(_s_dxf_code_y1, (int) currPoint.y());

      aChain.moveNext();
    }

  // 3 - Footer of the polyline

  saveDxfGroup(_s_dxf_code_ident, _s_dxf_tag_esq);
}


// SAVE A POLYLINE


template <class T>
void
DxfFile::savePolyline(const GenPolyline<T>& aPoly,
		      int aThickness,
		      QGEcolor aColor,
		      QGEoutline anOutline)
{
  // 1 - Header of the polyline

  saveDxfGroup(_s_dxf_code_com,   _s_dxf_com_polyl);
  saveDxfGroup(_s_dxf_code_ident, _s_dxf_tag_polyl);

  saveDxfFeatures(_s_dxf_layer_polyl,
		  aThickness,
		  aColor,
		  anOutline != QGE_OUTLINE_SOLID);

  saveDxfGroup(_s_dxf_code_vertflag, _s_dxf_default_vfg);
  saveDxfGroup(_s_dxf_code_flag,     _s_dxf_default_pfgo);

  // 2 - Vertices of the polyline

  deque< GenPoint<T> > pointList = aPoly.accessVertices();

  for (typename deque< GenPoint<T> >::iterator ptListIter = pointList.begin();
       ptListIter != pointList.end();
       ++ptListIter)
    {
      saveDxfGroup(_s_dxf_code_ident, _s_dxf_tag_vert);
      saveDxfGroup(_s_dxf_code_x1, (int) (*ptListIter).x());
      saveDxfGroup(_s_dxf_code_y1, (int) (*ptListIter).y());
    }

  // 3 - Footer of the polyline

  saveDxfGroup(_s_dxf_code_ident, _s_dxf_tag_esq);
}


// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// END OF TEMPLATE IMPLEMENTATION
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT




// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// I N L I N E   F U N C T I O N S   I M P L E M E N T A T I O N 
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII


// ==========
// IMAGE SIZE
// ==========


// GET THE MAXIMAL X COORDINATE OF THE IMAGE

inline int
DxfFile::sizeX() const
{
  return _maxX;
}


// GET THE MAXIMAL Y COORDINATE OF THE IMAGE

inline int
DxfFile::sizeY() const
{
  return _maxY;
}


// ================================
// ACCESS TO PRIMITIVES OF THE FILE
// ================================


// GET THE CHAINS OF POINTS CONTAINED IN THE FILE

inline const list<GenPointChain<int>*>&
DxfFile::accessChains() const
{
  return _chainList;
}


// GET A COPY OF THE CHAINS OF POINTS CONTAINED IN THE FILE

inline void
DxfFile::chains(list<GenPointChain<int>*>& aChainList) const
{
  transform(_chainList.begin(),
	    _chainList.end(),
	    back_inserter(aChainList),
	    qstlCloneObject());
}


// GET THE (QGAR) SEGMENTS CONTAINED IN THE FILE

inline const list<GenQgarSegment<int>*>&
DxfFile::accessSegments() const
{
  return _segmentList;
}


// GET A COPY OF THE (QGAR) SEGMENTS CONTAINED IN THE FILE

inline void
DxfFile::segments(list<GenQgarSegment<int>*>& aQSegList) const
{
  transform(_segmentList.begin(),
	    _segmentList.end(),
	    back_inserter(aQSegList),
	    qstlCloneObject());
}


// GET THE (QGAR) ARCS CONTAINED IN THE FILE

inline const list<GenQgarArc<int>*>&
DxfFile::accessArcs() const
{
  return _arcList;
}


// GET A COPY OF THE (QGAR) ARCS CONTAINED IN THE FILE

inline void
DxfFile::arcs(list<GenQgarArc<int>*>& aQArcList) const
{
  transform(_arcList.begin(),
	    _arcList.end(),
	    back_inserter(aQArcList),
	    qstlCloneObject());
}


// GET THE (QGAR) POLYLINES CONTAINED IN THE FILE

inline const list<GenQgarPolyline<int>*>&
DxfFile::accessPolylines() const
{
  return _polylineList;
}


// GET A COPY OF THE (QGAR) POLYLINES CONTAINED IN THE FILE

inline void
DxfFile::polylines(list<GenQgarPolyline<int>*>& aQPolylineList) const
{
  transform(_polylineList.begin(),
	    _polylineList.end(),
	    back_inserter(aQPolylineList),
	    qstlCloneObject());
}


// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// END OF INLINE FUNCTION IMPLEMENTATION
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII


} // namespace qgar

#endif /* __DXFFILE_H_INCLUDED__ */
