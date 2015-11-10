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
 * @file AbstractGraphicsFile.cpp
 *
 * @brief Implementation of functions of class qgar::AbstractGraphicsFile.
 *
 * See file AbstractGraphicsFile.h for the interface.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   Jul 5, 2005  14:32
 * @since  qgar 2.2
 */



// QGAR
#include "AbstractFile.h"
#include "AbstractGraphicsFile.h"
#include "primitives.h"



namespace qgar
{


// -------------------------------------------------------------------
// C O N S T R U C T O R 
// -------------------------------------------------------------------


// INITIALIZE WITH GIVEN NAME

AbstractGraphicsFile::AbstractGraphicsFile(const char* aFileName)

  : AbstractFile(aFileName)

{
  // VOID
}


// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------


AbstractGraphicsFile::~AbstractGraphicsFile()
{
  // VOID
}


// -------------------------------------------------------------------
// O U T P U T   Q G A R   S E G M E N T S
// -------------------------------------------------------------------


// OUTPUT A QGAR SEGMENT WITH COORDINATES OF TYPE 'int'

void
AbstractGraphicsFile::write(const GenQgarSegment<int>& aQSeg,
			    int        aThickness,
			    QGEcolor   aColor,
			    QGEoutline anOutline)
{
  const GenSegment<int>& seg = aQSeg.accessGeomStructure();

  write(seg.xSource(),
	seg.ySource(),
	seg.xTarget(),
	seg.yTarget(),
	(aThickness < 0)                ? aQSeg.thickness() : aThickness,
	(aColor == QGE_COLOR_NONE)      ? aQSeg.color()     : aColor,
	(anOutline == QGE_OUTLINE_NONE) ? aQSeg.outline()   : anOutline);
}


// OUTPUT A QGAR SEGMENT WITH COORDINATES OF TYPE 'float'

void
AbstractGraphicsFile::write(const GenQgarSegment<float>& aQSeg,
			    int        aThickness,
			    QGEcolor   aColor,
			    QGEoutline anOutline)
{
  const GenSegment<float>& seg = aQSeg.accessGeomStructure();

  write(seg.xSource(),
	seg.ySource(),
	seg.xTarget(),
	seg.yTarget(),
	(aThickness < 0)                ? aQSeg.thickness() : aThickness,
	(aColor == QGE_COLOR_NONE)      ? aQSeg.color()     : aColor,
	(anOutline == QGE_OUTLINE_NONE) ? aQSeg.outline()   : anOutline);
}



// OUTPUT A QGAR SEGMENT WITH COORDINATES OF TYPE 'double'

void
AbstractGraphicsFile::write(const GenQgarSegment<double>& aQSeg,
			    int        aThickness,
			    QGEcolor   aColor,
			    QGEoutline anOutline)
{
  const GenSegment<double>& seg = aQSeg.accessGeomStructure();

  write(seg.xSource(),
	seg.ySource(),
	seg.xTarget(),
	seg.yTarget(),
	(aThickness < 0)                ? aQSeg.thickness() : aThickness,
	(aColor == QGE_COLOR_NONE)      ? aQSeg.color()     : aColor,
	(anOutline == QGE_OUTLINE_NONE) ? aQSeg.outline()   : anOutline);
}


// -------------------------------------------------------------------
// O U T P U T   Q G A R   A R C S   O F   C I R C L E
// -------------------------------------------------------------------


// OUTPUT A QGAR ARC WITH COORDINATES OF TYPE 'int'

void
AbstractGraphicsFile::write(const GenQgarArc<int>& aQArc,
			    int        aThickness,
			    QGEcolor   aColor,
			    QGEoutline anOutline)
{
  const GenArc<int>& arc = aQArc.accessGeomStructure();

  write(arc.xSource(),
	arc.ySource(),
	arc.xTarget(),
	arc.yTarget(),
	arc.xCenter(),
	arc.yCenter(),
	(aThickness < 0)                ? aQArc.thickness() : aThickness,
	(aColor == QGE_COLOR_NONE)      ? aQArc.color()     : aColor,
	(anOutline == QGE_OUTLINE_NONE) ? aQArc.outline()   : anOutline);
}


// OUTPUT A QGAR ARC WITH COORDINATES OF TYPE 'float'

void
AbstractGraphicsFile::write(const GenQgarArc<float>& aQArc,
			    int        aThickness,
			    QGEcolor   aColor,
			    QGEoutline anOutline)
{
  const GenArc<float>& arc = aQArc.accessGeomStructure();

  write(arc.xSource(),
	arc.ySource(),
	arc.xTarget(),
	arc.yTarget(),
	arc.xCenter(),
	arc.yCenter(),
	(aThickness < 0)                ? aQArc.thickness() : aThickness,
	(aColor == QGE_COLOR_NONE)      ? aQArc.color()     : aColor,
	(anOutline == QGE_OUTLINE_NONE) ? aQArc.outline()   : anOutline);
}


// OUTPUT A QGAR ARC WITH COORDINATES OF TYPE 'double'

void
AbstractGraphicsFile::write(const GenQgarArc<double>& aQArc,
			    int        aThickness,
			    QGEcolor   aColor,
			    QGEoutline anOutline)
{
  const GenArc<double>& arc = aQArc.accessGeomStructure();

  write(arc.xSource(),
	arc.ySource(),
	arc.xTarget(),
	arc.yTarget(),
	arc.xCenter(),
	arc.yCenter(),
	(aThickness < 0)                ? aQArc.thickness() : aThickness,
	(aColor == QGE_COLOR_NONE)      ? aQArc.color()     : aColor,
	(anOutline == QGE_OUTLINE_NONE) ? aQArc.outline()   : anOutline);
}


// -------------------------------------------------------------------
// O U T P U T   Q G A R   P O L Y L I N E S 
// -------------------------------------------------------------------


// OUTPUT A QGAR POLYLINE WITH COORDINATES OF TYPE 'int'

void
AbstractGraphicsFile::write(const GenQgarPolyline<int>& aQPoly,
			    int        aThickness,
			    QGEcolor   aColor,
			    QGEoutline anOutline)
{
  write(aQPoly.accessGeomStructure(),
	(aThickness < 0)                ? aQPoly.thickness() : aThickness,
	(aColor == QGE_COLOR_NONE)      ? aQPoly.color()     : aColor,
	(anOutline == QGE_OUTLINE_NONE) ? aQPoly.outline()   : anOutline);
}

 

// OUTPUT A QGAR POLYLINE WITH COORDINATES OF TYPE 'float'

void
AbstractGraphicsFile::write(const GenQgarPolyline<float>& aQPoly,
			    int        aThickness,
			    QGEcolor   aColor,
			    QGEoutline anOutline)
{
  write(aQPoly.accessGeomStructure(),
	(aThickness < 0)                ? aQPoly.thickness() : aThickness,
	(aColor == QGE_COLOR_NONE)      ? aQPoly.color()     : aColor,
	(anOutline == QGE_OUTLINE_NONE) ? aQPoly.outline()   : anOutline);
}

 
// OUTPUT A QGAR POLYLINE WITH COORDINATES OF TYPE 'double'

void
AbstractGraphicsFile::write(const GenQgarPolyline<double>& aQPoly,
			    int        aThickness,
			    QGEcolor   aColor,
			    QGEoutline anOutline)
{
  write(aQPoly.accessGeomStructure(),
	(aThickness < 0)                ? aQPoly.thickness() : aThickness,
	(aColor == QGE_COLOR_NONE)      ? aQPoly.color()     : aColor,
	(anOutline == QGE_OUTLINE_NONE) ? aQPoly.outline()   : anOutline);
}


// -------------------------------------------------------------------


} // namespace qgar
