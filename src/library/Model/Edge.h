#ifndef GEMPP_EDGE_H
#define GEMPP_EDGE_H

#include "GraphElement.h"

class Vertex;

class DLL_EXPORT Edge : virtual public GraphElement {
    public:
        Edge();
        Edge(const Edge &other);
        Edge(Vertex *origin, Vertex *target);
        virtual ~Edge();

        Vertex *getOrigin() const;
        void setOrigin(Vertex *v);
        Vertex *getTarget() const;
        void setTarget(Vertex *v);

    private:
        Vertex *origin_;
        Vertex *target_;
};

#endif /* GEMPP_EDGE_H */
