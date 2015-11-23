/*
  Algorithms for fast computation of Zernike moments and their numerical stability
  Chandan Singh and Ekta Walia, Image and Vision Computing 29 (2011) 251–259

  Implemented from pseudo-code by Ilya Goldberg 2011-04-27
*/
#ifndef GEMPP_ZERNIKE_H
#define GEMPP_ZERNIKE_H

#include <QList>
#include <cmath>
#include <cfloat>
#include "Core/Constants.h"
#include "qgarlib/GenImage.h"

using namespace qgar;

#define GEMPP_MAX_ORDER 32

/**
 * @brief Computes the 2D Zernike invariant moments of binary shapes.
 * @param order the Zernike polynomial order (must be less than GEMPP_MAX_ORDER)
 * @param rad the radius used for normalization
 * @return the zernike moments
 */
QList<double> zernike2D(const BinaryImage &im, int order = 8, double rad = 0);

#endif /* GEMPP_ZERNIKE_H */
