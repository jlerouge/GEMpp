#include "Hierarchizer.h"

Hierarchizer::Hierarchizer(Graph *input) {
    setInput(input);
}

Hierarchizer::~Hierarchizer() {
    visitedVertices_.clear();
    visitedEdges_.clear();
    cycles_.clear();
}

void Hierarchizer::setInput(Graph *input) {
    input_ = input;
}

Graph *Hierarchizer::getInput() const {
    return input_;
}

//void Hierarchizer::setOutput(Graph *output) {
//    output_ = output;
//}

Graph *Hierarchizer::getOutput() const {
    return output_;
}

QList<QList<Vertex *>> Hierarchizer::getCycles() const {
    return cycles_;
}

void Hierarchizer::extract() {
    visitedVertices_.clear();
    visitedEdges_.clear();
    cycles_.clear();
    depthFirstSearch();
    // cycles_ = depthFirstSearch();
}

void Hierarchizer::depthFirstSearch(Vertex *root, QList<Vertex *> parents) {
    if(input_->getVertexCount() == 0)
        return;
    if(!root)
        root = input_->getVertex(0);
    Vertex *parent = parents.empty()? 0 : parents.first();
    if(!visitedVertices_.contains(root)) {
        qcout << "->I'm visiting vertex " << root->getID() << endl;
        if(parent)
            qcout << " and my parent is " << parent->getID() << endl;
        visitedVertices_.insert(root);
        parents.prepend(root);
        Vertex *neighbour;
        for(Edge *edge : root->getEdges(Vertex::EDGE_IN_OUT)) {
            if(!visitedEdges_.contains(edge)) {
                visitedEdges_.insert(edge);
                neighbour = root->getNeighbour(edge);
                qcout << " next neighbour of " << root->getID() << " is " << neighbour->getID() << endl;
                depthFirstSearch(neighbour, parents);
            }
        }
        return;
    }
    qcout << "->I've already visited vertex " << root->getID() << " ! " << endl;
    if(parent)
        qcout << " and my parent is " << parent->getID() << endl;
    // This is a new detected cycle
    cycles_.append(QList<Vertex *>());
    cycles_.last().append(root);
    qcout << root->getID() << " is appended to the cycle " << endl;
    for(Vertex *vparent : parents) {
        if(vparent == root)
            break;
        qcout << vparent->getID() << " is appended to the cycle " << endl;
        cycles_.last().append(vparent);
    }
}

//void Hierarchizer::depthFirstSearch(Vertex *root, QList<Vertex *> parents) {
//    if(input_->getVertexCount() == 0)
//        return;
//    if(!root)
//        root = input_->getVertex(0);
//    Vertex *parent = parents.empty()? 0 : parents.first();
//    if(!visitedVertices_.contains(root)) {
//        qcout << "->I'm visiting vertex " << root->getID() << endl;
//        if(parent)
//            qcout << " and my parent is " << parent->getID() << endl;
//        visitedVertices_.insert(root);
//        parents.prepend(root);
//        for(Vertex *neighbour : root->getNeighbours(Vertex::EDGE_IN_OUT)) {
//            if(neighbour != parent) {
//                qcout << " next neighbour of " << root->getID() << " is " << neighbour->getID() << endl;
//                depthFirstSearch(neighbour, parents);
//            }
//        }
//        return;
//    }
//    qcout << "->I've already visited vertex " << root->getID() << " ! " << endl;
//    if(parent)
//        qcout << " and my parent is " << parent->getID() << endl;
//    // This is a new detected cycle
//    cycles_.append(QList<Vertex *>());
//    cycles_.last().append(root);
//    qcout << root->getID() << " is appended to the cycle " << endl;
//    for(Vertex *vparent : parents) {
//        if(vparent == root)
//            break;
//        qcout << vparent->getID() << " is appended to the cycle " << endl;
//        cycles_.last().append(vparent);
//    }
//}
