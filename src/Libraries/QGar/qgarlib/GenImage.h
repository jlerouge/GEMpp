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


#ifndef __GENIMAGE_H_INCLUDED__
#define __GENIMAGE_H_INCLUDED__

/**
 * @file   GenImage.h
 * @brief  Header file of class qgar::GenImage.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   March 4, 2003  14:09
 * @since  Qgar 2.1
 */


// For RCS/CVS use: Do not delete
/* $Id: GenImage.h,v 1.47 2007/02/28 15:51:00 vasconcv Exp $ */


// STD
#include <sstream>
// QGAR
#include "BoundingBox.h"
#include "image.h"
#include "primitives.h"
#include "QgarErrorDomain.h"
#include "QgarErrorInvalidArg.h"
#include <QtCore>


using namespace std;


// _____________________________________________________________________
//
// WARNING: The following comment represents the documentation of
// namespace qgar. If the class is removed or altered, this comment
// must be moved to another QgarLib class file (.h).
// _____________________________________________________________________
//
/**
 * @brief Namespace of the QgarLib library.
 *
 * All classes, types, globals, etc. of the Qgar library are defined
 * in this namespace.
 */
namespace qgar
{



    /*---------------------------------------------------------------------+
 |                                                                     |
 |          P O L I C Y    C H E C K I N G    C L A S S E S            |
 |                                                                     |
 *---------------------------------------------------------------------*/

    /**
 * @ingroup DS_IMG
 *
 * @class GenImage_NoCheck GenImage.h
 *
 * @brief No-check policy.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   November 5, 2003  7:47
 * @since Qgar 2.1.1
 */
    template<typename T> class GenImage_NoCheck
    {
            // -------------------------------------------------------------------
            // P U B L I C   M E M B E R S
            // -------------------------------------------------------------------
        public:

            /**
 * @brief Check a range.
 *
 * @param aPPixmap  a pointer to the pixel map of an image
 * @param aWidth
 * @param aRange
 *
 * @exception qgar::QgarErrorDomain  pixel value out of range
 */
            void checkRange(const T* const aPPixmap,
                            int aWidth,
                            const BoundingBox& aRange) const
            {
                Q_UNUSED(aPPixmap);
                Q_UNUSED(aWidth);
                Q_UNUSED(aRange);
                // VOID
            }

            // -------------------------------------------------------------------
    }; // class GenImage_NoCheck




    /**
 * @ingroup DS_IMG
 *
 * @class GenImage_BoundCheck GenImage.h "qgarlib/GenImage_BoundCheck.h"
 *
 * @brief Policy to check bounds of pixel values.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   November 5, 2003  7:47
 * @since Qgar 2.1.1
 */
    template <typename T>
    class GenImage_BoundCheck
    {
            // -------------------------------------------------------------------
            // P U B L I C   M E M B E R S
            // -------------------------------------------------------------------
        public:

            /** @name Constructors */
            //        ============
            //@{

            /**
 * @brief Default constructor.
 *
 * Lower and upper bounds are intialized to zero.
 */
            GenImage_BoundCheck()

                : _lowerBound(0),
                  _upperBound(0)

            {
                // VOID
            }

            /**
 * @brief Construct from bounds.
 *
 * @param aLowerBnd    lower bound
 * @param anUpperBnd   upper bound
 */
            GenImage_BoundCheck(T aLowerBnd, T anUpperBnd)

                : _lowerBound(aLowerBnd),
                  _upperBound(anUpperBnd)

            {
                // VOID
            }

            //@}


            /** @name Checking */
            //        ========
            //@{

            /**
 * @brief Check that a pixel value is between the bounds.
 *
 * @param aPixel  a pixel value
 *
 * @exception qgar::QgarErrorDomain  pixel value out of range
 */
            void
            checkPixel(const T& aPixel) const

            {
                if ((aPixel < _lowerBound) || (aPixel > _upperBound))
                {
                    ostringstream os;
                    os << "Pixel value out of range: "
                       << aPixel;

                    throw QgarErrorDomain(__FILE__, __LINE__,
                                          "template <typename T> void qgar::GenImage_BoundCheck::checkPixel(const T&) const",
                                          os.str());
                }
            }

            /**
 * @brief Check that all the pixel values  is between the bounds.
 *
 * @param aPPixmap  a pointer to the pixel map of an image
 * @param aWidth
 * @param aRange
 *
 * @exception qgar::QgarErrorDomain  pixel value out of range
 */
            void checkRange(const T* const aPPixmap,
                            int aWidth,
                            const BoundingBox& aRange) const

            {
                for (int iCnt = aRange.xTopLeft() ; iCnt < aRange.width() ; ++iCnt)
                {
                    for (int jCnt = aRange.yTopLeft() ; jCnt < aRange.height() ; ++jCnt)
                    {
                        checkPixel(aPPixmap[(iCnt * aWidth) + jCnt]);
                    }
                }
            }

            //@}


            /** @name Accessor */
            //        ========
            //@{

            /**
 * @brief Get lower bound.
 */
            T lowerBound() const
            {
                return _lowerBound;
            }

            /**
 * @brief Get upper bound.
 */
            T upperBound() const
            {
                return _upperBound;
            }

            //@}


            /** @name Mutator */
            //        =======
            //@{

            /**
 * @brief Set lower bound.
 *
 * @param aBound  new value of the lower bound
 */
            void setLowerBound(const T& aBound)
            {
                _lowerBound = aBound;
            }

            /**
 * @brief Set upper bound.
 *
 * @param aBound  new value of the upper bound
 */
            void setUpperBound(const T& aBound)
            {
                _upperBound = aBound;
            }

            //@}


            // -------------------------------------------------------------------
            // P R I V A T E   M E M B E R S
            // -------------------------------------------------------------------
        private:


            /** @name Bounds */
            //        ======
            //@{

            /**
 * @brief Lower bound of pixel value.
 */
            T _lowerBound;

            /**
 * @brief Upper bound of pixel value.
 */
            T _upperBound;

            //@}


            // -------------------------------------------------------------------
    }; //  class GenImage_BoundCheck








    /*---------------------------------------------------------------------+
 |                                                                     |
 |             C  L  A  S  S       G  E  N  I  M  A  G  E              |
 |                                                                     |
 *---------------------------------------------------------------------*/

    /**
 * @ingroup DS_IMG
 *
 * @class GenImage GenImage.h "qgarlib/GenImage.h"
 *
 * @brief Template class for a generic image with pixels of type <b>T</b>.
 *
 * <ul>
 * <li>
 * Such an image is stored as <b>consecutive rows</b> im memory space.
 * </li>
 * <li>
 * The origin of the coordinate system is at top left corner of the
 * image.
@verbatim
   O
    +---------------->  X
    |
    |
    |
    V

    Y
@endverbatim
 * </li>
 * </ul>
 *
 * The implementation code uses some of Scott Meyers' tips from
 * [<a href="Bibliography.html#Meyer-1996">Meyer,&nbsp;1996</a>].
 * See especially item #20, pages 101-104,
 * about the return value optimization (RVO).
 *
 * <b>Predefined types:</b>
 * <br> &nbsp; &nbsp; &nbsp; &nbsp; See submodule
 * <a href="group__DS__IMG.html"><b>Images</b></a> for details.
 *
 * @warning
 * The following operators and functions are <b>not normalized</b>:
 * - qgar::GenImage::operator+
 * - qgar::GenImage::operator-
 * - qgar::GenImage::operator*
 * - qgar::GenImage::operator+=
 * - qgar::GenImage::operator-=
 * - qgar::GenImage::operator*=
 * - qgar::GenImage::plus
 * - qgar::GenImage::minus
 * - qgar::GenImage::times
 * - qgar::GenImage::plusEqual
 * - qgar::GenImage::minusEqual
 * - qgar::GenImage::timesEqual
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   March 4, 2003  14:09
 * @since  Qgar 2.1
 */
    template
    <
            class T,
            template<class> class CheckPolicy = GenImage_NoCheck
            >
    class GenImage

            : public CheckPolicy<T>

    {
            // -------------------------------------------------------------------
            // T Y P E   D E F I N I T I O N S
            // -------------------------------------------------------------------
        public:


            /** @name Types */
            //        =====
            //@{

            /**
   * @brief Type of the elements stored in the pixel map.
   */
            typedef T value_type;

            /**
   * @brief Reference to qgar::GenImage::value_type.
   */
            typedef value_type& reference;

            /**
   * @brief Constant reference to qgar::GenImage::value_type.
   */
            typedef const value_type& const_reference;

            /**
   * @brief Pointer to qgar::GenImage::value_type.
   */
            typedef value_type* pointer;

            /**
   * @brief Constant pointer to qgar::GenImage::value_type.
   */
            typedef const value_type* const_pointer;

            //@}


            // -------------------------------------------------------------------
            // P U B L I C    M E M B E R S
            // -------------------------------------------------------------------
        public:


            /** @name Constructors */
            //        ============
            //@{

            /**
   * @brief Default constructor.
   *
   * Set <b>0</b> to width, to height,
   * to pointer to pixel map, and to reference counter.
   */
            GenImage();

            /**
   * @brief Initialize with given width and height.
   *
   * @param aWidth   width of the image (in pixels)
   * @param aHeight  height of the image (in pixels)
   *
   * @warning The pixel map is allocated but is not initialized.
   */
            GenImage(unsigned int aWidth, unsigned int aHeight);

            //@}


            /** @name Constructor from raw data */
            //        =========================
            //@{

            /**
   * @brief Initialize from a pixmap.
   *
   * @param aWidth     width of the image (in pixels)
   * @param aHeight    height of the image (in pixels)
   * @param aPtPixMap  pointer to a pixel map
   *
   * @warning
   * <b>This constructor takes the ownership of the given pixmap.
   * The created instance will be responsible for deleting it</b>.
   *
   * @exception qgar::QgarErrorInvalidArg  pixel map not allocated
   */
            GenImage(unsigned int aWidth, unsigned int aHeight, pointer aPtPixMap)
            ;

            //@}


            /** @name Constructors from images */
            //        ========================
            //@{

            /**
   * @brief Copy constructor.
   *
   * Perform a <b>deep copy</b>: The pixel map of the source
   * image is duplicated.
   *
   * @param anImg image to be copied
   *
   * @see qgar::GenImage::operator= and qgar::GenImage::shallowCopy
   */
            GenImage(const GenImage& anImg);

            /**
   * @brief Conversion of an image of the same type, using policies.
   *
   * @param anImg  an image with the same pixel type
   *               <b>having different policies</b>
   */
            template<template <class> class OtherCheckPolicy>
            GenImage(const GenImage<value_type, OtherCheckPolicy>& anImg);

            /**
   * @brief Initialize from an image with pixels
   *        of a type different from <b>T</b>.
   *
   * @param anImg an image with pixels of type <b>U</b>
   *        (different from <b>T</b>)
   *
   * @warning Perform a <b>deep copy</b>: The pixel map of the source
   * image is duplicated.
   * This kind of conversion must be explicitely specified by the client.
   */
            template<class U,template<class> class UCheckPolicy>
            explicit GenImage(const GenImage<U, UCheckPolicy>& anImg);

            /**
   * @brief Initialize by copying a rectangular area, defined by a bounding
   *        box, of a given image.
   *
   * The rectangle sides are parallel to the coordinate axis.
   *
   * @param anImg    initial image
   * @param aBox     box defining the rectangular area to copy
   * @param aPixVal  pixel value to fill non-overlaping zones
   *                 (default <b>(T)0</b>)
   *
   * @warning The intersection between the rectangle and the given image must
   * be non-empty. If the overlaping zone is only partial, the non-overlaping
   * zone(s) are filled with pixels having value <b>aPixVal</b>.
   */
            template<template<class> class OtherCheckPolicy>
            GenImage(const GenImage<value_type,OtherCheckPolicy>& anImg,
                     const BoundingBox& aBox,
                     value_type aPixVal = static_cast<value_type>(0));

            /**
   * @brief Initialize by copying a rectangular area, defined by the
   * coordinates of its top left and bottom right corners, of a given image.
   *
   * The rectangle sides are parallel to the coordinate axis.
   *
   * @param anImg          initial image
   * @param aXTopLeft      X coordinate of the area top left corner
   * @param aYTopLeft      Y coordinate of the area top left corner
   * @param aXBottomRight  X coordinate of the area bottom right corner
   * @param aYBottomRight  Y coordinate of the area bottom right corner
   * @param aPixVal        pixel value to fill non-overlaping zones
   *                       (default <b>(T)0</b>)
   *
   * @warning The intersection between the rectangle and the given image must
   * be non-empty. If the overlaping zone is only partial, the non-overlaping
   * zone(s) are filled with pixels having value <b>aPixVal</b>.
   */
            template<template<class> class OtherCheckPolicy>
            GenImage(const GenImage<value_type, OtherCheckPolicy>& anImg,
                     unsigned int aXTopLeft,
                     unsigned int aYTopLeft,
                     unsigned int aXBottomRight,
                     unsigned int aYBottomRight,
                     value_type aPixVal = static_cast<value_type>(0));

            //@}


            /** @name Destructor */
            //        ==========
            //@{

            /**
   * @brief Free space allocated to the pixel map
   * if and only if the reference counter is null.
   */
            virtual ~GenImage();

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

            /**
   * @brief Get the number of bytes per pixel.
   */
            inline int bytesPerPixel() const;

            //@}


            /** @name Access to pixel values */
            //        ======================
            //@{

            /**
   * @brief Get a pixel value.
   *
   * @param aX  X coordinate (column index) of the pixel
   * @param aY  Y coordinate (row index) of the pixel
   */
            value_type pixel(unsigned int aX, unsigned int aY) const;

            /**
   * @brief Get a row of pixels.
   *
   * @param aRowIdx  row index in image
   * @param aRow     buffer to store the row of pixels
   *
   * @warning The behavior of the function is undefined
   * if the buffer size is smaller than the row size.
   */
            void row(unsigned int aRowIdx, pointer aRow) const;

            /**
   * @brief Get a column of pixels.
   *
   * @param aColIdx  column index in image
   * @param aCol     buffer to store the column of pixels
   *
   * @warning The behavior of the function is undefined
   * if the buffer size is smaller than the column size.
   */
            void column(unsigned int aColIdx, pointer aCol) const;

            //@}


            /** @name Access to direct transformations of the pixel map */
            //        =================================================
            //@{

            /**
   * @brief Get a pointer on a given pixel of the image
   *
   * @param aRowIdx  row index of the pixel
   * @param aColIdx  column index of the pixel
   */
            inline pointer pPixel(unsigned int aRowIdx, unsigned int aColIdx) const;

            /**
   * @brief Get a pointer on a row of pixels.
   *
   * @param aRowIdx  row index in image
   */
            inline pointer pRow(unsigned int aRowIdx) const;

            /**
   * @brief Get a pointer on a column of pixels.
   *
   * @param aColIdx  column index in image
   */
            inline pointer pColumn(unsigned int aColIdx) const;

            /**
   * @brief Get the pointer to the pixel map.
   */
            inline pointer pPixMap() const;

            //@}


            /** @name Set pixel values */
            //        ================
            //@{

            /**
   * @brief Set a pixel value.
   *
   * @param aX       X coordinate (column index) of the pixel
   * @param aY       Y coordinate (row index) of the pixel
   * @param aPixVal  value of the pixel
   */
            void setPixel(unsigned int aX, unsigned int aY, value_type aPixVal);

            /**
   * @brief Set a given row of pixels.
   *
   * @param aRowIdx  row index in image
   * @param aRow     row of pixels to store into the pixel map
   */
            void setRow(unsigned int aRowIdx, const_pointer const aRow);

            /**
   * @brief Set a given column of pixels.
   *
   * @param aColIdx  column index in image
   * @param aCol     column of pixels to store into the pixel map
   */
            void setColumn(unsigned int aColIdx, const_pointer const aCol);

            //@}


            /** @name Draw in the pixel map */
            //        =====================
            //@{

            /**
   * @brief Draw a segment in the pixel map.
   *
   * The segment pixels are set using Bresenham's algorithm.
   * See <i>W.M. Newman and R.F. Sproull, Principles of Interactive
   * Computer Graphics, pp. 25-26.</i>
   *
   * @param aSeg     segment to be drawn
   * @param aPixVal  value to set pixels with (default <b>(T)1</b>)
   */
            void draw(const Segment& aSeg, value_type aPixVal = (value_type)1);

            //@}


            /** @name Copy */
            //        ====
            //@{

            /**
   * @brief Shallow copy: The pixel map of the current image
   * is <b>not duplicated</b>.
   *
   * @see qgar::GenImage::operator= and copy constructor.
   *
   * @warning When the copy is completed, the pixel map of the new image
   * is the same memory space as the pixel map of the current image.
   */
            GenImage shallowCopy();

            //@}


            // =======================================================================
            /** @name Operators

      @warning Using stand-alone versions of operators
      (<b>operator+</b>, <b>operator-</b>,
      <b>operator*</b>) is much less efficient then using
      assignment versions (<b>operator+=</b>, <b>operator-=</b>,
      <b>operator*=</b>). For example, an expression like:
@verbatim
    res = a + b - c;
@endverbatim
      uses 2 temporary objects, one for each call to <b>operator+</b>
      and <b>operator-</b>(the pixel map of the last temporary object
      is then copied into the pixel map of <b>res</b>). These
      considerations also apply to functional operators (see the
      corresponding section). To preserve efficiency, the code should be
      written in this way:
@verbatim
    res = a;
    res += b;  // no temporary needed
    res -= c;  // no temporary needed
@endverbatim
  */
            // =======================================================================
            //@{

            /**
   * @brief Assign given image to current image.
   *
   * The current image must have the same dimensions as the given image.
   * The pixel map of the given image is copied into the pixel map of the
   * current image.
   *
   * @param anImg  image to assign to the current image
   *
   * @see qgar::GenImage::shallowCopy and copy constructor.
   *
   * @warning Perform a <b>deep copy</b>: The pixel map of the given
   * image is duplicated.
   */
            GenImage& operator=(const GenImage& anImg);

            /**
   * @brief Assign given image to current image.
   *
   * The current image is not supposed to initially have the same
   * dimensions as the given image.
   *
   * @param anImg  image to assign to the current image
   *
   * @see qgar::GenImage::shallowCopy and copy constructor.
   *
   * @warning Perform a <b>deep copy</b>: The pixel map of the given
   * image is duplicated.
   */
            template<template <class> class OtherCheckPolicy>
            GenImage& operator=(const GenImage<value_type, OtherCheckPolicy>& anImg);

            /**
   * @brief Same as function qgar::GenImage::plus.
   */
            template <template<class> class OtherCheckPolicy>
            GenImage
            operator+(const GenImage<value_type, OtherCheckPolicy>& anImg) const;

            /**
   * @brief Same as function qgar::GenImage::plusEqual.
   */
            template <template<class> class OtherCheckPolicy>
            GenImage& operator+=(const GenImage<value_type, OtherCheckPolicy>& anImg);

            /**
   * @brief Same as function qgar::GenImage::minus.
   */
            template <template<class> class OtherCheckPolicy>
            GenImage
            operator-(const GenImage<value_type, OtherCheckPolicy>& anImg) const;

            /**
   * @brief Same as function qgar::GenImage::minusEqual.
   */
            template <template<class> class OtherCheckPolicy>
            GenImage& operator-=(const GenImage<value_type, OtherCheckPolicy>& anImg);

            /**
   * @brief Same as function qgar::GenImage::times.
   */
            template <template<class> class OtherCheckPolicy>
            GenImage
            operator*(const GenImage<value_type, OtherCheckPolicy>& anImg) const;

            /**
   * @brief Same as function qgar::GenImage::timesEqual.
   */
            template <template<class> class OtherCheckPolicy>
            GenImage& operator*=(const GenImage<value_type, OtherCheckPolicy>& anImg);

            //@}


            // =====================================================================
            /** @name Functional operators

      @warning Using stand-alone versions of these functions
      (<b>plus</b>, <b>minus</b>, <b>times</b>) is
      much less efficient then using assignment versions
      (<b>plusEqual</b>, <b>minusEqual</b>,
      <b>timesEqual</b>). For example, an expression like:
@verbatim
    res = a.plus(b).minus(c);
@endverbatim
      uses 2 temporary objects, one for each call to <b>plusEqual</b>
      and <b>minusEqual</b> (the pixel map of the last temporary
      object is then copied into the pixel map of <b>res</b>). These
      considerations also apply to operators (see the corresponding section).
      To preserve efficiency, the code should be written in this way:
@verbatim
    res = a;
    res.plusEqual(b);   // no temporary needed
    res.minusEqual(c);  // no temporary needed
@endverbatim

      Operators implementation uses Scott Meyers' tips from
      [<a href="Bibliography.html#Meyer-1996">Meyer,&nbsp;1996</a>]:
      item #22, pages 107-110.
  */
            // =====================================================================
            //@{

            /**
   * @brief Add each pixel of the given image to the corresponding pixel
   * of the current image and store each result in a new pixel map.
   *
   * @param anImg image to be added to the current image
   *
   * @return A new image constructed from this new pixel map
   *
   * @warning Given and current images must have the same width and height.
   * The addition is not normalized: Each result is stored in the new
   * pixel map without any checking.
   */
            template<template<class> class OtherCheckPolicy>
            GenImage
            plus(const GenImage<value_type, OtherCheckPolicy>& anImg) const;

            /**
   * @brief Add a given image to the current image.
   *
   * Add each pixel of the given image to the corresponding pixel
   * of the current image and store each result in the pixel map
   * of the current image.
   *
   * @param anImg image to be added to the current image
   *
   * @warning Given and current images must have the same width
   * and height. The addition is not normalized: Each result is
   * stored in the pixel map of the current image without any checking.
   *
   * @exception qgar::QgarErrorDomain  image sizes do not match
   */
            template<template<class> class OtherCheckPolicy>
            GenImage&
            plusEqual(const GenImage<value_type, OtherCheckPolicy>& anImg)
            ;

            /**
   * @brief Subtract each pixel of the given image to the corresponding
   * pixel of the current image and store each result in a new pixel map.
   *
   * @return A new image constructed from this new pixel map
   *
   * @param anImg image to be subtracted to the current image
   *
   * @warning Given and current images must have the same width and height.
   * The subtraction is not normalized: Each result is stored in the new
   * pixel map without any checking.
   */
            template<template<class> class OtherCheckPolicy>
            GenImage
            minus(const GenImage<value_type, OtherCheckPolicy>& anImg) const;

            /**
   * @brief Subtract a given image to the current image.
   * @param anImg image to be subtracted to the current image
   *
   * Subtract each pixel of the given image to the corresponding pixel
   * of the current image and store each result in the pixel map
   * of the current image.
   *
   * @warning Given and current images must have the same width and height.
   * The subtraction is not normalized: Each result is stored in the pixel map
   * of the current image without any checking.
   *
   * @exception qgar::QgarErrorDomain  image sizes do not match
   */
            template<template<class> class OtherCheckPolicy>
            GenImage&
            minusEqual(const GenImage<value_type, OtherCheckPolicy>& anImg)
            ;

            /**
   * @brief Multiply each pixel of the given image to the corresponding
   * pixel of the current image and store each result in a new pixel map.
   *
   * @param anImg image to be multiplied by the current image
   *
   * @return A new image constructed from this new pixel map
   *
   * @warning Given and current images must have the same width and height.
   * The multiplication is not normalized: Each result is stored in the new
   * pixel map without any checking.
   */
            template<template<class> class OtherCheckPolicy>
            GenImage
            times(const GenImage<value_type, OtherCheckPolicy>& anImg) const;

            /**
   * @brief Multiply a given image by the current image.
   *
   * Multiply each pixel of the given image by the corresponding pixel
   * of the current image and store each result in the pixel map
   * of the current image.
   *
   * @param anImg image to be multiplied by the current image
   *
   * @warning Given and current images must have the same width and height.
   * The multiplication is not normalized: Each result is stored
   * in the pixel map of the current image without any checking.
   *
   * @exception qgar::QgarErrorDomain  image sizes do not match
   */
            template<template<class> class OtherCheckPolicy>
            GenImage&
            timesEqual(const GenImage<value_type, OtherCheckPolicy>& anImg)
            ;

            //@}


            /** @name Border mirroring */
            //        ================
            //@{

            /**
   * @brief Mirror border rows for convolutions.
   *
   * @param aRowIdx index of the row
   */
            int borderRows(int aRowIdx) const;

            /**
   * @brief Mirror border columns for convolutions.
   *
   * @param aColIdx index of the column
   */
            int borderCols(int aColIdx) const;

            //@}


            // -------------------------------------------------------------------
            // P R O T E C T E D    M E M B E R S
            // -------------------------------------------------------------------
        protected:


            /** @name Constructor from raw data */
            //        =========================
            //@{

            /**
   * @brief Initialize from all data.
   *
   * @param aBytesCnt    bytes per pixel
   * @param aPtRefCnt    pointer to a reference counter
   * @param aWidth       width of the image
   * @param aHeight      height of the image
   * @param aPtPixMap    pointer to a pixel map
   *
   * @warning Using this constructor may lead to serious bugs
   * due to dynamic memory space management.
   * Be sure that the value of the given reference counter (pointed
   * by <b>aPtRefCnt</b>) is correct: If the given pixel map
   * (pointed by <b>aPtPixMap</b>) is not shared by another
   * object, this value must be <b>0</b>. Otherwise, one must
   * add <b>1</b> to the value, before using the constructor:
@verbatim
(*_pRefCnt)++;
@endverbatim
   */
            GenImage(unsigned int  aBytesCnt,
                     int*          aPtRefCnt,
                     unsigned int  aWidth,
                     unsigned int  aHeight,
                     pointer       aPtPixMap);

            //@}


            /** @name Representation of an image */
            //        ==========================
            //@{

            /**
   * @brief Number of bytes per pixel.
   */
            unsigned int _bytesPerPixel;

            /**
   * @brief Reference counter.
   *
   * Its value represent the number of other images with which
   * the current image shares its pixel map.
   */
            int* _pRefCnt;

            /**
   * @brief Image width.
   */
            int _width;

            /**
   * @brief Image height.
   */
            int _height;

            /**
   * @brief Pointer to the pixel map,
   * organized as <b>consecutive rows</b>.
   */
            pointer _pPixMap;

            //@}


            /** @name Auxiliaries */
            //        ===========
            //@{

            /**
   * @brief Copy a rectangular area of the given image
   *        into the current image.
   *
   * The sides of the rectangle are parallel to the coordinate axis.
   *
   * @param anImg          initial image
   * @param aXTopLeft      X coordinate of the area top left corner
   * @param aYTopLeft      Y coordinate of the area left corner
   * @param aXBottomRight  X coordinate of the area bottom right corner
   * @param aYBottomRight  Y coordinate of the area bottom right corner
   * @param aPixVal        pixel value to fill non-overlaping zones
   *                       (default <b>(T)0</b>)
   *
   * @warning The intersection between the rectangle and the given image must
   * be non-empty. If the overlaping zone is only partial, the non-overlaping
   * zone(s) are filled with pixels having value <b>aPixVal</b>.
   *
   * @todo To be reimplemented.
   */
            void copyBox(const GenImage<value_type, CheckPolicy>& anImg,
                         unsigned int aXTopLeft,
                         unsigned int aYTopLeft,
                         unsigned int aXBottomRight,
                         unsigned int aYBottomRight,
                         value_type aPixVal = static_cast<value_type>(0));

            //@}


            // -------------------------------------------------------------------
    }; // class GenImage


} // namespace qgar




// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// I M P L E M E N T A T I O N
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII

#include "GenImage.tcc"

// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII




// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// PREDEFINED TYPES RELATED TO IMAGES
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


namespace qgar
{


    /** @name Pixel type names */
    //        ================
    //@{

    /**
 * @ingroup DS_IMG
 *
 * @brief Pixel type of a binary image.
 */
    typedef unsigned char BinaryPixel;

    /**
 * @ingroup DS_IMG
 *
 * @brief Pixel type of a grey-level image.
 */
    typedef unsigned char GreyLevelPixel;

    //@}


    /** @name Image type names */
    //        ================
    //@{

    /**
 * @ingroup DS_IMG
 *
 * @brief Binary image.
 */
    typedef GenImage<BinaryPixel> BinaryImage;

    /**
 * @ingroup DS_IMG
 *
 * @brief Grey-level Image.
 */
    typedef GenImage<GreyLevelPixel> GreyLevelImage;

    /**
 * @ingroup DS_IMG
 *
 * @brief Image with <b>unsigned char</b> pixels.
 */
    typedef GenImage<unsigned char> UCharImage;

    /**
 * @ingroup DS_IMG
 *
 * @brief Image with <b>int</b> pixels.
 */
    typedef GenImage<int> IntImage;

    /**
 * @ingroup DS_IMG
 *
 * @brief Images with <b>float</b> pixels.
 */
    typedef GenImage<float> FloatImage;

    /**
 * @ingroup DS_IMG
 *
 * @brief Images with <b>double</b> pixels.
 */
    typedef GenImage<double> DoubleImage;

    //@}


    /** @name Bounded image type names */
    //        ========================
    //@{

    /**
 * @ingroup DS_IMG
 *
 * @brief Bounded binary image.
 */
    typedef GenImage<BinaryPixel, GenImage_BoundCheck> BoundedBinaryImage;

    /**
 * @ingroup DS_IMG
 *
 * @brief Bounded grey-level image.
 */
    typedef GenImage<GreyLevelPixel, GenImage_BoundCheck> BoundedGreyLevelImage;

    /**
 * @ingroup DS_IMG
 *
 * @brief Bounded image with <b>unsigned char</b> pixels.
 */
    typedef GenImage<unsigned char, GenImage_BoundCheck> BoundedUCharImage;

    /**
 * @ingroup DS_IMG
 *
 * @brief Bounded image with <b>int</b> pixels.
 */
    typedef GenImage<int, GenImage_BoundCheck> BoundedIntImage;

    /**
 * @ingroup DS_IMG
 *
 * @brief Bounded image with <b>float</b> pixels.
 */
    typedef GenImage<float, GenImage_BoundCheck> BoundedFloatImage;

    /**
 * @ingroup DS_IMG
 *
 * @brief Bounded image with <b>double</b> pixels.
 */
    typedef GenImage<double, GenImage_BoundCheck> BoundedDoubleImage;

    //@}


} // namespace qgar


// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


#endif /* __GENIMAGE_H_INCLUDED__ */
