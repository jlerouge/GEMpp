#ifndef GEMPP_BIPARTITEGED_H
#define GEMPP_BIPARTITEGED_H

#include "GED.h"

/**
 * @brief The BipartiteGraphMatching class is an implementation of the suboptimal
 * bipartite graph matching algorithm that solves the graph edist distance problem.
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 * @see GraphEditDistance
 */
class DLL_EXPORT BipartiteGraphMatching: virtual public GraphEditDistance {
    public:
        /**
         * @brief Constructs a new BipartiteGraphMatching object with parameters.
         * @param pb the problem to solve
         * @param up the upper bound approximation parameter
         */
        BipartiteGraphMatching(Problem *pb, double up = 1);

        /**
         * @brief Destructs a BipartiteGraphMatching object.
         */
        virtual ~BipartiteGraphMatching();

    protected:
        virtual void initConstraints();
        virtual void initObjective();
};

#endif /* GEMPP_BIPARTITEGED_H */
