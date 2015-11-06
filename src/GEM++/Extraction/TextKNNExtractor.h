#ifndef __TEXTKNNEXTRACTOR_H__
#define __TEXTKNNEXTRACTOR_H__

#include <QPoint>
#include "PairExtractor.h"
#include "Model/Graph.h"

using namespace qgar;

class DLL_EXPORT TextKNearestNeighborGraphExtractor : public PairExtractor {
    public:
        TextKNearestNeighborGraphExtractor();
        TextKNearestNeighborGraphExtractor(const QPair<QString, QString> &inputs, const QPair<QString, QString> &outputs,
                                           const QPair<QString, QString> &metadata, ExtractionConfiguration *excfg);
        ~TextKNearestNeighborGraphExtractor();
        Graph *getTargetGraph();
        Graph *getQueryGraph();

    private:
        Graph *query_;
        Graph *target_;

        void performExtraction();
};

#endif /*__TEXTKNNEXTRACTOR_H__*/
