#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include "../../Portability.h"
#include <QString>
#include <stdexcept>

#define VERSION "1.0.0-beta"

// Weights
#define DEFAULT_C_V_CONST_ 1.0
#define DEFAULT_C_E_CONST_ 1.0
#define DEFAULT_S_V_CONST_ 0.0
#define DEFAULT_S_E_CONST_ 0.0

#define DEFAULT_C_V 0.0
#define DEFAULT_C_E 0.0
#define DEFAULT_S_V 1.0
#define DEFAULT_S_E 1.0

#define CONST_LABEL "_const_"

// Automatic configuration
#define GEM_AUTO "_auto_"

// Solver precision
#define PRECISION 6

// Math
#define PI 3.14159265358979323846264338328
DLL_EXPORT extern double precision;
DLL_EXPORT double roundAtPrecision(double number);
DLL_EXPORT long roundToNearestInt(double number);

// Error handling
DLL_EXPORT void GEM_exception(const QString &errorString);

#endif /* __CONSTANTS_H__ */
