#ifndef _LAYOUTGRAPH_H_
#define _LAYOUTGRAPH_H_

#include <QVector2D>
#include <QObject>
#include <cmath>
#include "LayoutVertex.h"
#include "LayoutEdge.h"
#include "../Model/Graph.h"

class DLL_EXPORT LayoutGraph: public QObject, public Graph{
        Q_OBJECT

    public :
        LayoutGraph(QObject *parent = 0, double centerForce = 1, Graph::Type type = Graph::DIRECTED);
        LayoutGraph(const QString &filename, QObject *parent = 0, double centerForce = 1);
        virtual ~LayoutGraph();

        double getCenterForce() const;
        void setCenterForce(double force);
        QList<LayoutVertex *> getVertices() const;
        LayoutVertex *getVertex(int i) const;
        virtual void addVertex(Vertex *v, QString id = "");
        QList <LayoutEdge *> getEdges() const;
        LayoutEdge *getEdge(int i) const;
        virtual void addEdge(Edge *e);
        const QVector2D &getCenterPos() const;
        void setCenterPos(const QVector2D &center);
        void start(int speed);
        void stop();

    signals :
        void layoutGraphChanged();

    private slots :
        void update();

    private:
        QVector2D center_;
        double centerForce_;
        QTimer *timer_;
};

#endif /* _LAYOUTGRAPH_H_ */
