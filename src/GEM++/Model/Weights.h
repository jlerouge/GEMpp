#ifndef GEMPP_WEIGHTS_H
#define GEMPP_WEIGHTS_H

#include <QStringList>
#include <qmath.h>
#include "GraphElement.h"
#include "WeightHash.h"
#include "../Core/IXmlSerializable.h"

#define GEMPP_DEFAULT_S_CONST 0.0
#define GEMPP_DEFAULT_S_ATTR 1.0
#define GEMPP_DEFAULT_S_POWER 2

#define GEMPP_DEFAULT_C_CONST 1.0
#define GEMPP_DEFAULT_C_ATTR 0.0
#define GEMPP_DEFAULT_C_POWER 1

class DLL_EXPORT Weights : virtual public IXmlSerializable {
        friend class QConfigurationDialog;
    public:
        enum Operation{
            CREATION = 0,
            SUBSTITUTION,
            COUNT
        };

        static const char* operationName[COUNT];
        static Operation fromName(QString opName);
        static QString toName(Operation op);

        Weights(const QString &substitution = "", const QString &creation = "");
        virtual ~Weights();

        bool containsWeight(Operation op, GraphElement::Type t, QString attribute) const;
        Weight* getWeight(Operation op, GraphElement::Type t, QString attribute) const;
        Weight* getWeightOrDefault(Operation op, GraphElement::Type t, QString attribute);
        void addWeight(Operation op, GraphElement::Type t, QString attribute, Weight::Type type, uint power, double value);

        double getDefaultWeight(Operation op) const;
        uint getDefaultPower(Operation op) const;

        Operation getCurrentOperation() const;
        void setCurrentOperation(Operation op);

        void print(Printer *p, Operation op);
        void save(const QString &filename, Operation op);

        double creationCost(GraphElement *e) const;
        double substitutionCost(GraphElement *e1, GraphElement *e2) const;

        WeightHash *getWeights(Operation op, GraphElement::Type t) const;

    protected:
        void fromFile(const QString &filename, Operation op);
        void fromXML(const QString &filename, Operation op);
        virtual void fromXML(const QString &filename);
        void toXML(Operation op);
        virtual void toXML();

    private:
        double weightedCost(GraphElement *e1, GraphElement *e2 = 0) const;

        QHash<QPair<Operation, GraphElement::Type>, WeightHash *> weights_;
        Operation currentOperation_;
};

void operator*=(Weights &w, double d);
void operator+=(Weights &w1, Weights w2);
uint levenshtein(QString s1, QString s2);

#endif /*WEIGHTS_H*/
