/*
  Algorithms for fast computation of Zernike moments and their numerical stability
  Chandan Singh and Ekta Walia, Image and Vision Computing 29 (2011) 251–259

  Implemented from pseudo-code by Ilya Goldberg 2011-04-27
*/
#ifndef __ZERNIKE_H__
#define __ZERNIKE_H__

#include <QList>
#include <cmath>
#include <cfloat>
#include "../Core/Constants.h"
#include "qgarlib/GenImage.h"

using namespace qgar;

#define MAX_ORDER 32

QList<double> zernike2D(const BinaryImage &im, int order = 8, double rad = 0);

#endif /*__ZERNIKE_H__*/
