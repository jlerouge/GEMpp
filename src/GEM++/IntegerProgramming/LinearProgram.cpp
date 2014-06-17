#include "LinearProgram.h"

LinearProgram::LinearProgram(Sense sense) : Program(sense) {
    out_ = LP;
}

LinearProgram::~LinearProgram() {
    delete objective_;
    for(auto c : constraints_)
        delete c;
}

Program::Type LinearProgram::getType() {
    return LINEAR;
}

QMap<QString, LinearConstraint *> &LinearProgram::getConstraints() {
    return constraints_;
}

void LinearProgram::addLinearConstraint(LinearConstraint *c) {
    if(!constraints_.contains(c->getID())) {
        QHash<Variable *, double> terms = c->getLinearExpression()->getTerms();
        for(auto t = terms.begin(); t != terms.end(); ++t) {
            t.key()->addColumn(c->getID(), t.value());
            addVariable(t.key());
        }
        constraints_.insert(c->getID(), c);
    }
}

//void LinearProgram::clearConstraints() {
//    constraints_.clear();
//}

LinearExpression *LinearProgram::getObjective() {
    return objective_;
}

void LinearProgram::setObjective(LinearExpression *e) {
    for(auto t = e->getTerms().begin(); t != e->getTerms().end(); ++t) {
        t.key()->addColumn("OBJ", t.value());
        addVariable(t.key());
    }
    objective_ = e;
}

void LinearProgram::printMPS(Printer *p) {
    p->dump("NAME\tGEM++");
    p->dump("OBJSENSE");
    p->indent();
    switch(sense_){
        case MINIMIZE:
            p->dump("MIN");
            break;
        case MAXIMIZE:
            p->dump("MAX");
            break;
    }
    p->unindent();

    // Define the rows (objective + constraints)
    p->dump("ROWS");
    p->indent();
    if(objective_->isSet()) {
        p->dump("N\tOBJ");
    }
    QString s;
    for(auto c : constraints_) {
        switch(c->getRelation()){
            case LinearConstraint::EQUAL:
                s = "E";
                break;
            case LinearConstraint::GREATER_EQ:
                s = "G";
                break;
            case LinearConstraint::LESS_EQ:
                s = "L";
                break;
        }
        s.append(QString("\t%1").arg(c->getID()));
        p->dump(s);
    }
    p->unindent();

    // Define the columns (variables)
    p->dump("COLUMNS");
    p->indent();
    for(Variable *v : variables_) {
        for(auto t = v->getColumns().begin(); t != v->getColumns().end(); ++t) {
            QString space = (t.value() >= 0)?" ":"";
            p->dump(QString("%1\t%2\t%3%4").arg(v->getID(), t.key(), space, QString::number(t.value(), 'f', PRECISION)));
        }
        p->newLine();
    }
    p->unindent();

    // Define the right-hand-sides
    p->dump("RHS");
    p->indent();
    for(auto c : constraints_)
        p->dump(QString("RHS\t\t%1\t%2").arg(c->getID(), QString::number(c->getRHS(), 'f', PRECISION)));
    p->unindent();

    p->dump("BOUNDS");
    p->indent();
    // Define the variable bounds
    for(Variable *v : variables_) {
        switch (v->getType()) {
            case Variable::BINARY:
                p->dump("BV\tBOUND\t"+v->getID());
                break;
            case Variable::BOUNDED:
                p->dump(QString("UI\tBOUND\t%1\t%2").arg(v->getID()).arg(v->getUpperBound()));
                p->dump(QString("LI\tBOUND\t%1\t%2").arg(v->getID()).arg(v->getLowerBound()));
                break;
            case Variable::CONTINUOUS:
                p->dump(QString("UP\tBOUND\t%1\t%2").arg(v->getID()).arg(v->getUpperBound()));
                p->dump(QString("LO\tBOUND\t%1\t%2").arg(v->getID()).arg(v->getLowerBound()));
                break;
        }
    }
    p->unindent();
    p->dump("ENDATA");
}

void LinearProgram::printLP(Printer *p) {
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
    for(auto it : constraints_)
        it->print(p);
    p->unindent();
    p->dump("Bounds");
    p->indent();
    for(auto it : variables_) {
        if(it->getType() != Variable::BINARY || !it->isActive())
            p->dump(QString("%1 <= %2 <= %3").arg(it->getLowerBound()).arg(it->getID()).arg(it->getUpperBound()));
    }
    p->unindent();
    p->dump("Generals");
    p->indent();
    for(auto it : variables_) {
        if(it->getType() == Variable::BOUNDED)
            it->print(p);
    }
    p->unindent();
    p->dump("Binaries");
    p->indent();
    for(auto it : variables_) {
        if(it->getType() == Variable::BINARY)
            it->print(p);
    }
    p->unindent();
    p->dump("End");
}

LinearProgram::Output LinearProgram::getOutput() {
    return out_;
}

void LinearProgram::setOutput(Output out) {
    out_ = out;
}

void LinearProgram::print(Printer *p) {
    switch(out_) {
        case LP:
            printLP(p);
            break;
        case MPS:
            printMPS(p);
            break;
    }
}

void LinearProgram::save(const QString &filename) {
    if(filename.endsWith(".mps", Qt::CaseInsensitive))
        out_ = MPS;
    else if (filename.endsWith(".lp", Qt::CaseInsensitive))
        out_ = LP;
    else
        GEM_exception(QString("%1 is not a *.mps nor *.lp file.").arg(filename));
    FileStream::saveFile(this, filename);
}

void operator+=(LinearProgram &lp, LinearConstraint *c) {
    lp.addLinearConstraint(c);
}

void operator+=(LinearProgram &lp, LinearExpression *e) {
    lp.setObjective(e);
}
