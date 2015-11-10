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


#ifndef __ERRORHANDLER_H_INCLUDED__
#define __ERRORHANDLER_H_INCLUDED__


/**
 * @file     ErrorHandler.h
 * @brief    Header file of class qgxml::ErrorHandler
 *
 * @author   <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     March 10, 2003  15:56
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: ErrorHandler.h,v 1.5 2004/07/02 20:36:43 masini Exp $ */

#include "../qgar.h"

namespace qgxml {

class SAXParseException;

/**
 * @class ErrorHandler ErrorHandler.h "ErrorHandler.h"
 * @ingroup XML
 * @brief Basic interface for SAX error handlers.
 *
 * If a SAX application needs to implement customized error handling,
 * it must implement this interface and then register an instance with
 * the XML reader using the setErrorHandler method. The parser will
 * then report all errors and warnings through this interface.
 * 
 * <b> This class is an adaptation for C++ of the interface of the same
 * name implemented in the Java SAX API (http://www.saxproject.org).
 * </b>
 * 
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a> (Adaptation).
 * @date   March 10, 2003  15:56
 * @since  Qgar 2.1.1
 */
class ErrorHandler {

// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~ErrorHandler() { }

//@}

/**
 * @brief Receive notification of a recoverable error.
 *
 * @param exception The error information encapsulated in a SAX parse
 *                  exception. 
 */
  virtual void error(const SAXParseException& exception) = 0;
   
/**
 * @brief Receive notification of a non-recoverable error.
 *
 * @param exception The error information encapsulated in a SAX parse
 *                  exception.
 */
  virtual void fatalError(const SAXParseException& exception) = 0;
   
/**
 * @brief Receive notification of a warning.
 *
 * @param exception The warning information encapsulated in a SAX
 *                  parse exception.
 */
  virtual void warning(const SAXParseException& exception) = 0;


// -------------------------------------------------------------------

}; // class ErrorHandler

} // namespace qgxml


#endif /* __ERRORHANDLER_H_INCLUDED__ */
