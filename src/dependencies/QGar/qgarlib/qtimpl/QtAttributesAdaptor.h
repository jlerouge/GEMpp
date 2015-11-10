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


#ifndef __QTATTRIBUTESADAPTOR_H_INCLUDED__
#define __QTATTRIBUTESADAPTOR_H_INCLUDED__

/**
 * @file     QTAttributesAdapter.h
 * @brief    Header file of class QTAttributesAdapter
 *
 * @author   <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     March 11, 2003  09:52
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QtAttributesAdaptor.h,v 1.5 2004/06/24 15:07:27 rendek Exp $ */


// QGAR
#include "QtStringConverter.h"
#include "../sax/Attributes.h"


// QT
#include <QtXml/qxml.h>


namespace qgxml {


/**
 * @class QtAttributesAdaptor QTAttributesAdapter.h
 * @brief Adapts the interface of Attributes to the Qt QXmlAttributes
 * class.
 *
 *
 * <p>
 * This class adapts the Qgar SAX Attributes interface to the Qt
 * implementation: QXmlAttributes.
 * </p>
 *
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   March 11, 2003  09:52
 * @since  Qgar 2.1.1
 */
class QtAttributesAdaptor : public Attributes {

// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:


/** @name Constructors */
//        ============
//@{
/**
 * @brief Default constructor
 *
 * @param attributes a pointer to a QXmlAttributes instance to be
 * adapted to the qgxml::Attributes instance.
 */
  QtAttributesAdaptor(QXmlAttributes * attributes);

//@}


/** @name Destructors */
//        ===========
//@{
/**
 * @brief Destructor
 */
  virtual ~QtAttributesAdaptor();
//@}


/** @name Access */
//        ======
//@{

/**
 * @brief Look up the index of an attribute by XML 1.0 qualified
 * name.
 *
 * @param qName The qualified (prefixed) name.
 *
 * @return The index of the attribute., or -1 if it does not appear in
 * the list.
 */
  virtual int getIndex(const std::string& qName) const;
  

/**
 * @brief Look up the index of an attribute by Namespace name.
 *
 * @param uri The Namespace URI, or the empty string if the name has
 * no Namespace URI.
 *
 * @param localName The attribute's local name.
 *
 * @return The index of the attribute, or -1 if it does not appear in
 * the list.
 */
  virtual int getIndex(const std::string& uri,
		       const std::string& localName) const;
  

/**
 * @brief Return the number of attributes in the list.
 * 
 * Once you know the number of attributes, you can iterate through the
 * list.
 *
 * @return The number of attributes in the list.
 */
  virtual int getLength() const;
  


/**
 * @brief Look up an attribute's local name by index.
 *
 * @param index The attribute index (zero-based).
 *
 * @return The local name, or the empty string if Namespace processing
 * is not being performed, or null if the index is out of range.
 */
  virtual std::string getLocalName(int index) const;


/**
 * @brief Look up an attribute's XML 1.0 qualified name by index.
 *
 * @param index The attribute index (zero-based).
 *
 * @return The XML 1.0 qualified name, or the empty string if none is
 * available, or null if the index is out of range.
 */  
  virtual std::string getQName(int index) const;
 
 
/**
 * @brief Look up an attribute's type by index.
 *
 * @param index The attribute index (zero-based).
 *
 * @return The attribute's type as a string.
 */
  virtual std::string getType(int index) const;
  

/**
 * @brief Look up an attribute's type by XML 1.0 qualified name.
 *
 * @param qName The XML 1.0 qualified name.
 *
 * @return The attribute type as a string.
 */
  virtual std::string getType(const std::string& qName) const;
  

/**
 * @brief Look up an attribute's type by Namespace name.
 *
 * @param uri The Namespace URI, or the empty String if the name has
 * no Namespace URI.
 *
 * @param localName The local name of the attribute.
 *
 * @return The attribute type as a string.
 */
  virtual std::string getType(const std::string& uri,
			      const std::string& localName) const;


/**
 * @brief Look up an attribute's Namespace URI by index.
 *
 * @param index The attribute index (zero-based).
 *
 * @return The Namespace URI, or the empty string if none is
 * available.
 */
  virtual std::string getURI(int index) const;


/**
 * @brief Look up an attribute's value by index
 *
 * @param index The attribute index (zero-based).
 *
 * @return The attribute's value as a string, or null if the index is
 * out of range.
 */  
  virtual std::string getValue(int index) const;


/**
 * @brief Look up an attribute's value by XML 1.0 qualified name.
 *
 * @param qName The XML 1.0 qualified name.
 *
 * @return The attribute value as a string, or null if the attribute
 * is not in the list or if qualified names are not available.
 */  
  virtual std::string getValue(const std::string& qName) const;


/**
 * @brief Look up an attribute's value by Namespace name.
 *
 * @param uri The Namespace URI, or the empty String if the name has
 * no Namespace URI.
 *
 * @param localName The local name of the attribute.
 *
 * @return The attribute value as a string, or null if the attribute
 * is not in the list.
 */  
  virtual std::string getValue(const std::string& uri,
			       const std::string& localName) const;
//@}



// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /// The adaptee, a QXmlAttribute instance.
  QXmlAttributes * _impl;
  
  /// A converter used to transform stl string to Qt QString and back.
  QtStringConverter _sc;

// -------------------------------------------------------------------

}; // class QtAttributesAdaptor

} // namespace qgxml

#endif /* __QTATTRIBUTESADAPTOR_H_INCLUDED__ */
