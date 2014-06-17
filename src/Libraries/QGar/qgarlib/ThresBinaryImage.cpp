/*---------------------------------------------------------------------*
 | Library QgarLib, graphics analysis and recognition                  |
 | Copyright (C) 2005  Qgar Project, LORIA                             |
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


/**
 * @file  ThresBinaryImage.cpp
 * @brief Implementation of class qgar::ThresBinaryImage.
 *
 * See file ThresBinaryImage.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   July 4, 2005  09:23
 * @since  Qgar 2.2
 */


// For RCS/CVS use: Do not delete
/* $Id: ThresBinaryImage.cpp,v 1.1 2005/10/14 17:05:48 masini Exp $ */



// QGAR
#include "GenImage.h"
#include "ThresBinaryImage.h"



namespace qgar
{

// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------


// CONSTRUCTOR

ThresBinaryImage::ThresBinaryImage(const GreyLevelImage& anImg, int aThres)

  : BinaryImage(anImg.width(),anImg.height())

{
  // Pointer to the pixel map of the given image
  GreyLevelImage::pointer pMapSource =  anImg.pPixMap();

  // Pointer to the pixel map of the binarized image
  BinaryImage::pointer pMapRes = pPixMap();

  int size = _width * _height;
  
  for (int iCnt = 0; iCnt < size ; ++iCnt, ++pMapRes, ++pMapSource)
    {
      *pMapRes = (*pMapSource < aThres) ? QGE_BW_BLACK : QGE_BW_WHITE;
    }  
}


// ---------------------------------------------------------------------
// V I R T U A L   D E S T R U C T O R
// ---------------------------------------------------------------------


ThresBinaryImage::~ThresBinaryImage()
{
  // VOID
}

// ---------------------------------------------------------------------
// G L O B A L   F U N C T I O N S
// ---------------------------------------------------------------------


ThresBinaryImage
qgThresBinarization(const GreyLevelImage& anImg, int aThres)
{
  return ThresBinaryImage(anImg, aThres);
}


// ----------------------------------------------------------------------


} // namespace qgar
