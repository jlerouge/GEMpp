#ifndef GEMPP_PROBLEM_H
#define GEMPP_PROBLEM_H

#include "Graph.h"
#include "Weights.h"
#include "Core/Matrix.h"

typedef struct CostIndex {
        GraphElement::Type type;
        int queryIndex;
        int targetIndex;
} CostIndex;

class DLL_EXPORT Problem : public QObject, virtual public IPrintable, virtual public ISaveable {
        Q_OBJECT
    public:
        /**
         * @brief The Type enum indicates the type of matching involved.
         */
        enum Type{
            NONE,     /**< no matching performed */
            SUBGRAPH, /**< subgraph matching */
            GED,      /**< graph edit distance */
            COUNT
        };

        static const char *typeName[COUNT];
        static QString toName(Type type);
        static Type fromName(QString name);

        Problem(Type type, Graph *query, Graph *target, Problem *parent = 0);
        virtual ~Problem();

        Type getType() const;
        Graph *getQuery() const;
        Graph *getTarget() const;
        Problem *getParent() const;
        double getCost(GraphElement::Type type, int queryIndex, int targetIndex) const;
        double getCost(CostIndex costIndex) const;
        void addCost(GraphElement::Type type, int queryIndex, int targetIndex, double value);
        void addCost(CostIndex costIndex, double value);
        void computeCosts(Weights *weights);

        void print(Printer *p);
        void save(const QString &filename);

    signals:
        /**
         * @brief Notifies that a subproblem has to be solved before solving the main ::Problem.
         * @param subproblem the subproblem to solve
         * @param weights the cost weights to apply
         */
        void prepare(Problem *problem, Weights *weights);

        /**
         * @brief Notifies when a ::Problem is ready to be solved.
         * @param problem the problem that is ready
         */
        void ready(Problem *problem);

    protected:
        double computeCost(GraphElement *element, Graph *graph, Weights *weights);
        void computeGraphCost(Graph *g1, Graph *g2, Weights *weights, GraphElement::Type type, int queryIndex, int targetIndex);

    private slots:
        void updateCost(Problem *subproblem, double value);

    private:
        Type type_;
        Graph *query_;
        Graph *target_;
        Problem *parent_;
        Matrix<double> vCosts_;
        Matrix<double> eCosts_;
        QMap<Problem *, CostIndex> subproblems_;
        QMutex mutex_;
};

#endif /* GEMPP_PROBLEM_H */
