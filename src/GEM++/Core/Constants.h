#ifndef GEMPP_CONSTANTS_H
#define GEMPP_CONSTANTS_H

#include "../../Portability.h"
#include <QString>
#include <stdexcept>

#define GEMPP_VERSION "1.0.0-beta"

#define GEMPP_CONST_LABEL "_const_"

// Automatic configuration
#define GEMPP_GEM_AUTO "_auto_"

// Solver precision
#define GEMPP_PRECISION 6

// Math
#define GEMPP_PI 3.14159265358979323846264338328
DLL_EXPORT extern double precision;
DLL_EXPORT double roundAtPrecision(double number);
DLL_EXPORT long roundToNearestInt(double number);

// Error handling
DLL_EXPORT void GEM_exception(const QString &errorString);

// XML
#define GEMPP_XSI_NS "http://www.w3.org/2001/XMLSchema-instance"
#define GEMPP_GEM_WEIGHTS_NS "http://julien.lerouge.me/GEM++/weights"
#define GEMPP_GEM_WEIGHTS_NS_LOC "http://julien.lerouge.me/GEM++/weights.xsd"

#endif /* GEMPP_CONSTANTS_H */
