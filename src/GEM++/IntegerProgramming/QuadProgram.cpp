#include "QuadProgram.h"

QuadProgram::QuadProgram(Sense sense) : Program(sense) {}

QuadProgram::~QuadProgram() {
    delete objective_;
    for(auto l: linearConstraints_)
        delete l;
    for(auto q: quadConstraints_)
        delete q;
}

Program::Type QuadProgram::getType() {
    return QUADRATIC;
}

QMap<QString, LinearConstraint *> &QuadProgram::getLinearConstraints() {
    return linearConstraints_;
}

QMap<QString, QuadConstraint *> &QuadProgram::getQuadConstraints() {
    return quadConstraints_;
}

void QuadProgram::addLinearConstraint(LinearConstraint *c) {
    if(!linearConstraints_.contains(c->getID())) {
        QHash<Variable *, double> &terms = c->getLinearExpression()->getTerms();
        for(auto t = terms.begin(); t != terms.end(); ++t) {
            t.key()->addColumn(c->getID(), t.value());
            addVariable(t.key());
        }
        linearConstraints_.insert(c->getID(), c);
    }
}

void QuadProgram::addQuadConstraint(QuadConstraint *c) {
    if(!linearConstraints_.contains(c->getID())) {
        // Linear terms
        QHash<Variable *, double> &qterms = c->getQuadExpression()->getTerms();
        for(auto t = qterms.begin(); t != qterms.end(); ++t) {
            t.key()->addColumn(c->getID(), t.value());
            addVariable(t.key());
        }
        // Quadratic terms
        QHash<Quad, double> &terms = c->getQuadExpression()->getQuadTerms();
        for(auto t = terms.begin(); t != terms.end(); ++t) {
            addVariable(t.key().first);
            addVariable(t.key().second);
        }
        quadConstraints_.insert(c->getID(), c);
    }
}

QuadExpression *QuadProgram::getObjective() {
    return objective_;
}

void QuadProgram::setObjective(QuadExpression *e) {
    // Linear terms
    for(auto t = e->getTerms().begin(); t != e->getTerms().end(); ++t) {
        t.key()->addColumn("OBJ", t.value());
        addVariable(t.key());
    }
    // Quadratic terms
    for(auto t = e->getQuadTerms().begin(); t != e->getQuadTerms().end(); ++t) {
        addVariable(t.key().first);
        addVariable(t.key().second);
    }
    objective_ = e;
}

void QuadProgram::save(const QString &filename) {
    FileStream::saveFile(this, filename);
}

void QuadProgram::print(Printer *p) {
    switch(sense_){
        case MINIMIZE:
            p->dump("Minimize");
            break;
        case MAXIMIZE:
            p->dump("Maximize");
            break;
    }
    p->indent();
    objective_->print(p);
    p->unindent();
    p->dump("Subject To");
    p->indent();
    for(auto it : linearConstraints_)
        it->print(p);
    for(auto it : quadConstraints_)
        it->print(p);
    p->unindent();
    p->dump("Bounds"); //FIXME
    p->indent();
    for(auto it : variables_) {
        if(it->getType() == Variable::BOUNDED)
            p->dump(QString("%1 <= %2 <= %3").arg(it->getLowerBound()).arg(it->getID()).arg(it->getUpperBound()));
    }
    p->unindent();
    p->dump("Generals"); //FIXME
    p->indent();
    for(auto it : variables_) {
        if(it->getType() == Variable::BOUNDED)
            it->print(p);
    }
    p->unindent();
    p->dump("Binaries"); //FIXME
    p->indent();
    for(auto it : variables_) {
        if(it->getType() == Variable::BINARY)
            it->print(p);
    }
    p->unindent();
    p->dump("End");
}

void operator+=(QuadProgram &lp, LinearConstraint *c) {
    lp.addLinearConstraint(c);
}

void operator+=(QuadProgram &lp, QuadConstraint *c) {
    lp.addQuadConstraint(c);
}

void operator+=(QuadProgram &lp, QuadExpression *e) {
    lp.setObjective(e);
}
