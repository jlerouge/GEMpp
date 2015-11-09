#ifndef GEMPP_SUBISO_H
#define GEMPP_SUBISO_H

#include "Formulation.h"
#include "Solution.h"
#include "../Model/Problem.h"
#include "../IntegerProgramming/LinearProgram.h"

/**
 * @brief The SubgraphIsomorphism class is an implementation of the formulation
 * that solves the subgraph isomorphism problem, with some tolerance. There are
 * three level of tolerance :
 *  - exact isomorphism
 *  - (vertex and edge) substitution tolerant
 *  - substitution tolerant and topology error tolerant
 *
 * The levels of tolerance are implemented in subclasses.
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 * @see ExactSubgraphIsomorphism, SubstitutionTolerantSubgraphIsomorphism, ErrorTolerantSubgraphIsomorphism
 * @warning This is an abstract class, it must be derived to be used.
 */
class DLL_EXPORT SubgraphIsomorphism : virtual public Formulation{
    public:
        /**
         * @brief Indicates the level of tolerance used when solving
         * the subgraph isomorphism problem.
         */
        enum Method{
            EXACT = 0, /**< exact subgraph isomorphism */
            LABEL, /**< substitution-tolerant subgraph isomorphism */
            TOPOLOGY, /**< error-tolerant subgraph isomorphism */
            COUNT /**< used to iterate on SubgraphIsomorphism::Method enum */
        };

        /**
         * @brief The names of methods.
         */
        static const char *methodName[COUNT];

        /**
         * @brief Retrieves the method from its name.
         * @param name the name
         * @return the method
         */
        static Method fromName(QString name);

        /**
         * @brief Returns the name of the method.
         * @param method the method
         * @return the name
         */
        static QString toName(Method method);

        /**
         * @brief Destructs a SubgraphIsomorphism object.
         */
        virtual ~SubgraphIsomorphism();

        virtual void cut(Solution *sol, CutMethod cm);

    protected:
        /**
         * @brief The matrix of the vertex substitution variables.
         */
        Matrix<Variable*> x_variables;

        /**
         * @brief The matrix of the edge substitution variables.
         */
        Matrix<Variable*> y_variables;

        /**
         * @brief The matrix of the vertex substitution costs.
         */
        Matrix<double> x_costs;

        /**
         * @brief The matrix of the edge substitution costs.
         */
        Matrix<double> y_costs;

        virtual void initVariables();
        virtual void initCosts();
        virtual void initObjective();
};

#endif /* GEMPP_SUBISO_H */
