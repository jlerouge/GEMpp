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


#ifndef __DTDHANDLER_H_INCLUDED__
#define __DTDHANDLER_H_INCLUDED__


/**
 * @file     DTDHandler.h
 * @brief    Header file of class qgxml::DTDHandler
 *
 * @author   <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     March 10, 2003  15:33
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: DTDHandler.h,v 1.5 2004/07/02 20:36:43 masini Exp $ */

#include <string>

#include "../qgar.h"

namespace qgxml {


/**
 * @class DTDHandler DTDHandler.h "DTDHandler.h"
 * @ingroup XML
 * @brief Receive notification of basic DTD-related events.
 *
 * If a SAX application needs information about notations and unparsed
 * entities, then the application implements this interface and
 * registers an instance with the SAX parser using the parser's
 * setDTDHandler method. The parser uses the instance to report
 * notation and unparsed entity declarations to the application.
 * 
 * <b> This class is an adaptation for C++ of the interface of the same
 * name implemented in the Java SAX API (http://www.saxproject.org).
 * </b>
 *
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   March 10, 2003  15:33
 * @since  Qgar 2.1.1
 */
class DTDHandler {

// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

/** @name Destructors */
//        ===========
//@{
/**
 * @brief Destructor
 */
  virtual ~DTDHandler() {}

//@}


/**
 * @brief Receive notification of a notation declaration event.
 *
 * @param name     The notation name.
 * @param publicId The notation's public identifier.
 * @param systemId The notation's system identifier.
 */
  virtual void notationDecl(const std::string & name, 
			    const std::string & publicId, 
			    const std::string & systemId) = 0;
  
/**
 * @brief Receive notification of an unparsed entity declaration event.
 *
 * @param name         The unparsed entity's name.
 * @param publicId     The entity's public identifier.
 * @param systemId     The entity's system identifier.
 * @param notationName The name of the associated notation.
 */
  virtual void unparsedEntityDecl(const std::string & name,
				  const std::string & publicId, 
				  const std::string & systemId,
				  const std::string & notationName) = 0;


// -------------------------------------------------------------------

}; // class DTDHandler

} // namespace qgxml


#endif /* __DTDHANDLER_H_INCLUDED__ */
