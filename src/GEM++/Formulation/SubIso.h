#ifndef __SUBISO_H__
#define __SUBISO_H__

#include "Formulation.h"
#include "Solution.h"
#include "../Model/Problem.h"
#include "../IntegerProgramming/LinearProgram.h"

class DLL_EXPORT SubgraphIsomorphism : virtual public Formulation{
    public:
        /**
         * @brief The SubgraphIsomorphism::Method enum indicates the method
         * used for the resolution of the subgraph isomorphism problem.
         */
        enum Method{
            EXACT = 0, /**< exact subgraph isomorphism */
            LABEL, /**< substitution-tolerant subgraph isomorphism */
            TOPOLOGY, /**< error-tolerant subgraph isomorphism */
            COUNT /**< used to iterate on SubgraphIsomorphism::Method enum */
        };
        static const char *methodName[COUNT];
        static Method fromName(QString name);
        static QString toName(Method method);

        virtual ~SubgraphIsomorphism();

        virtual void cut(Solution *sol, CutMethod cm);

    protected:
        Matrix<Variable*> x_variables;
        Matrix<Variable*> y_variables;
        Matrix<double> x_costs;
        Matrix<double> y_costs;

        virtual void initVariables();
        virtual void initCosts();
        virtual void initObjective();
};

#endif /*__SUBISO_H__*/
