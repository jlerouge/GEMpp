#include "Indexed.h"

Indexed::Indexed() : index_(0) {}

Indexed::Indexed(const Indexed &other) {
    index_ = other.getIndex();
}

Indexed::Indexed(int index) : index_(index) {}

Indexed::~Indexed() {}

int Indexed::getIndex() const {
    return index_;
}

void Indexed::setIndex(int index) {
    index_ = index;
}
