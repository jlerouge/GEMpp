/*---------------------------------------------------------------------*
 | Library QgarLib, graphics analysis and recognition                  |
 | Copyright (C) 2004  Qgar Project, LORIA                             |
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


#ifndef __ISERIALIZABLE_H_INCLUDED__
#define __ISERIALIZABLE_H_INCLUDED__


/**
 * @file ISerializable.h
 *
 * @brief Header file of class qgar::ISerializable.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   June 28, 2004  14:34
 * @since  Qgar 2.2
 */


// For RCS/CVS use: Do not delete
/* $Id: ISerializable.h,v 1.11 2007/02/14 17:34:05 masini Exp $ */



// STD
#include <iosfwd> // Avoid including classes when not necessary
#include <sstream>
// QGAR
#include "QgarErrorIO.h"




using namespace std;



namespace qgar
{

/**
 * @page serialization Object serialization
 *
 * An object of class <b>Example</b> can be serialized and deserialized using
 * operators '>>' and '<<', on condition that:
 *
 * <ul>
 * <li>
 * <p> Class <b>Example</b> inherits from class <b>ISerializable</b></p>
 * </li>
 *
 * <li>
 * <p>Class <b>Example</b> is provided with appropriate implementations of
 * functions <b>read</b> and <b>write</b>.</p>
 * </li>
 * </ul>
 *
 * Operators '>>' and '<<' also apply to file streams, as <b>ifstream
 * (resp. ifstream)</b> derives from <b>istream (resp. ostream)</b>.
 * 
 * See class qgar::GenQgarSegment for an example.
 * 
 * A serialized object conforms to the following pattern:
@code
  CLASS-NAME(DATA_1) ... (DATA_N)
@endcode
 *
 * The source code of functions <b>read</b> and <b>write</b>, to respectively
 * deserialize and serialize an object of class <b>Example</b>, should typically
 * conform to the following patterns.
 * <b>Warning: Values of data members must be read and written in the same order.</b>
 *
@code
  using namespace std;

  // DESERIALIZATION

  istream&
  Example::read(istream& anInStream)
  {
    qgReadObjName(anInStream, "Example");     // Get class name

    qgReadObjData(anInStream, this->_data_1); // Get first data member
    ...
    qgReadObjData(anInStream, this->_data_N); // Get last data member

    return anInStream;
  }

  // SERIALIZATION
  // data_1() is supposed to be the access function
  // of data member Example::data_1

  ostream&
  Example::write(ostream& anOutStream)
  {
    anOutStream << "Example"
                << '(' << this->_data_1() << ')'  // First data member
                ...
                << '(' << this->_data_N() << ')'; // Last data member

    return anOutStream;
  }
@endcode
 */


// -------------------------------------------------------------------
// D E S E R I A L I Z A T I O N
// -------------------------------------------------------------------


/** 
 * @name Global functions for object deserialization
 * @ingroup IO_SERIAL
 */
//@{

/**
 * @brief Read the name part of an object.
 *
 * @param anIStream  input stream to read from
 * @param aClassName name of the object class
 *
 * @exception qgar::QgarErrorIO  error in input stream
 */
DLL_EXPORT void qgReadObjName(istream& anIStream, const char* aClassName);


/**
 * @brief Read a data member of class <b>T</b>.
 *
 * @param anIStream input stream to read from
 * @param anObject  object to be deserialized
 *
 * @exception qgar::QgarErrorIO  error in input stream
 */
template <class T>
void qgReadObjData(istream& anIStream, T& anObject)



{
  char c;
  do
    {
      anIStream.get(c);
    }
  while (isspace(c));

  if (c != '(')
    {
      anIStream.putback(c);
      throw qgar::QgarErrorIO(__FILE__, __LINE__,
			      "template <class T> void qgar::qgReadObjData(std::istream&, T&)",
			      "Error in input stream: '(' expected.");
    }

  anIStream >> anObject;

  do
    {
      anIStream.get(c);
    }
  while (isspace(c));

  if (c != ')')
    {
      anIStream.putback(c);
      throw qgar::QgarErrorIO(__FILE__, __LINE__,
			      "template <class T> void qgar::qgReadObjData(std::istream&, T&)",
			      "Error in input stream: ')' expected.");
    }
}

//@}

// -------------------------------------------------------------------




/**
 * @ingroup IO_SERIAL
 *
 * @class ISerializable ISerializable.h "qgarlib/ISerializable.h"
 *
 * @brief Base interface of all serializable objects.
 *
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   June 28, 2004  14:34
 * @since  Qgar 2.1.1
 */
class ISerializable
{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  /**
   * @brief Deserializes the current object (from an input stream).
   *
   * @param anInStream  the input stream
   */
  virtual istream& read(istream& anInStream) = 0;


  /**
   * @brief Serializes the current object (to an input stream).
   *
   * @param anOutStream  the output stream
   */
  virtual ostream& write(ostream& anOutStream) const = 0;


/** @name Destructor */
//        ==========
//@{
/**
 * @brief Virtual destructor.
 */
  virtual ~ISerializable() 
  { 
    /* EMPTY */ 
  }
//@}

// -------------------------------------------------------------------
}; // class ISerializable




// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// GLOBAL STREAM OPERATORS TO SERIALIZE/DESERIALIZE OBJECTS
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


/** 
 * @name Stream operators for object serialization/deserialization */
//       =========================================================
//@{

  /**
   * @ingroup IO_SERIAL
   *
   * @brief Reads a serializable object from and input stream.
   *
   * @param anInStream the input stream to read an object from
   * @param aSerial    an object implementing
   *                   the qgar::ISerializable interface
   */
  inline istream& operator>>(istream& anInStream, ISerializable& aSerial)
  {
    return aSerial.read(anInStream);
  }


  /**
   * @ingroup IO_SERIAL
   *
   * @brief Writes a serializable object to an output stream.
   *
   * @param anOutStream  the output stream to write an object to
   * @param aSerial      an object implementing
   *                     the qgar::ISerializable interface
   */
  inline ostream& operator<<(ostream& anOutStream, const ISerializable& aSerial)
  {
    return aSerial.write(anOutStream);
  }

//@}


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


} // namespace qgar


#endif /* __ISERIALIZABLE_H_INCLUDED__ */
