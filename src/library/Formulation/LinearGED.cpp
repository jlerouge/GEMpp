#include "LinearGED.h"

LinearGraphEditDistance::LinearGraphEditDistance(Problem *pb, double up) : Formulation(pb) {
    lp_ = new LinearProgram(Program::MINIMIZE);
    init(up);
}

LinearGraphEditDistance::~LinearGraphEditDistance() {
    delete lp_;
    for(auto v : y_variables)
        for(auto it : v)
            delete it;
}

void LinearGraphEditDistance::initVariables() {
    GraphEditDistance::initVariables();
    QString id;
    y_variables = Matrix<Variable*>(nEP, nET);
    for(ij=0; ij < nEP; ++ij) {
        for(kl=0; kl < nET; ++kl) {
            id = QString("y_%1,%2").arg(ij).arg(kl);
            y_variables.setElement(ij, kl, new Variable(id));
        }
    }
}

void LinearGraphEditDistance::initCosts() {
    GraphEditDistance::initCosts();
    y_costs = Matrix<double>(nEP, nET);
    for(ij=0; ij < nEP; ++ij)
        for(kl=0; kl < nET; ++kl)
            y_costs.setElement(ij, kl, pb_->getCost(GraphElement::EDGE, ij, kl) - pb_->getQuery()->getEdge(ij)->getCost() - pb_->getTarget()->getEdge(kl)->getCost());
}

void LinearGraphEditDistance::restrictProblem(double up) {
    GraphEditDistance::restrictProblem(up);
    if(up < 1) {
        for(auto row : y_variables)
            for(auto v : row)
                v->activate();

        for(ij=0; ij < nEP; ++ij) {
            i = pb_->getQuery()->getEdge(ij)->getOrigin()->getIndex();
            j = pb_->getQuery()->getEdge(ij)->getTarget()->getIndex();
            for(kl=0; kl < nET; ++kl) {
                k = pb_->getTarget()->getEdge(kl)->getOrigin()->getIndex();
                l = pb_->getTarget()->getEdge(kl)->getTarget()->getIndex();
                if(isDirected) {
                    // y_ij,kl must be 0 if the couple (x_i,k * x_j,l) is inactive
                    if(!(x_variables.getElement(i, k)->isActive() && x_variables.getElement(j, l)->isActive()))
                        y_variables.getElement(ij, kl)->deactivate();
                } else {
                    // y_ij,kl must be 0 if the couples (x_i,k * x_j,l) and (x_i,l * x_j,k) are inactive
                    if(!((x_variables.getElement(i, k)->isActive() && x_variables.getElement(j, l)->isActive()) ||
                         (x_variables.getElement(i, l)->isActive() && x_variables.getElement(j, k)->isActive())))
                        y_variables.getElement(ij, kl)->deactivate();
                }
            }
        }
    }
}

void LinearGraphEditDistance::initConstraints() {
    for(i=0; i < nVP; ++i)
        *lp_ += new LinearConstraint(LinearExpression::sum(x_variables.getRow(i)), LinearConstraint::LESS_EQ, 1.0);

    for(k=0; k < nVT; ++k)
        *lp_ += new LinearConstraint(LinearExpression::sum(x_variables.getCol(k)), LinearConstraint::LESS_EQ, 1.0);

    for(ij=0; ij < nEP; ++ij)
        *lp_ += new LinearConstraint(LinearExpression::sum(y_variables.getRow(ij)), LinearConstraint::LESS_EQ, 1.0);

    for(kl=0; kl < nET; ++kl)
        *lp_ += new LinearConstraint(LinearExpression::sum(y_variables.getCol(kl)), LinearConstraint::LESS_EQ, 1.0);

    // (F1)
    //    for(ij=0; ij < nEP; ++ij) {
    //        i = pb_->getQuery()->getEdge(ij)->getOrigin()->getIndex();
    //        j = pb_->getQuery()->getEdge(ij)->getTarget()->getIndex();
    //        for(kl=0; kl < nET; ++kl) {
    //            // Adding a constraint is useless if y_ij,kl is inactive
    //            if(y_variables.getElement(ij, kl)->isActive()) {
    //                k = pb_->getTarget()->getEdge(kl)->getOrigin()->getIndex();
    //                l = pb_->getTarget()->getEdge(kl)->getTarget()->getIndex();
    //                if(isDirected) {
    //                    *lp_ += new LinearConstraint(*(x_variables.getElement(i, k)) - *(y_variables.getElement(ij, kl)),
    //                                                 LinearConstraint::GREATER_EQ, 0.0);
    //                    *lp_ += new LinearConstraint(*(x_variables.getElement(j, l)) - *(y_variables.getElement(ij, kl)),
    //                                                 LinearConstraint::GREATER_EQ, 0.0);
    //                } else {
    //                    *lp_ += new LinearConstraint(*(x_variables.getElement(i, k)) + *(x_variables.getElement(i, l)) - *(y_variables.getElement(ij, kl)),
    //                                                 LinearConstraint::GREATER_EQ, 0.0);
    //                    *lp_ += new LinearConstraint(*(x_variables.getElement(j, k)) + *(x_variables.getElement(j, l)) - *(y_variables.getElement(ij, kl)),
    //                                                 LinearConstraint::GREATER_EQ, 0.0);
    //                }
    //            }
    //        }
    //    }

    // (F2)
    LinearExpression *e1, *e2;
    for(ij=0; ij < nEP; ++ij) {
        i = pb_->getQuery()->getEdge(ij)->getOrigin()->getIndex();
        j = pb_->getQuery()->getEdge(ij)->getTarget()->getIndex();
        for(k=0; k < nVT; ++k) {
            e1 = new LinearExpression();
            e2 = new LinearExpression();
            QSet<Edge *> edges = pb_->getTarget()->getVertex(k)->getEdges(Vertex::EDGE_OUT);
            for(auto it = edges.begin(); it != edges.end(); ++it)
                e1->addTerm(*(y_variables.getElement(ij,(*it)->getIndex())));
            edges = pb_->getTarget()->getVertex(k)->getEdges(Vertex::EDGE_IN);
            for(auto it = edges.begin(); it != edges.end(); ++it)
                e2->addTerm(*(y_variables.getElement(ij,(*it)->getIndex())));
            e1->addTerm(*(x_variables.getElement(i, k))*(-1));
            e2->addTerm(*(x_variables.getElement(j, k))*(-1));
            if(!isDirected) {
                e1->addTerm(*(x_variables.getElement(j, k))*(-1));
                e2->addTerm(*(x_variables.getElement(i, k))*(-1));
            }
            *lp_ += new LinearConstraint(e1, LinearConstraint::LESS_EQ, 0.0);
            *lp_ += new LinearConstraint(e2, LinearConstraint::LESS_EQ, 0.0);
        }
    }
}

void LinearGraphEditDistance::initObjective() {
    LinearExpression *exp = new LinearExpression();

    for(i=0; i < nVP; ++i)
        for(k=0; k < nVT; ++k)
            *exp += *x_variables.getElement(i, k)*x_costs.getElement(i, k);

    for(ij=0; ij < nEP; ++ij)
        for(kl=0; kl < nET; ++kl)
            *exp += *y_variables.getElement(ij, kl)*y_costs.getElement(ij, kl);

    // Constant part of the objective
    double c = 0;
    for(i=0; i < nVP; ++i)
        c += pb_->getQuery()->getVertex(i)->getCost();
    for(k=0; k < nVT; ++k)
        c += pb_->getTarget()->getVertex(k)->getCost();
    for(ij=0; ij < nEP; ++ij)
        c += pb_->getQuery()->getEdge(ij)->getCost();
    for(kl=0; kl < nET; ++kl)
        c += pb_->getTarget()->getEdge(kl)->getCost();

    *exp += c;
    lp_->setObjective(exp);
}
