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


#ifndef __PBMFILE_H_INCLUDED__
#define __PBMFILE_H_INCLUDED__


/**
 * @file PbmFile.h
 *
 * @brief Header file of class qgar::PbmFile.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Karl Tombre & Gérald Masini</a>
 * @date   Jul, 3  2001  17:11
 * @since  Qgar 1.0
 */


// For RCS/CVS use: Do not delete
/* $Id: PbmFile.h,v 1.18 2006/07/04 13:37:43 masini Exp $ */



// QGAR
#include "AbstractPbmPlusFile.h"
#include "QgarErrorIO.h"



namespace qgar
{

/**
 * @ingroup IO_FILE
 *
 * @class PbmFile PbmFile.h "qgarlib/PbmFile.h"
 *
 * @brief File containing a basic image 
 * (see type qgar::BasicImage) in some PBM format.
 * 
 * For more information about PBM, see the
 * <a href="http://local.wasp.uwa.edu.au/~pbourke/dataformats/ppm/">PPM/PGM/PBM Image Files</a>. 
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Karl Tombre & Gérald Masini</a>
 * @date   Jul, 3  2001  17:11
 * @since  Qgar 1.0
 */
class PbmFile

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
   * @param aFormat   format of the image contained in the file
   *                 (default qgar::QGE_PBM_RAW)
   */
  DLL_EXPORT explicit PbmFile(const char* aFileName, QGEpbm aPbm = QGE_PBM_RAW);

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  DLL_EXPORT virtual ~PbmFile();

  //@}


  /** @name Input */
  //        =====
  //@{

  /**
   * @brief Read the image included in the file and return it.
   *
   * The file is opened in <b>read-only</b> mode at the call,
   * and closed before returning.
   *
   * @exception qgar::QgarErrorIO  bad pixel value
   */
  DLL_EXPORT virtual BinaryImage read();

  //@}


  /** @name Output */
  //        ======
  //@{

  /**
   * @brief Write the given image in the file using the PBM format.
   *
   * The file is opened in <b>write-only</b> mode at the call,
   * and closed before returning.
   * The inital content of the file, if any, is lost.
   *
   * @param anImg  image to be stored in the file
   */
  virtual void write(const BinaryImage& anImg);

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
  static const int s_pbm_header_line_size_;

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
  static const unsigned char s_pbm_magic_plain_;

  /**
   * @brief Character for format <b>RAW</b> in the magic number.
   */
  static const unsigned char s_pbm_magic_raw_;

  //@}


  /** @name Header */
  //        ======
  //@{

  /**
   * @brief Read file header. 
   *
   * @exception qgar::QgarErrorIO  bad magic number
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
  int maxPixel_;

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


}; // class PbmFile


} // namespace qgar 

#endif /* __PBMFILE_H_INCLUDED__ */
