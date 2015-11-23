#include "QuadExpression.h"

QuadExpression::QuadExpression() : LinearExpression() {
    quadTerms_ = QHash<Quad, double>();
}

void QuadExpression::multiplyBy(double d) {
    LinearExpression::multiplyBy(d);
    for(auto it : quadTerms_.keys())
        quadTerms_[it] = quadTerms_[it] * d;
}

QHash<Quad, double> &QuadExpression::getQuadTerms(){
    return quadTerms_;
}

void QuadExpression::addQuadTerm(QuadTerm t){
    //if(t.second && isActive(t))
    if(t.second) // allows more flexibility
    {
        if(quadTerms_.contains(t.first))
            quadTerms_[t.first] += t.second;
        else
            quadTerms_.insert(t.first, t.second);
    }
}

double QuadExpression::eval() {
    double result = LinearExpression::eval();
    for(auto it = quadTerms_.begin(); it != quadTerms_.end(); ++it)
        result += it.key().first->eval()*it.key().second->eval()*it.value();
    return result;
}

bool QuadExpression::isSet() {
    return (LinearExpression::isSet() || !quadTerms_.empty());
}

void QuadExpression::print(Printer *p) {
    p->dump(QuadExpression::toString());
}

QString QuadExpression::toString() {
    QString s = LinearExpression::toString();
    double d;
    for(auto it = quadTerms_.begin(); it != quadTerms_.end(); ++it) {
        d = it.value();
        if(d < 0) {
            d = -d;
            s.append(" - ");
        } else {
            s.append(" + ");
        }
        s.append(QString::number(d)+" "+it.key().first->getID()+" "+it.key().second->getID());
    }
    return s;
}

QuadExpression *QuadExpression::sum(QList<Variable*> &vars) {
    QuadExpression *e = new QuadExpression();
    for(Variable *v : vars)
        e->addTerm(qMakePair(v, 1.0));
    return e;
}

QuadExpression *QuadExpression::sum(QList<Quad> &quads) {
    QuadExpression *e = new QuadExpression();
    for(Quad q : quads)
        e->addQuadTerm(qMakePair(q, 1.0));
    return e;
}

void operator+=(QuadExpression &e, QuadTerm t) {
    e.addQuadTerm(t);
}

void operator-=(QuadExpression &e, QuadTerm t) {
    e.addQuadTerm(qMakePair(t.first, -t.second));
}

QuadTerm operator*(Variable &v, Term t) {
    return qMakePair(qMakePair(&v, t.first), t.second);
}

QuadTerm operator*(Term t, Variable &v) {
    return v*t;
}

QuadTerm operator*(Quad q, double d) {
    return qMakePair(q, d);
}

QuadTerm operator*(double d, Quad q) {
    return q*d;
}

QuadExpression *operator+(QuadTerm t1, QuadTerm t2) {
    QuadExpression *e = new QuadExpression();
    e->addQuadTerm(t1);
    e->addQuadTerm(t2);
    return e;
}

QuadExpression *operator-(QuadTerm t1, QuadTerm t2) {
    return t1 + qMakePair(t2.first, -t2.second);
}

QuadExpression *operator+(QuadTerm t1, Term t2) {
    QuadExpression *e = new QuadExpression();
    e->addQuadTerm(t1);
    e->addTerm(t2);
    return e;
}

QuadExpression *operator-(QuadTerm t1, Term t2) {
    return t1 + qMakePair(t2.first, -t1.second);
}

QuadExpression *operator+(Term t1, QuadTerm t2) {
    return t2 + t1;
}

QuadExpression *operator-(Term t1, QuadTerm t2) {
    return t1 + qMakePair(t2.first, -t2.second);
}

QuadExpression *operator+(QuadTerm t, double d) {
    QuadExpression *e = new QuadExpression();
    e->addQuadTerm(t);
    e->addConst(d);
    return e;
}

QuadExpression *operator-(QuadTerm t, double d) {
    return t + (-d);
}

QuadExpression *operator+(double d, QuadTerm t) {
    return t + d;
}

QuadExpression *operator-(double d, QuadTerm t) {
    return qMakePair(t.first, -t.second) + d;
}

QuadExpression *operator+(QuadExpression *e, QuadTerm t) {
    e->addQuadTerm(t);
    return e;
}

QuadExpression *operator+(QuadExpression *e, Term t) {
    e->addTerm(t);
    return e;
}

QuadExpression *operator+(QuadTerm t, QuadExpression *e) {
    return e + t;
}

QuadExpression *operator+(Term t, QuadExpression *e) {
    return e + t;
}

QuadExpression *operator-(QuadExpression *e, QuadTerm t) {
    e->addQuadTerm(qMakePair(t.first, -t.second));
    return e;
}

QuadExpression *operator-(QuadExpression *e, Term t) {
    e->addTerm(qMakePair(t.first, -t.second));
    return e;
}
