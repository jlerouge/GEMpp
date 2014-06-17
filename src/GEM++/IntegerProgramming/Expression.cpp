#include "Expression.h"

Expression::Expression() {
    const_ = 0;
}

void Expression::multiplyBy(double d) {
    const_ = const_ * d;
}

double Expression::getConst(){
    return const_;
}

void Expression::addConst(double d){
    const_ += d;
}

double Expression::eval() {
    return const_;
}

void Expression::print(Printer *p) {
    p->dump(this->toString());
}

QString Expression::toString() {
    return QString::number(const_);
}

void operator+=(Expression &e, double d) {
    e.addConst(d);
}

void operator-=(Expression &e, double d) {
    e.addConst(-d);
}
