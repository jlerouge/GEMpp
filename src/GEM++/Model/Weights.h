#ifndef __WEIGHTS_H__
#define __WEIGHTS_H__

#include <QHash>
#include <QStringList>
#include <qmath.h>
#include "GraphElement.h"
#include "../Core/FileStream.h"
#include "../Core/ISaveable.h"

class DLL_EXPORT Weights : virtual public IPrintable, virtual public ISaveable {
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

        Weights();
        Weights(const QString &substitution, const QString &creation);
        Weights(Weights &other);
        virtual ~Weights();

        double getWeight(QString attribute, Operation op, GraphElement::Type t) const;
        double getWeight(QString prefixedAttr) const;
        void setWeight(QString attribute, Operation op, GraphElement::Type t, double value);
        void setWeight(QString prefixedAttr, double value);
        const QHash<QString, double> &getWeights() const;
        Operation getSaveMode() const;
        void setSaveMode(Operation op);

        void print(Printer *p);
        void print(Printer *p, Operation op);
        void save(const QString &filename);
        void save(const QString &filename, Operation op);


        double creationCost(GraphElement *e);
        double substitutionCost(GraphElement *e1, GraphElement *e2);

    protected:
        void fromFw(const QString &filename, Operation op);

    private:
        QString getPrefix(Operation op, GraphElement::Type t) const;
        double weightedEuclideanDistance(GraphElement *e1, GraphElement *e2);

        QHash<QString, double> weights_;
        Operation saveMode_;
};
void operator*=(Weights &w, double d);
void operator+=(Weights &w1, Weights w2);

#endif /*__WEIGHTS_H__*/
