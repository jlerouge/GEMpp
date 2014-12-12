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

    p->dump(QString("upperbound : %1").arg(upperbound));
    p->unindent();
    p->dump("}");
}

bool Configuration::check() {
    if((matchingType == Problem::SUBGRAPH) && (upperbound < 1.0) && (subMethod == SubgraphIsomorphism::EXACT))
        GEM_exception("GEM++ forbids upper-bound approximation with exact subgraph isomorphism.\n"
                               "Please use substitution or error tolerant form instead.");
    return true;
}
