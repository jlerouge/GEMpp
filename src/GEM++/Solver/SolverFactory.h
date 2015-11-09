#ifndef GEMPP_SOLVERFACTORY_H
#define GEMPP_SOLVERFACTORY_H

#include "Solver.h"

class DLL_EXPORT SolverFactory {
    public:
        SolverFactory() {}
        ~SolverFactory() {}
        virtual Solver* create() = 0;
};

#define GEMPP_SolverFactory_iid "eu.litislab.GEM++.SolverFactory"
Q_DECLARE_INTERFACE(SolverFactory, SolverFactory_iid)

#endif /* GEMPP_SOLVERFACTORY_H */
