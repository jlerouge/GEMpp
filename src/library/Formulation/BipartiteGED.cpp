#include "BipartiteGED.h"

BipartiteGraphMatching::BipartiteGraphMatching(Problem *pb, double up) : Formulation(pb) {
    lp_ = new LinearProgram(Program::MINIMIZE);
    init(up);
}

BipartiteGraphMatching::~BipartiteGraphMatching() {
    delete lp_;
}

void BipartiteGraphMatching::initConstraints() {
    for(i=0; i < nVP; ++i)
        *lp_ += new LinearConstraint(LinearExpression::sum(x_variables.getRow(i)), LinearConstraint::LESS_EQ, 1.0);

    for(k=0; k < nVT; ++k)
        *lp_ += new LinearConstraint(LinearExpression::sum(x_variables.getCol(k)), LinearConstraint::LESS_EQ, 1.0);
}

void BipartiteGraphMatching::initObjective() {
    LinearExpression *exp = new LinearExpression();

    for(i=0; i < nVP; ++i)
        for(k=0; k < nVT; ++k)
            *exp += *x_variables.getElement(i, k)*x_costs.getElement(i, k);

    // Constant part of the objective
    double c = 0;
    for(i=0; i < nVP; ++i)
        c += pb_->getQuery()->getVertex(i)->getCost();
    for(k=0; k < nVT; ++k)
        c += pb_->getTarget()->getVertex(k)->getCost();

    *exp += c;
    lp_->setObjective(exp);
}
