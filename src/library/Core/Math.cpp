#include "Math.h"

double precision = pow(10, -GEMPP_PRECISION);

double roundAtPrecision(double number) {
    if(number < INFINITY)
        return floor(number) + roundToNearestInt((number - floor(number))/precision)*precision;
    return INFINITY;
}

long roundToNearestInt(double number) {
    return (long)(number + 0.5);
}
