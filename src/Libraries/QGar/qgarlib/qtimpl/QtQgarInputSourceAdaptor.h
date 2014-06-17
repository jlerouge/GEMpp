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


#ifndef __QTQGARINPUTSOURCEADAPTOR_H_INCLUDED__
#define __QTQGARINPUTSOURCEADAPTOR_H_INCLUDED__

/**
 * @file     QtQgarInputSourceAdaptor.h
 * @brief    Header file of class QtQgarInputSourceAdaptor
 *
 * @author   <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     March 17, 2003  13:23
 * @since    Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id */

// QGAR
#include "QIODeviceAdaptor.h"
#include "../sax/InputSource.h"


// QT
#include <QtXml/qxml.h>

namespace qgxml
{


/**
 * @class QtQgarInputSourceAdaptor QtQgarInputSourceAdaptor.h
 * @brief <BRIEF DESCRIPTION ENDING BY A BLANK LINE>
 * 
 * <DETAILED DESCRIPTION ENDING BY A BLANK LINE>
 * 
 * @warning <COMMENTS DESERVING SPECIAL ATTENTION.
 *           IMPERATIVELY DELETE THESE LINES WHEN USELESS>
 * 
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   March 17, 2003  13:23
 * @since  Qgar 2.1
 */
class QtQgarInputSourceAdaptor : public QXmlInputSource {

// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:


/** @name Constructor */
//        ===========
//@{
  QtQgarInputSourceAdaptor(InputSource * source) :
    QXmlInputSource(_io = new QIODeviceAdaptor(source->getByteStream()))
  { }
//@}


/** @name Destructor */
//        ==========
//@{

  virtual ~QtQgarInputSourceAdaptor()
  { /* NOP */ }
  
//@}

protected:
  
  QIODeviceAdaptor * _io;

// -------------------------------------------------------------------

}; // class QtQgarInputSourceAdaptor

} // namespace qgxml


#endif /* __QTQGARINPUTSOURCEADAPTOR_H_INCLUDED__ */

