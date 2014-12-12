#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include "../../Portability.h"
#include <QString>
#include <stdexcept>

#define VERSION "1.0.0-beta"

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

// XML
#define XSI_NS "http://www.w3.org/2001/XMLSchema-instance"
#define GEM_WEIGHTS_NS "http://julien.lerouge.me/GEM++/weights"
#define GEM_WEIGHTS_NS_LOC "http://julien.lerouge.me/GEM++/weights.xsd"

#endif /* __CONSTANTS_H__ */
