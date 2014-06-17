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
 * @file assert.cpp
 *
 * @brief Implementation of functions from assert.h.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gerald Masini">Gerald Masini</a>
 * @date   July 4, 2001  17:09
 * @since  qgar 1.0
 */



// STD
#include <iostream>
// QGAR
#include "assert.h"



using namespace std;



namespace qgar
{

// -------------------------------------------------------------------
// GLOBAL FUNCTIONS
// -------------------------------------------------------------------

// Print a diagnostic message about failure of assertion EXPR.
// FILE is the name of the source file including the assertion
// and LINE is the line number of the assertion in the file.

void
__qgPrintAssert(const char* anExpr, const char* aFile, int aLine)
{
  cerr << "QGAR ASSERT>>> Assertion failure: "
       << anExpr
       << endl
       << "  at line "
       << aLine
       << " in file "
       << aFile
       << endl;
}

// -------------------------------------------------------------------

} // namespace qgar
