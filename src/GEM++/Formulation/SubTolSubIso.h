#ifndef GEMPP_SUBTOLSUBISO_H
#define GEMPP_SUBTOLSUBISO_H

#include "SubIso.h"

/**
 * @brief The SubstitutionTolerantSubgraphIsomorphism class is an implementation of the formulation
 * that solves the subgraph isomorphism problem, which is tolerant to vertex and edge substitutions.
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 * @see SubgraphIsomorphism
 */
class DLL_EXPORT SubstitutionTolerantSubgraphIsomorphism : virtual public SubgraphIsomorphism{
    public:
        /**
         * @brief Constructs a new SubstitutionTolerantSubgraphIsomorphism object.
         */
        SubstitutionTolerantSubgraphIsomorphism() {}

        /**
         * @brief Constructs a new SubstitutionTolerantSubgraphIsomorphism object with parameters.
         * @param pb the problem to solve
         * @param up the upper bound approximation parameter
         * @param induced controls the use of induced matching
         */
        SubstitutionTolerantSubgraphIsomorphism(Problem *pb, double up, bool induced);

        /**
         * @brief Destructs a SubstitutionTolerantSubgraphIsomorphism object.
         */
        virtual ~SubstitutionTolerantSubgraphIsomorphism();

    protected:
        virtual void restrictProblem(double up);
        virtual void initConstraints();
};

#endif /* GEMPP_SUBTOLSUBISO_H */
