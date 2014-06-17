#include "BipartiteEdges.h"

BipartiteEdges::BipartiteEdges(Problem *pb, int i, int k) : Formulation(pb) {
    lp_ = new LinearProgram(Program::MINIMIZE);
    vi_ = pb->getPattern()->getVertex(i);
    vk_ = pb->getTarget()->getVertex(k);
    init();
}

BipartiteEdges::~BipartiteEdges() {
    delete lp_;
    for(auto v : y_variables)
        for(auto it : v)
            delete it;
}

QPair<int,int> BipartiteEdges::updateLowerBound(Solution *sol) {
    Q_UNUSED(sol);
    GEM_exception("Bipartite edges-subproblem does not handle row-generation.");
    return qMakePair(0, 0);
}

void BipartiteEdges::initVariables() {
    int nEi, nEk;
    nEi = vi_->getEdges(Vertex::EDGE_IN_OUT).size();
    nEk = vk_->getEdges(Vertex::EDGE_IN_OUT).size();

    QString id;
    y_variables = Matrix<Variable*>(nEi, nEk);
    for(ij=0; ij < nEi; ++ij) {
        for(kl=0; kl < nEk; ++kl) {
            id = QString("y_%1,%2").arg(vi_->getEdge(ij, Vertex::EDGE_IN_OUT)->getIndex()).arg(vk_->getEdge(kl, Vertex::EDGE_IN_OUT)->getIndex());
            y_variables.setElement(ij, kl, new Variable(id));
        }
    }
}

void BipartiteEdges::initCosts() {}

void BipartiteEdges::restrictProblem(double up) {
    Q_UNUSED(up);
}

void BipartiteEdges::initConstraints() {
    int nEi, nEk;
    nEi = vi_->getEdges(Vertex::EDGE_IN_OUT).size();
    nEk = vk_->getEdges(Vertex::EDGE_IN_OUT).size();

    for(ij=0; ij < nEi; ++ij, ++cuid_)
        *lp_ += new LinearConstraint(LinearExpression::sum(y_variables.getRow(ij)), LinearConstraint::LESS_EQ, 1.0, QString::number(cuid_));

    for(kl=0; kl < nEk; ++kl, ++cuid_)
        *lp_ += new LinearConstraint(LinearExpression::sum(y_variables.getCol(kl)), LinearConstraint::LESS_EQ, 1.0, QString::number(cuid_));
}

void BipartiteEdges::initObjective() {
    int nEi, nEk;
    nEi = vi_->getEdges(Vertex::EDGE_IN_OUT).size();
    nEk = vk_->getEdges(Vertex::EDGE_IN_OUT).size();
    LinearExpression *exp = new LinearExpression();

    for(ij=0; ij < nEi; ++ij)
        for(kl=0; kl < nEk; ++kl)
            *exp += *y_variables.getElement(ij,kl)*(pb_->getCost(vi_->getEdge(ij, Vertex::EDGE_IN_OUT)->getIndex(), vk_->getEdge(kl, Vertex::EDGE_IN_OUT)->getIndex(), GraphElement::EDGE)
                                                    - vi_->getEdge(ij, Vertex::EDGE_IN_OUT)->getCost() - vk_->getEdge(kl, Vertex::EDGE_IN_OUT)->getCost());

    // Constant part of the objective
    double c = 0;
    for(ij=0; ij < nEi; ++ij)
        c += vi_->getEdge(ij, Vertex::EDGE_IN_OUT)->getCost();
    for(kl=0; kl < nEk; ++kl)
        c += vk_->getEdge(kl, Vertex::EDGE_IN_OUT)->getCost();

    *exp += c;
    lp_->setObjective(exp);
}

void BipartiteEdges::cut(Solution *sol, CutMethod cm) {
    Q_UNUSED(sol);
    Q_UNUSED(cm);
}
