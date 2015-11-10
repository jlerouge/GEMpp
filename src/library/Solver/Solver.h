#ifndef GEMPP_SOLVER_H
#define GEMPP_SOLVER_H

#include "Configuration.h"
#include "Formulation/Solution.h"
#include "IntegerProgramming/LinearProgram.h"
#include "IntegerProgramming/QuadProgram.h"

class DLL_EXPORT Solver {
    public:
        enum Solvers{
            CPLEX = 0,
            GLPK,
            GUROBI,
            COUNT
        };
        static const char* solverName[COUNT];
        virtual ~Solver() {}
        static Solvers fromName(QString name);
        static QString toName(Solvers solver);

        virtual void setLinearProgram(LinearProgram *lp);
        virtual void setQuadProgram(QuadProgram *lp);
        virtual void init(LinearProgram *lp, Configuration *cfg = 0);
        virtual void init(QuadProgram *qp, Configuration *cfg = 0);

        virtual void init(Configuration *cfg = 0) = 0;
        virtual double solve(Solution *sol = 0) = 0;
        virtual void update(bool newBounds = false) = 0;

    protected:
        LinearProgram *lp_;
        QuadProgram *qp_;
        Configuration *cfg_;

    private:
        virtual void addVar(Variable *v) = 0;
        virtual void addLinearConstraint(LinearConstraint *c) = 0;
        virtual void addQuadConstraint(QuadConstraint *c) = 0;
        virtual void setObjective() = 0;
        virtual void prepare() = 0;
};

#endif /* GEMPP_SOLVER_H */
