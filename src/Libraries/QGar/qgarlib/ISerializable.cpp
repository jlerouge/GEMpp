/*---------------------------------------------------------------------*
 | Library QgarLib, graphics analysis and recognition                  |
 | Copyright (C) 2004  Qgar Project, LORIA                             |
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
 | http://www.gnu.org/licenses/lgpl.html for the terms of the license. |
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
 * @file ISerializable.cpp
 *
 * @brief Implementation of global functions for object (de)serialization.
 *
 * See file ISerializable.h for the interface.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   December 07, 2004  18:19
 * @since  Qgar 2.2
 */



// STD
#include <sstream>
// QGAR
#include "ISerializable.h"
#include "QgarErrorIO.h"



using namespace std;



namespace qgar
{

// -------------------------------------------------------------------
// D E S E R I A L I Z A T I O N
// -------------------------------------------------------------------

// READ THE NAME PART OF AN OBJECT

void qgReadObjName(std::istream& anIStream, const char* aClassName)



{
  char c;

  do
    {
      anIStream.get(c);
    }
  while (isspace(c));

  int idx = 0;

  while ((size_t)idx < strlen(aClassName))
  {
    if (c != aClassName[idx])
      {
      ostringstream os;
      os << "Error in input stream: '"
	 << aClassName
	 << "' expected";

      throw QgarErrorIO(__FILE__, __LINE__,
			"void qgar::qgReadObjName(std::istream&, const char*)",
			os.str());
      }

    ++idx;
    anIStream.get(c);
  }

  anIStream.putback(c);
}

// ----------------------------------------------------------------------

} // namespace qgar
