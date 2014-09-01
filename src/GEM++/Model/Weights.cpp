#include "Weights.h"

const char* Weights::operationName[Weights::COUNT] = {
    "Creation",
    "Substitution"
};

Weights::Operation Weights::fromName(QString opName) {
    for(Operation op = (Operation)0; op < COUNT; op = (Operation)((int)op + 1))
        if(QString(operationName[op]).startsWith(opName, Qt::CaseInsensitive))
            return op;
    GEM_exception(QString("Operation '%1' not recognized, please use c(reation) or s(ubstitution).").arg(opName));
    return COUNT;
}

QString Weights::toName(Operation op) {
    return operationName[op];
}

Weights::Weights(const QString &substitution, const QString &creation) : IXmlSerializable() {
    currentOperation_ = SUBSTITUTION;
    for(Operation op = (Operation)0; op < COUNT; op = (Operation)((int)op + 1))
        for(GraphElement::Type t = (GraphElement::Type)0; t < GraphElement::COUNT; t = (GraphElement::Type)((int)t + 1))
            weights_.insert(qMakePair(op,t), new WeightHash());

    fromFile(substitution, SUBSTITUTION);
    fromFile(creation, CREATION);

    for(Operation op = (Operation)0; op < COUNT; op = (Operation)((int)op + 1))
        for(GraphElement::Type t = (GraphElement::Type)0; t < GraphElement::COUNT; t = (GraphElement::Type)((int)t + 1))
            if(!containsWeight(op, t, CONST_LABEL))
                addWeight(op, t, CONST_LABEL, Weight::CONSTANT, 1, (op == SUBSTITUTION)? DEFAULT_S_CONST : DEFAULT_C_CONST);
}

Weights::~Weights() {
    clean();
    for(auto wh : weights_)
        delete wh;
}

bool Weights::containsWeight(Operation op, GraphElement::Type t, QString attribute) const {
    return getWeights(op,t)->contains(attribute);
}

Weight *Weights::getWeight(Operation op, GraphElement::Type t, QString attribute) const {
    if(!containsWeight(op, t, attribute))
        GEM_exception(QString("Weights object doesn't contain any %1 weight for %2 attribute \"%3\".").arg(toName(op), GraphElement::toName(t), attribute));
    return getWeights(op,t)->value(attribute);
}

void Weights::addWeight(Operation op, GraphElement::Type t, QString attribute, Weight::Type type, uint power, double value) {
    if(containsWeight(op, t, attribute))
        GEM_exception(QString("Weights object already contains a %1 weight for %2 attribute \"%3\".").arg(toName(op), GraphElement::toName(t), attribute));

    Weight *w = new Weight(type, power, value);
    getWeights(op,t)->insert(attribute, w);
}

double Weights::getDefaultWeight(Operation op) const {
    return (op == SUBSTITUTION) ? DEFAULT_S_ATTR : DEFAULT_C_ATTR;
}

uint Weights::getDefaultPower(Operation op) const {
    return (op == SUBSTITUTION) ? DEFAULT_S_POWER : DEFAULT_C_POWER;
}

WeightHash *Weights::getWeights(Operation op, GraphElement::Type t) const {
    return weights_[qMakePair(op, t)];
}

void Weights::fromFile(const QString &filename, Operation op) {
    if(!filename.isEmpty()) {
        if(!filename.endsWith(".fw", Qt::CaseInsensitive))
            GEM_exception(QString("%1 is not a *.fw file.").arg(filename));
        // Loads the weights configuration file
        fromXML(filename, op);
    }
}

void Weights::fromXML(const QString &filename, Operation op) {
    setCurrentOperation(op);
    fromXML(filename);
}

void Weights::fromXML(const QString &filename) {
    clean();
    QFile file(filename);
    if(!file.open(QFile::ReadOnly | QFile::Text))
        GEM_exception(QString("Error while loading %1 : %2").arg(filename, file.errorString()));

    /* Begin parsing */
    doc_ = new QDomDocument();
    doc_->setContent(&file, false);
    QDomElement attributes, attribute;
    QString name = "";
    Weight::Type type;
    uint power;
    double value = getDefaultWeight(currentOperation_);

    for(GraphElement::Type t = (GraphElement::Type)0; t < GraphElement::COUNT; t = (GraphElement::Type)((int)t + 1)) {
        attributes = doc_->documentElement().firstChildElement((t == GraphElement::VERTEX)? "nodes" : "edges");
        if(attributes.hasAttribute("mode"))
            getWeights(currentOperation_, t)->setMode(WeightHash::fromName(attributes.attribute("mode")));
        if(attributes.hasAttribute("root"))
            getWeights(currentOperation_, t)->setRoot(attributes.attribute("root").toUInt());
        attribute = attributes.firstChildElement("attribute");
        while(!attribute.isNull()) {
            name = (attribute.hasAttribute("name"))? attribute.attribute("name") : "";
            type = Weight::fromName(attribute.attribute("type"));
            if(type == Weight::CONSTANT)
                name = CONST_LABEL;
            if(attribute.hasAttribute("power"))
                power = attribute.attribute("power").toUInt();
            else
                power = getDefaultPower(currentOperation_);
            value = attribute.text().toDouble();
            addWeight(currentOperation_, t, name, type, power, value);
            attribute = attribute.nextSiblingElement("attribute");
        }
    }
    /* End parsing */

    file.close();
}

void Weights::toXML(Operation op) {
    setCurrentOperation(op);
    toXML();
}

void Weights::toXML() {
    clean();
    doc_ = new QDomDocument();
    QDomElement weights, attributes, attribute;
    QDomText valText;
    Weight *w;
    weights = doc_->createElement("weights");
    for(GraphElement::Type t = (GraphElement::Type)0; t < GraphElement::COUNT; t = (GraphElement::Type)((int)t + 1)) {
        attributes = doc_->createElement((t == GraphElement::VERTEX)? "nodes" : "edges");
        for(auto key : getWeights(currentOperation_,t)->keys()) {
            w = getWeights(currentOperation_,t)->value(key);
            attribute = doc_->createElement("attribute");
            attribute.setAttribute("name", key);
            attribute.setAttribute("power", w->getPower());
            attribute.setAttribute("type", Weight::toName(w->getType()));
            valText = doc_->createTextNode(QString::number(w->getValue()));
            attribute.appendChild(valText);
            attributes.appendChild(attribute);
        }
        weights.appendChild(attributes);
    }
    doc_->appendChild(weights);
}

void Weights::print(Printer *p, Operation op) {
    setCurrentOperation(op);
    IXmlSerializable::print(p);
}

void Weights::save(const QString &filename, Operation op) {
    setCurrentOperation(op);
    IXmlSerializable::save(filename);
}

Weights::Operation Weights::getCurrentOperation() const {
    return currentOperation_;
}

void Weights::setCurrentOperation(Operation op) {
    currentOperation_ = op;
}

double Weights::creationCost(GraphElement *e) const {
    return weightedCost(e);
}

double Weights::substitutionCost(GraphElement *e1, GraphElement *e2) const {
    if(e1->getType() != e2->getType())
        GEM_exception(QString("There are no possible substitutions between elements of different types"));

    // Test if all symbolic attributes of e1 and e2 are the same
    for(auto key : e1->getSymbolicAttributes().keys()) {
        // Compare only symbolic attributes that have non-zero weight
        if((getWeight(SUBSTITUTION, e1->getType(), key) != 0) && (e1->getSymbolicAttribute(key).compare(e2->getSymbolicAttribute(key), Qt::CaseInsensitive) != 0))
            // e1 and e2 are of different types
            return e1->getCost()+e2->getCost();
    }

    // e1 and e2 are of the same type
    return weightedCost(e1, e2);
}

double Weights::weightedCost(GraphElement *e1, GraphElement *e2) const {
    Operation op = (e2 == 0)? CREATION : SUBSTITUTION;
    GraphElement::Type type = e1->getType();
    Weight *w = getWeight(op, type, CONST_LABEL);
    double total_cost = pow(w->getValue(), w->getPower());
    double weight, cost;
    uint power;
    QList<QString> keys = e1->getNumericAttributes().keys();
    keys.append(e1->getStringAttributes().keys());

    for(auto key : keys) {
        try {
            w = getWeight(op, type, key);
            weight = w->getValue();
            power = w->getPower();
        } catch (std::exception &e) {
            weight = getDefaultWeight(op);
            power = getDefaultPower(op);
        }
        switch(op) {
            case SUBSTITUTION:
                if(e1->getNumericAttributes().contains(key)) {
                    cost = e1->getNumericAttribute(key) - e2->getNumericAttribute(key);
                } else {
                    cost = levenshtein(e1->getStringAttribute(key), e2->getStringAttribute(key));
                }
                break;
            case CREATION:
                if(e1->getNumericAttributes().contains(key)) {
                    cost = e1->getNumericAttribute(key);
                } else {
                    cost = e1->getStringAttribute(key).size();
                }
                break;
            default:
                break;
        }
        cost = pow(fabs(weight*cost), power);
        switch(getWeights(op, type)->getMode()) {
            case WeightHash::ADD:
                total_cost += cost;
                break;
            case WeightHash::MULTIPLY:
                total_cost *= cost;
                break;
            default:
                break;
        }
    }

    uint root = getWeights(op, type)->getRoot();
    if(root > 1)
        total_cost = pow(total_cost, 1.0/root);
    return total_cost;
}

void operator*=(Weights &w, double d) {
    for(Weights::Operation op = (Weights::Operation)0; op < Weights::COUNT; op = (Weights::Operation)((int)op + 1))
        for(GraphElement::Type t = (GraphElement::Type)0; t < GraphElement::COUNT; t = (GraphElement::Type)((int)t + 1))
            for(auto it = w.getWeights(op, t)->begin(); it != w.getWeights(op,t)->end(); ++it)
                w.getWeight(op, t, it.key())->value() *= d;
}

void operator+=(Weights &w1, Weights w2) {
    for(Weights::Operation op = (Weights::Operation)0; op < Weights::COUNT; op = (Weights::Operation)((int)op + 1))
        for(GraphElement::Type t = (GraphElement::Type)0; t < GraphElement::COUNT; t = (GraphElement::Type)((int)t + 1))
            for(auto it = w1.getWeights(op, t)->begin(); it != w1.getWeights(op, t)->end(); ++it)
                w1.getWeight(op, t, it.key())->value() += w2.getWeight(op, t, it.key())->getValue();
}

uint levenshtein(QString s1, QString s2) {
    const int len1 = s1.size(), len2 = s2.size();
    QVector<uint> col(len2+1), prevCol(len2+1);
    for (int i = 0; i < prevCol.size(); i++)
        prevCol[i] = i;
    for (int i = 0; i < len1; i++) {
        col[0] = i+1;
        for (int j = 0; j < len2; j++)
            col[j+1] = qMin(qMin(prevCol[1 + j] + 1, col[j] + 1),
                    prevCol[j] + (s1[i]==s2[j] ? 0 : 1));
        col.swap(prevCol);
    }
    return prevCol[len2];
}
