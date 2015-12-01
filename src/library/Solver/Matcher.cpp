#include "Matcher.h"

Matcher::Matcher() : QRunnable(), ICleanable(), QObject() {
    pb_ = 0;
    cfg_ = 0;
    s_ = 0;
    obj_ = 0;
    slout_ = 0;
}

Matcher::Matcher(Problem *pb, Configuration *cfg) : Matcher() {
    setProblem(pb);
    setConfiguration(cfg);
}

Matcher::~Matcher() {
    clean();
}

void Matcher::clean() {
    if(s_)
        delete s_;
    s_ = 0;
}

Problem *Matcher::getProblem() {
    return pb_;
}

void Matcher::setProblem(Problem *pb) {
    pb_ = pb;
}

Configuration *Matcher::getConfiguration() {
    return cfg_;
}

void Matcher::setConfiguration(Configuration *cfg) {
    clean();
    cfg_ = cfg;
    if(cfg)
        s_ = PluginLoader().loadSolver(Solver::fromName(cfg->solver));
}

double Matcher::getObjective() {
    return obj_;
}

void Matcher::setOutputSolutionList(SolutionList *slout) {
    slout_ = slout;
}

void Matcher::run(SolutionList *slout) {
    setOutputSolutionList(slout);
    run();
}

void Matcher::run() {
    obj_ = INFINITY;
    if(!pb_)
        Exception("The matcher needs a problem to solve before running the matching algorithm.");
    if(!cfg_)
        Exception("The matcher needs a configuration to run the matching algorithm.");
    if(!s_)
        Exception("The matcher has failed initializing a solver, thus it can't run the matching algorithm.");
    cfg_->matchingType = pb_->getType();
    cfg_->check();

    // Variables declaration
    GraphEditDistance *ged = 0;
    SubgraphMatching *sm = 0;
    Formulation *f = 0;
    SolutionList *sl = 0;

    switch(pb_->getType()) {
        case Problem::GED:
            switch(cfg_->gedMethod) {
                case GraphEditDistance::LINEAR:
                    ged = new LinearGraphEditDistance(pb_, cfg_->upperbound);
                    break;
                case GraphEditDistance::BIPARTITE:
                    initBipartiteCosts();
                    ged = new BipartiteGraphMatching(pb_, cfg_->upperbound);
                    break;
                default:
                    break;
            }
            f = (Formulation *) ged;
            break;
        case Problem::SUBGRAPH:
            switch(cfg_->subMethod) {
                case SubgraphMatching::EXACT:
                    sm = new SubgraphIsomorphism(pb_, cfg_->induced);
                    break;
                case SubgraphMatching::LABEL:
                    sm = new SubstitutionTolerantSubgraphMatching(pb_, cfg_->upperbound, cfg_->induced);
                    break;
                case SubgraphMatching::TOPOLOGY:
                    sm = new MinimumCostSubgraphMatching(pb_, cfg_->upperbound, cfg_->induced);
                    break;
                default:
                    break;
            }
            f = (Formulation *) sm;
            break;
        case Problem::NONE:
            break;
        default:
            break;
    }

    if(f) {
        switch(f->getProgram()->getType()) {
            case Program::LINEAR:
                s_->init(f->getLinearProgram(), cfg_);
                break;
            case Program::QUADRATIC:
                s_->init(f->getQuadProgram(), cfg_);
                break;
        }

        sl = slout_ ? slout_ : new SolutionList();
        sl->setFormulation(f);
        bool storeSolution = (cfg_->number > 1 || !cfg_->solution.isEmpty() || slout_);

        do {
            if(storeSolution)
                sl->newSolution();
            obj_ = s_->solve(sl->lastSolution());

            // Cut the found solution
            if(cfg_->number > 1) {
                f->cut(sl->lastSolution(), cfg_->cutMethod);
                s_->update();
            }

        } while (storeSolution && (sl->getSolutionCount() < cfg_->number) && sl->lastSolution()->isValid());

        // Save solution to file
        if(!cfg_->solution.isEmpty()) {
            QString filename = cfg_->solution;
            if(!QString::compare(filename, GEMPP_AUTO))
                filename = QString("%1_%2.sol").arg(pb_->getQuery()->getID(), pb_->getTarget()->getID());
            if(!cfg_->outputDir.isEmpty())
                filename = cfg_->outputDir + "/" + filename;
            sl->save(filename);
        }
        // Save program to file
        if(!cfg_->program.isEmpty()) {
            QString filename = cfg_->program;
            if(!QString::compare(filename, GEMPP_AUTO))
                filename = QString("%1_%2.lp").arg(pb_->getQuery()->getID(), pb_->getTarget()->getID());
            if(!cfg_->outputDir.isEmpty())
                filename = cfg_->outputDir + "/" + filename;
            f->getProgram()->save(filename);
        }

        // Retrieves the best objective (first solution)
        if(sl->getSolution(0))
            obj_ = sl->getSolution(0)->getObjective();

        // Round the objective according to the precision
        obj_ = roundAtPrecision(obj_);

        // If no output file is given, write to stdout
        //if(cfg_->matrix.isEmpty())
        //    qcout << obj_ << endl;

        if(!slout_) {
            switch(pb_->getType()) {
                case Problem::GED:
                    delete ged;
                    break;
                case Problem::SUBGRAPH:
                    delete sm;
                    break;
                case Problem::NONE:
                    break;
                default:
                    break;
            }
            if(sl)
                delete sl;
        }
    }

    emit finished(pb_, obj_);
}

void Matcher::initBipartiteCosts() {
    int nVP, nVT, i, k;
    nVP = pb_->getQuery()->getVertexCount();
    nVT = pb_->getTarget()->getVertexCount();

    BipartiteEdges *bipe;
    for(i=0; i < nVP; ++i) {
        for(k=0; k < nVT; ++k) {
            bipe = new BipartiteEdges(pb_, i, k);
            s_->init(bipe->getLinearProgram());
            pb_->addCost(i, k, s_->solve(), GraphElement::VERTEX);
            delete bipe;
        }
    }
    Vertex *v;
    for(i=0; i < nVP; ++i) {
        v = pb_->getQuery()->getVertex(i);
        for(auto e : v->getEdges(Vertex::EDGE_IN_OUT))
            v->setCost(v->getCost()+e->getCost());
    }
    for(k=0; k < nVT; ++k) {
        v = pb_->getTarget()->getVertex(k);
        for(auto e : v->getEdges(Vertex::EDGE_IN_OUT))
            v->setCost(v->getCost()+e->getCost());
    }
}
