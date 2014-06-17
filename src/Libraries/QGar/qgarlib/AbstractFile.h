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


#ifndef __ABSTRACTFILE_H_INCLUDED__
#define __ABSTRACTFILE_H_INCLUDED__


/**
 * @file   AbstractFile.h
 * @brief  Header file of class qgar::AbstractFile.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   Jul 02, 2001  17:13
 * @since  Qgar 1.0
 */


// For RCS/CVS use: Do not delete
/* $Id: AbstractFile.h,v 1.19 2007/02/14 17:34:04 masini Exp $ */



// STD
#include <fstream>
// QGAR
#include "QgarErrorInvalidArg.h"
#include "qgar.h"


namespace qgar
{


// -------------------------------------------------------------------
// T Y P E S   R E L A T E D   T O   F I L E S
// -------------------------------------------------------------------


/** @name Types related to files */
//        ======================
//@{

/**
 * @ingroup IO_FILE
 *
 * @brief File mode.
 */

enum QGEfileMode
{
  QGE_FILE_MODE_CLOSED,      // self-explanatory
  QGE_FILE_MODE_READ_ONLY,   // self-explanatory
  QGE_FILE_MODE_WRITE_ONLY,  // self-explanatory
  QGE_FILE_MODE_APPEND,      // self-explanatory
  QGE_FILE_MODE_READ_WRITE,  // self-explanatory
  QGE_FILE_MODE_READ_APPEND  // self-explanatory
};

//@}


// -------------------------------------------------------------------
// E N D   O F   T Y P E S   R E L A T E D   T O   F I L E S
// -------------------------------------------------------------------




/**
 * @ingroup IO_FILE
 *
 * @class AbstractFile AbstractFile.h "qgarlib/AbstractFile.h"
 *
 * @brief Base class implementing common tools to conveniently
 * define and use files in the Qgar way.
 *
 * @warning
 * This is an abstract class.
 * Pure virtual functions:
 * - qgar::AbstractFile::readHeader
 * - qgar::AbstractFile::writeHeader
 * - qgar::AbstractFile::readFooter
 * - qgar::AbstractFile::writeFooter
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   Jul 02, 2001  17:13
 * @since  Qgar 1.0
 */
class AbstractFile
{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Virtual destructor.
   *
   * Free space allocated to character string representing
   * the name of the file
   */
  virtual ~AbstractFile();

  //@}


  /** @name Access to file characteristics */
  //        ==============================
  //@{

  /**
   * @brief Get file name.
   */
  inline const char* name() const;

  /**
   * @brief Get current file mode.
   */
  inline QGEfileMode mode() const;

  /**
   * @brief Get file stream.
   */
  inline std::fstream& fstream();

  //@}


  /** @name Opening */
  //        =======
  //@{

  /**
   * @brief Open in <b>read-only</b> mode.
   *
   * The file is closed if necessary, and then is open
   * in the required mode.
   *
   * @warning
   * The file pointer is set to the first character of the file.
   *
   * @exception qgar::QgarErrorIO  file cannot be opened
   */
  virtual void openRONLY();

  /**
   * @brief Open in <b>write-only</b> mode.
   *
   * The file is closed if necessary, and then is open
   * in the required mode.
   *
   * @warning
   * If a same-named file exists, its content is lost.
   *
   * @exception qgar::QgarErrorIO  file cannot be opened
   */
  DLL_EXPORT virtual void openWONLY();

  /**
   * @brief Open in <b>append</b> mode.
   *
   * The file is closed if necessary, and then is open
   * in the required mode.
   * The content of the file, if any, is preserved
   * and the file pointer is set to the end of the file.
   *
   * @exception qgar::QgarErrorIO  file cannot be opened
   */
  virtual void openAPPEND();

  /**
   * @brief Open in <b>read-write</b> mode.
   *
   * The file is closed if necessary, and then is open
   * in the required mode.
   *
   * @warning
   * If a same-named file exists, its content is lost.
   *
   * @exception qgar::QgarErrorIO  file cannot be opened
   */
  virtual void openRW();

  /**
   * @brief Open in <b>read-append</b> mode.
   *
   * The file is closed if necessary, and then is open
   * in the required mode.
   * The content of the file, if any, is preserved
   * and the file pointer is set to the end of the file.
   *
   * @exception qgar::QgarErrorIO  file cannot be opened
   */
  virtual void openRA();

  //@}


  /** @name Closing */
  //        =======
  //@{

  /**
   * @brief Close the file.
   *
   * No effect if the file is already closed.
   */
  DLL_EXPORT virtual void close();

  //@}


  /** @name Predicates to check the file mode */
  //        =================================
  //@{

  /**
   * @brief Return <b>true</b> if the file is open
   * in <b>read-only</b>, <b>read-append</b> or <b>read-write</b> mode.
   */
  inline bool isOpenR();

 /**
   * @brief Return <b>true</b> if the file is open
   * in <b>write-only</b>, <b>read-write</b>,
   * <b>append</b>, <b>read-append</b>, mode.
   */
  inline bool isOpenW();

  /**
   * @brief Return <b>true</b> if the file is open
   * in <b>append</b> or <b>read-append</b> mode.
   */
  inline bool isOpenA();

  /**
   * @brief Return <b>true</b> if the file is open
   * in <b>read-only</b> mode.
   */
  inline bool isOpenRONLY();

  /**
   * @brief Return <b>true</b> if the file is open
   * in <b>write-only</b> mode.
   */
  inline bool isOpenWONLY();

  /**
   * @brief Return <b>true</b> if the file is open
   * in <b>read-write</b> mode.
   */
  inline bool isOpenRW();

  /**
   * @brief Return <b>true</b> if the file is open
   * in <b>read-append</b> mode.
   */
  inline bool isOpenRA();

  /**
   * @brief Return <b>true</b> if the file is open
   *   in <b>append</b> mode.
   */
  inline bool isOpenAPPEND();

  /**
   * @brief Return <b>true</b> if the file is closed.
   */
  inline bool isClosed();

  //@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
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
   * @brief Create a file of given name.
   *
   * @param aFileName name of the file
   *
   * @warning The file is closed and must be opened to be used.
   *
   * @exception qgar::QgarErrorInvalidArg  bad file name
   */
  AbstractFile(const char* aFileName);

  //@}


  /** @name Representation of a file */
  //        ========================
  //@{

  /**
   * @brief File name.
   */
  char* name_;

  /**
   * @brief File mode.
   */
  QGEfileMode mode_;

  /**
   * @brief Associated file stream.
   */
  std::fstream fstream_;

  //@}


// -------------------------------------------------------------------

}; // class AbstractFile




// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// I N L I N E    F U N C T I O N S    I M P L E M E N T A T I O N
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII


// ==============================
// ACCESS TO FILE CHARACTERISTICS
// ==============================


// GET FILE NAME

inline
const char*
AbstractFile::name() const
{
  return name_;
}


// GET CURRENT FILE MODE

inline
QGEfileMode
AbstractFile::mode() const
{
  return mode_;
}


// GET FILE STREAM

inline
std::fstream&
AbstractFile::fstream()
{
  return fstream_;
}


// =================================
// PREDICATES TO CHECK THE FILE MODE
// =================================


// READ-ONLY or READ-APPEND or READ-WRITE?

inline bool
AbstractFile::isOpenR()

{
  return
    (mode_ == QGE_FILE_MODE_READ_ONLY) ||
    (mode_ == QGE_FILE_MODE_READ_APPEND) ||
    (mode_ == QGE_FILE_MODE_READ_WRITE);
}


// WRITE-ONLY or READ-WRITE or APPEND or READ-APPEND?

inline bool
AbstractFile::isOpenW()
{
  return
    (mode_ == QGE_FILE_MODE_WRITE_ONLY) ||
    (mode_ == QGE_FILE_MODE_READ_WRITE) ||
    (mode_ == QGE_FILE_MODE_APPEND) ||
    (mode_ == QGE_FILE_MODE_READ_APPEND);
}


// APPEND or READ-APPEND?

inline bool
AbstractFile::isOpenA()
{
  return
    (mode_ == QGE_FILE_MODE_APPEND) ||
    (mode_ == QGE_FILE_MODE_READ_APPEND);
}


// READ-ONLY?

inline bool
AbstractFile::isOpenRONLY()
{
  return (mode_ == QGE_FILE_MODE_READ_ONLY);
}


// WRITE-ONLY?

inline bool
AbstractFile::isOpenWONLY()
{
  return (mode_ == QGE_FILE_MODE_WRITE_ONLY);
}


// READ-WRITE?

inline bool
AbstractFile::isOpenRW()
{
  return (mode_ == QGE_FILE_MODE_READ_WRITE);
}


// READ-APPEND?

inline bool
AbstractFile::isOpenRA()
{
  return (mode_ == QGE_FILE_MODE_READ_APPEND);
}


// APPEND?

inline bool
AbstractFile::isOpenAPPEND()
{
  return (mode_ == QGE_FILE_MODE_APPEND);
}


inline bool
AbstractFile::isClosed()
{
  return (mode_ == QGE_FILE_MODE_CLOSED);
}


// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII


} // namespace qgar


#endif /* __ABSTRACTFILE_H_INCLUDED__ */
