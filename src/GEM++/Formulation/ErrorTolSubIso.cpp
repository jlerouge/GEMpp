#include "ErrorTolSubIso.h"

ErrorTolerantSubgraphIsomorphism::ErrorTolerantSubgraphIsomorphism(Problem *pb, double up, bool induced) : Formulation(pb, induced) {
    lp_ = new LinearProgram(Program::MINIMIZE);
    init(up);
}

void ErrorTolerantSubgraphIsomorphism::initCosts() {
    SubgraphIsomorphism::initCosts();
    for(i=0; i < nVP; ++i)
        for(k=0; k < nVT; ++k)
            x_costs.addElement(i, k, -pb_->getPattern()->getVertex(i)->getCost());
    for(ij=0; ij < nEP; ++ij)
        for(kl=0; kl < nET; ++kl)
            y_costs.addElement(ij, kl, -pb_->getPattern()->getEdge(ij)->getCost());
}

void ErrorTolerantSubgraphIsomorphism::initConstraints() {
    for(i=0; i < nVP; ++i)
        *lp_ += new LinearConstraint(LinearExpression::sum(x_variables.getRow(i)), LinearConstraint::LESS_EQ, 1.0);

    for(k=0; k < nVT; ++k)
        *lp_ += new LinearConstraint(LinearExpression::sum(x_variables.getCol(k)), LinearConstraint::LESS_EQ, 1.0);

    for(ij=0; ij < nEP; ++ij)
        *lp_ += new LinearConstraint(LinearExpression::sum(y_variables.getRow(ij)), LinearConstraint::LESS_EQ, 1.0);

    // (F1a)
    //    for(ij=0; ij < nEP; ++ij) {
    //        i = pb_->getPattern()->getEdge(ij)->getOrigin()->getIndex();
    //        j = pb_->getPattern()->getEdge(ij)->getTarget()->getIndex();
    //        for(kl=0; kl < nET; ++kl) {
    //            if(y_variables.getElement(ij, kl)->isActive()) {
    //                k = pb_->getTarget()->getEdge(kl)->getOrigin()->getIndex();
    //                l = pb_->getTarget()->getEdge(kl)->getTarget()->getIndex();
    //                if(isDirected) {
    //                    *lp_ += new LinearConstraint(*(x_variables.getElement(i, k)) - *(y_variables.getElement(ij, kl)),
    //                                    LinearConstraint::GREATER_EQ, 0.0);
    //                    *lp_ += new LinearConstraint(*(x_variables.getElement(j, l)) - *(y_variables.getElement(ij, kl)),
    //                                    LinearConstraint::GREATER_EQ, 0.0);
    //                } else {
    //                    *lp_ += new LinearConstraint(*(x_variables.getElement(i, k)) + *(x_variables.getElement(i, l)) - *(y_variables.getElement(ij, kl)),
    //                                    LinearConstraint::GREATER_EQ, 0.0);
    //                    *lp_ += new LinearConstraint(*(x_variables.getElement(j, l)) + *(x_variables.getElement(j, k)) - *(y_variables.getElement(ij, kl)),
    //                                    LinearConstraint::GREATER_EQ, 0.0);
    //                }
    //            }
    //        }
    //    }

    // (F2a)
    LinearExpression *e1, *e2;
    for(ij=0; ij < nEP; ++ij) {
        i = pb_->getPattern()->getEdge(ij)->getOrigin()->getIndex();
        j = pb_->getPattern()->getEdge(ij)->getTarget()->getIndex();
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

    // (F2a) WTF
    //    LinearExpression *e1init, *e3init, *e1, *e2, *e3, *e4;
    //    for(ij=0; ij < nEP; ++ij) {
    //        i = pb_->getPattern()->getEdge(ij)->getOrigin()->getIndex();
    //        j = pb_->getPattern()->getEdge(ij)->getTarget()->getIndex();
    //        e1init = new LinearExpression();
    //        if(isDirected)
    //            e3init = new LinearExpression();

    //        for(k=0; k < nVT; ++k) {
    //            e1init->addTerm(*(x_variables.getElement(i, k)));
    //            if(isDirected)
    //                e3init->addTerm(*(x_variables.getElement(j, k)));
    //            else
    //                e1init->addTerm(*(x_variables.getElement(j, k)));
    //        }
    //        for(kl=0; kl < nET; ++kl) {
    //            e1init->addTerm(*(y_variables.getElement(ij, kl))*(-1));
    //            if(isDirected)
    //                e3init->addTerm(*(y_variables.getElement(ij, kl))*(-1));
    //        }

    //        for(k=0; k < nVT; ++k) {
    //            e1 = new LinearExpression(*e1init);
    //            e2 = new LinearExpression();
    //            if(isDirected) {
    //                e3 = new LinearExpression(*e3init);
    //                e4 = new LinearExpression();
    //            }

    //            e1->addTerm(*(x_variables.getElement(i, k))*(-1));
    //            e2->addTerm(*(x_variables.getElement(i, k)));
    //            if(isDirected) {
    //                e3->addTerm(*(x_variables.getElement(j, k))*(-1));
    //                e4->addTerm(*(x_variables.getElement(j, k)));
    //            } else {
    //                e1->addTerm(*(x_variables.getElement(j, k))*(-1));
    //                e2->addTerm(*(x_variables.getElement(j, k)));
    //            }

    //            QSet<Edge *> edges = pb_->getTarget()->getVertex(k)->getEdges(Vertex::EDGE_OUT);
    //            for(auto it = edges.begin(); it != edges.end(); ++it) {
    //                e1->addTerm(*(y_variables[ij][(*it)->getIndex()]));
    //                e2->addTerm(*(y_variables[ij][(*it)->getIndex()])*(-1));
    //            }
    //            edges = pb_->getTarget()->getVertex(k)->getEdges(Vertex::EDGE_IN);
    //            for(auto it = edges.begin(); it != edges.end(); ++it) {
    //                if(isDirected) {
    //                    e3->addTerm(*(y_variables[ij][(*it)->getIndex()]));
    //                    e4->addTerm(*(y_variables[ij][(*it)->getIndex()])*(-1));
    //                } else {
    //                    e1->addTerm(*(y_variables[ij][(*it)->getIndex()]));
    //                    e2->addTerm(*(y_variables[ij][(*it)->getIndex()])*(-1));
    //                }
    //            }

    //            *lp_ += new LinearConstraint(e1, LinearConstraint::GREATER_EQ, 0.0);
    //            *lp_ += new LinearConstraint(e2, LinearConstraint::GREATER_EQ, 0.0);
    //            if(isDirected) {
    //                *lp_ += new LinearConstraint(e3, LinearConstraint::GREATER_EQ, 0.0);
    //                *lp_ += new LinearConstraint(e4, LinearConstraint::GREATER_EQ, 0.0);
    //            }
    //        }
    //        delete e1init;
    //        if(isDirected)
    //            delete e3init;
    //    }

    // (F1a) and (F2a)
    LinearExpression *e;
    if(induced_) {
        for(kl=0; kl < nET; ++kl) {
            k = pb_->getTarget()->getEdge(kl)->getOrigin()->getIndex();
            l = pb_->getTarget()->getEdge(kl)->getTarget()->getIndex();
            e = new LinearExpression();
            for(auto v : x_variables.getCol(k))
                e->addTerm(*v);
            for(auto v : x_variables.getCol(l))
                e->addTerm(*v);
            for(auto v : y_variables.getCol(kl))
                e->addTerm((*v)*-1);
            *lp_+= new LinearConstraint(e, LinearConstraint::LESS_EQ, 1.0);
        }
    }
}

void ErrorTolerantSubgraphIsomorphism::initObjective() {
    SubgraphIsomorphism::initObjective();

    // Constant part of the objective
    double c = 0.0;
    for(i=0; i < nVP; ++i)
        c += pb_->getPattern()->getVertex(i)->getCost();
    for(ij=0; ij < nEP; ++ij)
        c += pb_->getPattern()->getEdge(ij)->getCost();

    lp_->getObjective()->addConst(c);
}
