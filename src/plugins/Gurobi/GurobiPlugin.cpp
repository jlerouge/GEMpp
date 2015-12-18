#include "GurobiPlugin.h"

Gurobi::Gurobi() : Solver() {
    try {
        env_ = new GRBEnv();
    } catch(GRBException e) {
        Exception("Gurobi is not correctly configured or has no valid license key.");
    }
    model_ = (GRBModel *)0;
}

Gurobi::~Gurobi() {
    if(model_)
        delete model_;
    delete env_;
}

void Gurobi::init(Configuration *cfg) {
    cfg_ = cfg;
    lp_ = (LinearProgram *)0;
    qp_ = (QuadProgram *)0;

    // Clean model
    if(model_)
        delete model_;
    model_ = (GRBModel *)0;
}

void Gurobi::prepare() {
    if(cfg_->verbose) {
        qcout << "Parallel : " << cfg_->parallelInstances << " instance(s) in parallel." << endl;
        qcout << "Gurobi : " << cfg_->threadsPerInstance << " thread(s)." << endl;
    }

    // Model creation
    model_ = new GRBModel(*env_);

    // Parameters
    model_->getEnv().set(GRB_DoubleParam_MIPGap, pow(10, -GEMPP_PRECISION));
    model_->getEnv().set(GRB_IntParam_OutputFlag, cfg_->verbose);
    model_->getEnv().set(GRB_DoubleParam_TimeLimit, cfg_->timeLimit);
    model_->getEnv().set(GRB_IntParam_Threads, cfg_->threadsPerInstance);
}

void Gurobi::update(bool newBounds) {
    if(lp_) {
        for(auto v : lp_->getVariables()) {
            try{
                model_->getVarByName(v->getID().toStdString());
            } catch(GRBException e) {
                addVar(v);
            }
            if(newBounds) {
                model_->getVarByName(v->getID().toStdString()).set(GRB_DoubleAttr_LB, v->getLowerBound());
                model_->getVarByName(v->getID().toStdString()).set(GRB_DoubleAttr_UB, v->getUpperBound());
            }
        }
        // Do not forget to update before adding constraints
        model_->update();
        for(auto c : lp_->getConstraints()) {
            try{
                model_->getConstrByName(c->getID().toStdString());
            } catch(GRBException e) {
                addLinearConstraint(c);
            }
        }
        // Do not forget to update before another update
        model_->update();
    } else if(qp_) {
        for(auto v : qp_->getVariables()) {
            try{
                model_->getVarByName(v->getID().toStdString());
            } catch(GRBException e) {
                addVar(v);
            }
            if(newBounds) {
                model_->getVarByName(v->getID().toStdString()).set(GRB_DoubleAttr_LB, v->getLowerBound());
                model_->getVarByName(v->getID().toStdString()).set(GRB_DoubleAttr_UB, v->getUpperBound());
            }
        }
        // Do not forget to update before adding constraints
        model_->update();
        for(auto c : qp_->getLinearConstraints()) {
            try{
                model_->getConstrByName(c->getID().toStdString());
            } catch(GRBException e) {
                addLinearConstraint(c);
            }
        }
        for(auto c : qp_->getQuadConstraints()) {
            try{
                model_->getConstrByName(c->getID().toStdString());
            } catch(GRBException e) {
                addQuadConstraint(c);
            }
        }
        // Do not forget to update before another update
        model_->update();
    }
}

double Gurobi::solve(Solution *sol) {
    if(!model_)
        Exception("Gurobi solver must be initialized before solving.");
    double obj = 0;
    switch(lp_ ? lp_->getSense() : qp_->getSense()) {
        case Program::MINIMIZE:
            obj = INFINITY;
            break;
        case Program::MAXIMIZE:
            obj = -INFINITY;
            break;
    }
    model_->optimize();

    Solution::Status status = Solution::NOT_SOLVED;
    switch(model_->get(GRB_IntAttr_Status)) {
        case GRB_LOADED:
            status = Solution::NOT_SOLVED;
            break;
        case GRB_INFEASIBLE:
            status = Solution::INFEASIBLE;
            break;
        case GRB_INF_OR_UNBD:
            status = Solution::INFEASIBLE;
            break;
        case GRB_UNBOUNDED:
            status = Solution::UNBOUNDED;
            break;
        case GRB_OPTIMAL:
            status = Solution::OPTIMAL;
            break;
        case GRB_CUTOFF:
            status = Solution::OPTIMAL;
            break;
        case GRB_ITERATION_LIMIT:
            status = Solution::SUBOPTIMAL;
            break;
        case GRB_NODE_LIMIT:
            status = Solution::SUBOPTIMAL;
            break;
        case GRB_TIME_LIMIT:
            status = Solution::SUBOPTIMAL;
            break;
        case GRB_SOLUTION_LIMIT:
            status = Solution::SUBOPTIMAL;
            break;
        case GRB_INTERRUPTED:
            status = Solution::SUBOPTIMAL;
            break;
        case GRB_NUMERIC:
            status = Solution::SUBOPTIMAL;
            break;
        case GRB_SUBOPTIMAL:
            status = Solution::SUBOPTIMAL;
            break;
    }
    if(sol) {
        sol->clean();
        sol->setStatus(status);
    }
    if(status == Solution::OPTIMAL || status == Solution::SUBOPTIMAL) {
        obj = model_->get(GRB_DoubleAttr_ObjVal);
        if(sol)
            for(int k=0; k < model_->get(GRB_IntAttr_NumVars); ++k)
                sol->addVariable((lp_?(Program *)lp_:(Program *)qp_)->getVariable(model_->getVar(k).get(GRB_StringAttr_VarName).c_str()),
                                 model_->getVar(k).get(GRB_DoubleAttr_X));
    }
    if(sol)
        sol->setObjective(obj);
    return obj;
}

void Gurobi::addVar(Variable *v) {
    char type = GRB_BINARY;
    switch(v->getType()) {
        case Variable::BINARY:
            type = GRB_BINARY;
            break;
        case Variable::BOUNDED:
            type = GRB_INTEGER;
            break;
        case Variable::CONTINUOUS:
            type = GRB_CONTINUOUS;
            break;
    }
    model_->addVar(v->getLowerBound(), v->getUpperBound(), 0.0, type, v->getID().toStdString());
}

void Gurobi::addLinearConstraint(LinearConstraint *c) {
    LinearExpression *ae = c->getLinearExpression();
    GRBLinExpr le = GRBLinExpr();
    char relation = GRB_EQUAL;
    switch(c->getRelation()) {
        case LinearConstraint::LESS_EQ:
            relation = GRB_LESS_EQUAL;
            break;
        case LinearConstraint::GREATER_EQ:
            relation = GRB_GREATER_EQUAL;
            break;
        case LinearConstraint::EQUAL:
            relation = GRB_EQUAL;
            break;
    }
    for(auto it = ae->getTerms().begin(); it != ae->getTerms().end(); ++it)
        le += model_->getVarByName(it.key()->getID().toStdString())*it.value();
    model_->addConstr(le, relation, c->getRHS()-ae->getConst(), c->getID().toStdString());
}

void Gurobi::addQuadConstraint(QuadConstraint *c) {
    QuadExpression *qe = c->getQuadExpression();
    GRBQuadExpr gqe = GRBQuadExpr();
    char relation = GRB_EQUAL;
    switch(c->getRelation()) {
        case LinearConstraint::LESS_EQ:
            relation = GRB_LESS_EQUAL;
            break;
        case LinearConstraint::GREATER_EQ:
            relation = GRB_GREATER_EQUAL;
            break;
        case LinearConstraint::EQUAL:
            relation = GRB_EQUAL;
            break;
    }
    // Linear terms
    for(auto it = qe->getTerms().begin(); it != qe->getTerms().end(); ++it)
        gqe += model_->getVarByName(it.key()->getID().toStdString())*it.value();
    // Quadratic terms
    for(auto it = qe->getQuadTerms().begin(); it != qe->getQuadTerms().end(); ++it)
        gqe += model_->getVarByName(it.key().first->getID().toStdString())*model_->getVarByName(it.key().second->getID().toStdString())*it.value();
    model_->addQConstr(gqe, relation, c->getRHS()-qe->getConst(), c->getID().toStdString());
}

void Gurobi::setObjective() {
    Program::Sense sense = Program::MINIMIZE;
    if(lp_)
        sense = lp_->getSense();
    else if(qp_)
        sense = qp_->getSense();
    switch(sense) {
        case LinearProgram::MAXIMIZE:
            model_->set(GRB_IntAttr_ModelSense, GRB_MAXIMIZE);
            break;
        case Program::MINIMIZE:
            model_->set(GRB_IntAttr_ModelSense, GRB_MINIMIZE);
            break;
    }

    if(lp_) {
        LinearExpression *obj = lp_->getObjective();
        GRBLinExpr le = GRBLinExpr();
        for(auto it = obj->getTerms().begin(); it != obj->getTerms().end(); ++it)
            le += model_->getVarByName(it.key()->getID().toStdString())*it.value();
        le += obj->getConst();
        model_->setObjective(le);
    } else if(qp_) {
        QuadExpression *obj = qp_->getObjective();
        GRBQuadExpr qe = GRBQuadExpr();
        // Linear terms
        for(auto it = obj->getQuadTerms().begin(); it != obj->getQuadTerms().end(); ++it)
            qe += model_->getVarByName(it.key().first->getID().toStdString())*model_->getVarByName(it.key().second->getID().toStdString())*it.value();
        // Quadratic terms
        for(auto it = obj->getTerms().begin(); it != obj->getTerms().end(); ++it)
            qe += model_->getVarByName(it.key()->getID().toStdString())*it.value();
        qe += obj->getConst();
        model_->setObjective(qe);
    }
}
