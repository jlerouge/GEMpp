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


/**
 * @file   GenImage.tcc
 * @brief  Implementation of function members of class qgar::GenImage.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   January 27, 2005  21:12
 * @since  Qgar 2.2
 */



// STD
#include <cmath>
#include <sstream>
#include <cstring>
// QGAR
#include "array.h"



using namespace std;



namespace qgar
{


// -------------------------------------------------------------------
// C O N S T R U C T O R S
// -------------------------------------------------------------------


// DEFAULT CONSTRUCTOR

template <class T, template<class> class CheckPolicy>
GenImage<T, CheckPolicy>::GenImage()

    : _bytesPerPixel(sizeof(T)),
      _pRefCnt(new int(0)),
      _width(0),
      _height(0),
      _pPixMap(0)

{
    // VOID
}


// INITIALIZE WITH GIVEN WIDTH AND HEIGHT
// The pixel map is allocated but is not initialized

template <class T, template<class> class CheckPolicy>
GenImage<T, CheckPolicy>::GenImage(unsigned int aWidth,
                                   unsigned int aHeight)

    : _bytesPerPixel(sizeof(T)),
      _pRefCnt(new int(0)),
      _width(aWidth),
      _height(aHeight)

{
    _pPixMap = new T[aWidth * aHeight];
}


// -------------------------------------------------------------------
// C O N S T R U C T O R   F R O M   R A W   D A T A
// -------------------------------------------------------------------


// INITIALIZE FROM PIXMAP

template<class T, template<class> class CheckPolicy>
GenImage<T, CheckPolicy>::GenImage(unsigned int aWidth, 
                                   unsigned int aHeight,
                                   T* aPtPixMap)



    : _bytesPerPixel(sizeof(T)),
      _pRefCnt(new int(0)),
      _width(aWidth),
      _height(aHeight),
      _pPixMap(aPtPixMap)

{
    // Ensure given pixmap pointer is not null
    if (! _pPixMap )
    {
        throw QgarErrorInvalidArg(__FILE__, __LINE__,
                                  "template<class T, template<class> class CheckPolicy> qgar::GenImage<T, CheckPolicy>::GenImage(unsigned int, unsigned int, T*)",
                                  "Pointer to pixmap cannot be null");
    }

    // Ensure that given pixmap conforms to image invariant
    this->checkRange(_pPixMap, _width, BoundingBox(Point(), _width, _height));
}


// INITIALIZE FROM FULL DATA

template <class T, template<class> class CheckPolicy>
GenImage<T, CheckPolicy>::GenImage(unsigned int aBytesCnt,
                                   int* aPtRefCnt,
                                   unsigned int aWidth,
                                   unsigned int aHeight,
                                   T* aPtPixMap)

    : _bytesPerPixel(aBytesCnt),
      _pRefCnt(aPtRefCnt),
      _width(aWidth),
      _height(aHeight),
      _pPixMap(aPtPixMap)

{
    // Ensure that passed pixmap does not contradict image invariant.
    this->checkRange(_pPixMap, _width, BoundingBox(Point(), _width, _height));
}


// -------------------------------------------------------------------
// C O N S T R U C T O R S   F R O M   I M A G E S
// -------------------------------------------------------------------


// COPY CONSTRUCTOR

template <class T, template<class> class CheckPolicy>
GenImage<T, CheckPolicy>::GenImage(const GenImage& anImg)

    : _bytesPerPixel(anImg._bytesPerPixel),
      _pRefCnt(new int(0)),
      _width(anImg._width),
      _height(anImg._height)

{
    int size = _width * _height;
    _pPixMap = new T[size];
    memcpy(_pPixMap, anImg._pPixMap, size * sizeof(T));
}


// CONVERSION FROM AN IMAGE HAVING SAME PIXEL TYPE 'T'
// BUT DIFFERENT POLICIES

template <class T, template<class> class CheckPolicy>
template <template<class> class OtherCheckPolicy>
GenImage<T, CheckPolicy>::GenImage(const GenImage<T, OtherCheckPolicy>& anImg)

    : _bytesPerPixel(anImg.bytesPerPixel()),
      _pRefCnt(new int(0)),
      _width(anImg.width() ),
      _height(anImg.height() )

{
    // Ensure that passed pixmap does not contradict image invariant.
    this->checkRange(anImg.pPixMap(), _width, BoundingBox(Point(), _width, _height));

    int size = _width * _height;
    _pPixMap = new T[size];
    memcpy(_pPixMap, anImg.pPixMap(), size * sizeof(T));
}


// INITIALIZE FROM AN IMAGE WITH PIXELS OF A TYPE DIFFERENT FROM 'T'

template<class T, template<class> class CheckPolicy>
template<class U, template<class> class UCheck>
GenImage<T, CheckPolicy>::GenImage(const GenImage<U, UCheck>& anImg)

    : _bytesPerPixel(sizeof(T)),
      _pRefCnt(new int(0)),
      _width(anImg.width()),
      _height(anImg.height())

{
    int size = _width * _height;
    _pPixMap = new T[size];

    U* pMapFrom = anImg.pPixMap();
    T* pMapTo   = _pPixMap;
    for (int iCnt = 0; iCnt < size ; ++iCnt, ++pMapTo, ++pMapFrom)
    {
        *pMapTo = static_cast<T>(*pMapFrom);
    }

    // Ensure that passed pixmap does not contradict image invariant.
    this->checkRange(_pPixMap, _width, BoundingBox(Point(), _width, _height));
}


// INITIALIZE BY COPYING A BOUNDING BOX OF A GIVEN IMAGE
//
// The bounding box defines a rectangular area whose sides are parallel
// to the coordinate axis.
// The intersection between this rectangle and the given image must be
// non-empty. If the overlaping zone is only partial, the non-overlaping
// zones are filled with pixels having value 'aPixVal'

template<class T, template<class> class CheckPolicy>
template<template<class> class OtherCheckPolicy>
GenImage<T, CheckPolicy>::GenImage(const GenImage<T, OtherCheckPolicy>& anImg,
                                   const BoundingBox& aBox,
                                   T aPixVal)

    : _bytesPerPixel(anImg.bytesPerPixel()),
      _pRefCnt(new int(0)),
      _width(aBox.width()),
      _height(aBox.height()),
      _pPixMap(new T[aBox.width() * aBox.height()])

{
    copyBox(anImg,
            aBox.xTopLeft(),
            aBox.yTopLeft(),
            aBox.xBottomRight(),
            aBox.yBottomRight(),
            aPixVal);

    // Ensure that modified pixmap does not contradict image invariant.
    this->checkRange(_pPixMap, _width, aBox);
}


// INITIALIZE BY COPYING A RECTANGULAR AREA OF A GIVEN IMAGE
//
// The rectangle sides are parallel to the coordinate axis.
// The intersection between the rectangle and the given image must be
// non-empty. If the overlaping zone is only partial, the non-overlaping
// zones are filled with pixels having value 'aPixVal'

template <class T, template<class> class CheckPolicy>
template <template<class> class OtherCheckPolicy>
GenImage<T, CheckPolicy>::GenImage(const GenImage<T, OtherCheckPolicy>& anImg,
                                   unsigned int aXTopLeft,
                                   unsigned int aYTopLeft,
                                   unsigned int aXBottomRight,
                                   unsigned int aYBottomRight,
                                   T aPixVal)

    : _bytesPerPixel(anImg.bytesPerPixel()),
      _pRefCnt(new int(0)),
      _width(aXBottomRight - aXTopLeft + 1),
      _height(aYBottomRight - aYTopLeft + 1 ),
      _pPixMap(new T[  (aXBottomRight - aXTopLeft + 1)
      * (aYBottomRight - aYTopLeft + 1)])

{
    copyBox(anImg,
            aXTopLeft,
            aYTopLeft,
            aXBottomRight,
            aYBottomRight,
            aPixVal);

    // Ensure that passed pixmap does not contradict image invariant.
    this->checkRange(_pPixMap,
                     _width,
                     BoundingBox(aXTopLeft, aYTopLeft, aXBottomRight, aYBottomRight));
}


// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------


template <class T, template<class> class CheckPolicy>
GenImage<T, CheckPolicy>::~GenImage()
{
    if (*_pRefCnt == 0)
    {
        // The space allocated to the pixel map
        // is not shared with another object
        delete [] _pPixMap;
        delete _pRefCnt;
    }
    else
    {
        // The space allocated to the pixel map is shared
        // with at least one other object:
        // just decrement the reference counter
        (*_pRefCnt)--;
    }
}


// -------------------------------------------------------------------
// A C C E S S   T O   I M A G E   C H A R A C T E R I S T I C S
// -------------------------------------------------------------------


// GET THE IMAGE WIDTH

template <class T, template<class> class CheckPolicy>
inline int
GenImage<T, CheckPolicy>::width() const
{
    return _width;
}


// GET THE IMAGE HEIGHT

template <class T, template<class> class CheckPolicy>
inline int
GenImage<T, CheckPolicy>::height() const
{
    return _height;
}


// GET THE NUMBER OF BYTES PER PIXEL

template <class T, template<class> class CheckPolicy>
inline int
GenImage<T, CheckPolicy>::bytesPerPixel() const
{
    return _bytesPerPixel;
}


// -------------------------------------------------------------------
// A C C E S S   T O   P I X E L   V A L U E S
// -------------------------------------------------------------------


// GET A PIXEL VALUE

template <class T, template<class> class CheckPolicy>
T
GenImage<T, CheckPolicy>::pixel(unsigned int aX,
                                unsigned int aY)
const
{
    return *(_pPixMap + (aY * _width) + aX);
}


// FILL A GIVEN ARRAY WITH A ROW OF PIXELS

template <class T, template<class> class CheckPolicy>
void
GenImage<T, CheckPolicy>::row(unsigned int aRowIdx,
                              T* aRow)
const
{
    memcpy(aRow, _pPixMap + (aRowIdx * _width), _width * sizeof(T));
}


// GET A COLUMN OF PIXELS

template <class T, template<class> class CheckPolicy>
void
GenImage<T, CheckPolicy>::column(unsigned int aColIdx,
                                 T* aCol)
const
{
    T* pMap = _pPixMap + aColIdx;
    T* pCol  = aCol;
    for (int iCnt = 0;
         iCnt < _height ;
         ++iCnt, ++pCol, pMap += _width)
    {
        *pCol = *pMap;
    }
}


// -------------------------------------------------------------------
// ACCESS TO DIRECT TRANSFORMATIONS OF THE PIXEL MAP
// -------------------------------------------------------------------


// GET A POINTER ON A GIVEN PIXEL

template <class T, template<class> class CheckPolicy>
inline T*
GenImage<T, CheckPolicy>::pPixel(unsigned int aRowIdx,
                                 unsigned int aColIdx) const
{
    return _pPixMap + (aRowIdx * _width) + aColIdx;
}


// GET A POINTER ON A ROW OF PIXELS

template <class T, template<class> class CheckPolicy>
inline T*
GenImage<T, CheckPolicy>::pRow(unsigned int aRowIdx) const
{
    return _pPixMap + (aRowIdx * _width);
}


// GET A POINTER ON A COLUMN OF PIXELS

template <class T, template<class> class CheckPolicy>
inline T*
GenImage<T, CheckPolicy>::pColumn(unsigned int aColIdx) const
{
    return _pPixMap + aColIdx;
}


// GET THE POINTER TO THE PIXEL MAP

template <class T, template<class> class CheckPolicy>
inline T*
GenImage<T, CheckPolicy>::pPixMap() const
{
    return _pPixMap;
}


// -------------------------------------------------------------------
// S E T   P I X E L   V A L U E S
// -------------------------------------------------------------------


// SET A PIXEL VALUE

template <class T, template<class> class CheckPolicy>
void
GenImage<T, CheckPolicy>::setPixel(unsigned int aX,
                                   unsigned int aY,
                                   T aPixVal)
{
    *(_pPixMap + (aY * _width) + aX) = aPixVal;

    // Ensure that new pixel value does not contradict image invariant.
    this->checkRange(_pPixMap, _width, BoundingBox(aX, aY, 1, 1));
}


// SET A ROW OF PIXELS

template <class T, template<class> class CheckPolicy>
void
GenImage<T, CheckPolicy>::setRow(unsigned int aRowIdx,
                                 const T* const aRow)
{
    memcpy(_pPixMap + (aRowIdx * _width), aRow, _width * sizeof(T));

    // Ensure that new row does not contradict pixel invariant.
    this->checkRange(_pPixMap + (aRowIdx * _width), _width,
                     BoundingBox(Point(), _width, _height));
}


// SET A COLUMN OF PIXELS

template <class T, template<class> class CheckPolicy>
void
GenImage<T, CheckPolicy>::setColumn(unsigned int aColIdx,
                                    const T* const aCol)
{
    T* pMapTo = _pPixMap + aColIdx;
    const T* pCol  = aCol;
    for (int iCnt = 0;
         iCnt < _height ;
         ++iCnt, ++pCol, pMapTo += _width)
    {
        *pMapTo = *pCol;
    }

    // Ensure that the new column does not contradict invariant.
    this->checkRange(_pPixMap, _width, BoundingBox(Point(), 1, _height));
}


// -------------------------------------------------------------------
// D R A W   I N   T H E   P I X E L   M A P
// -------------------------------------------------------------------


// Bresenham's algorithm is used
// Pixels are set to value 'aPixVal'

template <class T, template<class> class CheckPolicy>
void
GenImage<T, CheckPolicy>::draw(const Segment& aSeg, T aPixVal)
{
    Point p1 = aSeg.source();
    Point p2 = aSeg.target();
    
    int x;
    int y;
    int xlast;
    int ylast;
    
    int dx = (int)(fabs((double)p2.x() - p1.x())); // Delta x
    int dy = (int)(fabs((double)p2.y() - p1.y())); // Delta y
    
    if (dx > dy)
    {
        // Main axis Ox
        if (p1.x() < p2.x())
        {
            // find out where to start and where to end
            x     = p1.x();
            y     = p1.y();
            xlast = p2.x();
            ylast = p2.y();
        }
        else
        {
            x     = p2.x();
            y     = p2.y();
            xlast = p1.x();
            ylast = p1.y();
        }

        int e = (dy << 1) - dx; // Initialize
        if (y < ylast)
        {
            for (int iCnt = 0 ; iCnt < dx ; ++iCnt)
            {
                // Write if in image
                if ((x > 0) && (x < _width) && (y > 0) && (y < _height))
                {
                    setPixel(x, y, aPixVal);
                }
                if (e > 0)
                {
                    ++y;
                    e += (dy << 1) - (dx << 1);
                }
                else
                {
                    e += (dy << 1);
                }
                ++x;
            }
        }
        else
        {
            for (int iCnt = 0 ; iCnt < dx ; ++iCnt)
            {
                // Write if in image
                if ((x > 0) && (x < _width) && (y > 0) && (y < _height))
                {
                    setPixel(x, y, aPixVal);
                }
                if (e > 0)
                {
                    --y;
                    e += (dy << 1) - (dx << 1);
                }
                else
                {
                    e += (dy << 1);
                }
                ++x;
            }
        }
    }
    else
    {
        // Main axis Oy
        if (p1.y() < p2.y())
        {
            x     = p1.x();
            y     = p1.y();
            xlast = p2.x();
            ylast = p2.y();
        }
        else
        {
            x = p2.x();
            y = p2.y();
            xlast = p1.x();
            ylast = p1.y();
        }

        int e = (dx << 1) - dy;
        if (x < xlast)
        {
            for (int iCnt =0 ; iCnt < dy ; ++iCnt)
            {
                // Write if in image
                if ((x > 0) && (x < _width) && (y > 0) && (y < _height))
                {
                    setPixel(x, y, aPixVal);
                }

                if (e > 0)
                {
                    ++x;
                    e += (dx << 1) - (dy << 1);
                }
                else
                {
                    e += (dx << 1);
                }
                ++y;
            }
        }
        else
        {
            for (int iCnt = 0 ; iCnt < dy ; ++iCnt)
            {
                if ((x > 0) && (x < _width) && (y > 0) && (y < _height))
                {
                    setPixel(x, y, aPixVal);
                }

                if (e > 0)
                {
                    --x;
                    e += (dx << 1) - (dy << 1);
                }
                else
                {
                    e += (dx << 1);
                }
                ++y;
            }
        }
    }

    if ((xlast > 0) && (xlast < _width) && (ylast > 0) && (ylast < _height))
    {
        setPixel(xlast, ylast, aPixVal); // write last pixel
    }
}


// -------------------------------------------------------------------
// C O P Y
// -------------------------------------------------------------------


// SHALLOW COPY: THE PIXEL MAP OF THE CURRENT IMAGE IS NOT DUPLICATED

template <class T, template<class> class CheckPolicy>
GenImage<T, CheckPolicy>
GenImage<T, CheckPolicy>::shallowCopy()
{
    (*_pRefCnt)++;

    return GenImage<T, CheckPolicy>(_bytesPerPixel,
                                    _pRefCnt,
                                    _width,
                                    _height,
                                    _pPixMap);
}


// -------------------------------------------------------------------
// A S S I G N M E N T
// -------------------------------------------------------------------


// ASSIGN GIVEN IMAGE TO CURRENT IMAGE: PERFORM A DEEP COPY

template <class T, template<class> class CheckPolicy>
GenImage<T, CheckPolicy>& 
GenImage<T, CheckPolicy>::operator=(const GenImage& anImg)
{
    if (this != &anImg)
    {
        _width  = anImg.width();
        _height = anImg.height();

        // Free the current pixel map and allocate a new one
        delete [] _pPixMap;
        int size = _width * _height;
        _pPixMap = new T[size];

        // Copy the pixel map
        memcpy(_pPixMap, anImg.pPixMap(), size * sizeof(T));
    }
    return *this;
}


// ASSIGN GIVEN IMAGE TO CURRENT IMAGE: PERFORM A DEEP COPY

template <class T, template<class> class CheckPolicy>
template<template <class> class OtherCheckPolicy>
GenImage<T, CheckPolicy>& 
GenImage<T, CheckPolicy>::operator=(const GenImage<T, OtherCheckPolicy>& anImg)
{
    // Ensure that rhs pixmap does not contradict lhs invariant.
    this->checkRange(anImg.pPixMap(), anImg.width(),
                     BoundingBox(Point(), anImg.width(), anImg.height()));

    _width  = anImg.width();
    _height = anImg.height();

    // Free the current pixel map and allocate a new one
    delete [] _pPixMap;
    int size = _width * _height;
    _pPixMap = new T[size];

    // Copy the pixel map
    memcpy(_pPixMap, anImg.pPixMap(), size * sizeof(T));

    return *this;
}


// -------------------------------------------------------------------
// I M A G E   A D D I T I O N S
// -------------------------------------------------------------------


// ADD 2 IMAGES: THE ADDITION IS NOT NORMALIZED

template <class T, template<class> class CheckPolicy>
template<template<class> class OtherCheckPolicy>
GenImage<T, CheckPolicy> 
GenImage<T, CheckPolicy>::operator+(const GenImage<T, OtherCheckPolicy>& anImg) const
{
    return plus(anImg);
}


// ADD TO CURRENT IMAGE: THE ADDITION IS NOT NORMALIZED

template <class T, template<class> class CheckPolicy>
template<template<class> class OtherCheckPolicy>
GenImage<T, CheckPolicy>& 
GenImage<T, CheckPolicy>::operator+=(const GenImage<T, OtherCheckPolicy>& anImg)
{
    return plusEqual(anImg);
}


// ADD 2 IMAGES: THE ADDITION IS NOT NORMALIZED
template <class T, template<class> class CheckPolicy>
template<template<class> class OtherCheckPolicy>
GenImage<T, CheckPolicy>
GenImage<T, CheckPolicy>::plus(const GenImage<T, OtherCheckPolicy>& anImg) const
{
    return GenImage(*this).plusEqual(anImg);
}

// ADD TO CURRENT IMAGE: THE ADDITION IS NOT NORMALIZED
template <class T, template<class> class CheckPolicy>
template<template<class> class OtherCheckPolicy>
GenImage<T, CheckPolicy>&
GenImage<T, CheckPolicy>::plusEqual(const GenImage<T, OtherCheckPolicy>& anImg)



{
    if ((_width != anImg.width()) || (_height != anImg.height()))
    {
        // Image sizes do not match
        ostringstream os;
        os << "Size of image to be added ["
           << anImg.width()
           << " X "
           << anImg.height()
           << "] is different from current image size ["
           << _width
           << " X "
           << _height
           << "]";

        throw QgarErrorDomain(__FILE__, __LINE__,
                              "template <class T, template<class> class CheckPolicy> template<template<class> class OtherCheckPolicy> qgar::GenImage<T, CheckPolicy>& qgar::GenImage<T, CheckPolicy>::plusEqual(const qgar::GenImage<T, OtherCheckPolicy>&)",
                              os.str());
    }

    T* pMapTo  = _pPixMap;
    T* pMapFrom = anImg.pPixMap();
    int size  = _width * _height;
    for (int iCnt = 0 ; iCnt < size ; ++iCnt, ++pMapTo, ++pMapFrom)
    {
        *pMapTo += *pMapFrom;
    }

    // Ensure that pixmap after operation still conforms to the invariant.
    this->checkRange(_pPixMap, _width, BoundingBox(Point(), _width, _height));

    return *this;
}


// -------------------------------------------------------------------
// I M A G E   S U B T R A C T I O N
// -------------------------------------------------------------------


// SUBTRACT 2 IMAGES: THE SUBTRACTION IS NOT NORMALIZED

template <class T, template<class> class CheckPolicy>
template<template<class> class OtherCheckPolicy>
GenImage<T, CheckPolicy> 
GenImage<T, CheckPolicy>::operator-(const GenImage<T, OtherCheckPolicy>& anImg) const
{
    return minus(anImg);
}


// SUBTRACT TO CURRENT IMAGE: THE ADDITION IS NOT NORMALIZED

template <class T, template<class> class CheckPolicy>
template<template<class> class OtherCheckPolicy>
GenImage<T, CheckPolicy>& 
GenImage<T, CheckPolicy>::operator-=(const GenImage<T, OtherCheckPolicy>& anImg)
{
    return minusEqual(anImg);
}


// SUBTRACT 2 IMAGES: THE SUBTRACTION IS NOT NORMALIZED
template <class T, template<class> class CheckPolicy>
template<template<class> class OtherCheckPolicy>
GenImage<T, CheckPolicy> 
GenImage<T, CheckPolicy>::minus(const GenImage<T, OtherCheckPolicy>& anImg) const
{
    // Create a copy of the current image and subtract the given image to it
    return GenImage(*this).minusEqual(anImg);
}

// SUBTRACT TO CURRENT IMAGE: THE SUBTRACTION IS NOT NORMALIZED
template <class T, template<class> class CheckPolicy>
template<template<class> class OtherCheckPolicy>
GenImage<T, CheckPolicy>& 
GenImage<T, CheckPolicy>::minusEqual(const GenImage<T, OtherCheckPolicy>& anImg)



{
    if ((_width != anImg.width()) || (_height != anImg.height()))
    {
        // Image sizes do not match
        ostringstream os;
        os << "Size of image to be added ["
           << anImg.width()
           << " X "
           << anImg.height()
           << "] is different from current image size ["
           << _width
           << " X "
           << _height
           << "]";

        throw QgarErrorDomain(__FILE__, __LINE__,
                              "template <class T, template<class> class CheckPolicy> template<template<class> class OtherCheckPolicy> qgar::GenImage<T, CheckPolicy>& qgar::GenImage<T, CheckPolicy>::minusEqual(const qgar::GenImage<T, OtherCheckPolicy>&)",
                              os.str());
    }

    T* pMapTo  = _pPixMap;
    T* pMapFrom = anImg.pPixMap();
    int size  = _width * _height;
    for (int iCnt = 0 ; iCnt < size ; ++iCnt, ++pMapTo, ++pMapFrom)
    {
        *pMapTo -= *pMapFrom;
    }

    // Ensure that pixmap after operation still conforms to the invariant.
    this->checkRange(_pPixMap, _width, BoundingBox(Point(), _width, _height));

    return *this;
}


// -------------------------------------------------------------------
// I M A G E   M U L T I P L I C A T I O N
// -------------------------------------------------------------------


// MULTIPLY 2 IMAGES: THE MULTIPLICATION IS NOT NORMALIZED

template <class T, template<class> class CheckPolicy>
template<template<class> class OtherCheckPolicy>
GenImage<T, CheckPolicy> 
GenImage<T, CheckPolicy>::operator*(const GenImage<T, OtherCheckPolicy>& anImg) const
{
    return times(anImg);
}


// MULTIPLY BY GIVEN IMAGE: THE MULTIPLICATION IS NOT NORMALIZED

template <class T, template<class> class CheckPolicy>
template<template<class> class OtherCheckPolicy>
GenImage<T, CheckPolicy>&
GenImage<T, CheckPolicy>::operator*=(const GenImage<T, OtherCheckPolicy>& anImg)
{
    return timesEqual(anImg);
}


// MULTIPLY 2 IMAGES: THE MULTIPLICATION IS NOT NORMALIZED
template <class T, template<class> class CheckPolicy>
template<template<class> class OtherCheckPolicy>
GenImage<T, CheckPolicy>
GenImage<T, CheckPolicy>::times(const GenImage<T, OtherCheckPolicy>& anImg) const
{
    // Create a copy of the current image and multiply the given image to it
    return GenImage(*this).timesEqual(anImg);
}


// MULTIPLY BY GIVEN IMAGE: THE MULTIPLICATION IS NOT NORMALIZED
template <class T, template<class> class CheckPolicy>
template<template<class> class OtherCheckPolicy>
GenImage<T, CheckPolicy>&
GenImage<T, CheckPolicy>::timesEqual(const GenImage<T, OtherCheckPolicy>& anImg)



{

    if ((_width != anImg.width()) || (_height != anImg.height()))
    {
        // Image sizes do not match
        ostringstream os;
        os << "Size of image to be added ["
           << anImg.width()
           << " X "
           << anImg.height()
           << "] is different from current image size ["
           << _width
           << " X "
           << _height
           << "]";

        throw QgarErrorDomain(__FILE__, __LINE__,
                              "template <class T, template<class> class CheckPolicy> template<template<class> class OtherCheckPolicy> qgar::GenImage<T, CheckPolicy>& qgar::GenImage<T, CheckPolicy>::timesEqual(const qgar::GenImage<T, OtherCheckPolicy>&)",
                              os.str());
    }

    T* pMapTo   = _pPixMap;
    T* pMapFrom = anImg.pPixMap();
    int size  = _width * _height;
    for (int iCnt = 0 ; iCnt < size ; iCnt++, ++pMapTo, ++pMapFrom)
    {
        *pMapTo *= *pMapFrom;
    }

    // Ensure that pixmap after operation still conforms to the invariant.
    this->checkRange(_pPixMap, _width, BoundingBox(Point(), _width, _height));

    return *this;
}


// -------------------------------------------------------------------
// B O R D E R   M I R R O R I N G
// -------------------------------------------------------------------


// MIRROR BORDER ROWS FOR CONVOLUTIONS

template <class T, template<class> class CheckPolicy>
int
GenImage<T, CheckPolicy>::borderRows(int aRowIdx) const
{ 
    return (aRowIdx < 0)
            ? -aRowIdx
            : (
                  (aRowIdx < _height)
                  ? aRowIdx
                  : (_height - aRowIdx + _height - 2)
                    );
}


// MIRROR BORDER COLUMNS FOR CONVOLUTIONS

template <class T, template<class> class CheckPolicy>
int
GenImage<T, CheckPolicy>::borderCols(int aColIdx) const
{
    return (aColIdx < 0)
            ? -aColIdx
            : (
                  (aColIdx < _width)
                  ? aColIdx
                  : (_width - aColIdx + _width - 2)
                    );
}


// -------------------------------------------------------------------
// A U X I L I A R I E S 
// -------------------------------------------------------------------


// PERFORM THE COPY OF A RECTANGULAR ZONE OF A GIVEN IMAGE
// INTO THE CURRENT IMAGE

template <class T, template<class> class CheckPolicy>
void 
GenImage<T, CheckPolicy>::copyBox(const GenImage<T, CheckPolicy>& anImg,
                                  unsigned int aXTopLeft,
                                  unsigned int aYTopLeft,
                                  unsigned int aXBottomRight,
                                  unsigned int aYBottomRight,
                                  T aPixVal)
{
    Q_UNUSED(aXBottomRight);
    Q_UNUSED(aYBottomRight);
    T*  pMapTo  = _pPixMap;   // Pointer to the current image
    int rowTo   = 0;          // Row index in current image
    int rowFrom = aYTopLeft;  // Row index in given image

    // Fill non-overlaping rows (if any)
    for ( ; rowFrom < 0 ; ++rowTo, ++rowFrom)
    {
        qgFill(pMapTo, _width, aPixVal);
    }

    // Pointer to the first significant pixel in the given image
    T* pMapFrom = anImg.pPixMap() + (rowFrom * anImg.width());

    // Copy significant pixels from the rectangle into the current image
    for ( ;
          (rowTo < _height) && (rowFrom < anImg.height()) ;
          ++rowTo, ++rowFrom)
    {
        int currCol = 0;
        int imgCol = aXTopLeft;

        // Fill non-overlaping rows (if any)
        for ( ; imgCol < 0 ; ++currCol, ++imgCol, ++pMapTo)
        {
            *pMapTo = aPixVal;
        }


        pMapFrom = anImg.pPixMap() + (rowFrom * anImg.width()) + imgCol;
        for ( ;
              (currCol < _width) && (imgCol < anImg.width()) ;
              ++currCol, ++imgCol, ++pMapTo, ++pMapFrom)
        {
            *pMapTo = *pMapFrom;
        }

        // Fill non-overlaping rows (if any)
        qgFill(pMapTo, _width - currCol, aPixVal);
    } // END copy of the significant pixels

    // Fill non-overlaping rows (if any)
    for ( ; rowTo < _height ; ++rowTo)
    {
        qgFill(pMapTo, _width, aPixVal);
    }
}


// -------------------------------------------------------------------


} // namespace qgar
