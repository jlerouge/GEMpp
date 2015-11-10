#include "Program.h"

Program::Program(Sense sense) {
    sense_ = sense;
}

Program::~Program() {}

QHash<QString, Variable *> &Program::getVariables() {
    return variables_;
}

void Program::addVariable(Variable *v) {
    variables_.insert(v->getID(), v);
}

Variable *Program::getVariable(QString id) {
    if(!variables_.contains(id))
        Exception(QString("The requested variable %1 is not present in the program").arg(id));
    return variables_[id];
}

Program::Sense Program::getSense() {
    return sense_;
}

void Program::setSense(Sense sense) {
    sense_ = sense;
}
