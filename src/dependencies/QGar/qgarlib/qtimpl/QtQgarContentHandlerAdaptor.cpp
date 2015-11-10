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


/**
 * @file  QtQgarContentHandlerAdaptor.cpp
 * @brief Implementation of class QtQgarContentHandlerAdaptor
 *
 *        See file QtQgarContentHandlerAdaptor.h for the interface.
 *
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   March 11, 2003  14:03
 * @since  Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QtQgarContentHandlerAdaptor.cpp,v 1.4 2004/07/01 22:19:21 masini Exp $ */


#include "QtQgarContentHandlerAdaptor.h"

// QGAR
#include "QtAttributesAdaptor.h"
#include "QtLocatorAdaptor.h"
#include "../sax/ContentHandler.h"
#include "../sax/SAXException.h"



using namespace std;

namespace qgxml {


// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

QtQgarContentHandlerAdaptor::QtQgarContentHandlerAdaptor(ContentHandler
							 * handler)
{
  _impl = handler;
  _locatorImpl = 0;
}



// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------

QtQgarContentHandlerAdaptor::~QtQgarContentHandlerAdaptor()
{
  delete _locatorImpl;
}



// ---------------------------------------------------------------------
// O T H E R
// ---------------------------------------------------------------------

bool 
QtQgarContentHandlerAdaptor::characters(const QString & ch)
{
  bool retval = true;

  try {

    _impl->characters(_sc(ch).c_str(), 0, ch.length());
  }
  catch(SAXException& e) {
    retval = false;
    _errorMsg = e.getMessage();
  }

  return retval;
}

// ---------------------------------------------------------------------

bool
QtQgarContentHandlerAdaptor::endDocument()
{
  bool retval = true;

  try {

    _impl->endDocument();
  }
  catch(SAXException& e) {

    retval = false;
    _errorMsg = e.getMessage();
  }

  return retval;
}

// ---------------------------------------------------------------------

bool 
QtQgarContentHandlerAdaptor::endElement ( const QString & namespaceURI, 
					  const QString & localName, 
					  const QString & qName ) 
{
  bool retval = true;

  try {

    _impl->endElement(_sc(namespaceURI), _sc(localName), _sc(qName));
  }
   catch(SAXException& e) {
     retval = false;
     _errorMsg = e.getMessage();
   }

  return retval;
}
  
// ---------------------------------------------------------------------

bool 
QtQgarContentHandlerAdaptor::endPrefixMapping (const QString & prefix)
{
  bool retval = true;

  try {

    _impl->endPrefixMapping(_sc(prefix));
  }
  catch(SAXException& e) {
    retval = false;
    _errorMsg = e.getMessage();
  }

  return retval;
}

// ---------------------------------------------------------------------

QString 
QtQgarContentHandlerAdaptor::errorString() const
{
  return _errorMsg;
}

// ---------------------------------------------------------------------

bool 
QtQgarContentHandlerAdaptor::ignorableWhitespace ( const QString & ch )
{
  bool retval = true;

  try {
    
    _impl->ignorableWhitespace(_sc(ch).c_str(), 0, ch.length());
  }
  catch(SAXException& e) {
    retval = false;
    _errorMsg = e.getMessage();
  }

  return retval;
}

// ---------------------------------------------------------------------

void 
QtQgarContentHandlerAdaptor::setDocumentLocator (QXmlLocator * locator)
{
  
  //-- Update the locator adaptor.

  delete _locatorImpl;
  _locatorImpl = new QtLocatorAdaptor(locator);
  

  //-- Delegate to the adaptee.

  _impl->setDocumentLocator(_locatorImpl);
}

// ---------------------------------------------------------------------

bool 
QtQgarContentHandlerAdaptor::startDocument()
{
  bool retval = true;

  try {

    _impl->startDocument();
  }
  catch(SAXException& e) {
    retval = false;
    _errorMsg = e.getMessage();
  }

  return retval;
}
  
// ---------------------------------------------------------------------

bool 
QtQgarContentHandlerAdaptor::processingInstruction ( const QString & target, 
						     const QString & data )
{
  bool retval = true;

  try {

    _impl->processingInstruction(_sc(target), _sc(data));
  }
  catch(SAXException& e) {
    retval = false;
    _errorMsg = e.getMessage();
  }

  return retval;
}
  
// ---------------------------------------------------------------------

bool 
QtQgarContentHandlerAdaptor::skippedEntity (const QString & name)  
{
  bool retval = true;

  try {

    _impl->skippedEntity(_sc(name));
  }
  catch(SAXException& e) {
    retval = false;
    _errorMsg = e.getMessage();
  }

  return retval;
}

// ---------------------------------------------------------------------
bool 
QtQgarContentHandlerAdaptor::startElement (const QString & namespaceURI,
					   const QString & localName, 
					   const QString & qName, 
					   const QXmlAttributes& atts)
{
  bool retval = true;

  try {
    _impl->startElement(_sc(namespaceURI),
 			_sc(localName),
   			_sc(qName),
			QtAttributesAdaptor(const_cast<QXmlAttributes *>(&atts)));
  }
  catch(SAXException& e) {
     retval = false;
     _errorMsg = e.getMessage();
  }

  return retval;
}

// ---------------------------------------------------------------------

bool 
QtQgarContentHandlerAdaptor::startPrefixMapping ( const QString & prefix, 
						  const QString & uri )  
{
  bool retval = true;

  try {

    _impl->startPrefixMapping(_sc(prefix), _sc(uri));
  }
  catch(SAXException& e) {
    retval = false;
    _errorMsg = e.getMessage();
  }

  return retval;
}

// ----------------------------------------------------------------------

} // namespace qgxml
