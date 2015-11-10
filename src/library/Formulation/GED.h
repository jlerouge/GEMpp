#ifndef GEMPP_GED_H
#define GEMPP_GED_H

#include "Formulation.h"
#include "Solution.h"

/**
 * @brief The GraphEditDistance class is an implementation of the formulation
 * that solves the graph edist distance problem. There are two available methods of solving :
 *  - GED (our method)
 *  - bipartite graph matching, which is a suboptimal algorithm to solve GED
 *
 * These methods are implemented in subclasses.
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 * @see BipartiteGraphMatching, LinearGraphEditDistance
 * @warning This is an abstract class, it must be derived to be used.
 */
class DLL_EXPORT GraphEditDistance : virtual public Formulation {
    public:
        /**
         * @brief Indicates the method used for the resolution of the graph edit distance problem.
         */
        enum Method{
            LINEAR = 0, /**< linear graph edit distance (our method) */
            BIPARTITE, /**< bipartite graph matching (suboptimal) */
            COUNT /**< used to iterate on GraphEditDistance::Method enum */
        };

        /**
         * @brief The names of methods.
         */
        static const char* methodName[COUNT];

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
         * @brief Destructs a GraphEditDistance object.
         */
        virtual ~GraphEditDistance();

        virtual void cut(Solution *sol, CutMethod cm);

    protected:
        /**
         * @brief The matrix of the vertex substitution variables.
         */
        Matrix<Variable*> x_variables;

        /**
         * @brief The matrix of the vertex substitution costs.
         */
        Matrix<double> x_costs;

        virtual void initVariables();
        virtual void initCosts();
        virtual void restrictProblem(double up);
};

#endif /* GEMPP_GED_H */
