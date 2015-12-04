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
        QList<QList<Vertex *>> getCycles() const;

        /**
         * @brief Runs the extraction.
         */
        void extract();

    private:
        void depthFirstSearch(Vertex *root = 0, QList<Vertex *> parents = QList<Vertex *>());
        //QList<QList<Vertex *>> depthFirstSearch(Vertex *root = 0, Vertex *parent = 0);

        QSet<Vertex *> visitedVertices_;
        QSet<Edge *> visitedEdges_;

        QList<QList<Vertex *>> cycles_;

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
