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


#ifndef __SAXPARSEEXCEPTION_H_INCLUDED__
#define __SAXPARSEEXCEPTION_H_INCLUDED__


/**
 * @file     SAXParseException.h
 * @brief    Header file of class qgxml::SAXParseException
 *
 * @author   <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     March 11, 2003  15:34
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: SAXParseException.h,v 1.5 2004/07/02 20:36:43 masini Exp $ */

#include <string>
#include "Locator.h"
#include "SAXException.h"

namespace qgxml {


/**
 * @class SAXParseException SAXParseException.h "SAXParseException.h"
 * @ingroup XML
 * @brief Encapsulate an XML parse error or warning.
 *
 * This exception may include information for locating the error in
 * the original XML document, as if it came from a Locator  object. 
 *
 * <b> This class is an adaptation for C++ of the interface of the same
 * name implemented in the Java SAX API(http://www.saxproject.org).
 * </b>
 * 
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a> (Adaptation)
 * @date   March 11, 2003  15:34
 * @since  Qgar 2.1.1
 */
class SAXParseException : public SAXException {

// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:


/** @name Constructors */
//        ============
//@{
/**
 * @brief Default constructor
 */
  SAXParseException() 
  { /* EMPTY */ }

/**
 * @brief Create a new SAXParseException from a message and a
 * Locator.
 *
 * @param message The error or warning message.
 * @param locator The locator object for the error or warning.
 */
  SAXParseException(const std::string & message, 
		    const Locator &  locator) 
    : SAXException(message),
      _publicId(locator.getPublicId()),
      _systemId(locator.getSystemId()),
      _lineNumber(locator.getLineNumber()),
      _columnNumber(locator.getColumnNumber())
  { /* EMPTY */  }

/**
 * @brief Create a new SAXParseException.
 *
 * @param message      The error or warning message.
 * @param publicId     The public identifier of the entity that
 *                     generated the error or warning.
 * @param systemId     The system identifier of the entity that
 *                     generated the error or warning.
 * @param lineNumber   The line number of the end of the text that
 *                     caused the error or warning. 
 * @param columnNumber The column number of the end of the text that
 *                     cause the error or warning.
 */
  SAXParseException(const std::string & message, 
		    const std::string & publicId,
		    const std::string & systemId,
		    int lineNumber,
		    int columnNumber)
    : SAXException(message),
      _publicId(publicId),
      _systemId(systemId),
      _lineNumber(lineNumber),
      _columnNumber(columnNumber)
  { /* EMPTY */ }
		  
//@}


/** @name Destructor */
//        ==========
//@{
/**
 * @brief Destructor
 */
  virtual ~SAXParseException() throw() {}
//@}


/** @name Access */
//        ======
//@{

/**
 * @brief Get the public identifier of the entity where the exception
 * occurred.
 *
 * @return A string containing the public identifier, or an empty
 *         string if none is available.
 */
  std::string getPublicId() const
  {
    return _publicId;
  }

/**
 * @brief Get the system identifier of the entity where the exception
 * occurred.
 *
 * @return A string containing the system identifier, or an empty
 *         string if none is available.
 */
  std::string getSystemId() const
  {
    return _systemId;
  }

/**
 * @brief The line number of the end of the text where the exception
 * occurred.
 *
 * @return An integer representing the line number, or -1 if none is
 *         available.
 */
  int getLineNumber() const
  {
    return _lineNumber;
  }

/**
 * @brief The column number of the end of the text where the exception
 * occurred.
 *
 * @return An integer representing the column number, or -1 if none is
 *            available.
 */
  int getColumnNumber() const
  {
    return _columnNumber;
  }
//@}



protected:
  
  /// The public identifier of the entity where the exception occurred.
  std::string _publicId;

  /// The system identifier of the entity where the exception occurred.
  std::string _systemId;

  /**
   * The line number of the end of the text where the exception
   * occurred.
   */
  int _lineNumber;

  /**
   * The column number of the end of the text where the exception
   * occurred.
   */
  int _columnNumber;

// -------------------------------------------------------------------

}; // class SAXParseException

} // namespace qgxml


#endif /* __SAXPARSEEXCEPTION_H_INCLUDED__ */
