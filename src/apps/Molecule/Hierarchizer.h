#ifndef GEMPP_HIERARCHIZER_H
#define GEMPP_HIERARCHIZER_H

#include <QSet>
#include "Core/Matrix.h"
#include "Model/Graph.h"

/**
 * @brief The Hierarchizer class implements the cycles detection
 * and the hierarchization of molecule graphs.
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
// FIXME: use PIVAJ Extractor formalism (and apply it to other extractors too)

class DLL_EXPORT Hierarchizer {
    public:
        /**
         * @brief Constructs a new Hierarchizer object with parameters.
         */
        Hierarchizer(Graph *input);

        /**
         * @brief Destructs a Hierarchizer object.
         */
        virtual ~Hierarchizer();

        /**
         * @brief Sets the input of the extraction.
         * @param input the input
         */
        void setInput(Graph *input);

        /**
         * @brief Returns the input of the extraction.
         * @return the input
         */
        Graph *getInput() const;

        /**
         * @brief Returns the output of the extraction.
         * @return the output
         */
        Graph *getOutput() const;

        /**
         * @brief Returns the detected cycles.
         * @return the output
         */
        QList<QSet<Vertex *>> getCycles() const;

        /**
         * @brief Returns the detected chains.
         * @return the output
         */
        QList<QSet<Edge *>> getChains() const;

        /**
         * @brief Runs the extraction.
         */
        void extract();

    private:
        void extractCycles();
        void dfsCycles(Vertex *root = 0, QList<Vertex *> parents = QList<Vertex *>());
        void filterCycles();
        void fusionCycles();
        void hierarchizeCycles();

        static bool isAdmissibleCycle(QSet<Vertex *> cycle);

        void extractChains();
        void filterChains();
        void fusionChains();
        void hierarchizeChains();

        static bool areChainable(Edge *e1, Edge *e2);
        static bool areMergeable(QSet<Edge *> chain1, QSet<Edge *> chain2);
        static bool isAdmissibleChain(QSet<Edge *> chain);

        QSet<Vertex *> visitedVertices_;
        QSet<Edge *> visitedEdges_;
        QList<QSet<Vertex *>> cycles_;
        QList<QSet<Edge *>> chains_;

        /**
         * @brief The input of the extraction.
         */
        Graph *input_;
        /**
         * @brief The output of the extraction.
         */
        Graph *output_;
};

#endif /*HIERARCHIZER_H*/
