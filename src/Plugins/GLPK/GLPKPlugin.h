/*  GEM++GLPK : a solver plugin for GEM++ based on GLPK
    Copyright (C) 2013-2015 LITIS laboratory

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

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
