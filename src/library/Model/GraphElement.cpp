#include "GraphElement.h"

const char* GraphElement::typeName[GraphElement::COUNT] = {
    "graph",
    "node",
    "edge"
};

GraphElement::Type GraphElement::toType(QString name) {
    for(Type t = (Type)0; t < COUNT; t = (Type)((int)t + 1))
        if(QString(typeName[t]).startsWith(name, Qt::CaseInsensitive))
            return t;
    Exception(QString("Type '%1' not recognized, please use v(ertex) or e(dge).").arg(name));
    return COUNT;
}

QString GraphElement::toName(Type type) {
    return typeName[type];
}

GraphElement::GraphElement(Type type) : Identified(), Indexed() {
    type_ = type;
    cost_ = 0;
}

GraphElement::GraphElement(const GraphElement &other) : Identified(other), Indexed(other) {
    type_ = other.getType();
    cost_ = other.getCost();
    for(QString name : other.getAttributes().keys())
        addAttribute(name, new Attribute(*(other.getAttribute(name))));
}

GraphElement::~GraphElement() {
    qDeleteAll(attributes_.values());
    attributes_.clear();
}

double GraphElement::getCost() const {
    return cost_;
}

void GraphElement::setCost(double d) {
    cost_ = d;
}

GraphElement::Type GraphElement::getType() const {
    return type_;
}

void GraphElement::setType(Type type) {
    type_ = type;
}

void GraphElement::addAttribute(const QString &name, QMetaType::Type type, QVariant value) {
    addAttribute(name, new Attribute(type, value));
}

void GraphElement::addAttribute(const QString &name, Attribute *attribute) {
    attributes_.insert(name, attribute);
}

bool GraphElement::hasAttribute(const QString &name) const {
    return attributes_.contains(name);
}

Attribute *GraphElement::getAttribute(const QString &name) const {
    if(!hasAttribute(name))
        Exception(QString("%1 element \"%2\" has no attribute \"%3\"").arg(toName(type_), getID(), name));
    return attributes_[name];
}

const QMap<QString, Attribute *> &GraphElement::getAttributes() const {
    return attributes_;
}

void GraphElement::print(Printer *p) {
    p->dump(getID());
}

QDomElement GraphElement::save(QDomDocument *document) {
    QDomElement element = document->createElement(toName(getType()));
    QDomElement attr, attrType;
    QDomText attrText;
    for(QString key : attributes_.keys()) {
        attr = document->createElement("attr");
        attr.setAttribute("name", key);
        attrType = document->createElement(Attribute::toName(attributes_[key]->getType()));
        attrText = document->createTextNode(attributes_[key]->getValue().toString());
        attrType.appendChild(attrText);
        attr.appendChild(attrType);
        element.appendChild(attr);
    }
    return element;
}

void GraphElement::load(QDomElement element) {
    QDomElement attr;
    QMetaType::Type attrMetaType;
    attr = element.firstChildElement("attr");
    while(!attr.isNull()) {
        attrMetaType = Attribute::toType(attr.firstChildElement().tagName().toLower());
        addAttribute(attr.attribute("name"), attrMetaType, Attribute::toVariant(attrMetaType, attr.firstChildElement().text()));
        attr = attr.nextSiblingElement("attr");
    }
}
