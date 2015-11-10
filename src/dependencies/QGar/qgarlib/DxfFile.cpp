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


/**
 * @file   DxfFile.cpp
 * @brief  Implementation of class qgar::DxfFile.
 *
 * See file DxfFile.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date   Jul 4, 2001  16:15
 * @since  qgar 1.0
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
#include "DxfFile.h"
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


    // Table to convert Qgar colors into DXF colors
    const int DxfFile::_s_dxf_colors[] =
    {
        7,   // QGE_COLOR_NONE             -> DXF black
        7,   // QGE_COLOR_DEFAULT          -> DXF black
        7,   // QGE_COLOR_BLACK            -> DXF black
        8,   // QGE_COLOR_DARK_GRAY        -> DXF gray
        8,   // QGE_COLOR_GRAY             -> DXF gray
        8,   // QGE_COLOR_LIGHT_GRAY       -> DXF gray
        15,  // QGE_COLOR_WHITE            -> DXF white
        6,   // QGE_COLOR_MAGENTA          -> DXF magenta
        6,   // QGE_COLOR_PURPLE           -> DXF magenta
        4,   // QGE_COLOR_CYAN             -> DXF cyan
        5,   // QGE_COLOR_MEDIUM_BLUE      -> DXF blue
        5,   // QGE_COLOR_BLUE             -> DXF blue
        3,   // QGE_COLOR_OLIVE_GREEN      -> DXF green
        3,   // QGE_COLOR_DARK_GREEN       -> DXF green
        3,   // QGE_COLOR_GREEN            -> DXF green
        2,   // QGE_COLOR_YELLOW           -> DXF yellow
        1,   // QGE_COLOR_ORANGE           -> DXF red
        1,   // QGE_COLOR_RED              -> DXF red
        1,   // QGE_COLOR_PINK             -> DXF red
        1,   // QGE_COLOR_SALMON_PINK      -> DXF red
        7,   // QGE_COLOR_BROWN            -> DXF black
        7    // QGE_COLOR_CHOCOLATE_BROWN  -> DXF black
    };


    // DXF codes
    const int DxfFile::_s_dxf_code_com      = 999; // Comment
    const int DxfFile::_s_dxf_code_ident    = 0;   // Identifier
    const int DxfFile::_s_dxf_code_name     = 2;   // Name
    const int DxfFile::_s_dxf_code_color   = 62;   // Color
    const int DxfFile::_s_dxf_code_x1       = 10;  // X1
    const int DxfFile::_s_dxf_code_x2       = 11;  // X2
    const int DxfFile::_s_dxf_code_y1       = 20;  // Y1
    const int DxfFile::_s_dxf_code_y2       = 21;  // Y2
    const int DxfFile::_s_dxf_code_thick    = 39;  // Thickness
    const int DxfFile::_s_dxf_code_radius   = 40;  // Radius / total pattern length
    const int DxfFile::_s_dxf_code_start    = 50;  // Start angle
    const int DxfFile::_s_dxf_code_end      = 51;  // End angle
    const int DxfFile::_s_dxf_code_flag     = 70;  // Standard flag value
    const int DxfFile::_s_dxf_code_lintp    = 3;   // Descriptive text for linetype
    const int DxfFile::_s_dxf_code_algt     = 72;  // Alignment code
    const int DxfFile::_s_dxf_code_dash     = 73;  // Number of dash length items
    const int DxfFile::_s_dxf_code_ltp      = 6;   // Ltype name
    const int DxfFile::_s_dxf_code_layer    = 8;   // Layer name
    const int DxfFile::_s_dxf_code_elev     = 38;  // Elevation
    const int DxfFile::_s_dxf_code_vertflag = 66;  // Vertices flag
    const int DxfFile::_s_dxf_code_txthght  = 40;  // Text height
    const int DxfFile::_s_dxf_code_txt      = 1;   // Text value


    // DXF tags
    const char* const DxfFile::_s_dxf_tag_sec   = "SECTION";
    const char* const DxfFile::_s_dxf_tag_tbs   = "TABLES";
    const char* const DxfFile::_s_dxf_tag_tbl   = "TABLE";
    const char* const DxfFile::_s_dxf_tag_layer = "LAYER";
    const char* const DxfFile::_s_dxf_tag_ltp   = "LTYPE";
    const char* const DxfFile::_s_dxf_tag_ent   = "ENTITIES";
    const char* const DxfFile::_s_dxf_tag_arc   = "ARC";
    const char* const DxfFile::_s_dxf_tag_seg   = "LINE";
    const char* const DxfFile::_s_dxf_tag_polyl = "POLYLINE";
    const char* const DxfFile::_s_dxf_tag_vert  = "VERTEX";
    const char* const DxfFile::_s_dxf_tag_eof   = "EOF";
    const char* const DxfFile::_s_dxf_tag_end   = "ENDSEC";
    const char* const DxfFile::_s_dxf_tag_etb   = "ENDTAB";
    const char* const DxfFile::_s_dxf_tag_esq   = "SEQEND";
    const char* const DxfFile::_s_dxf_tag_txt   = "TEXT";


    // DXF comments
    const char* const DxfFile::_s_dxf_com_create = "** Created by Qgar on ";
    const char* const DxfFile::_s_dxf_com_def    = "** Definitions";
    const char* const DxfFile::_s_dxf_com_ltp    = "** Linetype definitions";
    const char* const DxfFile::_s_dxf_com_layer  = "** Layer definitions";
    const char* const DxfFile::_s_dxf_com_ent    = "** Entities";
    const char* const DxfFile::_s_dxf_com_seg    = "** Segment";
    const char* const DxfFile::_s_dxf_com_arc    = "** Arc";
    const char* const DxfFile::_s_dxf_com_dwall  = "** Dividing wall";
    const char* const DxfFile::_s_dxf_com_bwall  = "** Bearing wall";
    const char* const DxfFile::_s_dxf_com_swind  = "** Simple window";
    const char* const DxfFile::_s_dxf_com_dwind  = "** Double window";
    const char* const DxfFile::_s_dxf_com_door   = "** Door";
    const char* const DxfFile::_s_dxf_com_stairs = "** Stairs";
    const char* const DxfFile::_s_dxf_com_pipe   = "** Pipe";
    const char* const DxfFile::_s_dxf_com_chain  = "** Chain";
    const char* const DxfFile::_s_dxf_com_polyl  = "** Polyline";
    const char* const DxfFile::_s_dxf_com_txt    = "** Text";


    // DXF defaults
    const char* const DxfFile::_s_dxf_default_cont = "CONTINUOUS";  // Linetype for LTYPE
    const char* const DxfFile::_s_dxf_default_dash = "DASHED";      // Linetype for LTYPE
    const char* const DxfFile::_s_dxf_default_dltp = "----";        // Descriptive for LTYPE
    const int    DxfFile::_s_dxf_default_ltp   = 1;  // Number of LTYPE
    const int    DxfFile::_s_dxf_default_fly   = 2;  // Flag value for LAYER
    const int    DxfFile::_s_dxf_default_layer = 8;  // Number of LAYERS
    const int    DxfFile::_s_dxf_default_flt   = 64; // Flag value for LTYPE
    const int    DxfFile::_s_dxf_default_alg   = 65; // Aligment value for LTYPE
    const int    DxfFile::_s_dxf_default_dash1 = 0;  // Dash length for LTYPE
    const int    DxfFile::_s_dxf_default_dash2 = 2;  // Dash length for LTYPE
    const double DxfFile::_s_dxf_default_pat1  = 0.; // Total length pattern for LTYPE
    const double DxfFile::_s_dxf_default_pat2  = 2.; // Total length pattern for LTYPE
    const int    DxfFile::_s_dxf_default_wpo   = 1;  // Default thickness for POLYLINE
    const int    DxfFile::_s_dxf_default_vfg   = 1;  // Vertices follow POLYLINE definition
    const int    DxfFile::_s_dxf_default_pfgo  = 0;  // Polylines are opened
    const int    DxfFile::_s_dxf_default_pfgc  = 1;  // Polylines are closed


    // DXF layers
    const char* const DxfFile::_s_dxf_layer_prm    = "PRIMITIVE";
    const char* const DxfFile::_s_dxf_layer_dwall  = "DIVWALL";
    const char* const DxfFile::_s_dxf_layer_bwall  = "BEARWALL";
    const char* const DxfFile::_s_dxf_layer_swind  = "SIMWIN";
    const char* const DxfFile::_s_dxf_layer_dwind  = "DOUWIN";
    const char* const DxfFile::_s_dxf_layer_door   = "DOOR";
    const char* const DxfFile::_s_dxf_layer_stairs = "STAIRS";
    const char* const DxfFile::_s_dxf_layer_pipe   = "PIPE";
    const char* const DxfFile::_s_dxf_layer_chain  = "CHAINE";
    const char* const DxfFile::_s_dxf_layer_polyl  = "POLYLINE";
    const char* const DxfFile::_s_dxf_layer_txt    = "TEXT";


    //  Maximum length of a DXF field
    const unsigned int DxfFile::_s_dxf_maxbuf = 256;


    // ---------------------------------------------------------------------
    // C O N S T R U C T O R S
    // ---------------------------------------------------------------------


    // INITIALIZE WITH GIVEN FILE NAME

    DxfFile::DxfFile(const char* aFileName)

        : AbstractGraphicsFile(aFileName),
          _maxX(0),
          _maxY(0),
          _lastGroup(new char[_s_dxf_maxbuf])

    {
        // VOID
    }


    // ---------------------------------------------------------------------
    // D E S T R U C T O R
    // ---------------------------------------------------------------------


    DxfFile::~DxfFile()
    {
        delete [] _lastGroup;

        // Free all allocated graphical objects
        for_each(_segmentList.begin(),  _segmentList.end(),  qstlDeleteObject());
        for_each(_arcList.begin(),      _arcList.end(),      qstlDeleteObject());
        for_each(_chainList.begin(),    _chainList.end(),    qstlDeleteObject());
        for_each(_polylineList.begin(), _polylineList.end(), qstlDeleteObject());
    }


    // -------------------------------------------------------------------
    // H E A D E R
    // -------------------------------------------------------------------


    // READ THE HEADER OF A DXF FILE

    void
    DxfFile::readHeader()



    {
        if (retrieveDxfGroup() == _s_dxf_code_ident)
        {
            if (!strcmp(_lastGroup, _s_dxf_tag_sec))
            {
                do
                {
                    // Read to the next name or identifier
                    while ((retrieveDxfGroup() != _s_dxf_code_name)
                           && (_lastGroupCode != _s_dxf_code_ident))
                    {
                        // VOID
                    }
                    // Entities?
                    if ((_lastGroupCode == _s_dxf_code_name)
                            && (!strcmp(_lastGroup, _s_dxf_tag_ent)))
                    {
                        retrieveDxfGroup();
                        return;
                    }
                }
                // End reached?
                while ((_lastGroupCode != _s_dxf_code_ident)
                       || strcmp(_lastGroup, _s_dxf_tag_eof));
            }
        }
        else
        {
            ostringstream os;
            os << "Bad header in file "
               << name_;
            throw QgarErrorIO(__FILE__, __LINE__,
                              "void qgar::DxfFile::readHeader()",
                              os.str());
        }
    }


    // WRITE THE HEADER OF A DXF FILE

    void
    DxfFile::writeHeader()
    {
        time_t date;
        time(&date);
        fstream_ << _s_dxf_code_com
                 << endl
                 << _s_dxf_com_create
                 << asctime(localtime(&date));

        saveDxfGroup(_s_dxf_code_ident, _s_dxf_tag_sec);

        // 1 - Definition of LTYPE & LAYERS
        saveDxfGroup(_s_dxf_code_com,  _s_dxf_com_def);
        saveDxfGroup(_s_dxf_code_name, _s_dxf_tag_tbs);

        // 2 - Header for LTYPE
        saveDxfGroup(_s_dxf_code_com,   _s_dxf_com_ltp);
        saveDxfGroup(_s_dxf_code_ident, _s_dxf_tag_tbl);
        saveDxfGroup(_s_dxf_code_name,  _s_dxf_tag_ltp);
        saveDxfGroup(_s_dxf_code_flag,  _s_dxf_default_ltp);

        // 3 - LTYPE Continuous
        saveDxfGroup(_s_dxf_code_ident,  _s_dxf_tag_ltp);
        saveDxfGroup(_s_dxf_code_name,   _s_dxf_default_cont);
        saveDxfGroup(_s_dxf_code_flag,   _s_dxf_default_flt);
        saveDxfGroup(_s_dxf_code_lintp,  _s_dxf_default_dltp);
        saveDxfGroup(_s_dxf_code_algt,   _s_dxf_default_alg);
        saveDxfGroup(_s_dxf_code_dash,   _s_dxf_default_dash1);
        saveDxfGroup(_s_dxf_code_radius, _s_dxf_default_pat1);

        // 4 - LTYPE Dashed
        saveDxfGroup(_s_dxf_code_ident,  _s_dxf_tag_ltp);
        saveDxfGroup(_s_dxf_code_name,   _s_dxf_default_dash);
        saveDxfGroup(_s_dxf_code_flag,   _s_dxf_default_flt);
        saveDxfGroup(_s_dxf_code_lintp,  _s_dxf_default_dltp);
        saveDxfGroup(_s_dxf_code_algt,   _s_dxf_default_alg);
        saveDxfGroup(_s_dxf_code_dash,   _s_dxf_default_dash2);
        saveDxfGroup(_s_dxf_code_radius, _s_dxf_default_pat2);
        saveDxfGroup(_s_dxf_code_ident,  _s_dxf_tag_etb);

        // 5 - Header for LAYERS
        saveDxfGroup(_s_dxf_code_com,   _s_dxf_com_layer);
        saveDxfGroup(_s_dxf_code_ident, _s_dxf_tag_tbl);
        saveDxfGroup(_s_dxf_code_name,  _s_dxf_tag_ltp);
        saveDxfGroup(_s_dxf_code_flag,  _s_dxf_default_layer);

        // 6 - LAYERS
        saveDxfLayer(_s_dxf_layer_prm,   _s_dxf_default_fly, _s_dxf_colors[QGE_COLOR_BLACK],  _s_dxf_default_cont);
        saveDxfLayer(_s_dxf_layer_dwall, _s_dxf_default_fly, _s_dxf_colors[QGE_COLOR_GRAY],   _s_dxf_default_cont);
        saveDxfLayer(_s_dxf_layer_bwall, _s_dxf_default_fly, _s_dxf_colors[QGE_COLOR_GRAY],   _s_dxf_default_cont);
        saveDxfLayer(_s_dxf_layer_swind, _s_dxf_default_fly, _s_dxf_colors[QGE_COLOR_BLUE],   _s_dxf_default_cont);
        saveDxfLayer(_s_dxf_layer_dwind, _s_dxf_default_fly, _s_dxf_colors[QGE_COLOR_BLUE],   _s_dxf_default_cont);
        saveDxfLayer(_s_dxf_layer_door,  _s_dxf_default_fly, _s_dxf_colors[QGE_COLOR_RED],    _s_dxf_default_cont);
        saveDxfLayer(_s_dxf_layer_stairs,_s_dxf_default_fly, _s_dxf_colors[QGE_COLOR_GREEN],  _s_dxf_default_cont);
        saveDxfLayer(_s_dxf_layer_pipe,  _s_dxf_default_fly, _s_dxf_colors[QGE_COLOR_YELLOW], _s_dxf_default_cont);
        saveDxfLayer(_s_dxf_layer_chain, _s_dxf_default_fly, _s_dxf_colors[QGE_COLOR_BLUE],   _s_dxf_default_cont);
        saveDxfLayer(_s_dxf_layer_polyl, _s_dxf_default_fly, _s_dxf_colors[QGE_COLOR_BLACK],  _s_dxf_default_cont);

        saveDxfGroup(_s_dxf_code_ident, _s_dxf_tag_etb);
        saveDxfGroup(_s_dxf_code_ident, _s_dxf_tag_end);

        // 7 - Header for ENTITIES
        saveDxfGroup(_s_dxf_code_com,   _s_dxf_com_ent);
        saveDxfGroup(_s_dxf_code_ident, _s_dxf_tag_sec);
        saveDxfGroup(_s_dxf_code_name,  _s_dxf_tag_ent);
    }


    // -------------------------------------------------------------------
    // F O O T E R
    // -------------------------------------------------------------------


    // WRITE THE FOOTER OF A DXF FILE

    void
    DxfFile::writeFooter()
    {
        saveDxfGroup(_s_dxf_code_ident, _s_dxf_tag_end);
        saveDxfGroup(_s_dxf_code_ident, _s_dxf_tag_eof);
    }


    // ---------------------------------------------------------------------
    // B U F F E R E D   I N P U T
    // ----------------------------------------------------------------------


    // READ ALL DXF ENTITIES CONTAINED IN THE FILE

    void
    DxfFile::read(bool convertPolylines)



    {
        isOpenR();

        // Qgar entities are recognized using the category of DXF entities
        bool endReached = false;
        while(!endReached)
        {
            if (_lastGroupCode == _s_dxf_code_ident)
            {
                // BLOCK 1
                if (!(strcmp(_lastGroup, _s_dxf_tag_seg)))
                {
                    retrieveQgarSegment(_segmentList);
                }
                else
                {
                    // BLOCK 2
                    if (!(strcmp(_lastGroup, _s_dxf_tag_arc)))
                    {
                        retrieveQgarArc(_arcList);
                    }
                    else
                    {
                        // BLOCK 3
                        if (!strcmp(_lastGroup, _s_dxf_tag_polyl))
                        {
                            retrieveChainOrQgarPolyline(_chainList, _polylineList);
                        }
                        else
                        {
                            // BLOCK 4
                            if (!strcmp(_lastGroup, _s_dxf_tag_eof))
                            {
                                endReached = true;
                            }
                            else
                            {
                                // BLOCK 5
                                if (!strcmp(_lastGroup, _s_dxf_tag_end))
                                {
                                    endReached = true;
                                }
                                else
                                {
                                    ostringstream os;
                                    os << "Junk in file: "
                                       << name_;
                                    throw QgarErrorIO(__FILE__, __LINE__,
                                                      "void qgar::DxfFile::read(bool)",
                                                      os.str());
                                }
                            } // END Block 5
                        }  // END Block 4
                    } // END Block 3
                } // END Block 2
            } // END Block 1
            else
            {
                retrieveDxfGroup();
            }
        } // END while

        if (convertPolylines)
        {
            list<QgarPolyline*>::iterator itPLL;
            for (itPLL = _polylineList.begin();
                 itPLL != _polylineList.end();
                 ++itPLL)
            {
                // Transform polyline into a list of segments
                list<QgarSegment> segList = (*itPLL)->toQgarSegList();

                for(list<QgarSegment>::iterator it = segList.begin();
                    it != segList.end();
                    ++it)
                {
                    _segmentList.push_back(new QgarSegment(*it));
                }

                // Polyline is no longer needed.
                delete *itPLL;
            }
            _polylineList.clear();
        }
    }


    // ---------------------------------------------------------------------
    // O U T P U T   C H A I N S   O F   P O I N T S
    // ----------------------------------------------------------------------


    // CHAIN OF INTEGER POINTS

    void
    DxfFile::write(AbstractGenPointChain<int>& aChain,
                   int aThickness,
                   QGEcolor aColor)
    {
        isOpenW();
        saveChain(aChain, aThickness, aColor);
    }


    // CHAIN OF FLOAT POINTS

    void
    DxfFile::write(AbstractGenPointChain<float>& aChain,
                   int aThickness,
                   QGEcolor aColor)
    {
        isOpenW();
        saveChain(aChain, aThickness, aColor);
    }


    // CHAINS OF DOUBLE POINTS

    void
    DxfFile::write(AbstractGenPointChain<double>& aChain,
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
    DxfFile::write(int aXSource,
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
    DxfFile::write(float aXSource,
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
    DxfFile::write(double aXSource,
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
    DxfFile::write(const list<GenQgarSegment<int>*>& aQSegList,
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
    DxfFile::write(int aXSource,
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
    DxfFile::write(float aXSource,
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
    DxfFile::write(double aXSource,
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
    DxfFile::write(list<GenQgarArc<int>*>& aQArcList,
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
    DxfFile::write(const GenPolyline<int>& aPoly,
                   int aThickness,
                   QGEcolor aColor,
                   QGEoutline anOutline)
    {
        isOpenW();
        savePolyline(aPoly, aThickness, aColor, anOutline);
    }


    // FLOAT POLYLINE

    void
    DxfFile::write(const GenPolyline<float>& aPoly,
                   int aThickness,
                   QGEcolor aColor,
                   QGEoutline anOutline)
    {
        isOpenW();
        savePolyline(aPoly, aThickness, aColor, anOutline);
    }


    // DOUBLE POLYLINE

    void
    DxfFile::write(const GenPolyline<double>& aPoly,
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
    DxfFile::write(GenPolygon<int>* aPolygon,
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
    DxfFile::write(const BoundingBox& aBox,
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
    DxfFile::write(const char* aText,
                   int         aX,
                   int         aY,
                   int         aHeight,
                   QGEcolor    aColor)
    {
        isOpenW();

        saveDxfGroup(_s_dxf_code_com,   _s_dxf_com_txt);
        saveDxfGroup(_s_dxf_code_ident, _s_dxf_tag_txt);
        saveDxfGroup(_s_dxf_code_layer, _s_dxf_layer_txt);

        if (aColor != QGE_COLOR_DEFAULT)
        {
            saveDxfGroup(_s_dxf_code_color, _s_dxf_colors[aColor]);
        }

        saveDxfGroup(_s_dxf_code_txthght, aHeight);
        saveDxfGroup(_s_dxf_code_txt,     aText);
        saveDxfGroup(_s_dxf_code_x1,      aX);
        saveDxfGroup(_s_dxf_code_y1,      aY);
    }


    // ---------------------------------------------------------------------
    // AUXILIARIES: SAVE DXF ENTITIES INTO THE FILE
    // ---------------------------------------------------------------------


    // SAVE THE DEFINITION OF A LAYER

    void
    DxfFile::saveDxfLayer(const char* aName,
                          int         aFlag,
                          int         aColor,
                          const char* aLType)
    {
        saveDxfGroup(_s_dxf_code_ident, _s_dxf_tag_layer);
        saveDxfGroup(_s_dxf_code_name,  aName);
        saveDxfGroup(_s_dxf_code_flag,  aFlag);
        saveDxfGroup(_s_dxf_code_color, aColor);
        saveDxfGroup(_s_dxf_code_ltp,   aLType);
    }


    // SAVE COMMON FEATURES

    void
    DxfFile::saveDxfFeatures(const char* aLayer,
                             int      aThickness,
                             QGEcolor aColor,
                             bool     isDashed)
    {
        saveDxfGroup(_s_dxf_code_layer, aLayer);

        if (aColor != QGE_COLOR_DEFAULT)
        {
            saveDxfGroup(_s_dxf_code_color, _s_dxf_colors[aColor]);
        }

        if (aThickness != 1)
        {
            saveDxfGroup(_s_dxf_code_thick, aThickness);
        }

        if (isDashed)
        {
            saveDxfGroup(_s_dxf_code_ltp, _s_dxf_default_dash);
        }
    }


    // ---------------------------------------------------------------------
    // AUXILIARIES: SAVE PRIMITIVES IN THE FILE
    // ---------------------------------------------------------------------


    // SAVE A SEGMENT WITH INTEGER COORDINATES

    void
    DxfFile::saveSegment(int aXSource,
                         int aYSource,
                         int aXTarget,
                         int aYTarget,
                         int aThickness,
                         QGEcolor aColor,
                         QGEoutline anOutline)
    {
        saveDxfGroup(_s_dxf_code_com,   _s_dxf_com_seg);
        saveDxfGroup(_s_dxf_code_ident, _s_dxf_tag_seg);

        saveDxfFeatures(_s_dxf_layer_prm,
                        aThickness,
                        aColor,
                        anOutline != QGE_OUTLINE_SOLID);

        saveDxfGroup(_s_dxf_code_x1, aXSource);
        saveDxfGroup(_s_dxf_code_y1, aYSource);

        saveDxfGroup(_s_dxf_code_x2, aXTarget);
        saveDxfGroup(_s_dxf_code_y2, aYTarget);
    }


    // SAVE AN ARC WITH INTEGER COORDINATES

    void
    DxfFile::saveArc(int aXSource,
                     int aYSource,
                     int aXTarget,
                     int aYTarget,
                     int aXCenter,
                     int aYCenter,
                     int aThickness,
                     QGEcolor aColor,
                     QGEoutline anOutline)
    {
        saveDxfGroup(_s_dxf_code_com,   _s_dxf_com_arc);
        saveDxfGroup(_s_dxf_code_ident, _s_dxf_tag_arc);

        saveDxfFeatures(_s_dxf_layer_prm,
                        aThickness,
                        aColor,
                        anOutline != QGE_OUTLINE_SOLID);

        // Center
        saveDxfGroup(_s_dxf_code_x1, aXCenter);
        saveDxfGroup(_s_dxf_code_y1, aYCenter);

        // Radius
        saveDxfGroup(_s_dxf_code_radius, qgDist(aXSource, aYSource, aXCenter, aYCenter));

        // Center point
        Point c(aXCenter,aYCenter);

        // Source angle
        saveDxfGroup(_s_dxf_code_start, 360 - qgAngleDegrees(c, Point(aXSource,aYSource)));
        // Target angle
        saveDxfGroup(_s_dxf_code_end,   360 - qgAngleDegrees(c, Point(aXTarget,aYTarget)));
    }


    // SAVE A BOUNDING BOX

    void
    DxfFile::saveBox(int aXTopLeft,
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
    // AUXILIARIES: RETRIEVE DXF ENTITIES FROM THE FILE
    // ---------------------------------------------------------------------


    // RETRIEVE A DXF GROUP FROM THE FILE
    // Return the code of the group that has been read, and put
    // the corresponding value in the qgar::DxfFile::lastGroup
    // data member as a chain of characters.
    // Comment are ignored.

    int
    DxfFile::retrieveDxfGroup()
    {
        char buf[_s_dxf_maxbuf];

        // Read code and value of the group.
        fstream_.getline(buf, _s_dxf_maxbuf);
        int code = atoi(buf);

        fstream_.getline(buf, _s_dxf_maxbuf);

        // If the group is a comment, read the next one
        if (code == _s_dxf_code_com)
        {
            return(retrieveDxfGroup());
        }
        else
        {
            int coord;

            _lastGroupCode = code;
            strcpy(_lastGroup, buf);

            // Windows ASCII files include lines terminated by '\r\n'.
            // '\r' is replaced by '\0' as it causes trouble
            // to the analysis of the DXF file.
            if (_lastGroup[strlen(_lastGroup) - 1] == '\r')
                _lastGroup[strlen(_lastGroup) - 1] = '\0';

            // Update maximal coordinates
            if ((code == _s_dxf_code_x1) || (code == _s_dxf_code_x2))
            {
                coord = atoi(buf);

                if (coord > _maxX)
                {
                    _maxX = coord;
                }
            }

            if ((code == _s_dxf_code_y1) || (code == _s_dxf_code_y2))
            {
                coord = atoi(buf);

                if (coord > _maxY)
                {
                    _maxY = coord;
                }
            }

            // Return result
            return(code);
        }
    }


    // RETRIEVE POINTS (VERTICES OF A POLYLINE) FROM THE FILE
    //
    // aThickness: only significant when the function is called
    // to construct a Qgar polyline

    void
    DxfFile::retrievePoints(list<Point>& anEdgeList,
                            int* aThickness,
                            bool* isDashed)
    {
        *aThickness = 1;
        *isDashed   = false;
        retrieveDxfGroup();

        while (_lastGroupCode != _s_dxf_code_ident)
        {
            switch (_lastGroupCode)
            {
                case _s_dxf_code_thick:
                    *aThickness = atoi(_lastGroup);
                    break;
                case _s_dxf_code_ltp:
                    if (!strcmp(_lastGroup, _s_dxf_default_dash))
                    {
                        *isDashed = true;
                    }
                    break;
                default:
                    // VOID
                    break;
            }
            retrieveDxfGroup();
        }

        Point pt;
        while (!strcmp(_lastGroup, _s_dxf_tag_vert))
        {
            while (retrieveDxfGroup() != _s_dxf_code_ident)
            {
                switch (_lastGroupCode)
                {
                    case _s_dxf_code_x1:
                        pt.setX(atoi(_lastGroup));
                        break;
                    case _s_dxf_code_y1:
                        pt.setY(atoi(_lastGroup));
                        break;
                    default:
                        // VOID
                        break;
                }
            }
            anEdgeList.push_back(pt);
        }

        if (!strcmp(_lastGroup, _s_dxf_tag_esq))
        {
            retrieveDxfGroup();
        }
    }


    // ---------------------------------------------------------------------
    // AUXILIARIES:
    // RETRIEVE A PRIMITIVE FROM THE FILE AND APPEND IT TO A LIST
    // ---------------------------------------------------------------------


    // RETRIEVE A SEGMENT ENTITY FROM THE FILE

    void
    DxfFile::retrieveQgarSegment(list<GenQgarSegment<int>*>& aSegList)



    {
        if (retrieveDxfGroup() == _s_dxf_code_layer)
        {
            if (!strcmp(_lastGroup, _s_dxf_layer_prm))
            {
                retrieveDxfGroup();
                aSegList.push_back(retrievePQgarSegment());
            }
            else
            {
                ostringstream os;
                os << "Junk in file "
                   << name_;
                throw QgarErrorIO(__FILE__, __LINE__,
                                  "void qgar::DxfFile::retrieveQgarSegment(std::list<qgar::GenQgarSegment<int>*>&)",
                                  os.str());
            }
        }
        else
        {
            aSegList.push_back(retrievePQgarSegment());
        }
    }


    // RETRIEVE AN ARC ENTITY FROM THE FILE

    void
    DxfFile::retrieveQgarArc(list<GenQgarArc<int>*>& anArcList)



    {
        if (retrieveDxfGroup() == _s_dxf_code_layer)
        {
            if (!strcmp(_lastGroup, _s_dxf_layer_prm))
            {
                retrieveDxfGroup();
                anArcList.push_back(retrievePQgarArc());
            }
            else
            {
                ostringstream os;
                os << "Junk in file "
                   << name_;
                throw QgarErrorIO(__FILE__, __LINE__,
                                  "void qgar::DxfFile::retrieveQgarArc(std::list<qgar::GenQgarArc<int>*>&)",
                                  os.str());
            }
        }
        else
        {
            anArcList.push_back(retrievePQgarArc());
        }
    }


    // RETRIEVE A POLYLINE ENTITY FROM THE FILE
    //
    // aChainList   when the entity is a chain,
    //              it is added to the end of the list
    // aPolyList    when the entity is a polyline,
    //              it is added to the end of the list

    void
    DxfFile::retrieveChainOrQgarPolyline(list<GenPointChain<int>*>& aChainList,
                                         list<GenQgarPolyline<int>*>& aPolyList)



    {
        if (retrieveDxfGroup() == _s_dxf_code_layer)
        {
            if (!strcmp(_lastGroup, _s_dxf_layer_chain))
            {
                aChainList.push_back(retrievePChain());
            }
            else
            {
                if (!strcmp(_lastGroup, _s_dxf_layer_polyl))
                {
                    aPolyList.push_back(retrievePQgarPolyline());
                }
                else
                {
                    ostringstream os;
                    os << "Junk in file "
                       << name_;
                    throw QgarErrorIO(__FILE__, __LINE__,
                                      "void qgar::DxfFile::retrieveChainOrQgarPolyline(std::list<qgar::GenPointChain<int>*>&, std::list<qgar::GenQgarPolyline<int>*>&)",
                                      os.str());
                }
            }
        }
        else
        {
            ostringstream os;
            os << "Junk in file "
               << name_;
            throw QgarErrorIO(__FILE__, __LINE__,
                              "void qgar::DxfFile::retrieveChainOrQgarPolyline(std::list<qgar::GenPointChain<int>*>&, std::list<qgar::GenQgarPolyline<int>*>&)",
                              os.str());
        }
    }


    // ---------------------------------------------------------------------
    // AUXILIARIES: GET A POINTER TO A PRIMITIVE OF THE FILE
    // ---------------------------------------------------------------------


    // GET A POINTER TO A (QGAR) SEGMENT FROM THE FILE

    GenQgarSegment<int>*
    DxfFile::retrievePQgarSegment()
    {
        Point p1;
        Point p2;
        int thickness   = 1;
        bool isDashed = false;

        while (_lastGroupCode != _s_dxf_code_ident)
        {
            switch (_lastGroupCode)
            {
                case _s_dxf_code_x1:
                    p1.setX(atoi(_lastGroup));
                    break;
                case _s_dxf_code_y1:
                    p1.setY(atoi(_lastGroup));
                    break;
                case _s_dxf_code_x2:
                    p2.setX(atoi(_lastGroup));
                    break;
                case _s_dxf_code_y2:
                    p2.setY(atoi(_lastGroup));
                    break;
                case _s_dxf_code_thick:
                    thickness = atoi(_lastGroup);
                    break;
                case _s_dxf_code_ltp:
                    if (!strcmp(_lastGroup, _s_dxf_default_dash))
                    {
                        isDashed = true;
                    }
                    break;
                default:
                    break;
            }
            retrieveDxfGroup();
        }

        return new GenQgarSegment<int>(p1,
                                       p2,
                                       thickness,
                                       QGE_COLOR_DEFAULT,
                                       isDashed
                                       ? QGE_OUTLINE_DASH_SSPACED
                                       : QGE_OUTLINE_SOLID);
    }


    // GET A POINTER TO A (QGAR) ARC FROM THE FILE

    GenQgarArc<int>*
    DxfFile::retrievePQgarArc()
    {
        int x;
        int y;
        double radius = 0.f;
        double startAngle = 0.f;
        double endAngle = 0.f;
        int thickness = 1;
        bool isDashed = false;

        while (_lastGroupCode != _s_dxf_code_ident)
        {
            switch (_lastGroupCode)
            {
                case _s_dxf_code_x1:
                    x = atoi(_lastGroup);
                    break;
                case _s_dxf_code_y1:
                    y = atoi(_lastGroup);
                    break;
                case _s_dxf_code_radius:
                    radius = atof(_lastGroup);
                    break;
                case _s_dxf_code_start:
                    startAngle = atof(_lastGroup);
                    break;
                case _s_dxf_code_end:
                    endAngle = atof(_lastGroup);
                    break;
                case _s_dxf_code_thick:
                    thickness = atoi(_lastGroup);
                    break;
                case _s_dxf_code_ltp:
                    if (!strcmp(_lastGroup, _s_dxf_default_dash))
                    {
                        isDashed = true;
                    }
                    break;
                default:
                    break;
            }
            retrieveDxfGroup();
        }

        double sAng = qgDegreesToRadians(360. - endAngle);
        double tAng = qgDegreesToRadians(360. - startAngle);

        return
                new GenQgarArc<int>(GenPoint<int>(x + (int) (radius * cos(sAng)),
                                                  y + (int) (radius * sin(sAng))),
                                    GenPoint<int>(x + (int) (radius * cos(tAng)),
                                                  y + (int) (radius * sin(tAng))),
                                    GenPoint<int>(x,y),
                                    thickness,
                                    QGE_COLOR_DEFAULT,
                                    isDashed
                                    ? QGE_OUTLINE_DASH_SSPACED
                                    : QGE_OUTLINE_SOLID);
    }


    // GET A POINTER TO A (QGAR) POLYLINE FROM THE FILE

    GenQgarPolyline<int>*
    DxfFile::retrievePQgarPolyline()
    {
        list<Point> pointList;
        int thickness;
        bool isDashed;
        retrievePoints(pointList, &thickness, &isDashed);

        list<Point>::iterator itPL = pointList.begin();
        Segment seg(*itPL++, *itPL++);
        QgarPolyline* polyline =
                new QgarPolyline(seg,
                                 thickness,
                                 QGE_COLOR_DEFAULT,
                                 isDashed
                                 ? QGE_OUTLINE_DASH_SSPACED
                                 : QGE_OUTLINE_SOLID);

        while (itPL != pointList.end())
        {
            polyline->appendTarget(*itPL);
            ++itPL;
        }

        return (polyline);
    }


    // GET A POINTER TO A CHAIN OF POINTS FROM THE FILE

    PointChain*
    DxfFile::retrievePChain()
    {
        list<Point> pointList;
        list<Point>::iterator itPL;
        int  unusedThickness;
        bool unusedDashFlag;

        retrievePoints(pointList, &unusedThickness, &unusedDashFlag);
        PointChain* chain = new PointChain();

        for (itPL = pointList.begin(); itPL != pointList.end(); ++itPL)
        {
            chain->push_back(*itPL);
        }

        return chain;
    }


    // ---------------------------------------------------------------------
    // PRIVATE FUNCTIONS NOT YET IMPLEMENTED
    // ---------------------------------------------------------------------


    // =================
    // OUTPUT COMPONENTS
    // =================


    // WRITE A (CONNECTED) COMPONENT

    void
    DxfFile::write(const ConnectedComponents::node_type* const aPNode,
                   int        aThickness,
                   QGEcolor   aColor,
                   QGEoutline anOutline)



    {
        Q_UNUSED(aPNode);
        Q_UNUSED(aThickness);
        Q_UNUSED(aColor);
        Q_UNUSED(anOutline);
        throw QgarErrorDeveloper(__FILE__, __LINE__,
                                 "void qgar::DxfFile::write(const qgar::ConnectedComponents::node_type* const, int, qgar::QGEcolor, qgar::QGEoutline)",
                                 "Not yet implemented: See Phil Buzz!");
    }


    // ==============
    // OUTPUT CIRCLES
    // ==============


    // WRITE A CIRCLE WITH COORDINATES OF TYPE 'int'

    void
    DxfFile::write(int aXCenter,
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
                                 "void qgar::DxfFile::write(int, int, double, int, qgar::QGEcolor, qgar::QGEoutline)",
                                 "Not yet implemented: See Phil Buzz!");
    }


    // WRITE A CIRCLE WITH COORDINATES OF TYPE 'float'

    void
    DxfFile::write(float aXCenter,
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
                                 "void qgar::DxfFile::write(float, float, double, int, qgar::QGEcolor, qgar::QGEoutline)",
                                 "Not yet implemented: See Phil Buzz!");
    }


    // WRITE AN ARC WITH COORDINATES OF TYPE 'double'

    void
    DxfFile::write(double aXCenter,
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
                                 "void qgar::DxfFile::write(double, double, double, int, qgar::QGEcolor, qgar::QGEoutline)",
                                 "Not yet implemented: See Phil Buzz!");
    }


    // =============
    // OUTPUT POINTS
    // =============


    // WRITE A POINT WITH COORDINATES OF TYPE 'int'

    void
    DxfFile::write(int aX, int aY, int aThickness, QGEcolor aColor)
    {
        Q_UNUSED(aX);
        Q_UNUSED(aY);
        Q_UNUSED(aThickness);
        Q_UNUSED(aColor);
        throw QgarErrorDeveloper(__FILE__, __LINE__,
                                 "void qgar::DxfFile::write(int, int, int, qgar::QGEcolor)",
                                 "Not yet implemented: See Phil Buzz!");
    }


    // WRITE A POINT WITH COORDINATES OF TYPE 'float'

    void
    DxfFile::write(float aX, float aY, int aThickness, QGEcolor aColor)
    {
        Q_UNUSED(aX);
        Q_UNUSED(aY);
        Q_UNUSED(aThickness);
        Q_UNUSED(aColor);
        throw QgarErrorDeveloper(__FILE__, __LINE__,
                                 "void qgar::DxfFile::write(float, float, int, qgar::QGEcolor)",
                                 "Not yet implemented: See Phil Buzz!");
    }



    // WRITE A POINT WITH COORDINATES OF TYPE 'double'

    void
    DxfFile::write(double aX, double aY, int aThickness, QGEcolor aColor)
    {
        Q_UNUSED(aX);
        Q_UNUSED(aY);
        Q_UNUSED(aThickness);
        Q_UNUSED(aColor);
        throw QgarErrorDeveloper(__FILE__, __LINE__,
                                 "void qgar::DxfFile::write(double, double, int, qgar::QGEcolor)",
                                 "Not yet implemented: See Phil Buzz!");
    }


    // --------------------------------------------------------------------

} // namespace qgar
