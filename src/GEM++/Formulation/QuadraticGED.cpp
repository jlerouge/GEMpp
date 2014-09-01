#include "QuadraticGED.h"

QuadGraphEditDistance::QuadGraphEditDistance(Problem *pb, double up) : Formulation(pb) {
    qp_ = new QuadProgram(QuadProgram::MINIMIZE);
    init(up);
}

QuadGraphEditDistance::~QuadGraphEditDistance() {
    delete qp_;
}

void QuadGraphEditDistance::initVariables() {
    GraphEditDistance::initVariables();
    y1_variables = Matrix<Quad>(nEP, nET);
    if(!isDirected)
        y2_variables = Matrix<Quad>(nEP, nET);
    for(ij=0; ij < nEP; ++ij) {
        i = pb_->getPattern()->getEdge(ij)->getOrigin()->getIndex();
        j = pb_->getPattern()->getEdge(ij)->getTarget()->getIndex();
        for(kl=0; kl < nET; ++kl) {
            k = pb_->getTarget()->getEdge(kl)->getOrigin()->getIndex();
            l = pb_->getTarget()->getEdge(kl)->getTarget()->getIndex();
            y1_variables.setElement(ij, kl, qMakePair(x_variables.getElement(i, k), x_variables.getElement(j, l)));
            if(!isDirected)
                y2_variables.setElement(ij, kl, qMakePair(x_variables.getElement(i, l), x_variables.getElement(j, k)));
        }
    }
}

void QuadGraphEditDistance::initCosts() {
    GraphEditDistance::initCosts();
    y_costs = Matrix<double>(nEP, nET);
    for(ij=0; ij < nEP; ++ij)
        for(kl=0; kl < nET; ++kl)
            y_costs.setElement(ij, kl, pb_->getCost(ij, kl, GraphElement::EDGE) - pb_->getPattern()->getEdge(ij)->getCost() - pb_->getTarget()->getEdge(kl)->getCost());
}

void QuadGraphEditDistance::initConstraints() {
    QList<Quad> ql;

    for(i=0; i < nVP; ++i)
        *qp_ += new LinearConstraint(LinearExpression::sum(x_variables.getRow(i)), LinearConstraint::LESS_EQ, 1.0);

    for(k=0; k < nVT; ++k)
        *qp_ += new LinearConstraint(LinearExpression::sum(x_variables.getCol(k)), LinearConstraint::LESS_EQ, 1.0);

    for(ij=0; ij < nEP; ++ij) {
        ql = y1_variables.getRow(ij);
        if(!isDirected)
            ql.append(y2_variables.getRow(ij));
        *qp_ += new QuadConstraint(QuadExpression::sum(ql), QuadConstraint::LESS_EQ, 1.0);
    }

    for(kl=0; kl < nET; ++kl) {
        ql = y1_variables.getCol(kl);
        if(!isDirected)
            ql.append(y2_variables.getCol(kl));
        *qp_ += new QuadConstraint(QuadExpression::sum(ql), QuadConstraint::LESS_EQ, 1.0);
    }
}

void QuadGraphEditDistance::initObjective() {
    QuadExpression *exp = new QuadExpression();

    for(i=0; i < nVP; ++i)
        for(k=0; k < nVT; ++k)
            exp->addTerm(*x_variables.getElement(i, k)*x_costs.getElement(i, k));

    for(ij=0; ij < nEP; ++ij)
        for(kl=0; kl < nET; ++kl) {
            exp->addQuadTerm(y1_variables.getElement(ij, kl)*y_costs.getElement(ij, kl));
            if(!isDirected)
                exp->addQuadTerm(y2_variables.getElement(ij, kl)*y_costs.getElement(ij, kl));
        }

    // Constant part of the objective
    double c = 0;
    for(i=0; i < nVP; ++i)
        c += pb_->getPattern()->getVertex(i)->getCost();
    for(k=0; k < nVT; ++k)
        c += pb_->getTarget()->getVertex(k)->getCost();
    for(ij=0; ij < nEP; ++ij)
        c += pb_->getPattern()->getEdge(ij)->getCost();
    for(kl=0; kl < nET; ++kl)
        c += pb_->getTarget()->getEdge(kl)->getCost();

    *exp += c;
    qp_->setObjective(exp);
}
