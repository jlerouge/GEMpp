#include "LayoutEdge.h"

LayoutEdge::LayoutEdge(LayoutVertex *origin, LayoutVertex *target, int size, QColor color) : LayoutGraphElement(size, color) {
    Edge((Vertex *)origin, (Vertex *)target);
}

LayoutEdge::LayoutEdge(const Edge &e) : Edge(e), LayoutGraphElement(15, QColor(Qt::white)) {}

LayoutEdge::~LayoutEdge() {}

LayoutEdge *LayoutEdge::upcast(Edge *e) {
    return dynamic_cast<LayoutEdge *>(e);
}

Edge *LayoutEdge::downcast(LayoutEdge *e) {
    return dynamic_cast<Edge *>(e);
}
