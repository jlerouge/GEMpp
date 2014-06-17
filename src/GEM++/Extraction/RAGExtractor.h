#ifndef __RAGEXTRACTOR_H__
#define __RAGEXTRACTOR_H__

#include <QPoint>
#include "Extractor.h"
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

class DLL_EXPORT RegionAdjacencyGraphExtractor : public Extractor {
    public:
        RegionAdjacencyGraphExtractor();
        RegionAdjacencyGraphExtractor(const QString &input, const QString &output, const QString &metadata, ExtractionConfiguration *excfg);
        ~RegionAdjacencyGraphExtractor();
        Graph *getGraph();

    private:
        Graph *graph_;
        BinaryImage img_;
        int ct;

        void performExtraction();
        void invert(BinaryImage &img);
        QPoint getCentroid(BinaryImage &img, const GenPoint<int> &origin);
        int getArea(BinaryImage &img);
        bool areAdjacent(BinaryImage &im1, BoundingBox &bb1, BinaryImage &im2, BoundingBox &bb2);
        BinaryImage adjacencyImage(BinaryImage &im, BoundingBox &bb, BoundingBox &bbUnion);
};

#endif /*__RAGEXTRACTOR_H__*/
