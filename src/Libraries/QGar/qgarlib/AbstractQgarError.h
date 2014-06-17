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


#ifndef __ABSTRACTQGARERROR_H_INCLUDED__
#define __ABSTRACTQGARERROR_H_INCLUDED__


/**
 * @file AbstractQgarError.h
 *
 * @brief Header file of class qgar::AbstractQgarError.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gerald Masini">Gerald Masini</a>
 * @date   November 6, 2003  18:18
 * @since  Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: AbstractQgarError.h,v 1.15 2007/02/14 17:34:04 masini Exp $ */



// STD
#include <cstring>

#include "qgar.h"

using namespace std;

namespace qgar
{

/**
 * @ingroup ERROR
 *
 * @class AbstractQgarError AbstractQgarError.h "qgarlib/AbstractQgarError.h"
 *
 * @brief Base class for Qgar exceptions.
 * 
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gerald Masini">Gerald Masini</a>
 * @date   November 6, 2003  18:18
 * @since  Qgar 2.1
 */
class AbstractQgarError
{
// -------------------------------------------------------------------
// P U B L I C   M E M B E R S
// -------------------------------------------------------------------
public:

  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  DLL_EXPORT virtual ~AbstractQgarError();

  //@}


  /** @name Display */
  //        =======
  //@{

  /**
   * @brief Display the error message header (first line of the message),
   * including an explicit description (in capital letters)
   * of the error type.
   *
   * @param anErrorKind  explicit description of the error type
   */
  DLL_EXPORT virtual void displayHeader(const char* anErrorKind) const;

  /**
   * @brief Enable the display of error messages
   *   when exceptions are raised.
   *
   * @warning This is a static function.
   */
  static void errorMsgOn();

  /**
   * @brief Disable the display of error messages
   *   when exceptions are raised.
   *
   * @warning This is a static function.
   */
  static void errorMsgOff();

  //@}

// -------------------------------------------------------------------
// P R O T E C T E D   M E M B E R S
// -------------------------------------------------------------------
protected:
  
  //  ============================================
  /** @name Constructors
      Constructors belong to the protected section
      so that the class cannot be instantiated.
   */
  //  ============================================
  //@{

  /**
   * @brief Construct without displaying any error message.
   *
   * @param aFuncProfile  profile of the function throwing the exception
   */
  AbstractQgarError(const char* aFuncProfile);

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
   * @param anErrorKind   explicit description (in capital letters) of the error type
   * @param aFileName     name of the file including the function throwing the exception
   * @param aLineNumber   line number (in the file) of the <b>throw</b> instruction
   * @param aFuncProfile  profile of the function throwing the exception
   * @param aDiagnostic   full explicit diagnostic
   */
  AbstractQgarError(const char* anErrorKind,
		    const char* aFileName,
		    int aLineNumber,
		    const char* aFuncProfile,
		    const string aDiagnostic);
  //@}

  /** @name Messages */
  //        ========
  //@{

  /**
   * @brief Display flag for error messages.
   *
   * When <b>true</b> (which is the default), an error message
   * is displayed when a Qgar exception is raised.
   */
  static bool msgFlag_;

  //@}

// -------------------------------------------------------------------
}; // class AbstractQgarError


} // namespace qgar


#endif /* __ABSTRACTQGARERROR_H_INCLUDED__ */
