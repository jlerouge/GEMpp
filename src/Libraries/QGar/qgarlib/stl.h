/*---------------------------------------------------------------------*
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


#ifndef __STL_H_INCLUDED__
#define __STL_H_INCLUDED__


/**
 * @file stl.h
 *
 * @brief Extensions to the STL library.
 *
 * They include a set of useful STL-based definitions
 * of structures and functions.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date   September 2, 2002  15:56
 * @since  Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: stl.h,v 1.4 2007/02/14 17:34:06 masini Exp $ */



// STD
#include <functional>



namespace qgar
{


/**
 * @ingroup GLOB_STL
 *
 * @struct qstlDeleteObject stl.h "qgarlib/stl.h"
 *
 * @brief Struct designed to delete objects.
 *
 * This struct is designed to delete objects, handled by a pointer,
 * through STL algorithms. Below is a typical use of this struct:
 * \code
 * #include <list>
 * #include <algorithm>
 * #include "Object.h"
 * #include "stl.h"
 *  
 * list<Object*> myList;
 *
 * ...
 * 
 * // Clean up
 * for_each(myList.begin(), myList.end(), qstlDeleteObject());
 * \endcode
 *
 * For further information, see item #7 in
 * [<a href="Bibliography.html#Meyer-2001">Meyer,&nbsp;2001</a>].
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date   September 2, 2002  15:56
 * @since  Qgar 2.1
 */
struct qstlDeleteObject
{

  /**
   * @brief Deletes an object via a passed pointer.
   *
   * @param ptr  pointer to the object to be deleted
   */
  template<typename T>
  void operator()(const T* ptr) const
  {
    delete ptr;
  }

}; // Struct qstlDeleteObject



/**
 * @ingroup GLOB_STL
 *
 * @struct qstlCloneObject stl.h "qgarlib/stl.h"
 *
 * @brief Struct designed to clone objects.
 *
 * This struct is designed to clone objects, handled by a pointer,
 * through STL algorithms. Below is a typical use of this struct:
 * \code
 * #include <list>
 * #include <algorithm>
 * #include "Object.h"
 * #include "stl.h"
 * 
 * list<Object*> myList;
 * list<Object*> myCopyList;
 *
 * ...
 * 
 * // Make a copy of the list
 * transform(myList.begin(), myList.end(),
 *           back_inserter(myCopyList), qstlCloneObject());
 *
 * \endcode
 *
 * For further information, see
 * [<a href="Bibliography.html#Meyer-2001">Meyer,&nbsp;2001</a>].
 *
 * @author Philippe Dosch (copy)
 * @date   September 2, 2002  15:56
 * @since  Qgar 2.1
 */
struct qstlCloneObject
{

  /**
   * @brief Duplicates a passed object using its copy constructor.
   *
   * @param t   object to be duplicated
   */
  template<typename T>
  T* operator()(const T* t) const
  {
    return new T(*t);
  }

}; // Struct qstlCloneObject



/**
 * @ingroup GLOB_STL
 *
 * @class mem_ptr_fun_t stl.h "qgarlib/stl.h"
 *
 * @brief Adaptor for member functions to a unary_function.
 *
 * <p>
 * qgar::mem_fun_ptr_t is an adaptor for member functions that take one
 * argument. If T is some class with a member Result T::f(Arg) (Result
 * type can be void, and t an instance of T. Then the
 * mem_ptr_fun_t<result, T, Arg> is a valid STL functor that makes
 * possible the call of t->f() as if it was a normal function.
 * </p>
 * <p>
 * If F is a qgar::mem_ptr_fun_t that was constructed to use the member
 * function T::f, and if t a pointer to an instance of T (T*)  and a
 * is a value of type Arg, then the expression F(a) is equivalent to
 * the expression t->f(a). The difference is simply that F can be
 * passed to STL algorithms whose arguments must be function
 * objects.
 * </p>
 * <p>
 * It is usually rather inconvienient to use the constructor of
 * mem_ptr_fun_t directly. It is better to use the helper function
 * qst_mem_ptr_fun instead.
 * </p>
 *
 * @see qgar::qstl_mem_ptr_fun()
 *
 * @author Jan Rendek
 * @date May 28, 2003  16:11
 * @since  Qgar 2.1
 */
template<typename Result, typename X, typename Arg>
class mem_ptr_fun_t

  : public std::unary_function<Arg, Result>

{

public:

  /**
   * @brief Creates an adapter to a unary member function of an
   *   instance of class <b>X</b>.
   *
   * @param inst  instance of which the function member will be called
   * @param ptr   pointer on the function member to be called
   */
  mem_ptr_fun_t(X* inst, Result (X::*ptr)(Arg)) 
    : _inst(inst), _ptr(ptr)
  {
    /* EMPTY */
  }

  /**
   * @brief Executes the unary member function passed on creation and
   *   return the result.
   *
   * @param a  parameter passed to the member function
   */
  Result operator()(Arg a)
  {
    return (_inst->*_ptr)(a);
  }

private:
  /// Pointer to the instance whose member function is to be called.
  X* _inst;
  /// Pointer to the member function to be called.
  Result (X::*_ptr)(Arg);

}; // Class mem_ptr_fun_t



/**
 * @ingroup GLOB_STL
 *
 * @class const_mem_ptr_fun_t stl.h "qgarlib/stl.h"
 *
 * @brief Adaptor for const member functions to a unary_function.
 *
 * <p>
 * mem_fun_ptr_t is an adaptor for const member functions that take
 * one argument. If T is some class with a member Result T::f(Arg)
 * (Result type can be void, and t an instance of T. Then the
 * mem_ptr_fun_t<result, T, Arg> is a valid STL functor that makes
 * possible the call of t->f() as if it was a normal function.
 * </p>
 * <p>
 * If F is a mem_ptr_fun_t that was constructed to use the member
 * function T::f(Arg), and if t a pointer to an instance of T (T*) and
 * a is a value of type Arg, then the expression F(a) is equivalent to
 * the expression t->f(a). The difference is simply that F can be
 * passed to STL algorithms whose arguments must be function
 * objects.
 * </p>
 * <p>
 * It is usually rather inconvienient to use the constructor of
 * mem_ptr_fun_t directly. It is better to use the helper function
 * qst_mem_ptr_fun instead.
 * </p>
 *
 * @see qgar::mem_ptr_fun()
 *
 * @author Jan Rendek
 * @date May 28, 2003  16:11
 * @since  Qgar 2.1
 */
template<typename Result, typename X, typename Arg>
class const_mem_ptr_fun_t

  : public std::unary_function<Arg, Result>

{

public:

  /**
   * @brief Creates an adapter to a unary member function of an
   * instance of class X.
   *
   * @param inst  instance of which the function member will be called
   * @param ptr   pointer on the function member to be called
   */
  const_mem_ptr_fun_t(const X * const inst, Result (X::*ptr)(Arg) const) 
    : _inst(inst), _ptr(ptr)
  {
    /* EMPTY */
  }

  /**
   * @brief Executes the unary member function passed on creation and
   * return the result.
   *
   * @param a   parameter passed to the member function
   */
  Result operator()(Arg a) const
  {
    return (_inst->*_ptr)(a);
  }

private:

  /// Pointer to the instance whose member function is to be called.
  X* _inst;

  /// Pointer to the member function to be called.
  Result (X::*_ptr)(Arg) const;

}; // Class const_mem_ptr_fun_t



/**
 * @class mem_ptr_fun2_t stl.h "qgarlib/stl.h"
 * @ingroup GLOB_STL
 * @brief Adaptor for member functions to a binary_function.
 *
 * <p>
 * mem_fun2_ptr_t is an adaptor for member functions that take two
 * arguments. If T is some class with a member Result T::f(Arg1, Arg2)
 * (Result type can be void), and t an instance of T. Then the
 * mem_ptr_fun2_t<Result, T, Arg1, Arg2> is a valid STL functor that makes
 * possible the call of t->f() as if it was a normal function.
 * </p>
 * <p>
 * If F is a mem_ptr_fun_t that was constructed to use the member
 * function T::f, and if t a pointer to an instance of T (T*)  and a
 * is a value of type Arg, then the expression F(a, b) is equivalent to
 * the expression t->f(a, b). The difference is simply that F can be
 * passed to STL algorithms whose arguments must be function
 * objects.
 * </p>
 * <p>
 * It is usually rather inconvienient to use the constructor of
 * mem_ptr_fun2_t directly. It is better to use the helper function
 * qst_mem_ptr_fun instead.
 * </p>
 *
 * @see qgar::qstl_mem_ptr_fun()
 *
 * @author Jan Rendek
 * @date June 03, 2003  08:41
 * @since  Qgar 2.1
 */
template<typename Result, typename X, typename Arg1, typename Arg2>
class mem_ptr_fun2_t

  : public std::binary_function<Arg1, Arg2, Result>

{

public:

  /**
   * @brief Creates an adapter to a binary member function
   *   of an instance of class <b>X</b>.
   *
   * @param inst  instance of which the function member will be called
   * @param ptr   pointer on the function member to be called
   */
  mem_ptr_fun2_t(X * inst, Result (X::*ptr)(Arg1, Arg2)) 
    : _inst(inst), _ptr(ptr)
  {
    /* EMPTY */
  }

  /**
   * @brief Executes the binary member function passed on creation
   * and return the result.
   *
   * @param a  first parameter passed to the member function
   * @param b  second parameter passed to the member function
   */
  Result operator()(Arg1 a, Arg2 b)
  {
    return (_inst->*_ptr)(a, b);
  }

private:

  /// Pointer to the instance whose member function is to be called.
  X* _inst;

  /// Pointer to the member function to be called.
  Result (X::*_ptr)(Arg1, Arg2);

}; // Class mem_ptr_fun2_t



/**
 * @ingroup GLOB_STL
 *
 * @class const_mem_ptr_fun2_t stl.h "qgarlib/stl.h"
 *
 * @brief Adaptor for member functions to a binary_function.
 *
 * <p>
 * const_mem_fun2_ptr_t is an adaptor for const  member functions 
 * that take two arguments. If T is some class with a member 
 * Result T::f(Arg1, Arg2) (Result type can be void), and t an
 * instance of T. Then the const_mem_ptr_fun2_t<Result, T, Arg1, Arg2>
 * is a valid STL functor that makes  possible the call of t->f() as
 * if it was a normal function.
 * </p>
 * <p>
 * If F is a const_mem_ptr_fun2_t that was constructed to use the member
 * function T::f, and if t a pointer to an instance of T (T*)  and a
 * is a value of type Arg1, b a value of type Arg2, then the
 * expression F(a, b) is equivalent to the expression t->f(a, b). The
 * difference is simply that F can be passed to STL algorithms whose
 * arguments must be function objects.
 * </p>
 * <p>
 * It is usually rather unconvenient to use the constructor of
 * const_mem_ptr_fun2_t directly. It is better to use the helper function
 * qst_mem_ptr_fun instead.
 * </p>
 *
 * @see qgar::qstl_mem_ptr_fun()
 *
 * @author Jan Rendek
 * @date June 03, 2003  08:41
 * @since  Qgar 2.1
 */
template<typename Result, typename X, typename Arg1, typename Arg2>
class const_mem_ptr_fun2_t

  : public std::binary_function<Arg1, Arg2, Result>

{

public:

  /**
   * @brief Creates an adapter to a binary member function
   *   of an instance of class X.
   *
   * @param inst   instance of which the function member will be called
   * @param ptr    pointer on the function member to be called
   */
  const_mem_ptr_fun2_t(X * inst, Result (X::*ptr)(Arg1, Arg2) const) 
    : _inst(inst), _ptr(ptr)
  {
    /* EMPTY */
  }


  /**
   * @brief Executes the binary member function passed on creation
   *   and return the result.
   *
   * @param a   first parameter passed to the member function
   * @param b   second parameter passed to the member function
   */
  Result operator()(Arg1 a, Arg2 b) const
  {
    return (_inst->*_ptr)(a, b);
  }

private:

  /// A pointer to the instance whose member function is to be called.
  X* _inst;

  /// A pointer to the member function to be called.
  Result (X::*_ptr)(Arg1, Arg2) const;

}; // Class const_mem_ptr_fun2_t



/**
 * @ingroup GLOB_STL
 *
 * @brief Adapts a single argument member function
 *   to an  <b>unary_function</b>.
 *
 * @param inst   instance whose function member is to be called
 * @param f      pointer on the function member of inst to call
 *
 * @since  Qgar 2.1
 */
template <typename Result, typename X, typename Arg>
inline mem_ptr_fun_t<Result, X, Arg>
qstl_mem_ptr_fun(X* inst, Result (X::*f)(Arg))
{
  return mem_ptr_fun_t<Result, X, Arg>(inst, f);
}


  
/**
 * @ingroup GLOB_STL
 *
 * @brief Adapts a single argument const member function
 *   to a <b>unary_function</b>.
 *
 * @param inst   instance whose function member is to be called
 * @param f      pointer on the function member of inst to call
 *
 * @since  Qgar 2.1
 */
template <typename Result, typename X, typename Arg>
inline const_mem_ptr_fun_t<Result, X, Arg>
qstl_mem_ptr_fun(X* inst, Result (X::*f)(Arg) const)
{
  return const_mem_ptr_fun_t<Result, X, Arg>(inst, f);
}



/**
 * @ingroup GLOB_STL
 *
 * @brief Adapts a two arguments member function
 *   to a <b>binary_function</b>.
 *
 * @param inst  instance whose function member is to be called
 * @param f     pointer on the function member of inst to call
 *
 * @since  Qgar 2.1
 */
template <typename Result, typename X, typename Arg1, typename Arg2>
inline mem_ptr_fun2_t<Result, X, Arg1, Arg2>
qstl_mem_ptr_fun(X* inst, Result (X::*f)(Arg1, Arg2))
{
  return mem_ptr_fun2_t<Result, X, Arg1, Arg2>(inst, f);
}



/**
 * @ingroup GLOB_STL
 *
 * @brief Adapts a two arguments member function
 *   to a <b>binary_function</b>.
 *
 * @param inst  instance whose function member is to be called
 * @param f     pointer on the function member of inst to call
 *
 * @since  Qgar 2.1
 */
template <typename Result, typename X, typename Arg1, typename Arg2>
inline const_mem_ptr_fun2_t<Result, X, Arg1, Arg2>
qstl_mem_ptr_fun(X* inst, Result (X::*f)(Arg1, Arg2) const)
{
  return const_mem_ptr_fun2_t<Result, X, Arg1, Arg2>(inst, f);
}



} // namespace qgar


#endif /* __STL_H_INCLUDED__ */
