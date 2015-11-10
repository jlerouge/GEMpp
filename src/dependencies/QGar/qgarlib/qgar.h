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

#ifndef __QGAR_H_INCLUDED__
#define __QGAR_H_INCLUDED__

/**
 * @file qgar.h
 *
 * @brief Global utilities for information about Qgar Software.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   June 16, 2006  17:07
 * @since  Qgar 2.2
 */


// For RCS/CVS use: Do not delete
/* $Id: qgar.h,v 1.1 2006/06/23 15:32:45 gerald Exp $ */

#include "../../library/Core/Portability.h"
#include <QtCore>

namespace qgar
{


// -------------------------------------------------------------------
// Q G A R   V E R S I O N
// -------------------------------------------------------------------


/** @name Global functions about array indexes */
//        ====================================
//@{

/**
 * @ingroup GLOB_QGAR
 *
 * @brief Return the current version number of the Qgar Software.
 */
inline double
qgVersionNb()
{
    return 4.0;
}

/**
 * @ingroup GLOB_QGAR
 *
 * @brief Return the full name of the current Qgar Software version.
 */
inline const char* //const
qgVersion()
{
    return "Qgar 4.0 (Caravelas version), August 28, 2008";
}

// -------------------------------------------------------------------

} // namespace qgar


#endif /* __QGAR_H_INCLUDED__ */
