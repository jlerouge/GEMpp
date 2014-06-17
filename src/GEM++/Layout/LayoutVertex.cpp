#include "LayoutVertex.h"

LayoutVertex::LayoutVertex(int negativeForce, int size, QColor color) : LayoutGraphElement(size, color) {
    Vertex();
    pos_ = QVector2D(0,0);
    force_ = QVector2D(0,0);
    negativeForce_ = negativeForce;
    locked_ = false;
}

LayoutVertex::LayoutVertex(const Vertex &other) : Vertex(other), LayoutGraphElement(15, QColor(Qt::yellow)) {
    pos_ = QVector2D(0,0);
    force_ = QVector2D(0,0);
    negativeForce_ = 50;
    locked_ = false;
}

LayoutVertex::~LayoutVertex() {}

bool LayoutVertex::getLocked() const {
    return locked_;
}

void LayoutVertex::setLocked(bool locked) {
    locked_ = locked;
}

const QVector2D &LayoutVertex::getPosition() const {
    return pos_;
}

void LayoutVertex::setPosition(QVector2D position) {
    pos_ = position;
}

const QVector2D &LayoutVertex::getForce() const {
    return force_;
}

void LayoutVertex::setForce(QVector2D force) {
    force_ = force;
}

QSet<LayoutEdge *> LayoutVertex::getEdges(Direction d) const {
    QSet<Edge *> edges = Vertex::getEdges(d);
    QSet<LayoutEdge *> layoutEdges;
    for(auto e : edges)
        layoutEdges.insert(LayoutEdge::upcast(e));
    return layoutEdges;
}

double LayoutVertex::getNegativeForce() const {
    return negativeForce_;
}

void LayoutVertex::setNegativeForce(double force) {
    negativeForce_ = force;
}

void LayoutVertex::updatePosition() {
    if(!locked_ && (force_.length() > 0.05))
        pos_ += force_;
}

LayoutVertex *LayoutVertex::upcast(Vertex *v) {
    return dynamic_cast<LayoutVertex *>(v);
}

Vertex *LayoutVertex::downcast(LayoutVertex *v) {
    return dynamic_cast<Vertex *>(v);
}
