#include "SubTolSubIso.h"

SubstitutionTolerantSubgraphIsomorphism::SubstitutionTolerantSubgraphIsomorphism(Problem *pb, bool low, double up, bool induced) : Formulation(pb, low, induced) {
    lp_ = new LinearProgram(Program::MINIMIZE);
    init(up);
}

SubstitutionTolerantSubgraphIsomorphism::~SubstitutionTolerantSubgraphIsomorphism() {
    delete lp_;
}

QPair<int,int> SubstitutionTolerantSubgraphIsomorphism::updateLowerBound(Solution *sol) {
    Q_UNUSED(sol); // FIXME
    GEM_exception("SubTolSubIso does not implement row-generation yet.");
    return qMakePair(0, 0); // FIXME
}

void SubstitutionTolerantSubgraphIsomorphism::restrictProblem(double up) {
    if(up < 1) {
        for(auto row : x_variables)
            for(auto v : row)
                v->activate();

        for(auto row : y_variables)
            for(auto v : row)
                v->activate();

        QList<double> v;
        for(i=0; i < nVP; ++i) {
            v = x_costs.getRow(i);
            std::sort(v.begin(), v.end());
            for(k=0; k < nVT; ++k)
                if(x_costs.getElement(i, k) > v[floor(nVT * up)])
                    x_variables.getElement(i, k)->deactivate();
        }

        for(k=0; k < nVT; ++k) {
            v = x_costs.getCol(k);
            std::sort(v.begin(), v.end());
            for(i=0; i < nVP; ++i)
                if(x_costs.getElement(i, k) > v[floor(nVP * up)])
                    x_variables.getElement(i, k)->deactivate();
        }

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

void SubstitutionTolerantSubgraphIsomorphism::initConstraints() {
    Q_UNUSED(low_); // FIXME

    for(i=0; i < nVP; ++i, ++cuid_)
        *lp_ += new LinearConstraint(LinearExpression::sum(x_variables.getRow(i)), LinearConstraint::EQUAL, 1.0, QString::number(cuid_));

    for(k=0; k < nVT; ++k, ++cuid_)
        *lp_ += new LinearConstraint(LinearExpression::sum(x_variables.getCol(k)), LinearConstraint::LESS_EQ, 1.0, QString::number(cuid_));

    for(ij=0; ij < nEP; ++ij, ++cuid_)
        *lp_ += new LinearConstraint(LinearExpression::sum(y_variables.getRow(ij)), LinearConstraint::EQUAL, 1.0, QString::number(cuid_));

    // (F1)
    //    for(ij=0; ij < nEP; ++ij) {
    //        i = pb_->getPattern()->getEdge(ij)->getOrigin()->getIndex();
    //        j = pb_->getPattern()->getEdge(ij)->getTarget()->getIndex();
    //        for(kl=0; kl < nET; ++kl) {
    //            if(y_variables.getElement(ij, kl)->isActive()) {
    //                k = pb_->getTarget()->getEdge(kl)->getOrigin()->getIndex();
    //                l = pb_->getTarget()->getEdge(kl)->getTarget()->getIndex();
    //                if(isDirected) {
    //                    *lp_ += new LinearConstraint(*(x_variables.getElement(i, k)) - *(y_variables.getElement(ij, kl)),
    //                                    LinearConstraint::GREATER_EQ, 0.0, QString::number(cuid_)); ++cuid_;
    //                    *lp_ += new LinearConstraint(*(x_variables.getElement(j, l)) - *(y_variables.getElement(ij, kl)),
    //                                    LinearConstraint::GREATER_EQ, 0.0, QString::number(cuid_)); ++cuid_;
    //                    *lp_ += new LinearConstraint(*(x_variables.getElement(i, k)) + *(x_variables.getElement(j, l)) - *(y_variables.getElement(ij, kl)),
    //                                    LinearConstraint::LESS_EQ, 1.0, QString::number(cuid_)); ++cuid_;
    //                } else {
    //                    *lp_ += new LinearConstraint(*(x_variables.getElement(i, k)) + *(x_variables.getElement(i, l)) - *(y_variables.getElement(ij, kl)),
    //                                    LinearConstraint::GREATER_EQ, 0.0, QString::number(cuid_)); ++cuid_;
    //                    *lp_ += new LinearConstraint(*(x_variables.getElement(j, l)) + *(x_variables.getElement(j, k)) - *(y_variables.getElement(ij, kl)),
    //                                    LinearConstraint::GREATER_EQ, 0.0, QString::number(cuid_)); ++cuid_;
    //                    *lp_ += new LinearConstraint(*(x_variables.getElement(i, k)) + *(x_variables.getElement(j, l)) + *(x_variables.getElement(i, l)) +
    //                                    *(x_variables.getElement(j, k)) - *(y_variables.getElement(ij, kl)), LinearConstraint::LESS_EQ, 1.0, QString::number(cuid_)); ++cuid_;
    //                }
    //            } else {
    //                cuid_ += 3;
    //            }
    //        }
    //    }

    // (F2)
    LinearExpression *e1, *e2;
    for(ij=0; ij < nEP; ++ij) {
        i = pb_->getPattern()->getEdge(ij)->getOrigin()->getIndex();
        j = pb_->getPattern()->getEdge(ij)->getTarget()->getIndex();
        for(k=0; k < nVT; ++k) {
            e1 = new LinearExpression();
            e2 = new LinearExpression();
            QSet<Edge *> edges = pb_->getTarget()->getVertex(k)->getEdges(Vertex::EDGE_OUT);
            for(auto it = edges.begin(); it != edges.end(); ++it) {
                e1->addTerm(*(y_variables.getElement(ij,(*it)->getIndex())));
                if(!isDirected)
                    e2->addTerm(*(y_variables.getElement(ij,(*it)->getIndex())));
            }
            edges = pb_->getTarget()->getVertex(k)->getEdges(Vertex::EDGE_IN);
            for(auto it = edges.begin(); it != edges.end(); ++it) {
                e2->addTerm(*(y_variables.getElement(ij,(*it)->getIndex())));
                if(!isDirected)
                    e1->addTerm(*(y_variables.getElement(ij,(*it)->getIndex())));
            }
            e1->addTerm(*(x_variables.getElement(i, k))*(-1));
            e2->addTerm(*(x_variables.getElement(j, k))*(-1));
            if(!isDirected) {
                e1->addTerm(*(x_variables.getElement(j, k))*(-1));
                e2->addTerm(*(x_variables.getElement(i, k))*(-1));
            }
            *lp_ += new LinearConstraint(e1, LinearConstraint::EQUAL, 0.0, QString::number(cuid_)); ++cuid_;
            *lp_ += new LinearConstraint(e2, LinearConstraint::EQUAL, 0.0, QString::number(cuid_)); ++cuid_;
        }
    }

    // (F1) and (F2)
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
            *lp_+= new LinearConstraint(e, LinearConstraint::LESS_EQ, 1.0, QString::number(cuid_)); ++cuid_;
        }
    }
}
