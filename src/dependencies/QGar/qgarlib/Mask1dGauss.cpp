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
 * @file Mask1dGauss.cpp
 *
 * @brief Implementation of class qgar::Mask1dGauss.
 *
 * See file Mask1dGauss.h for the interface.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date   July 03, 2001  10:33
 * @since  qgar 1.0
 */

// The following code is an adaptation of code written by Carsten Steger
// at TU Muenchen, Germany. Here is the copyright notice from his code:
//+----------------------------------------------------------------------+
//| Copyright (C) 1996 Carsten Steger                                    |
//|                                                                      |
//| This program is free software; you can redistribute it and/or modify |
//| it under the terms of the GNU General Public License as published by |
//| the Free Software Foundation; either version 2, or (at your option)  |
//| any later version.                                                   |
//|                                                                      |
//| This program is distributed in the hope that it will be useful, but  |
//| WITHOUT ANY WARRANTY; without even the implied warranty of           |
//| MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    |
//| General Public License for more details.                             |
//|                                                                      |
//| You should have received a copy of the GNU General Public License    |
//| along with this program; if not, write to the Free Software          |
//| Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.            |
//+----------------------------------------------------------------------+



// QGAR
#include "Mask1dGauss.h"
#include "math.h"



using namespace std;



namespace qgar
{


// LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
//
// L O C A L   A U X I L I A R I E S
//
// LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL

namespace
{


double MASK1DGAUSS_phi0(double aX, double aSigma)
{
  return 0.5 * qgErfc((-aX / aSigma) / Math::QG_SQRT_2);
}


} // unnamed namespace

// LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL




// -------------------------------------------------------------------
// C O N S T R U C T O R S 
// -------------------------------------------------------------------

// COPY CONSTRUCTOR

Mask1dGauss::Mask1dGauss(const Mask1dGauss& aMask)

  : DMask1d(aMask)

{
  // VOID
}


//INITIALIZE FROM GIVEN SIGMA

Mask1dGauss::Mask1dGauss(double aSigma)
{
  // Error < 0.001 on each side

  double limit = ceil(3.09023230616781 * aSigma);
  int    n     = (int) ceil(limit);

  width_     = (2 * n) + 1;         // Width of mask [-n..n]
  pCoeffMap_ = new double[width_];  // Allocate space for mask

  // Fill [-(n-1)..(n-1)]

  double* pm = pCoeffMap_ + 1;
  for (int idx = -n + 1 ; idx <= (n - 1) ; ++idx)
    {
      *pm++ =   MASK1DGAUSS_phi0( 0.5 - idx, aSigma)
	      - MASK1DGAUSS_phi0(-0.5 - idx, aSigma);
    }

  // Fill extremities
  *pCoeffMap_ = 1. - MASK1DGAUSS_phi0(n - 0.5, aSigma);  // -n
  *pm         =      MASK1DGAUSS_phi0(0.5 - n, aSigma);  // +n
}


// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------


Mask1dGauss::~Mask1dGauss()
{
  // VOID
}


// -------------------------------------------------------------------
// O P E R A T O R S 
// -------------------------------------------------------------------

// ASSIGNMENT
// PERFORM A DEEP COPY

Mask1dGauss& Mask1dGauss::operator=(const Mask1dGauss& aMask)
{
  DMask1d::operator=(aMask);
  return *this;
}
 
// -------------------------------------------------------------------


} // namespace qgar
