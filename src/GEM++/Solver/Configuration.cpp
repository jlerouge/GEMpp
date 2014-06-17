#include "Configuration.h"

Configuration::Configuration() {
    clean();
}

Configuration::~Configuration() {}

void Configuration::clean() {
    substitution = "";
    creation = "";
    outputDir = "";
    program = "";
    solution = "";
    solver = "Gurobi";
    matrix = "";
    ext = "";

    verbose = false;
    cutMethod = Formulation::SOLUTION;
    number = 1;

    matchingType = Problem::NONE;
    subMethod = SubgraphIsomorphism::TOPOLOGY;
    induced = false;
    gedMethod = GraphEditDistance::LINEAR;

    lowerbound = false;
    rowgen = false;

    upperbound = false;
    limit = 1.0;
    colgen = false;
    step = 0.0;

    threadsPerInstance = qMax(QThread::idealThreadCount(), 1);
    parallelInstances = 1;

    timeLimit = INFINITY; // seconds
}

void Configuration::print(Printer *p) {
    p->dump("Configuration {");
    p->indent();

    p->dump("substitution : "+substitution);
    p->dump("creation : "+creation);
    p->dump("outputDir : "+outputDir);
    p->dump("program : "+program);
    p->dump("solution : "+solution);
    p->dump("solver : "+solver);
    p->dump("matrix : "+matrix);
    p->dump("ext : "+ext);

    p->dump(QString("verbose : %1").arg(verbose));
    p->dump(QString("number : %1").arg(number));
    p->dump("cutMethod : "+Formulation::toName(cutMethod));

    p->dump("matchingType : "+Problem::toName(matchingType));
    switch(matchingType) {
        case Problem::GED:
            p->dump("gedMethod : "+GraphEditDistance::toName(gedMethod));
            break;
        case Problem::SUBGRAPH:
            p->dump("subMethod : "+SubgraphIsomorphism::toName(subMethod));
            p->dump(QString("induced : %1").arg(induced));
            break;
        default:
            break;
    }

    p->dump(QString("lowerbound : %1").arg(lowerbound));
    p->dump(QString("rowgen : %1").arg(rowgen));

    p->dump(QString("upperbound : %1").arg(upperbound));
    p->dump(QString("limit : %1").arg(limit));
    p->dump(QString("colgen : %1").arg(colgen));
    p->dump(QString("step : %1").arg(step));

    p->unindent();
    p->dump("}");
}

bool Configuration::check() {
    if(rowgen && colgen)
        GEM_exception("GEM++ cannot handle row-generation and column-generation at the same time.");
    if(lowerbound && colgen)
        GEM_exception("GEM++ cannot handle lowerbound approximation and column-generation at the same time yet.");
    switch(matchingType) {
        case Problem::GED:
            if(rowgen && (gedMethod == GraphEditDistance::QUADRATIC || gedMethod == GraphEditDistance::BIPARTITE))
                GEM_exception(QString("GEM++ forbids row-generation with %1 form.\n"
                                               "Please use linear form instead, or switch to column generation.")
                                       .arg(GraphEditDistance::methodName[gedMethod]));
            if(lowerbound && (gedMethod == GraphEditDistance::QUADRATIC || gedMethod == GraphEditDistance::BIPARTITE))
                GEM_exception(QString("GEM++ forbids lower-bound approximation with %1 form.\n"
                                               "Please use linear form instead, or switch to upper-bound approximation.")
                                       .arg(GraphEditDistance::methodName[gedMethod]));
            break;
        case Problem::SUBGRAPH:
            if(colgen && (subMethod == SubgraphIsomorphism::EXACT))
                GEM_exception("GEM++ forbids column-generation with exact subgraph isomorphism.\n"
                                       "Please use substitution or error tolerant form instead, or switch to row-generation.");
            if(upperbound && (subMethod == SubgraphIsomorphism::EXACT))
                GEM_exception("GEM++ forbids upper-bound approximation with exact subgraph isomorphism.\n"
                                       "Please use substitution or error tolerant form instead, or switch to lower-bound approximation.");
            break;
        default:
            break;
    }
    return true;
}
