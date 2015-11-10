#ifndef GEMPP_PLUGINLOADER_H
#define GEMPP_PLUGINLOADER_H

#include <QPluginLoader>
#include "SolverFactory.h"

class DLL_EXPORT PluginLoader : public QPluginLoader {
    public:
        PluginLoader();
        ~PluginLoader();

        Solver *loadSolver(Solver::Solvers solver);
};

#endif /* GEMPP_PLUGINLOADER_H */
