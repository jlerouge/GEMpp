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


#ifndef __XMLREADER_H_INCLUDED__
#define __XMLREADER_H_INCLUDED__


/**
 * @file     XMLReader.h
 * @brief    Header file of class qgxml::XMLReader
 *
 * @author   <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     March 3, 2003  15:40
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: XMLReader.h,v 1.5 2004/07/02 20:36:43 masini Exp $ */

#include <string>

#include "../qgar.h"

namespace qgxml {

class ContentHandler;
class DTDHandler;
class EntityResolver;
class ErrorHandler;
class InputSource;




/**
 * @class XMLReader XMLReader.h "XMLReader.h"
 * @ingroup XML
 * @brief Interface for reading an XML document using callbacks.
 *
 * XMLReader is the interface that an XML parser's SAX2 driver must
 * implement. This interface allows an application to set and query
 * features and properties in the parser, to register event handlers
 * for document processing, and to initiate a document parse.
 *
 * <b> This class is an adaptation for C++ of the interface of the same
 * name implemented in the Java SAX API(http://www.saxproject.org).
 * </b> 
 * 
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a> (Adaptation)
 * @date   March 3, 2003  15:40
 * @since  Qgar 2.1.1
 */
class XMLReader {

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
  virtual ~XMLReader() {}

//@}

/** @name Access */
//        ======
//@{
/**
 * @brief Return the current content handler.
 *
 * @return The current content handler, or null if none has been
 *         registered.
 */
  virtual ContentHandler * getContentHandler() const = 0;

/**
 * @brief Return the current DTD handler.
 *
 * @return The current DTD handler, or null if none has been
 *         registered.
 */
  virtual DTDHandler * getDTDHandler() const = 0;

/**
 * @brief Return the current entity resolver.
 *
 * @return The current entity resolver, or null if none has been
 *         registered.
 */
  virtual EntityResolver * getEntityResolver() const = 0;

/**
 * @brief Return the current error handler.
 *
 * @return The current error handler, or null if none has been
 *         registered.
 */
  virtual ErrorHandler * getErrorHandler() const = 0;

/**
 * @brief Look up the value of a feature flag.
 *
 * @param name The feature name.
 *
 * @return The current value of the feature (true or false).
 */
  virtual bool getFeature(const std::string& name) const = 0;

/**
 * @brief Look up the value of a property.
 *
 * @param name The property name.
 *
 * @return The current value of the property.
 */
  virtual void * getProperty(const std::string& name) const = 0;

//@}

/**
 * @brief Parse an XML document.
 *
 * The application can use this method to instruct the XML reader to
 * begin parsing an XML document from any valid input source (a
 * character stream, a byte stream, or a URI). 
 *
 * During the parse, the XMLReader will provide information about the
 * XML document through the registered event handlers.
 *
 * @param input The input source for the top-level of the XML
 *              document.
 */
  virtual void parse(InputSource& input) = 0;

/**
 * @brief Parse an XML document from a system identifier (URI).
 *
 * This method is a shortcut for the common case of reading a document
 * from a system identifier. It is the exact equivalent of parse(new
 * InputSource(systemId));
 *
 * @param systemId The system identifier (URI).
 */
  virtual void parse(const std::string& systemId) = 0;


/** @name Transform */
//        =========
//@{
/**
 * @brief Allow an application to register a content event handler.
 *
 * If the application does not register a content handler, all content
 * events reported by the SAX parser will be silently ignored. 
 *
 * Applications may register a new or different handler in the middle
 * of a parse, and the SAX parser must begin using the new handler
 * immediately.
 *
 * @param handler The content handler.
 */
  virtual void setContentHandler(ContentHandler * handler) = 0;

/**
 * @brief Allow an application to register a DTD event handler.
 *
 * If the application does not register a DTD handler, all DTD events
 * reported by the SAX parser will be silently ignored. 
 *
 * Applications may register a new or different handler in the middle
 * of a parse, and the SAX parser must begin using the new handler
 * immediately.
 *
 * @param handler The DTD handler.
 */
  virtual void setDTDHandler(DTDHandler * handler) = 0;

/**
 * @brief Allow an application to register an entity resolver.
 *
 * If the application does not register an entity resolver, the
 * XMLReader will perform its own default resolution. 
 *
 * Applications may register a new or different resolver in the middle
 * of a parse, and the SAX parser must begin using the new resolver
 * immediately.
 *
 * @param resolver The entity resolver.
 */
  virtual void setEntityResolver(EntityResolver * resolver) = 0;

/**
 * @brief Allow an application to register an error event handler.
 *
 * If the application does not register an error handler, all error
 * events reported by the SAX parser will be silently ignored;
 * however, normal processing may not continue. 
 *
 * Applications may register a new or different handler in the middle
 * of a parse, and the SAX parser must begin using the new handler
 * immediately.
 *
 * @param handler The error handler.
 */
  virtual void setErrorHandler(ErrorHandler * handler) = 0;

/**
 * @brief Set the value of a feature flag.
 *
 * @param name  The feature name.
 * @param value The requested value of the feature (true or false).
 */
  virtual void setFeature(const std::string& name, bool value) = 0;

/**
 * @brief Set the value of a property.
 *
 * @param name  The property name.
 * @param value The requested value for the property.
 */
  virtual void setProperty(const std::string& name, void * value) = 0;
//@}


}; // class XMLReader

} // namespace qgxml


#endif /* __XMLREADER_H_INCLUDED__ */
