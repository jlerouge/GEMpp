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


#ifndef __PGMFILE_H_INCLUDED__
#define __PGMFILE_H_INCLUDED__


/**
 * @file   PgmFile.h
 *
 * @brief  Header file of class qgar::PgmFile.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Karl Tombre & Gérald Masini</a>
 * @date   July 3,  2001  16:56
 * @since  Qgar 1.0
 */

// For RCS/CVS use: Do not delete
/* $Id: PgmFile.h,v 1.17 2007/02/14 17:34:05 masini Exp $ */



// QGAR
#include "AbstractPbmPlusFile.h"
#include "GenImage.h"



namespace qgar
{

/**
 * @ingroup IO_FILE
 *
 * @class PgmFile PgmFile.h "qgarlib/PgmFile.h"
 *
 * @brief File containing a grey-level image in PGM format.
 *
 * 
 * Such a file includes a header followed by pixel values.
 * The header <b>must</b> conform to the following pattern.
@verbatim
P[2|5]
# First comment line
...
# Last comment line
width height
max_pixel_value
@endverbatim
 * - A line of the header cannot be more than <b>255</b>
 *   (qgar::PbmFile::s_pbm_header_line_size_) characters long.
 * - The first line begins with two characters, a magic
 *   number which gives the format of the file, possibly followed
 *   by any number of space (<b>'&nbsp;'</b>) or tabulation
 *   (<b>'\\t'</b>) characters.
 *   The first magic character is always <b>'P'</b>
 *   (qgar::AbstractPbmPlusFile::s_pbm_format_),
 *   the second is <b>'2'</b> (qgar::PbmFile::s_pgm_magic_plain_)
 *   for a file in <b>plain</b> format,
 *   or <b>'5'</b> (qgar::PbmFile::s_pbm_magic_raw_)
 *   for a file in <b>raw</b> format.
 * - The first line <i>may</i> be followed by an arbitrary number
 *   of comment lines, beginning with character <b>'#'</b>
 *   (qgar::AbstractPbmPlusFile::s_pbm_comment_).
 * - The next line includes two integer numbers, which respectively
 *   give the width and the height of the image stored in the file.
 * - The next line includes an integer number, which gives
 *   the maximum value of a pixel of the image stored in the file.
 *
 * The line following the header contains the pixel values
 * of the image:
 * - In <b>plain</b> format, each pixel is coded by a chain
 *   of characters representing the integer value of the pixel,
 *   which cannot exceed the maximum given by the header.
 *   Values are separated by at least one separator character,
 *   <i>i.e.</i> a space (<b>'&nbsp;'</b>), a tabulation
 *   (<b>'\\t'</b>), a line feed  (<b>'\\n'</b>) or a return
 *   (<b>'\\r'</b>) character.
 * - In <b>raw</b> format, each pixel is represented by a character.
 *   The (integer) numeric value of the character represents
 *   the value of the pixel. Characters are consecutively stored
 *   in the file, without any separator characters between
 *   them.
 *
 *
 * @warning
 * Such a file cannot be opened in <b>append</b>
 * or <b>read-append</b> mode.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Karl Tombre & Gérald Masini</a>
 * @date   Jul, 3  2001  16:25
 * @since  Qgar 1.0
 */
class PgmFile

  : public AbstractPbmPlusFile

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  /** @name Constructors */
  //        ============
  //@{

  /**
   * @brief Initialize from file name and format.
   *
   * @param aFileName name of the new file
   * @param aPbm      format of the image contained in the file
   *                  (default qgar::QGE_PBM_RAW)
   */
  explicit PgmFile(const char* aFileName, QGEpbm aPbm = QGE_PBM_RAW);

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  virtual ~PgmFile();

  //@}


  /** @name Input */
  //        =====
  //@{

  /**
   * @brief Read the grey-level image included in the file,
   * and return it.
   *
   * The file is opened in <b>read-only</b> mode at the call,
   * and closed before returning.
   */
  virtual GreyLevelImage read();

  //@}


  /** @name Output */
  //        ======
  //@{

  /**
   * @brief Write the given grey-level image in the file
   * using a PGM format.
   *
   * The file is opened in <b>write-only</b> mode at the call,
   * and closed before returning.
   * The inital content of the file, if any, is lost.
   *
   * @param anImg  image to be stored in the file
   */
  virtual void write(const GreyLevelImage& anImg);

  //@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /** @name Auxiliary data for I/O */
  //        ======================
  //@{

  /**
   * @brief Maximum length of a line of the file header.
   */
  static const int s_pgm_header_line_size_;

  /**
   * @brief I/O buffer.
   */
  char* inBuf_;

  //@}


  /** @name Magic numbers */
  //        =============
  //@{

  /**
   * @brief Character for format <b>PLAIN</b> in the magic number.
   */
  static const unsigned char s_pgm_magic_plain_;

  /**
   * @brief Character for format <b>RAW</b> in the magic number.
   */
  static const unsigned char s_pgm_magic_raw_;

  //@}


  /** @name Header */
  //        ======
  //@{

  /**
   * @brief Read file header. 
   *
   * @exception qgar::QgarErrorIO  bad magic number
   * @exception qgar::QgarErrorIO  bad max pixel value
   */
  virtual void readHeader();

  /**
   * @brief Write file header.
   */
  virtual void writeHeader();

  //@}


// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:


  /** @name Image features */
  //        ==============
  //@{

  /**
   * @brief Maximum value of a pixel of the current image.
   */
  GreyLevelPixel maxPixel_;

  /**
   * @brief Number of rows of the current image.
   */
  int rowCnt_;

  /**
   * @brief Number of columns of the current image.
   */
  int colCnt_;

  //@}
 

// -------------------------------------------------------------------

}; // class PgmFile


} // namespace qgar


#endif /* __PGMFILE_H_INCLUDED__ */
