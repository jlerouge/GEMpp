#include "Weight.h"

const char* Weight::typeName[Weight::COUNT] = {
    "Constant",
    "Discrete",
    "Numeric",
    "String"
};

Weight::Type Weight::fromName(QString name) {
    for(Type type = (Type)0; type < COUNT; type = (Type)((int)type + 1))
        if(QString(typeName[type]).startsWith(name, Qt::CaseInsensitive))
            return type;
    GEM_exception(QString("Type '%1' not recognized, please use c(onstant), d(iscrete), n(umeric) or s(tring).").arg(name));
    return COUNT;
}

QString Weight::toName(Type type) {
    return typeName[type];
}

Weight::Weight(Type type, uint power, double value) : type_(type), power_(power), value_(value) {}

Weight::Weight(Weight &other) {
    setType(other.getType());
    setPower(other.getPower());
    setValue(other.getValue());
}

Weight::~Weight() {}

Weight::Type Weight::getType() const {
    return type_;
}

Weight::Type &Weight::type() {
    return type_;
}

void Weight::setType(Type type) {
    type_ = type;
}

uint Weight::getPower() const {
    return power_;
}

uint &Weight::power() {
    return power_;
}

void Weight::setPower(uint power) {
    power_ = power;
}

double Weight::getValue() const {
    return value_;
}

double &Weight::value() {
    return value_;
}

void Weight::setValue(double value) {
    value_ = value;
}
