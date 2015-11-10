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


#ifndef __QTQGARERRORHANDLERADAPTOR_H_INCLUDED__
#define __QTQGARERRORHANDLERADAPTOR_H_INCLUDED__

/**
 * @file     QtQgarErrorHandlerAdaptor.h
 * @brief    Header file of class QtQgarErrorHandlerAdaptor
 *
 * @author   <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     March 11, 2003  15:03
 * @since    Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QtQgarErrorHandlerAdaptor.h,v 1.2 2004/06/21 16:03:37 rendek Exp $ */



// QT
#include <QtXml/qxml.h>

#include "QtStringConverter.h"

namespace qgxml {

class ErrorHandler;

/**
 * @class QtQgarErrorHandlerAdaptor QtQgarErrorHandlerAdaptor.h
 * @brief <BRIEF DESCRIPTION ENDING BY A BLANK LINE>
 * 
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan
 * Rendek">Jan Rendek</a> 
 * @date   March 11, 2003  15:03
 * @since  Qgar 2.1
 */
class QtQgarErrorHandlerAdaptor : public QXmlErrorHandler {

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
  QtQgarErrorHandlerAdaptor(ErrorHandler * handler);

//@}


/** @name Destructor */
//        ==========
//@{
/**
 * @brief Destructor
 */
  virtual ~QtQgarErrorHandlerAdaptor();

//@}

  
  virtual bool error(const QXmlParseException & exception );
  
  virtual bool fatalError(const QXmlParseException & exception);
  
  virtual bool warning(const QXmlParseException & exception );

  virtual QString errorString() const;
  


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  ErrorHandler * _impl;

  QString _errorMsg;

  QtStringConverter _sc;

// -------------------------------------------------------------------

}; // class QtQgarErrorHandlerAdaptor

} // namespace qgxml


#endif /* __QTQGARERRORHANDLERADAPTOR_H_INCLUDED__ */
