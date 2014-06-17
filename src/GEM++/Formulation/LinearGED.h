#ifndef __LINEARGED_H__
#define __LINEARGED_H__

#include "GED.h"

class DLL_EXPORT LinearGraphEditDistance : public GraphEditDistance {
    public:
        LinearGraphEditDistance(Problem *pb, bool low, double up);
        virtual ~LinearGraphEditDistance();

        QPair<int,int> updateLowerBound(Solution *sol);

    private:
        Matrix<Variable*> y_variables;
        Matrix<double> y_costs;

        virtual void initVariables();
        virtual void initCosts();
        virtual void restrictProblem(double up);
        virtual void initConstraints();
        virtual void initObjective();
};

#endif /*__LINEARGED_H__*/
