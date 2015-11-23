#include "Identified.h"

Identified::Identified() {
    id_ = "";
}

Identified::Identified(const Identified &other) {
    id_ = other.getID();
}

Identified::Identified(QString id) : id_(id) {}

Identified::~Identified() {}

const QString &Identified::getID() const {
    return id_;
}

void Identified::setID(QString id) {
    id_ = id;
}
