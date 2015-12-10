#include "Vertex.h"

const char* Vertex::directionName[Vertex::COUNT] = {
    "in",
    "out",
    "both"
};


Vertex::Vertex() : GraphElement(GraphElement::VERTEX) {
    inEdges_ = QSet<Edge *>();
    outEdges_ = QSet<Edge *>();
}

Vertex::Vertex(const Vertex &other) : Identified(other), Indexed(other), GraphElement(other) {
    outEdges_ = other.getEdges(EDGE_OUT);
    inEdges_ = other.getEdges(EDGE_IN);
}

Vertex::~Vertex() {}

void Vertex::addEdge(Edge *e, Direction d) {
    switch(d) {
        case EDGE_IN:
            inEdges_.insert(e);
            break;
        case EDGE_OUT:
            outEdges_.insert(e);
            break;
        case EDGE_IN_OUT:
            inEdges_.insert(e);
            outEdges_.insert(e);
            break;
        default:
            break;
    }
}

void Vertex::removeEdge(Edge *e) {
    if(inEdges_.contains(e))
        inEdges_.remove(e);
    else if(outEdges_.contains(e))
        outEdges_.remove(e);
    else
        Exception(QString("The edge %1 cannot be removed from vertex %2").arg(e->getID(), id_));
}

Edge *Vertex::getEdge(int e, Direction d) const {
    switch(d) {
        case EDGE_IN:
            return inEdges_.toList().at(e);
        case EDGE_OUT:
            return outEdges_.toList().at(e);
        case EDGE_IN_OUT:
            return getEdges(EDGE_IN_OUT).toList().at(e);
        default:
            break;
    }
    return 0;
}

QSet<Edge *> Vertex::getEdges(Direction d) const {
    switch(d) {
        case EDGE_IN:
            return inEdges_;
        case EDGE_OUT:
            return outEdges_;
        case EDGE_IN_OUT:
            return getEdges(EDGE_IN).unite(getEdges(EDGE_OUT));
        default:
            break;
    }
    return QSet<Edge *>();
}

Vertex *Vertex::getNeighbour(Edge *e) const {
    if(e->getOrigin() == const_cast<Vertex *>(this))
        return e->getTarget();
    if(e->getTarget() == const_cast<Vertex *>(this))
        return e->getOrigin();
    Exception(QString("The edge %1 is not a valid incident edge for vertex %2.").arg(e->getIndex()).arg(getIndex()));
}

QSet<Vertex *> Vertex::getNeighbours(Direction d) const {
    QSet<Vertex *> vertices;
    switch(d) {
        case EDGE_IN:
            for(auto e : inEdges_)
                vertices.insert(e->getOrigin());
            break;
        case EDGE_OUT:
            for(auto e : outEdges_)
                vertices.insert(e->getTarget());
            break;
        case EDGE_IN_OUT:
            return getNeighbours(EDGE_IN).unite(getNeighbours(EDGE_OUT));
        default:
            break;
    }
    return vertices;
}
