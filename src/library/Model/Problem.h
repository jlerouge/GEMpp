#ifndef GEMPP_PROBLEM_H
#define GEMPP_PROBLEM_H

#include "Graph.h"
#include "Weights.h"
#include "Core/Matrix.h"

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

        Problem(Type t, Graph *query, Graph *target);
        virtual ~Problem();

        Graph *getQuery() const;
        Graph *getTarget() const;
        double getCost(int iQuery, int iTarget, GraphElement::Type type) const;
        void addCost(int iQuery, int iTarget, double value, GraphElement::Type type);
        void computeCosts(Weights *weights);
        Type getType() const;

        void print(Printer *p);
        void save(const QString &filename);

    signals:
        /**
         * @brief Solves a subproblem coming from a parent ::Problem dealing
         * with hierarchical ::Graphs, using the same ::Configuration as for the
         * original ::Problem.
         * @param subproblem the subproblem to solve
         * @param type the ::GraphElement::Type containing the hierarchical subgraphs
         * @param iQuery the index of the query ::GraphElement
         * @param iTarget the index of the target ::GraphElement
         */
        void solveSubProblem(Problem *subProblem, Weights *weights, GraphElement::Type type, int iQuery, int iTarget);

    protected:
        double computeCost(Vertex *vertex, Graph *graph, Weights *weights);
        void computeGraphCost(Graph *g1, Graph *g2, Weights *weights, GraphElement::Type type, int iQuery, int iTarget);

    private:
        Type type_;
        Graph *query_;
        Graph *target_;
        Matrix<double> vCosts_;
        Matrix<double> eCosts_;
        QList<Problem *> subProblems_;
};

#endif /* GEMPP_PROBLEM_H */
