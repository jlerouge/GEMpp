#include "Problem.h"

const char *Problem::typeName[Problem::COUNT] = {
    "none",
    "subgraph matching",
    "graph edit distance"
};

Problem::Type Problem::fromName(QString name) {
    for(Type t = (Type)0; t < COUNT; t = (Type)((int)t + 1))
        if(QString(typeName[t]).contains(name, Qt::CaseInsensitive))
            return t;
    Exception(QString("Problem type '%1' not recognized, please use sub(graph) or dist(ance).").arg(name));
    return COUNT;
}

QString Problem::toName(Type type) {
    return typeName[type];
}

Problem::Problem(Type t, Graph *pattern, Graph *target, Weights *weights) : type_(t), pattern_(pattern), target_(target), deleteGraphs_(false) {
    if(pattern_->getType() != target_->getType())
        Exception("Both graphs must have the same type (directed or undirected).");
    vCosts_ = Matrix<double>(pattern_->getVertexCount(), target_->getVertexCount());
    eCosts_ = Matrix<double>(pattern_->getEdgeCount(), target_->getEdgeCount());
    if(weights)
        computeCosts(weights);
}

Problem::Problem(Type t, const QString &pattern, const QString &target, const QString &substitution, const QString &creation) : type_(t), deleteGraphs_(true) {
    Weights weights(substitution, creation);
    pattern_ = new Graph(pattern);
    target_ = new Graph(target);
    if(pattern_->getType() != target_->getType())
        Exception("Both graphs must have the same type (directed or undirected).");
    vCosts_ = Matrix<double>(pattern_->getVertexCount(), target_->getVertexCount());
    eCosts_ = Matrix<double>(pattern_->getEdgeCount(), target_->getEdgeCount());
    computeCosts(&weights);
}

Problem::~Problem() {
    if(deleteGraphs_) {
        delete pattern_;
        delete target_;
    }
}

Problem::Type Problem::getType() const {
    return type_;
}

void Problem::print(Printer *p) {
    p->dump("<problem edgemode=\""+Graph::toName(pattern_->getType())+"\" type=\""+toName(type_)+"\">");
    p->indent();
    p->dump("<query id=\""+pattern_->getID()+"\"/>");
    p->dump("<target id=\""+target_->getID()+"\"/>");
    p->unindent();
    p->dump("</problem>");
}

Graph *Problem::getQuery() const {
    return pattern_;
}

Graph *Problem::getTarget() const {
    return target_;
}

double Problem::getCost(int iQuery, int iTarget, GraphElement::Type type) const {
    switch(type) {
        case GraphElement::VERTEX:
            return vCosts_.getElement(iQuery, iTarget);
        case GraphElement::EDGE:
            return eCosts_.getElement(iQuery, iTarget);
        default:
            return 0;
    }
    // This should never happen
    return 0;
}

void Problem::addCost(int iQuery, int iTarget, double value, GraphElement::Type type) {
    switch(type) {
        case GraphElement::VERTEX:
            vCosts_.addElement(iQuery, iTarget, value);
            break;
        case GraphElement::EDGE:
            eCosts_.addElement(iQuery, iTarget, value);
            break;
        default:
            break;
    }
}

void Problem::save(const QString &filename) {
    FileUtils::save(this, filename);
}

void Problem::computeCosts(Weights *weights) {
    // Vertices creation costs
    for(auto v : pattern_->getVertices())
        v->setCost(weights->creationCost(v));
    for(auto v : target_->getVertices())
        v->setCost(weights->creationCost(v));
    // Vertices substitution costs
    for(int i=0; i < pattern_->getVertexCount(); ++i)
        for(int k=0; k < target_->getVertexCount(); ++k)
            vCosts_.setElement(i, k, weights->substitutionCost(pattern_->getVertex(i), target_->getVertex(k)));

    // Edges creation costs
    for(auto e : pattern_->getEdges())
        e->setCost(weights->creationCost(e));
    for(auto e : target_->getEdges())
        e->setCost(weights->creationCost(e));
    // Edges substitution costs
    for(int ij=0; ij < pattern_->getEdgeCount(); ++ij)
        for(int kl=0; kl < target_->getEdgeCount(); ++kl)
            eCosts_.setElement(ij, kl, weights->substitutionCost(pattern_->getEdge(ij), target_->getEdge(kl)));
}
