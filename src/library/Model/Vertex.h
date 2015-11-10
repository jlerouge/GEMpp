#ifndef GEMPP_VERTEX_H
#define GEMPP_VERTEX_H

#include <QSet>
#include "GraphElement.h"
#include "Edge.h"

class DLL_EXPORT Vertex : virtual public GraphElement {
    public:
        enum Direction {
            EDGE_IN = 0,
            EDGE_OUT,
            EDGE_IN_OUT,
            COUNT
        };
        static const char* directionName[COUNT];

        Vertex();
        Vertex(const Vertex &other);
        virtual ~Vertex();

        void addEdge(Edge *e, Direction d);
        void removeEdge(Edge *e);
        Edge *getEdge(int e, Direction d) const;
        QSet<Edge *> getEdges(Direction d) const;
        QSet<Vertex *> getNeighbours(Direction d) const;
        void setParentIndex(int parentIndex);
        int getParentIndex() const;

    private:
        QSet<Edge *> outEdges_;
        QSet<Edge *> inEdges_;
        int parentIndex_;
};

#endif /*VERTEX_H*/
