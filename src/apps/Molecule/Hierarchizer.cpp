#include "Hierarchizer.h"

Hierarchizer::Hierarchizer(Graph *input) {
    setInput(input);
    output_ = 0;
}

Hierarchizer::~Hierarchizer() {
    visitedVertices_.clear();
    visitedEdges_.clear();
    cycles_.clear();
    if(output_)
        delete output_;
    output_ = 0;
}

void Hierarchizer::setInput(Graph *input) {
    input_ = input;
}

Graph *Hierarchizer::getInput() const {
    return input_;
}

Graph *Hierarchizer::getOutput() const {
    return output_;
}

QList<QSet<Vertex *> > Hierarchizer::getCycles() const {
    return cycles_;
}

void Hierarchizer::extract() {
    cycles_.clear();
    if(output_)
        delete output_;
    output_ = 0;

    output_ = input_->copy();
    extractCycles();
}

void Hierarchizer::extractCycles() {
    visitedVertices_.clear();
    visitedEdges_.clear();

    dfsCycles();
    fusionCycles();
    hierarchizeCycles();
}

void Hierarchizer::fusionCycles() {
    // Fusion the cycles having at least 2 vertices in common
    QSet<Vertex *> temp;
    for(int i = 0; i < cycles_.size(); ++i) {
        for(int j = i + 1; j < cycles_.size(); ++j) {
            temp = cycles_[i];
            temp = temp.intersect(cycles_[j]);
            if(temp.size() > 1) {
                temp = cycles_[i];
                temp = temp.unite(cycles_[j]);
                cycles_.removeAt(j);
                cycles_[i] = temp;
                i = 0;
                break;
            }
        }
    }
}

void Hierarchizer::hierarchizeCycles() {
    QString cycleName;
    Graph *subgraph;
    Vertex *cycleVertex;
    for(QSet<Vertex *> cycle : cycles_) {
        subgraph = output_->inducedSubgraph(cycle);

        // Remove vertices from parent graph
        cycleName = "";
        for(Vertex *v : cycle) {
            output_->removeVertex(v->getID());
            cycleName += QString("%1_").arg(v->getID());
        }
        cycleName.remove(cycleName.size()-1, 1);

        // Create a hierarchical vertex
        cycleVertex = new Vertex();
        cycleVertex->setGraph(subgraph);
        output_->addVertex(cycleVertex, cycleName);

        // Remove edges from parent graph
        QList<Edge *> eList = output_->getEdges();
        for(Edge *e : eList) {
            if(cycle.contains(e->getOrigin()) && cycle.contains(e->getTarget()))
                output_->removeEdge(e);
            else if(cycle.contains(e->getOrigin()))
                e->setOrigin(cycleVertex);
            else if(cycle.contains(e->getTarget()))
                e->setTarget(cycleVertex);
        }

        //qDeleteAll(cycle);
    }
}

void Hierarchizer::dfsCycles(Vertex *root, QList<Vertex *> parents) {
    if(output_->getVertexCount() == 0)
        return;
    if(!root)
        root = output_->getVertex(0);
    if(!visitedVertices_.contains(root)) {
        visitedVertices_.insert(root);
        parents.prepend(root);
        Vertex *neighbour;
        for(Edge *edge : root->getEdges(Vertex::EDGE_IN_OUT)) {
            if(!visitedEdges_.contains(edge)) {
                visitedEdges_.insert(edge);
                neighbour = root->getNeighbour(edge);
                dfsCycles(neighbour, parents);
            }
        }
        return;
    }

    // This is a new detected cycle
    cycles_.append(QSet<Vertex *>());
    cycles_.last().insert(root);
    for(Vertex *vparent : parents) {
        if(vparent == root)
            break;
        cycles_.last().insert(vparent);
    }
}
