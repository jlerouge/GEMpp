#include "Edge.h"

Edge::Edge() : Edge(0, 0) {}

Edge::Edge(Vertex *origin, Vertex *target) : GraphElement() {
    type_ = GraphElement::EDGE;
    origin_ = origin;
    target_ = target;
}

Edge::Edge(const Edge &other) : GraphElement(other) {
    origin_ = other.getOrigin();
    target_ = other.getTarget();
}

Edge::~Edge() {}

Vertex *Edge::getOrigin() const {
    return origin_;
}

Vertex *Edge::getTarget() const {
    return target_;
}

void Edge::setOrigin(Vertex *v) {
    origin_ = v;
}

void Edge::setTarget(Vertex *v) {
    target_ = v;
}
