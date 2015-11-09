#ifndef GEMPP_FORMULATION_H
#define GEMPP_FORMULATION_H

#include "../Model/Problem.h"
#include "../IntegerProgramming/LinearProgram.h"
#include "../IntegerProgramming/QuadProgram.h"

class Solution;

/**
 * @brief The Formulation class represents the mathematical programming formulation used
 * to solve a graph matching problem.
 *
 * The formulation is dedicated to a particular problem (subgraph isomorphism, graph edit
 * distance...), an thus generates a linear/quadratic program that can be used to solve it.
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 * @warning This is an abstract class, it must be derived to be used.
 */
class DLL_EXPORT Formulation {
    public:
        /**
         * @brief The method used to cut a previously found solution.
         */
        enum CutMethod {
            SOLUTION = 0, /**< makes only this particular solution no more feasible */
            MATCHINGS, /**< makes every vertex matching and every edge matching no more feasible */
            ELEMENTS, /**< makes every vertex matched and every edge matched no more matchable */
            COUNT /**< used to iterate on Formulation::CutMethod enum */
        };

        /**
         * @brief The names of the cut methods.
         */
        static const char *cutMethodName[COUNT];

        /**
         * @brief Retrieves the cut method from its name.
         * @param name the name
         * @return the cut method
         */
        static CutMethod fromName(QString name);

        /**
         * @brief Returns the name of the cut method.
         * @param method the cut method
         * @return the name
         */
        static QString toName(CutMethod method);

        /**
         * @brief Constructs a new Formulation object.
         */
        Formulation();

        /**
         * @brief Constructs a new Formulation object with parameters.
         * @param pb the problem to solve
         * @param induced controls the use of induced matching
         */
        Formulation(Problem *pb, bool induced = false);

        /**
         * @brief Destructs a Formulation object.
         */
        virtual ~Formulation() {}

        /**
         * @brief Initializes the formulation, calling the abstract methods of the subclass.
         * @param up the upper bound approximation parameter
         */
        void init(double up = 1.0);

        /**
         * @brief Cuts a solution by adding constraints w.r.t the cut method.
         * @param sol the solution to cut
         * @param cm the cut method
         */
        virtual void cut(Solution *sol, CutMethod cm) = 0;

        /**
         * @brief Sets the problem to solve.
         * @param pb the problem
         */
        void setProblem(Problem *pb);

        /**
         * @brief Returns the problem to solve.
         * @return the problem
         */
        Problem *getProblem();

        /**
         * @brief Returns the linear program made to solve the problem (if applicable).
         * @return the linear program
         */
        LinearProgram *getLinearProgram();

        /**
         * @brief Returns the quadratic program made to solve the problem (if applicable).
         * @return the quadratic program
         */
        QuadProgram *getQuadProgram();

        /**
         * @brief Returns the program (linear or quadratic) made to solve the problem.
         * @return the program
         */
        Program *getProgram();

    protected:
        /**
         * @brief The problem to solve.
         */
        Problem *pb_;

        /**
         * @brief The program (linear or quadratic) made to solve the problem.
         */
        Program *p_;

        /**
         * @brief The linear program made to solve the problem.
         */
        LinearProgram *lp_;

        /**
         * @brief The quadratic program made to solve the problem.
         */
        QuadProgram *qp_;

        /**
         * @brief Controls the use of induced matching.
         */
        bool induced_;

        // Convenient variables that
        // are used in init methods
        int nVP, nVT, nEP, nET;
        int i, j, k, l, ij, kl;
        bool isDirected;

        /**
         * @brief Initializes the substitution variables.
         */
        virtual void initVariables() = 0;

        /**
         * @brief Initializes the substitution and creation costs.
         */
        virtual void initCosts() = 0;

        /**
         * @brief Prevents some variables to be used based on the substitution costs
         * and the upper bound apprixomation parameter.
         *
         * @param up the upper bound apprixomation parameter
         */
        virtual void restrictProblem(double up) = 0;

        /**
         * @brief Initializes the constraints.
         */
        virtual void initConstraints() = 0;

        /**
         * @brief Initializes the objective function.
         */
        virtual void initObjective() = 0;
};

#endif /* GEMPP_FORMULATION_H */
