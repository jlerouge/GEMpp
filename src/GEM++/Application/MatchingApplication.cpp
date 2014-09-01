#include "MatchingApplication.h"

MatchingApplication::MatchingApplication(int &argc, char **argv, Problem::Type type, bool isMultiMatching) : ConsoleApplication(argc, argv) {
    cfg_ = 0;
    matchingType_ = type;
    isMultiMatching_ = isMultiMatching;
    matrix_ = 0;
    w_ = 0;
    g1_ = 0;
    g2_ = 0;
    gl1_ = 0;
    gl2_ = 0;
    isPopulating_ = false;
    finishedCount_ = 0;
    totalCount_ = 0;
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
}

void MatchingApplication::finished(Problem *pb, double objective) {
    if(!matrix_)
        GEM_exception("The objective matrix must be initialized before updating.");
    matrix_->setElement(pb->getPattern()->getIndex(), pb->getTarget()->getIndex(), objective);
    delete pb;

    if(++finishedCount_ < totalCount_) {
        // There are still waiting threads
        populate();
    } else {
        // Make sure this is called only once
        finalize();
    }
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
            GEM_exception(QString("You must provide exactly two %1 (%2 given)").arg(isMultiMatching_?"directories":"graphs").arg(args.size()));

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
        finishedCount_ = 0;
        totalCount_ = queue_.size();
        populate();

        return exec();
    } catch(std::exception &e) {
        error(e);
    }
    return EXIT_FAILURE;
}

void MatchingApplication::populate() {
    if(!isPopulating_) {
        isPopulating_ = true;
        QThreadPool *tp = QThreadPool::globalInstance();
        QPair<Graph*, Graph*> pair;
        int current = tp->activeThreadCount(), max = tp->maxThreadCount();
        while(current < max && !queue_.isEmpty()) {
            pair = queue_.dequeue();
            Matcher *matcher = new Matcher(new Problem(matchingType_, pair.first, pair.second, w_), cfg_);
            matcher->setAutoDelete(true);
            connect(matcher, SIGNAL(finished(Problem*,double)), this, SLOT(finished(Problem*,double)));
            tp->start(matcher);
            ++current;
        }
        isPopulating_ = false;
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
    addAggregationOption();
    addExplorationOption();
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
            cfg_->program = GEM_AUTO;
        if(isOptionSet("solutions"))
            cfg_->solution = GEM_AUTO;
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
        cfg_->program = (isOptionSet("program") ? optionValue("program") : (isOptionSet("auto-prog") ? GEM_AUTO : ""));
        cfg_->solution = (isOptionSet("solution") ? optionValue("solution") : (isOptionSet("auto-sol") ? GEM_AUTO : ""));
    }

    switch(cfg_->matchingType) {
        case Problem::GED:
            if(isOptionSet("formulation"))
                cfg_->gedMethod = GraphEditDistance::fromName(optionValue("formulation"));
            break;
        case Problem::SUBGRAPH:
            if(isOptionSet("tolerance"))
                cfg_->subMethod = SubgraphIsomorphism::fromName(optionValue("tolerance"));
            cfg_->induced = isOptionSet("induced");
            break;
        default:
            break;
    }

    cfg_->lowerbound = isOptionSet("aggregate");
    if(isOptionSet("explore"))
        cfg_->upperbound = optionValue("explore").toDouble()/100;

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

void MatchingApplication::addAggregationOption() {
    addOption("a", "aggregate", "Lower bound approx (rows aggregation).");
}

void MatchingApplication::addExplorationOption() {
    addOption("e", "explore", "Upper bound approx (cols selection).", "0 - 100%");
}

void MatchingApplication::addSolverOption() {
    addOption("",  "solver", "Sets the solver (default : Gurobi).", "Cplex/GLPK/Gurobi", "Gurobi");
}

void MatchingApplication::addJobsOption() {
    addOption("j",  "jobs", "Sets the number of jobs to run simultaneously.", "int", "1");
}
