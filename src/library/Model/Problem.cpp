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

Problem::Problem(Type type, Graph *query, Graph *target, Problem *parent) : type_(type), query_(query), target_(target), parent_(parent), mutex_(QMutex::Recursive) {
    if(query_->getType() != target_->getType())
        Exception("Both graphs must have the same type (directed or undirected).");
    vCosts_ = Matrix<double>(query_->getVertexCount(), target_->getVertexCount());
    eCosts_ = Matrix<double>(query_->getEdgeCount(), target_->getEdgeCount());
}

Problem::~Problem() {
    //qDeleteAll(subproblems_);
}

Problem::Type Problem::getType() const {
    return type_;
}

Graph *Problem::getQuery() const {
    return query_;
}

Graph *Problem::getTarget() const {
    return target_;
}

Problem *Problem::getParent() const {
    return parent_;
}

double Problem::getCost(GraphElement::Type type, int queryIndex, int targetIndex) const {
    switch(type) {
        case GraphElement::VERTEX:
            return vCosts_.getElement(queryIndex, targetIndex);
        case GraphElement::EDGE:
            return eCosts_.getElement(queryIndex, targetIndex);
        default:
            break;
    }
    return 0;
}

double Problem::getCost(CostIndex costIndex) const {
    return getCost(costIndex.type, costIndex.queryIndex, costIndex.targetIndex);
}

void Problem::addCost(GraphElement::Type type, int queryIndex, int targetIndex, double value) {
    switch(type) {
        case GraphElement::VERTEX:
            vCosts_.addElement(queryIndex, targetIndex, value);
            break;
        case GraphElement::EDGE:
            eCosts_.addElement(queryIndex, targetIndex, value);
            break;
        default:
            break;
    }
}

void Problem::addCost(CostIndex costIndex, double value) {
    addCost(costIndex.type, costIndex.queryIndex, costIndex.targetIndex, value);
}

void Problem::computeCosts(Weights *weights) {
    // Creation costs
    query_->computeCosts(weights);
    target_->computeCosts(weights);

    // Substitution costs
    double cost;

    // Prevent from emitting ready signal too early
    mutex_.lock();

    // Vertices
    Vertex *qv, *tv;
    for(int i=0; i < query_->getVertexCount(); ++i) {
        for(int k=0; k < target_->getVertexCount(); ++k) {
            qv = query_->getVertex(i);
            tv = target_->getVertex(k);
            if(qv->getGraph() && tv->getGraph()) {
                computeGraphCost(qv->getGraph(), tv->getGraph(), weights, GraphElement::VERTEX, i, k);
                continue;
            }

            if(qv->getGraph())
                cost = computeCost(tv, qv->getGraph(), weights);
            else if (tv->getGraph())
                cost = computeCost(qv, tv->getGraph(), weights);
            else
                cost = weights->substitutionCost(qv, tv);
            vCosts_.setElement(i, k, cost);
        }
    }

    // Edges
    Edge *qe, *te;
    for(int ij=0; ij < query_->getEdgeCount(); ++ij) {
        for(int kl=0; kl < target_->getEdgeCount(); ++kl) {
            qe = query_->getEdge(ij);
            te = target_->getEdge(kl);
            if(qe->getGraph() && te->getGraph()) {
                computeGraphCost(qe->getGraph(), te->getGraph(), weights, GraphElement::EDGE, ij, kl);
                continue;
            }

            if(qe->getGraph())
                cost = computeCost(te, qe->getGraph(), weights);
            else if (te->getGraph())
                cost = computeCost(qe, te->getGraph(), weights);
            else
                cost = weights->substitutionCost(qe, te);
            eCosts_.setElement(ij, kl, cost);
        }
    }

    if(subproblems_.isEmpty())
        emit ready(const_cast<Problem *>(this));

    mutex_.unlock();
}

void Problem::print(Printer *p) {
    p->dump("<problem edgemode=\""+Graph::toName(query_->getType())+"\" type=\""+toName(type_)+"\">");
    p->indent();
    p->dump("<query id=\""+query_->getID()+"\"/>");
    p->dump("<target id=\""+target_->getID()+"\"/>");
    p->unindent();
    p->dump("</problem>");
}

void Problem::save(const QString &filename) {
    FileUtils::save(this, filename);
}

double Problem::computeCost(GraphElement *element, Graph *graph, Weights *weights) {
    QList<double> costs;
    QList<GraphElement *> terminals = graph->getTerminals(element->getType());
    for(GraphElement *other : terminals)
        costs.append(weights->substitutionCost(element, other));
    int iMin = std::min_element(costs.begin(), costs.end()) - costs.begin();
    return costs[iMin] + graph->getCost() - terminals[iMin]->getCost();
}

void Problem::computeGraphCost(Graph *g1, Graph *g2, Weights *weights, GraphElement::Type type, int queryIndex, int targetIndex) {
    Problem *problem = new Problem(Problem::GED, g1, g2, const_cast<Problem *>(this));
    CostIndex costIndex = {type, queryIndex, targetIndex};
    subproblems_.insert(problem, costIndex);
    emit prepare(problem, weights);
}

void Problem::updateCost(Problem *subproblem, double value) {
    mutex_.lock();
    if(subproblems_.contains(subproblem)) {
        addCost(subproblems_.value(subproblem), value);
        subproblems_.remove(subproblem);
        if(subproblems_.isEmpty())
            emit ready(const_cast<Problem *>(this));
        delete subproblem;
    }
    mutex_.unlock();
}
