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
 * @file AbstractPbmPlusFile.cpp
 *
 * @brief Implementation of class qgar::AbstractPbmPlusFile.
 *
 * See file AbstractPbmPlusFile.h for the interface.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   Jul 3, 2001  16:32
 * @since  qgar 1.0
 */



// QGAR
#include "AbstractPbmPlusFile.h"
#include "QgarErrorIO.h"
#include "QgarErrorUser.h"



namespace qgar
{


// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
// S T A T I C   M E M B E R S
// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS


// ==============================
// CHARACTERISTICS OF A PBM+ FILE
// ==============================

// CHARACTER INTRODUCING THE MAGIC NUMBER
const unsigned char AbstractPbmPlusFile::s_pbm_magic_   = 'P';

// CHARACTER INTRODUCING COMMENTS
const unsigned char AbstractPbmPlusFile::s_pbm_comment_ = '#';


// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
// E N D   O F   S T A T I C   M E M B E R S
// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS




// -------------------------------------------------------------------
// C O N S T R U C T O R 
// -------------------------------------------------------------------


AbstractPbmPlusFile::AbstractPbmPlusFile(const char* aFileName,
					 QGEpbm aPbm)

  : AbstractFile(aFileName),
    format_(aPbm)

{
  // VOID
}


// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------


AbstractPbmPlusFile::~AbstractPbmPlusFile()
{
  // VOID
}


// -------------------------------------------------------------------

} // namespace qgar
