#include "LayoutGraphElement.h"

LayoutGraphElement::LayoutGraphElement(int size, QColor color) {
    size_ = size;
    color_ = color;
}

LayoutGraphElement::~LayoutGraphElement() {}

int LayoutGraphElement::getSize() const {
    return size_;
}

void LayoutGraphElement::setSize(int size) {
    size_ = size;
}

const QColor &LayoutGraphElement::getColor() const {
    return color_;
}

void LayoutGraphElement::setColor(const QColor &color) {
    color_ = color;
}
