#include "GraphElement.h"

const char* GraphElement::typeName[GraphElement::COUNT] = {
    "vertex",
    "edge"
};

GraphElement::Type GraphElement::fromName(QString name) {
    for(Type t = (Type)0; t < COUNT; t = (Type)((int)t + 1))
        if(QString(typeName[t]).startsWith(name, Qt::CaseInsensitive))
            return t;
    Exception(QString("Type '%1' not recognized, please use v(ertex) or e(dge).").arg(name));
    return COUNT;
}

QString GraphElement::toName(Type type) {
    return typeName[type];
}

GraphElement::GraphElement() : Identified(), Indexed() {
    type_ = COUNT;
    cost_ = 0;
}

GraphElement::GraphElement(const GraphElement &other) : Identified(other), Indexed(other) {
    cost_ = other.getCost();
    type_ = other.getType();
    numericAttributes_ = other.getNumericAttributes();
    stringAttributes_ = other.getStringAttributes();
    symbolicAttributes_ = other.getSymbolicAttributes();
}

GraphElement::~GraphElement() {}

double GraphElement::getCost() const {
    return cost_;
}

void GraphElement::setCost(double d) {
    cost_ = d;
}

GraphElement::Type GraphElement::getType() const {
    return type_;
}

void GraphElement::addNumericAttribute(const QString &attribute, double value) {
    numericAttributes_.insert(attribute, value);
}

double GraphElement::getNumericAttribute(QString attribute) const {
    return numericAttributes_[attribute];
}

void GraphElement::addStringAttribute(const QString &attribute, const QString &value) {
    stringAttributes_.insert(attribute, value);
}

QString GraphElement::getStringAttribute(const QString &attribute) const {
    return stringAttributes_[attribute];
}

void GraphElement::addSymbolicAttribute(const QString &attribute, const QString &value) {
    symbolicAttributes_.insert(attribute, value);
}

QString GraphElement::getSymbolicAttribute(const QString &attribute) const {
    return symbolicAttributes_[attribute];
}

const QMap<QString, double>& GraphElement::getNumericAttributes() const {
    return numericAttributes_;
}

const QMap<QString, QString>& GraphElement::getStringAttributes() const {
    return stringAttributes_;
}

const QMap<QString, QString>& GraphElement::getSymbolicAttributes() const {
    return symbolicAttributes_;
}

void GraphElement::print(Printer *p) {
    p->dump(id_);
}
