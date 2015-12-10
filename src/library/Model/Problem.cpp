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

Problem::Problem(Type t, Graph *query, Graph *target) : type_(t), query_(query), target_(target) {
    if(query_->getType() != target_->getType())
        Exception("Both graphs must have the same type (directed or undirected).");
    vCosts_ = Matrix<double>(query_->getVertexCount(), target_->getVertexCount());
    eCosts_ = Matrix<double>(query_->getEdgeCount(), target_->getEdgeCount());
}

Problem::~Problem() {
    qDeleteAll(subProblems_);
}

Problem::Type Problem::getType() const {
    return type_;
}

void Problem::print(Printer *p) {
    p->dump("<problem edgemode=\""+Graph::toName(query_->getType())+"\" type=\""+toName(type_)+"\">");
    p->indent();
    p->dump("<query id=\""+query_->getID()+"\"/>");
    p->dump("<target id=\""+target_->getID()+"\"/>");
    p->unindent();
    p->dump("</problem>");
}

Graph *Problem::getQuery() const {
    return query_;
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
    // Creation costs
    query_->computeCosts(weights);
    target_->computeCosts(weights);

    double cost;
    Vertex *qv, *tv;
    // Vertices substitution costs
    for(int i=0; i < query_->getVertexCount(); ++i) {
        for(int k=0; k < target_->getVertexCount(); ++k) {
            qv = query_->getVertex(i);
            tv = target_->getVertex(k);
            if(qv->getGraph() && tv->getGraph()) {
                computeGraphCost(qv->getGraph(), tv->getGraph(), weights, GraphElement::VERTEX, i, k);
                continue;
            }
            if (qv->getGraph())
                cost = computeCost(tv, qv->getGraph(), weights);
            else if (tv->getGraph())
                cost = computeCost(qv, tv->getGraph(), weights);
            else
                cost = weights->substitutionCost(qv, tv);
            vCosts_.setElement(i, k, cost);
        }
    }

    Edge *qe, *te;
    // Edges substitution costs
    for(int ij=0; ij < query_->getEdgeCount(); ++ij) {
        for(int kl=0; kl < target_->getEdgeCount(); ++kl) {
            qe = query_->getEdge(ij);
            te = target_->getEdge(kl);
            if(qe->getGraph() && te->getGraph()) {
                computeGraphCost(qe->getGraph(), te->getGraph(), weights, GraphElement::EDGE, ij, kl);
                continue;
            }
            if (qe->getGraph())
                cost = computeCost(te, qe->getGraph(), weights);
            else if (te->getGraph())
                cost = computeCost(qe, te->getGraph(), weights);
            else
                cost = weights->substitutionCost(qe, te);
            eCosts_.setElement(ij, kl, cost);
        }
    }
}

double Problem::computeCost(GraphElement *element, Graph *graph, Weights *weights) {
    QList<double> costs;
    QList<GraphElement *> terminals = graph->getTerminals(element->getType());
    for(GraphElement *other : terminals)
        costs.append(weights->substitutionCost(element, other));
    int iMin = std::min_element(costs.begin(), costs.end()) - costs.begin();
    return costs[iMin] + graph->getCost() - terminals[iMin]->getCost();
}

void Problem::computeGraphCost(Graph *g1, Graph *g2, Weights *weights, GraphElement::Type type, int iQuery, int iTarget) {
    Problem *subProblem = new Problem(Problem::GED, g1, g2);
    subProblems_.append(subProblem);
    emit solveSubProblem(subProblem, weights, type, iQuery, iTarget);
}
