#include "QuadConstraint.h"

QuadConstraint::QuadConstraint(QuadExpression *exp, Relation relation, double rhs, QString uid) :
    Constraint(static_cast<Expression *>(exp), relation, rhs, "Q"+uid) {}

QuadConstraint::~QuadConstraint() {
    delete exp_;
}

QuadExpression *QuadConstraint::getQuadExpression() {
    return dynamic_cast<QuadExpression *>(exp_);
}

bool QuadConstraint::eval() {
    double lhs = getQuadExpression()->eval();
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

void QuadConstraint::print(Printer *p) {
    p->dump(QuadConstraint::toString());
}

QString QuadConstraint::toString() {
    QString s = getQuadExpression()->toString();
    // Remove the constant
    QStringList ss = s.split(" ");
    ss.removeFirst();
    ss.removeFirst();
    s = ss.join(" ");
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
    s.append(QString("%1").arg(rhs_ - exp_->getConst()));
    return s;
}
