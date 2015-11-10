#ifndef GEMPP_BIPARTITEEDGES_H
#define GEMPP_BIPARTITEEDGES_H

#include "Formulation.h"
#include "Solution.h"
#include "../IntegerProgramming/LinearProgram.h"

/**
 * @brief The BipartiteEdges class is an implementation of the edge assignment
 * subproblem, for the bipartite graph matching algorithm. The resulting distance
 * is used to compute the vertex substitution costs in the main problem.
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 * @see BipartiteGraphMatching
 */
class DLL_EXPORT BipartiteEdges: public Formulation {
    public:
        /**
         * @brief Constructs a new BipartiteEdges object with parameters.
         * @param pb the problem to solve
         * @param i the index of the vertex in the query graph
         * @param k the index of the vertex in the target graph
         */
        BipartiteEdges(Problem *pb, int i, int k);

        /**
         * @brief Destructs a BipartiteGraphMatching object.
         */
        virtual ~BipartiteEdges();

        virtual void cut(Solution *sol, CutMethod cm);

    private:
        Vertex *vi_, *vk_;

        /**
         * @brief The matrix of the edge substitution variables.
         */
        Matrix<Variable*> y_variables;

        virtual void initVariables();
        virtual void initCosts();
        virtual void restrictProblem(double up);
        virtual void initConstraints();
        virtual void initObjective();
};

#endif /* GEMPP_BIPARTITEEDGES_H */
