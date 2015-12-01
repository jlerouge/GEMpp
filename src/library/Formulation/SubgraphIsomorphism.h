#ifndef GEMPP_SUBGRAPHISOMORPHISM_H
#define GEMPP_SUBGRAPHISOMORPHISM_H

#include "STSM.h"

/**
 * @brief The SubgraphIsomorphism class is an implementation of the formulation
 * that solves the (exact) subgraph isomorphism problem. This implementation forbids
 * vertex and edge substitutions where the substitution cost is higher than a given
 * precision (to avoid numerical problems).
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 * @see SubgraphMatching, SubstitutionTolerantSubgraphMatching
 */

class DLL_EXPORT SubgraphIsomorphism : virtual public SubstitutionTolerantSubgraphMatching{
    public:
        /**
         * @brief Constructs a new SubgraphIsomorphism object with parameters.
         * @param pb the problem to solve
         * @param induced controls the use of induced matching
         */
        SubgraphIsomorphism(Problem *pb, bool induced);

        /**
         * @brief Destructs a SubgraphIsomorphism object.
         */
        virtual ~SubgraphIsomorphism() {}

    protected:
        virtual void restrictProblem(double up);
};

#endif /* GEMPP_SUBGRAPHISOMORPHISM_H */
