#ifndef GEMPP_CONSTANTS_H
#define GEMPP_CONSTANTS_H

#include "Math.h"
#include "Exception.h"

#define GEMPP_VERSION "1.0.0-beta"

#define GEMPP_CONST_LABEL "_const_"

// Automatic configuration
#define GEMPP_AUTO "_auto_"

// XML
#define GEMPP_XSI_NS "http://www.w3.org/2001/XMLSchema-instance"
#define GEMPP_WEIGHTS_NS "http://julien.lerouge.me/GEM++/weights"
#define GEMPP_WEIGHTS_NS_LOC "http://julien.lerouge.me/GEM++/weights.xsd"

/** @brief The standard filename extensions of the image formats that are accepted by COLILOC. */
#define IMG_FORMATS "*.bmp *.jp2 *.jpg *.jpeg *.pbm *.pgm *.png *.ppm *.tif *.tiff"

/** @brief The time a notification message will be displayed in the GUI before it disappear. */
#define MESSAGE_TIMEOUT 3000

#endif /* GEMPP_CONSTANTS_H */
