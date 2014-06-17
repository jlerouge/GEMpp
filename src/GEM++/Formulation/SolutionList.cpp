#include "SolutionList.h"

SolutionList::SolutionList(Formulation *f) : formulation_(f) {}

SolutionList::~SolutionList() {
    for(auto it : solutions_)
        delete it;
}

void SolutionList::setFormulation(Formulation *f) {
    formulation_ = f;
}

Formulation *SolutionList::getFormulation() {
    return formulation_;
}

Solution *SolutionList::newSolution() {
    solutions_.push_back(new Solution(formulation_));
    return lastSolution();
}

Solution *SolutionList::lastSolution() {
    return solutions_.empty() ? 0 : solutions_.last();
}

Solution *SolutionList::getSolution(int i) {
    return (i >= solutions_.size()) ? 0 : solutions_[i];
}

int SolutionList::getSolutionCount() {
    return solutions_.size();
}

void SolutionList::print(Printer *p) {
    if(solutions_.isEmpty())
        GEM_exception("The SolutionList cannot be printed without having actual solutions.");
    p->dump("<?xml version=\"1.0\"?>");
    p->dump("<solutionlist>");
    p->indent();
    formulation_->getProblem()->print(p);
    p->dump(QString("<solutions count=\"%1\">").arg(solutions_.size()));
    p->indent();
    for(int k=0; k < solutions_.size(); ++k) {
        p->dump(QString("<solution number=\"%1\">").arg(k));
        p->indent();
        solutions_[k]->printSolution(p);
        p->unindent();
        p->dump("</solution>");
    }
    p->unindent();
    p->dump("</solutions>");
    p->unindent();
    p->dump("</solutionlist>");
}

QList<Solution *>::iterator SolutionList::begin() {
    return solutions_.begin();
}

QList<Solution *>::iterator SolutionList::end() {
    return solutions_.end();
}

void SolutionList::save(const QString &filename) {
    FileStream::saveFile(this, filename);
}
