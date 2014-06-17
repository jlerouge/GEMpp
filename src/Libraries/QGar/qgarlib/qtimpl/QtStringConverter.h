/*---------------------------------------------------------------------*
 | Library QgarLib, graphics analysis and recognition                  |
 | Copyright (C) 2003  Qgar Project, LORIA                             |
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


#ifndef __QTSTRINGCONVERTER_H_INCLUDED__
#define __QTSTRINGCONVERTER_H_INCLUDED__

/**
 * @file     QtStringConverter.h
 * @brief    Header file of class QtStringConverter
 *
 * @author   <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     March 17, 2003  17:47
 * @since    Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QtStringConverter.h,v 1.2 2004/06/10 07:56:12 rendek Exp $ */

#include "../qgar.h"

#include <string>
#include <QString>

namespace qgxml {


/**
 * @class QtStringConverter QtStringConverter.h
 * @brief <BRIEF DESCRIPTION ENDING BY A BLANK LINE>
 * 
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   March 17, 2003  17:47
 * @since  Qgar 2.1
 */
class QtStringConverter {

// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  // ----------------------------------------------------
  // USING DEFAULT CONSTRUCTORS, DESTRUCTOR AND OPERATOR.
  // ----------------------------------------------------


 static std::string convert(const QString& qtString)
  {
    return ( (qtString.isNull()) ? "" : std::string(qtString.toLatin1()) );
  }

// -------------------------------------------------------------------

 static QString convert(const std::string& stlString)
  {
    return QString(stlString.c_str());
  }

// -------------------------------------------------------------------

 std::string operator()(const QString& qtString)
  {
    return convert(qtString);
  }
  
// -------------------------------------------------------------------

 QString operator()(const std::string& stlString)
  {
    return convert(stlString);
  }

// -------------------------------------------------------------------

}; // class QtStringConverter

} // namespace qgxml


#endif /* __QTSTRINGCONVERTER_H_INCLUDED__ */
