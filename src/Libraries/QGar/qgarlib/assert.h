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


/**
 * @file assert.h
 *
 * @brief Macros to define assertions.
 *
 * This header file refers to the <b>QGARDEBUG</b> macro name,
 * which is not defined in the file. Assertions are therefore compiled
 * into a program either when providing the (preprocessor) option
 * <b>-DQGARDEBUG</b> in the command line invoking the compiler,
 * or when defining <b>QGARDEBUG</b> as a macro name in the source
 * code, before the inclusion of the present header file:
@code
...
#define QGARDEBUG // To be imperatively placed ahead of the #include below
...
...
#include "assert.h"
...
@endcode
 *
 * Assertions are used in a similar way as standard macros <b>assert()</b>
 * (see standard header file <b>assert.h</b>).
 *
 * <ul>
 *
 * <li><p><b>void qgarAssert(int EX)</b>
 * 
 * If <b>EX</b> is <b>false</b>, print a diagnostic
 * message on the standard error output and abort.
 *
 * Execution of a user-defined function may be substituted
 * for abortion: See macro <b>setQgarAssertHandler</b>.
 * </p></li>
 *
 * <li><p><b>void qgarAssertAndEval(EX, EX2)</b>
 *
 * Same as <b>qgarAssert(EX)</b>, but <b>EX2</b> is evaluated
 * before abortion.
 * </p></li>
 *
 * <li><p><b>void qgarAssertAndCatch(EX, EX2)</b>
 *
 * Same as <b>qgarAssertAndEval(EX, EX2)</b>, but does not abort:
 * Execution proceeds sequentially when returning from the macro.
 * </p></li>
 *
 * <li><p><b>void setQgarAssertHandler(void (*HANDLER)(int))</b>
 *
 * Substitute the execution of a user-defined function for abortion
 * in case of assertion failer. The function must conform to the
 * following pattern:
@code
#include "assert.h"

...

void userHandler(int i)
{
  signal(SIGABRT, SIG_IGN);
  ...
  ...  // user-specific code
  ...
  signal(SIGABRT, userHandler);
}
@endcode
 * See macro <b>resetQgarAssertHandler</b>.
 * </p></li>
 *
 * <li><p><b>void resetQgarAssertHandler()</b>
 *
 * Restore abortion in case of assertion failer.
 * See macro <b>setQgarAssertHandler</b>.
 * </p></li>
 *
 * </ul>
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   July 4, 2001  17:07
 * @since  Qgar 1.0
 */


// For RCS/CVS use: Do not delete
/* $Id: assert.h,v 1.5 2007/02/14 17:34:06 masini Exp $ */



// STD
#include <csignal>
#include <iostream>
#include <sys/types.h>



namespace qgar
{


// -------------------------------------------------------------------
// M A C R O S
// -------------------------------------------------------------------


#undef qgarAssert
#undef qgarAssertAndEval
#undef qgarAssertAndCatch
#undef setQgarAssertHandler
#undef resetQgarAssertHandler



#ifdef QGARDEBUG


  /** @name Set user-defined handler for assertion failure */
  //        ==============================================
  //@{

  /**
   * @ingroup GLOB_ASSERT
   *
   * @brief Substitute the execution of a user-defined function
   * for abortion in case of assertion failer.
   *
   * The user-defined function must conform to the following pattern:
@code
#include "assert.h"

...

void userHandler(int i)
{
  signal(SIGABRT, SIG_IGN);
  ...
  ...  // user-specific code
  ...
  signal(SIGABRT, userHandler);
}
@endcode
   * See macro <b>resetQgarAssertHandler</b> to restore abortion
   * in case of assertion failure.
   *
   * @param HANDLER  function to be run in case of assertion failure
   */
  #define setQgarAssertHandler(HANDLER)       \
     if (signal(SIGABRT, HANDLER) == SIG_ERR) \
       {                                      \
          cerr << "setQgarAssertHandler >>> Handler not set: Error by signal()"\
               << endl;                       \
          exit(200);                          \
        }

  /**
   * @ingroup GLOB_ASSERT
   *
   * @brief Restore abortion in case of assertion failure.
   *
   * See macro setQgarAssertHandler.
   */
  #define resetQgarAssertHandler()            \
     if (signal(SIGABRT, SIG_DFL) == SIG_ERR) \
       {                                      \
         cerr << "resetQgarAssertHandler >>> Handler not reset: Error by signal()"\
              << endl;                        \
         exit(200);                           \
       }

  //@}


  #if defined(__STDC__)


  /** @name Set assertions */
  //        ==============
  //@{

  /**
   * @ingroup GLOB_ASSERT
   *
   * @brief Print a diagnostic message if assertion fails.
   *
   * If <b>EX</b> is <b>false</b>, print a diagnostic
   * message on the standard error output and abort.
   * Execution of a user-defined function may be substituted
   * for abortion: See macro setQgarAssertHandler.
   *
   * @param EX  boolean expression
   */
    #define qgarAssert(EX)                             \
       if(!(EX))                                       \
         {                                             \
           __qgPrintAssert(#EX, __FILE__, __LINE__);   \
           kill(GETPID(), SIGABRT);                    \
         }

  /**
   * @ingroup GLOB_ASSERT
   *
   * @brief Same as <b>qgarAssert(EX)</b>,
   *   but <b>EX2</b> is evaluated before abortion.
   *
   * @param EX   boolean expression
   * @param EX2  expression
   */
    #define qgarAssertAndEval(EX,EX2)                  \
       if(!(EX))                                       \
         {                                             \
           __qgPrintAssert(#EX, __FILE__, __LINE__);   \
           EX2;                                        \
           kill(GETPID(), SIGABRT);                    \
         }

  /**
   * @ingroup GLOB_ASSERT
   *
   * @brief Same as <b>qgarAssertAndEval(EX,EX2)</b>, but does not abort:
   * Execution proceeds sequentially when returning from the macro.
   *
   * @param EX   boolean expression
   * @param EX2  expression
   */
    #define qgarAssertAndCatch(EX,EX2)                 \
       if(!(EX))                                       \
         {                                             \
           __qgPrintAssert(#EX, __FILE__, __LINE__);   \
           EX2;                                        \
         }


  #else /* __STDC__ */


    #define qgarAssert(EX)                              \
       if(!(EX))                                        \
          {                                             \
           __qgPrintAssert("EX", __FILE__, __LINE__);   \
           kill(GETPID(), SIGABRT);                     \
         }

    #define qgarAssertAndEval(EX,EX2)                   \
       if(!(EX))                                        \
         {                                              \
           __qgPrintAssert("EX", __FILE__, __LINE__);   \
           EX2;                                         \
           kill(GETPID(), SIGABRT);                     \
         }

    #define qgarAssertAndCatch(EX,EX2)                  \
       if(!(EX))                                        \
         {                                              \
           __qgPrintAssert("EX", __FILE__, __LINE__);   \
           EX2;                                         \
         }

  //@}


  #endif /* __STDC__ */


#else /* QGARDEBUG */


  // QGARDEBUG is not #define'd
  // or preprocessor option -DQGARDEBUG is not set
  // => Ignore assertions

  #define qgarAssert(IGNORE)                  ((void)0)
  #define qgarAssertAndEval(IGNORE1,IGNORE2)  ((void)0)
  #define qgarAssertAndCatch(IGNORE1,IGNORE2) ((void)0)
  #define setQgarAssertHandler(IGNORE)        ((void)0)
  #define resetQgarAssertHandler()            ((void)0)


#endif /* QGARDEBUG */


} // namespace qgar




// Excerpt from <assert.h>:
//
// *******************************************************************
// Note that the ANSI C Standard requires all headers to be idempotent
// except <assert.h> which is explicitly required not to be idempotent
// (section 4.1.2). Therefore, it is by intent that the header guards
// (#ifndef _ASSERT_H) do not span this entire file.
// *******************************************************************
//
// The principle remains true for <qgarAssert.h>:
// Therefore, the header guard  #ifndef __ASSERT_H_INCLUDED__
// does not span the entire file. 





#ifndef __ASSERT_H_INCLUDED__
#define __ASSERT_H_INCLUDED__


namespace qgar
{


// -------------------------------------------------------------------
// G L O B A L    F U N C T I O N S
// -------------------------------------------------------------------


/** 
 * @ingroup GLOB_ASSERT_AUX
 *
 * @brief Print a diagnostic message about failure of an assertion.
 *
 * @param anExpr  assertion
 * @param aFile   name of the source file including the assertion
 * @param aLine   line number of the assertion in the file
 */
extern void __qgPrintAssert(const char* anExpr,
			    const char* aFile,
			    int aLine);


// -------------------------------------------------------------------


} // namespace qgar


#endif /* __ASSERT_H_INCLUDED__ */
