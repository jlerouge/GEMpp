#ifndef GEMPP_VERTEX_H
#define GEMPP_VERTEX_H

#include <QSet>
#include "GraphElement.h"
#include "Edge.h"

class Graph;

/**
 * @brief The Vertex class represents a vertex of a ::Graph. It may have attributes,
 * and any two vertices can be linked with an ::Edge.
 * @see GraphElement
 * @see Edge
 * @see Graph
 */
class DLL_EXPORT Vertex : virtual public GraphElement {
    public:
        /**
         * @brief Indicates the direction of an incident edge.
         */
        enum Direction {
            EDGE_IN = 0, /**< the edge is incident to the vertex */
            EDGE_OUT, /**< the edge is incident from the vertex */
            EDGE_IN_OUT, /**< the edge is undirected */
            COUNT /**< used to iterate on Vertex::Direction enum */
        };

        /**
         * @brief The names of the directions.
         */
        static const char* directionName[COUNT];

        /**
         * @brief Constructs a new Vertex object.
         */
        Vertex();

        /**
         * @brief Constructs a copy of an existing Vertex object.
         * @param other the Vertex to copy
         */
        Vertex(const Vertex &other);

        /**
         * @brief Destructs an Edge object.
         */
        virtual ~Vertex();

        /**
         * @brief Adds an incident edge to this ::Vertex.
         * @param e the edge to add
         * @param d its direction
         */
        void addEdge(Edge *e, Direction d);

        /**
         * @brief Remove an incident edge from this ::Vertex.
         * @param e the edge to remove
         */
        void removeEdge(Edge *e);

        /**
         * @brief Returns an edge from the list of incident edges
         * having a particular direction.
         * @param e the index of the edge in the list
         * @param d the direction of the edge
         */
        Edge *getEdge(int e, Direction d) const;

        /**
         * @brief Returns all the incident edges having a
         * particular direction.
         * @param d the direction of the edges
         */
        QSet<Edge *> getEdges(Direction d) const;

        /**
         * @brief Returns the neighbour ::Vertex corresponding
         * to one particular ::Edge.
         * @param e the edge
         * @return the neighbour
         * @warning throws an exception if e is not a valid
         * incident edge.
         */
        Vertex *getNeighbour(Edge *e) const;

        /**
         * @brief Returns all the neighbour vertices (::Vertex),
         * considering only edges having a particular direction.
         * @param d the direction of the edges
         */
        QSet<Vertex *> getNeighbours(Direction d) const;

        /**
         * @brief Returns the ::Graph represented by this ::Vertex.
         * @return a graph
         */
        Graph *getGraph() const;

        /**
         * @brief Sets the ::Graph represented by this ::Vertex.
         * @param graph a graph
         */
        void setGraph(Graph *graph);

    private:
        /**
         * @brief The set of ::Edge incident from this Vertex
         */
        QSet<Edge *> outEdges_;

        /**
         * @brief The set of ::Edge incident to this Vertex
         */
        QSet<Edge *> inEdges_;

        /**
         * @brief A subgraph represented by a ::Vertex of the parent ::Graph.
         * This allows to construct hierarchical graphs.
         */
        Graph *graph_;
};

#endif /* GEMPP_VERTEX_H */
