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


#ifndef __QGARERRORDEVELOPER_H_INCLUDED__
#define __QGARERRORDEVELOPER_H_INCLUDED__


/**
 * @file QgarErrorDeveloper.h
 *
 * @brief Header file of class qgar::QgarErrorDeveloper.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gerald Masini">Gerald Masini</a>
 * @date   November 7, 2003  16:16
 * @since  Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QgarErrorDeveloper.h,v 1.12 2007/02/14 17:34:05 masini Exp $ */



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
 * @class QgarErrorDeveloper QgarErrorDeveloper.h "qgarlib/QgarErrorDeveloper.h"
 *
 * @brief Class for Qgar developer exceptions.
 *
 * A developer exception is raised within code being developed:
 * Incomplete or raw implementation, exotic case, bug in an experimental
 * algorithm, etc.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gerald Masini">Gerald Masini</a>
 * @date   November 7, 2003  16:16
 * @since  Qgar 2.1
 */
class QgarErrorDeveloper

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
   * @param aFuncProfile  profile of the function throwing the exception
   */
  explicit QgarErrorDeveloper(const char* aFuncProfile);

  /**
   * @brief Construct and display an error message.
   * @param aFileName     name of the file including the function throwing the exception
   * @param aLineNumber   line number (in the file) of the <b>throw</b> instruction
   * @param aFuncProfile  profile of the function throwing the exception
   * @param aDiagnostic   full explicit diagnostic
   *
   * An error message includes 4 lines:
   * - message header,  displayed by
   *   qgar::AbstractQgarError::displayErrorMessageHeader(const char*)
   * - file name and line number of the corresponding <b>throw</b> instruction
   * - function profile
   * - diagnostic
   */
  QgarErrorDeveloper(const char* aFileName,
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
  virtual ~QgarErrorDeveloper() throw();
  //@}

// -------------------------------------------------------------------
}; // class QgarErrorDeveloper


} // namespace qgar

#endif /* __QGARERRORDEVELOPER_H_INCLUDED__ */
