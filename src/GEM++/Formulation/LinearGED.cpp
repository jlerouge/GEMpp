#include "LinearGED.h"

LinearGraphEditDistance::LinearGraphEditDistance(Problem *pb, bool low, double up) : Formulation(pb, low) {
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
            //id = QString("y_%1,%2").arg(pb_->getPattern()->getEdge(ij)->getIndex()).arg(pb_->getTarget()->getEdge(kl)->getIndex());
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
            y_costs.setElement(ij, kl, pb_->getCost(ij, kl, GraphElement::EDGE) - pb_->getPattern()->getEdge(ij)->getCost() - pb_->getTarget()->getEdge(kl)->getCost());
}

void LinearGraphEditDistance::restrictProblem(double up) {
    GraphEditDistance::restrictProblem(up);
    if(up < 1) {
        for(auto row : y_variables)
            for(auto v : row)
                v->activate();

        for(ij=0; ij < nEP; ++ij) {
            i = pb_->getPattern()->getEdge(ij)->getOrigin()->getIndex();
            j = pb_->getPattern()->getEdge(ij)->getTarget()->getIndex();
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
    for(i=0; i < nVP; ++i, ++cuid_)
        *lp_ += new LinearConstraint(LinearExpression::sum(x_variables.getRow(i)), LinearConstraint::LESS_EQ, 1.0, QString::number(cuid_));

    for(k=0; k < nVT; ++k, ++cuid_)
        *lp_ += new LinearConstraint(LinearExpression::sum(x_variables.getCol(k)), LinearConstraint::LESS_EQ, 1.0, QString::number(cuid_));

    for(ij=0; ij < nEP; ++ij, ++cuid_)
        *lp_ += new LinearConstraint(LinearExpression::sum(y_variables.getRow(ij)), LinearConstraint::LESS_EQ, 1.0, QString::number(cuid_));

    for(kl=0; kl < nET; ++kl, ++cuid_)
        *lp_ += new LinearConstraint(LinearExpression::sum(y_variables.getCol(kl)), LinearConstraint::LESS_EQ, 1.0, QString::number(cuid_));

    if(!low_) {
        for(ij=0; ij < nEP; ++ij) {
            i = pb_->getPattern()->getEdge(ij)->getOrigin()->getIndex();
            j = pb_->getPattern()->getEdge(ij)->getTarget()->getIndex();
            for(kl=0; kl < nET; ++kl) {
                // Adding a constraint is useless if y_ij,kl is inactive
                if(y_variables.getElement(ij, kl)->isActive()) {
                    k = pb_->getTarget()->getEdge(kl)->getOrigin()->getIndex();
                    l = pb_->getTarget()->getEdge(kl)->getTarget()->getIndex();
                    if(isDirected) {
                        *lp_ += new LinearConstraint(*(x_variables.getElement(i, k)) - *(y_variables.getElement(ij, kl)),
                                        LinearConstraint::GREATER_EQ, 0.0, QString::number(cuid_)); ++cuid_;
                        *lp_ += new LinearConstraint(*(x_variables.getElement(j, l)) - *(y_variables.getElement(ij, kl)),
                                        LinearConstraint::GREATER_EQ, 0.0, QString::number(cuid_)); ++cuid_;
                        *lp_ += new LinearConstraint(*(x_variables.getElement(i, k)) + *(x_variables.getElement(j, l)) - *(y_variables.getElement(ij, kl)),
                                        LinearConstraint::LESS_EQ, 1.0, QString::number(cuid_)); ++cuid_;
                    } else {
                        *lp_ += new LinearConstraint(*(x_variables.getElement(i, k)) + *(x_variables.getElement(i, l)) - *(y_variables.getElement(ij, kl)),
                                        LinearConstraint::GREATER_EQ, 0.0, QString::number(cuid_)); ++cuid_;
                        *lp_ += new LinearConstraint(*(x_variables.getElement(j, k)) + *(x_variables.getElement(j, l)) - *(y_variables.getElement(ij, kl)),
                                        LinearConstraint::GREATER_EQ, 0.0, QString::number(cuid_)); ++cuid_;
                        *lp_ += new LinearConstraint(*(x_variables.getElement(i, k)) + *(x_variables.getElement(j, l)) + *(x_variables.getElement(i, l)) +
                                        *(x_variables.getElement(j, k)) - *(y_variables.getElement(ij, kl)), LinearConstraint::LESS_EQ, 1.0, QString::number(cuid_)); ++cuid_;
                    }
                } else {
                    cuid_ += 3;
                }
            }
        }
    } else {
        for(ij=0; ij < nEP; ++ij) {
            i = pb_->getPattern()->getEdge(ij)->getOrigin()->getIndex();
            j = pb_->getPattern()->getEdge(ij)->getTarget()->getIndex();
            LinearExpression *e1 = new LinearExpression();
            LinearExpression *e2 = new LinearExpression();
            LinearExpression *e3 = new LinearExpression();
            for(kl=0; kl < nET; ++kl) {
                // Adding terms is useless if y_ij,kl is inactive
                if(y_variables.getElement(ij, kl)->isActive()) {
                    k = pb_->getTarget()->getEdge(kl)->getOrigin()->getIndex();
                    l = pb_->getTarget()->getEdge(kl)->getTarget()->getIndex();
                    e1->addTerm(*(x_variables.getElement(i, k)));
                    e3->addTerm(*(x_variables.getElement(i, k)));
                    if(!isDirected) {
                        e1->addTerm(*(x_variables.getElement(i, l)));
                        e3->addTerm(*(x_variables.getElement(i, l)));
                    }
                    e2->addTerm(*(x_variables.getElement(j, l)));
                    e3->addTerm(*(x_variables.getElement(j, l)));
                    if(!isDirected) {
                        e2->addTerm(*(x_variables.getElement(j, k)));
                        e3->addTerm(*(x_variables.getElement(j, k)));
                    }
                    e1->addTerm(*(y_variables.getElement(ij, kl))*(-1));
                    e2->addTerm(*(y_variables.getElement(ij, kl))*(-1));
                    e3->addTerm(*(y_variables.getElement(ij, kl))*(-1));
                }
            }
            *lp_ += new LinearConstraint(e1, LinearConstraint::GREATER_EQ, 0.0, QString("A%1").arg(cuid_)); ++cuid_;
            *lp_ += new LinearConstraint(e2, LinearConstraint::GREATER_EQ, 0.0, QString("A%1").arg(cuid_)); ++cuid_;
            *lp_ += new LinearConstraint(e3, LinearConstraint::LESS_EQ, nET, QString("A%1").arg(cuid_)); ++cuid_;
        }
        for(kl=0; kl < nET; ++kl) {
            k = pb_->getTarget()->getEdge(kl)->getOrigin()->getIndex();
            l = pb_->getTarget()->getEdge(kl)->getTarget()->getIndex();
            LinearExpression *e1 = new LinearExpression();
            LinearExpression *e2 = new LinearExpression();
            LinearExpression *e3 = new LinearExpression();
            for(ij=0; ij < nEP; ++ij) {
                // Adding terms is useless if y_ij,kl is inactive
                if(y_variables.getElement(ij, kl)->isActive()) {
                    i = pb_->getPattern()->getEdge(ij)->getOrigin()->getIndex();
                    j = pb_->getPattern()->getEdge(ij)->getTarget()->getIndex();
                    e1->addTerm(*(x_variables.getElement(i, k)));
                    e3->addTerm(*(x_variables.getElement(i, k)));
                    if(!isDirected) {
                        e1->addTerm(*(x_variables.getElement(i, l)));
                        e3->addTerm(*(x_variables.getElement(i, l)));
                    }
                    e2->addTerm(*(x_variables.getElement(j, l)));
                    e3->addTerm(*(x_variables.getElement(j, l)));
                    if(!isDirected) {
                        e2->addTerm(*(x_variables.getElement(j, k)));
                        e3->addTerm(*(x_variables.getElement(j, k)));
                    }
                    e1->addTerm(*(y_variables.getElement(ij, kl))*(-1));
                    e2->addTerm(*(y_variables.getElement(ij, kl))*(-1));
                    e3->addTerm(*(y_variables.getElement(ij, kl))*(-1));
                }
            }
            *lp_ += new LinearConstraint(e1, LinearConstraint::GREATER_EQ, 0.0, QString("A%1").arg(cuid_)); ++cuid_;
            *lp_ += new LinearConstraint(e2, LinearConstraint::GREATER_EQ, 0.0, QString("A%1").arg(cuid_)); ++cuid_;
            *lp_ += new LinearConstraint(e3, LinearConstraint::LESS_EQ, nEP, QString("A%1").arg(cuid_)); ++cuid_;
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
        c += pb_->getPattern()->getVertex(i)->getCost();
    for(k=0; k < nVT; ++k)
        c += pb_->getTarget()->getVertex(k)->getCost();
    for(ij=0; ij < nEP; ++ij)
        c += pb_->getPattern()->getEdge(ij)->getCost();
    for(kl=0; kl < nET; ++kl)
        c += pb_->getTarget()->getEdge(kl)->getCost();

    *exp += c;
    lp_->setObjective(exp);
}

QPair<int,int> LinearGraphEditDistance::updateLowerBound(Solution *sol){
    Q_UNUSED(sol);
    return qMakePair(0, 0);
    // FIXME
    // FIXME : cuid_

    //    LinearConstraint *c1 = 0, *c2 = 0, *c3 = 0;
    //    int nbErrors = 0;

    //    for(auto vec : x_variables)
    //        for(auto var : vec)
    //            var->setValue(sol->getValue(var->getID()));

    //    for(auto vec : y_variables)
    //        for(auto var : vec)
    //            var->setValue(sol->getValue(var->getID()));

    //    for(ij=0; ij < nEP; ++ij) {
    //        i = pb_->getPattern()->getEdge(ij)->getOrigin()->getIndex();
    //        j = pb_->getPattern()->getEdge(ij)->getTarget()->getIndex();
    //        for(kl=0; kl < nET; ++kl) {
    //            k = pb_->getTarget()->getEdge(kl)->getOrigin()->getIndex();
    //            l = pb_->getTarget()->getEdge(kl)->getTarget()->getIndex();
    //            switch(pb_->getPattern()->getType()) {
    //                case Graph::DIRECTED:
    //                    c1 = new LinearConstraint(*(x_variables.getElement(i, k)) - *(y_variables.getElement(ij, kl)), LinearConstraint::GREATER_EQ, 0.0);
    //                    c2 = new LinearConstraint(*(x_variables.getElement(j, l)) - *(y_variables.getElement(ij, kl)), LinearConstraint::GREATER_EQ, 0.0);
    //                    c3 = new LinearConstraint(*(x_variables.getElement(i, k)) + *(x_variables.getElement(j, l)) - *(y_variables.getElement(ij, kl)), LinearConstraint::LESS_EQ, 1.0);
    //                    break;
    //                case Graph::UNDIRECTED:
    //                    c1 = new LinearConstraint(*(x_variables.getElement(i, k)) + *(x_variables.getElement(i, l)) - *(y_variables.getElement(ij, kl)), LinearConstraint::GREATER_EQ, 0.0);
    //                    c2 = new LinearConstraint(*(x_variables.getElement(j, k)) + *(x_variables.getElement(j, l)) - *(y_variables.getElement(ij, kl)), LinearConstraint::GREATER_EQ, 0.0);
    //                    c3 = new LinearConstraint(*(x_variables.getElement(i, k)) + *(x_variables.getElement(j, l)) + *(x_variables.getElement(i, l)) + *(x_variables.getElement(j, k)) - *(y_variables.getElement(ij, kl)), LinearConstraint::LESS_EQ, 1.0);
    //                    break;
    //            }
    //            if(!c1->eval()) {
    //                ++nbErrors;
    //                *lp_ += c1;
    //            } else {
    //                delete c1;
    //            }
    //            if(!c2->eval()) {
    //                ++nbErrors;
    //                *lp_ += c2;
    //            } else {
    //                delete c2;
    //            }
    //            if(!c3->eval()) {
    //                ++nbErrors;
    //                *lp_ += c3;
    //            } else {
    //                delete c3;
    //            }
    //        }
    //    }
    //    return QPair<int,int>(nbErrors, 2*nEP*nET+nEP+nET+nVP+nVT);
}
