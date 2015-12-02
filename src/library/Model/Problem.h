#ifndef GEMPP_PROBLEM_H
#define GEMPP_PROBLEM_H

#include "Graph.h"
#include "Weights.h"
#include "Core/Matrix.h"

class DLL_EXPORT Problem : virtual public IPrintable, virtual public ISaveable {
    public:
        /**
         * @brief The Type enum indicates the type of matching involved.
         */
        enum Type{
            NONE, /**< no matching performed */
            SUBGRAPH, /**< subgraph matching */
            GED, /**< graph edit distance */
            COUNT
        };

        static const char *typeName[COUNT];
        static QString toName(Type type);
        static Type fromName(QString name);

        Problem(Type t, const QString &pattern, const QString &target, const QString &substitution, const QString &creation);
        Problem(Type t, Graph *pattern, Graph *target, Weights *weights = 0);
        virtual ~Problem();

        Graph *getQuery() const;
        Graph *getTarget() const;
        double getCost(int iQuery, int iTarget, GraphElement::Type type) const;
        void addCost(int iQuery, int iTarget, double value, GraphElement::Type type);
        void computeCosts(Weights *weights);
        Type getType() const;

        void print(Printer *p);
        void save(const QString &filename);

    private:
        Type type_;
        Graph *pattern_;
        Graph *target_;
        Matrix<double> vCosts_;
        Matrix<double> eCosts_;
        bool deleteGraphs_;
};

#endif /* GEMPP_PROBLEM_H */
