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


#ifndef __DEFAULTHANDLER_H_INCLUDED__
#define __DEFAULTHANDLER_H_INCLUDED__


/**
 * @file     DefaultHandler.h
 * @brief    Header file of class qgxml::DefaultHandler
 *
 * @author   <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     March 3, 2003  17:47
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: DefaultHandler.h,v 1.5 2004/07/02 20:36:43 masini Exp $ */

#include "ContentHandler.h"
#include "DTDHandler.h"
#include "EntityResolver.h"
#include "ErrorHandler.h"
#include "Attributes.h"
#include "SAXParseException.h"

namespace qgxml {


/**
 * @class DefaultHandler DefaultHandler.h "DefaultHandler.h"
 * @ingroup XML
 * @brief Default base class for SAX2 event handlers.
 *
 * This class is available as a convenience base class for SAX2
 * applications: it provides default implementations for all of the
 * callbacks in the four core SAX2 handler classes:
 * - EntityResolver
 * - DTDHandler
 * - ContentHandler
 * - ErrorHandler
 *
 * @see ContentHandler
 * @see DTDHandler
 * @see EntityResolver
 * @see ErrorHandler
 *
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   March 3, 2003  17:47
 * @since  Qgar 2.1.1
 */
class DefaultHandler : public ContentHandler,
        public DTDHandler,
        public EntityResolver,
        public ErrorHandler
{

    // -------------------------------------------------------------------
    // P U B L I C    M E M B E R S
    // -------------------------------------------------------------------
public:

    // --------------------------------------
    // USING DEFAULT CONSTRUCTOR & DESTRUCTOR
    // --------------------------------------


    /** @name ContentHandler Impl */
    //        ===================
    //@{

    virtual void characters(const char * ch,
                            const unsigned int start,
                            const unsigned int length)
    {
        Q_UNUSED(ch);
        Q_UNUSED(start);
        Q_UNUSED(length);
        /* EMPTY */
    }


    virtual void endDocument()
    { /* EMPTY */ }


    virtual void endElement(const std::string& uri,
                            const std::string& localName,
                            const std::string& qName)
    {
        Q_UNUSED(uri);
        Q_UNUSED(localName);
        Q_UNUSED(qName);
        /* EMPTY */
    }


    virtual void endPrefixMapping(const std::string& prefix)
    {
        Q_UNUSED(prefix);
        /* EMPTY */
    }


    virtual void ignorableWhitespace(const char * ch,
                                     const unsigned int start,
                                     const unsigned int length)
    {
        Q_UNUSED(ch);
        Q_UNUSED(start);
        Q_UNUSED(length);
        /* EMPTY */
    }


    virtual void processingInstruction(const std::string& target,
                                       const std::string& data)
    {
        Q_UNUSED(target);
        Q_UNUSED(data);
        /* EMPTY */
    }


    virtual void setDocumentLocator(Locator * locator)
    {
        Q_UNUSED(locator);
        /* EMPTY */
    }


    virtual void skippedEntity(const std::string& name)
    {
        Q_UNUSED(name);
        /* EMPTY */
    }


    virtual void startDocument()
    { /* EMPTY */ }


    virtual void startElement(const std::string& uri,
                              const std::string& localName,
                              const std::string& qName,
                              const Attributes& atts)
    {
        Q_UNUSED(uri);
        Q_UNUSED(localName);
        Q_UNUSED(qName);
        Q_UNUSED(atts);
        /* EMPTY */
    }


    virtual void startPrefixMapping(const std::string& prefix,
                                    const std::string& uri)
    {
        Q_UNUSED(prefix);
        Q_UNUSED(uri);
        /* EMPTY */
    }


    //@}

    /** @name DTDHandler Impl */
    //        ===============
    //@{

    virtual void notationDecl(const std::string& name,
                              const std::string& publicId,
                              const std::string& systemId)
    {
        Q_UNUSED(name);
        Q_UNUSED(publicId);
        Q_UNUSED(systemId);
        /* EMPTY */
    }


    virtual void unparsedEntityDecl(const std::string& name,
                                    const std::string& publicId,
                                    const std::string& systemId,
                                    const std::string& notationName)
    {
        Q_UNUSED(name);
        Q_UNUSED(publicId);
        Q_UNUSED(systemId);
        Q_UNUSED(notationName);
        /* EMPTY */
    }

    //@}

    /** @name EntityResolver Impl */
    //        ===================
    //@{

    virtual InputSource * resolveEntity(const std::string& publicId,
                                        const std::string& systemId)
    {
        Q_UNUSED(publicId);
        Q_UNUSED(systemId);
        return 0;
    }

    //@}

    /** @name ErrorHandler Impl */
    //        =================
    //@{

    virtual void error(const SAXParseException& exception)
    {
        Q_UNUSED(exception);
        /* EMPTY */
    }


    virtual void fatalError(const SAXParseException& exception)
    {
        Q_UNUSED(exception);
        /* EMPTY */
    }


    virtual void warning(const SAXParseException& exception)
    {
        Q_UNUSED(exception);
        /* EMPTY */
    }


    //@}

    // -------------------------------------------------------------------

}; // class DefaultHandler

} // namespace qgxml


#endif /* __DEFAULTHANDLER_H_INCLUDED__ */
