#include "Formulation.h"

const char *Formulation::cutMethodName[Formulation::COUNT] = {
    "Solution",
    "Matchings",
    "Elements"
};

Formulation::CutMethod Formulation::fromName(QString name) {
    for(CutMethod m = (CutMethod)0; m < COUNT; m = (CutMethod)((int)m + 1))
        if(QString(cutMethodName[m]).startsWith(name, Qt::CaseInsensitive))
            return m;
    GEM_exception(QString("Cut method '%1' not recognized, please use s(olution), m(atchings) or e(lements).").arg(name));
    return COUNT;
}

QString Formulation::toName(CutMethod method) {
    return cutMethodName[(int)method];
}

Formulation::Formulation() : pb_(0), p_(0), lp_(0), qp_(0), cuts_(0), low_(false), induced_(false) {}

Formulation::Formulation(Problem *pb, bool low, bool induced) : Formulation() {
    pb_ = pb;
    low_ = low;
    induced_ = induced;
}

void Formulation::setProblem(Problem *pb) {
    pb_ = pb;
}

Problem *Formulation::getProblem() {
    return pb_;
}

LinearProgram *Formulation::getLinearProgram() {
    if(p_->getType() == Program::QUADRATIC)
        GEM_exception("A quadratic formulation has no linear program");
    return lp_;
}

QuadProgram *Formulation::getQuadProgram() {
    if(p_->getType() == Program::LINEAR)
        GEM_exception("A linear formulation has no quadratic program");
    return qp_;
}

Program *Formulation::getProgram() {
    return p_;
}

void Formulation::init(double up) {
    nVP = pb_->getPattern()->getVertexCount();
    nVT = pb_->getTarget()->getVertexCount();
    nEP = pb_->getPattern()->getEdgeCount();
    nET = pb_->getTarget()->getEdgeCount();
    i = j = k = l = ij = kl = 0;
    isDirected = (pb_->getPattern()->getType() == Graph::DIRECTED);
    initVariables();
    initCosts();
    restrictProblem(up);
    cuid_ = 0;
    initConstraints();
    initObjective();
    if(lp_ != 0)
        p_ = (Program *) lp_;
    else if(qp_ != 0)
        p_ = (Program *) qp_;
    else
        GEM_exception("The program has not been created during formulation initialization");
}

void Formulation::updateUpperBound(double up) {
    restrictProblem(up);
    cuid_ = 0;
    initConstraints();
}
