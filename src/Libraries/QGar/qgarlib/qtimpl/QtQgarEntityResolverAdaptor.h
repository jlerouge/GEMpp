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


#ifndef __QTQGARENTITYRESOLVERADAPTOR_H_INCLUDED__
#define __QTQGARENTITYRESOLVERADAPTOR_H_INCLUDED__

/**
 * @file     QtQgarEntityResolverAdaptor.h
 * @brief    Header file of class QtQgarEntityResolverAdaptor
 *
 * @author   <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     March 11, 2003  15:52
 * @since    Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QtQgarEntityResolverAdaptor.h,v 1.3 2004/06/21 16:03:37 rendek Exp $ */


// QGAR
#include "QtStringConverter.h"

// QT
#include <QtXml/qxml.h>


namespace qgxml {

class EntityResolver;

/**
 * @class QtQgarEntityResolverAdaptor QtQgarEntityResolverAdaptor.h
 * @brief <BRIEF DESCRIPTION ENDING BY A BLANK LINE>
 * 
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   March 11, 2003  15:52
 * @since  Qgar 2.1
 *
 */
class QtQgarEntityResolverAdaptor : public QXmlEntityResolver {

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
  QtQgarEntityResolverAdaptor(EntityResolver * res);

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
virtual ~QtQgarEntityResolverAdaptor();

//@}

  virtual bool resolveEntity(const QString & publicId,
			     const QString & systemId, 
			     QXmlInputSource *& ret);
  
  virtual QString errorString() const;



// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  EntityResolver * _impl;

  QString _errorMsg;

  QtStringConverter _sc;

// -------------------------------------------------------------------

}; // class QtQgarEntityResolverAdaptor

} // namespace qgxml


#endif /* __QTQGARENTITYRESOLVERADAPTOR_H_INCLUDED__ */
