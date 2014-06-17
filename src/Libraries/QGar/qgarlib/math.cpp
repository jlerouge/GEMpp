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
 * @file  math.cpp
 * @brief Implementation of utilities for mathematical operations.
 *
 * See file math.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   December 06, 2004  18:08
 * @since  Qgar 2.2
 */



// STD
#include <limits>
// QGAR
#include "math.h"



using namespace std;



namespace qgar
{


/*---------------------------------------------------------------------*
 |                                                                     |
 |                    C  L  A  S  S      M  A  T  H                    |
 |                                                                     |
 *---------------------------------------------------------------------*/


// ---------------------------------------------------------------------
// CONSTANTS TO PRESERVE COMPATIBILITY WITH WINDOWS OS
// ----------------------------------------------------------------------


// Maximum double number
const double
Math::QG_DOUBLE_MAX = 1.79769313486231570e+308;

// Minimum double number
const double
Math::QG_DOUBLE_MIN = 4.94065645841246544e-324;

// Maximum float number.
const float
Math::QG_FLOAT_MAX  = 3.40282346638528860e+38;

// Minimum double number
const float
Math::QG_FLOAT_MIN  = 1.40129846432481707e-45;


// ----------------------------------------------------------------------
// CONSTANTS RELATED TO E
// ----------------------------------------------------------------------

// ALL VALUES COMPUTED BY MAPLE
// ============================


// E            = 2.718281828459045235360287471352662497757
const double
Math::QG_E      = 2.7182818284590452354;


// log_2(E)     = 1.442695040888963407359924681001892137426
const double
Math::QG_LOG2E  = 1.4426950408889634074;

// log_10(E)    = 0.434294481903251827651128918916605082294
const double
Math::QG_LOG10E = 0.43429448190325182765;

// Log_E(2)     = 0.693147180559945309417232121458176568075
const double
Math::QG_LN2    = 0.69314718055994530942;

// Log_E(10)    = 2.302585092994045684017991454684364207601
const double
Math::QG_LN10   = 2.30258509299404568402;


// ----------------------------------------------------------------------
// CONSTANTS RELATED TO PI
// ----------------------------------------------------------------------

// ALL VALUES COMPUTED BY MAPLE


// PI               = 3.141592653589793238462643383279502884197
const double
Math::QG_PI         = 3.14159265358979323846;

// PI/2             = 1.570796326794896619231321691639751442098
const double
Math::QG_PI_2       = 1.57079632679489661923; 

// PI/3             = 1.047197551196597746154214461093167628066
const double
Math::QG_PI_3       = 1.04719755119659774615;

// PI/4             = 0.7853981633974483096156608458198757210492
const double
Math::QG_PI_4       = 0.78539816339744830962;

// PI/6             = 0.5235987755982988730771072305465838140329
const double
Math::QG_PI_6       = 0.52359877559829887308;

// 2*PI             = 6.283185307179586476925286766559005768394
const double
Math::QG_2PI        = 6.28318530717958647692;


// sqrt(2*PI)       = 2.506628274631000502415765284811045253008
const double
Math::QG_SQRT_2PI   = 2.50662827463100050242;

// sqrt(PI)         = 1.772453850905516027298167483341145182798
const double
Math::QG_SQRT_PI    = 1.77245385090551602730;


// 1/(2*PI)         = 0.1591549430918953357688837633725143620344
const double
Math::QG_1_2PI      = 0.15915494309189533577;

// 1/PI             = 0.3183098861837906715377675267450287240689
const double
Math::QG_1_PI       = 0.31830988618379067154; 

// 1/sqrt(PI)       = 0.5641895835477562869480794515607725858441
const double
Math::QG_1_SQRT_PI  = 0.56418958354775628695;

// 1/sqrt(2*PI)     = 0.3989422804014326779399460599343818684758
const double
Math::QG_1_SQRT_2PI = 0.39894228040143267794;


// 2/PI             = 0.6366197723675813430755350534900574481378
const double
Math::QG_2_PI       = 0.63661977236758134308;

// 2/sqrt(PI)       = 1.1283791670955125738961589031215451716881
const double
Math::QG_2_SQRT_PI  = 1.12837916709551257390;


// ----------------------------------------------------------------------
// CONSTANTS RELATED TO SQRT(2)
// ----------------------------------------------------------------------

// ALL VALUES COMPUTED BY MAPLE


// sqrt(2)           = 1.414213562373095048801688724209698078570
const double
Math::QG_SQRT_2      = 1.41421356237309504880;

// 1/sqrt(2)         = 0.7071067811865475244008443621048490392847
const double
Math::QG_1_SQRT_2    = 0.70710678118654752440; 


// ----------------------------------------------------------------------
// CONSTANTS RELATED TO SQRT(3)
// ----------------------------------------------------------------------

// ALL VALUES COMPUTED BY MAPLE


// sqrt(3)           = 1.732050807568877293527446341505872366943
const double
Math::QG_SQRT_3      = 1.73205080756887729353;

// 1/sqrt(3)         = 0.5773502691896257645091487805019574556475
const double
Math::QG_1_SQRT_3    = 0.57735026918962576451;


// ----------------------------------------------------------------------
// CONSTANTS FOR CONVERSIONS
// ----------------------------------------------------------------------

// ALL VALUES COMPUTED BY MAPLE


// To convert radians to degrees: 180 / PI
const double
Math::QG_RADIANS_TO_DEGREES = 57.2957795130823208768;

// To convert degrees to radians: PI / 180
const double
Math::QG_DEGREES_TO_RADIANS =  0.01745329251994329577;


// ----------------------------------------------------------------------
// LIMITS
// ----------------------------------------------------------------------


// Square root of the maximum positive integer coded on 4 bytes
const int
Math::QG_SQRT_MAX_INT16b = 46340;


// ---------------------------------------------------------------------
// THRESHOLDS FOR (IN)EQUALITY TESTS
// ---------------------------------------------------------------------


// Threshold for double numbers
double
Math::s_epsilon_double_ = 0.0001;


// Threshold for float numbers
float
Math::s_epsilon_float_ = 0.0001f;


// Threshold for integer numbers
int
Math::s_epsilon_int_ = 1;

// Threshold for angles in radians
// 0.005 radian ~ 0.25 degree
double
Math::s_epsilon_radian_ = 0.005;

// Threshold for angles in degrees
// 0.25 degree ~ 0.005 radian
double
Math::s_epsilon_degree_ = 0.25;


// ---------------------------------------------------------------------
// THRESHOLDS FOR NUMERIC CALCULUS
// ---------------------------------------------------------------------


// Relative error for floating point numeric calculus
// The default value corresponds to 12 significant figures
double
Math::s_rel_error_fp_ = 1.e-12;




/***********************************************************************
 *                                                                     *
 *                  G L O B A L   F U N C T I O N S                    *
 *                                                                     *
 ***********************************************************************/



// *********************************************************************
// ERROR FUNCTIONS
// *********************************************************************


// Code inspired by various pieces of free code


// COMPUTE THE ERROR FUNCTION OF THE ARGUMENT
//
// erf(x) = 1 - erfc(x)
//        = 2/sqrt(pi) * integral_0^x e^{-t^2} dt
//
// -1 <= erf(x) <= 1
//
// For |x| <= 2.2, the integral is calculated as:
//
//  x - x^3/3 + x^5/(5*2!) - x^7/(7*3!) + ...
//
double
qgErf(double x)
{
  // Use erfc(x) when |x| > 2.2
  if (fabs(x) > 2.2)
    {
      return 1. - qgErfc(x);
    }

  double sum  = x;
  double term = x;
  double xsqr = x * x;

  int iCnt = 1;

  do
    {
      term *= xsqr / iCnt;
      sum -= term / ((2 * iCnt) + 1);
      ++iCnt;

      term *= xsqr / iCnt;
      sum += term / ((2 * iCnt) + 1);
      ++iCnt;
    }
  while (fabs(term/sum) > Math::relError());

  return Math::QG_2_SQRT_PI * sum;
}


// COMPUTE THE COMPLEMENTARY ERROR FUNCTION OF THE ARGUMENT
//
// erfc(x) = 1 - erf(x)
//         = 2/sqrt(pi) * integral_x^infinity  e^{-t^2} dt
//
// 0 <= erfc(x) <= 2
//
// For x >= 2.2, erfc(x) is calculated as:
//
//    e^{-x^2}/sqrt(pi)
//  * 
//    (1 / (x + (2/2 / (x + (3/2 / x + (4/2 / (x +...)))))))
//
double
qgErfc(double x)
{
  // Use erf(x) when |x| < 2.2
  if (fabs(x) < 2.2)
    {
      return 1. - qgErf(x);
    }

  // The calculus hereafter is only valid for x >= 0
  //
  // It would be certainly better to use function signbit()
  // from <cmath>, but this function is not (yet) in the standard
  // if (signbit(x))
  if (x < 0.)
    {
      return 2.0 - qgErfc(-x);
    }

  // Numerator
  double n = 1.;
  // Last two convergent numerators
  double n1 = 1.;
  double n2 = x;
  // Last two convergent denominators
  double d1 = x;
  double d2 = (x * x) + 0.5;
  // Last two convergents quotients: n1/d1 and n2/d2
  double nd1;
  double nd2 = n2 / d2;

  do
    {
      double tmp = (n1 * n) + (n2 * x);
      n1 = n2;
      n2 = tmp;

      tmp = (d1 * n) + (d2 * x);
      d1 = d2;
      d2 = tmp;

      nd1 = nd2;
      nd2 = n2 / d2;

      n += 0.5;
    }
  while ((fabs(nd1 - nd2) / nd2) > Math::relError());

  return Math::QG_1_SQRT_PI * exp(-x * x) * nd2;
}


// *********************************************************************

} // namespace qgar
