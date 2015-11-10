#ifndef GEMPP_EXACTSUBISO_H
#define GEMPP_EXACTSUBISO_H

#include "SubTolSubIso.h"

/**
 * @brief The ExactSubgraphIsomorphism class is an implementation of the formulation
 * that solves the exact subgraph isomorphism problem. This implementation forbids
 * vertex and edge substitutions where the substitution cost is higher than a given
 * precision (to avoid numerical problems).
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 * @see SubgraphIsomorphism, SubstitutionTolerantSubgraphIsomorphism
 */

class DLL_EXPORT ExactSubgraphIsomorphism : virtual public SubstitutionTolerantSubgraphIsomorphism{
    public:
        /**
         * @brief Constructs a new ExactSubgraphIsomorphism object with parameters.
         * @param pb the problem to solve
         * @param induced controls the use of induced matching
         */
        ExactSubgraphIsomorphism(Problem *pb, bool induced);

        /**
         * @brief Destructs a ExactSubgraphIsomorphism object.
         */
        virtual ~ExactSubgraphIsomorphism() {}

    protected:
        virtual void restrictProblem(double up);
};

#endif /* GEMPP_EXACTSUBISO_H */
