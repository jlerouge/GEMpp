#ifndef __GED_H__
#define __GED_H__

#include "Formulation.h"
#include "Solution.h"

class DLL_EXPORT GraphEditDistance : virtual public Formulation {
    public:
        /**
         * @brief The GraphEditDistance::Method enum indicates the method
         * used for the resolution of the graph edit distance problem.
         */
        enum Method{
            LINEAR = 0, /**< linear graph edit distance, with x and y variables */
            BIPARTITE, /**< bipartite graph matching (inexact method) */
            COUNT /**< used to iterate on GraphEditDistance::Method enum */
        };
        static const char* methodName[COUNT];
        static Method fromName(QString name);
        static QString toName(Method method);

        virtual ~GraphEditDistance();

        virtual void cut(Solution *sol, CutMethod cm);

    protected:
        Matrix<Variable*> x_variables;
        Matrix<double> x_costs;

        virtual void initVariables();
        virtual void initCosts();
        virtual void restrictProblem(double up);
};

#endif /*__GED_H__*/
