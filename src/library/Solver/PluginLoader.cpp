#include "PluginLoader.h"

PluginLoader::PluginLoader() : QPluginLoader() {}

PluginLoader::~PluginLoader() {}

Solver* PluginLoader::loadSolver(Solver::Solvers solver) {
    QString name = Solver::solverName[solver];
    #if defined(WIN32) || defined(WIN64)
    #if defined(GEMDEBUG)
        setFileName(QString("GEM++%1d.dll").arg(name));
    #elif defined(GEMRELEASE)
        setFileName(QString("GEM++%1.dll").arg(name));
    #endif
    #elif defined(LINUX)
        setFileName(QString("../lib/libGEM++%1.so").arg(name));
    #endif

    QObject *plugin = instance();
    if(!plugin)
        Exception(QString("%1 plugin cannot be loaded : %2").arg(name,errorString()));
    SolverFactory *solverFactory = qobject_cast<SolverFactory *>(plugin);
    if(!solverFactory)
        Exception(QString("%1 solver cannot be used.").arg(name));
    return solverFactory->create();
}
