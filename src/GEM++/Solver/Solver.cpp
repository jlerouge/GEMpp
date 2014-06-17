#include "Solver.h"

DLL_EXPORT const char* Solver::solverName[Solver::COUNT] = {
    "Cplex",
    "GLPK",
    "Gurobi"
};

Solver::Solvers Solver::fromName(QString name) {
    for(Solvers m = (Solvers)0; m < COUNT; m = (Solvers)((int)m + 1))
        if(QString(solverName[m]).startsWith(name, Qt::CaseInsensitive))
            return m;
    GEM_exception(QString("Solver '%1' not recognized, please use c(plex), gl(pk) or gu(robi).").arg(name));
    return COUNT;
}

QString Solver::toName(Solvers solver) {
    return solverName[(int)solver];
}

void Solver::init(LinearProgram *lp, Configuration *cfg) {
    init(cfg);
    lp_ = lp;
    prepare();
    update(false);
    setObjective();
}

void Solver::init(QuadProgram *qp, Configuration *cfg) {
    init(cfg);
    qp_ = qp;
    prepare();
    update(false);
    setObjective();
}

void Solver::setLinearProgram(LinearProgram *lp) {
    lp_ = lp;
}

void Solver::setQuadProgram(QuadProgram *qp) {
    qp_ = qp;
}
