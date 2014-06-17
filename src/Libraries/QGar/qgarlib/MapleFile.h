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


#ifndef __MAPLEFILE_H_INCLUDED__
#define __MAPLEFILE_H_INCLUDED__


/**
 * @file MapleFile.h
 *
 * @brief Header file of class qgar::MapleFile.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date   Jul, 3  2001  9:23
 * @since  Qgar 1.0
 */


// For RCS/CVS use: Do not delete
/* $Id: MapleFile.h,v 1.16 2006/06/23 15:22:14 gerald Exp $ */



// QGAR
#include "AbstractFile.h"
#include "GenImage.h"
namespace qgar
{
  // Avoid #include's when not necessary
  class Histogram;
}



namespace qgar
{


/**
 * @ingroup IO_FILE
 *
 * @class MapleFile MapleFile.h "qgarlib/MapleFile.h"
 *
 * @brief File containing a Maple program.
 * 
 * @warning Using default destructor.
 *
 * @todo
 * There is no function to read such a file.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date   Jul, 3  2001  9:23
 * @since  Qgar 1.0
 */
class MapleFile

  : public AbstractFile

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  /** @name Constructors */
  //        ============
  //@{

  /**
   * @brief Initialize from file name.
   *
   * @param aFileName name of the new file
   */
  explicit MapleFile(const char* aFileName);

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  virtual ~MapleFile();

  //@}


  /** @name Output */
  //        ======
  //@{

  /**
   * @brief Write a grey-level image.
   *
   * The file is opened in <b>write-only</b> mode
   * and closed before returning.
   *
   * The code to draw the surface of the grey-level image <b>aGlvmg</b>
   * is stored in the file. The axes of the resulting image are set
   * so that the surface is in the same reference frame as the image
   * when it is displayed. To display the corresponding surface,
   * load the resulting file using Maple command <b>read</b>.
   *
   * @param aGlvImg  a grey-level image
   * @param aRate    sampling rate in the image (default <b>1</b>)
   */
  void write(const GreyLevelImage& aGlvImg, int aRate = 1);

  /** 
   * @brief Write a float image.
   * 
   * The file is opened in <b>write-only</b> mode
   * and closed before returning.
   *
   * The code to draw the surface of the grey-level image <b>aGlvmg</b>
   * is stored in the file. The axes of the resulting image are set
   * so that the surface is in the same reference frame as the image
   * when it is displayed. To display the corresponding surface,
   * load the resulting file using Maple command <b>read</b>.
   *
   * @param aFloatImg  a float image
   * @param aRate      sampling rate in the image (default <b>1</b>)
   */
  void write(const FloatImage& aFloatImg, int aRate = 1);

  /** 
   * @brief Write a histogram.
   *
   * The file is open in <b>write-only</b> mode
   * and closed before returning.
   *
   * The code to draw the histogram as a curve is stored in the file.
   * To display the corresponding surface, load the
   * resulting file using Maple command <b>read</b>.
   *
   * @param aHistogram  a histogram
   */
  void write(Histogram& aHistogram);

  //@}


// -------------------------------------------------------------------
}; // class MapleFile


} // namespace qgar 

#endif /* __MAPLEFILE_H_INCLUDED__ */
