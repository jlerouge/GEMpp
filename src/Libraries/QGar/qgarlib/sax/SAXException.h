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


#ifndef __SAXEXCEPTION_H_INCLUDED__
#define __SAXEXCEPTION_H_INCLUDED__


/**
 * @file     SAXException.h
 * @brief    Header file of class qgxml::SAXException
 *
 * @author   <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     March 10, 2003  11:14
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id */


#include <stdexcept>
#include <string>

#include "../qgar.h"

namespace qgxml
{

/**
 * @class SAXException SAXException.h "SAXException.h"
 * @ingroup XML
 * @brief Encapsulate a general SAX error or warning.
 *
 * <p>
 * This class can contain basic error or warning information from
 * either the XML parser or the application: a parser writer or
 * application writer can subclass it to provide additional
 * functionality. SAX handlers may throw this exception or any
 * exception subclassed from it.
 * </p>
 * <p>
 * <b> This class is an adaptation for C++ of the interface of the same
 * name implemented in the Java SAX API(http://www.saxproject.org).
 * </b>
 * </p>
 *
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a> (Adaptation)
 * @date   March 10, 2003  11:14
 * @since  Qgar 2.1.1
 *
 * @todo Implement the embedded exception.
 */
class SAXException : public std::runtime_error {

// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

/** @name Constructors */
//        ============
//@{

/**
 * Default Constructor
 */
  SAXException() : std::runtime_error("Unknown Exception")
  { /* EMPTY */ }

/**
 * @brief Copy-Constructor
 */
  SAXException(const SAXException& rhs) 
    :  std::runtime_error( rhs.what() ) 
  { /* EMPTY */ }

/**
 * @brief Create a new SAXException.
 *
 * @param message The error or warning message.
 */
  SAXException(const std::string& message) 
    : std::runtime_error(message.c_str()) 
  { /* EMPTY */ }

//@}




/** @name Access */
//        ======
//@{

/**
 * @brief Return a detail message for this exception.
 *
 * @return The error or warning message.
 */
  virtual const char * getMessage() 
  {
      return what();
  }

/**
 * @brief Return a detail message for this exception.
 *
 * @return The error or warning message.
 */
  virtual const char * getMessage() const
  {
      return what();
  }

//@}






/** @name Destructor */
//        ==========
//@{

/**
 *
 */
  virtual ~SAXException() throw() { }

//@}


}; // class SAXException

} // namespace qgxml


#endif /* __SAXEXCEPTION_H_INCLUDED__ */

