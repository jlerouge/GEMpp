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
 * @file   AbstractFile.cpp
 *
 * @brief  Implementation of class qgar::AbstractFile.
 *
 * See file AbstractFile.h for the interface.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   July 2, 2001  17:13
 * @since  Qgar 1.0
 */


// STD
#include <cstring>
#include <fstream>
#include <sstream>
// QGAR
#include "AbstractFile.h"
#include "QgarErrorIO.h"
#include "QgarErrorInvalidArg.h"



using namespace std;



namespace qgar
{


// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------


AbstractFile::AbstractFile(const char* aFileName)



  : mode_(QGE_FILE_MODE_CLOSED)

{
  // Close file in any case
  fstream_.close();

  // Check file name
  if ((aFileName == 0) || (*aFileName == '\0'))
    {
      throw QgarErrorInvalidArg(__FILE__, __LINE__,
				"qgar::AbstractFile::AbstractFile(const char*)",
				"Empty file name");
    }

  name_ = new char[strlen(aFileName) + 1];
  strcpy(name_, aFileName);
}


// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------


AbstractFile::~AbstractFile()
{
  delete [] name_;
}


// ---------------------------------------------------------------------
// O P E N I N G
// ---------------------------------------------------------------------


// OPEN IN READ-ONLY MODE

void
AbstractFile::openRONLY()
{
  // Close file in any case
  close();

  // Open file in appropriate mode
  // Courtesy of Microsoft Corp.:
  // the failbits MUST be cleared before calling open()
  fstream_.clear();
  fstream_.open(name_, ios::in | ios::binary);

  if (!fstream_)
    {
      ostringstream os;
      os << "Cannot open file "
	 << name_
	 << " in read-only mode";
      throw QgarErrorIO(__FILE__, __LINE__,
			"void qgar::AbstractFile::openRONLY()",
			os.str());
    }

  mode_ = QGE_FILE_MODE_READ_ONLY;

  // Set file pointer to the beginning of the file
  fstream_.seekg(0);
}


// OPEN FOR WRITE-ONLY MODE

void
AbstractFile::openWONLY()
{
  // Close file in any case
  close();

  // Open file in appropriate mode
  // Courtesy of Microsoft Corp.:
  // 1. the failbits MUST be cleared before calling open()
  // 2. ios::trunc MUST be specified within MSVC++
  fstream_.clear();
  fstream_.open(name_, ios::out | ios::trunc | ios::binary);

  if (!fstream_)
    {
      ostringstream os;
      os << "Cannot open file "
	 << name_
	 << " in write-only mode";
      throw QgarErrorIO(__FILE__, __LINE__,
			"void qgar::AbstractFile::openWONLY()",
			os.str());
    }

  mode_ = QGE_FILE_MODE_WRITE_ONLY;

  // Set file pointer to the beginning of the file
  fstream_.seekg(0);
}


// OPEN IN APPEND MODE

void
AbstractFile::openAPPEND()
{
  // Close file in any case
  close();

  // Open file in appropriate mode
  // Courtesy of Microsoft Corp.:
  // the failbits MUST be cleared before calling open()
  fstream_.clear();
  fstream_.open(name_, ios::app | ios::binary);

  if (!fstream_)
    {
      ostringstream os;
      os << "Cannot open file "
	 << name_
	 << " in append mode";
      throw QgarErrorIO(__FILE__, __LINE__,
			"void qgar::AbstractFile::openAPPEND()",
			os.str());
    }

  mode_ = QGE_FILE_MODE_APPEND;

  // Set file pointer to the end of the file
  fstream_.seekg(0, ios::end);
}


// OPEN IN READ-WRITE MODE

void
AbstractFile::openRW()
{
  // Close file in any case
  close();

  // Open file in appropriate mode
  fstream_.open(name_, ios::in | ios::out | ios::binary);

  if (!fstream_) 
    {
      ostringstream os;
      os << "Cannot open file "
	 << name_
	 << " in read-write mode";
      throw QgarErrorIO(__FILE__, __LINE__,
			"void qgar::AbstractFile::openRW()",
			os.str());
    }

  mode_ = QGE_FILE_MODE_READ_WRITE;

  // Set file pointer to the beginning of the file
  fstream_.seekg(0);
}


// OPEN IN READ-APPEND MODE

void
AbstractFile::openRA()
{
  // Close file in any case
  close();

  // Open file in appropriate mode
  fstream_.open(name_, ios::in | ios::app | ios::binary);

  if (!fstream_)
    {
      ostringstream os;
      os << "Cannot open file "
	 << name_
	 << " in read-append mode";
      throw QgarErrorIO(__FILE__, __LINE__,
			"void qgar::AbstractFile::openRA()",
			os.str());
    }

  mode_ = QGE_FILE_MODE_READ_APPEND;

  // Set file pointer to the end of the file
  fstream_.seekg(0, ios::end);
}


// ---------------------------------------------------------------------
// C L O S I N G
// ---------------------------------------------------------------------


// CLOSE FILE

void
AbstractFile::close()
{
  // No effect if the file is already closed

  if (!isClosed())
    {
      fstream_.close();
      mode_ = QGE_FILE_MODE_CLOSED;
    }
}


// ----------------------------------------------------------------------

} // namespace qgar
