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


#ifndef __QGARERRORUSER_H_INCLUDED__
#define __QGARERRORUSER_H_INCLUDED__


/**
 * @file QgarErrorUser.h
 *
 * @brief Header file of class qgar::QgarErrorUser.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gerald Masini">Gerald Masini</a>
 * @date   November 12, 2003  16:02
 * @since  Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QgarErrorUser.h,v 1.11 2007/02/14 17:34:05 masini Exp $ */



// STD
#include <cstring>
#include <stdexcept>
// QGAR
#include "AbstractQgarError.h"



using namespace std;



namespace qgar
{


/**
 * @ingroup ERROR
 *
 * @class rQgarErrorUser QgarErrorUser.h "qgarlib/QgarErrorUser.h"
 *
 * @brief Class for Qgar user exceptions.
 *
 * A user exception is raised because of programming errors:
 * Index out of range, file opened in a wrong mode, etc.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gerald Masini">Gerald Masini</a>
 * @date   November 12, 2003  16:02
 * @since  Qgar 2.1
 */
class QgarErrorUser

  : public logic_error,
    public AbstractQgarError

{
// -------------------------------------------------------------------
// P U B L I C   M E M B E R S
// -------------------------------------------------------------------
public:

  /** @name Constructors */
  //        ============
  //@{

  /**
   * @brief Construct from the profile of the function throwing
   *        the exception, without displaying any error message.
   *
   * @param aFuncProfile  profile of the function throwing the exception
   */
  explicit QgarErrorUser(const char* aFuncProfile);

  /**
   * @brief Construct and display an error message.
   *
   * An error message includes 4 lines:
   * - message header,  displayed by
   *   qgar::AbstractQgarError::displayErrorMessageHeader(const char*)
   * - file name and line number of the corresponding <b>throw</b> instruction
   * - function profile
   * - diagnostic
   *
   * @param aFileName     name of the file including the function throwing the exception
   * @param aLineNumber   line number (in the file) of the <b>throw</b> instruction
   * @param aFuncProfile  profile of the function throwing the exception
   * @param aDiagnostic   full explicit diagnostic
   */
  QgarErrorUser(const char* aFileName,
        int aLineNumber,
        const char* aFuncProfile,
        const string aDiagnostic);

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  virtual ~QgarErrorUser() throw();

  //@}

// -------------------------------------------------------------------
}; // class QgarErrorUser


} // namespace qgar


#endif /* __QGARERRORUSER_H_INCLUDED__ */
