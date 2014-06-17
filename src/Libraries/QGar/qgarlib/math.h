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


#ifndef __MATH_H_INCLUDED__
#define __MATH_H_INCLUDED__


/**
 * @file   math.h
 * @brief  Definitions of global utilities for mathematical operations.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   December 06, 2004  18:08
 * @since  Qgar 2.2
 */


// For RCS/CVS use: Do not delete
/* $Id: math.h,v 1.8 2007/02/14 17:34:06 masini Exp $ */



// STD
#include <cmath>
#include <cstdlib>



using namespace std;



namespace qgar
{



/*---------------------------------------------------------------------*
 |                                                                     |
 |                    C  L  A  S  S      M  A  T  H                    |
 |                                                                     |
 *---------------------------------------------------------------------*/



/**
 * @ingroup GLOB_MATH
 *
 * @class Math math.h "qgarlib/math.h"
 *
 * @brief Global constants and thresholds,
 *   implemented as static data members of the class.
 *
 * The class is just a collection of constants and therefore cannot be
 * instanciated.
 *
 * All mathematical constants have been computed using
 * <a href="http://www.maplesoft.com/" target="_blank">Maple</a>.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   February 21, 2003  17:50
 * @since  Qgar 2.0
 */
class Math
{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  // =================================================================
  /** @name Constants to preserve compatibility with Windows OS
      <b>Note:</b> Most of these constants are defined in math.h when
      using a Unix/Linux OS, but are not available when using
      a Windows OS.
  */
  // =================================================================
  //@{
  /**
   * @brief Maximum <b>double</b> number.
   *
   * @warning Only valid for IEEE-754 compliant architectures.
   */
  static const double QG_DOUBLE_MAX;

  /**
   * @brief Minimum  <b>double</b> number.
   *
   * @warning Only valid for IEEE-754 compliant architectures.
   */
  static const double QG_DOUBLE_MIN;

  /**
   * @brief Maximum  <b>float</b> number.
   *
   * @warning Only valid for IEEE-754 compliant architectures.
   */
  static const float QG_FLOAT_MAX;

  /**
   * @brief Minimum  <b>float</b> number.
   *
   * @warning Only valid for IEEE-754 compliant architectures.
   */
  static const float QG_FLOAT_MIN;
  //@}


  /** @name Constants related to e */
  //        ======================
  //@{

  /**
   * @brief Value of \f$e\f$
   *
   * @since  Qgar 2.2
   */
  static const double QG_E;

  /**
   * @brief Value of \f$\log_2{e}\f$
   *
   * @since  Qgar 2.2
   */
  static const double QG_LOG2E;

  /**
   * @brief  Value of \f$\log_{10}{e}\f$
   *
   * @since  Qgar 2.2
   */
  static const double QG_LOG10E;

  /**
   * @brief  Value of \f$\ln{2}\f$
   *
   * @since  Qgar 2.2
   */
  static const double QG_LN2;

  /**
   * @brief  Value of \f$\ln{10}\f$
   *
   * @since  Qgar 2.2
   */
  static const double QG_LN10;

  //@}


  /** @name Constants related to Pi */
  //        =======================
  //@{

  /**
   * @brief Value of \f$2\pi\f$
   */
  static const double QG_2PI;

  /**
   * @brief Value of \f$\pi\f$
   */
  static const double QG_PI;

  /**
   * @brief Value of \f$\frac{\pi}{2}\f$
   */
  static const double QG_PI_2;

  /**
   * @brief Value of \f$\frac{\pi}{3}\f$
   */
  static const double QG_PI_3;

  /**
   * @brief Value of \f$\frac{\pi}{4}\f$
   */
  static const double QG_PI_4;

  /**
   * @brief Value of \f$\frac{\pi}{6}\f$
   */
  static const double QG_PI_6;

  /**
   * @brief Value of \f$\sqrt{2\pi}\f$
   */
  static const double QG_SQRT_2PI;

  /**
   * @brief Value of \f$\sqrt{\pi}\f$
   */
  static const double QG_SQRT_PI;

  /**
   * @brief Value of \f$\frac{1}{2\pi}\f$
   */
  static const double QG_1_2PI;

  /**
   * @brief Value of \f$\frac{1}{\pi}\f$
   */
  static const double QG_1_PI;

  /**
   * @brief Value of \f$\frac{1}{\sqrt{2\pi}}\f$
   */
  static const double QG_1_SQRT_2PI;

  /**
   * @brief Value of \f$\frac{1}{\sqrt{\pi}}\f$
   */
  static const double QG_1_SQRT_PI;

  /**
   * @brief Value of \f$\frac{2}{\pi}\f$
   *
   * @since  Qgar 2.2
   */
  static const double QG_2_PI ;

  /**
   * @brief Value of \f$\frac{2}{\sqrt{\pi}}\f$.
   *
   * @since  Qgar 2.2
   */
  static const double QG_2_SQRT_PI;

  //@}


  /** @name Constants related to sqrt(2) */
  //        ============================
  //@{

  /**
   * @brief Value of \f$\sqrt{2}\f$
   */
  static const double QG_SQRT_2;

  /**
   * @brief Value of \f$\frac{1}{\sqrt{2}}\f$
   */
  static const double QG_1_SQRT_2;

  //@}


  /** @name Constants related to sqrt(3) */
  //        ============================
  //@{

  /**
   * @brief Value of \f$\sqrt{3}\f$
   */
  static const double QG_SQRT_3;

  /**
   * @brief Value of \f$\frac{1}{\sqrt{3}}\f$
   */
  static const double QG_1_SQRT_3;

  //@}


  /** @name Constants for conversions */
  //        =========================
  //@{

  /**
   * @brief Mutiplication factor to convert
   *   radians to degrees (\f$\frac{180}{\Pi}\f$).
   *
   * @since Qgar 2.2
   */
  static const double QG_RADIANS_TO_DEGREES;

  /**
   * @brief Mutiplication factor to convert
   *   degrees to radians (\f$\frac{\Pi}{180}\f$).
   *
   * @since Qgar 2.2
   */
  static const double QG_DEGREES_TO_RADIANS;

  //@}


  /** @name Constants related to limits */
  //        ===========================
  //@{

  /**
   * @brief Square root of the maximum positive integer
   *   coded on 16 bits (4 bytes: <b>0x7fffffff</b>).
   */
  static const int QG_SQRT_MAX_INT16b;

  //@}


  /** @name Access to thresholds for numeric calculus */
  //        =========================================
  //@{

  /**
   * @brief Get relative error
   *   for floating point numeric calculus.
   *
   * @since  Qgar 2.2
   */
  static double inline relError();

  //@}


  /** @name Access to thresholds for (in)equality tests */
  //        ===========================================
  //@{

  /**
   * @brief Get threshold for equality tests
   *   between <b>double</b> numbers.
   */
  static double inline epsilonD();

  /**
   * @brief Get threshold for equality tests
   *   between <b>float</b> numbers.
   */
  static float inline epsilonF();

  /**
   * @brief Get threshold for equality tests
   *   between <b>int</b> numbers.
   */
  static int inline epsilonI();

  /**
   * @brief Get threshold for equality tests
   *   between angles in radians.
   */
  static double inline epsilonRadian();

  /**
   * @brief Get threshold for equality tests
   *   between angles in degrees.
   */
  static double inline epsilonDegree();

  //@}


  /** @name Set thresholds for numeric calculus */
  //        ===================================
  //@{

  /**
   * @brief Set relative error
   *   for floating point numeric calculus.
   *
   * @param aRelError  new value of the relative error
   *
   * @since  Qgar 2.2
   */
  static void inline setRelError(double aRelError);

  //@}


  /** @name Set thresholds for (in)equality tests */
  //        =====================================
  //@{

  /**
   * @brief Set threshold for equality tests
   *   between <b>double</b> numbers.
   *
   * @param anEpsilon new value of the threshold
   */
  static void inline setEpsilonD(double anEpsilon);

  /**
   * @brief Set threshold for equality test
   *   between <b>float</b> numbers.
   *
   * @param anEpsilon new value of the threshold
   */
  static void inline setEpsilonF(float anEpsilon);

  /**
   * @brief Set threshold for equality tests
   *   between <b>int</b> numbers.
   *
   * @param anEpsilon new value of the threshold
   */
  static void inline setEpsilonI(int anEpsilon);

  /**
   * @brief Set threshold for equality tests
   *   between angles in radians.
   *
   * @param anEpsilon new value of the threshold
   */
  static void inline setEpsilonRadian(double anEpsilon);

  /**
   * @brief Set threshold for equality tests
   *   between angles in degrees.
   *
   * @param anEpsilon new value of the threshold
   */
  static void inline setEpsilonDegree(double anEpsilon);

  //@}


// -------------------------------------------------------------------
// P R I V A T E   M E M B E R S
// -------------------------------------------------------------------
private:

  /** @name Constructors */
  //        ============
  //@{

  /**
   * @brief Disabled default constructor.
   *
   * @warning The constructor belongs to the private section
   * so that the class cannot be instantiated.
   */
  Math()
  {
    // VOID
  }

  //@}


  /** @name Thresholds for (in)equality tests */
  //        =================================
  //@{

  /**
   * @brief Threshold to test (in)equality between double numbers
   *   (default <b>1.e-4</b>).
   */
  static double s_epsilon_double_;

  /**
   * @brief Threshold to test (in)equality between float numbers
   *   (default <b>1.e-4</b>).
   */
  static float s_epsilon_float_;
  
  /**
   * @brief Threshold to test (in)equality between integer numbers
   *   (default <b>1</b>).
   */
  static int s_epsilon_int_;

  /**
   * @brief Threshold for testing (in)equality between angles in radians
   *   (default <b>0.005 radian</b> \f$\approx\f$ 0.25 degree).
   */
  static double s_epsilon_radian_;

  /**
   * @brief Threshold for testing (in)equality between angles in degrees
   *   (default <b>0.25 degree</b>).
   */
  static double s_epsilon_degree_;

  //@}


  /** @name Thresholds for numeric calculus */
  //        ===============================
  //@{

  /**
   * @brief Relative error for floating point numeric calculus
   *   (default <b>1.e-12</b>).
   *
   * The default value corresponds to 12 significant figures.
   * It can be adjusted to trade off between accuracy and speed:
   * See functions qgar::Math::relError and qgar::Math::setRelError.
   *
   * @warning
   * Assuming a usual 52-bit mantissa in a <b>double</b> number,
   * the lowest value of this threshold should be <b>1.e-15</b>
   *
   * @since  Qgar 2.2
   */
  static double s_rel_error_fp_;

  //@}


// -------------------------------------------------------------------

}; // class Math




// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// I N L I N E    F U N C T I O N S    I M P L E M E N T A T I O N
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII


// =========================================
// ACCESS TO THRESHOLDS FOR NUMERIC CALCULUS
// =========================================


// GET RELATIVE ERROR FOR FLOATING POINT NUMERIC CALCULUS

double
inline Math::relError()
{
  return s_rel_error_fp_;
}


// ===========================================
// Access to thresholds for (in)equality tests
// ===========================================


// GET THRESHOLD FOR EQUALITY TESTS BETWEEN double NUMBERS

double
inline Math::epsilonD()
{
  return s_epsilon_double_;
}


// GET THRESHOLD FOR EQUALITY TESTS BETWEEN float NUMBERS

float
inline Math::epsilonF()
{
  return s_epsilon_float_;
}


// GET THRESHOLD FOR EQUALITY TESTS BETWEEN int NUMBERS

int
inline Math::epsilonI()
{
  return s_epsilon_int_;
}


// GET THRESHOLD FOR EQUALITY TESTS BETWEEN ANGLES IN RADIANS

double
inline Math::epsilonRadian()
{
  return s_epsilon_radian_;
}


// GET THRESHOLD FOR EQUALITY TESTS BETWEEN ANGLES IN DEGREES

double
inline Math::epsilonDegree()
{
  return s_epsilon_degree_;
}


// ===================================
// SET THRESHOLDS FOR NUMERIC CALCULUS
// ===================================


// SET RELATIVE ERROR FOR FLOATING POINT NUMERIC CALCULUS

void
inline Math::setRelError(double aRelError)
{
  s_rel_error_fp_ = aRelError;
}


// =====================================
// SET THRESHOLDS FOR (IN)EQUALITY TESTS
// =====================================


// SET THRESHOLD FOR EQUALITY TESTS BETWEEN double NUMBERS

void
inline Math::setEpsilonD(double anEpsilon)
{
  s_epsilon_double_ = anEpsilon;
}


// SET THRESHOLD FOR EQUALITY TEST BETWEEN float NUMBERS

void
inline Math::setEpsilonF(float anEpsilon)
{
  s_epsilon_float_ = anEpsilon;
}


// SET THRESHOLD FOR EQUALITY TESTS BETWEEN int NUMBERS

void
inline Math::setEpsilonI(int anEpsilon)
{
  s_epsilon_int_ = anEpsilon;
}


// SET THRESHOLD FOR EQUALITY TESTS BETWEEN ANGLES IN RADIANS

void
inline Math::setEpsilonRadian(double anEpsilon)
{
  s_epsilon_radian_ = anEpsilon;
}


// SET THRESHOLD FOR EQUALITY TESTS BETWEEN ANGLES IN DEGREES

void
inline Math::setEpsilonDegree(double anEpsilon)
{
  s_epsilon_degree_ = anEpsilon;
}


// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// END OF INLINE FUNCTIONS IMPLEMENTATION
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII




/***********************************************************************
 *                                                                     *
 *                  G L O B A L   F U N C T I O N S                    *
 *                                                                     *
 ***********************************************************************/



// *********************************************************************
// C O M P A R I S O N S
// *********************************************************************


/** @name Global functions to test approximate equality between numbers */
//        =============================================================
//@{

/**
 * @ingroup GLOB_MATH
 *
 * @brief Is a double number approximately equal to zero?
 *
 * @param aDouble    a double number
 * @param anEpsilon  tolerance threshold aroud zero
 *                   (default qgar::Math::epsilonD())
 */
inline bool
qgEq0(double aDouble, double anEpsilon = Math::epsilonD())
{
  return (aDouble <= anEpsilon) && (aDouble >= -anEpsilon);
}


/**
 * @ingroup GLOB_MATH
 *
 * @brief Is a float number approximately equal to zero?
 *
 * @param aFloat     a float number
 * @param anEpsilon  tolerance threshold aroud zero
 *                   (default qgar::Math::epsilonF())
 */
inline bool
qgEq0(float aFloat, float anEpsilon = Math::epsilonF())
{
  return (aFloat <= anEpsilon) && (aFloat >= -anEpsilon);
}


/**
 * @ingroup GLOB_MATH
 *
 * @brief Is an integer number approximately equal to zero?
 *
 * @param anInt      an integer number
 * @param anEpsilon  tolerance threshold aroud zero (optional)
 *                   (default qgar::Math::epsilonI())
 */
inline bool
qgEq0(int anInt, int anEpsilon = Math::epsilonI())
{
  return (anInt <= anEpsilon) && (anInt >= -anEpsilon);
}


/**
 * @ingroup GLOB_MATH
 *
 * @brief Is an angle in radians approximately equal to zero?
 *
 * @param aRadian    an angle in radians
 * @param anEpsilon  tolerance threshold aroud zero
 *                   (default qgar::Math::epsilonRadian())
 */
inline bool
qgEq0Radian(double aRadian,
	    double anEpsilon = Math::epsilonRadian())
{
  return qgEq0(aRadian, anEpsilon);
}


/**
 * @ingroup GLOB_MATH
 *
 * @brief Is an angle in degrees approximately equal to zero?
 *
 * @param aDegree    an angle in degrees
 * @param anEpsilon  tolerance threshold aroud zero
 *                   (default qgar::Math::epsilonDegree())
 */
inline bool
qgEq0Degree(double aDegree,
	    double anEpsilon = Math::epsilonDegree())
{
  return qgEq0(aDegree, anEpsilon);
}

/**
 * @ingroup GLOB_MATH
 *
 * @brief Approximate equality between two double numbers.
 *
 * @param aDouble1   a double number
 * @param aDouble2   a double number
 * @param anEpsilon  tolerance threshold for equality
 *                   (default qgar::Math::epsilonD())
 */
inline bool
qgEq(double aDouble1,
     double aDouble2,
     double anEpsilon = Math::epsilonD())
{
  return qgEq0((aDouble1 - aDouble2), anEpsilon);
}


/**
 * @ingroup GLOB_MATH
 *
 * @brief Approximate equality between two float numbers.
 *
 * @param aFloat1    a float number
 * @param aFloat2    a float number
 * @param anEpsilon  tolerance threshold for equality
 *                   (default qgar::Math::epsilonF())
 */
inline bool
qgEq(float aFloat1,
     float aFloat2,
     float anEpsilon = Math::epsilonF())
{
  return qgEq0((aFloat1 - aFloat2), anEpsilon);
}


/**
 * @ingroup GLOB_MATH
 *
 * @brief Approximate equality between two integer numbers.
 *
 * @param anInt1     an integer number
 * @param anInt2     an integer number
 * @param anEpsilon  tolerance threshold for equality
 *                   (default qgar::Math::epsilonI())
 */
inline bool
qgEq(int anInt1, int anInt2, int anEpsilon = Math::epsilonI())
{
  return qgEq0((anInt1 - anInt2), anEpsilon);
}


/**
 * @ingroup GLOB_MATH
 *
 * @brief Approximate equality between two angles in radians.
 *
 * @param aRadian1   an angle in radians
 * @param aRadian2   an angle in radians
 * @param anEpsilon  tolerance threshold for equality
 *                   (default qgar::Math::epsilonRadian())
 */
inline bool
qgEqRadian(double aRadian1,
	   double aRadian2,
	   double anEpsilon = Math::epsilonRadian())
{
  return qgEq0((aRadian1 - aRadian2), anEpsilon);
}


/**
 * @ingroup GLOB_MATH
 *
 * @brief Approximate equality between two angles in degrees.
 *
 * @param aDegree1   an angle in degrees
 * @param aDegree2   an angle in degrees
 * @param anEpsilon  tolerance threshold for equality
 *                   (default qgar::Math::epsilonDegree())
 */
inline bool
qgEqDegree(double aDegree1,
	   double aDegree2,
	   double anEpsilon = Math::epsilonDegree())
{
  return qgEq0((aDegree1 - aDegree2), anEpsilon);
}

//@}


/** @name Global functions to test approximate inequality between numbers */
//        ===============================================================
//@{

/**
 * @ingroup GLOB_MATH
 *
 * @brief Is a double number approximately not equal to zero?
 *
 * @param aDouble   a double (number)
 * @param anEpsilon tolerance threshold aroud zero
 *                   (default qgar::Math::epsilonD())
 */
inline bool
qgNotEq0(double aDouble, double anEpsilon = Math::epsilonD())
{
  return !qgEq0(aDouble, anEpsilon);
}


/**
 * @ingroup GLOB_MATH
 *
 * @brief Is a float number approximately not equal to zero?
 *
 * @param aFloat     a float number
 * @param anEpsilon  tolerance threshold aroud zero
 *                   (default qgar::Math::epsilonF())
 */
inline bool
qgNotEq0(float aFloat, float anEpsilon = Math::epsilonF())
{
  return !qgEq0(aFloat, anEpsilon);
}


/**
 * @ingroup GLOB_MATH
 *
 * @brief Is an integer number approximately not equal to zero?
 *
 * @param anInt      an integer number
 * @param anEpsilon  tolerance threshold aroud zero
 *                   (default qgar::Math::epsilonI())
 */
inline bool
qgNotEq(int anInt, int anEpsilon = Math::epsilonI())
{
  return !qgEq0(anInt, anEpsilon);
}


/**
 * @ingroup GLOB_MATH
 *
 * @brief Is an angle in radians approximately not equal to zero?
 *
 * @param aRadian    an angle in radians
 * @param anEpsilon  tolerance threshold aroud zero
 *                   (default qgar::Math::epsilonRadian())
 */
inline bool
qgNotEq0Radian(double aRadian,
	       double anEpsilon = Math::epsilonRadian())
{
  return !qgEq0(aRadian, anEpsilon);
}


/**
 * @ingroup GLOB_MATH
 *
 * @brief Is an angle in degrees approximately not equal to zero?
 *
 * @param aDegree    an angle in degrees
 * @param anEpsilon  tolerance threshold aroud zero
 *                   (default qgar::Math::qgEDegree())
 */
inline bool
qgNotEq0Degree(double aDegree,
	       double anEpsilon = Math::epsilonDegree())
{
  return !qgEq0(aDegree, anEpsilon);
}


/**
 * @ingroup GLOB_MATH
 *
 * @brief Approximate inequality between two double numbers.
 *
 * @param aDouble1  a double (number)
 * @param aDouble2  a double (number)
 * @param anEpsilon tolerance threshold for inequality
 *                   (default qgar::Math::epsilonD())
 */
inline bool
qgNotEq(double aDouble1,
	double aDouble2,
	double anEpsilon = Math::epsilonD())
{
  return !qgEq(aDouble1, aDouble2, anEpsilon);
}


/**
 * @ingroup GLOB_MATH
 *
 * @brief Approximate inequality between two float numbers.
 *
 * @param aFloat1    a float number
 * @param aFloat2    a float number
 * @param anEpsilon  tolerance threshold for inequality
 *                   (default qgar::Math::epsilonF())
 */
inline bool
qgNotEq(float aFloat1,
	float aFloat2,
	float anEpsilon = Math::epsilonF())
{
  return !qgEq(aFloat1, aFloat2, anEpsilon);
}


/**
 * @ingroup GLOB_MATH
 *
 * @brief Approximate inequality between two integer numbers.
 *
 * @param anInt1     an integer number
 * @param anInt2     an integer number
 * @param anEpsilon  tolerance threshold for inequality
 *                   (default qgar::Math::epsilonI())
 */
inline bool
qgNotEq(int anInt1, int anInt2,
	int anEpsilon = Math::epsilonI())
{
  return !qgEq(anInt1, anInt2, anEpsilon);
}


/**
 * @ingroup GLOB_MATH
 *
 * @brief Approximate inequality between two angles in radians.
 *
 * @param aRadian1   an angle in radians
 * @param aRadian2   an angle in radians
 * @param anEpsilon  tolerance threshold for inequality
 *                   (default qgar::Math::epsilonRadian())
 */
inline bool
qgNotEqRadian(double aRadian1,
	      double aRadian2,
	      double anEpsilon = Math::epsilonRadian())
{
  return !qgEq(aRadian1, aRadian2, anEpsilon);
}


/**
 * @ingroup GLOB_MATH
 *
 * @brief Approximate inequality between two angles in degrees.
 *
 * @param aDegree1   an angle in degrees
 * @param aDegree2   an angle in degrees
 * @param anEpsilon  tolerance threshold for inequality
 *                   (default Math::epsilonDegree())
 */
inline bool
qgNotEqDegree(double aDegree1,
	      double aDegree2,
	      double anEpsilon = Math::epsilonDegree())
{
  return !qgEq(aDegree1, aDegree2, anEpsilon);
}

//@}


// *********************************************************************
// C O N V E R S I O N S
// *********************************************************************


/**  @name Global functions for conversion in radians and degrees */
//         ======================================================
//@{

/**
 * @ingroup GLOB_MATH
 *
 * @brief Convert from radians to degrees.
 *
 * @param aRadians   an angle in radians
 */
inline double
qgRadiansToDegrees(double aRadians)
{
  return aRadians * Math::QG_RADIANS_TO_DEGREES;
}

/**
 * @ingroup GLOB_MATH
 *
 * @brief Convert from degrees to radians.
 *
 * @param aDegrees  an angle in degrees
 */
inline double
qgDegreesToRadians(double aDegrees)
{
  return aDegrees * Math::QG_DEGREES_TO_RADIANS;
}

//@}


// *********************************************************************
// E R R O R   F U N C T I O N S
// *********************************************************************


/**  @name Global error functions */
//         ======================
//@{

  /**
   * @ingroup GLOB_MATH
   *
   * @brief Compute the error function of the argument.
   *
   * Same as C function <b>erf(x)</b> (from \<cmath\>),
   * which is not yet included in the ISO C standard.
   *
   * The relative error between the results provided by this function
   * and C function <b>erf(x)</b> is guaranteed to be less than
   * <b>1.e-11</b>, using the standard precision rate given by
   * function qgar::Math::relError.
   * This precision rate may be changed using function
   * qgar::Math::setRelError.
   * Note that, assuming a usual 52-bit mantissa in a <b>double</b>
   * number, the lowest rate should be <b>1.e-15</b>
   *
   * \f[
   * -1~~\leq
   * ~~erf(x) = 1 - erfc(x)
   * = \frac{2}{\sqrt{\pi}} \int_{0}^{x} e^{-t^2} dt
   * ~~\leq~~1
   * \f]
   *
   * For \f$\mid{x}\mid\leq 2.2\f$, the integral is calculated
   * using a series:
   *
   * \f[
   * x - \frac{x^3}{3} + \frac{x^5}{5 \times 2!} - \frac{x^7}{7 \times 3!} + ...
   * \f]
   *
   * @param x  a <b>double</b> number
   */
  double qgErf(double x);


  /**
   * @ingroup GLOB_MATH
   *
   * Same as C function <b>erfc(x)</b> (from \<cmath\>),
   * which is not yet included in the ISO C standard.
   *
   * The relative error between the results provided by this function
   * and C function <b>erfc(x)</b> is guaranteed to be less than
   * <b>1.e-11</b>, using the standard precision rate given by
   * function qgar::Math::relError.
   * This precision rate may be changed using function
   * qgar::Math::setRelError.
   * Note that, assuming a usual 52-bit mantissa in a <b>double</b>
   * number, the lowest rate should be <b>1.e-15</b>
   *
   * @brief Compute the complementary error function of the argument.
   *
   * \f[
   * 0~~\leq
   * ~~erfc(x) = 1 - erf(x)
   * = \frac{2}{\sqrt{\pi}} \int_{x}^{+\infty} e^{-t^2} dt
   * ~~\leq~~2
   * \f]
   *
   * For \f$x > 2.2\f$, \f$erfc(x)\f$ is calculated 
   * using a continued fraction:
   *
   * \f[
   * \frac{e^{-x^2}}{\sqrt{\pi}}\times \frac{1}{x + U_0}
   * ~~~with~~U_i = \frac{2 + \frac{i}{2}}{x + U_{i+1}}
   * \f]
   *
   * @param x  a <b>double</b> number
   */
  double qgErfc(double x);

//@}


// *********************************************************************
// M O D U L E   O F   A   N U M B E R
// *********************************************************************


/** @name Global functions to compute the module of a number */
//        ==================================================
//@{

/**
 * @ingroup GLOB_MATH
 *
 * @brief Module of given value (any type).
 *
 * @param aVal  a value
 */
template <class T>
inline T
qgAbs(T aVal)
{
  return ((aVal < static_cast<T>(0)) ? -aVal : aVal);
}

/**
 * @ingroup GLOB_MATH
 *
 * @brief Module of an <b>int</b> number.
 *
 * @param aNb  an <b>int</b> number
 */
template <>
inline int
qgAbs<int>(int aNb)
{
  return abs(aNb);
}

/**
 * @ingroup GLOB_MATH
 *
 * @brief Module of a <b>float</b> number.
 *
 * @param aNb  a <b>float</b> number
 */
template <>
inline float
qgAbs<float>(float aNb)
{
  return fabsf(aNb);
}

/**
 * @ingroup GLOB_MATH
 *
 * @brief Module of a <b>double</b> number.
 *
 * @param aNb  a <b>double</b> double
 */
template <>
inline double
qgAbs<double>(double aNb)
{
  return fabs(aNb);
}

//@}


/***********************************************************************
 *                                                                     *
 **********************************************************************/



} // namespace qgar


#endif /* __MATH_H_INCLUDED__ */
