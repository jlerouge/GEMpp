/*---------------------------------------------------------------------+
 | Library QgarLib, graphics analysis and recognition                  |
 | Copyright (C) 2005  Qgar Project, LORIA                             |
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
 * @file VecFile.cpp
 *
 * @brief Implementation of class qgar::VecFile.
 *
 * See file VecFile.h for the interface.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   November 17, 2005  15:36
 * @since  qgar 2.2
 */


// STD
#include <cstring>
#include <iostream>
#include <sstream>
// QGAR
#include "AbstractGenPointChain.h"
#include "BoundingBox.h"
#include "ConnectedComponents.h"
#include "GenPointChain.h"
#include "primitives.h"
#include "QgarErrorDeveloper.h"
#include "QgarErrorIO.h"
#include "QgarErrorUser.h"
#include "VecFile.h"



namespace qgar
{


// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
// V E C   S Y N T A C T I C A L   F E A T U R E S   ( S T A T I C )
// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS


// ====
// FILE
// ====


// MAXIMUM LENGTH OF A FILE LINE
const int VecFile::s_vec_line_size_ = 255;


// =======
// VERSION
// =======


// MAXIMUM LENGTH OF THE VERSION STRING
const int VecFile::s_vec_version_size_ = 15;

// SUPPORTED VERSION
const char* const VecFile::s_vec_version_nb_ = "VEC-1.0";


// ========
// COMMENTS
// ========

// TOKEN INTRODUCING COMMENTS
const char VecFile::s_vec_comment_ = '%';


// ==========
// RESOLUTION
// ==========


const int VecFile::s_vec_dpi_unknown_ = -1;  // unknown


// ==========
// PRIMITIVES
// ==========


// PRIMITIVE CODES
const char VecFile::s_vec_prim_none_    = '0';  // none
const char VecFile::s_vec_prim_arc_     = 'A';  // arc of circle
const char VecFile::s_vec_prim_circle_  = 'C';  // circle
const char VecFile::s_vec_prim_segment_ = 'L';  // line segment
const char VecFile::s_vec_prim_text_    = 'T';  // textual region


// OUTLINES
const char VecFile::s_vec_outline_continuous_ = 'C';  // continuous (solid)
const char VecFile::s_vec_outline_dashed_     = 'D';  // dashed


// TEXT FEATURES

const double VecFile::s_vec_text_unknown_ = -1.; // value of an unknown feature
const int    VecFile::s_vec_text_size_    = 127; // maximum length of text string


// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
// E N D   O F   V E C   S Y N T A C T I C A L   F E A T U R E S
// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS




// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------


// WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
// - Add 1 character for the NULL termination character
//   when allocating character chains
// - Add 1 character for the NULL character which is automatically
//   appended to an input line when allocating the input buffer
// WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW


// INITIALIZE WITH GIVEN FILE NAME

VecFile::VecFile(const char* aFileName)

    : AbstractGraphicsFile(aFileName),
      inBuf_         (new char[s_vec_line_size_ + 1]),    // I/O buffer
      fileVersion_   (new char[s_vec_version_size_ + 1]), // string for version
      xsize_         (0),
      ysize_         (0),
      dpi_           (s_vec_dpi_unknown_),                // unknown resolution
      eof_flag_      (false),                             // not EOF
      lastPrimitive_ (s_vec_prim_none_),                  // no input primitive yet
      text_          (new char[s_vec_text_size_ + 1])     // string for text

{
    // VOID
}


// INITIALIZE WITH GIVEN FILE NAME, SIZE AND RESOLUTION

VecFile::VecFile(const char* aFileName,
                 int aWidth,
                 int aHeight,
                 int aDpi)

    : AbstractGraphicsFile(aFileName),
      inBuf_         (new char[s_vec_line_size_ + 1]),    // I/O buffer
      fileVersion_   (new char[s_vec_version_size_ + 1]), // string for version
      xsize_         (aWidth),
      ysize_         (aHeight),
      dpi_           (aDpi),
      eof_flag_      (false),                             // not EOF
      lastPrimitive_ (s_vec_prim_none_),                  // no input primitive yet
      text_          (new char[s_vec_text_size_ + 1])     // string for text

{
    // VOID
}


// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------


VecFile::~VecFile()
{
    // Delete character chains allocated by constructors
    delete [] inBuf_;
    delete [] fileVersion_;
    delete [] text_;
}


// -------------------------------------------------------------------
// H E A D E R   &   F O O T E R 
// -------------------------------------------------------------------


// READ THE HEADER OF A VEC FILE

void
VecFile::readHeader()



{
    // Read the current line
    fstream_.getline(inBuf_, s_vec_line_size_);

    // First character must introduce a comment
    if (inBuf_[0] != s_vec_comment_)
    {
        std::ostringstream os;
        os << "Bad header in file "
           << name_
           << ": first character should be "
           << s_vec_comment_;
        throw QgarErrorIO(__FILE__, __LINE__,
                          "void qgar::VecFile::readHeader()",
                          os.str());
    }

    // Store current line into a string stream
    std::istringstream iss(std::string((const char*)(inBuf_ + 1)),
                           std::istringstream::in);

    // Get version number
    iss >> fileVersion_;

    // The version number must conform to the supported version
    if (strcmp(fileVersion_, s_vec_version_nb_) != 0)
    {
        std::ostringstream os;
        os << "Bad VEC version in file "
           << name_
           << ": "
           << fileVersion_
           << " not supported, should be "
           << s_vec_version_nb_;
        throw QgarErrorUser(__FILE__, __LINE__,
                            "void qgar::VecFile::readHeader()",
                            os.str());
    }

    // Get X and Y maximum coordinates (width and height)
    iss >> xsize_;
    iss >> ysize_;

    if (iss.eof())
    {
        // End of line: no resolution given
        dpi_ = s_vec_dpi_unknown_;
    }
    else
    {
        // Get resolution
        iss >> dpi_;

        if (!(iss.eof()))
        {
            // Line not terminated: bad header
            std::ostringstream os;
            os << "Bad header in file "
               << name_
               << ": "
               << inBuf_;
            throw QgarErrorIO(__FILE__, __LINE__,
                              "void qgar::VecFile::readHeader()",
                              os.str());
        }
    }
}


// WRITE THE HEADER OF A VEC FILE

void
VecFile::writeHeader()
{
    fstream_ << s_vec_comment_     // first character
             << s_vec_version_nb_  // VEC version
             << ' '
             << xsize_             // maximum X coordinate
             << ' '
             << ysize_;            // maximum Y coordinate

    // Possible initial resolution
    if (dpi_ != s_vec_dpi_unknown_)
    {
        fstream_ << ' ' << dpi_;
    }

    fstream_ << std::endl;
}


// -------------------------------------------------------------------
// I N P U T
// -------------------------------------------------------------------


// INPUT NEXT PRIMITIVE IN FILE

char
VecFile::read()



{
    // File open for reading?
    isOpenR();

    // Read the current line
    fstream_.getline(inBuf_, s_vec_line_size_);

    // End of file?
    if (fstream_.eof())
    {
        eof_flag_ = true;
        return EOF ;
    }

    // Store current line into a string stream
    std::istringstream iss(std::string((const char*)inBuf_),
                           std::istringstream::in);

    // Get primitive type
    iss >> lastPrimitive_;

    switch (lastPrimitive_)
    {
    // ***************************************************************
    // S E G M E N T
    // ***************************************************************
    case s_vec_prim_segment_:

        getOutline(iss);    // outline
        iss >> x1_          // X source
            >> y1_          // Y source
            >> x2_          // X target
            >> y2_          // Y target
            >> thickness_;  // thickness

        break;

        // ***************************************************************
        // C I R C L E
        // ***************************************************************
    case s_vec_prim_circle_:

        getOutline(iss);    // outline
        iss >> x1_          // X center
            >> y1_          // Y center
            >> radius_      // radius
            >> thickness_;  // thickness

        break;

        // ***************************************************************
        // A R C   O F   C I R C L E
        // ***************************************************************
    case s_vec_prim_arc_:

        getOutline(iss);           // outline
        iss >> x1_                 // X center
            >> y1_                 // Y center
            >> radius_             // radius
            >> startAngleDegrees_  // source angle
            >> endAngleDegrees_    // target angle
            >> thickness_;         // thickness

        break;

        // ***************************************************************
        // T E X T U A L   R E G I O N
        // ***************************************************************
    case s_vec_prim_text_:

        iss >> x1_                   // X coordinate of insertion point
            >> y1_                   // Y coordinate of insertion point
            >> x2_                   // X coordinate of opposite point
            >> y2_                   // Y coordinate of opposite point
            >> orientationDegrees_   // base line angle
            >> fontHeight_           // font height
            >> fontWidthFactor_      // font width factor
            >> fontStrokeWidth_;     // font stroke width

        // Skip space characters
        char c;
        do
        {
            c = iss.get();
        }
        while (c == ' ');

        // Text string must be a introduced as a comment
        if (c != s_vec_comment_)
        {
            std::ostringstream os;
            os << "Bad text string in file "
               << name_
               << ": "
               << " should be introduced by "
               << s_vec_comment_;
            throw QgarErrorIO(__FILE__, __LINE__,
                              "void qgar::VecFile::read()", os.str());
        }

        // Read text string
        iss >> text_;

        break;

        // ***************************************************************
        // E R R O R :   U N K N O W N   P R I M I T I V E   T Y P E
        // ***************************************************************
    default:

        std::ostringstream os;
        os << "Unknown primitive in file "
           << name_
           << ": "
           << lastPrimitive_;
        throw QgarErrorIO(__FILE__, __LINE__,
                          "void qgar::VecFile::read()", os.str());

        // ***************************************************************
    } // END switch

    // End of line?
    if (!iss.eof())
    {
        std::ostringstream os;
        os << "Junk in file "
           << name_
           << ": "
           << inBuf_;
        throw QgarErrorIO(__FILE__, __LINE__,
                          "void qgar::VecFile::read()", os.str());
    }

    // Return primitive type
    return lastPrimitive_;
}


// ---------------------------------------------------------------------
// O U T P U T   S E G M E N T S 
// ---------------------------------------------------------------------


// OUTPUT A SEGMENT WITH COORDINATES OF TYPE int

void
VecFile::write(int aXSource,
               int aYSource,
               int aXTarget,
               int aYTarget,
               int        aThickness,
               QGEcolor   aColor,
               QGEoutline anOutline)
{
    Q_UNUSED(aColor);
    isOpenW();

    fstream_ << s_vec_prim_segment_     // primitive code
             << ' '
             << toVecOutline(anOutline) // continuous|dashed
             << ' '
             << aXSource                // x1
             << ' '
             << aYSource                // y1
             << ' '
             << aXTarget                // x2
             << ' '
             << aYTarget                // y2
             << ' '
             << aThickness              // width
             << std::endl;
}


// OUTPUT A SEGMENT WITH COORDINATES OF TYPE float

void
VecFile::write(float aXSource,
               float aYSource,
               float aXTarget,
               float aYTarget,
               int        aThickness,
               QGEcolor   aColor,
               QGEoutline anOutline)
{
    write((int) aXSource,
          (int) aYSource,
          (int) aXTarget,
          (int) aYTarget,
          aThickness,
          aColor,
          anOutline);
}


// OUTPUT A SEGMENT WITH COORDINATES OF TYPE double

void
VecFile::write(double aXSource,
               double aYSource,
               double aXTarget,
               double aYTarget,
               int        aThickness,
               QGEcolor   aColor,
               QGEoutline anOutline)
{
    write((int) aXSource,
          (int) aYSource,
          (int) aXTarget,
          (int) aYTarget,
          aThickness,
          aColor,
          anOutline);
}


// ---------------------------------------------------------------------
// O U T P U T   C I R C L E S
// ---------------------------------------------------------------------


// OUTPUT A CIRCLE WITH COORDINATES OF TYPE int

void
VecFile::write(int aXCenter,
               int aYCenter,
               double aRadius,
               int        aThickness,
               QGEcolor   aColor,
               QGEoutline anOutline)
{
    Q_UNUSED(aColor);
    isOpenW();

    fstream_ << s_vec_prim_circle_      // primitive code
             << ' '
             << toVecOutline(anOutline) // continuous|dashed
             << ' '
             << aXCenter                // xcenter
             << ' '
             << aYCenter                // ycenter
             << ' '
             << aRadius                 // radius
             << ' '
             << aThickness              // width
             << std::endl;
}


// OUTPUT A CIRCLE WITH COORDINATES OF TYPE float

void
VecFile::write(float aXCenter,
               float aYCenter,
               double aRadius,
               int        aThickness,
               QGEcolor   aColor,
               QGEoutline anOutline)
{
    write((int) aXCenter,
          (int) aYCenter,
          aRadius,
          aThickness,
          aColor,
          anOutline);
}


// OUTPUT A CIRCLE WITH COORDINATES OF TYPE double

void
VecFile::write(double aXCenter,
               double aYCenter,
               double aRadius,
               int        aThickness,
               QGEcolor   aColor,
               QGEoutline anOutline)
{
    write((int) aXCenter,
          (int) aYCenter,
          aRadius,
          aThickness,
          aColor,
          anOutline);
}


// ---------------------------------------------------------------------
// O U T P U T   A R C S   O F   C I R C L E
// ---------------------------------------------------------------------


// OUTPUT AN ARC WITH COORDINATES OF TYPE int

void
VecFile::write(int aXSource,
               int aYSource,
               int aXTarget,
               int aYTarget,
               int aXCenter,
               int aYCenter,
               int        aThickness,
               QGEcolor   aColor,
               QGEoutline anOutline)
{
    Q_UNUSED(aColor);
    isOpenW();

    fstream_ << s_vec_prim_arc_         // primitive code
             << ' '
             << toVecOutline(anOutline) // continuous|dashed
             << ' '
             << aXCenter                // xcenter
             << ' '
             << aYCenter                // ycenter
             << ' '
             << qgDist(aXCenter, aYCenter, aXSource, aYSource)  // radius
             << ' '
             << qgAngleDegrees(Point(aXCenter,aYCenter),
                               Point(aXSource,aYSource))  // source angle
             << ' '
             << qgAngleDegrees(Point(aXCenter,aYCenter),
                               Point(aXTarget,aYTarget))  // target angle
             << ' '
             << aThickness              // width
             << std::endl;
}


// OUTPUT AN ARC WITH COORDINATES OF TYPE float

void
VecFile::write(float aXSource,
               float aYSource,
               float aXTarget,
               float aYTarget,
               float aXCenter,
               float aYCenter,
               int        aThickness,
               QGEcolor   aColor,
               QGEoutline anOutline)
{
    write((int) aXSource,
          (int) aYSource,
          (int) aXTarget,
          (int) aYTarget,
          (int) aXCenter,
          (int) aYCenter,
          aThickness,
          aColor,
          anOutline);
}


// OUTPUT AN ARC WITH COORDINATES OF TYPE double

void
VecFile::write(double aXSource,
               double aYSource,
               double aXTarget,
               double aYTarget,
               double aXCenter,
               double aYCenter,
               int        aThickness,
               QGEcolor   aColor,
               QGEoutline anOutline)
{
    write((int) aXSource,
          (int) aYSource,
          (int) aXTarget,
          (int) aYTarget,
          (int) aXCenter,
          (int) aYCenter,
          aThickness,
          aColor,
          anOutline);
}


// ---------------------------------------------------------------------
// O U T P U T   T E X T U A L   R E G I O N S
// ---------------------------------------------------------------------


// OUTPUT A TEXTUAL REGION

void
VecFile::write(int aXInsert,
               int aYInsert,
               int aXOpposite,
               int aYOpposite,
               double anOrientationDegrees,
               const char* aText,
               double aFontHeight,
               double aFontWidth,
               double aFontStrokeWidth)
{
    isOpenW();

    fstream_ << s_vec_prim_text_        // primitive code
             << ' '
             << aXInsert                // x1
             << ' '
             << aYInsert                // y1
             << ' '
             << aXOpposite              // x2
             << ' '
             << aYOpposite              // y2
             << ' '
             << anOrientationDegrees    // angle of the base line of the text
             << ' '
             << aFontHeight             // font height
             << ' '
             << aFontWidth              // font width
             << ' '
             << aFontStrokeWidth        // font stroke width
             << ' '
             << s_vec_comment_          // character introducing text
             << aText                   // text string
             << std::endl;
}


// ---------------------------------------------------------------------
// A U X I L I A R I E S
// ---------------------------------------------------------------------


// CONVERT A QGAR OUTLINE TO A VEC OUTLINE

char
VecFile::toVecOutline(QGEoutline anOutline) const
{
    return
            ((anOutline == QGE_OUTLINE_NONE)    ||
             (anOutline == QGE_OUTLINE_SOLID)   ||
             (anOutline == QGE_OUTLINE_DEFAULT))
            ? s_vec_outline_continuous_
            : s_vec_outline_dashed_;
}


// GET AN OUTLINE FROM THE FILE

void
VecFile::getOutline(std::istringstream& anIStream)



{
    char vecOutline;
    anIStream >> vecOutline;

    switch (vecOutline)
    {
    // CONTINUOUS
    case s_vec_outline_continuous_:
        outline_ = QGE_OUTLINE_SOLID;
        break;

        // DASHED
    case s_vec_outline_dashed_:
        outline_ = QGE_OUTLINE_DASH_REGULAR;
        break;

        // UNKNOWN
    default:
        std::ostringstream os;
        os << "Unknown outline in file "
           << name_
           << ": "
           << inBuf_;
        throw QgarErrorIO(__FILE__, __LINE__,
                          "void qgar::VecFile::getOutline(const std::istringstream&)",
                          os.str());
    } // END switch
}


// ---------------------------------------------------------------------
// P R I V A T E   F U N C T I O N S   N O T   I M P L E M E N T E D
// ---------------------------------------------------------------------


// =============
// OUTPUT POINTS
// =============


// OUTPUT A POINT WITH COORDINATES OF TYPE int

void
VecFile::write(int aX, int aY, int aThickness, QGEcolor aColor)



{
    Q_UNUSED(aX);
    Q_UNUSED(aY);
    Q_UNUSED(aThickness);
    Q_UNUSED(aColor);
    throw QgarErrorDeveloper(__FILE__, __LINE__,
                             "void qgar::DxfFile::write(int, int, int, qgar::QGEcolor)",
                             "Points are not supported by current VEC format!");
}


// OUTPUT A POINT WITH COORDINATES OF TYPE float

void
VecFile::write(float aX, float aY, int aThickness, QGEcolor aColor)



{
    Q_UNUSED(aX);
    Q_UNUSED(aY);
    Q_UNUSED(aThickness);
    Q_UNUSED(aColor);
    throw QgarErrorDeveloper(__FILE__, __LINE__,
                             "void qgar::DxfFile::write(float, float, int, qgar::QGEcolor)",
                             "Points are not supported by current VEC format!");
}


// OUTPUT A POINT WITH COORDINATES OF TYPE double

void
VecFile::write(double aX, double aY, int aThickness, QGEcolor aColor)



{
    Q_UNUSED(aX);
    Q_UNUSED(aY);
    Q_UNUSED(aThickness);
    Q_UNUSED(aColor);
    throw QgarErrorDeveloper(__FILE__, __LINE__,
                             "void qgar::DxfFile::write(double, double, int, QGEcolor)",
                             "Points are not supported by current VEC format!");
}


// =======================
// OUTPUT CHAINS OF POINTS
// =======================


// OUTPUT A CHAIN OF POINTS WITH COORDINATES OF TYPE int

void
VecFile::write(AbstractGenPointChain<int>& aChain,
               int aThickness,
               QGEcolor aColor)



{
    Q_UNUSED(aChain);
    Q_UNUSED(aThickness);
    Q_UNUSED(aColor);
    throw QgarErrorDeveloper(__FILE__, __LINE__,
                             "void qgar::DxfFile::write(qgar::AbstractGenPointChain<int>&, int, qgar::QGEcolor)",
                             "Chains of points are not supported by current VEC format!");
}


// OUTPUT A CHAIN OF POINTS WITH COORDINATES OF TYPE float

void
VecFile::write(AbstractGenPointChain<float>& aChain,
               int aThickness,
               QGEcolor aColor)



{
    Q_UNUSED(aChain);
    Q_UNUSED(aThickness);
    Q_UNUSED(aColor);
    throw QgarErrorDeveloper(__FILE__, __LINE__,
                             "void qgar::DxfFile::write(qgar::AbstractGenPointChain<float>&, int, qgar::QGEcolor)",
                             "Chains of points are not supported by current VEC format!");
}


// OUTPUT A CHAIN OF POINTS WITH COORDINATES OF TYPE double

void
VecFile::write(AbstractGenPointChain<double>& aChain,
               int aThickness,
               QGEcolor aColor)



{
    Q_UNUSED(aChain);
    Q_UNUSED(aThickness);
    Q_UNUSED(aColor);
    throw QgarErrorDeveloper(__FILE__, __LINE__,
                             "void qgar::DxfFile::write(qgar::AbstractGenPointChain<double>&, int, qgar::QGEcolor)",
                             "Chains of points are not supported by current VEC format!");
}


// ================
// OUTPUT POLYLINES
// ================


// OUTPUT A POLYLINE WITH COORDINATES OF TYPE int

void
VecFile::write(const GenPolyline<int>& aPoly,
               int aThickness,
               QGEcolor aColor,
               QGEoutline anOutline)



{
    Q_UNUSED(aPoly);
    Q_UNUSED(aThickness);
    Q_UNUSED(aColor);
    Q_UNUSED(anOutline);
    throw QgarErrorDeveloper(__FILE__, __LINE__,
                             "void qgar::DxfFile::write(const qgar::GenPolyline<int>&, int, qgar::QGEcolor, qgar::QGEoutline)",
                             "Polylines are not supported by current VEC format!");
}


// OUTPUT A POLYLINE WITH COORDINATES OF TYPE float

void
VecFile::write(const GenPolyline<float>& aPoly,
               int aThickness,
               QGEcolor aColor,
               QGEoutline anOutline)



{
    Q_UNUSED(aPoly);
    Q_UNUSED(aThickness);
    Q_UNUSED(aColor);
    Q_UNUSED(anOutline);
    throw QgarErrorDeveloper(__FILE__, __LINE__,
                             "void qgar::DxfFile::write(const qgar::GenPolyline<float>&, int, qgar::QGEcolor, qgar::QGEoutline)",
                             "Polylines are not supported by current VEC format!");
}


// OUTPUT A POLYLINE WITH COORDINATES OF TYPE double

void
VecFile::write(const GenPolyline<double>& aPoly,
               int aThickness,
               QGEcolor aColor,
               QGEoutline anOutline)



{
    Q_UNUSED(aPoly);
    Q_UNUSED(aThickness);
    Q_UNUSED(aColor);
    Q_UNUSED(anOutline);
    throw QgarErrorDeveloper(__FILE__, __LINE__,
                             "void qgar::DxfFile::write(const qgar::GenPolyline<double>&, int, qgar::QGEcolor, qgar::QGEoutline)",
                             "Polylines are not supported by current VEC format!");
}


// =====================
// OUTPUT BOUNDING BOXES
// =====================


// OUTPUT A BOUNDING BOX WITH COORDINATES OF TYPE int

void
VecFile::write(const BoundingBox& aBox,
               int aThickness,
               QGEcolor aColor,
               QGEoutline anOutline)



{
    Q_UNUSED(aBox);
    Q_UNUSED(aThickness);
    Q_UNUSED(aColor);
    Q_UNUSED(anOutline);
    throw QgarErrorDeveloper(__FILE__, __LINE__,
                             "void qgar::DxfFile::write(const qgar::BoundingBox&, int, qgar::QGEcolor, qgar::QGEoutline)",
                             "Polylines are not supported by current VEC format!");
}


// =============================
// OUTPUT (CONNECTED) COMPONENTS
// =============================


// RECORD A (CONNECTED) COMPONENT

void
VecFile::write(const ConnectedComponents::node_type* const aPNode,
               int aThickness,
               QGEcolor aColor,
               QGEoutline anOutline)



{
    Q_UNUSED(aPNode);
    Q_UNUSED(aThickness);
    Q_UNUSED(aColor);
    Q_UNUSED(anOutline);
    throw QgarErrorDeveloper(__FILE__, __LINE__,
                             "void qgar::DxfFile::write(const qgar::ConnectedComponents::node_type* const, int, qgar::QGEcolor, qgar::QGEoutline)",
                             "Connected components are not supported by current VEC format!");
}


// ---------------------------------------------------------------------


} // namespace qgar
