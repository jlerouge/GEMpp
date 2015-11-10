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
 * @file AbstractQgarError.cpp
 *
 * @brief Implementation of class qgar::AbstractQgarError.
 *
 * See file AbstractQgarError.h for the interface.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gerald Masini">Gerald Masini</a>
 * @date   February 18, 2003  16:48
 * @since  qgar 2.1
 */


// STD
#include <string>
#include <iostream>
// QGAR
#include "AbstractQgarError.h"



using namespace std;



namespace qgar
{


// -------------------------------------------------------------------
// S T A T I C   M E M B E R   I N I T I A L I Z A T I O N S
// -------------------------------------------------------------------


bool AbstractQgarError::msgFlag_ = true;


// -------------------------------------------------------------------
// C O N S T R U C T O R S 
// -------------------------------------------------------------------


// CONSTRUCT FROM THE PROFILE OF THE FUNCTION THROWING THE EXCEPTION,
// WITHOUT DISPLAYING ANY ERROR MESSAGE

AbstractQgarError::AbstractQgarError(const char* aFuncProfile)
{
    Q_UNUSED(aFuncProfile);
    // VOID
}


// CONSTRUCT AND DISPLAY AN ERROR MESSAGE

AbstractQgarError::AbstractQgarError(const char* anErrorKind,
                                     const char* aFileName,
                                     int aLineNb,
                                     const char* aFuncProfile,
                                     const string aDiagnostic)
{
    if(msgFlag_)
    {
        displayHeader(anErrorKind);
        cerr << "Line "
             << aLineNb
             << " in file: "
             << aFileName
             << endl
             << "Function: "
             << aFuncProfile
             << endl
             << ">>> "
             << aDiagnostic
             << endl
             << endl;
    }
}


// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------


AbstractQgarError::~AbstractQgarError()
{
    // VOID
}


// -------------------------------------------------------------------
// D I S P L A Y 
// -------------------------------------------------------------------


void AbstractQgarError::errorMsgOn()
{
    msgFlag_ = true;
}


void AbstractQgarError::errorMsgOff()
{
    msgFlag_ = false;
}


void AbstractQgarError::displayHeader(const char* anErrorKind) const
{
    cerr << endl
         << endl
         << "QGAR: "
         << anErrorKind
         << endl;
}


// -------------------------------------------------------------------


} // namespace qgar
