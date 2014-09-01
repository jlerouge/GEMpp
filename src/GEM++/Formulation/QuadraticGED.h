#ifndef __QUADRATICGED_H__
#define __QUADRATICGED_H__

#include "GED.h"

class DLL_EXPORT QuadGraphEditDistance : virtual public GraphEditDistance {
    public:
        QuadGraphEditDistance(Problem *pb, double up);
        virtual ~QuadGraphEditDistance();

    private:
        Matrix<Quad> y1_variables;
        Matrix<Quad> y2_variables;
        Matrix<double> y_costs;

        virtual void initVariables();
        virtual void initCosts();
        virtual void initConstraints();
        virtual void initObjective();
};

#endif /*__QUADRATICGED_H__*/
