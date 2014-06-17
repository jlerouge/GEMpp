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


#ifndef __ABSTRACTPBMPLUS_H_INCLUDED__
#define __ABSTRACTPBMPLUS_H_INCLUDED__


/**
 * @file   AbstractPbmPlusFile.h
 *
 * @brief  Header file of class qgar::AbstractPbmPlusFile.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Karl Tombre & Gérald Masini</a>
 * @date   Jul, 3  2001  16:25
 * @since  Qgar 1.0
 */


// For RCS/CVS use: Do not delete
/* $Id: AbstractPbmPlusFile.h,v 1.16 2006/07/04 13:37:38 masini Exp $ */



// QGAR
#include "AbstractFile.h"
#include "GenImage.h"



namespace qgar
{


// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// T Y P E S   R E L A T E D   T O   P B M   F I L E S
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


/** @name Types related to PBM files */
//        ==========================
//@{

/**
 * @ingroup IO_FILE
 *
 * @brief PBM+ file formats: raw and plain.
 */

enum QGEpbm
{
  QGE_PBM_PLAIN,  // self-explanatory
  QGE_PBM_RAW     // self-explanatory
};

//@}


// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT





/**
 * @ingroup IO_FILE
 *
 * @class AbstractPbmPlusFile AbstractPbmPlusFile.h "qgarlib/AbstractPbmPlusFile.h"
 *
 * @brief File containing a binary or grey-level image
 * in some PBM+ format.
 * 
 *  For more information about PBM, see the
 *  <a href="http://www.bath.ac.uk/BUCS/Software/graphics/pbm/pbm.html">PBMPLUS home page</a>.
 *
 * This is an abstract class. Pure virtual functions:
 * - qgar::AbstractPbmPlusFile::read
 * - qgar::AbstractPbmPlusFile::write
 * - qgar::AbstractPbmPlusFile::readHeader
 * - qgar::AbstractPbmPlusFile::writeHeader
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Karl Tombre & Gérald Masini</a>
 * @date   Jul, 3  2001  16:25
 * @since  Qgar 1.0
 */
class AbstractPbmPlusFile

  : public AbstractFile

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
   */
  virtual ~AbstractPbmPlusFile();

  //@}


  /** @name Access to file characteristics */
  //        ==============================
  //@{

  /**
   * @brief Get the format of the file.
   */
  inline QGEpbm format();

  //@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:


  //  =================================================
  /** @name Constructors
      Constructors belong to the protected section
      so that the class cannot be instantiated by users.
   */
  //  ==================================================
  //@{

  /**
   * @brief Initialize from full data.
   *
   * @param aFileName  name of the new file
   * @param aPbm       format of the image contained in the file (default raw)
   *
   * @exception qgar::QgarErrorInvalidArg  bad image size
   */
  AbstractPbmPlusFile(const char* aFileName,
		      QGEpbm      aPbm = QGE_PBM_RAW);

  //@}


  /** @name Characteristics of a PBM+ file */
  //        ==============================
  //@{

  /**
   * @brief Format of the file.
   */
  QGEpbm format_;

  //@}


  /** @name Header: syntactical features */
  //        ============================
  //@{

  /**
   * @brief Character introducing the magic number.
   */
  static const unsigned char s_pbm_magic_;

  /**
   * @brief Character introducing comments.
   */
  static const unsigned char s_pbm_comment_;

  //@}


  /** @name Header: I/O */
  //        ===========
  //@{

  /**
   * @brief Read header of the file (pure virtual function).
   */
  virtual void readHeader() = 0;

  /**
   * @brief Write header of the file (pure virtual function).
   */
  virtual void writeHeader() = 0;

  //@}


// -------------------------------------------------------------------
}; // class AbstractPbmPlusFile




// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// I N L I N E   F U N C T I O N S   I M P L E M E N T A T I O N 
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII


// ======
// ACCESS
// ======


// GET FILE FORMAT.

inline QGEpbm
AbstractPbmPlusFile::format()
{
  return format_;
}


// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII


} // namespace qgar


#endif /* __ABSTRACTPBMPLUS_H_INCLUDED__ */
