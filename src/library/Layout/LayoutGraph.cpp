#include "LayoutGraph.h"

LayoutGraph::LayoutGraph(QObject *parent, double centerForce, Graph::Type type) : QObject(parent), Graph(type) {
    center_ = QVector2D(0, 0);
    centerForce_ = centerForce;
    timer_ = new QTimer();
    connect(timer_, SIGNAL(timeout()), this, SLOT(update()));
}

LayoutGraph::LayoutGraph(const QString &filename, QObject *parent, double centerForce) : LayoutGraph(parent, centerForce) {
    load(filename);
}

LayoutGraph::~LayoutGraph() {
    delete timer_;
}

double LayoutGraph::getCenterForce() const {
    return centerForce_;
}

void LayoutGraph::setCenterForce(double force) {
    centerForce_ = force;
}

void LayoutGraph::start(int speed) {
    timer_->start(speed);
}

void LayoutGraph::stop() {

    timer_->stop();
}

QList<LayoutVertex *> LayoutGraph::getVertices() const {
    QList<LayoutVertex *> vl;
    for(int i=0; i < getVertexCount(); ++i)
        vl.push_back(getVertex(i));
    return vl;
}

LayoutVertex *LayoutGraph::getVertex(int i) const {
    return LayoutVertex::upcast(Graph::getVertex(i));
}

void LayoutGraph::addVertex(Vertex *v, QString id) {
    LayoutVertex *lv = new LayoutVertex(*v);
    Graph::addVertex(LayoutVertex::downcast(lv), id);
    delete v;
}

QList<LayoutEdge *> LayoutGraph::getEdges() const {
    QList<LayoutEdge *> el;
    for(int i=0; i < getEdgeCount(); ++i)
        el.push_back(getEdge(i));
    return el;
}

LayoutEdge *LayoutGraph::getEdge(int i) const {
    return LayoutEdge::upcast(Graph::getEdge(i));
}

void LayoutGraph::addEdge(Edge *e) {
    LayoutEdge *le = new LayoutEdge(*e);
    Graph::addEdge(LayoutEdge::downcast(le));
    delete e;
}

const QVector2D &LayoutGraph::getCenterPos() const {
    return center_;
}

void LayoutGraph::setCenterPos(const QVector2D &center) {
    center_ = center;
}

void LayoutGraph::update() {
    QVector2D force, vector;
    double length;
    for(auto v : getVertices()) {
        if(!v->getLocked()) {
            force = QVector2D(0,0);

            //Central force
            length = hypot(v->getPosition().x(), v->getPosition().y());
            if (length > centerForce_)
                force -= v->getPosition()*centerForce_/length;
            else
                force -= v->getPosition();

            //Negative force from other vertices
            for (auto otherV : getVertices()) {
                if(v != otherV) {
                    vector = v->getPosition() - otherV->getPosition();
                    double length = hypot(vector.x(), vector.y());
                    if (length > 1)
                        vector *= (v->getNegativeForce() + otherV->getNegativeForce())/(length*length);
                    else
                        vector = QVector2D(rand()/(double)RAND_MAX, rand()/(double)RAND_MAX);
                    force += vector;
                }
            }

            for (auto e : v->getEdges(Vertex::EDGE_IN_OUT)) {
                vector = LayoutVertex::upcast(e->getTarget())->getPosition() - LayoutVertex::upcast(e->getOrigin())->getPosition();
                if (LayoutVertex::upcast(e->getTarget()) == v)
                    vector = -vector;

                double length = hypot(vector.x(), vector.y());
                if (length > 1)
                    force += vector*(length - e->getSize())*0.02/length;
            }
            v->setForce(force);
        }
    }
    for(auto v : getVertices())
        v->updatePosition();

    emit layoutGraphChanged();
}
