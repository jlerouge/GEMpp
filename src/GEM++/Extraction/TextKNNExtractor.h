#ifndef __TEXTKNNEXTRACTOR_H__
#define __TEXTKNNEXTRACTOR_H__

#include <QPoint>
#include "PairExtractor.h"
#include "Zernike.h"
#include "BinaryPNG.h"
#include "../Model/Graph.h"
#include "qgarlib/CleanedBinaryImage.h"
#include "qgarlib/Dist34BlackCCImage.h"
#include "qgarlib/HysteresisBinaryImage.h"
#include "qgarlib/LabeledSkeletonImage.h"
#include "qgarlib/LinkedChainList.h"
#include "qgarlib/PbmFile.h"
#include "qgarlib/ConnectedComponents.h"
#include "qgarlib/DilatedBinaryImage.h"
#include "qgarlib/ErodedBinaryImage.h"

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
