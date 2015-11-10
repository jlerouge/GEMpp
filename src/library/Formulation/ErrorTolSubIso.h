#ifndef GEMPP_ERRORTOLSUBISO_H
#define GEMPP_ERRORTOLSUBISO_H

#include "SubTolSubIso.h"
/**
 * @brief The ErrorTolerantSubgraphIsomorphism class is an implementation of the formulation
 * that solves the subgraph isomorphism problem, which is tolerant to vertex and edge substitutions
 * and tolerant to topology errors.
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 * @see SubgraphIsomorphism, SubstitutionTolerantSubgraphIsomorphism
 */
class DLL_EXPORT ErrorTolerantSubgraphIsomorphism : virtual public SubstitutionTolerantSubgraphIsomorphism{
    public:
        /**
         * @brief Constructs a new ErrorTolerantSubgraphIsomorphism object with parameters.
         * @param pb the problem to solve
         * @param up the upper bound approximation parameter
         * @param induced controls the use of induced matching
         */
        ErrorTolerantSubgraphIsomorphism(Problem *pb, double up, bool induced);

        /**
         * @brief Destructs a ErrorTolerantSubgraphIsomorphism object.
         */
        virtual ~ErrorTolerantSubgraphIsomorphism() {}

    protected:
        virtual void initCosts();
        virtual void initConstraints();
        virtual void initObjective();
};

#endif /* GEMPP_ERRORTOLSUBISO_H*/
