#ifndef GEMPP_LINEARGED_H
#define GEMPP_LINEARGED_H

#include "GED.h"

/**
 * @brief The LinearGraphEditDistance class is an implementation of the optimal linear programming
 * formulation that solves the graph edist distance problem.
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 * @see GraphEditDistance
 */
class DLL_EXPORT LinearGraphEditDistance : public GraphEditDistance {
    public:
        /**
         * @brief Constructs a new LinearGraphEditDistance object with parameters.
         * @param pb the problem to solve
         * @param up the upper bound approximation parameter
         */
        LinearGraphEditDistance(Problem *pb, double up);

        /**
         * @brief Destructs a LinearGraphEditDistance object.
         */
        virtual ~LinearGraphEditDistance();

    private:
        /**
         * @brief The matrix of the edge substitution variables.
         */
        Matrix<Variable*> y_variables;

        /**
         * @brief The matrix of the edge substitution costs.
         */
        Matrix<double> y_costs;

        virtual void initVariables();
        virtual void initCosts();
        virtual void restrictProblem(double up);
        virtual void initConstraints();
        virtual void initObjective();
};

#endif /* GEMPP_LINEARGED_H */
