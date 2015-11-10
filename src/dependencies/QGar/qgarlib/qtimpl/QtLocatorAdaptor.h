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


#ifndef __QTLOCATORADAPTOR_H_INCLUDED__
#define __QTLOCATORADAPTOR_H_INCLUDED__

/**
 * @file     QtLocatorAdaptor.h
 * @brief    Header file of class QtLocatorAdaptor
 *
 * @author   <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     March 10, 2003  17:46
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QtLocatorAdaptor.h,v 1.5 2004/06/24 15:07:27 rendek Exp $ */


// QGAR
#include "../sax/Locator.h"

// QT
#include <QtXml/qxml.h>

namespace qgxml {


/**
 * @class QtLocatorAdaptor QtLocatorAdaptor.h
 * @brief Adapts the interface of Locator to the Qt QXmlLocator
 * 
 * <p>
 * This class adapts the Qgar SAX Locator interface to the Qt
 * implementation: QXmlLocator.
 * </p>
 *
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   March 10, 2003  17:46
 * @since  Qgar 2.1.1
 */
class QtLocatorAdaptor : public Locator {

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
  QtLocatorAdaptor(QXmlLocator * locator);

//@}


/** @name Destructors */
//        ===========
//@{

/**
 * @brief Destructor
 */
  virtual ~QtLocatorAdaptor();

//@}


/** @name Access */
//        ======
//@{

  virtual int getColumnNumber() const;

  virtual int getLineNumber() const;

  virtual std::string getPublicId() const;

  virtual std::string getSystemId() const;

//@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  QXmlLocator * _impl;


// -------------------------------------------------------------------

}; // class QtLocatorAdaptor

} // namespace qgxml


#endif /* __QTLOCATORADAPTOR_H_INCLUDED__ */
