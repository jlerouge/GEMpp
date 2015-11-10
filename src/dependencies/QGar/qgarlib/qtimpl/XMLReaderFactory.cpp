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

/**
 * @file  XMLReaderFactory.cpp
 * @brief Implementation of class XMLReaderFactory
 *
 *        See file XMLReaderFactory.h for the interface.
 *
 * @warning <COMMENTS DESERVING SPECIAL ATTENTION.
 *           DELETE THESE 3 LINES WHEN USELESS>
 * 
 * @bug  <DESCRIPTION OF KNOWN BUGS, IF ANY.
 *        DELETE THESE 3 LINES WHEN USELESS>
 *
 * @todo <DESCRIPTION OF WHAT REMAINS TO BE DONE.
 *        DELETE THESE 3 LINES WHEN USELESS>
 *
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   March 3, 2003  15:34
 * @since  Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: XMLReaderFactory.cpp,v 1.3 2004/06/21 16:03:37 rendek Exp $ */


#include "../sax/XMLReaderFactory.h"
#include "QtXMLReaderAdaptor.h"


namespace qgxml {


// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
XMLReaderFactory::XMLReaderFactory()
{
}


// -------------------------------------------------------------------

XMLReader *
XMLReaderFactory::createXMLReader() 
{
  return new QtXMLReaderAdaptor();
}


// ----------------------------------------------------------------------

} // namespace qgxml
