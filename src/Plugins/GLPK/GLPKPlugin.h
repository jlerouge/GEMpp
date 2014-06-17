#ifndef __GLPKPLUGIN_H__
#define __GLPKPLUGIN_H__

#include <QObject>
#include <QtPlugin>
#include "glpk.h"
#include "Solver/SolverFactory.h"

class GLPK : public Solver{
    public:
        GLPK();
        ~GLPK();

        void init(Configuration *cfg);
        double solve(Solution *sol = 0);
        void update(bool newBounds = false);

    private:
        glp_prob *model_;
        glp_iocp config_;
        QHash<QString, int> varOrder_;
        QHash<QString, int> constOrder_;
        int *ia_, *ja_;
        double *ar_;
        int nz_;

        void addVar(Variable *v);
        void addLinearConstraint(LinearConstraint *c);
        void addQuadConstraint(QuadConstraint *c);
        void setObjective();
        void prepare();
        void initMatrix();
};

class GLPKFactory : public QObject, public SolverFactory {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID "eu.litislab.GEM++.GLPKFactory" FILE "GLPKFactory.json")
        Q_INTERFACES(SolverFactory)
    public:
        virtual Solver* create() {
            return new GLPK();
        }
};

#endif /* __GLPKPLUGIN_H__ */
