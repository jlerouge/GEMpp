#include "Constants.h"
#include <cmath>
#include "Printer.h"

double precision = pow(10, -PRECISION);

double roundAtPrecision(double number) {
    if(number < INFINITY)
        return floor(number) + roundToNearestInt((number - floor(number))/precision)*precision;
    return INFINITY;
}

long roundToNearestInt(double number) {
    return (long)(number + 0.5);
}

void GEM_exception(const QString &errorString) {
    throw std::logic_error(errorString.toStdString());
}
