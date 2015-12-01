#ifndef GEMPP_MCSM_H
#define GEMPP_MCSM_H

#include "STSM.h"
/**
 * @brief The MinimumCostSubgraphMatching class is an implementation of the formulation
 * that solves the subgraph matching problem, which is tolerant to vertex and edge substitutions
 * and tolerant to topology errors.
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 * @see SubgraphMatching, SubstitutionTolerantSubgraphMatching
 */
class DLL_EXPORT MinimumCostSubgraphMatching : virtual public SubstitutionTolerantSubgraphMatching{
    public:
        /**
         * @brief Constructs a new MinimumCostSubgraphMatching object with parameters.
         * @param pb the problem to solve
         * @param up the upper bound approximation parameter
         * @param induced controls the use of induced matching
         */
        MinimumCostSubgraphMatching(Problem *pb, double up, bool induced);

        /**
         * @brief Destructs a MinimumCostSubgraphMatching object.
         */
        virtual ~MinimumCostSubgraphMatching() {}

    protected:
        virtual void initCosts();
        virtual void initConstraints();
        virtual void initObjective();
};

#endif /* GEMPP_MCSM_H*/
