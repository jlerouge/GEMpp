#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <QSet>
#include <QList>
#include <QFileInfo>
#include "Metadata.h"
#include "Vertex.h"
#include "Edge.h"
#include "../Core/Identified.h"
#include "../Core/Random.h"

class DLL_EXPORT Graph : virtual public IPrintable, virtual public ISaveable, virtual public Identified, virtual public Indexed {
    public:
        enum Type {
            DIRECTED = 0,
            UNDIRECTED,
            COUNT
        };

        static const char *typeName[COUNT];
        static QString toName(Type type);
        static Type fromName(QString type);

        Graph(Type type=DIRECTED);
        Graph(const QString &filename);
        virtual ~Graph();

        const QList <Vertex *> &getVertices() const;
        Vertex *getVertex(int i) const;
        virtual void addVertex(Vertex *v, QString id = "");
        virtual void removeVertex(Vertex *v);
        const QList <Edge *> &getEdges() const;
        Edge *getEdge(int i) const;
        virtual void addEdge(Edge *e);
        virtual void removeEdge(Edge *e);

        Metadata *getMetadata() const;
        int getVertexCount() const;
        int getEdgeCount() const;
        Type getType() const;
        void setType(Type type);
        Graph *neighborhoodSubgraph(int iSeed, int nbhdSize);
        Graph *neighborhoodSubgraph(QSet<int> iSeeds, int nbhdSize);
        Graph *randomSubgraph(int iSeed, int vCount);

        void print(Printer *p);
        void save(const QString &filename);

    protected:
        void fromFile (const QString &filename);
        void fromGML (const QString &filename);
        void fromGXL (const QString &filename);
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

#endif /*__GRAPH_H__*/
