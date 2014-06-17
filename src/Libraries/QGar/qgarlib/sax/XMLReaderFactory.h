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


#ifndef __XMLREADERFACTORY_H_INCLUDED__
#define __XMLREADERFACTORY_H_INCLUDED__

/**
 * @file     XMLReaderFactory.h
 * @brief    Header file of class qgxml::XMLReaderFactory
 *
 * @author   <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     March 3, 2003  15:34
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: XMLReaderFactory.h,v 1.5 2004/07/02 20:36:43 masini Exp $ */


// QGAR
#include "../qgar.h"

namespace qgxml {

class XMLReader;

/**
 * @class XMLReaderFactory XMLReaderFactory.h "XMLReaderFactory.h"
 * @ingroup XML
 * @brief Factory for creating an XML reader.
 *
 * This class contains static methods for creating an XML reader.
 * 
 * <b> This class is an adaptation for C++ of the interface of the same
 * name implemented in the Java SAX API(http://www.saxproject.org).
 * </b> 
 *
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   March 3, 2003  15:34
 * @since  Qgar 2.1.1
 */
class XMLReaderFactory  {

// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

/**
 * @brief Creates an XMLReader.
 *
 * @return A new XMLReader.
 */
static XMLReader * createXMLReader();

// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

/** @name Constructor */
//        ===========
//@{
/**
 * @brief Default constructor
 */
  XMLReaderFactory();

//@}

// -------------------------------------------------------------------

}; // class XMLReaderFactory

} // namespace qgxml


#endif /* __XMLREADERFACTORY_H_INCLUDED__ */
