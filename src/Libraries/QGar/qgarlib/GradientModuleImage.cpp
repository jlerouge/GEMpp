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
 * @file GradientModuleImage.cpp
 *
 * @brief Implementation of class qgar::GradientModuleImage.
 *
 * See file GradientModuleImage.h for the interface.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   July 3, 2001  15:24
 * @since  Qgar 1.0
 */



// STD
#include <cmath>
// QGAR
#include "AbstractGradientImage.h"
#include "GenImage.h"
#include "GradientModuleImage.h"



using namespace std;



namespace qgar
{


// -------------------------------------------------------------------
// C O N S T R U C T O R
// -------------------------------------------------------------------


GradientModuleImage::GradientModuleImage(AbstractGradientImage& aGradImg)

  : FloatImage(aGradImg.dxImg())

{
  *this *= aGradImg.dxImg();  // x*x

  FloatImage* yImg = new FloatImage(aGradImg.dyImg());
  *yImg *= aGradImg.dyImg();  // y*y

  *this += *yImg;             // x*x + y*y

  delete yImg;

  float* p    = _pPixMap;
  float* pEnd = _pPixMap + (_width * _height);

  for (/* VOID */ ; p < pEnd ; ++p)
    {
      *p = (float) sqrt((double) *p);  // sqrt(x*x + y*y)
    }
}


// -------------------------------------------------------------------


} // namespace qgar
