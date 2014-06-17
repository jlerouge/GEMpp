#ifndef __CPLEXPLUGIN_H__
#define __CPLEXPLUGIN_H__

using namespace std;

#include <QObject>
#include <QtPlugin>
#include "ilcplex/ilocplex.h"
#include "Solver/SolverFactory.h"

class Cplex : public Solver {
    public:
        Cplex();
        ~Cplex();

        void init(Configuration *cfg);
        double solve(Solution *sol = 0);
        void update(bool newBounds = false);

    private:
        IloEnv *env_;
        IloModel *model_;
        IloCplex *cplex_;
        IloNumVarArray variables_;
        QHash<Variable*, int> varOrder_;
        QSet<QString> constraints_;

        void addVar(Variable *v);
        void addLinearConstraint(LinearConstraint *c);
        void addQuadConstraint(QuadConstraint *c);
        void setObjective();
        void prepare();
};


class CplexFactory : public QObject, public SolverFactory {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID "eu.litislab.GEM++.CplexFactory" FILE "CplexFactory.json")
        Q_INTERFACES(SolverFactory)
    public:
        virtual Solver* create() {
            return new Cplex();
        }
};

#endif /* __CPLEXPLUGIN_H__ */
