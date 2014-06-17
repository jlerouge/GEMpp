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


#ifndef __QTQGARDTDHANDLERADAPTOR_H_INCLUDED__
#define __QTQGARDTDHANDLERADAPTOR_H_INCLUDED__

/**
 * @file     QtQgarDTDHandlerAdaptor.h
 * @brief    Header file of class QtQgarDTDHandlerAdaptor
 *
 * @author   <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     March 11, 2003  17:31
 * @since    Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QtQgarDTDHandlerAdaptor.h,v 1.3 2004/06/21 16:03:37 rendek Exp $ */


// QGAR
#include "QtStringConverter.h"

// QT
#include <QtXml/qxml.h>

namespace qgxml {

class DTDHandler;

/**
 * @class QtQgarDTDHandlerAdaptor QtQgarDTDHandlerAdaptor.h
 * @brief <BRIEF DESCRIPTION ENDING BY A BLANK LINE>
 * 
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan
 * Rendek">Jan Rendek</a> 
 * @date   March 11, 2003  17:31
 * @since  Qgar 2.1
 */
class QtQgarDTDHandlerAdaptor : public QXmlDTDHandler {

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
  QtQgarDTDHandlerAdaptor(DTDHandler * handler);

//@}


/** @name Destructors */
//        ===========
//@{
/**
 * @brief Destructor
 */
  virtual ~QtQgarDTDHandlerAdaptor();
//@}
  

  virtual bool notationDecl(const QString& name,
			    const QString& publicId,
			    const QString& systemId);

  virtual bool unparsedEntityDecl(const QString& name,
				  const QString& publicId,
				  const QString& systemId,
				  const QString & notationName);
  
  virtual QString errorString() const;



// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  DTDHandler * _impl;
  
  QString _errorMsg;

  QtStringConverter _sc;

// -------------------------------------------------------------------

}; // class QtQgarDTDHandlerAdaptor

} // namespace qgxml


#endif /* __QTQGARDTDHANDLERADAPTOR_H_INCLUDED__ */
