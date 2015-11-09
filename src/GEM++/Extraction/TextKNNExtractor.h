#ifndef GEMPP_TEXTKNNEXTRACTOR_H
#define GEMPP_TEXTKNNEXTRACTOR_H

#include <QPoint>
#include "PairExtractor.h"
#include "Model/Graph.h"

using namespace qgar;

/**
 * @brief The TextKNearestNeighborGraphExtractor class allows
 * the extraction of text regions graphs on OCR'ed pages.
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
class DLL_EXPORT TextKNearestNeighborGraphExtractor : public PairExtractor {
    public:
        /**
         * @brief Constructs a new TextKNearestNeighborGraphExtractor object.
         */
        TextKNearestNeighborGraphExtractor();

        /**
         * @brief Constructs a TextKNearestNeighborGraphExtractor object with parameters.
         * @param inputs the pair of input filenames of the extraction
         * @param outputs the pair of output filenames of the extraction
         * @param metadata the pair of metadata filenames on the extraction
         * @param excfg configuration of the extractor
         */
        TextKNearestNeighborGraphExtractor(const QPair<QString, QString> &inputs,
                                           const QPair<QString, QString> &outputs,
                                           const QPair<QString, QString> &metadata,
                                           ExtractionConfiguration *excfg);
        /**
         * @brief Destructs a TextKNearestNeighborGraphExtractor object.
         */
        ~TextKNearestNeighborGraphExtractor();

        /**
         * @brief Returns the output query graph.
         * @return a graph
         */
        Graph *getQueryGraph();

        /**
         * @brief Returns the output target graph.
         * @return a graph
         */
        Graph *getTargetGraph();

    private:
        /**
         * @brief The output query graph.
         */
        Graph *query_;

        /**
         * @brief The output target graph.
         */
        Graph *target_;

        void performExtraction();
};

#endif /*TEXTKNNEXTRACTOR_H*/
