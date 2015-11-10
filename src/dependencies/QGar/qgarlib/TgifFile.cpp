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
 * @file   TgifFile.cpp
 * @brief  Implementation of class qgar::TgifFile.
 *
 *         See file TgifFile.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gerald Masini">Gérald Masini</a>
 * @date   Jul, 3  2001  18:21
 * @since  Qgar 1.0
 */



// STD
#include <cmath>
// QGAR
#include "AbstractGenPointChain.h"
#include "BoundingBox.h"
#include "Component.h"
#include "ConnectedComponents.h"
#include "GenTree.h"
#include "primitives.h"
#include "QgarErrorDeveloper.h"
#include "TgifFile.h"




using namespace std;



namespace qgar
{


// LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
//
// L O C A L   A U X I L I A R I E S
//
// LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL

namespace
{


// WIDTH OF A TGIF ARROW HEAD
// aThickness  thickness of the drawing (default 1)

int TGIFFILE_arrowHeadWidth(int aThickness = 1)
{
  // width = line-thickness + 2
  return aThickness + 2;
}


// HEIGHT OF A TGIF ARROW HEAD
// aThickness  thickness of the drawing (default 1)

int TGIFFILE_arrowHeadHeight(int aThickness = 1)
{
  // height = 6 + 2 * (line-thickness + (line-thickness / 5))
  return 6 + 2 * (aThickness + (aThickness / 5));
}


} // unnamed namespace

// LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL




// -------------------------------------------------------------------
// T G I F   S P E C I F I C   I N F O R M A T I O N   ( S T A T I C ) 
// -------------------------------------------------------------------

// TGIF  VERSION 3.0, PATCHLEVEL 17
// ********************************
// ALL INFORMATION IS INTEGER
// TGIF UNITS
//   length: 1/5 mm (1cm = 50 units)
//   angle : 1/64 degree

// Number of pixels per inch
const int   TgifFile::s_tgif_pix_per_inch_   = 128;
// A4 page width
const float TgifFile::s_tgif_a4_page_width_  = 8.25f * s_tgif_pix_per_inch_;
// A4 page height
const float TgifFile::s_tgif_a4_page_height_ = 11.7f * s_tgif_pix_per_inch_;

// Current Tgif version
const char* TgifFile::s_tgif_version_ = "3.0-p17";

// Table of Tgif colors (see enum type qgar::QGEcolor)
const char* TgifFile::s_tgif_colors_[21] =
{
  "#000000",   // QGE_COLOR_DEFAULT (black)
  "#000000",   // QGE_COLOR_BLACK
  "#707070",   // QGE_COLOR_DARK_GRAY
  "#a0a0a0",   // QGE_COLOR_GRAY
  "#d0d0d0",   // QGE_COLOR_LIGHT_GRAY
  "#ffffff",   // QGE_COLOR_WHITE
  "#ff00ff",   // QGE_COLOR_MAGENTA
  "#cc00cc",   // QGE_COLOR_PURPLE
  "#00ffff",   // QGE_COLOR_CYAN
  "#00aaee",   // QGE_COLOR_MEDIUM_BLUE
  "#0000ff",   // QGE_COLOR_BLUE
  "#888800",   // QGE_COLOR_OLIVE_GREEN
  "#008800",   // QGE_COLOR_DARK_GREEN
  "#00ff00",   // QGE_COLOR_GREEN
  "#ffff00",   // QGE_COLOR_YELLOW
  "#ff8000",   // QGE_COLOR_ORANGE    
  "#ff0000",   // QGE_COLOR_RED
  "#ff4080",   // QGE_COLOR_PINK
  "#ff8080",   // QGE_COLOR_SALMON_PINK
  "#bb7020",   // QGE_COLOR_BROWN
  "#a02000"    // QGE_COLOR_CHOCOLATE_BROWN
};

// Table of Tgif outline types (see enum type qgar::QGEoutline)
const unsigned char TgifFile::s_tgif_outlines_[10] =
{
  0,  // QGE_OUTLINE_DEFAULT (solid)
  0,  // QGE_OUTLINE_SOLID
  1,  // QGE_OUTLINE_DASH_SSPACED
  2,  // QGE_OUTLINE_DASH_SPACED
  3,  // QGE_OUTLINE_DASH_REGULAR
  4,  // QGE_OUTLINE_DASH_LS
  5,  // QGE_OUTLINE_DASH_SS
  6,  // QGE_OUTLINE_DASH_LSS
  7,  // QGE_OUTLINE_DASH_LSPACED
  8   // QGE_OUTLINE_DOT
};


// -------------------------------------------------------------------
// C O N S T R U C T O R S
// -------------------------------------------------------------------


// INITIALIZE WITH GIVEN NAME

TgifFile::TgifFile(char* aFileName)

    : AbstractGraphicsFile(aFileName),
      tgifObjectCnt_(0)

{
  // VOID
}


// -------------------------------------------------------------------
// D E S T R U C T O R
// -------------------------------------------------------------------


TgifFile::~TgifFile()
{
  // VOID
}


// --------------------------------------------------------------------
// O U T P U T   P O I N T S
// --------------------------------------------------------------------


// INTEGER POINTS
void
TgifFile::write(const GenPoint<int>& aPt,
		int aThickness,
		QGEcolor aColor)
{
  isOpenW();
  savePoint(aPt.x(), aPt.y(), aThickness, aColor);
}


// FLOAT POINTS

void
TgifFile::write(const GenPoint<float>& aPt,
		int aThickness,
		QGEcolor aColor)
{
  isOpenW();
  savePoint((int) aPt.x(), (int) aPt.y(), aThickness, aColor);
}


// DOUBLE POINTS

void
TgifFile::write(const GenPoint<double>& aPt,
		int aThickness,
		QGEcolor aColor)
{
  isOpenW();
  savePoint((int) aPt.x(), (int) aPt.y(), aThickness, aColor);
}


// --------------------------------------------------------------------
// O U T P U T   C H A I N S   O F   P O I N T S
// --------------------------------------------------------------------


// CHAINS OF INTEGER POINTS

void
TgifFile::write(AbstractGenPointChain<int>& aChain,
		int aThickness,
		QGEcolor aColor)
{
  isOpenW();
  saveChain(aChain, aThickness, aColor);
}


// CHAINS OF FLOAT POINTS

void
TgifFile::write(AbstractGenPointChain<float>& aChain,
		int aThickness,
		QGEcolor aColor)
{
  isOpenW();
  saveChain(aChain, aThickness, aColor);
}


// CHAINS OF DOUBLE POINTS

void
TgifFile::write(AbstractGenPointChain<double>& aChain,
		int aThickness,
		QGEcolor aColor)
{
  isOpenW();
  saveChain(aChain, aThickness, aColor);
}


// --------------------------------------------------------------------
// O U T P U T   L I N E   S E G M E N T S
// --------------------------------------------------------------------


// INTEGER SEGMENTS

void
TgifFile::write(int aXSource,
		int aYSource,
		int aXTarget,
		int aYTarget,
		int        aThickness,
		QGEcolor   aColor,
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


// FLOAT SEGMENTS

void
TgifFile::write(float aXSource,
		float aYSource,
		float aXTarget,
		float aYTarget,
		int        aThickness,
		QGEcolor   aColor,
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


// DOUBLE SEGMENTS

void
TgifFile::write(double aXSource,
		double aYSource,
		double aXTarget,
		double aYTarget,
		int        aThickness,
		QGEcolor   aColor,
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


// --------------------------------------------------------------------
// O U T P U T   C I R C L E S
// --------------------------------------------------------------------


// CIRCLES WITH INTEGER COORDINATES

void
TgifFile::write(int aXCenter,
		int aYCenter,
		double aRadius,
		int aThickness,
		QGEcolor aColor,
		QGEoutline anOutline)
{
  isOpenW();

  saveCircle(aXCenter,
	     aYCenter,
	     (int) aRadius,
	     aThickness,
	     aColor,
	     anOutline);
}


// CIRCLES WITH FLOAT COORDINATES

void
TgifFile::write(float aXCenter,
		float aYCenter,
		double aRadius,
		int aThickness,
		QGEcolor aColor,
		QGEoutline anOutline)
{
  isOpenW();

  saveCircle((int) aXCenter,
	     (int) aYCenter,
	     (int) aRadius,
	     aThickness,
	     aColor,
	     anOutline);
}


// CIRCLES WITH DOUBLE COORDINATES

void
TgifFile::write(double aXCenter,
		double aYCenter,
		double aRadius,
		int aThickness,
		QGEcolor aColor,
		QGEoutline anOutline)
{
  isOpenW();

  saveCircle((int) aXCenter,
	     (int) aYCenter,
	     (int) aRadius,
	     aThickness,
	     aColor,
	     anOutline);
}


// --------------------------------------------------------------------
// O U T P U T   A R C S   O F   C I R C L E
// --------------------------------------------------------------------


// ARCS WITH INTEGER COORDINATES

void
TgifFile::write(int aXSource,
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


// ARCS WITH FLOAT COORDINATES

void
TgifFile::write(float aXSource,
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

// ARCS WITH DOUBLE COORDINATES

void
TgifFile::write(double aXSource,
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


// --------------------------------------------------------------------
// O U T P U T   P O L Y L I N E S
// --------------------------------------------------------------------


// POLYLINES WITH INTEGER COORDINATES

void
TgifFile::write(const GenPolyline<int>& aPoly,
		int aThickness,
		QGEcolor aColor,
		QGEoutline anOutline)
{
  isOpenW();
  savePolyline(aPoly, aThickness, aColor, anOutline);
}


// POLYLINES WITH FLOAT COORDINATES

void
TgifFile::write(const GenPolyline<float>& aPoly,
		int aThickness,
		QGEcolor aColor,
		QGEoutline anOutline)
{
  isOpenW();
  savePolyline(aPoly, aThickness, aColor, anOutline);
}


// POLYLINES WITH DOUBLE COORDINATES

void
TgifFile::write(const GenPolyline<double>& aPoly,
		int aThickness,
		QGEcolor aColor,
		QGEoutline anOutline)
{
  isOpenW();
  savePolyline(aPoly, aThickness, aColor, anOutline);
}


// -------------------------------------------------------------------
// O U T P U T   B O U N D I N G   B O X E S
// -------------------------------------------------------------------


// BOUNDING BOXES WITH INTEGER COORDINATES

void
TgifFile::write(const BoundingBox& aBox,
		int aThickness,
		QGEcolor aColor,
		QGEoutline anOutline)
{
  isOpenW();

  saveBox(aBox.xTopLeft(),
	  aBox.yTopLeft(),
	  aBox.xBottomRight(),
	  aBox.yBottomRight(),
	  aThickness,
	  aColor,
	  anOutline);
}


// -------------------------------------------------------------------
// O U T P U T   C O M P O N E N T S
// -------------------------------------------------------------------


// CONTOUR OF COMPONENT AND OF ALL INCLUDED COMPONENTS

void
TgifFile::write(const ConnectedComponents::node_type* const aPNode,
		int aThickness,
		QGEcolor aColor,
		QGEoutline anOutline)
{
  isOpenW();

  // Pointer to the component (included in the node)
  Component* const pComp = aPNode->accessData();

  // Write contour
  if (pComp->areaPx() == 1)
    {
      // The component includes a single pixel
      write((pComp->accessContour()).front(),
	    (pComp->color() == QGE_BW_WHITE) ? QGE_COLOR_RED : QGE_COLOR_BLUE);
    }
  else
    {
      // The component includes at least two pixels
      write(IPolyline(pComp->accessContour()),
	    aThickness,
	    (pComp->color() == QGE_BW_WHITE) ? QGE_COLOR_RED : QGE_COLOR_BLUE,
	    anOutline);
    }

  // Write bounding box
  write(pComp->accessBoundingBox(), 1, QGE_COLOR_BLACK, QGE_OUTLINE_SOLID);

  // Write children and siblings
  PRIVATEwriteComponent(aPNode->pFirstChild(), aThickness, aColor, anOutline);
}


// -------------------------------------------------------------------
// O U T P U T
// -------------------------------------------------------------------


// WRITE FILE HEADER

void
TgifFile::writeHeader()
{
// Current Tgif version
  fstream_ << "%TGIF " << s_tgif_version_ << endl;

// For the moment, write header as it is found in a simple Tgif file.
// We'll take care of the details when we get time!

// [1]  PAGE STYLE
// [2]  FILE VERSION
// [3]  CURRENT COLOR REDUCTION(100) ['SetReduction' in 'Layout' menu]
// [4][5] COORDINATES OF THE CURRENT POINT (?)
// [6]  CURRENT ZOOM MAGNITUDE(0) ['ZoomIn' and 'ZoomOut' in the 'Layout' menu]
// [7]  ENGLISH GRID SIZE(16): ?
// [8]  GRID(0): ?
// [9]  CURRENT COLOR(0): index in the table of the 'Color' menu
// [10][11] CURRENT HORIZONTAL(1) and VERTICAL(1) ALIGNMENTS ['View' menu]
// [12] CURRENT LINE WIDTH(1)
// [13] SPLINE(0): ?
// [14] CURRENT LINE STYLE(0)
// [15] CURRENT OBJECT FILL(0)
// [16] CURRENT PEN PATTERN(1)
// [17] CURRENT TEXT JUSTIFICATION(1) ['TextStyle' in 'Text' menu]
// [18] CURRENT FONT NAME(Helvetica)
// [19] CURRENT TEXT STYLE(0) ['Textmenu']
// [20] POINT SIZE(12)
// [21] 0: ?
// [22] CURRENT LINE DASH(0)
// [23] CURRENT GRID SYSTEM(1) ['ShowGrid/HideGrid' in 'Layout' menu]
// [24] CURRENT METRIC GRID SIZE(5): 1(maximum grid) to 5(minimum grid)
// [25] CURRENT TEXT SPACING(0)
// [26] ZOOM IN(0): ?
// [27] GRID SHOWN(1=ShowGrid) ['Layout' menu]
// [28] MOVE MODE(1)
// [29] TEXT ROTATE(0): ?
// [30] CURRENT ROUND CORNER BOX RADIUS(16)
// [31] USE GRAY SCALE(1=UseGrayScale) ['Layout' menu]
// [32] CURRENT PAGE LAYOUT MODE(0)
// [33] CURRENT PAGE ARG1(1)
// [34] CURRENT PAGE ARG2(1)
// [35] PAGE LINE SHOWN IN TILE MODE(1)
// [36] COLOR DUMP(0)
   fstream_ << "state(0,33,100.000,0,0,0,16,0,0,1,1,0,0,0,0,1,1,"
	    << "'Helvetica',0,12,0,0,1,5,0,0,1,1,0,16,1,0,1,1,1,0,"
// [37][38] CURRENT PAGE WIDTH AND HEIGHT
	    << floor(s_tgif_a4_page_width_)
	    << ','
	    << floor(s_tgif_a4_page_height_)
	    << ','
// [39] STRETCHABLE TEXT(0=no)
// [40] CURRENT TEXT ROTATION(0 degree)
// [41] CURRENT ROTATION INCREMENT(2880 i.e. 45 degrees)
	    << "0,0,2880).\n";

// WARNING: Imperatively use two strings!
// Otherwise, '$' followed by 'Header' is mistaken for a command by CVS.
   fstream_ << "%\n% @(#)$"
	    << "Header$\n% %W%\n%\n";

// UNIT (?)
   fstream_ << "unit(\"1 pixel/pixel\").\n";
// TABLE OF AVAILABLE COLORS
   fstream_ << "color_info(21,65535,0,[\n"
	    << "\t\"#000000\", 0, 0, 0, 0, 0, 0, 1,\n"
	    << "\t\"#707070\", 28784, 28784, 28784, 28672, 28672, 28672, 1,\n"
	    << "\t\"#a0a0a0\", 41120, 41120, 41120, 40960, 40960, 40960, 1,\n"
	    << "\t\"#d0d0d0\", 53456, 53456, 53456, 53248, 53248, 53248, 1,\n"
	    << "\t\"#ffffff\", 65535, 65535, 65535, 65280, 65280, 65280, 1,\n"
	    << "\t\"#ff00ff\", 65535, 0, 65535, 65280, 0, 65280, 1,\n"
	    << "\t\"#cc00cc\", 52428, 0, 52428, 52224, 0, 52224, 1,\n"
	    << "\t\"#00ffff\", 0, 65535, 65535, 0, 65280, 65280, 1,\n"
	    << "\t\"#00aaee\", 0, 43690, 61166, 0, 43520, 60928, 1,\n"
	    << "\t\"#0000ff\", 0, 0, 65535, 0, 0, 65280, 1,\n"
	    << "\t\"#888800\", 34952, 34952, 0, 34816, 34816, 0, 1,\n"
	    << "\t\"#008800\", 0, 34952, 0, 0, 34816, 0, 1,\n"
	    << "\t\"#00ff00\", 0, 65535, 0, 0, 65280, 0, 1,\n"
	    << "\t\"#ffff00\", 65535, 65535, 0, 65280, 65280, 0, 1,\n"
	    << "\t\"#ff8000\", 65535, 32896, 0, 65280, 32768, 0, 1,\n"
	    << "\t\"#ff0000\", 65535, 0, 0, 65280, 0, 0, 1,\n"
	    << "\t\"#ff4080\", 65535, 16448, 32896, 65280, 16384, 32768, 1,\n"
	    << "\t\"#ff8080\", 65535, 32896, 32896, 65280, 32768, 32768, 1,\n"
	    << "\t\"#bb7020\", 48059, 28784, 8224, 47872, 28672, 8192, 1,\n"
	    << "\t\"#a02000\", 41120, 8224, 0, 40960, 8192, 0, 1\n"
	    << "]).\n";
// CURRENT PAGE
   fstream_ << "page(1,\"\",1).\n";
}


// WRITE FILE FOOTER

void
TgifFile::writeFooter()
{
  // VOID
}


// -------------------------------------------------------------------
// SAVE PREDICATES DESCRIBING TGIF OBJECTS
// -------------------------------------------------------------------


// BEGIN POLYLINE: TO BE SEPARATELY PERFORMED
// ================================================
// aVerticesCnt  number of vertices of the polyline
// aColor       color of the drawing
// ================================================
void
TgifFile::savePolylineBegin(int aVerticesCnt, QGEcolor aColor)
{
// [1] COLOR(black)
   fstream_ << "poly('"
	    << s_tgif_colors_[aColor]
	    << "',"
	    << aVerticesCnt
	    << ",[\n\t";
}

// MIDDLE: TO BE SEPARATELY CONSTRUCTED
// ================================================
// [2] NUMBER OF VERTICES
// [3] COORDINATES OF VERTICES
//     format: "[\n" x1,y1,x2,y2, ... xN,yN "]"
// ================================================

// END POLYLINE: TO BE SEPARATELY PERFORMED
// ================================================
// aVerticesCnt  number of vertices of the polyline
// aThickness    thickness of the drawing
// anOutline     outline of the drawing
// ================================================
void
TgifFile::savePolylineEnd(int aVerticesCnt,
			  int aThickness,
			  QGEoutline anOutline)
{
  int ahh = TGIFFILE_arrowHeadHeight(aThickness);
  int ahw = TGIFFILE_arrowHeadWidth(aThickness);

   fstream_ << "],"
// [4] LINE STYLE(0) ['Line Style' in 'Properties' menu]
//     0=QGE_PBM_PLAIN  1=ARROW AT EXTREMUM  2=ARROW AT ORIGIN  3=DOUBLE ARROW
	    << "0,"
// [5] LINE WIDTH(1) ['Line Width' in 'Properties' menu]
//     1=THINEST to 7=THICKEST
	    << aThickness
	    << ','
// [6] PEN PATTERN(0) ['Pen' in 'Properties' menu]
//     0=NONE   1=QGE_COLOR_BLACK   2=QGE_COLOR_WHITE ... 31
	    << "1,"
// [7] OBJECT IDENTIFICATION NUMBER
	    << tgifObjectCnt_++
	    << ','
// [8] SPLINE(0): interpolated spline object?
	    << "0,"
// [9] OBJECT FILL PATTERN(0) ['Fill' in 'Properties' menu]
//     same as pen pattern
	    << "1,"
// [10] DASH(0) ['Line Dash' in 'Properties' menu]
	    << s_tgif_outlines_[(int) anOutline]
	    << ','
// [11] ROTATION(0): ?
	    << "0,"
// [12][13] HEIGHT AND WIDTH OF THE ARROWHEAD
	    << ahh
	    << ','
	    << ahw
	    << ','
// [14] LOCKED(0): ?
// [15] TRANSFORMED(0) [see 'Main' and 'Mode' menus]
//      0=the initial object has not been rotated
//      1=the initial object has been rotated
// [16] INVISIBLE(0): ?
	    << "0,0,0,"
// SPECIFICATIONS of
// [17] LINE WIDTH       : value between quotes
// [18] ARROW HEAD WIDTH : value between quotes
// [19] ARROW HEAD HEIGHT: value between quotes
	    << "'"
	    << aThickness
	    << "','"
	    << ahh
	    << "','"
	    << ahw
	    << "',\n    \"";
// [20] SMOOTH [see 'Edit' menu]: value between double quotes
   int nibble_count = 0;
   int bit_count    = 0;
   for (int idx = 0; idx < aVerticesCnt; idx++)
     {
       if (++bit_count == 4)
	 {
	   if (nibble_count++ == 64)
	     {
	       nibble_count = 1;
	       fstream_ << "\n     ";
	     }
	   fstream_ << "0";
	   bit_count = 0;
	 }
       if ((aVerticesCnt & 0x3) != 0)
	 {
	   if (nibble_count++ == 64)
	     {
	       nibble_count = 1;
	       fstream_ << "\n     ";
	     }
	   fstream_ << "0";
	 }
     } // END for idx
   fstream_ << "\","
// [21] ATTRIBUTES LIST
// format: "[\n" values... "]"
// **** End of the Prolog predicate describing the segment: ")."
	    << "[\n])."
	    << endl;
}



// ======================================
// A POINT (INTEGER COORDINATES)
// ======================================
// aX          X coordinate of the point
// aY          Y coordinate of the point
// aColor     color of the drawing
// aThickness  thickness of the drawing
// ======================================
void
TgifFile::savePoint(int aX,
		    int aY,
		    int aThickness,
		    QGEcolor aColor)
{
  savePolylineBegin(1, aColor);

  fstream_ << aX
	   << ','
	   << aY;

  savePolylineEnd(1, aThickness, QGE_OUTLINE_SOLID);
}



// ========================================
// A SEGMENT (INTEGER COORDINATES)
// ========================================
// aXSource   X coordinate of the source point
// aYSource   Y coordinate of the source point
// aXTarget   X coordinate of the target point
// aYTarget   Y coordinate of the target point
// aColor    color of the drawing
// aThickness thickness of the drawing
// anOutline  outline of the drawing
// ========================================
void
TgifFile::saveSegment(int aXSource,
		      int aYSource,
		      int aXTarget,
		      int aYTarget,
		      int aThickness,
		      QGEcolor aColor,
		      QGEoutline anOutline)
{
  savePolylineBegin(2, aColor);
    
  fstream_ << aXSource
	   << ','
	   << aYSource
	   << ','
	   << aXTarget
	   << ','
	   << aYTarget;

  savePolylineEnd(2, aThickness, anOutline);
}



// ===========================================
// A CIRCLE (INTEGER COORDINATES)
// ===========================================
// aXCenter    X coordinate of the center
// aYCenter    Y coordinate of the center
// aRadius     radius
// aColor     color of the drawing
// aThickness  thickness of the drawing
// anOutline   outline of the drawing
// ===========================================
void
TgifFile::saveCircle(int aXCenter,
		     int aYCenter,
		     int aRadius,
		     int aThickness,
		     QGEcolor aColor,
		     QGEoutline anOutline)
{
  fstream_ << "oval('"
// [1] COLOR(black) ['Color' menu]
	   << s_tgif_colors_[aColor]
// [2] ?
	   << "','',"
// [3][4] COORDINATES OF THE UPPER QGE_POSITION_LEFT CORNER OF THE BOUNDING BOX
	   << (aXCenter - aRadius)
	   << ','
	   << (aYCenter - aRadius)
	   << ','
// [5][6] COORDINATES OF THE LOWER QGE_POSITION_RIGHT CORNER  OF THE BOUNDING BOX
	   << (aXCenter + aRadius)
	   << ','
	   << (aYCenter + aRadius)
// [7] OBJECT FILL PATTERN(0) ['Fill' in 'Properties' menu]
	   << ",0,"
// [8] LINE WIDTH(1) ['Line Width' in 'Properties' menu]
	   << aThickness
// [9] PEN PATTERN(0) ['Pen' in 'Properties' menu]
	   << ",1,"
// [10] OBJECT IDENTIFICATION NUMBER(1)
	   << tgifObjectCnt_++
	   << ','
// [11] LINE DASH(0) ['Line Dash' in 'Properties' menu]
	   << s_tgif_outlines_[anOutline]
// [12] ROTATION(0)
// [13] LOCKED(0)
// [14] TRANSFORMED(0) [see 'Main' and 'Mode' menus]
// [15] INVISIBLE(0)
	   << ",0,0,0,0,'"
// [16] SPECIFICATION of LINE WIDTH: value between quotes
	   << aThickness
// [17] ?
	   << "',0," 
// [18] ATTRIBUTES LIST
// format: "[\n" values... "]"
// **** End of the Prolog predicate describing the segment: ")."
	   << "[\n])."
	   << endl;
} // END saveCircle



// =========================================
// AN ARC OF CIRCLE (INTEGER COORDINATES)
// =========================================
// aXSource     X coordinate of source point
// aYSource     Y coordinate of source point
// aXTarget     X coordinate of target point
// aYTarget     Y coordinate of target point
// aXCenter     X coordinate of the center
// aYCenter     Y coordinate of the center
// aColor       color of the drawing
// aThickness   thickness of the drawing
// anOutline    outline of the drawing
// =========================================
void
TgifFile::saveArc(int aXSource,
		  int aYSource,
		  int aXTarget,
		  int aYTarget,
		  int aXCenter,
		  int aYCenter,
		  int aThickness,
		  QGEcolor aColor,
		  QGEoutline anOutline)
{
// Height and width of an arrow head
  int ahh = TGIFFILE_arrowHeadHeight(aThickness);
  int ahw = TGIFFILE_arrowHeadWidth(aThickness);

// *********************************************************
// From Tgif source file arc.c:
//
// 0 degree is horizontal in the direction of the X axis.
// Positive angles measures counter-clockwise from 0 degree.
// Negative angles measures clockwise from 0 degree.
//
// #define ARC_CCW 0   // counter-clockwise
// #define ARC_CW  1   // clockwise
// *********************************************************

// A Qgar arc is always Tgif-clockwise
   int direction = 1;

// Radius
   int radius = (int) qgDist(aXSource, aYSource, aXCenter, aYCenter);

// Start angle: Angle at starting point.
// WARNING: It must be between -180 degrees and +180 degrees.
   Point c(aXCenter,aYCenter);
   int sourceAngle = (int) qgAngleDegrees(c, Point(aXSource,aYSource));
   int startAngle = (sourceAngle >= 180)
                    ? (360 - sourceAngle)
                    : -sourceAngle;

// Delta angle: Amount between start angle and extremum angle.
// It must be negative because arc direction is always Tgif-clockwise.
   int deltaAngle
     = ((int) qgAngleDegrees(c, Point(aXTarget,aYTarget))) - sourceAngle;
   deltaAngle = (deltaAngle < 0)
                ? (-360 - deltaAngle)
                : -deltaAngle;

// Save predicate.
   fstream_ << "arc('"
// [1] COLOR(black)
	    << s_tgif_colors_[aColor]
	    << "',"
// [2] OBJECT FILL PATTERN(0) ['Fill' in 'Properties' menu]
//     0=NONE   1=QGE_COLOR_BLACK   2=QGE_COLOR_WHITE ... 31
	    << "0,"
// [3] LINE WIDTH(1) ['Line Width' in 'Properties' menu]
//     1=THINEST to 7=THICKEST
	    << aThickness
	    << ','
// [4] PEN PATTERN(0) ['Pen' in 'Properties' menu]
//     0=NONE   1=QGE_COLOR_BLACK   2=QGE_COLOR_WHITE ... 31
	    << "1,"
// [5] DASH(0) ['Line Dash' in 'Properties' menu]
	    << s_tgif_outlines_[anOutline]
	    << ','
// [6][7] COORDINATES OF THE UPPER LEFT CORNER OF THE FULL CIRCLE (?)
	    << (aXCenter - radius)
	    << ','
	    << (aYCenter - radius)
	    << ','
// [8][9]   CENTER COORDINATES
// [10][11] ORIGIN POINT COORDINATES
// [12][13] EXTREMUM POINT COORDINATES
	    << aXCenter
	    << ','
	    << aYCenter
	    << ','
	    << aXSource
	    << ','
	    << aYSource
	    << ','
	    << aXTarget
	    << ','
	    << aYTarget
	    << ','
// [14] DIRECTION
//      0=counter-clockwise   1=clockwise
	    << direction
	    << ','
// [15][16] WIDTH AND HEIGHT OF THE FULL CIRCLE (?)
	    << (radius * 2)
	    << ','
	    << (radius * 2)
	    << ','
// [17] START ANGLE
// [18] DELTA ANGLE: amount between start angle and extremum angle
// Tgif angle unit = 1/64 degree
	    << (startAngle * 64)
	    << ','
	    << (deltaAngle * 64)
	    << ','
// [19] OBJECT IDENTIFICATION NUMBER(1)
	    << tgifObjectCnt_++
	    << ','
// [20] ROTATION(0): ?
	    << "0,"
// [21] LINE STYLE(0) ['Line Style' in 'Properties' menu]
//      0=QGE_PBM_PLAIN  2=ARROW AT ORIGIN  1=ARROW AT EXTREMUM  3=DOUBLE ARROW
	    << "0,"
// [22][23] HEIGHT and WIDTH OF THE ARROWHEAD
	    << ahh
	    << ','
	    << ahw
	    << ','
// [24] LOCKED(0): ?
// [25] TRANSFORMED(0) [see 'Main' and 'Mode' menus]
//      0=the initial object has not been rotated
//      1=the initial object has been rotated
// [26] INVISIBLE(0): ?
	    << "0,0,0,"
// SPECIFICATIONS of
// [27]   LINE WIDTH       : value between quotes
// [28]   ARROW HEAD WIDTH : value between quotes
// [29]   ARROW HEAD HEIGHT: value between quotes
	    << "'"
	    << aThickness
	    << "','"
	    << ahh
	    << "','"
	    << ahw
	    << "',"
// [30] ATTRIBUTES LIST
// format: "[\n" values... "]"
// **** End of the Prolog predicate describing the segment: ")."
	    << "[\n])."
	    << endl;
} // END saveArc



// =================================================
// A BOX (INTEGER COORDINATES)
// =================================================
// aXTopLeft      X coordinate of top left point
// aYTopLeft      Y coordinate of top left point
// aXBottomRight  X coordinate of bottom right point
// aYBottomRight  Y coordinate of bottom right point
// aColor        color of the drawing
// aThickness     thickness of the drawing
// anOutline      outline of the drawing
// =================================================
void
TgifFile::saveBox(int aXTopLeft,
		  int aYTopLeft,
		  int aXBottomRight,
		  int aYBottomRight,
		  int aThickness,
		  QGEcolor aColor,
		  QGEoutline anOutline)
{
   fstream_ << "box('"
// [1] COLOR(black) ['Color' menu]
	    << s_tgif_colors_[aColor]
// [2] ?
	    << "','',"
// [3][4] COORDINATES OF THE UPPER QGE_POSITION_LEFT CORNER
	    << aXTopLeft
	    << ','
	    << aYTopLeft
	    << ','
// [5][6] COORDINATES OF THE LOWER QGE_POSITION_RIGHT CORNER
	    << aXBottomRight
	    << ','
	    << aYBottomRight
// [7] OBJECT FILL PATTERN(0) ['Fill' in 'Properties' menu]
	    << ",0,"
// [8] LINE WIDTH(1) ['Line Width' in 'Properties' menu]
	    << aThickness
// [9] PEN PATTERN(0) ['Pen' in 'Properties' menu]
	    << ",1,"
// [10] OBJECT IDENTIFICATION NUMBER(1)
	    << tgifObjectCnt_++
	    << ','
// [11] LINE DASH(0) ['Line Dash' in 'Properties' menu]
	    << s_tgif_outlines_[anOutline]
// [12] ROTATION(0): ?
// [13] LOCKED(0): ?
// [14] TRANSFORMED(0) [see Main and Mode menus]
// [15] INVISIBLE(0): ?
	    << ",0,0,0,0,'"
// [16] SPECIFICATION of LINE WIDTH: value between quotes
	    << aThickness
// [17] ?
	    <<"',0," 
// [18] ATTRIBUTES LIST
// format: "[\n" values... "]"
// **** End of the Prolog predicate describing the segment: ")."
	    << "[\n])."
	    << endl;
}


// -------------------------------------------------------------------
// F U N C T I O N S   N O T   Y E T   I M P L E M E N T E D
// -------------------------------------------------------------------


// READ HEADER

void
TgifFile::readHeader()



{
  throw QgarErrorDeveloper(__FILE__, __LINE__,
			   "void qgar::TgifFile::readHeader()",			   
			   "Not yet implemented: See GéGé le CHaNMé!");
}


// -------------------------------------------------------------------
// A U X I L I A R I E S   ( P R I V A T E )
// -------------------------------------------------------------------

// WRITE A NODE OF A COMPONENT TREE,
// AS WELL AS ITS SIBLINGS AND CHILDREN

void
TgifFile::PRIVATEwriteComponent(const ConnectedComponents::node_type* const aPNode,
				int aThickness,
				QGEcolor aColor,
				QGEoutline anOutline)
{
  if (aPNode != 0)
    {
      // Pointer to the component (included in the node)
      Component* const pComp = aPNode->accessData();

      // Write contour
      if (pComp->areaPx() == 1)
	{
	  // The component includes a single pixel
	  write((pComp->accessContour()).front(),
		(pComp->color() == QGE_BW_WHITE) ? QGE_COLOR_RED : QGE_COLOR_BLUE);
	}
      else
	{
	  // The component includes at least two pixels
	  write(IPolyline(pComp->accessContour()),
		aThickness,
		(pComp->color() == QGE_BW_WHITE) ? QGE_COLOR_RED : QGE_COLOR_BLUE,
		anOutline);
	}

      // Write bounding box
      write(pComp->accessBoundingBox(), 1, QGE_COLOR_BLACK, QGE_OUTLINE_SOLID);

      // Write children and siblings
      PRIVATEwriteComponent(aPNode->pFirstChild(), aThickness, aColor, anOutline);
      PRIVATEwriteComponent(aPNode->pRSibling(),   aThickness, aColor, anOutline);
    }
}

// ----------------------------------------------------------------------

} // namespace qgar
