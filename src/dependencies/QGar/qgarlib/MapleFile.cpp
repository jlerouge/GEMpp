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
 * @file   MapleFile.cpp
 * @brief  Implementation of class qgar::MapleFile.
 *
 *         See file MapleFile.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date   Jul 3, 2001  09:29
 * @since  qgar 1.0
 */



// QGAR
#include "GenImage.h"
#include "Histogram.h"
#include "MapleFile.h"



namespace qgar
{


// -------------------------------------------------------------------
// C O N S T R U C T O R S 
// -------------------------------------------------------------------


// =========================
// INITIALIZE FROM FILE NAME
// =========================


MapleFile::MapleFile(const char* aFileName)

  : AbstractFile(aFileName)

{
  // NOTHING TO DO
}


// -------------------------------------------------------------------
// O U T P U T
// -------------------------------------------------------------------


// ========================
// WRITE A GREY-LEVEL IMAGE
// ========================


void
MapleFile::write(const GreyLevelImage& aGlvImg, int aRate)
{
 // Open file in WRITE-ONLY mode
  openWONLY();

  // Write header
  fstream_ << "fich :=[";

  int wCnt = (aGlvImg.width()  / aRate) - 1;
  int hCnt = (aGlvImg.height() / aRate) - 1;


  // WARNING: idx is used out of the loop body
  int idx = 0;

  for ( /* VOID */ ; idx < hCnt ; ++idx)
    {
      fstream_ << '[';

      // WARNING: kdx is used out of the loop body
      int kdx = 0;

      for ( /* VOID */ ; kdx < wCnt ; ++kdx)
	{
	  fstream_ << '[' << kdx << ", " << idx << ", "
		   << (int) aGlvImg.pixel(aRate * idx, aRate * kdx)
		   << "],";
	} // END for 

      fstream_ << '[' << kdx << ", " << idx << ", "
	       << (int) aGlvImg.pixel(aRate * idx, aRate * kdx)
	       << "]],";
    } // END for idx


  fstream_ << '[';


 // WARNING: jdx is used out of the loop body
  int jdx = 0;

  for ( /* VOID */ ; jdx < wCnt ; ++jdx)
    {
      fstream_ << '[' << jdx << ", " << idx << ", "
	       << (int) aGlvImg.pixel(aRate * idx, aRate * jdx)
	       << "],";
    } // END for jdx
 

 fstream_ << '[' << jdx << ", " << idx << ", "
	  << (int) aGlvImg.pixel(aRate * idx, aRate * jdx)
	  << "]]];" << std::endl;

  // Write footer
  fstream_ << "with(plots);surfdata(fich);" << std::endl;

  // Close file
  close();
}


// ===================
// WRITE A FLOAT IMAGE
// ===================


void
MapleFile::write(const FloatImage& aFloatImg, int aRate)
{
 // Open file in WRITE-ONLY mode
  openWONLY();

  // Write header
  fstream_ << "fich :=[";

  int wCnt = (aFloatImg.width()  / aRate) - 1;
  int hCnt = (aFloatImg.height() / aRate) - 1;
 

 // WARNING: idx is used out of the loop body
  int idx = 0;

  for ( /* VOID */ ; idx < hCnt ; ++idx)
    {
      fstream_ << '[';

      // WARNING: kdx is used out of the loop body
      int kdx = 0;

      for ( /* VOID */ ; kdx < wCnt ; ++kdx)
	{
	  fstream_ << '[' << kdx << ", " << idx << ", "
		   << aFloatImg.pixel(aRate * idx, aRate * kdx)
		   << "],";
	}

	fstream_ << '[' << kdx << ", " << idx << ", "
		 << aFloatImg.pixel(aRate * idx, aRate * kdx)
		 << "]],";
    } // END for idx


  fstream_ << '[';


 // WARNING: jdx used is out of the loop body
  int jdx = 0;

  for ( /* VOID */ ; jdx < wCnt ; ++jdx)
    {
      fstream_ << '[' << jdx << ", " << idx << ", "
	       << aFloatImg.pixel(aRate * idx, aRate * jdx)
	       << "],";
    } // END for jdx


  fstream_ << '[' << jdx << ", " << idx << ", "
	   << aFloatImg.pixel(aRate * idx, aRate * jdx)
	   << "]]];" << std::endl;

  // Write footer
  fstream_ << "with(plots);surfdata(fich);" << std::endl;

  // Close file
  close();
}


// =================
// WRITE A HISTOGRAM
// =================


void
MapleFile::write(Histogram& aHistogram)
{
  // Open file for in WRITE-ONLY mode
  openWONLY();

  // Write header
  fstream_ << "fich :=[";

  int sRate   = aHistogram.samplingRate();
  int max     = aHistogram.upperBnd();
  // WARNING: the sampling rate may be greater than 1
  int idx     = aHistogram.lowerBnd();
  int nextIdx = idx + sRate;

  for ( /* VOID */ ; idx <= max ; idx += sRate, nextIdx += sRate)
    {
      fstream_ << '[' << idx << ", " << aHistogram[idx] << ']';

      if (nextIdx <= max)
	{
	  fstream_ << ',';
	}
    } // END for

  // Write footer
  fstream_ << "];\nplot(fich);" << std::endl;

  // Close file
  close();
}


// -------------------------------------------------------------------
// D E S T R U C T O R
// -------------------------------------------------------------------


// VIRTUAL DESTRUCTOR

MapleFile::~MapleFile()
{
  // VOID
}


// -------------------------------------------------------------------

} // namespace qgar
