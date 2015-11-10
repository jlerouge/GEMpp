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


#ifndef __QIODEVICEADAPTOR_H_INCLUDED__
#define __QIODEVICEADAPTOR_H_INCLUDED__

/**
 * @file     QIODeviceAdaptor.h
 * @brief    Header file of class QIODeviceAdaptor
 *
 * @author   <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date     March 14, 2003  15:27
 * @since    Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QIODeviceAdaptor.h,v 1.3 2004/06/24 15:07:27 rendek Exp $ */

#include "../qgar.h"

#include <QIODevice>
#include <istream>

namespace qgxml {

/**
 * @class QIODeviceAdaptor QIODeviceAdaptor.h
 * @brief Adapts the interface of Qt QIODevice to std::istream.
 *
 * 
 * <p>
 * This class adapts a standard input stream (std::istream) into a valid Qt
 * QIODevice. All function calls performed on an instance of this class are
 * transformed into calls to the istream data member. Although this
 * class extends QIODevice, it implements only a <strong>sequential
 * input stream</strong>
 * </p>
 * <p>
 * For compatibility reasons with the parent class QIODevice, this
 * class implements some inherited function members that are not
 * relevant for  a sequential output stream. These members are:
 * - size()
 * - writeBlock()
 * - putch()
 *
 * Any attempt to use these function members will raise a
 * std::runtime_error exception.
 * </p>
 *
 * @author <a href="mailto:qgar-contact@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a> 
 * @date   March 14, 2003  15:27
 * @since  Qgar 2.1.1
 */
class QIODeviceAdaptor : public QIODevice {

// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:


/** @name Constructors */
//        ============
//@{
/**
 * @brief Default constructor
 *
 * <p>
 * Create an adaptor redirecting class to a QIODevice instance to a
 * istream instance. This QIODevice should be used only as a
 * sequential input device.
 * </p>
 * <p>
 * The QIODevice flags set at the creation are: 
 * - IO_ReadOnly 
 * - IO_Sequential 
 * - IO_Open;
 * </p>
 *
 * @param stream The stream to which all calls will be redirected to.
 */
explicit QIODeviceAdaptor(std::istream * stream);
//@}


/** @name Destructors */
//        ===========
//@{
/**
 * @brief Destructor
 */
  virtual ~QIODeviceAdaptor();
//@}


/**
 * @brief Open the I/O device using a specified mode.
 *
 * <p>
 * This function is provided for compatibility purpose only. The
 * stream is declared opened at creation time (see QIODeviceAdatptor)
 * and will remain this way until destroyed. Thus this function member
 * returns always true.
 * </p>
 *
 * @return always true
 */
  virtual bool open(QIODevice::OpenMode mode);


/**
 * @brief Closes the device.
 */
  virtual void close();


/**
 * @brief flushes an open iodevice
 *
 */
  virtual void flush();

/**
 * @brief Reads a block of data from the stream. 
 *
 * Reads at most maxlen bytes from the I/O device into data and
 * returns the number of bytes actually read.
 *
 * @param data a pointer on a free memory space where to store the
 * read data. This space must be big enough to hold up to maxlen
 * bytes.
 *
 * @param maxlen The maximum number of bytes to be read from the
 * device.
 * 
 * @return the number of bytes actually read.
 */
  virtual qint64 readData(char * data, qint64 maxlen);


/**
 * @brief Writes a block of data to the stream
 *
 * @return nothing since any call to this function member will raise an
 * exception.
 *
 * @warning Method redefined for compatibility purpose only. Calling
 * it will raise an error.
 *
 * @throw std::runtime_error whenever this function member is called.
 */
  virtual qint64 writeData(const char * data, qint64 len);


/**
 * @brief reads a single byte from the stream.
 *
 * @return the byte read cast into an int.
 */
  virtual bool getChar(char * c);

// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

/**
 * @brief The input stream implementing this IODevice.
 *
 * This data member is the 'real' implementation of the
 * IODevice. Every calls to a function member of this class is
 * translated and redirected to it.
 */
  std::istream * _stream;


// -------------------------------------------------------------------

}; // class QIODeviceAdaptor

} // namespace qgxml


#endif /* __QIODEVICEADAPTOR_H_INCLUDED__ */
