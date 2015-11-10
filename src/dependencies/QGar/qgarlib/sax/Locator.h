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


#ifndef __LOCATOR_H_INCLUDED__
#define __LOCATOR_H_INCLUDED__


/**
 * @file     Locator.h
 * @brief    Header file of class qgxml::Locator
 *
 * @author   <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     March 10, 2003  14:39
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: Locator.h,v 1.5 2004/07/02 20:36:43 masini Exp $ */

#include <string>

#include "../qgar.h"

namespace qgxml {


/**
 * @class Locator Locator.h "Locator.h"
 * @ingroup XML
 * @brief Interface for associating a SAX event with a document
 * location.
 *
 * If a SAX parser provides location information to the SAX
 * application, it does so by implementing this interface and then
 * passing an instance to the application using the content handler's
 * setDocumentLocator method. The application can use the object to
 * obtain the location of any other SAX event in the XML source
 * document.
 *
 * <b> This class is an adaptation for C++ of the interface of the same
 * name implemented in the Java SAX API (http://www.saxproject.org).
 * </b>
 * 
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a> (Adaptation).
 * @date   March 10, 2003  14:39
 * @since  Qgar 2.1.1
 */
class Locator {

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
  virtual ~Locator() 
  { /* EMPTY */ }
//@}


/** @name Access */
//        ======
//@{

/**
 * @brief Return the column number where the current document event
 * ends.
 *
 * @return The column number.
 */
  virtual int getColumnNumber() const = 0;

/**
 * @brief Return the line number where the current document event
 * ends.
 *
 * @return The line number.
 */
  virtual int getLineNumber() const = 0;

/**
 * @brief Return the public identifier for the current document
 * event.
 *
 * @return A string containing the public identifier, or an empty
 * string if none is available.
 */
  virtual std::string getPublicId() const = 0;

/**
 * @brief Return the system identifier for the current document
 * event.
 *
 * @return A string containing the system identifier, or an empty
 * string if none is available.
 */
  virtual std::string getSystemId() const = 0;
//@}


// -------------------------------------------------------------------

}; // class Locator

} // namespace qgxml


#endif /* __LOCATOR_H_INCLUDED__ */
