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


#ifndef __CONTENTHANDLER_H_INCLUDED__
#define __CONTENTHANDLER_H_INCLUDED__


/**
 * @file     ContentHandler.h
 * @brief    Header file of class qgxml::ContentHandler.
 *
 * @author   <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     March 3, 2003  16:45
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: ContentHandler.h,v 1.7 2004/07/02 20:36:43 masini Exp $ */

#include <string>

#include "../qgar.h"

namespace qgxml {

class Attributes;
class Locator;


/**
 * @class ContentHandler ContentHandler.h "ContentHandler.h"
 * @ingroup XML
 * @brief Receive notification of the logical content of a document
 *
 * This is the main interface that most SAX applications implement: if
 * the application needs to be informed of basic parsing events, it
 * implements this interface and registers an instance with the SAX
 * parser using the setContentHandler method. The parser uses the
 * instance to report basic document-related events like the start and
 * end of elements and character data. 
 *
 * The order of events in this interface is very important, and
 * mirrors the order of information in the document itself. For
 * example, all of an element's content (character data, processing
 * instructions, and/or subelements) will appear, in order, between
 * the startElement event and the corresponding endElement event.
 * 
 * <b> This class is an adaptation for C++ of the interface of the same
 * name implemented in the Java SAX API (http://www.saxproject.org).
 * </b>
 *
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a> (Adaptation).
 * @date   March 3, 2003  16:45
 * @since  Qgar 2.1.1
 */
class ContentHandler {

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
  virtual ~ContentHandler() {}
//@}

  
/**
 * @brief Receive notification of character data.
 * 
 * @param ch     The characters from the XML document.
 * @param start  The start position in the array.
 * @param length The number of characters to read from the array.
 */
  virtual void characters(const char * ch, 
			  const unsigned int start, 
			  const unsigned int length) = 0;
  
/**
 * @brief Receive notification of the end of a document.
 *
 * The SAX parser will invoke this method only once, and it will be
 * the last method invoked during the parse. The parser shall not
 * invoke this method until it has either abandoned parsing (because
 * of an unrecoverable error) or reached the end of input.
 *
 * @see startDocument()
 */
  virtual void endDocument() = 0;

/**
 * @brief Receive notification of the end of an element.
 *
 * The SAX parser will invoke this method at the end of every element
 * in the XML document; there will be a corresponding startElement
 * event for every endElement event (even when the element is empty).
 *
 * @param uri       The Namespace URI, or the empty string if the
 *                  element has no Namespace URI or if Namespace
 *                  processing is not being performed. 
 * @param localName The local name (without prefix), or the empty
 *                  string if Namespace processing is not being performed.
 * @param qName     The qualified XML 1.0 name (with prefix), or the
 *                  empty string if qualified names are not
 *                  available.
 *
 * @see startElement()
 */
  virtual void endElement(const std::string& uri,
			  const std::string& localName, 
			  const std::string& qName) = 0;

/**
 * @brief End the scope of a prefix-URI mapping.
 *
 * @param prefix The prefix that was being mapped. This is the empty
 *               string when a default mapping scope ends.
 *
 * @see startPrefixMapping
 */
  virtual void endPrefixMapping(const std::string& prefix) = 0;
  
/**
 * @brief Receive notification of ignorable whitespace in element
 * content.
 *
 * @param ch     The characters from the XML document.
 * @param start  The start position in the array.
 * @param length The number of characters to read from the array.
 */
  virtual void ignorableWhitespace(const char * ch, 
				   const unsigned int start, 
				   const unsigned int length) =  0;
  
/**
 * @brief Receive notification of a processing instruction.
 *
 * @param target The processing instruction target.
 * @param data   The processing instruction data. The data does not
 *               include any whitespace separating it from the
 *               target.
 */
  virtual void processingInstruction(const std::string& target, 
				     const std::string& data) = 0;
  
/**
 * @brief Receive an object for locating the origin of SAX document
 * events.
 *
 * @param locator An object that can return the location of any SAX
 *                document event.
 */
  virtual void setDocumentLocator(Locator * locator) = 0;
  
/**
 * @brief Receive notification of a skipped entity.
 *
 * @param name The name of the skipped entity.
 */
  virtual void skippedEntity(const std::string& name) = 0;
  
/**
 * @brief Receive notification of the beginning of a document.
 *
 * The SAX parser will invoke this method only once, before any other
 * event callbacks (except for setDocumentLocator()).
 * 
 * @see endDocument()
 */
  virtual void startDocument() = 0;

/**
 * @brief Receive notification of the beginning of an element.
 *
 * The Parser will invoke this method at the beginning of every
 * element in the XML document; there will be a corresponding
 * endElement event for every startElement event (even when the
 * element is empty). All of the element's content will be reported,
 * in order, before the corresponding endElement event.
 *
 * @param uri       The Namespace URI, or the empty string if the
 *                  element has no Namespace URI or if Namespace
 *                  processing is not being performed. 
 * @param localName The local name (without prefix), or the empty
 *                  string if Namespace processing is not being
 *                  performed.
 * @param qName     The qualified name (with prefix), or the empty
 *                  string if qualified names are not available.
 * @param atts      The attributes attached to the element.
 *
 * @see endElement()
 */
  virtual void startElement(const std::string& uri,
			    const std::string& localName,
			    const std::string& qName,
			    const Attributes& atts) = 0;
  
/**
 * @brief Begin the scope of a prefix-URI Namespace mapping.
 *
 * @param prefix The Namespace prefix being declared. An empty string
 *               is used for the default element namespace, which has
 *               no prefix.
 * @param uri    The Namespace URI the prefix is mapped to.
 *
 * @see endPrefixMapping()
 */
  virtual void startPrefixMapping(const std::string& prefix, 
				  const std::string& uri) = 0;
  

// -------------------------------------------------------------------

}; // class ContentHandler

} // namespace qgxml


#endif /* __CONTENTHANDLER_H_INCLUDED__ */
