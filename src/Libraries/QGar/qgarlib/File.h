/*---------------------------------------------------------------------+
 | Library QgarLib, graphics analysis and recognition                  |
 | Copyright (C) 2002  Qgar Project, LORIA                             |
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
 | http://www.gnu.org/licenses/lgpl.html for the terms of the licence. |
 | To receive a paper copy, write to the Free Software Foundation,     |
 | Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.       |
 |                                                                     |
 | Contact Project Qgar for any information:                           |
 |   LORIA - équipe Qgar                                               |
 |   B.P. 239, 54506 Vandoeuvre-lès-Nancy Cedex, France                |
 |   email: qgar-contact@loria.fr                                      |
 |   http://www.qgar.org/                                              |
 *---------------------------------------------------------------------*/


#ifndef __FILE_H_INCLUDED__
#define __FILE_H_INCLUDED__


/**
 * @file File.h
 *
 * @brief Header file of class qgar::File.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   Jul, 3  2001  18:00
 * @since  Qgar 1.0
 */

// For RCS/CVS use: Do not delete
/* $Id: File.h,v 1.15 2006/06/23 15:22:13 gerald Exp $ */



// QGAR
#include "AbstractFile.h"



namespace qgar
{

/**
 * @ingroup IO_FILE
 *
 * @class File File.h "qgarlib/File.h"
 *
 * @brief Qgar regular file.
 *
 * To be typically used to save and restore serialized objects.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   Jul, 3  2001  18:00
 * @since  Qgar 1.0
 */
class File

  : public AbstractFile

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  /** @name Constructors */
  //        ============
  //@{

  /**
   * @brief Create a file with given name.
   *
   * @param aFileName name of the file to be created
   *
   * @warning The file is closed and must be opened to be used.
   */
  explicit File(const char* aFileName);

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  virtual ~File();

  //@}


// -------------------------------------------------------------------
}; // class File

} // namespace qgar 


#endif /* __FILE_H_INCLUDED__ */
