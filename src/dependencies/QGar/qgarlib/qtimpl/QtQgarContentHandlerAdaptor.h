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


#ifndef __QTQGARCONTENTHANDLERADAPTOR_H_INCLUDED__
#define __QTQGARCONTENTHANDLERADAPTOR_H_INCLUDED__

/**
 * @file     QtQgarContentHandlerAdaptor.h
 * @brief    Header file of class QtQgarContentHandlerAdaptor
 *
 * @author   <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     March 11, 2003  14:03
 * @since    Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QtQgarContentHandlerAdaptor.h,v 1.3 2004/06/21 16:03:37 rendek Exp $ */


// QT
#include <QtXml/qxml.h>

// QGAR
#include "QtStringConverter.h"


namespace qgxml {

class ContentHandler;
class QtLocatorAdaptor;

/**
 * @class QtQgarContentHandlerAdaptor QtQgarContentHandlerAdaptor.h
 * @brief <BRIEF DESCRIPTION ENDING BY A BLANK LINE>
 * 
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   March 11, 2003  14:03
 * @since  Qgar 2.1
 */
class QtQgarContentHandlerAdaptor : public QXmlContentHandler {

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
 explicit  QtQgarContentHandlerAdaptor(ContentHandler * handler);


//@}


/** @name Destructors */
//        ===========
//@{
/**
 * @brief Destructor
 */
 virtual ~QtQgarContentHandlerAdaptor();
//@}


 virtual bool characters ( const QString & ch );

 virtual bool endDocument();

 virtual bool endElement ( const QString & namespaceURI,
			    const QString & localName, 
			    const QString & qName ); 
  
 virtual bool endPrefixMapping ( const QString & prefix );

 virtual QString errorString() const;

 virtual bool ignorableWhitespace ( const QString & ch );

 virtual void setDocumentLocator ( QXmlLocator * locator );

 virtual bool startDocument();
  
 virtual bool processingInstruction ( const QString & target,
				       const QString & data );
  
 virtual bool skippedEntity ( const QString & name );
  

 virtual bool startElement ( const QString & namespaceURI,
			      const QString & localName, 
			      const QString & qName, 
			      const QXmlAttributes & atts );

 virtual bool startPrefixMapping ( const QString & prefix,
				    const QString & uri );  


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:
  
  ContentHandler * _impl;

  QString _errorMsg;

  QtStringConverter _sc;

  QtLocatorAdaptor * _locatorImpl;
  
// -------------------------------------------------------------------

}; // class QtQgarContentHandlerAdaptor

} // namespace qgxml


#endif /* __QTQGARCONTENTHANDLERADAPTOR_H_INCLUDED__ */
