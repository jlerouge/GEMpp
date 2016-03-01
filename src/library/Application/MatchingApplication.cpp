#include "MatchingApplication.h"

MatchingApplication::MatchingApplication(int &argc, char **argv, Problem::Type type, bool isMultiMatching) : ConsoleApplication(argc, argv), mutex_(QMutex::Recursive) {
    cfg_ = 0;
    matchingType_ = type;
    isMultiMatching_ = isMultiMatching;
    matrix_ = 0;
    w_ = 0;
    g1_ = 0;
    g2_ = 0;
    gl1_ = 0;
    gl2_ = 0;
}

MatchingApplication::~MatchingApplication() {
    if(cfg_)
        delete cfg_;
    if(matrix_)
        delete matrix_;
    if(w_)
        delete w_;
    if(g1_)
        delete g1_;
    if(g2_)
        delete g2_;
    // Don't delete twice if they are the same lists
    if(gl2_ && gl1_ && (gl2_ != gl1_))
        delete gl2_;
    if(gl1_)
        delete gl1_;
    //    if(mutex_)
    //        delete mutex_;
}

void MatchingApplication::finished(Problem *problem, double objective) {
    if(!matrix_)
        Exception("The objective matrix must be initialized before updating.");
    matrix_->setElement(problem->getQuery()->getIndex(), problem->getTarget()->getIndex(), objective);

    mutex_.lock();
    population_.remove(problem);
    delete problem;
    // Make sure finalize is called only once
    if(population_.empty())
        finalize();
    mutex_.unlock();
}

void MatchingApplication::finalize() {
    if(isMultiMatching_ && (gl1_ == gl2_))
        matrix_->symmetrize();
    if(!cfg_->matrix.isEmpty())
        matrix_->save(cfg_->matrix);
    else
        matrix_->show();
    quit();
}

int MatchingApplication::match() {
    try{
        addOptions();
        processArguments();
        initConfiguration();

        // Cleaning
        if(w_)
            delete w_;
        if(g1_)
            delete g1_;
        if(g2_)
            delete g2_;
        if(gl1_)
            delete gl1_;
        if(gl2_)
            delete gl2_;
        w_ = 0;
        g1_ = g2_ = 0;
        gl1_ = gl2_ = 0;

        // Check number of arguments
        QStringList args = positionalArguments();
        if(args.size() != 2)
            Exception(QString("You must provide exactly two %1 (%2 given)").arg(isMultiMatching_?"directories":"graphs").arg(args.size()));

        // Loading weights and graphs
        w_ = new Weights(cfg_->substitution, cfg_->creation);
        if(isMultiMatching_) {
            gl1_ = new GraphList(QDir(args.at(0)), cfg_->ext);
            gl2_ = (args.at(0).compare(args.at(1)) == 0)? gl1_ : new GraphList(QDir(args.at(1)), cfg_->ext);
        } else {
            g1_ = new Graph(args.at(0));
            g2_ = new Graph(args.at(1));
        }
        initMatrix();
        QThreadPool::globalInstance()->setMaxThreadCount(cfg_->parallelInstances);

        // Running the matching(s)
        if(isMultiMatching_) {
            for(auto i : *gl1_)
                for(auto j : *gl2_)
                    if((gl1_ != gl2_) || (j->getIndex() > i->getIndex()))
                        queue_.enqueue(qMakePair(i,j));
        } else {
            queue_.enqueue(qMakePair(g1_, g2_));
        }
        populate();

        return exec();
    } catch(std::exception &e) {
        error(e);
    }
    return EXIT_FAILURE;
}

void MatchingApplication::prepare(Problem *problem, Weights *weights) {
    connect(problem, SIGNAL(prepare(Problem*,Weights*)), this, SLOT(prepare(Problem*,Weights*)));
    connect(problem, SIGNAL(ready(Problem*)), this, SLOT(solve(Problem*)));
    problem->computeCosts(weights);
}

void MatchingApplication::solve(Problem *problem) {
    Matcher *matcher = new Matcher(problem, cfg_);
    matcher->setAutoDelete(true);
    if(population_.contains(problem))
        connect(matcher, SIGNAL(finished(Problem*,double)), this, SLOT(finished(Problem*,double)));
    else if(problem->getParent())
        connect(matcher, SIGNAL(finished(Problem*,double)), problem->getParent(), SLOT(updateCost(Problem*,double)));
    QThreadPool *tp = QThreadPool::globalInstance();
    tp->start(matcher);
}

void MatchingApplication::populate() {
    QPair<Graph*, Graph*> pair;
    while(!queue_.isEmpty()) {
        pair = queue_.dequeue();
        Problem *problem = new Problem(matchingType_, pair.first, pair.second);
        population_.insert(problem);
        prepare(problem, w_);
    }
}

void MatchingApplication::initMatrix() {
    if(matrix_)
        delete matrix_;
    int rows = 1, cols = 1;
    if(isMultiMatching_) {
        rows = gl1_->getGraphCount();
        cols = gl2_->getGraphCount();
    }
    matrix_ = new Matrix<double>(rows, cols, 0.0);
}

Matrix<double> *MatchingApplication::matrix() {
    return matrix_;
}

void MatchingApplication::addOptions() {
    addSubstitutionOption();
    addCreationOption();
    addNumberOption();
    addCutOption();
    if(isMultiMatching_) {
        addAutoProgramsOption();
        addAutoSolutionsOption();
        addOutputDirOption();
        addExtensionOption();
        addMatrixOption();
        addJobsOption();
    } else {
        addProgramOption();
        addAutoProgramOption();
        addSolutionOption();
        addAutoSolutionOption();
    }
    switch(matchingType_) {
        case Problem::GED:
            addFormulationOption();
            break;
        case Problem::SUBGRAPH:
            addToleranceOption();
            addInducedOption();
            break;
        default:
            break;
    }
    addExplorationOption();
    addTimeLimitOption();
    addSolverOption();
    addVerboseOption();
    addVersionOption();
    addHelpOption();
}

void MatchingApplication::initConfiguration() {
    if(cfg_)
        delete cfg_;
    cfg_ = new Configuration();
    cfg_->matchingType = matchingType_;
    if(isOptionSet("substitution"))
        cfg_->substitution = optionValue("substitution");
    if(isOptionSet("creation"))
        cfg_->creation = optionValue("creation");
    if(isOptionSet("number"))
        cfg_->number = optionValue("number").toInt();
    if(isOptionSet("cut"))
        cfg_->cutMethod = Formulation::fromName(optionValue("cut"));

    if(isMultiMatching_) {
        if(isOptionSet("programs"))
            cfg_->program = GEMPP_AUTO;
        if(isOptionSet("solutions"))
            cfg_->solution = GEMPP_AUTO;
        if(isOptionSet("output-dir"))
            cfg_->outputDir = optionValue("output-dir");
        if(isOptionSet("ext"))
            cfg_->ext = optionValue("ext");
        if(isOptionSet("matrix")) {
            cfg_->matrix = optionValue("matrix");
            if(!cfg_->matrix.isEmpty()) {
                QFile f(cfg_->matrix);
                if(f.exists()) {
                    qcout << QString("The file %1 already exists, do you want to overwrite it ? [y/N]").arg(f.fileName()) << endl;
                    char c = getchar();
                    if(c == 'y' || c == 'Y') {
                        f.remove();
                    } else {
                        qcout << "Program interrupted by user." << endl;
                        ::exit(EXIT_FAILURE);
                    }
                }
            }
        }
        if(isOptionSet("jobs"))
            cfg_->parallelInstances = optionValue("jobs").toInt();
        cfg_->threadsPerInstance = qMax(cfg_->threadsPerInstance / cfg_->parallelInstances, 1);
    } else {
        cfg_->program = (isOptionSet("program") ? optionValue("program") : (isOptionSet("auto-prog") ? GEMPP_AUTO : ""));
        cfg_->solution = (isOptionSet("solution") ? optionValue("solution") : (isOptionSet("auto-sol") ? GEMPP_AUTO : ""));
    }

    switch(cfg_->matchingType) {
        case Problem::GED:
            if(isOptionSet("formulation"))
                cfg_->gedMethod = GraphEditDistance::fromName(optionValue("formulation"));
            break;
        case Problem::SUBGRAPH:
            if(isOptionSet("tolerance"))
                cfg_->subMethod = SubgraphMatching::fromName(optionValue("tolerance"));
            cfg_->induced = isOptionSet("induced");
            break;
        default:
            break;
    }

    if(isOptionSet("explore"))
        cfg_->upperbound = optionValue("explore").toDouble()/100;
    if(isOptionSet("time"))
        cfg_->timeLimit = optionValue("time").toDouble();

    if(isOptionSet("solver"))
        cfg_->solver = optionValue("solver");
    cfg_->verbose = isOptionSet("verbose");

    // Checks the configuration
    cfg_->check();
}

Configuration *MatchingApplication::configuration() {
    return cfg_;
}


void MatchingApplication::addSubstitutionOption() {
    addOption("s", "substitution", "Defines the weights for substitution costs.", "file.fw");
}

void MatchingApplication::addCreationOption() {
    addOption("c", "creation", "Defines the weights for creation costs.", "file.fw");
}

void MatchingApplication::addNumberOption() {
    addOption("n", "number", "Searches the 'n' best solutions.", "int");
}

void MatchingApplication::addCutOption() {
    addOption("",  "cut", "Defines the cut method (default : s).", "s/m/e", "s");
}

void MatchingApplication::addExtensionOption() {
    addOption("", "ext", "Restricts the graph extension", ".gxl/.gml");
}

void MatchingApplication::addOutputDirOption() {
    addOption("d", "output-dir", "Sets the output directory.", "dir");
}

void MatchingApplication::addProgramOption() {
    addOption("p", "program", "Outputs the program to the given file.", "file.mps/.lp");
}

void MatchingApplication::addAutoProgramOption() {
    addOption("P", "auto-prog", "Shortcut for option '-p g1_g2.lp'.");
}

void MatchingApplication::addAutoProgramsOption() {
    addOption("p", "programs", "Outputs the programs.");
}

void MatchingApplication::addSolutionOption() {
    addOption("o", "solution", "Outputs the solution to the given file.", "file.sol");
}

void MatchingApplication::addAutoSolutionOption() {
    addOption("O", "auto-sol", "Shortcut for option '-o g1_g2.sol'.");
}

void MatchingApplication::addAutoSolutionsOption() {
    addOption("o", "solutions", "Outputs the solutions.");
}

void MatchingApplication::addMatrixOption() {
    addOption("m", "matrix", "Outputs the distances to the given file.", "file.mat");
}

void MatchingApplication::addFormulationOption() {
    addOption("f", "formulation", "Sets the formulation type (default : l).", "l/q/b", "l");
}

void MatchingApplication::addToleranceOption() {
    addOption("t", "tolerance", "Sets the tolerance level (default : t).", "e/l/t", "t");
}

void MatchingApplication::addInducedOption() {
    addOption("i", "induced", "Performs induced subgraph matching.");
}

void MatchingApplication::addExplorationOption() {
    addOption("e", "explore", "Upper bound approx (cols selection).", "0%-100%");
}

void MatchingApplication::addTimeLimitOption() {
    addOption("", "time", "Maximum solving time for on instance.", "number in seconds");
}

void MatchingApplication::addSolverOption() {
    addOption("",  "solver", "Sets the solver (default : Gurobi).", "Cplex/GLPK/Gurobi", "Gurobi");
}

void MatchingApplication::addJobsOption() {
    addOption("j",  "jobs", "Sets the number of jobs to run simultaneously.", "int", "1");
}
