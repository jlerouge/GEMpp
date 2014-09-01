#ifndef __FORMULATION_H__
#define __FORMULATION_H__

#include "../Model/Problem.h"
#include "../IntegerProgramming/LinearProgram.h"
#include "../IntegerProgramming/QuadProgram.h"

class Solution;

class DLL_EXPORT Formulation {
    public:
        enum CutMethod {
            SOLUTION = 0,
            MATCHINGS,
            ELEMENTS,
            COUNT
        };
        static const char *cutMethodName[COUNT];
        static CutMethod fromName(QString name);
        static QString toName(CutMethod method);

        Formulation();
        Formulation(Problem *pb, bool low = false, bool induced = false);
        virtual ~Formulation() {}

        void init(double up = 1.0);
        virtual void cut(Solution *sol, CutMethod cm) = 0;

        void setProblem(Problem *pb);
        Problem *getProblem();
        LinearProgram *getLinearProgram();
        QuadProgram *getQuadProgram();
        Program *getProgram();

    protected:
        Problem *pb_;
        Program *p_;
        LinearProgram *lp_;
        QuadProgram *qp_;
        bool low_;
        bool induced_;

        // Convenient variables that
        // are used in init methods
        int nVP, nVT, nEP, nET;
        int i, j, k, l, ij, kl;
        bool isDirected;

        virtual void initVariables() = 0;
        virtual void initCosts() = 0;
        virtual void restrictProblem(double up) = 0;
        virtual void initConstraints() = 0;
        virtual void initObjective() = 0;
};

#endif /*__FORMULATION_H__*/
