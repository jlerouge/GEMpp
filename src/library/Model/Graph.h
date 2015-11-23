#ifndef GEMPP_GRAPH_H
#define GEMPP_GRAPH_H

#include <QSet>
#include <QList>
#include <QFileInfo>
#include "Metadata.h"
#include "Vertex.h"
#include "Edge.h"
#include "Core/Identified.h"
#include "Core/Random.h"

/**
 * @brief The Graph class represents an attributed graph structure, having a set of ::Vertex and a set of ::Edge.
 * The ::Graph may be directed or undirected.
 * @see Edge
 * @see Vertex
 */
class DLL_EXPORT Graph : virtual public IPrintable, virtual public ISaveable, virtual public Identified, virtual public Indexed {
    public:
        /**
         * @brief Indicates the type of the ::Graph.
         */
        enum Type {
            DIRECTED = 0, /**< the edges have directions */
            UNDIRECTED, /**< the edges have no direction */
            COUNT /**< used to iterate on Graph::Type */
        };

        /**
         * @brief The names of the types.
         */
        static const char *typeName[COUNT];

        /**
         * @brief Returns the name of the type.
         * @param type the type
         * @return the name
         */
        static QString toName(Type type);

        /**
         * @brief Retrieves the type from its name.
         * @param name the name
         * @return the type
         */
        static Type fromName(QString type);

        /**
         * @brief Constructs a new Graph object with parameters.
         * @param type the graph type
         */
        Graph(Type type=DIRECTED);

        /**
         * @brief Constructs a new Graph object by loading a graph file.
         * @param filename the graph file
         */
        Graph(const QString &filename);

        /**
         * @brief Destructs a Graph object.
         */
        virtual ~Graph();

        /**
         * @brief Returns all the vertices of the graph.
         * @return a list of ::Vertex
         */
        const QList <Vertex *> &getVertices() const;

        /**
         * @brief Returns a vertex of the graph.
         * @param i the index of the vertex
         * @return the ::Vertex
         */
        Vertex *getVertex(int i) const;

        /**
         * @brief Adds a vertex to the graph.
         * @param v the vertex to add
         * @param id the identifier of the vertex (if omitted, one is automatically generated)
         */
        virtual void addVertex(Vertex *v, QString id = "");

        /**
         * @brief Removes a vertex from the graph.
         * @param v the vertex to remove
         */
        virtual void removeVertex(Vertex *v);

        /**
         * @brief Returns all the edges of the graph.
         * @return a list of ::Edge
         */
        const QList <Edge *> &getEdges() const;

        /**
         * @brief Returns an ::Edge of the graph.
         * @param i the index of the ::Edge
         * @return the ::Edge
         */
        Edge *getEdge(int i) const;

        /**
         * @brief Adds an edge to the graph.
         * @param e the edge to add
         */
        virtual void addEdge(Edge *e);

        /**
         * @brief Removes an edge from the graph.
         * @param e the edge to remove
         */
        virtual void removeEdge(Edge *e);

        /**
         * @brief Returns the metadata on the graph.
         * @param the metadata
         */
        Metadata *getMetadata() const;

        /**
         * @brief Returns the number of vertices of the graph.
         * @return the number of vertices
         */
        int getVertexCount() const;

        /**
         * @brief Returns the number of edges of the graph.
         * @return the number of edges
         */
        int getEdgeCount() const;

        /**
         * @brief Returns the type of the graph.
         */
        Type getType() const;

        /**
         * @brief Sets the type of the graph.
         * @param type the type to set
         */
        void setType(Type type);

        /**
         * @brief Computes a neighbourhood sugraph from this graph,
         * starting with a central seed vertex, adding recursively
         * neighbour vertices to a list and generating the induced subgraph.
         * @param iSeed the central vertex
         * @param nbhdSize the size of the neighborhood (maximal number of edges
         * between two vertices of the subgraph)
         */
        Graph *neighborhoodSubgraph(int iSeed, int nbhdSize);

        /**
         * @brief Computes a neighbourhood sugraph from this graph,
         * starting with several central seed vertices, adding recursively
         * neighbour vertices to a list and generating the induced subgraph.
         * @param iSeeds the central vertices
         * @param nbhdSize the size of the neighborhood (maximal number of edges between two vertices of the subgraph)
         */
        Graph *neighborhoodSubgraph(QSet<int> iSeeds, int nbhdSize);

        /**
         * @brief Computes a random subgraph, by traversing the edges starting
         * from a seed vertex, and selecting randomly a fixed number of neighbour
         * vertices.
         * @param iSeed the central vertex
         * @param vCount the number of vertices to select randomly
         */
        Graph *randomSubgraph(int iSeed, int vCount);

        void print(Printer *p);
        void save(const QString &filename);

    protected:
        /**
         * @brief Imports a graph from a graph file. Guess which importation method to use,
         * using the filename extension.
         * @param filename the graph file
         */
        void fromFile (const QString &filename);

        /**
         * @brief Imports a graph from a GML graph file.
         * @param filename the graph file
         */
        void fromGML (const QString &filename);

        /**
         * @brief Imports a graph from a GXL graph file.
         * @param filename the graph file
         */
        void fromGXL (const QString &filename);

        /**
         * @brief Imports a graph from a XML graph metadata file.
         * This metadata file must likely contains an URL to the actual graph file.
         * @param filename the graph metadata file
         */
        void fromXML (const QString &filename);

    private:
        Graph *neighborhoodSubgraphRec(QSet<Vertex *> vertices, int nbhdSize);
        Graph *generateInducedSubgraph(const QSet<Vertex *> &vertices);

        Type type_;
        Metadata *metadata_;
        QList<Vertex *> vertices_;
        QHash<QString, int> verticesInsertionOrder_;
        QList<Edge *> edges_;
};

#endif /*GRAPH_H*/
