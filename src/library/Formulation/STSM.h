#ifndef GEMPP_STSM_H
#define GEMPP_STSM_H

#include "SubgraphMatching.h"

/**
 * @brief The SubstitutionTolerantSubgraphMatching class is an implementation of the formulation
 * that solves the subgraph matching problem, which is tolerant to vertex and edge substitutions.
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 * @see SubgraphMatching
 */
class DLL_EXPORT SubstitutionTolerantSubgraphMatching : virtual public SubgraphMatching{
    public:
        /**
         * @brief Constructs a new SubstitutionTolerantSubgraphMatching object.
         */
        SubstitutionTolerantSubgraphMatching() {}

        /**
         * @brief Constructs a new SubstitutionTolerantSubgraphMatching object with parameters.
         * @param pb the problem to solve
         * @param up the upper bound approximation parameter
         * @param induced controls the use of induced matching
         */
        SubstitutionTolerantSubgraphMatching(Problem *pb, double up, bool induced);

        /**
         * @brief Destructs a SubstitutionTolerantSubgraphMatching object.
         */
        virtual ~SubstitutionTolerantSubgraphMatching();

    protected:
        virtual void restrictProblem(double up);
        virtual void initConstraints();
};

#endif /* GEMPP_STSM_H */
