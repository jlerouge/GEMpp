#include "LinearConstraint.h"

LinearConstraint::LinearConstraint(LinearExpression *exp, Relation relation, double rhs, QString uid) :
    Constraint(static_cast<Expression *>(exp), relation, rhs, "L"+uid) {}

LinearConstraint::~LinearConstraint() {
    delete exp_;
}

LinearExpression *LinearConstraint::getLinearExpression() {
    return dynamic_cast<LinearExpression *>(exp_);
}

bool LinearConstraint::eval() {
    double lhs = getLinearExpression()->eval();
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

void LinearConstraint::print(Printer *p) {
    p->dump(LinearConstraint::toString());
}

QString LinearConstraint::toString() {
    QString s = getLinearExpression()->toString();

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
