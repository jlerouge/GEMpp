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


#ifndef __ABSTRACTMULTIIMAGE_H_INCLUDED__
#define __ABSTRACTMULTIIMAGE_H_INCLUDED__


/**
 * @file   AbstractMultiImage.h
 * @brief  Header file of class qgar::AbstractMultiImage.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   April 25, 2003  14:43
 * @since  Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: AbstractMultiImage.h,v 1.10 2005/10/14 17:05:45 masini Exp $ */



namespace qgar
{

/**
 * @ingroup DS_IMG
 *
 * @class AbstractMultiImage AbstractMultiImage.h "qgarlib/AbstractMultiImage.h"
 *
 * @brief Root class for classes defining multi-layered images.
 * 
 * Just an empty abstract class to group such classes together in
 * the same subtree of the inheritance hierarchy.
 */
class AbstractMultiImage
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
  virtual ~AbstractMultiImage();

  //@}


  /** @name Access to image characteristics */
  //        ===============================
  //@{

  /**
   * @brief Get the image width.
   */
  inline int width() const;

  /**
   * @brief Get the image height.
   */
  inline int height() const;

  //@}


  /** @name Operators */
  //        =========
  //@{

  /**
   * @brief Assign given image to current image.
   * @param anImg  image to assign to the current image
   */
  AbstractMultiImage& operator=(const AbstractMultiImage& anImg);

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
   * @brief Default constructor: Set <b>0</b> to width and height.
   *
   * The constructor belongs to the protected section
   * so that the class cannot be instantiated.
   */
  AbstractMultiImage();

  /**
   * @brief Copy constructor.
   *
   * @param anImg image to be copied
   */
  AbstractMultiImage(const AbstractMultiImage& anImg);

  /**
   * @brief Initialize with given width and height.
   *
   * @param aWidth   width of the image (in pixels)
   * @param aHeight  height of the image (in pixels)
   */
  AbstractMultiImage(unsigned int aWidth, unsigned int aHeight);

  //@}


  /** @name Representation of an image */
  //        ==========================
  //@{

  /**
   * @brief Width of the image.
   */
  int _width;

  /**
   * @brief Height of the image.
   */
  int _height;

  //@}

// -------------------------------------------------------------------
}; // class AbstractMultiImage



// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// I N L I N E     F U N C T I O N S     I M P L E M E N T A T I O N 
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// ACCESS TO IMAGE CHARACTERISTICS
// ===============================


// GET THE IMAGE WIDTH

inline int
AbstractMultiImage::width() const
{
  return _width;
}


// GET THE IMAGE HEIGHT

inline int
AbstractMultiImage::height() const
{
  return _height;
}


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


} // namespace qgar 


#endif /* __ABSTRACTMULTIIMAGE_H_INCLUDED__ */
