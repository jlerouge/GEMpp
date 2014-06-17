#include "LinearExpression.h"

LinearExpression::LinearExpression() : Expression() {
    terms_ = QHash<Variable *, double>();
}

void LinearExpression::multiplyBy(double d) {
    Expression::multiplyBy(d);
    for(auto it : terms_.keys())
        terms_[it] = terms_[it] * d;
}

QHash<Variable *, double> &LinearExpression::getTerms(){
    return terms_;
}

void LinearExpression::addTerm(Term t){
    //if(t.second && t.first->isActive())
    if(t.second) // allows more flexibility
    {
        if(terms_.contains(t.first))
            terms_[t.first] += t.second;
        else
            terms_.insert(t.first, t.second);
    }
}

double LinearExpression::eval() {
    double result = Expression::eval();
    for(auto it = terms_.begin(); it != terms_.end(); ++it)
        result += it.key()->eval()*it.value();
    return result;
}

bool LinearExpression::isSet() {
    return !terms_.empty();
}

void LinearExpression::print(Printer *p) {
    p->dump(LinearExpression::toString());
}

QString LinearExpression::toString() {
    QString s = Expression::toString();
    double d;
    for(auto it = terms_.begin(); it != terms_.end(); ++it) {
        d = it.value();
        if(d < 0) {
            d = -d;
            s.append(" - ");
        } else {
            s.append(" + ");
        }
        s.append(QString::number(d)+" "+it.key()->getID());
    }
    return s;
}

LinearExpression *LinearExpression::sum(QList<Variable *> vars) {
    LinearExpression *e = new LinearExpression();
    for(Variable *v : vars)
        *e += *v;
    return e;
}

void operator+=(LinearExpression &e, Term t) {
    e.addTerm(t);
}

void operator-=(LinearExpression &e, Term t) {
    e += qMakePair(t.first, -t.second);
}

Term operator*(Variable &v, double d) {
    return qMakePair(&v, d);
}

Term operator*(double d, Variable &v) {
    return v*d;
}

LinearExpression *operator+(Term t1, Term t2) {
    LinearExpression *e = new LinearExpression();
    e->addTerm(t1);
    e->addTerm(t2);
    return e;
}

LinearExpression *operator-(Term t1, Term t2) {
    return t1 + qMakePair(t2.first, -t2.second);
}

LinearExpression *operator+(Term t, double d) {
    LinearExpression *e = new LinearExpression();
    e->addTerm(t);
    e->addConst(d);
    return e;
}

LinearExpression *operator-(Term t, double d) {
    return t + (-d);
}

LinearExpression *operator+(double d, Term t) {
    return t + d;
}

LinearExpression *operator-(double d, Term t) {
    return qMakePair(t.first, -t.second) + d;
}

LinearExpression *operator+(LinearExpression *e, Term t) {
    e->addTerm(t);
    return e;
}

LinearExpression *operator-(LinearExpression *e, Term t) {
    e->addTerm(qMakePair(t.first, -t.second));
    return e;
}
