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
 |   LORIA - йquipe Qgar                                               |
 |   B.P. 239, 54506 Vandoeuvre-lиs-Nancy Cedex, France                |
 |   email: qgar-contact@loria.fr                                      |
 |   http://www.qgar.org/                                              |
 *---------------------------------------------------------------------*/


/**
 * @file   SvgFile.cpp
 * @brief  Implementation of class qgar::SvgFile.
 *
 * See file SvgFile.h for the interface.
 *
 * @author <a href="mailto:chesnokov.yuriy@gmail.com?subject=Qgar fwd Chesnokov Yuriy">Chesnokov Yuriy</a>
 * @date   Mar, 12  2013  10:00
 * @since  Qgar 4.0.0
 */


// STD
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <iterator>
#include <sstream>
// QGAR
#include "AbstractGenPointChain.h"
#include "BoundingBox.h"
#include "ConnectedComponents.h"
#include "SvgFile.h"
#include "GenPointChain.h"
#include "primitives.h"
#include "QgarErrorDeveloper.h"
#include "QgarErrorIO.h"
#include "stl.h"



using namespace std;



namespace qgar
{


    // ---------------------------------------------------------------------
    // S T A T I C   C O N S T A N T S
    // ---------------------------------------------------------------------


    // Table to convert Qgar colors into SVG colors
    const char* SvgFile::_s_svg_colors[22] =
    {
        "black",      // QGE_COLOR_NONE             -> DXF black
        "black",      // QGE_COLOR_DEFAULT          -> DXF black
        "black",      // QGE_COLOR_BLACK            -> DXF black
        "gray",       // QGE_COLOR_DARK_GRAY        -> DXF gray
        "gray",       // QGE_COLOR_GRAY             -> DXF gray
        "gray",       // QGE_COLOR_LIGHT_GRAY       -> DXF gray
        "white",      // QGE_COLOR_WHITE            -> DXF white
        "magenta",    // QGE_COLOR_MAGENTA          -> DXF magenta
        "magenta",    // QGE_COLOR_PURPLE           -> DXF magenta
        "cyan",       // QGE_COLOR_CYAN             -> DXF cyan
        "blue",       // QGE_COLOR_MEDIUM_BLUE      -> DXF blue
        "blue",       // QGE_COLOR_BLUE             -> DXF blue
        "green",      // QGE_COLOR_OLIVE_GREEN      -> DXF green
        "green",      // QGE_COLOR_DARK_GREEN       -> DXF green
        "green",      // QGE_COLOR_GREEN            -> DXF green
        "yellow",     // QGE_COLOR_YELLOW           -> DXF yellow
        "red",        // QGE_COLOR_ORANGE           -> DXF red
        "red",        // QGE_COLOR_RED              -> DXF red
        "red",        // QGE_COLOR_PINK             -> DXF red
        "red",        // QGE_COLOR_SALMON_PINK      -> DXF red
        "black",      // QGE_COLOR_BROWN            -> DXF black
        "black"       // QGE_COLOR_CHOCOLATE_BROWN  -> DXF black
    };


    // SVG codes
    const char* const SvgFile::_s_svg_code_points     = "points";
    const char* const SvgFile::_s_svg_code_x          = "x";
    const char* const SvgFile::_s_svg_code_y          = "y";
    const char* const SvgFile::_s_svg_code_color      = "stroke";
    const char* const SvgFile::_s_svg_code_thick      = "stroke-width";
    const char* const SvgFile::_s_svg_code_fill       = "fill";


    // SVG tags
    const char* const SvgFile::_s_svg_tag_seg         = "<line";
    const char* const SvgFile::_s_svg_tag_polyl       = "<polyline";
    const char* const SvgFile::_s_svg_tag_esq         = "/>";
    const char* const SvgFile::_s_svg_tag_txt         = "<text";


    // DXF defaults
    const char* const SvgFile::_s_svg_default_fill    = "none";


    //  Maximum length of a SVG field
    const unsigned int SvgFile::_s_svg_maxbuf = 256;


    // ---------------------------------------------------------------------
    // C O N S T R U C T O R S
    // ---------------------------------------------------------------------


    // INITIALIZE WITH GIVEN FILE NAME

    SvgFile::SvgFile(const char* aFileName)

        : AbstractGraphicsFile(aFileName),
          _maxX(0),
          _maxY(0),
          _lastAttribute(new char[_s_svg_maxbuf])

    {
        // VOID
    }


    // ---------------------------------------------------------------------
    // D E S T R U C T O R
    // ---------------------------------------------------------------------


    SvgFile::~SvgFile()
    {
        delete [] _lastAttribute;

        // Free all allocated graphical objects
        for_each(_segmentList.begin(),  _segmentList.end(),  qstlDeleteObject());
        for_each(_arcList.begin(),      _arcList.end(),      qstlDeleteObject());
        for_each(_chainList.begin(),    _chainList.end(),    qstlDeleteObject());
        for_each(_polylineList.begin(), _polylineList.end(), qstlDeleteObject());
    }


    // -------------------------------------------------------------------
    // H E A D E R
    // -------------------------------------------------------------------


    // READ THE HEADER OF A SVG FILE

    void
    SvgFile::readHeader()
    {
        if (false)
        {
            // TODO:
        }
        else
        {
            ostringstream os;
            os << "Unsuported header in file "
               << name_;
            throw QgarErrorIO(__FILE__, __LINE__,
                              "void qgar::SvgFile::readHeader()",
                              os.str());
        }
    }


    // WRITE THE HEADER OF A SVG FILE

    void
    SvgFile::writeHeader(int width, int height)
    {
        startSvgDocument(width, height);
    }

    void
    SvgFile::writeBackground(const char *filename, int width, int height)
    {
        fstream_ << "<image x=\"0\" y=\"0\" width=\"" << width << "\" height=\"" << height << "\" xlink:href=\"" << filename << "\"/>" << endl;
    }

    // -------------------------------------------------------------------
    // F O O T E R
    // -------------------------------------------------------------------


    // WRITE THE FOOTER OF A SVG FILE

    void
    SvgFile::writeFooter()
    {
        endSvgDocument();
    }


    // ---------------------------------------------------------------------
    // B U F F E R E D   I N P U T
    // ----------------------------------------------------------------------


    // READ ALL SVG ENTITIES CONTAINED IN THE FILE

    void
    SvgFile::read(bool convertPolylines)
    {
        Q_UNUSED(convertPolylines);
        isOpenR();

        ostringstream os;
        os << "Unsuported element in file "
           << name_;
        throw QgarErrorIO(__FILE__, __LINE__,
                          "void qgar::SvgFile::read()",
                          os.str());
    }


    // ---------------------------------------------------------------------
    // O U T P U T   C H A I N S   O F   P O I N T S
    // ----------------------------------------------------------------------


    // CHAIN OF INTEGER POINTS

    void
    SvgFile::write(AbstractGenPointChain<int>& aChain,
                   int aThickness,
                   QGEcolor aColor)
    {
        isOpenW();
        saveChain(aChain, aThickness, aColor);
    }


    // CHAIN OF FLOAT POINTS

    void
    SvgFile::write(AbstractGenPointChain<float>& aChain,
                   int aThickness,
                   QGEcolor aColor)
    {
        isOpenW();
        saveChain(aChain, aThickness, aColor);
    }


    // CHAINS OF DOUBLE POINTS

    void
    SvgFile::write(AbstractGenPointChain<double>& aChain,
                   int aThickness,
                   QGEcolor aColor)
    {
        isOpenW();
        saveChain(aChain, aThickness, aColor);
    }


    // ---------------------------------------------------------------------
    // O U T P U T   S E G M E N T S
    // ---------------------------------------------------------------------


    // SEGMENT WITH INTEGER COORDINATES

    void
    SvgFile::write(int aXSource,
                   int aYSource,
                   int aXTarget,
                   int aYTarget,
                   int aThickness,
                   QGEcolor aColor,
                   QGEoutline anOutline)
    {
        isOpenW();
        saveSegment(aXSource,
                    aYSource,
                    aXTarget,
                    aYTarget,
                    aThickness,
                    aColor,
                    anOutline);
    }


    // SEGMENT WITH FLOAT COORDINATES

    void
    SvgFile::write(float aXSource,
                   float aYSource,
                   float aXTarget,
                   float aYTarget,
                   int aThickness,
                   QGEcolor aColor,
                   QGEoutline anOutline)
    {
        isOpenW();
        saveSegment((int) aXSource,
                    (int) aYSource,
                    (int) aXTarget,
                    (int) aYTarget,
                    aThickness,
                    aColor,
                    anOutline);
    }


    // SEGMENT WITH DOUBLE COORDINATES

    void
    SvgFile::write(double aXSource,
                   double aYSource,
                   double aXTarget,
                   double aYTarget,
                   int aThickness,
                   QGEcolor aColor,
                   QGEoutline anOutline)
    {
        isOpenW();
        saveSegment((int) aXSource,
                    (int) aYSource,
                    (int) aXTarget,
                    (int) aYTarget,
                    aThickness,
                    aColor,
                    anOutline);
    }


    // LIST OF QGAR SEGMENTS WITH INTEGER COORDINATES

    void
    SvgFile::write(const list<GenQgarSegment<int>*>& aQSegList,
                   int aThickness,
                   QGEcolor aColor,
                   QGEoutline anOutline)
    {
        for (list<QgarSegment*>::const_iterator qsegListIter = aQSegList.begin();
             qsegListIter != aQSegList.end();
             ++qsegListIter)
        {
            write((*qsegListIter)->accessGeomStructure(),
                  aThickness,
                  aColor,
                  anOutline);
        }
    }


    // ---------------------------------------------------------------------
    // O U T P U T   A R C S   O F   C I R C L E
    // ---------------------------------------------------------------------


    // ARC WITH INTEGER COORDINATES

    void
    SvgFile::write(int aXSource,
                   int aYSource,
                   int aXTarget,
                   int aYTarget,
                   int aXCenter,
                   int aYCenter,
                   int aThickness,
                   QGEcolor aColor,
                   QGEoutline anOutline)
    {
        isOpenW();

        saveArc(aXSource,
                aYSource,
                aXTarget,
                aYTarget,
                aXCenter,
                aYCenter,
                aThickness,
                aColor,
                anOutline);
    }


    // ARC WITH FLOAT COORDINATES

    void
    SvgFile::write(float aXSource,
                   float aYSource,
                   float aXTarget,
                   float aYTarget,
                   float aXCenter,
                   float aYCenter,
                   int aThickness,
                   QGEcolor aColor,
                   QGEoutline anOutline)
    {
        isOpenW();

        saveArc((int) aXSource,
                (int) aYSource,
                (int) aXTarget,
                (int) aYTarget,
                (int) aXCenter,
                (int) aYCenter,
                aThickness,
                aColor,
                anOutline);
    }


    // ARC WITH DOUBLE COORDINATES

    void
    SvgFile::write(double aXSource,
                   double aYSource,
                   double aXTarget,
                   double aYTarget,
                   double aXCenter,
                   double aYCenter,
                   int aThickness,
                   QGEcolor aColor,
                   QGEoutline anOutline)
    {
        isOpenW();

        saveArc((int) aXSource,
                (int) aYSource,
                (int) aXTarget,
                (int) aYTarget,
                (int) aXCenter,
                (int) aYCenter,
                aThickness,
                aColor,
                anOutline);
    }


    // LIST OF QGAR ARCS WITH INTEGER COORDINATES

    void
    SvgFile::write(list<GenQgarArc<int>*>& aQArcList,
                   int aThickness,
                   QGEcolor aColor,
                   QGEoutline anOutline)
    {
        for (list<QgarArc*>::iterator qarcListIter = aQArcList.begin() ;
             qarcListIter != aQArcList.end() ;
             ++qarcListIter)
        {
            write((*qarcListIter)->accessGeomStructure(),
                  aThickness,
                  aColor,
                  anOutline);
        }
    }


    // ---------------------------------------------------------------------
    // O U T P U T   P O L Y L I N E S
    // ---------------------------------------------------------------------


    // INTEGER POLYLINE

    void
    SvgFile::write(const GenPolyline<int>& aPoly,
                   int aThickness,
                   QGEcolor aColor,
                   QGEoutline anOutline)
    {
        isOpenW();
        savePolyline(aPoly, aThickness, aColor, anOutline);
    }


    // FLOAT POLYLINE

    void
    SvgFile::write(const GenPolyline<float>& aPoly,
                   int aThickness,
                   QGEcolor aColor,
                   QGEoutline anOutline)
    {
        isOpenW();
        savePolyline(aPoly, aThickness, aColor, anOutline);
    }


    // DOUBLE POLYLINE

    void
    SvgFile::write(const GenPolyline<double>& aPoly,
                   int aThickness,
                   QGEcolor aColor,
                   QGEoutline anOutline)
    {
        isOpenW();
        savePolyline(aPoly, aThickness, aColor, anOutline);
    }


    // ---------------------------------------------------------------------
    // O U T P U T   P O L Y G O N S
    // ---------------------------------------------------------------------


    // POLYGON WITH INTEGER COORDINATES

    void
    SvgFile::write(GenPolygon<int>* aPolygon,
                   int aThickness,
                   QGEcolor aColor,
                   QGEoutline anOutline)
    {
        list<Segment> segList = aPolygon->toSegList();

        for(list<Segment>::iterator itLSeg = segList.begin();
            itLSeg != segList.end();
            ++itLSeg)
        {
            write(*itLSeg, aThickness, aColor, anOutline);
        }
    }


    // ---------------------------------------------------------------------
    // O U T P U T   B O U N D I N G   B O X E S
    // ---------------------------------------------------------------------


    // BOUNDING BOX WITH INTEGER COORDINATES

    void
    SvgFile::write(const BoundingBox& aBox,
                   int aThickness,
                   QGEcolor aColor,
                   QGEoutline anOutline)
    {
        saveBox(aBox.xTopLeft(),
                aBox.yTopLeft(),
                aBox.xBottomRight(),
                aBox.yBottomRight(),
                aThickness,
                aColor,
                anOutline);
    }



    // ---------------------------------------------------------------------
    // O U T P U T   Q G A R   P R I M I T I V E S
    // ---------------------------------------------------------------------


    // void
    // DxfFile::write(list<AbstractGenQgarPrimitive<int>*>& aQPrimList,
    // 		  int aThickness,
    // 		  QGEcolor aColor,
    // 		  QGEoutline anOutline)
    // {
    //   for (list<AbstractGenQgarPrimitive<int>*>::iterator qpListIter
    //          = aQPrimList.begin();
    //        qpListIter != aQPrimList.end();
    //        ++qpListIter)
    //     {
    //       (*qpListIter)->write(*this, aThickness, aColor, anOutline);
    //     }
    // }


    // ---------------------------------------------------------------------
    // O U T P U T   T E X T S
    // ---------------------------------------------------------------------


    void
    SvgFile::write(const char* aText,
                   int         aX,
                   int         aY,
                   int         aHeight,
                   QGEcolor    aColor)
    {
        Q_UNUSED(aText);
        Q_UNUSED(aX);
        Q_UNUSED(aY);
        Q_UNUSED(aHeight);
        Q_UNUSED(aColor);
        isOpenW();

        throw QgarErrorDeveloper(__FILE__, __LINE__,
                                 "void qgar::SvgFile::write(const char*, int, int, int, qgar::QGEcolor)",
                                 "Not yet implemented: See Phil Buzz!");
    }


    // ---------------------------------------------------------------------
    // AUXILIARIES: SAVE SVG ENTITIES INTO THE FILE
    // ---------------------------------------------------------------------


    // START DOCUMENT

    void
    SvgFile::startSvgDocument(int width, int height)
    {
        fstream_ << "<?xml version=\"1.0\" standalone=\"no\"?>"
                 << endl
                 << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\""
                 << endl
                 << "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">"
                 << endl
                 << endl
                 << "<svg width=\"" << width << "\" height=\"" << height << "\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">"
                 << endl;
    }


    // END DOCUMENT

    void
    SvgFile::endSvgDocument()
    {
        fstream_ << "</svg>"
                 << endl;
    }


    // START ELEMENT

    void
    SvgFile::startSvgElement(const char* aTag)
    {
        fstream_ << "  "
                 << aTag
                 << " ";
    }


    // END ELEMENT

    void
    SvgFile::endSvgElement(const char* aTag)
    {
        fstream_ << aTag
                 << endl;
    }


    // ---------------------------------------------------------------------
    // AUXILIARIES: SAVE PRIMITIVES IN THE FILE
    // ---------------------------------------------------------------------


    // SAVE A SEGMENT WITH INTEGER COORDINATES

    void
    SvgFile::saveSegment(int aXSource,
                         int aYSource,
                         int aXTarget,
                         int aYTarget,
                         int aThickness,
                         QGEcolor aColor,
                         QGEoutline anOutline)
    {
        Q_UNUSED(aXSource);
        Q_UNUSED(aYSource);
        Q_UNUSED(aXTarget);
        Q_UNUSED(aYTarget);
        Q_UNUSED(aThickness);
        Q_UNUSED(aColor);
        Q_UNUSED(anOutline);
        throw QgarErrorDeveloper(__FILE__, __LINE__,
                                 "void qgar::SvgFile::saveSegment(int, int, int, int, int, qgar::QGEcolor, agar::QGEoutline)",
                                 "Not yet implemented: See Phil Buzz!");
    }


    // SAVE AN ARC WITH INTEGER COORDINATES

    void
    SvgFile::saveArc(int aXSource,
                     int aYSource,
                     int aXTarget,
                     int aYTarget,
                     int aXCenter,
                     int aYCenter,
                     int aThickness,
                     QGEcolor aColor,
                     QGEoutline anOutline)
    {
        Q_UNUSED(aXSource);
        Q_UNUSED(aYSource);
        Q_UNUSED(aXTarget);
        Q_UNUSED(aYTarget);
        Q_UNUSED(aXCenter);
        Q_UNUSED(aYCenter);
        Q_UNUSED(aThickness);
        Q_UNUSED(aColor);
        Q_UNUSED(anOutline);
        throw QgarErrorDeveloper(__FILE__, __LINE__,
                                 "void qgar::SvgFile::saveArc(int, int, int, int, int, int, int, qgar::QGEcolor, agar::QGEoutline)",
                                 "Not yet implemented: See Phil Buzz!");
    }


    // SAVE A BOUNDING BOX

    void
    SvgFile::saveBox(int aXTopLeft,
                     int aYTopLeft,
                     int aXBottomRight,
                     int aYBottomRight,
                     int aThickness,
                     QGEcolor aColor,
                     QGEoutline anOutline)
    {
        saveSegment(aXTopLeft, aYTopLeft, aXTopLeft, aYBottomRight,
                    aThickness,
                    aColor,
                    anOutline);

        saveSegment(aXTopLeft, aYTopLeft, aXBottomRight, aYTopLeft,
                    aThickness,
                    aColor,
                    anOutline);

        saveSegment(aXBottomRight, aYTopLeft, aXBottomRight, aYBottomRight,
                    aThickness,
                    aColor,
                    anOutline);

        saveSegment(aXTopLeft, aYBottomRight, aXBottomRight, aYBottomRight,
                    aThickness,
                    aColor,
                    anOutline);
    }


    // ---------------------------------------------------------------------
    // PRIVATE FUNCTIONS NOT YET IMPLEMENTED
    // ---------------------------------------------------------------------


    // =================
    // OUTPUT COMPONENTS
    // =================


    // WRITE A (CONNECTED) COMPONENT

    void
    SvgFile::write(const ConnectedComponents::node_type* const aPNode,
                   int        aThickness,
                   QGEcolor   aColor,
                   QGEoutline anOutline)
    {
        Q_UNUSED(aPNode);
        Q_UNUSED(aThickness);
        Q_UNUSED(aColor);
        Q_UNUSED(anOutline);
        throw QgarErrorDeveloper(__FILE__, __LINE__,
                                 "void qgar::SvgFile::write(const qgar::ConnectedComponents::node_type* const, int, qgar::QGEcolor, qgar::QGEoutline)",
                                 "Not yet implemented: See Phil Buzz!");
    }


    // ==============
    // OUTPUT CIRCLES
    // ==============


    // WRITE A CIRCLE WITH COORDINATES OF TYPE 'int'

    void
    SvgFile::write(int aXCenter,
                   int aYCenter,
                   double aRadius,
                   int        aThickness,
                   QGEcolor   aColor,
                   QGEoutline anOutline)
    {
        Q_UNUSED(aXCenter);
        Q_UNUSED(aYCenter);
        Q_UNUSED(aRadius);
        Q_UNUSED(aThickness);
        Q_UNUSED(aColor);
        Q_UNUSED(anOutline);
        throw QgarErrorDeveloper(__FILE__, __LINE__,
                                 "void qgar::SvgFile::write(int, int, double, int, qgar::QGEcolor, qgar::QGEoutline)",
                                 "Not yet implemented: See Phil Buzz!");
    }


    // WRITE A CIRCLE WITH COORDINATES OF TYPE 'float'

    void
    SvgFile::write(float aXCenter,
                   float aYCenter,
                   double aRadius,
                   int        aThickness,
                   QGEcolor   aColor,
                   QGEoutline anOutline)
    {
        Q_UNUSED(aXCenter);
        Q_UNUSED(aYCenter);
        Q_UNUSED(aRadius);
        Q_UNUSED(aThickness);
        Q_UNUSED(aColor);
        Q_UNUSED(anOutline);
        throw QgarErrorDeveloper(__FILE__, __LINE__,
                                 "void qgar::SvgFile::write(float, float, double, int, qgar::QGEcolor, qgar::QGEoutline)",
                                 "Not yet implemented: See Phil Buzz!");
    }


    // WRITE AN ARC WITH COORDINATES OF TYPE 'double'

    void
    SvgFile::write(double aXCenter,
                   double aYCenter,
                   double aRadius,
                   int        aThickness,
                   QGEcolor   aColor,
                   QGEoutline anOutline)
    {
        Q_UNUSED(aXCenter);
        Q_UNUSED(aYCenter);
        Q_UNUSED(aRadius);
        Q_UNUSED(aThickness);
        Q_UNUSED(aColor);
        Q_UNUSED(anOutline);
        throw QgarErrorDeveloper(__FILE__, __LINE__,
                                 "void qgar::SvgFile::write(double, double, double, int, qgar::QGEcolor, qgar::QGEoutline)",
                                 "Not yet implemented: See Phil Buzz!");
    }


    // =============
    // OUTPUT POINTS
    // =============


    // WRITE A POINT WITH COORDINATES OF TYPE 'int'

    void
    SvgFile::write(int aX, int aY, int aThickness, QGEcolor aColor)
    {
        Q_UNUSED(aX);
        Q_UNUSED(aY);
        Q_UNUSED(aThickness);
        Q_UNUSED(aColor);
        throw QgarErrorDeveloper(__FILE__, __LINE__,
                                 "void qgar::SvgFile::write(int, int, int, qgar::QGEcolor)",
                                 "Not yet implemented: See Phil Buzz!");
    }


    // WRITE A POINT WITH COORDINATES OF TYPE 'float'

    void
    SvgFile::write(float aX, float aY, int aThickness, QGEcolor aColor)
    {
        Q_UNUSED(aX);
        Q_UNUSED(aY);
        Q_UNUSED(aThickness);
        Q_UNUSED(aColor);
        throw QgarErrorDeveloper(__FILE__, __LINE__,
                                 "void qgar::SvgFile::write(float, float, int, qgar::QGEcolor)",
                                 "Not yet implemented: See Phil Buzz!");
    }



    // WRITE A POINT WITH COORDINATES OF TYPE 'double'

    void
    SvgFile::write(double aX, double aY, int aThickness, QGEcolor aColor)
    {
        Q_UNUSED(aX);
        Q_UNUSED(aY);
        Q_UNUSED(aThickness);
        Q_UNUSED(aColor);
        throw QgarErrorDeveloper(__FILE__, __LINE__,
                                 "void qgar::SvgFile::write(double, double, int, qgar::QGEcolor)",
                                 "Not yet implemented: See Phil Buzz!");
    }


    // --------------------------------------------------------------------

} // namespace qgar
