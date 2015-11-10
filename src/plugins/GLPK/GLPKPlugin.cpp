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

#include "GLPKPlugin.h"

GLPK::GLPK() : Solver() {
    ia_ = 0;
    ja_ = 0;
    ar_ = 0;
    model_ = (glp_prob *)0;
}

GLPK::~GLPK() {
    glp_delete_prob(model_);
    glp_free_env();

    // Free the matrix
    if(ia_)
        free(ia_);
    if(ja_)
        free(ja_);
    if(ar_)
        free(ar_);
}

void GLPK::init(Configuration *cfg) {
    cfg_ = cfg;
    lp_ = (LinearProgram *)0;
    qp_ = (QuadProgram *)0;
    nz_ = 0;

    // Clean model
    if(model_)
        glp_delete_prob(model_);
    model_ = (glp_prob *)0;

    if(!varOrder_.empty())
        varOrder_.clear();
    if(!constOrder_.empty())
        constOrder_.clear();
}

void GLPK::prepare() {
    // Check if this is really linear programing
    if(qp_)
        Exception("GLPK cannot solve quadratic programs, please use Gurobi or Cplex instead or switch to linear formulation.");

    glp_init_iocp(&config_);
    config_.msg_lev = cfg_->verbose? GLP_MSG_ALL:GLP_MSG_OFF;
    if(cfg_->timeLimit == INFINITY)
        config_.tm_lim = INT_MAX;
    else
        config_.tm_lim = (int) cfg_->timeLimit*1000;
    config_.mip_gap = pow(10, -GEMPP_PRECISION);
    config_.presolve = GLP_ON;

    // Model creation
    model_ = glp_create_prob();
    glp_set_prob_name(model_, "glpk");
}

void GLPK::update(bool newBounds) {
    for(auto v : lp_->getVariables()) {
        if(!varOrder_.contains(v->getID()))
            addVar(v);
        if(newBounds)
            glp_set_col_bnds(model_, varOrder_[v->getID()], GLP_DB, v->getLowerBound(), v->getUpperBound());
    }
    for(auto c : lp_->getConstraints())
        if(!constOrder_.contains(c->getID()))
            addLinearConstraint(c);

    initMatrix();
}

void GLPK::initMatrix() {
    // Free the matrix
    if(ia_) {
        free(ia_);
        ia_ = 0;
    }
    if(ja_) {
        free(ja_);
        ja_ = 0;
    }
    if(ar_) {
        free(ar_);
        ar_ = 0;
    }

    ia_ = (int *) calloc(1+nz_, sizeof(int));
    ja_ = (int *) calloc(1+nz_, sizeof(int));
    ar_ = (double *) calloc(1+nz_, sizeof(double));

    int cpt = 0;
    LinearExpression *le;
    for(auto c : lp_->getConstraints()) {
        le = c->getLinearExpression();
        for(auto it = le->getTerms().begin(); it != le->getTerms().end(); ++it) {
            ++cpt;
            ia_[cpt] = constOrder_[c->getID()];
            ja_[cpt] = varOrder_[it.key()->getID()];
            ar_[cpt] = it.value();
        }
    }
    glp_load_matrix(model_, nz_, ia_, ja_, ar_);
}

double GLPK::solve(Solution *sol) {
    if(!model_)
        Exception("GLPK solver must be initialized before solving.");
    double obj = 0;
    switch(lp_->getSense()) {
        case Program::MINIMIZE:
            obj = INFINITY;
            break;
        case Program::MAXIMIZE:
            obj = -INFINITY;
            break;
    }
    Solution::Status status = Solution::NOT_SOLVED;
    if(!glp_intopt(model_, &config_)) {
        switch(glp_mip_status(model_)) {
            case GLP_OPT:
                status = Solution::OPTIMAL;
                break;
            case GLP_FEAS:
                status = Solution::SUBOPTIMAL;
                break;
            case GLP_NOFEAS:
                status = Solution::INFEASIBLE;
                break;
            case GLP_UNDEF:
                status = Solution::NOT_SOLVED;
                break;
        }
    }
    if(sol) {
        sol->clean();
        sol->setStatus(status);
    }
    if(status == Solution::OPTIMAL || status == Solution::SUBOPTIMAL) {
        obj = glp_mip_obj_val(model_);
        if(sol)
            for(auto it = varOrder_.begin(); it != varOrder_.end(); ++it)
                sol->addVariable(lp_->getVariable(it.key()), glp_mip_col_val(model_, it.value()));
    }
    if(sol)
        sol->setObjective(obj);
    return obj;
}

void GLPK::addVar(Variable *v) {
    glp_add_cols(model_, 1);
    varOrder_.insert(v->getID(), varOrder_.size()+1);
    glp_set_col_name(model_, varOrder_[v->getID()], v->getID().toStdString().c_str());
    glp_set_col_bnds(model_, varOrder_[v->getID()], GLP_DB, v->getLowerBound(), v->getUpperBound());
    switch(v->getType()) {
        case Variable::BINARY:
            glp_set_col_kind(model_, varOrder_[v->getID()], GLP_BV);
            break;
        case Variable::BOUNDED:
            glp_set_col_kind(model_, varOrder_[v->getID()], GLP_IV);
            break;
        case Variable::CONTINUOUS:
            glp_set_col_kind(model_, varOrder_[v->getID()], GLP_CV);
            break;
    }
}

void GLPK::addLinearConstraint(LinearConstraint *c) {
    glp_add_rows(model_, 1);
    constOrder_.insert(c->getID(), constOrder_.size()+1);
    glp_set_row_name(model_, constOrder_[c->getID()], c->getID().toStdString().c_str());

    double bound = c->getRHS()-c->getLinearExpression()->getConst();
    switch(c->getRelation()) {
        case Constraint::LESS_EQ:
            glp_set_row_bnds(model_, constOrder_[c->getID()], GLP_UP, 0, bound);
            break;
        case Constraint::GREATER_EQ:
            glp_set_row_bnds(model_, constOrder_[c->getID()], GLP_LO, bound, 0);
            break;
        case Constraint::EQUAL:
            glp_set_row_bnds(model_, constOrder_[c->getID()], GLP_FX, bound, bound);
            break;
    }
    nz_ += c->getLinearExpression()->getTerms().size();
}

void GLPK::addQuadConstraint(QuadConstraint *c) {
    Q_UNUSED(c);
}

void GLPK::setObjective() {
    switch(lp_->getSense()) {
        case LinearProgram::MAXIMIZE:
            glp_set_obj_dir(model_, GLP_MAX);
            break;
        case Program::MINIMIZE:
            glp_set_obj_dir(model_, GLP_MIN);
            break;
    }
    LinearExpression *obj = lp_->getObjective();

    for(auto it = obj->getTerms().begin(); it != obj->getTerms().end(); ++it)
        glp_set_obj_coef(model_, varOrder_[it.key()->getID()], it.value());
    // Constant term
    glp_set_obj_coef(model_, 0, obj->getConst());
}
