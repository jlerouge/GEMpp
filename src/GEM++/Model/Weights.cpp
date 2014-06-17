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

Weights::Weights() : saveMode_(SUBSTITUTION) {
    weights_ = QHash<QString, double>();
    weights_.insert(getPrefix(SUBSTITUTION,GraphElement::VERTEX)+CONST_LABEL, DEFAULT_S_V_CONST_);
    weights_.insert(getPrefix(SUBSTITUTION,GraphElement::EDGE)+CONST_LABEL, DEFAULT_S_E_CONST_);
    weights_.insert(getPrefix(CREATION,GraphElement::VERTEX)+CONST_LABEL, DEFAULT_C_V_CONST_);
    weights_.insert(getPrefix(CREATION,GraphElement::EDGE)+CONST_LABEL, DEFAULT_C_E_CONST_);
}

Weights::Weights(const QString &substitution, const QString &creation) : Weights() {
    // Loads the configuration for substitution costs
    if(!substitution.isEmpty())
        fromFw(substitution, SUBSTITUTION);

    // Loads the configuration for creation costs
    if(!creation.isEmpty())
        fromFw(creation, CREATION);
}

Weights::Weights(Weights &other) : Weights() {
    for(auto it = other.getWeights().begin(); it != other.getWeights().end(); ++it)
        weights_.insert(it.key(), it.value());
}

Weights::~Weights() {}

void Weights::fromFw(const QString &filename, Operation op) {
    if(!filename.endsWith(".fw", Qt::CaseInsensitive))
        GEM_exception(QString("%1 is not a *.fw file.").arg(filename));

    QString buffer = FileStream::loadFile(filename);
    QRegExp vertices("nodes\\_features\\_weights");
    QRegExp edges("edges\\_features\\_weights");

    /* Begin parsing */
    int ibegin = vertices.indexIn(buffer);
    ibegin += vertices.matchedLength();
    int iend = edges.indexIn(buffer);
    QStringList sl = buffer.mid(ibegin,iend-ibegin).simplified().split(" ");

    // Vertices
    if(sl.size() > 1) {
        for(auto it = sl.begin(); it != sl.end(); it += 2) {
            if(it == sl.end()) break;
            weights_.insert(getPrefix(op, GraphElement::VERTEX)+(*it), (it+1)->toDouble());
        }
    }

    ibegin = iend + edges.matchedLength();
    sl = buffer.right(buffer.length()-ibegin).simplified().split(" ");

    // Edges
    if(sl.size() > 1) {
        for(auto it = sl.begin(); it != sl.end(); it += 2) {
            if(it == sl.end()) break;
            weights_.insert(getPrefix(op, GraphElement::EDGE)+(*it), (it+1)->toDouble());
        }
    }
    /* End parsing */
}

double Weights::getWeight(QString attribute, Operation op, GraphElement::Type t) const {
    if(weights_.contains(getPrefix(op, t)+attribute))
        return weights_[getPrefix(op, t)+attribute];
    else {
        /* The const weight is already defined by the constructor
           so we return the default non-const value */
        switch (op) {
            case SUBSTITUTION:
                switch(t) {
                    case GraphElement::VERTEX:
                        return DEFAULT_S_V;
                    case GraphElement::EDGE:
                        return DEFAULT_S_E;
                    default:
                        return 0;
                }
            case CREATION:
                switch(t) {
                    case GraphElement::VERTEX:
                        return DEFAULT_C_V;
                    case GraphElement::EDGE:
                        return DEFAULT_C_E;
                    default:
                        return 0;
                }
            default:
                break;
        }
    }

    // This should never happen.
    return 0;
}

double Weights::getWeight(QString prefixedAttr) const {
    if(weights_.contains(prefixedAttr))
        return weights_[prefixedAttr];

    GEM_exception(QString("Weights object doesn't contain any %2 weight.").arg(prefixedAttr));

    // This should never happen.
    return 0;
}

void Weights::setWeight(QString attribute, Operation op, GraphElement::Type t, double value) {
    setWeight(getPrefix(op, t)+attribute, value);
}

void Weights::setWeight(QString prefixedAttr, double value) {
    weights_.insert(prefixedAttr, value);
    //if(weights_.contains(prefixedAttr))
    //    weights_[prefixedAttr] = value;
    //else
    //    GEM_exception(QString("Weights object does not contain any %1 weight.").arg(prefixedAttr));
}

const QHash<QString, double> &Weights::getWeights() const {
    return weights_;
}

void Weights::print(Printer *p) {
    print(p, saveMode_);
}

void Weights::print(Printer *p, Operation op) {
    p->dump("nodes_features_weights");
    p->indent();
    QString prefix = getPrefix(op, GraphElement::VERTEX);
    QString attrName;
    for(auto att : weights_.keys()) {
        if(att.startsWith(prefix)) {
            attrName = att;
            attrName.replace(prefix, "");
            p->dump(QString("%1\t%2").arg(attrName).arg(weights_[att]));
        }
    }
    p->unindent();
    p->newLine();
    p->dump("edges_features_weights");
    p->indent();
    prefix = getPrefix(op, GraphElement::EDGE);
    for(auto att : weights_.keys()) {
        if(att.startsWith(prefix)) {
            attrName = att;
            attrName.replace(prefix, "");
            p->dump(QString("%1\t%2").arg(attrName).arg(weights_[att]));
        }
    }
    p->unindent();
    p->newLine();
}

void Weights::save(const QString &filename) {
    if(!filename.endsWith(".fw", Qt::CaseInsensitive))
        GEM_exception(QString("%1 is not a .fw file").arg(filename));
    FileStream::saveFile(this, filename);
}

void Weights::save(const QString &filename, Operation op) {
    setSaveMode(op);
    save(filename);
}

Weights::Operation Weights::getSaveMode() const {
    return saveMode_;
}

void Weights::setSaveMode(Operation op) {
    saveMode_ = op;
}

QString Weights::getPrefix(Operation op, GraphElement::Type t) const {
    QString prefix;
    switch(op) {
        case SUBSTITUTION:
            prefix = "S_";
            break;
        case CREATION:
            prefix = "C_";
            break;
        default:
            break;
    }
    switch(t) {
        case GraphElement::VERTEX:
            prefix += "V_";
            break;
        case GraphElement::EDGE:
            prefix += "E_";
            break;
        default:
            break;
    }
    return prefix;
}

double Weights::creationCost(GraphElement *e) {
    double cost = getWeight(CONST_LABEL, CREATION, e->getType());
    for(auto key : e->getNumericAttributes().keys())
        cost += getWeight(key, CREATION, e->getType())*e->getNumericAttribute(key);
    return cost;
}

double Weights::substitutionCost(GraphElement *e1, GraphElement *e2) {
    if(e1->getType() != e2->getType())
        GEM_exception(QString("There are no possible substitutions between elements of different types"));

    // Test if all symbolic attributes of e1 and e2 are the same
    for(auto key : e1->getSymbolicAttributes().keys()) {
        // Compare only symbolic attributes that have non-zero weight
        if(getWeight(key, SUBSTITUTION, e1->getType()) && (e1->getSymbolicAttribute(key).compare(e2->getSymbolicAttribute(key), Qt::CaseInsensitive) != 0))
            // e1 and e2 are of different types
            return e1->getCost()+e2->getCost();
    }

    // e1 and e2 are of the same type
    return weightedEuclideanDistance(e1, e2);
}

double Weights::weightedEuclideanDistance(GraphElement *e1, GraphElement *e2) {
    double d, res = getWeight(CONST_LABEL, SUBSTITUTION, e1->getType());
    for(auto key : e1->getNumericAttributes().keys()) {
        d = (e1->getNumericAttribute(key) - e2->getNumericAttribute(key))*getWeight(key, SUBSTITUTION, e1->getType());
        res += d*d;
    }
    return qSqrt(res);
}

void operator*=(Weights &w, double d) {
    for(auto it = w.getWeights().begin(); it != w.getWeights().end(); ++it)
        w.setWeight(it.key(), it.value()*d);
}

void operator+=(Weights &w1, Weights w2) {
    for(auto it = w1.getWeights().begin(); it != w1.getWeights().end(); ++it)
        w1.setWeight(it.key(), it.value()+w2.getWeight(it.key()));
}
