#ifndef GEMPP_EDGE_H
#define GEMPP_EDGE_H

#include "GraphElement.h"

class Vertex;

/**
 * @brief The Edge class represents an edge between two vertices (::Vertex) of a ::Graph.
 * An Edge may have attributes, as a Vertex does, and it can be directed or undirected.
 * The direction of the Edge is specied in Vertex::addEdge using a Vertex::Direction.
 * @see GraphElement
 * @see Vertex
 * @see Graph
 */
class DLL_EXPORT Edge : virtual public GraphElement {
    public:
        /**
         * @brief Constructs a new Edge object.
         */
        Edge();

        /**
         * @brief Constructs a copy of an existing Edge object.
         * @param other the Edge to copy
         */
        Edge(const Edge &other);

        /**
         * @brief Constructs a new Edge object with parameters.
         * @param origin the origin vertex
         * @param target the target vertex
         */
        Edge(Vertex *origin, Vertex *target);

        /**
         * @brief Destructs an Edge object.
         */
        virtual ~Edge();

        /**
         * @brief Returns the origin vertex.
         * @return the origin vertex.
         */
        Vertex *getOrigin() const;

        /**
         * @brief Sets the origin vertex.
         * @param v the origin vertex
         */
        void setOrigin(Vertex *v);

        /**
         * @brief Returns the target vertex.
         * @return the target vertex.
         */
        Vertex *getTarget() const;

        /**
         * @brief Sets the target vertex.
         * @param v the target vertex
         */
        void setTarget(Vertex *v);

    private:
        /**
         * @brief The origin ::Vertex. The edge is incident from this vertex.
         * @note The order is not important in case of undirected ::Edge.
         */
        Vertex *origin_;

        /**
         * @brief The target ::Vertex. The edge is incident to this vertex.
         * @note The order is not important in case of undirected ::Edge.
         */
        Vertex *target_;
};

#endif /* GEMPP_EDGE_H */
