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


#ifndef __INPUTSOURCE_H_INCLUDED__
#define __INPUTSOURCE_H_INCLUDED__


/**
 * @file     InputSource.h
 * @brief    Header file of class qgxml::InputSource
 *
 * @author   <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     March 12, 2003  10:00
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: InputSource.h,v 1.5 2004/07/02 20:36:43 masini Exp $ */


#include <istream>
#include <string>

#include "../qgar.h"

namespace qgxml {


/**
 * @class InputSource InputSource.h "InputSource.h"
 * @ingroup XML
 * @brief A single input source for an XML entity.
 * 
 * This class allows a SAX application to encapsulate information
 * about an input source in a single object, which may include a
 * public identifier, a system identifier, and/or a byte stream.
 * 
 * <b> This class is an adaptation for C++ of the interface of the same
 * name implemented in the Java SAX API (http://www.saxproject.org).
 * </b>
 * 
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a> (Adaptation)
 * @date   March 12, 2003  10:00
 * @since  Qgar 2.1.1
 */
class InputSource {

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
  InputSource() : _byteStream(0) 
  { /* EMPTY */ }


/**
 * @brief Create a new input source from an input stream
 *
 * @param byteStream The raw byte stream containing the document.
 */  
  InputSource(std::istream& byteStream)  
    : _byteStream(&byteStream)
  { /* EMPTY */ }


/**
 * @brief Create a new input source with a system identifier.
 *
 * @param systemId The system identifier (URI).
 */  
  InputSource(const std::string& systemId)
    : _byteStream(0), _systemId(systemId)
  { /* EMPTY */ }

 
/**
 * @brief Copy-constructor
 */
  InputSource(const InputSource& rhs) 
    :  _byteStream(rhs._byteStream), 
       _systemId(rhs._systemId), 
       _publicId(rhs._publicId),
       _encoding(rhs._encoding)
  { /* EMPTY */ }

//@}


/** @name Destructor */
//        ==========
//@{

/**
 * @brief Destructor
 */
  virtual ~InputSource() 
  { /* EMPTY */ }

//@}


/** @name Access */
//        ======
//@{

/**
 * @brief Get the byte stream for this input source.
 *
 * @return The byte stream, or null if none was supplied.
 */
  virtual std::istream* getByteStream() 
  { return _byteStream; }


/**
 * @brief Get the character encoding for a byte stream or URI.
 *
 * @return The encoding.
 */
  virtual std::string getEncoding() 
  { return _encoding; }

/**
 * @brief Get the public identifier for this input source.
 *
 * @return The public identifier, or an empty string if none was supplied.
 */
  virtual std::string getPublicId()
  { return _publicId; }
    
/**
 * @brief Get the system identifier for this input source.
 *
 * @return The system identifier, or an empty string if none was
 *         supplied.
 */
  virtual std::string getSystemId()
  { return _systemId; }


//@}


/** @name Transformation */
//        ==============
//@{

/**
 * @brief Set the byte stream for this input source.
 *
 * @param byteStream An std::inputstream containing an XML document or
 *                   other entity.
 */
  virtual void setByteStream(std::istream& byteStream)
  { _byteStream = &byteStream; }

/**
 * @brief Set the character encoding, if known.
 *
 * @param encoding A string describing the character encoding.
 */
  virtual void setEncoding(const std::string& encoding)
  { _encoding = encoding; }

/**
 * @brief Set the public identifier for this input source.
 *
 * @param publicId The public identifier as a string.
 */
  virtual void setPublicId(const std::string& publicId)
  { _publicId = publicId; }
  
/**
 * @brief Set the system identifier for this input source.
 *
 * @param systemId The system identifier as a string.
 */
  virtual void setSystemId(const std::string& systemId)
  { _systemId = systemId; }
  
//@}


/** @name Operators */
//        =========
//@{
/**
 * @brief Assignment operator
 */
InputSource& operator=(const InputSource& rhs)
{
  if (this != &rhs) {
    _byteStream = rhs._byteStream;
    
    _systemId = rhs._systemId;
    _publicId = rhs._publicId;
    _encoding = rhs._encoding;
  }

  return *this;
}
//@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /// The input stream the input source gets its data from.
  std::istream * _byteStream;

  /// The system ID of this input source, empty if unknown.
  std::string _systemId;

  /// The public TD of this input source, empty if unknown.
  std::string _publicId;

  /// The encoding of this input source, empty if unknown.
  std::string _encoding;


// -------------------------------------------------------------------

}; // class InputSource

} // namespace qgxml


#endif /* __INPUTSOURCE_H_INCLUDED__ */
