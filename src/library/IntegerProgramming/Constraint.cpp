#include "Constraint.h"

uint Constraint::count_ = 0;

Constraint::Constraint(Expression *exp, Relation relation, double rhs) : Identified() {
    exp_ = exp;
    relation_ = relation;
    rhs_ = rhs;
    setID(QString("_C%1").arg(count_++));
}

Constraint::~Constraint() {}

Expression *Constraint::getExpression() {
    return exp_;
}

double Constraint::getRHS() {
    return rhs_;
}

Constraint::Relation Constraint::getRelation() {
    return relation_;
}

bool Constraint::eval() {
    double lhs = exp_->eval();
    switch(relation_) {
        case LESS_EQ:
            return (lhs <= rhs_);
        case GREATER_EQ:
            return (lhs >= rhs_);
        case EQUAL:
            return (fabs(lhs-rhs_) < precision); // FIXME: vérifier si ça marche
    }
    return false;
}

void Constraint::print(Printer *p) {
    p->dump(toString());
}

QString Constraint::toString() {
    QString s;
    s = exp_->toString();
    switch(relation_){
        case GREATER_EQ:
            s.append(" >= ");
            break;
        case LESS_EQ:
            s.append(" <= ");
            break;
        case EQUAL:
            s.append(" = ");
            break;
    }
    s.append(QString("%1").arg(rhs_));
    return s;
}
