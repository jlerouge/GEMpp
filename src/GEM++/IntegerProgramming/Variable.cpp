#include "Variable.h"

Variable::Variable(QString id, Type type, int lowerBound, int upperBound) : Identified(id), type_(type) {
    activate(lowerBound, upperBound);
    columns_ = QHash<QString, double>();
    value_ = lowerBound_;
}

Variable::~Variable() {}

Variable::Type Variable::getType() {
    return type_;
}

void Variable::setType(Type type) {
    type_ = type;
}

void Variable::setValue(int val) {
    if(val < lowerBound_ || val > upperBound_)
        GEM_exception(QString("Illegal value assignment for variable %1 : %2 is out of bounds [%3;%4]").arg(id_).arg(val).arg(lowerBound_).arg(upperBound_));
    value_ = val;
}

int Variable::eval() {
    return value_;
}

bool Variable::isActive() {
    return (lowerBound_ != 0 || upperBound_ != 0);
}

int Variable::getLowerBound() {
    return lowerBound_;
}

void Variable::setLowerBound(int lowerBound) {
    if(lowerBound > upperBound_)
        GEM_exception(QString("Illegal lower bound assignment for variable %1 : LB=%2 > UB=%3").arg(id_).arg(lowerBound).arg(upperBound_));
    if(type_ == BINARY && lowerBound != 0)
        GEM_exception(QString("Illegal lower bound assignment for variable %1 : LB=%2 must be 0").arg(id_).arg(lowerBound));
    lowerBound_ = lowerBound;
}

int Variable::getUpperBound() {
    return upperBound_;
}

void Variable::setUpperBound(int upperBound) {
    if(upperBound < lowerBound_)
        GEM_exception(QString("Illegal upper bound assignment for variable %1 : UB=%2 < LB=%3").arg(id_).arg(upperBound).arg(lowerBound_));
    if(type_ == BINARY && upperBound != 1 && upperBound != 0)
        GEM_exception(QString("Illegal upper bound assignment for variable %1 : UB=%2 must be 0 or 1").arg(id_).arg(upperBound));
    upperBound_ = upperBound;
}

void Variable::activate(int lowerBound, int upperBound) {
    switch(type_) {
        case BOUNDED:
            lowerBound_ = lowerBound;
            upperBound_ = upperBound;
            break;
        case CONTINUOUS:
            lowerBound_ = lowerBound;
            upperBound_ = upperBound;
            break;
        case BINARY:
            lowerBound_ = 0;
            upperBound_ = 1;
            break;
    }
    if(lowerBound_ > upperBound_)
        GEM_exception(QString("Illegal bounds for variable %1 : LB=%2 > UB=%3").arg(id_).arg(lowerBound_).arg(upperBound_));
}

void Variable::deactivate() {
    lowerBound_ = 0;
    upperBound_ = 0;
}

void Variable::addColumn(QString id, double d) {
    columns_.insert(id, d);
}

QHash<QString, double> &Variable::getColumns() {
    return columns_;
}

double Variable::getColumn(QString id) {
    return columns_[id];
}

void Variable::print(Printer *p) {
    p->dump(id_);
}

Variable::operator Term() const {
    return qMakePair((Variable *)this, 1.0);
}

bool operator==(Quad q1, Quad q2) {
    return (q1.first == q2.first && q1.second == q2.second) || (q1.first == q2.second && q1.second == q2.first);
}

bool isActive(QuadTerm t) {
    return (t.first.first->isActive() && t.first.second->isActive());
}
