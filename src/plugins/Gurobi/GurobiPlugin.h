#ifndef __GUROBIPLUGIN_H__
#define __GUROBIPLUGIN_H__

#include <QObject>
#include <QtPlugin>
#include "gurobi_c++.h"
#include "Solver/SolverFactory.h"

class Gurobi : public Solver {
    public:
        Gurobi();
        ~Gurobi();

        void init(Configuration *cfg);
        double solve(Solution *sol = 0);
        void update(bool newBounds = 0);

    private:
        GRBEnv *env_;
        GRBModel *model_;

        void addVar(Variable *v);
        void addLinearConstraint(LinearConstraint *c);
        void addQuadConstraint(QuadConstraint *c);
        void setObjective();
        void prepare();
};

class GurobiFactory : public QObject, public SolverFactory {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID "eu.litislab.GEM++.GurobiFactory" FILE "GurobiFactory.json")
        Q_INTERFACES(SolverFactory)
    public:
        virtual Solver* create() {
            return new Gurobi();
        }
};

#endif /* __GUROBIPLUGIN_H__ */
