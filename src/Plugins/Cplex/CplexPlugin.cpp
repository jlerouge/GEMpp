#include "CplexPlugin.h"
Cplex::Cplex() : Solver() {
    env_ = (IloEnv *)0;
    model_ = (IloModel *)0;
    cplex_ = (IloCplex *)0;
}

Cplex::~Cplex() {
    if(env_)
        delete env_;
    if(cplex_)
        delete cplex_;
    if(model_)
        delete model_;
}

void Cplex::init(Configuration *cfg) {
    // Clean up
    if(cplex_)
        delete cplex_;
    cplex_ = (IloCplex *)0;
    if(model_)
        delete model_;
    model_ = (IloModel *)0;
    if(!varOrder_.empty())
        varOrder_.clear();
    if(!constraints_.empty())
        constraints_.clear();
    if(!env_)
        env_ = new IloEnv();

    cfg_ = cfg;
    lp_ = (LinearProgram *)0;
    qp_ = (QuadProgram *)0;
}

void Cplex::prepare() {
    if(!cfg_->verbose)
        env_->setOut(env_->getNullStream());

    // Model creation
    model_ = new IloModel(*env_);
    cplex_ = new IloCplex(*model_);
    variables_ = IloNumVarArray(*env_);

    // Solver parameters
    cplex_->setParam(IloCplex::EpGap, pow(10, -PRECISION));
    cplex_->setParam(IloCplex::TiLim, cfg_->timeLimit);
    cplex_->setParam(IloCplex::Threads, cfg_->threadsPerInstance);
}

void Cplex::update(bool newBounds) {
    if(lp_) {
        for(auto v : lp_->getVariables()) {
            if(!varOrder_.contains(v))
                addVar(v);
            if(newBounds) {
                variables_[varOrder_[v]].setLB(v->getLowerBound());
                variables_[varOrder_[v]].setUB(v->getUpperBound());
            }
        }
        for(auto c : lp_->getConstraints())
            if(!constraints_.contains(c->getID()))
                addLinearConstraint(c);
    } else if(qp_) {
        for(auto v : qp_->getVariables()) {
            if(!varOrder_.contains(v))
                addVar(v);
            if(newBounds) {
                variables_[varOrder_[v]].setLB(v->getLowerBound());
                variables_[varOrder_[v]].setUB(v->getUpperBound());
            }
        }
        for(auto c : qp_->getLinearConstraints())
            if(!constraints_.contains(c->getID()))
                addLinearConstraint(c);
        for(auto c : qp_->getQuadConstraints())
            if(!constraints_.contains(c->getID()))
                addQuadConstraint(c);
    }
}

double Cplex::solve(Solution *sol) {
    if(!cplex_)
        GEM_exception("Cplex solver must be initialized before solving.");
    double obj = 0;
    switch(lp_ ? lp_->getSense() : qp_->getSense()) {
        case Program::MINIMIZE:
            obj = INFINITY;
            break;
        case Program::MAXIMIZE:
            obj = -INFINITY;
            break;
    }
    cplex_->solve();
    Solution::Status status = Solution::NOT_SOLVED;
    switch(cplex_->getStatus()) {
        case IloAlgorithm::Unknown:
            status = Solution::NOT_SOLVED;
            break;
        case IloAlgorithm::Error:
            status = Solution::NOT_SOLVED;
            break;
        case IloAlgorithm::Infeasible:
            status = Solution::INFEASIBLE;
            break;
        case IloAlgorithm::InfeasibleOrUnbounded:
            status = Solution::INFEASIBLE;
            break;
        case IloAlgorithm::Unbounded:
            status = Solution::UNBOUNDED;
            break;
        case IloAlgorithm::Feasible:
            status = Solution::SUBOPTIMAL;
            break;
        case IloAlgorithm::Optimal:
            status = Solution::OPTIMAL;
            break;
    }
    if(sol) {
        sol->clean();
        sol->setStatus(status);
    }
    if(status == Solution::OPTIMAL || status == Solution::SUBOPTIMAL) {
        obj = cplex_->getObjValue();
        if(sol) {
            IloNumArray vals(*env_);
            cplex_->getValues(vals, variables_);
            for(int k=0; k < variables_.getSize(); ++k)
                sol->addVariable((lp_?(Program *)lp_:(Program *)qp_)->getVariable(variables_[k].getName()), roundToNearestInt(vals[k]));
        }
    }
    if(sol)
        sol->setObjective(obj);
    return obj;
}

void Cplex::addVar(Variable *v) {
    IloNumVar::Type type = IloNumVar::Bool;
    switch(v->getType()) {
        case Variable::BINARY:
            type = IloNumVar::Bool;
            break;
        case Variable::BOUNDED:
            type = IloNumVar::Int;
            break;
        case Variable::CONTINUOUS:
            type = IloNumVar::Float;
            break;
    }
    varOrder_.insert(v, variables_.getSize());
    variables_.add(IloNumVar(*env_, v->getLowerBound(), v->getUpperBound(), type, v->getID().toStdString().c_str()));
}

void Cplex::addLinearConstraint(LinearConstraint *c) {
    LinearExpression *ae = c->getLinearExpression();
    IloNumExprArg exp = IloNumExprArg();
    exp = variables_[0]*0;
    for(auto it = ae->getTerms().begin(); it != ae->getTerms().end(); ++it)
        exp = exp + variables_[varOrder_[it.key()]]*it.value();

    switch(c->getRelation()) {
        case LinearConstraint::LESS_EQ:
            model_->add(exp <= c->getRHS()-ae->getConst());
            break;
        case LinearConstraint::GREATER_EQ:
            model_->add(exp >= c->getRHS()-ae->getConst());
            break;
        case LinearConstraint::EQUAL:
            model_->add(exp == c->getRHS()-ae->getConst());
            break;
    }
    constraints_.insert(c->getID());
}

void Cplex::addQuadConstraint(QuadConstraint *c) {
    QuadExpression *qe = c->getQuadExpression();
    IloNumExprArg exp = IloNumExprArg();
    exp = variables_[0]*0;

    // Linear terms
    for(auto it = qe->getTerms().begin(); it != qe->getTerms().end(); ++it)
        exp = exp + variables_[varOrder_[it.key()]]*it.value();
    // Quadratic terms
    for(auto it = qe->getQuadTerms().begin(); it != qe->getQuadTerms().end(); ++it)
        exp = exp + variables_[varOrder_[it.key().first]]*variables_[varOrder_[it.key().second]]*it.value();

    switch(c->getRelation()) {
        case LinearConstraint::LESS_EQ:
            model_->add(exp <= c->getRHS()-qe->getConst());
            break;
        case LinearConstraint::GREATER_EQ:
            model_->add(exp >= c->getRHS()-qe->getConst());
            break;
        case LinearConstraint::EQUAL:
            model_->add(exp == c->getRHS()-qe->getConst());
            break;
    }
    constraints_.insert(c->getID());
}

void Cplex::setObjective() {
    Program::Sense sense = Program::MINIMIZE;
    IloObjective obj;
    if(lp_)
        sense = lp_->getSense();
    else if(qp_)
        sense = qp_->getSense();
    switch(sense) {
        case LinearProgram::MAXIMIZE:
            obj = IloMaximize(*env_);
            break;
        case Program::MINIMIZE:
            obj = IloMinimize(*env_);
            break;
    }

    IloNumExprArg exp = IloNumExprArg();
    exp = variables_[0]*0;
    if(lp_) {
        LinearExpression *linexp = lp_->getObjective();
        for(auto it = linexp->getTerms().begin(); it != linexp->getTerms().end(); ++it)
            exp = exp + variables_[varOrder_[it.key()]]*it.value();
        exp = exp + linexp->getConst();
    } else if(qp_) {
        QuadExpression *quadexp = qp_->getObjective();
        // Linear terms
        for(auto it = quadexp->getTerms().begin(); it != quadexp->getTerms().end(); ++it)
            exp = exp + variables_[varOrder_[it.key()]]*it.value();
        // Quadratic terms
        for(auto it = quadexp->getQuadTerms().begin(); it != quadexp->getQuadTerms().end(); ++it)
            exp = exp + variables_[varOrder_[it.key().first]]*variables_[varOrder_[it.key().second]]*it.value();
        exp = exp + quadexp->getConst();
    }
    obj.setExpr(exp);
    model_->add(obj);
}
