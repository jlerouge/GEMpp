#include "Solution.h"

const char *Solution::statusName[Solution::COUNT] = {
    "not solved",
    "infeasible",
    "unbounded",
    "suboptimal",
    "optimal"
};

Solution::Status Solution::fromName(QString name) {
    for(Status s = (Status)0; s < COUNT; s = (Status)((int)s + 1))
        if(QString(statusName[s]).startsWith(name, Qt::CaseInsensitive))
            return s;
    Exception(QString("Solution status '%1' not recognized, please use n(ot solved),\ni(nfeasible), u(nbounded), s(uboptimal) or o(ptimal).").arg(name));
    return COUNT;
}

QString Solution::toName(Status status) {
    return statusName[status];
}

Solution::Solution(Formulation *f)
{
    formulation_ = f;
    clean();
}

Solution::~Solution() {}

void Solution::addVariable(Variable *v, int value) {
    if(value) {
        variables_.insert(v, value);
        QStringList sl = v->getID().mid(2).split(',');
        if(v->getID().startsWith("x_"))
            x_variables_.insert(sl[0].toInt(), sl[1].toInt());
        else if(v->getID().startsWith("y_"))
            y_variables_.insert(sl[0].toInt(), sl[1].toInt());
    }
}

int Solution::activeIndex(int index, bool left) {
    QString pattern = left? QString("^x_%1,(.)+$") : QString("^x_(.)+,%1$");
    pattern = pattern.arg(index);
    QRegExp re(pattern);
    for(int i=0; i < variables_.size(); ++i)
        if(re.exactMatch(variables_.keys().at(i)->getID()))
            return i;
    return -1;
}

QHash<Variable *, int> &Solution::getVariables() {
    return variables_;
}

QMap<int, int> &Solution::getXVariables() {
    return x_variables_;
}

QMap<int, int> &Solution::getYVariables() {
    return y_variables_;
}

int Solution::getValue(Variable * v) {
    if(variables_.contains(v))
        return variables_[v];
    return 0;
}

void Solution::setStatus(Status status) {
    status_ = status;
}

Solution::Status Solution::getStatus() {
    return status_;
}

void Solution::setObjective(double objective) {
    objective_ = roundAtPrecision(objective);
}

double Solution::getObjective() {
    return objective_;
}

void Solution::clean() {
    variables_.clear();
    switch(formulation_->getProgram()->getSense()) {
        case Program::MINIMIZE:
            objective_ = INFINITY;
            break;
        case Program::MAXIMIZE:
            objective_ = -INFINITY;
            break;
    }
    status_ = NOT_SOLVED;
}

bool Solution::isValid() {
    return (status_ == SUBOPTIMAL) || (status_ == OPTIMAL);
}

void Solution::print(Printer *p) {
    p->dump("<?xml version=\"1.0\"?>");
    p->dump("<solution>");
    p->indent();
    formulation_->getProblem()->print(p);
    printSolution(p);
    p->unindent();
    p->dump("</solution>");
}

void Solution::printSolution(Printer *p) {
    p->dump(QString("<objective status=\"%1\" value=\"%2\"/>").arg(toName(status_)).arg(objective_));
    Problem *pb = formulation_->getProblem();

    if(status_ == SUBOPTIMAL || status_ == OPTIMAL) {
        p->dump("<nodes>");
        p->indent();
        if(!x_variables_.isEmpty())
            for(auto it = x_variables_.begin(); it != x_variables_.end(); ++it) {
                p->dump(QString("<substitution cost=\"%1\">").arg(pb->getCost(GraphElement::VERTEX, it.key(), it.value())));
                p->indent();
                p->dump(QString("<node type=\"query\" index=\"%1\"/>").arg(it.key()));
                p->dump(QString("<node type=\"target\" index=\"%1\"/>").arg(it.value()));
                p->unindent();
                p->dump("</substitution>");
            }
        if(x_variables_.size() < pb->getQuery()->getVertexCount() ||
                ((x_variables_.size() < pb->getTarget()->getVertexCount()) &&
                 (formulation_->getProblem()->getType() != Problem::SUBGRAPH))) {
            for(int i=0; i < pb->getQuery()->getVertexCount(); ++i)
                if(!x_variables_.contains(i)) {
                    p->dump(QString("<insertion cost=\"%1\">").arg(pb->getQuery()->getVertex(i)->getCost()));
                    p->indent();
                    p->dump(QString("<node type=\"query\" index=\"%1\"/>").arg(i));
                    p->unindent();
                    p->dump("</insertion>");
                }
            if(formulation_->getProblem()->getType() != Problem::SUBGRAPH)
                for(int k=0; k < pb->getTarget()->getVertexCount(); ++k)
                    if(!x_variables_.values().contains(k)) {
                        p->dump(QString("<deletion cost=\"%1\">").arg(pb->getTarget()->getVertex(k)->getCost()));
                        p->indent();
                        p->dump(QString("<node type=\"target\" index=\"%1\"/>").arg(k));
                        p->unindent();
                        p->dump("</deletion>");
                    }
        }
        p->unindent();
        p->dump("</nodes>");
        p->dump("<edges>");
        p->indent();
        if(!y_variables_.isEmpty())
            for(auto it = y_variables_.begin(); it != y_variables_.end(); ++it) {
                p->dump(QString("<substitution cost=\"%1\">").arg(pb->getCost(GraphElement::EDGE, it.key(), it.value())));
                p->indent();
                p->dump(QString("<edge type=\"query\" from=\"%1\" to=\"%2\"/>")
                        .arg(pb->getQuery()->getEdge(it.key())->getOrigin()->getIndex())
                        .arg(pb->getQuery()->getEdge(it.key())->getTarget()->getIndex()));
                p->dump(QString("<edge type=\"target\" from=\"%1\" to=\"%2\"/>")
                        .arg(pb->getTarget()->getEdge(it.value())->getOrigin()->getIndex())
                        .arg(pb->getTarget()->getEdge(it.value())->getTarget()->getIndex()));
                p->unindent();
                p->dump("</substitution>");
            }
        if(y_variables_.size() < pb->getQuery()->getEdgeCount() ||
                ((y_variables_.size() < pb->getTarget()->getEdgeCount()) &&
                 (formulation_->getProblem()->getType() != Problem::SUBGRAPH))) {
            for(int ij=0; ij < formulation_->getProblem()->getQuery()->getEdgeCount(); ++ij)
                if(!y_variables_.contains(ij)) {
                    p->dump(QString("<insertion cost=\"%1\">").arg(pb->getQuery()->getEdge(ij)->getCost()));
                    p->indent();
                    p->dump(QString("<edge type=\"query\" from=\"%1\" to=\"%2\"/>")
                            .arg(pb->getQuery()->getEdge(ij)->getOrigin()->getIndex())
                            .arg(pb->getQuery()->getEdge(ij)->getTarget()->getIndex()));
                    p->unindent();
                    p->dump("</insertion>");
                }

            if(formulation_->getProblem()->getType() != Problem::SUBGRAPH)
                for(int kl=0; kl < formulation_->getProblem()->getTarget()->getEdgeCount(); ++kl)
                    if(!y_variables_.values().contains(kl)) {
                        p->dump(QString("<deletion cost=\"%1\">").arg(pb->getTarget()->getEdge(kl)->getCost()));
                        p->indent();
                        p->dump(QString("<edge type=\"target\" from=\"%1\" to=\"%2\"/>")
                                .arg(pb->getTarget()->getEdge(kl)->getOrigin()->getIndex())
                                .arg(pb->getTarget()->getEdge(kl)->getTarget()->getIndex()));
                        p->unindent();
                        p->dump("</deletion>");
                    }
        }
        p->unindent();
        p->dump("</edges>");
    }
}

void Solution::save(const QString &filename) {
    FileUtils::save(this, filename);
}
