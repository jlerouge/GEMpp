#include "ExactSubIso.h"

ExactSubgraphIsomorphism::ExactSubgraphIsomorphism(Problem *pb, bool induced) : Formulation(pb, induced) {
    lp_ = new LinearProgram(Program::MINIMIZE);
    init();
}

void ExactSubgraphIsomorphism::restrictProblem(double up) {
    if(up < 1)
        GEM_exception("Exact subgraph isomorphism does not handle upper-bound approximation nor column generation.");

    for(auto row : x_variables)
        for(auto v : row)
            v->activate();

    for(auto row : y_variables)
        for(auto v : row)
            v->activate();

    for(i=0; i < nVP; ++i)
        for(k=0; k < nVT; ++k)
            if(x_costs.getElement(i, k) > precision)
                x_variables.getElement(i, k)->deactivate();

    for(ij=0; ij < nEP; ++ij) {
        i = pb_->getPattern()->getEdge(ij)->getOrigin()->getIndex();
        j = pb_->getPattern()->getEdge(ij)->getTarget()->getIndex();
        for(kl=0; kl < nET; ++kl) {
            if(y_costs.getElement(ij, kl) > precision)
                y_variables.getElement(ij, kl)->deactivate();
            else {
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
