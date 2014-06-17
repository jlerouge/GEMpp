#ifndef __PLUGINLOADER_H__
#define __PLUGINLOADER_H__

#include <QPluginLoader>
#include "SolverFactory.h"

class DLL_EXPORT PluginLoader : public QPluginLoader {
    public:
        PluginLoader();
        ~PluginLoader();

        Solver *loadSolver(Solver::Solvers solver);
};

#endif /* __PLUGINLOADER_H__ */
