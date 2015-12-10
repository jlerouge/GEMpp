#include "Hierarchizer.h"

Hierarchizer::Hierarchizer(Graph *input) {
    setInput(input);
    output_ = 0;
}

Hierarchizer::~Hierarchizer() {
    visitedVertices_.clear();
    visitedEdges_.clear();
    cycles_.clear();
    chains_.clear();
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

QList<QSet<Edge *> > Hierarchizer::getChains() const {
    return chains_;
}

void Hierarchizer::extract() {
    cycles_.clear();
    chains_.clear();
    if(output_)
        delete output_;
    output_ = 0;

    output_ = input_->copy();
    extractCycles();
    extractChains();
}

void Hierarchizer::extractCycles() {
    visitedVertices_.clear();
    visitedEdges_.clear();

    dfsCycles();
    filterCycles();
    fusionCycles();
    hierarchizeCycles();
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

void Hierarchizer::filterCycles() {
    // Filter the cycles that are not admissible (e.g. too much vertices)
    // FIXME : do the isAdmissibleCycle function
    for(int i = 0; i < cycles_.size();) {
        if(!isAdmissibleCycle(cycles_[i]))
            cycles_.removeAt(i);
        else
            ++i;
    }
}

void Hierarchizer::fusionCycles() {
    // Fusion the cycles having at least 2 vertices in common
    QSet<Vertex *> temp;
    for(int i = 0; i < cycles_.size(); ++i) {
        for(int j = i + 1; j < cycles_.size(); ++j) {
            temp = cycles_[i];
            temp = temp.intersect(cycles_[j]);
            if(temp.size() >= 1) {
                temp = cycles_[i];
                temp = temp.unite(cycles_[j]);
                if(isAdmissibleCycle(temp)) {
                    cycles_.removeAt(j);
                    cycles_[i] = temp;
                    // Next i iteration will be i = 0
                    i = -1;
                    break;
                }
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
            if(cycle.contains(e->getOrigin()) && cycle.contains(e->getTarget())) {
                output_->removeEdge(e);
            } else if(cycle.contains(e->getOrigin())) {
                e->setOrigin(cycleVertex);
                cycleVertex->addEdge(e, Vertex::EDGE_OUT);
            } else if(cycle.contains(e->getTarget())) {
                e->setTarget(cycleVertex);
                cycleVertex->addEdge(e, Vertex::EDGE_IN);
            }
        }

        // FIXME
        //qDeleteAll(cycle);
    }
}

bool Hierarchizer::isAdmissibleCycle(QSet<Vertex *> cycle) {
    // FIXME : do the isAdmissibleCycle function
    return true;
}

void Hierarchizer::extractChains() {
    for(Edge *edge : output_->getEdges()) {
        chains_.append(QSet<Edge *>());
        chains_.last().insert(edge);
    }
    fusionChains();
    filterChains();
    hierarchizeChains();
}

void Hierarchizer::filterChains() {
    // Filter the chains that are not admissible
    // or too short (single-edge chains)
    for(int i = 0; i < chains_.size();) {
        if(!isAdmissibleChain(chains_[i]) || (chains_[i].size() < 2))
            chains_.removeAt(i);
        else
            ++i;
    }
}

void Hierarchizer::fusionChains() {
    // Fusion the chains that have one vertex in common
    // and which results in an admissible longer chain
    QSet<Edge *> temp;
    for(int i = 0; i < chains_.size(); ++i) {
        for(int j = i + 1; j < chains_.size(); ++j) {
            if(areMergeable(chains_[i], chains_[j])) {
                temp = chains_[i];
                temp = temp.unite(chains_[j]);
                if(isAdmissibleChain(temp)) {
                    chains_.removeAt(j);
                    chains_[i] = temp;
                    // Next i iteration will be i = 0
                    i = -1;
                    break;
                }
            }
        }
    }
}

void Hierarchizer::hierarchizeChains() {
    Graph *subgraph;
    QString chainName;
    Vertex *chainVertex;
    for(QSet<Edge *> chain : chains_) {
        QSet<Vertex *> vertices;
        for(Edge *edge : chain) {
            vertices.insert(edge->getOrigin());
            vertices.insert(edge->getTarget());
        }
        qcout << "chain : " << endl;
        for(Vertex *vertex : vertices) {
            qcout << "vertex : " << vertex->getID() << endl;
            for(Edge * edge : vertex->getEdges(Vertex::EDGE_IN_OUT)) {
                qcout << " has edge from " << edge->getOrigin()->getID() << " to " << edge->getTarget()->getID() << endl;
            }
        }

        subgraph = output_->inducedSubgraph(vertices);

        // Remove vertices from parent graph
        chainName = "";
        for(Vertex *v : vertices) {
            output_->removeVertex(v->getID());
            chainName += QString("%1_").arg(v->getID());
        }
        chainName.remove(chainName.size()-1, 1);

        // Create a hierarchical vertex
        chainVertex = new Vertex();
        chainVertex->setGraph(subgraph);
        output_->addVertex(chainVertex, chainName);

        // Remove edges from parent graph
        QList<Edge *> eList = output_->getEdges();
        for(Edge *e : eList) {
            if(chain.contains(e)) {
                output_->removeEdge(e);
            } else if(vertices.contains(e->getOrigin())) {
                e->setOrigin(chainVertex);
                chainVertex->addEdge(e, Vertex::EDGE_OUT);
            } else if(vertices.contains(e->getTarget())) {
                e->setTarget(chainVertex);
                chainVertex->addEdge(e, Vertex::EDGE_IN);
            }
        }

        // FIXME
        //qDeleteAll(vertices);
    }
}

bool Hierarchizer::areChainable(Edge *e1, Edge *e2) {
    if(e1->getOrigin()->getEdges(Vertex::EDGE_IN_OUT).size() > 2
            || e1->getTarget()->getEdges(Vertex::EDGE_IN_OUT).size() > 2
            || e2->getOrigin()->getEdges(Vertex::EDGE_IN_OUT).size() > 2
            || e2->getTarget()->getEdges(Vertex::EDGE_IN_OUT).size() > 2)
        return false;

    return (e1->getOrigin() == e2->getOrigin()
            || e1->getOrigin() == e2->getTarget()
            || e1->getTarget() == e2->getOrigin()
            || e1->getTarget() == e2->getTarget());
}

bool Hierarchizer::areMergeable(QSet<Edge *> chain1, QSet<Edge *> chain2) {
    for(Edge *edge1 : chain1) {
        for(Edge *edge2 : chain2) {
            if(areChainable(edge1, edge2))
                return true;
        }
    }
    return false;
}

bool Hierarchizer::isAdmissibleChain(QSet<Edge *> chain) {
    // Do not accept cyclic chains and other connected patterns
    QSet<Vertex *> vertices;
    for(auto edge : chain) {
        vertices.insert(edge->getOrigin());
        vertices.insert(edge->getTarget());
    }
    return (vertices.size() == (chain.size() + 1));
}
