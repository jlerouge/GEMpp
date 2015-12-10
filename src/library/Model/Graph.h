#ifndef GEMPP_GRAPH_H
#define GEMPP_GRAPH_H

#include <QSet>
#include <QList>
#include <QFileInfo>
#include "Metadata.h"
#include "Vertex.h"
#include "Edge.h"
#include "Weights.h"
#include "Core/Identified.h"
#include "Core/Random.h"

/**
 * @brief The Graph class represents an attributed graph structure, having a set of ::Vertex and a set of ::Edge.
 * The ::Graph may be directed or undirected.
 * @see Edge
 * @see Vertex
 */
class DLL_EXPORT Graph : virtual IXmlSerializable, virtual public IPrintable, virtual public GraphElement {
    public:
        /**
         * @brief Indicates the type of the ::Graph.
         */
        enum Type {
            DIRECTED = 0, /**< the ::Edges have directions */
            UNDIRECTED,   /**< the ::Edges have no direction */
            TYPE_COUNT    /**< used to iterate on ::Graph::Type */
        };

        enum Format {
            GML = 0,     /**< Graph Modeling Language */
            GXL,         /**< Graph eXchange Language */
            XML,         /**< XML metadata + a GML/GXL file */
            FORMAT_COUNT /**< used to iterate on ::Graph::Format */
        };

        /**
         * @brief The names of the ::Types.
         */
        static const char *typeName[TYPE_COUNT];

        /**
         * @brief Returns the name of the ::Type.
         * @param type the ::Type
         * @return the name
         */
        static QString toName(Type type);

        /**
         * @brief Retrieves the ::Type from its name.
         * @param name the name
         * @return the ::Type
         */
        static Type toType(QString name);

        /**
         * @brief The names of the formats.
         */
        static const char *formatName[FORMAT_COUNT];

        /**
         * @brief Returns the name of the ::Format.
         * @param format the ::Format
         * @return the name
         */
        static QString toName(Format format);

        /**
         * @brief Retrieves the ::Format from its name.
         * @param name the name
         * @return the ::Format
         */
        static Format toFormat(QString name);

        /**
         * @brief Constructs a new ::Graph object with parameters.
         * @param type the graph type
         */
        Graph(Type type=DIRECTED);

        /**
         * @brief Constructs a new ::Graph object by loading a file.
         * @param filename the graph file
         */
        Graph(const QString &filename);

        /**
         * @brief Destructs a Graph object.
         */
        virtual ~Graph();

        /**
         * @brief Returns all the ::Vertices of the ::Graph.
         * @return a list of ::Vertex
         */
        const QList <Vertex *> &getVertices() const;

        /**
         * @brief Returns all the terminal ::GraphElement of the ::Graph
         * (the ones that contain no hierarchical subgraph), as well as
         * the terminal ::GraphElements contained in the hierarchical subgraphs.
         * @param the type of terminal elements
         * @return a list of ::GraphElement
         */
        QList<GraphElement *> getTerminals(GraphElement::Type type) const;

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
         * @brief Removes a ::Vertex from the ::Graph.
         * @param id the id of the ::Vertex to remove
         */
        virtual void removeVertex(QString id);

        /**
         * @brief Removes a ::Vertex from the ::Graph.
         * @param index the index of the ::Vertex to remove
         */
        virtual void removeVertex(int index);

        /**
         * @brief Removes a ::Vertex from the ::Graph.
         * @param v the ::Vertex to remove
         */
        virtual void removeVertex(Vertex *v);

        /**
         * @brief Returns all the ::Edges of the ::Graph.
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
         * @brief Adds an ::Edge to the ::Graph.
         * @param e the ::Edge to add
         */
        virtual void addEdge(Edge *e);

        /**
         * @brief Removes an ::Edge from the ::Graph.
         * @param index the index of the ::Edge to remove
         */
        virtual void removeEdge(int index);

        /**
         * @brief Removes an ::Edge from the ::Graph.
         * @param e the ::Edge to remove
         */
        virtual void removeEdge(Edge *e);

        /**
         * @brief Returns the ::Metadata on the ::Graph.
         * @return the ::Metadata
         */
        Metadata *getMetadata() const;

        /**
         * @brief Returns the number of ::Vertices of the ::Graph.
         * @return the number of ::Vertices
         */
        int getVertexCount() const;

        /**
         * @brief Returns the number of ::Edges of the ::Graph.
         * @return the number of ::Edges
         */
        int getEdgeCount() const;

        /**
         * @brief Returns the ::Graph::Type of the ::Graph.
         */
        Type getType() const;

        /**
         * @brief Sets the type of the graph.
         * @param type the type to set
         */
        void setType(Type type);

        /**
         * @brief Computes the creation costs of all elements of the ::Graph,
         * and sets the overall cost as the sum of the elements costs.
         * @param weights the weights used to compute the costs
         */
        void computeCosts(Weights *weights);

        /**
         * @brief Returns a deep copy of this ::Graph.
         * @return the copied ::Graph
         */
        Graph *copy() const;

        /**
         * @brief Computes a neighbourhood sugraph from this graph,
         * starting with a central seed vertex, adding recursively
         * neighbour vertices to a list and generating the induced subgraph.
         * @param iSeed the central vertex
         * @param nbhdSize the size of the neighborhood (maximal number of edges
         * between two vertices of the subgraph)
         */
        Graph *neighborhoodSubgraph(int iSeed, int nbhdSize) const;

        /**
         * @brief Computes a neighbourhood sugraph from this graph,
         * starting with several central seed vertices, adding recursively
         * neighbour vertices to a list and generating the induced subgraph.
         * @param iSeeds the central vertices
         * @param nbhdSize the size of the neighborhood (maximal number of edges between two vertices of the subgraph)
         */
        Graph *neighborhoodSubgraph(QSet<int> iSeeds, int nbhdSize) const;

        /**
         * @brief Computes a random subgraph, by traversing the edges starting
         * from a seed vertex, and selecting randomly a fixed number of neighbour
         * vertices.
         * @param iSeed the central vertex
         * @param vCount the number of vertices to select randomly
         */
        Graph *randomSubgraph(int iSeed, int vCount) const;

        /**
         * @brief Generates the subgraph induced by a set of ::Vertex
         * @param vertices the set of ::Vertex
         * @return the induced subgraph
         */
        Graph *inducedSubgraph(const QSet<Vertex *> &vertices) const;

        /**
         * @brief Prints the ::Graph to a ::Printer using the GML format.
         * @param p the printer
         */
        virtual void print(Printer *p);

        /**
         * @brief Imports a graph from a graph file. Guesses which
         * import method to use using the filename extension.
         * @param filename the graph file
         */
        void load(const QString &filename);

        /**
         * @brief Exports a graph to a graph file. Guesses which
         * export method to use using the filename extension.
         * @param filename the graph file
         */
        void save(const QString &filename);

        /**
         * @brief Serializes the graph to an XML element in the GXL format.
         * @param document the root XML document
         * @return the XML element
         */
        QDomElement save(QDomDocument *document);

        /**
         * @brief Deserializes the graph from an XML element in the GXL format.
         * @param element the XML element
         */
        void load(QDomElement element);

    protected:
        /**
         * @brief Imports a graph from a GML graph file.
         * @param filename the graph file
         */
        void fromGML(const QString &filename);

        /**
         * @brief Imports a graph from a GXL graph file.
         * @see IXmlSerializable
         */
        void fromXML();

        /**
         * @brief Imports a graph, loading a XML graph metadata file first.
         * This metadata file most likely contains an URL to the actual graph file.
         * @param filename the graph metadata file
         */
        void fromXMLMetadata (const QString &filename);

        /**
         * @brief Exports a graph to a GML graph file.
         * @param filename the graph file
         */
        void toGML(const QString &filename);

        /**
         * @brief Exports a graph to a GXL graph file.
         * @see IXmlSerializable
         */
        void toXML();

        /**
         * @brief Exports a graph, saving a XML graph metadata file first.
         * This metadata file most likely contains an URL to the actual graph file.
         * @param filename the graph metadata file
         */
        void toXMLMetadata (const QString &filename);

    private:
        Graph *neighborhoodSubgraphRec(QSet<Vertex *> vertices, int nbhdSize) const;

        Type type_;
        Metadata *metadata_;
        QList<Vertex *> vertices_;
        QHash<QString, int> verticesInsertionOrder_;
        QList<Edge *> edges_;
};

#endif /* GEMPP_GRAPH_H */
