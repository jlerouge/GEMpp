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


#ifndef __SVGFILE_H_INCLUDED__
#define __SVGFILE_H_INCLUDED__


/**
 * @file SvgFile.h
 *
 * @brief Header file of class qgar::SvgFile.
 *
 *
 * @author <a href="mailto:chesnokov.yuriy@gmail.com?subject=Qgar fwd Chesnokov Yuriy">Chesnokov Yuriy</a>
 * @date   Mar, 12  2013  10:00
 * @since  Qgar 4.0.0
 */


// For RCS/CVS use: Do not delete
/* $Id: SvgFile.h,v 1.0 2013/03/12 10:00:00 masini Exp $ */


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
 * @class SvgFile SvgFile.h "qgarlib/SvgFile.h"
 *
 * @brief File including Svg graphics.
 *
 * @warning
 * To enable access to the primitives contained in a SVG file,
 * function qgar::SvgFile::read(bool) must first be called on the file:
@verbatim
  #include <algorithm>
  #include <list>

  #include "SvgFile.h"
  #include "primitives.h"
  #include "stl.h"

  using namespace qgar;
  using namespace std;

  ...

  // Open an existing SVG file
  svgFile.openRONLY();

  // Read the primitives contained in the file
  svgFile.read();

  // Close the file when useless
  svgFile.close();

  // Get and use primitives...
  ...
  list<GenQgarSegment<int>*> qgarSegList;
  svgFile.segments(qgarSegList);
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
 *     qgar::SvgFile::write(const Component&, int, QGEcolor, QGEoutline).</li>
 * </ul>
 *
 *
 * @author <a href="mailto:chesnokov.yuriy@gmail.com?subject=Qgar fwd Chesnokov Yuriy">Chesnokov Yuriy</a>
 * @date   Mar, 12  2013  10:00
 * @since  Qgar 4.0.0
 */
    class SvgFile

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
            DLL_EXPORT explicit SvgFile(const char* aFileName);

            //@}


            /** @name Destructor */
            //        ==========
            //@{

            /**
   * @brief Virtual destructor.
   */
            DLL_EXPORT virtual ~SvgFile();

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
   * @brief Read the header of a SVG file.
   *
   * @warning To be used only with SVG files created by Qgar.
   *
   * @exception qgar::QgarErrorIO  bad header
   */
            void readHeader();

            /**
   * @brief Write the header of a SVG file.
   */
            DLL_EXPORT void writeHeader(int width, int height);

            //@}


            /** @name Background */
            //        ======
            //@{

            /**
   * @brief Write the background image of a SVG file.
   */
            DLL_EXPORT void writeBackground(const char *filename, int width, int height);

            //@}


            /** @name Footer */
            //        ======
            //@{

            /**
   * @brief Write the footer of a SVG file.
   */
            DLL_EXPORT void writeFooter();

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
   *     qgar::SvgFile::read(bool) has not been called previously.</li>
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
   *     qgar::SvgFile::read(bool) has not been called previously.</li>
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
   *     qgar::SvgFile::read(bool) has not been called previously.</li>
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
   *     qgar::SvgFile::read(bool) has not been called previously.</li>
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
   * @brief Read all SVG entities contained in the file.
   *
   * The SVG entities are transformed into (Qgar) primitives
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

            /** @name SVG Colors */
            //        ==========
            //@{

            /**
   * @brief Table to convert Qgar colors into SVG colors.
   *
   * <table cellpadding="2" cellspacing="1">
   * <tr><td><b>Qgar color</b>                </td><td><b>SVG color</b></td></tr>
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
            static const char* _s_svg_colors[22];

            //@}


            /** @name SVG codes */
            //        =========
            //@{

            /** @brief points                             */ static const char* const _s_svg_code_points;
            /** @brief X                                  */ static const char* const _s_svg_code_x;
            /** @brief Y                                  */ static const char* const _s_svg_code_y;
            /** @brief Color                              */ static const char* const _s_svg_code_color;
            /** @brief Thickness                          */ static const char* const _s_svg_code_thick;
            /** @brief Fill                               */ static const char* const _s_svg_code_fill;

            //@}


            /** @name SVG tags */
            //        ========
            //@{

            /** @brief LINE                               */ static const char* const _s_svg_tag_seg;
            /** @brief POLYLINE                           */ static const char* const _s_svg_tag_polyl;
            /** @brief SEQEND                             */ static const char* const _s_svg_tag_esq;
            /** @brief TEXT                               */ static const char* const _s_svg_tag_txt;

            //@}


            /** @name DXF defaults */
            //        ============
            //@{

            /** @brief Fill (none)                        */ static const char* const _s_svg_default_fill;

            //@}


            /** @name SVG features */
            //        ============
            //@{

            /**
   * @brief Maximum length of a SVG field (<b>256</b>).
   */
            static const unsigned int _s_svg_maxbuf;

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


            /** @name Last attribute read */
            //        ===============
            //@{

            /**
   * @brief Code of last attribute read.
   */
            int _lastAttributeCode;

            /**
   * @brief Value of last attribute read.
   */
            char* _lastAttribute;

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


            /** @name Write SVG entities in the file */
            //        ==============================
            //@{

            /**
   * @brief Starts a SVG document in the file
   */
            void startSvgDocument(int width, int height);

            /**
   * @brief Ends a SVG document in the file
   */
            void endSvgDocument();

            /**
   * @brief Starts a SVG element in the file
   *
   * @param aTag
   */
            void startSvgElement(const char* aTag);

            /**
   * @brief End a SVG element in the file
   *
   * @param aTag
   */
            void endSvgElement(const char* aTag);

            /**
   * @brief Write a SVG attribute into the file.
   *
   * @param aCode
   * @param aAttribute
   */
            template <class T>
            void
            writeSvgAttribute(const char* aCode, const T aAttribute);

            /**
   * @brief Write a SVG attribute into the file.
   *
   * @param aCode
   * @param aAttribute
   */
            template <class T>
            void
            writeSvgAttribute(const char* aCode, const deque<GenPoint<T> >& aAttribute);

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
                       QGEcolor aColor = QGE_COLOR_DEFAULT);

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
                       QGEcolor aColor = QGE_COLOR_DEFAULT);

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
                       QGEcolor aColor = QGE_COLOR_DEFAULT);


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
                               QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

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
                               QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

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
                               QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);


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
                               QGEoutline anOutline  = QGE_OUTLINE_DEFAULT);

            //@}



            // -------------------------------------------------------------------

    }; // class SvgFile




    // TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
    // TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
    // T E M P L A T E   I M P L E M E N T A T I O N
    // TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
    // TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


    // =============================================
    // AUXILIARIES: WRITE SVG ENTITIES INTO THE FILE
    // =============================================


    // WRITE A SVG ATTRIBUTE

    template <class T>
    void
    SvgFile::writeSvgAttribute(const char* aCode, const T aAttribute)
    {
        fstream_ << aCode
                 << "=\""
                 << aAttribute
                 << "\" ";
    }

    template <class T>
    void
    SvgFile::writeSvgAttribute(const char* aCode, const deque<GenPoint<T> >& aAttribute)
    {
        fstream_ << aCode
                 << "=\"";

        for (typename deque<GenPoint<T> >::const_iterator attributeIter = aAttribute.begin();
             attributeIter != aAttribute.end();
             ++attributeIter)
        {
            fstream_ << (int)(*attributeIter).x()
                     << ","
                     << (int)(*attributeIter).y();
            if (attributeIter < aAttribute.end() - 1)
            {
                fstream_ << " ";
            }
        }

        fstream_ << "\" ";
    }


    // ========================================
    // AUXILIARIES: SAVE PRIMITIVES IN THE FILE
    // ========================================


    // SAVE A CHAIN OF POINTS WITH COORDINATES OF TYPE 'T'


    template <class T>
    void
    SvgFile::saveChain(AbstractGenPointChain<T>& aChain,
                       int aThickness,
                       QGEcolor aColor)
    {
        Q_UNUSED(aChain);
        Q_UNUSED(aThickness);
        Q_UNUSED(aColor);
        throw QgarErrorDeveloper(__FILE__, __LINE__,
                                 "void qgar::SvgFile::saveChain(AbstractGenPointChain<T>&, int, qgar::QGEcolor)",
                                 "Not yet implemented: See Phil Buzz!");
    }


    // SAVE A POLYLINE


    template <class T>
    void
    SvgFile::savePolyline(const GenPolyline<T>& aPoly,
                          int aThickness,
                          QGEcolor aColor,
                          QGEoutline anOutline)
    {
        Q_UNUSED(anOutline);

        // 1 - Header of the polyline

        startSvgElement(_s_svg_tag_polyl);

        // 2 - Vertices of the polyline

        const deque<GenPoint<T> >& pointList = aPoly.accessVertices();

        writeSvgAttribute(_s_svg_code_points, pointList);

        // 3 - Style of the polyline

        writeSvgAttribute(_s_svg_code_fill, _s_svg_default_fill);
        writeSvgAttribute(_s_svg_code_color, _s_svg_colors[aColor]);
        writeSvgAttribute(_s_svg_code_thick, aThickness);

        // 4 - Footer of the polyline

        endSvgElement(_s_svg_tag_esq);
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
    SvgFile::sizeX() const
    {
        return _maxX;
    }


    // GET THE MAXIMAL Y COORDINATE OF THE IMAGE

    inline int
    SvgFile::sizeY() const
    {
        return _maxY;
    }


    // ================================
    // ACCESS TO PRIMITIVES OF THE FILE
    // ================================


    // GET THE CHAINS OF POINTS CONTAINED IN THE FILE

    inline const list<GenPointChain<int>*>&
    SvgFile::accessChains() const
    {
        return _chainList;
    }


    // GET A COPY OF THE CHAINS OF POINTS CONTAINED IN THE FILE

    inline void
    SvgFile::chains(list<GenPointChain<int>*>& aChainList) const
    {
        transform(_chainList.begin(),
                  _chainList.end(),
                  back_inserter(aChainList),
                  qstlCloneObject());
    }


    // GET THE (QGAR) SEGMENTS CONTAINED IN THE FILE

    inline const list<GenQgarSegment<int>*>&
    SvgFile::accessSegments() const
    {
        return _segmentList;
    }


    // GET A COPY OF THE (QGAR) SEGMENTS CONTAINED IN THE FILE

    inline void
    SvgFile::segments(list<GenQgarSegment<int>*>& aQSegList) const
    {
        transform(_segmentList.begin(),
                  _segmentList.end(),
                  back_inserter(aQSegList),
                  qstlCloneObject());
    }


    // GET THE (QGAR) ARCS CONTAINED IN THE FILE

    inline const list<GenQgarArc<int>*>&
    SvgFile::accessArcs() const
    {
        return _arcList;
    }


    // GET A COPY OF THE (QGAR) ARCS CONTAINED IN THE FILE

    inline void
    SvgFile::arcs(list<GenQgarArc<int>*>& aQArcList) const
    {
        transform(_arcList.begin(),
                  _arcList.end(),
                  back_inserter(aQArcList),
                  qstlCloneObject());
    }


    // GET THE (QGAR) POLYLINES CONTAINED IN THE FILE

    inline const list<GenQgarPolyline<int>*>&
    SvgFile::accessPolylines() const
    {
        return _polylineList;
    }


    // GET A COPY OF THE (QGAR) POLYLINES CONTAINED IN THE FILE

    inline void
    SvgFile::polylines(list<GenQgarPolyline<int>*>& aQPolylineList) const
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

#endif /* __SVGFILE_H_INCLUDED__ */
