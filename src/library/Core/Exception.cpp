#include "Exception.h"

void Exception(const QString &errorString) {
    throw std::logic_error(errorString.toStdString());
}
