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
    upperbound = 1.0;

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
    p->dump(QString("upperbound : %1").arg(upperbound));
    p->unindent();
    p->dump("}");
}

bool Configuration::check() {
    if((matchingType == Problem::GED) && lowerbound && (gedMethod == GraphEditDistance::QUADRATIC || gedMethod == GraphEditDistance::BIPARTITE))
        GEM_exception(QString("GEM++ forbids lower-bound approximation with %1 form.\n"
                                       "Please use linear form instead, or switch to upper-bound approximation.")
                               .arg(GraphEditDistance::methodName[gedMethod]));
    else
        if((matchingType == Problem::SUBGRAPH) && (upperbound < 1.0) && (subMethod == SubgraphIsomorphism::EXACT))
            GEM_exception("GEM++ forbids upper-bound approximation with exact subgraph isomorphism.\n"
                                   "Please use substitution or error tolerant form instead, or switch to lower-bound approximation.");
    return true;
}
