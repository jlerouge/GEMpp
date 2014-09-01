#ifndef __BIPARTITEEDGES_H__
#define __BIPARTITEEDGES_H__

#include "Formulation.h"
#include "Solution.h"
#include "../IntegerProgramming/LinearProgram.h"

class DLL_EXPORT BipartiteEdges: public Formulation {
    public:
        BipartiteEdges(Problem *pb, int i, int k);
        virtual ~BipartiteEdges();
        virtual void cut(Solution *sol, CutMethod cm);

    private:
        Vertex *vi_, *vk_;
        Matrix<Variable*> y_variables;

        virtual void initVariables();
        virtual void initCosts();
        virtual void restrictProblem(double up);
        virtual void initConstraints();
        virtual void initObjective();
};

#endif /*__BIPARTITEEDGES_H__*/
