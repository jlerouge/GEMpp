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


#ifndef __ENTITYRESOLVER_H_INCLUDED__
#define __ENTITYRESOLVER_H_INCLUDED__


/**
 * @file     EntityResolver.h
 * @brief    Header file of class qgxml::EntityResolver
 *
 * @author   <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     March 10, 2003  15:52
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: EntityResolver.h,v 1.6 2004/07/02 20:36:43 masini Exp $ */


#include <string>

#include "../qgar.h"

namespace qgxml {

class InputSource;

/**
 * @class EntityResolver EntityResolver.h "EntityResolver.h"
 * @ingroup XML
 * @brief Basic interface for resolving entities.
 *
 * <p> 
 * If a SAX application needs to implement customized handling for
 * external entities, it must implement this interface and register an
 * instance with the SAX driver using the setEntityResolver  method. 
 * </p>
 * <p>
 * The XML reader will then allow the application to intercept any
 * external entities (including the external DTD subset and external
 * parameter entities, if any) before including them.
 * </p>
 * 
 * <b> This class is an adaptation for C++ of the interface of the same
 * name implemented in the Java SAX API (http://www.saxproject.org).
 * </b>
 * 
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a> (Adaptation).
 * @date   March 10, 2003  15:52
 * @since  Qgar 2.1.1
 */
class EntityResolver {

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
  virtual ~EntityResolver() { }
//@}

/**
 * @brief Allow the application to resolve external entities.
 *
 * @param publicId The public identifier of the external entity being
 *                 referenced.
 * @param systemId The system identifier of the external entity being
 *                 referenced. 
 *
 * @return An InputSource object describing the new input source.
 */
  virtual InputSource * resolveEntity(const std::string& publicId,
				      const std::string& systemId) = 0;



// -------------------------------------------------------------------

}; // class EntityResolver

} // namespace qgxml


#endif /* __ENTITYRESOLVER_H_INCLUDED__ */
