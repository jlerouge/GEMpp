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
 * @file QgarErrorDeveloper.cpp
 *
 * @brief Implementation of class qgar::QgarErrorDeveloper.
 *
 * See file QgarErrorDeveloper.h for the interface.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gerald Masini">Gerald Masini</a>
 * @date   February 18, 2003  16:48
 * @since  qgar 2.1
 */



// STD
#include <cstring>
#include <stdexcept>
// QGAR
#include "QgarErrorDeveloper.h"



namespace qgar
{


// -------------------------------------------------------------------
// C O N S T R U C T O R S
// -------------------------------------------------------------------

// CONSTRUCT FROM THE PROFILE OF THE FUNCTION THROWING THE EXCEPTION,
// WITHOUT DISPLAYING ANY ERROR MESSAGE

QgarErrorDeveloper::QgarErrorDeveloper(const char* aFuncProfile)

  : logic_error(string(aFuncProfile)),
    AbstractQgarError(aFuncProfile)

{
  // VOID
}

// CONSTRUCT AND DISPLAY AN ERROR MESSAGE

QgarErrorDeveloper::QgarErrorDeveloper(const char* aFileName,
                       int aLineNb,
                       const char* aFuncProfile,
                       const string aDiagnostic)

  : logic_error(string(aFuncProfile)),
    AbstractQgarError("DEVELOPER ERROR",
              aFileName,
              aLineNb,
              aFuncProfile,
              aDiagnostic)

{
  // VOID
}

// -------------------------------------------------------------------
// D E S T R U C T O R
// -------------------------------------------------------------------

QgarErrorDeveloper::~QgarErrorDeveloper() throw()
{
  // VOID
}

// -------------------------------------------------------------------


} // namespace qgar
