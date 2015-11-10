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
 * @file  QtQgarErrorHandlerAdaptor.cpp
 * @brief Implementation of class QtQgarErrorHandlerAdaptor.
 *
 *        See file QtQgarErrorHandlerAdaptor.h for the interface.
 *
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   March 11, 2003  15:03
 * @since  Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QtQgarErrorHandlerAdaptor.cpp,v 1.4 2004/07/01 22:19:21 masini Exp $ */


#include "QtQgarErrorHandlerAdaptor.h"

// QGAR
#include "../sax/ErrorHandler.h"
#include "../sax/SAXParseException.h"

namespace qgxml {


// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QtQgarErrorHandlerAdaptor::QtQgarErrorHandlerAdaptor(ErrorHandler * h)
{
  _impl = h;
}


// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------

QtQgarErrorHandlerAdaptor::~QtQgarErrorHandlerAdaptor()
{ /* NOP */ }

// ---------------------------------------------------------------------
// O T H E R
// ---------------------------------------------------------------------

bool 
QtQgarErrorHandlerAdaptor::error(const QXmlParseException & exception)
{
  bool retval = true;

  try {

    _impl->error(SAXParseException(_sc(exception.message()),
				   _sc(exception.publicId()),
				   _sc(exception.systemId()),
				   exception.lineNumber(),
				   exception.columnNumber()
				   ));
  }
  catch(SAXParseException& e) {
    retval = false;
    _errorMsg = e.getMessage();
  }

  return retval;
}

// ---------------------------------------------------------------------
  
bool 
QtQgarErrorHandlerAdaptor::fatalError(const QXmlParseException& exception) 
{
  bool retval = true;

  try {

    _impl->fatalError(SAXParseException(_sc(exception.message()),
					_sc(exception.publicId()),
					_sc(exception.systemId()),
					exception.lineNumber(),
					exception.columnNumber()
					));
  }
  catch(SAXException& e) {
    retval = false;
    _errorMsg = e.getMessage();
  }

  return retval;
}

// ---------------------------------------------------------------------
  
bool 
QtQgarErrorHandlerAdaptor::warning(const QXmlParseException& exception)
{
  bool retval = true;

  try {

    _impl->warning(SAXParseException(_sc(exception.message()),
				     _sc(exception.publicId()),
				     _sc(exception.systemId()),
				     exception.lineNumber(),
				     exception.columnNumber()
				     ));

  }
  catch(SAXException& e) {
    retval = false;
    _errorMsg = e.getMessage();
  }

  return retval;
}

// ---------------------------------------------------------------------

QString
QtQgarErrorHandlerAdaptor::errorString() const
{
  return _errorMsg;
}

// ----------------------------------------------------------------------

} // namespace qgxml
