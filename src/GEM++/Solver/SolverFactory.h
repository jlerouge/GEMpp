#ifndef __SOLVERFACTORY_H__
#define __SOLVERFACTORY_H__

#include "Solver.h"

class DLL_EXPORT SolverFactory {
    public:
        SolverFactory() {}
        ~SolverFactory() {}
        virtual Solver* create() = 0;
};

#define SolverFactory_iid "eu.litislab.GEM++.SolverFactory"
Q_DECLARE_INTERFACE(SolverFactory, SolverFactory_iid)

#endif /* __SOLVERFACTORY_H__ */
