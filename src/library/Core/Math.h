#ifndef GEMPP_MATH_H
#define GEMPP_MATH_H

#include <cmath>
#include "Portability.h"

#define GEMPP_PRECISION 6
#define GEMPP_PI 3.14159265358979323846264338328

/**
 * @brief The absolute precision 10^(-GEMPP_PRECISION) 
 */
DLL_EXPORT extern double precision;

/**
 * @brief Rounds a double variable using a precision of GEMPP_PRECISION decimals
 * @param number the number to round
 */
DLL_EXPORT double roundAtPrecision(double number);

/**
 * @brief Rounds a double variable to the nearest integer
 * @param number the number to round
 */
DLL_EXPORT long roundToNearestInt(double number);

#endif /* GEMPP_MATH_H */
